#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // ʹ�õ�ǰʱ������ʼ�����������
   rand();

    // �����������
    int random_number = rand()%100+1; 
    
    printf("�������: %d\n", random_number);

    return 0;
}

