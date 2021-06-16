#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12 //定义散列表长为数组的长度
#define NULLKEY -32768

typedef struct
{
    int *elem; //数据元素存储基地址，动态分配数组
    int count; //当前数据元素个数
} HashTable;
int m = 0; //散列表长，全局变量

//初始化散列表
int InitHashTable(HashTable *H)
{
    int i;
    m = HASHSIZE;
    H->count = m;
    H->elem = (int *)malloc(m * sizeof(int));
    for (i = 0; i < m; i++)
    {
        H->elem[i] = NULLKEY;
    }
    return 0;
}

//散列函数
int Hash(int key)
{
    return key % m; //除留余数法
}

//插入关键字进散列表
void InsertHash(HashTable *H, int key)
{
    int addr = Hash(key);
    while (H->elem[addr] != NULLKEY) //如果不为空，则冲突
    {
        addr = (addr + 1) % m; //开放地址法的线性探测
    }

    H->elem[addr] = key; //直到有空位后插入关键字
}

//散列表查找关键字
int SearchHash(HashTable *H, int key)
{
    int addr = 0;
    addr = Hash(key);            //如果关键字在数组中已经存在，则直接获得addr
    while (H->elem[addr] != key) //如果关键字在数组中不存在，则需要遍历一遍数组挨个查找
    {
        printf("addr = %d\n", addr);
        addr = (addr + 1) % m;
        if (H->elem[addr] == NULLKEY || addr == Hash(key))
        {
            //如果循环回原点
            return -ENODATA;
        }
    }
    return addr;
}

int main()
{
    int i = 0;
    int key[] = {12, 67, 56, 16, 25, 37, 22, 28, 15, 47, 48, 34};
    int searchValue = 0;
    int addr;
    HashTable *H;

    //初始化Hash表
    InitHashTable(H);

    //插入数据
    for (i = 0; i < HASHSIZE; i++)
    {
        InsertHash(H, key[i]);
    }

    printf("Hash Table:\n");
    for (i = 0; i < HASHSIZE; i++)
    {
        printf("%d ", H->elem[i]);
    }
    printf("\n");

    printf("Please Input Search value\n");
    if (!scanf("%d", &searchValue))
        printf("Scanf error\n");
    addr = SearchHash(H, searchValue);
    if (addr >= 0)
        printf("Found at [%d]\n", addr);
    else
        printf("Not Found\n");
    return 0;
}