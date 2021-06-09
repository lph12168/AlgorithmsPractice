#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
typedef struct
{
    int r[MAXSIZE]; //r[0]用作临时变量或哨兵
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
    seqInit(L, L->length);
    for (int i = 1; i < L->length / 2; i++)
        swap(L, i, rand() % (length -1) + 1);
    L->r[0] = 0;
}

//初始化为从大到小反向序列
void reverseInit(Sqlist *L, int length)
{
    for (int i = 1; i < L->length ; i++)
        L->r[L->length - i] = i;
    L->r[0] = 0;
}

void printValue(Sqlist *L, int length)
{
    for (int k = 1; k < L->length; k++)
        printf("%d ", L->r[k]);
    printf("\n");
}

void HeapAdjust(Sqlist *L, int s, int m)
{
    int temp, j = 0;
    temp = L->r[s];
    printf("s = %d, m = %d, temp = %d\n", s, m, temp);
    for (j = 2 * s; j <= m; j *= 2) {
        if (j < m && L->r[j] < L->r[j + 1])
            ++j;
        if (temp >= L->r[j])
            break;
        L->r[s] = L->r[j];
        s = j;
        printValue(L, L->length);
    }
    L->r[s] = temp;
}

void HeapSort(Sqlist *L)
{
    int i, heapLen = 0;
    printf("%s ...\n", __func__);
    heapLen = L->length -1; //heapLen是实际存储数据的长度
    printf("Step 1: Build big top heap\n");
    //构建大顶堆
    for (i = heapLen / 2; i > 0; i--) {
        HeapAdjust(L, i, heapLen);
        printValue(L, L->length);
    }
    printf("Step 2: Sorting\n");
    for (i = heapLen; i > 1; i--) {
        printValue(L, L->length);
        swap(L, 1, i);
        HeapAdjust(L, 1, i - 1);
        printValue(L, L->length);
    }
}

void main()
{
    Sqlist *L = (Sqlist*)malloc(sizeof(Sqlist));
    L->length = sizeof(L->r) / sizeof(L->r[0]);
    seqInit(L, L->length);
    printf("Input value\n");
    printValue(L, L->length);
    HeapSort(L);
    printf("Output value\n");
    printValue(L, L->length);
}