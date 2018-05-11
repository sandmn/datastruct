

#pragma once

#include<stddef.h>
//二叉树中各节点的数据类型定义
typedef char TreeType;

//二叉树中各节点的结构定义
typedef struct TreeNode
{
    TreeType data;//节点的数据域
    struct TreeNode* lchild;//指向左节点的指针
    struct TreeNode* rchild;//指向右节点的指针
}TreeNode;

//树的初始化
void TreeInit(TreeNode** proot);


//先序遍历树
void PreOrder(TreeNode* root);

//中序遍历
void InOrder(TreeNode* root);

//后序遍历
void PostOrder(TreeNode* root);

//层序遍历
void LevelOrder(TreeNode* root);

//根据先序遍历的结果创建一棵树
//arr表示先序遍历的字符串，size表示字符串的长度，index表示数组下标的指针，flag表示空树的标记
TreeNode* TreeCreate(TreeType arr[],size_t size,char null_flag);

//克隆一棵树
TreeNode* TreeClone(TreeNode* root);

//二叉树的销毁
//void TreeDestroy(TreeNode** root);

//求二叉树中的结点个数
size_t TreeSize(TreeNode* root);

//求二叉树中叶子节点个数
size_t TreeLeafCount(TreeNode* root);

//求二叉树第k层节点的个数
size_t TreeKLevelSize(TreeNode* root,int K);

//求二叉树的深度或高度
size_t TreeHeight(TreeNode* root);

//在二叉树中查找节点(给定数值，求对应节点的指针，假设二叉树中的节点是不重复的)
TreeNode* TreeFind(TreeNode* root,TreeType to_find);

//求当前节点的父节点
TreeNode* Parent(TreeNode* root,TreeNode* child);

//查找指定节点的左孩子
TreeNode* LChild(TreeNode* node);

//查找指定节点的右孩子
TreeNode* RChild(TreeNode* node);

//非递归实现树的先序遍历
void TreePreOrderByLoop(TreeNode* root);

//非递归实现树的中中序遍历
void TreeInOrderByLoop(TreeNode* root);

//非递归实现树的后序遍历
void TreePostOrderByLoop(TreeNode* root);
