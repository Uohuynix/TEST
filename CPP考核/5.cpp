#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // 使用当前时间来初始化随机数种子
   rand();

    // 生成随机整数
    int random_number = rand()%100+1; 
    
    printf("随机整数: %d\n", random_number);

    return 0;
}

