#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
typedef struct
{
    int r[MAXSIZE + 1]; //r[0]用作临时变量或哨兵
    int length;
} Sqlist;

void swap(Sqlist *L, int i, int j)
{
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

//初始化为从小到大顺序序列
void seqInit(Sqlist *L, int length)
{
    for (int i = 0; i < L->length; i++)
        L->r[i] = i;
}

//打乱顺序，生成随机数组
void randInit(Sqlist *L, int length)
{
    for (int i = 1; i < L->length/2; i++)
        swap(L, i, rand() % (length -1) + 1);
}

//初始化为从大到小反向序列
void reverseInit(Sqlist *L, int length)
{
    for (int i = 1; i < L->length; i++)
        L->r[L->length - i] = i;
}

void printValue(Sqlist *L, int length)
{
    for (int k = 1; k < L->length; k++)
        printf("%d ", L->r[k]);
    printf("\n");
}

void ShellSort(Sqlist *L)
{
    int i,j = 0;
    int increment = L->length;
    printf("Shell Sorting\n");
    do
    {
        increment = increment / 3 + 1; //增量序列
        for (i = increment + 1; i <= L->length; i++) {
            //一次内循环只挪一个值，将r[j + increment]和r[j]交换
            if (L->r[i] < L->r[i - increment]) {
                L->r[0] = L->r[i];
                //用r[0]值作为循环终止条件，找到局部最小值
                for (j = i - increment; j > 0 && L->r[j] > L->r[0]; j -= increment) {
                    printf("Before in loop: i = %d, j = %d, increment = %d, a[0] = %d\n", i, j, increment, L->r[0]);
                    printValue(L, L->length);
                    L->r[j + increment] = L->r[j];
                    printf("After in loop: i = %d, j = %d, increment = %d, a[0] = %d\n", i, j, increment, L->r[0]);
                    printValue(L, L->length);
                }
                //在上面for循环条件结束时j的值会多减1
                L->r[j + increment] = L->r[0];
                printf("Out loop: i = %d, j = %d, increment = %d, a[0] = %d\n", i, j, increment, L->r[0]);
                printValue(L, L->length);
            }
        }
    }
    while (increment > 1);
}

void main()
{
    Sqlist *L = (Sqlist*)malloc(sizeof(Sqlist));
    L->length = sizeof(L->r) / sizeof(L->r[0]);
    reverseInit(L, L->length);
    printf("Input value\n");
    printValue(L, L->length);
    ShellSort(L);
    printf("Output value\n");
    printValue(L, L->length);
}