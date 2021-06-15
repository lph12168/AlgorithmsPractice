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

int Partition(Sqlist *L, int low, int high)
{
    int pivotkey;
    pivotkey = L->r[low];
    while (low < high)
    {
        while (low < high && L->r[high] >= pivotkey)
            high--;
        printf("high--: low = %d, high = %d\n", low, high);
        swap(L, low, high);
        printValue(L, L->length);
        while (low < high && L->r[low] <= pivotkey)
            low++;
        printf("low++: low = %d, high = %d\n", low, high);
        swap(L, low, high);
        printValue(L, L->length);
    }
    //printf("%s: low = %d, high = %d\n", __func__, low, high);
    //printValue(L, L->length);
    return low;
}

int Partition1(Sqlist *L, int low, int high)
{
    int pivotkey;
    //优化，三数取中
    int m = low + (high - low) / 2;
    if (L->r[low] > L->r[high])
        swap(L, low, high);
    if (L->r[m] > L->r[high])
        swap(L, high, m);
    if (L->r[m] > L->r[low])
        swap(L, m, low);
    pivotkey = L->r[low];
    //以替换代替交换
    L->r[0] = pivotkey;
    while (low < high)
    {
        while (low < high && L->r[high] >= pivotkey)
            high--;
        L->r[low] = L->r[high];
        while (low < high && L->r[low] <= pivotkey)
            low++;
        L->r[high] = L->r[low];
    }
    L->r[low] = L->r[0];
    printf("%s: low = %d, high = %d\n", __func__, low, high);
    printValue(L, L->length);
    return low;
}

void QSort(Sqlist *L, int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = Partition(L, low, high);
        QSort(L, low, pivot - 1); //排序low->pivot - 1
        QSort(L, pivot + 1, high); //排序pivot+1->high
    }
}

void QSort1(Sqlist *L, int low, int high)
{
    int pivot;
    while (low < high)
    {
        pivot = Partition1(L, low, high);
        QSort1(L, low, pivot - 1);
        //用迭代而不是递归
        low = pivot + 1;
    }
}

void QuickSort(Sqlist *L)
{
    printf("%s ...\n", __func__);
    QSort1(L, 1, L->length - 1);
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
    //randInit(L, L->length);
    printf("Input value\n");
    printValue(L, L->length);
    QuickSort(L);
    printf("Output value\n");
    printValue(L, L->length);
}