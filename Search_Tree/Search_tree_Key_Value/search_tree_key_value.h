#pragma once

#include<stddef.h>
//二叉搜索树键值对节点的操作

//#define FOR_ARRAY
#ifdef FOR_ARRAY
typedef char SearchTreeKeyType;
typedef int SearchTreeValueType;

#else 

typedef char SearchTreeKeyType;
typedef char SearchTreeValueType;

#endif

#ifdef FOR_ARRAY
typedef struct SearchTreeNode
{
    SearchTreeKeyType key;//判断依据的值
    SearchTreeValueType value;//键值的相关属性
    struct SearchTreeNode* lchild;
    struct SearchTreeNode* rchild;
}SearchTreeNode;

#else
#define MAXKEYSIZE 128
#define MAXVALUESIZE 256
typedef struct SearchTreeNode
{
    SearchTreeKeyType key[MAXKEYSIZE];//判断依据的值
    SearchTreeValueType value[MAXVALUESIZE];//键值的相关属性
    struct SearchTreeNode* lchild;
    struct SearchTreeNode* rchild;
}SearchTreeNode;

#endif

//初始化
void SearchTreeInit(SearchTreeNode** proot);


//统计数组中的元素个数，插入元素操作
void SearchTreeInsert(SearchTreeNode** proot,SearchTreeKeyType key);

//根据搜索二叉树统计数组中的元素个数
void GetCount(SearchTreeKeyType array[],size_t size);


//构造插入一棵中英文对照字典树
void TrieInsert(SearchTreeNode** proot,SearchTreeKeyType* key,SearchTreeValueType* value);



