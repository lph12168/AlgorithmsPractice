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

void SelectionSort(Sqlist *L)
{
    int i,j,min = 0;
    printf("Sorting\n");
    for (i = 1; i < L->length; i ++)
    {
        min = i;
        for (j = i + 1; j < L->length; j ++) {
            if (L->r[j] < L->r[min]) {
                min = j;
            }
        }
        if (i != min)
            swap(L, i, min);
        for (int k = 1; k < L->length; k ++)
            printf("%d ", L->r[k]);
        printf("\n");
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
    SelectionSort(L);
    printf("Output value\n");
    for (int i = 1; i < L->length; i++)
        printf("%d ", L->r[i]);
}