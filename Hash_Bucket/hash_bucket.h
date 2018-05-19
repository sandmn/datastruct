
#pragma once

#include<stddef.h>

#define HASHMAXSIZE 1000//定义数组的最大长度

typedef int KeyType;
typedef int ValType;

//定义哈希表中的元素类型
//哈希表中的数组元素为节点指针类型，一个节点包含一个key，一个value,一个指向下一个节点的指针
typedef struct HashElemNode
{
    KeyType key;
    ValType value;
    struct HashElemNode* next;
}HashElemNode;

typedef size_t (*HashFunc)(KeyType key);


//定义哈希表
typedef struct HashTable
{
    HashElemNode* data[HASHMAXSIZE];//哈希表中的数组元素定义
    size_t size;//哈希表的实际元素个数
    HashFunc func;//哈希函数
}HashTable;

//初始化哈希表
void HashInit(HashTable* ht,HashFunc func);

//销毁哈希表
void HashDestroy(HashTable* ht);

//向哈希表中插入元素
void HashInsert(HashTable* ht,KeyType key,ValType value);

//在哈希表中中查找元素
int HashFindEx(HashTable* ht,KeyType key,ValType* value);

//在哈希表中删除元素
void HashDelete(HashTable* ht,KeyType key);
