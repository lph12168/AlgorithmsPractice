#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void Merge(int SR[], int TR[], int i, int m, int n)
{
    int j, k, l;
    //将SR有小到大归并到TR，k在循环结束后会加1
    for (j = m + 1, k = i; i <= m && j <=n; k++)
    {
        if (SR[i] < SR[j]) {
            TR[k] = SR[i++];
            printf("Merged: TR[%d] = %d\n", k, TR[k]);
        }
        else {
            TR[k] = SR[j++];
            printf("Merged: TR[%d] = %d\n", k, TR[k]);
        }
    }
    //将剩余的i->m复制到TR
    if (i <= m)
    {
        for (l = 0; l <= m - i; l++) {
            TR[k + l] = SR[i + l]; //！！！调试了好几天一直越界出错的原因是把这里的l写成了1
            printf("Remained: TR[%d] = %d\n", k + l, TR[k + l]);
        }
    }
    //将剩余的j->n复制到TR
    if (j <= n)
    {
        for (l = 0; l <= n -j; l++) {
            TR[k + l] = SR[j + l];
        printf("Remained: TR[%d] = %d\n", k + l, TR[k + l]);
        }
    }
}

void MergePass(int SR[], int TR[], int s, int n)
{
    int i = 1;
    int j;
    while (i <= n - 2 * s + 1) {
        Merge(SR, TR, i, i + s -1, i + 2 * s - 1); //两两归并
        i = i + 2 * s;
    }
    if (i < n - s + 1)
        Merge(SR, TR, i, i + s -1, n); //归并最后两个序列
    else
        for ( j = i; j <= n; j++) {
            TR[j] = SR[j]; //最后剩下的单个序列
            printf("last remain: TR[%d] = %d\n", j, TR[j]);
        }
}

void MSort(int SR[], int TR1[], int s, int t)
{
    int m;
    int TR2[MAXSIZE + 1];
    if (s == t)
        TR1[s] = SR[s];
    else
    {
        m = (s + t) / 2; //平分为s->m, m+1->t
        MSort(SR, TR2, s, m); //归并排序s->m
        MSort(SR, TR2, m + 1, t); //归并排序m+1->t
        Merge(TR2, TR1, s, m, t); //归并排序s->m, m+1->t
    }
}

void MergeSort(Sqlist *L)
{
    MSort(L->r, L->r, 1, L->length -1);
}

void MergeSort2(Sqlist *L)
{
    int mergeLen = L->length - 1;
    int* TR = (int*)malloc(L->length * sizeof(int));
    int k = 1;
    memset(TR, 0, L->length * sizeof(int));
    printf("%s ...\n", __func__);
    while (k < L->length)
    {
        //变化细节参考《大话数据结构》414页
        MergePass(L->r, TR, k, mergeLen);
        k = 2 * k;
        MergePass(TR, L->r, k, mergeLen);
        k = 2 * k;
    }
}

void main()
{
    Sqlist *L = (Sqlist*)malloc(sizeof(Sqlist));
    L->length = sizeof(L->r) / sizeof(L->r[0]);
    L->r[0] = 99;
    L->r[1] = 50;
    L->r[2] = 10;
    L->r[3] = 90;
    L->r[4] = 30;
    L->r[5] = 70;
    L->r[6] = 40;
    L->r[7] = 80;
    L->r[8] = 60;
    L->r[9] = 20;
    //reverseInit(L, L->length);
    printf("Input value\n");
    printValue(L, L->length);
    MergeSort(L);
    printf("Output value\n");
    printValue(L, L->length);
}