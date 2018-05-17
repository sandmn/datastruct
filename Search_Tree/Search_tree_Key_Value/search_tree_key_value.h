#pragma once

#include<stddef.h>
//二叉搜索树键值对节点的操作
typedef char SearchTreeKeyType;
typedef int SearchTreeValueType;
typedef struct SearchTreeNode
{
    SearchTreeKeyType key;//判断依据的值
    SearchTreeValueType value;//键值的相关属性
    struct SearchTreeNode* lchild;
    struct SearchTreeNode* rchild;
}SearchTreeNode;

//初始化
void SearchTreeInit(SearchTreeNode** proot);


//统计数组中的元素个数，插入元素操作
void SearchTreeInsert(SearchTreeNode** proot,SearchTreeKeyType key);

//根据搜索二叉树统计数组中的元素个数
void GetCount(SearchTreeKeyType array[],size_t size);


