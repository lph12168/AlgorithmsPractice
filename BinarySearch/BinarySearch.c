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

int Binary_Search(int *a, int n, int key)
{
    int low, high, mid;
    low = 1;
    high = n;
    while (low <= high)
    {
        mid = (low + high) / 2;
        printf("%s mid = %d, low = %d, high = %d\n", __func__, mid, low, high);
        if (key < a[mid]) {
            high = mid - 1;
        }
        else if (key > a[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -ENODATA;
}

int BinarySearch(Sqlist *L, int searchValue)
{
    printf("%s ...\n", __func__);
    return Binary_Search(L->r, L->length - 1, searchValue);
}

void main()
{
    Sqlist *L = (Sqlist*)malloc(sizeof(Sqlist));
    L->length = sizeof(L->r) / sizeof(L->r[0]);
    int searchValue = 0;
    int foundPlace = 0;
    seqInit(L, L->length);
    printf("Input value\n");
    printValue(L, L->length);
    printf("Please Input Search value\n");
    if (!scanf("%d", &searchValue))
        printf("Scanf error\n");
    foundPlace = BinarySearch(L, searchValue);
    printf("Found at [%d]\n", foundPlace);
}