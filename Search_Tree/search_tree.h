#pragma once


//二叉搜索树是一个二叉树，它还满足：
//根节点的左子树中所有节点都比根节点小，根节点的右子树中所有节点都比根节点大

//定义二叉搜索树的节点结构：孩子表示法
typedef char SearchTreeType;
typedef struct SearchTreeNode
{
    SearchTreeType data;
    struct SearchTreeNode* lchild;
    struct SearchTreeNode* rchild;
}SearchTreeNode;

//初始化二叉搜索树
void SearchTreeInit(SearchTreeNode** proot);

//在二叉搜索树中插入元素（递归）
void SearchTreeInsert(SearchTreeNode** proot,SearchTreeType value);

//在二叉搜索树中查找指定元素
SearchTreeNode* SearchTreeFind(SearchTreeNode* root,SearchTreeType to_find);

//在二叉搜索树中删除指定元素
void SearchTreeRemove(SearchTreeNode** proot,SearchTreeType to_remove);

//在二叉搜索树中插入指定元素（非递归）
void SearchTreeInsertByLoop(SearchTreeNode** proot,SearchTreeType value);

//在二叉搜索树中查找指定元素（非递归）
SearchTreeNode* SearchTreeFindByLoop(SearchTreeNode* root,SearchTreeType to_find);

