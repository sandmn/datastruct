#pragma once

#include<stddef.h>
//定义哈希表，哈希表是由一个数组构成
//哈希函数使用除留余数法

#define HASHMAXSIZE 1000

typedef int KeyType;
typedef int ValType;

typedef enum 
{
    Empty,
    Valid,
    Deleted
}Stat;

//哈希表数组中的元素类型
typedef struct HashElemType
{
    KeyType key;//包含一个键值
    ValType value;//包含一个值
    Stat stat;//定义哈希表中的元素状态
}HashElemType;

typedef size_t (*HashFunc)(KeyType key);//哈希函数指针定义，输入参数是键值，返回值是数组组下标

typedef struct HashTable
{
    HashElemType data[HASHMAXSIZE];//哈希表数组中的元素类型是HashElem类型的
    size_t size;//哈希表中实际元素的长度，但[0,size)不是有效元素区间
    HashFunc func;//哈希函数
}HashTable;


//哈希表的初始化
void HashInit(HashTable* ht,HashFunc func);

//销毁哈希表
void HashDestroy(HashTable* ht);

//向哈希表中插入元素
void HashInsert(HashTable* ht,KeyType key,ValType value);

//在哈希表中查找元素
int HashFind(HashTable* ht,KeyType key,ValType* value);

//删除哈希表中的元素
void HashDelete(HashTable* ht,KeyType key);
