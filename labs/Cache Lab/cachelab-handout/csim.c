#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
typedef struct
{
    int valid_bits;//表示当前cache_line是否被填充
    unsigned tag;
    int lru_stamp;
} cache_line;
int s, E, b, S;
int hit = 0, miss = 0, eviction = 0;
char *filepath = NULL;
cache_line **cache=NULL;

void init()
{
    // 相当于SxE大小的矩阵，因为用不到block offset，所以可以不考虑他
    cache = (cache_line **)malloc(sizeof(cache_line*) * S);
    for (int i = 0; i < S; i++)
    {
        *(cache + i) = (cache_line *)malloc(sizeof(cache_line) * E);
    }
    // 上述代码分配空间，下面进行初始化
    for (int i = 0; i < S; i++)
    {
        for (int j = 0; j < E; j++)
        {
            cache[i][j].valid_bits = 0;
            cache[i][j].tag = 0xffffffff;
            cache[i][j].lru_stamp = 0;
        }
    }
}

int find_max_time(unsigned s_addr){
    int max_stamp=0;
    int max_idx=0;
    for(int i=0;i<E;i++){
        if(cache[s_addr][i].lru_stamp>max_stamp){
            max_stamp=cache[s_addr][i].lru_stamp;
            max_idx=i;
        }

    }
    return max_idx;

}

void update_cache(unsigned address)
{
/*
    这个函数把所有的情况都包含了（也即包含了L,M,S，因为这个三个指令的特点就是都会先查看是否hit，
    如果没有hit，则会检测对应的set的所有line，如果有空位就放进去，也就是直接映射。如果没有空位，则会
    导致冲突，从而发生替换。L和S好解释，都需要hit miss 以及eviction检测，而M则是L和S的结合，其也是
    需要hit，miss,eviction检测,但是它是两次，所以M需要调用两次这个函数）

*/

    //获取set的编号和tag
    unsigned s_addr=(address>>b) & ((0xffffffff)>>(32-s));
    unsigned tag_addr=address>>(s+b);
    //检测hit
    for (int i = 0; i < E; i++)
    {
        if(cache[s_addr][i].tag==tag_addr){
            //说明命中了，需要更新lru
            hit++;
            cache[s_addr][i].lru_stamp=0;

            return ;
        }
    }
    //发现没有命中，则需要看看是否有空位
    for (int i = 0; i < E; i++){
        if(cache[s_addr][i].valid_bits==0){
            cache[s_addr][i].valid_bits=1;
            cache[s_addr][i].tag=tag_addr;
            cache[s_addr][i].lru_stamp=0;
            miss++;
            return;
        }
    }
    //发现没有空位置，则需要LRU替换,注意是组内替换
    //先找出最大的时间戳的位置
    int max_line=find_max_time(s_addr);
    miss++;
    eviction++;
    cache[s_addr][max_line].tag=tag_addr;
    cache[s_addr][max_line].lru_stamp=0;   
}

void update_time(){
    for (int i = 0; i < S; i++)
    {
       for (int j = 0; j < E; j++)
       {
            {
                //这个位置有填充
                if(cache[i][j].valid_bits==1){
                    cache[i][j].lru_stamp++;
                }
            }
       }
       
    }
    
}

int main(int argc, char **argv)
{
    int opt;
    /* looping over arguments */
    /*
        getop挺好用，x:表示 -x必须带有参数也即形如 -x 6的形式
        6就存在这个optarg中（字符串的形式）
    */
    while (-1 != (opt = getopt(argc, argv, "s:E:b:t:")))
    {
        /* determine which argument it’s processing */
        switch (opt)
        {
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            filepath = optarg;
            break;
        }
    }
    // S表示set的个数
    S = 1 << s;
    // 初始化cache内存
    init();
    // 读取文件内容
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        printf("There is no such file!");
        exit(-1);
    }
    char op;
    unsigned address;
    int size;
    while (fscanf(file, " %c %x,%d", &op, &address, &size) > 0)
    {
        if(op=='I'){
            continue;
        }else{
             update_cache(address);
             if(op=='M'){
                update_cache(address);
             }
             
        }
        update_time();
        
    }
    fclose(file);
    for(int i=0;i<S;i++){
        free(cache[i]);
    }
    free(cache);
    printSummary(hit, miss, eviction);

    return 0;
}
