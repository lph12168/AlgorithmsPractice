#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
typedef struct
{
    int r[MAXSIZE + 1]; //r[0]用作临时变量或哨兵
    int length;
}Sqlist;

void swap(Sqlist *L, int i, int j)
{
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}

void randInit(Sqlist *L, int length) //打乱顺序，生成随机数组
{
    for (int i = 1; i < L->length/2; i++) {
        swap(L, i, rand() % (length -1) + 1);
    }
}

void InsertSort(Sqlist *L)
{
    int i,j = 0;
    printf("Insert Sorting\n");
    for (i = 2; i < L->length; i ++)
    {
        if (L->r[i] < L->r[i-1]) {
            L->r[0] = L->r[i];
            //用r[0]值作为循环终止条件，找到局部最小值
            for (j = i-1; L->r[j] > L->r[0]; j--) {
                L->r[j+1] = L->r[j];
            }
            //在上面for循环条件结束时j的值会多减1
            L->r[j+1] = L->r[0];
        for (int k = 1; k < L->length; k++)
            printf("%d ", L->r[k]);
        printf("\n");
        }
    }
}

void main()
{
    Sqlist *L = (Sqlist*)malloc(sizeof(Sqlist));
    L->length = sizeof(L->r) / sizeof(L->r[0]);
    for (int i = 0; i < L->length; i++)
        L->r[i] = i;
    printf("Org value\n");
    for (int i = 1; i < L->length; i++)
        printf("%d ", L->r[i]);
    printf("\n");
    randInit(L, L->length);
    printf("Input value\n");
    for (int i = 1; i < L->length; i++)
        printf("%d ", L->r[i]);
    printf("\n");
    InsertSort(L);
    printf("Output value\n");
    for (int i = 1; i < L->length; i++)
        printf("%d ", L->r[i]);
}