#include<iostream>
#include<stdio.h>
using namespace std;
typedef unsigned char *pointer;
/*
 *这里开始都是函数的定义
 * */

int uadd_ok(unsigned x,unsigned y){
    unsigned res =x + y;//默认是unsigned int
    if (res <x||res<y){
    return 1;
    }
    return 0;
}

//数据在内存中的表示
void show_bytes(pointer start,size_t len){
    size_t i;
    for (i=0;i<len;i++){
        printf("%p\t0x%.2x\n",start+i,start[i]);
    }
}
int main(){
    //cout<<uadd_ok(32,32)<<endl;
    int a=15213;
    show_bytes((pointer)&a,sizeof(int));
    return 0;
}
