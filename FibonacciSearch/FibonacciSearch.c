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

int Fibonacci(int i)
{
    if (i < 2)
        return i == 0 ? 0 : 1;
    return Fibonacci(i - 1) + Fibonacci(i - 2);
}

int Fibonacci1(int *a, int i)
{
    if (i < 2) {
        i == 0 ? 0 : 1;
        a[i] = i;
        return a[i];
    }
    a[i] = Fibonacci1(a, i - 1) + Fibonacci1(a, i - 2);
    return a[i];
}

int Fibonacci_Search(int *a, int n, int key)
{
    int low, high, mid, i, k;
    int F[n];
    low = 1;
    high = n;
    k = 0;
    Fibonacci1(F, n);
    for (i = 0; i <= n; i++) {
        printf("%d ", F[i]);
    }
    printf("\n");
    while (n > F[k] - 1)
        k++;
    printf("%s k = %d\n", __func__, k);
    for (i = n; i < F[k] - 1; i++)
        a[i] = a[n];
    while (low <= high)
    {
        mid = low + F[k - 1] - 1;
        printf("%s mid = %d, low = %d, high = %d\n", __func__, mid, low, high);
        if (key < a[mid]) {
            high = mid - 1;
            k = k - 1;
        }
        else if (key > a[mid]) {
            low = mid + 1;
            k = k - 2;
        }
        else {
            if (mid <= n)
                return mid;
            else
                return n;
        }
    }
    return -ENODATA;
}

int FibonacciSearch(Sqlist *L, int searchValue)
{
    printf("%s ...\n", __func__);
    return Fibonacci_Search(L->r, L->length - 1, searchValue);
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
    foundPlace = FibonacciSearch(L, searchValue);
    printf("Found at [%d]\n", foundPlace);
}