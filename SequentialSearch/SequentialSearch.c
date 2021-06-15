#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define MAXSIZE 9
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

int Sequential_Search(int *a, int n, int key)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (a[i] == key)
            return i;
    }
    return -ENODATA;
}

int Sequential_Search1(int *a, int n, int key)
{
    int i = n;
    a[0] = key;
    while (a[i] != key)
    {
        i--;
    }
    return i;
}

int SequentialSearch(Sqlist *L, int searchValue)
{
    return Sequential_Search1(L->r, L->length, searchValue);
}

void main()
{
    Sqlist *L = (Sqlist*)malloc(sizeof(Sqlist));
    L->length = sizeof(L->r) / sizeof(L->r[0]);
    int searchValue = 0;
    int foundPlace = 0;
    randInit(L, L->length);
    printf("Input value\n");
    printValue(L, L->length);
    printf("Please Input Search value\n");
    if (!scanf("%d", &searchValue))
        printf("Scanf error\n");
    foundPlace = SequentialSearch(L, searchValue);
    printf("Found at [%d]\n", foundPlace);
}