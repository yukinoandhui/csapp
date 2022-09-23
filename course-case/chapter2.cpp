#include<iostream>
using namespace std;

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

int main(){
    cout<<uadd_ok(32,32)<<endl;
    return 0;
}
