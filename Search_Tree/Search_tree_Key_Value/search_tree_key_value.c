#include "search_tree_key_value.h"
#include<stdlib.h>
#include<stdio.h>

//初始化
void SearchTreeInit(SearchTreeNode** proot)
{
    if(proot == NULL)
    {
        //非法输入
        return;
    }
    *proot = NULL;
    return;
}

SearchTreeNode* CreateNode(SearchTreeKeyType key)
{
    SearchTreeNode* new_node = (SearchTreeNode*)malloc(sizeof(SearchTreeNode));
    new_node->key = key;
    new_node->value = 0;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

//插入元素
void SearchTreeInsert(SearchTreeNode** proot,SearchTreeKeyType key)
{
    if(proot == NULL)
    {
        //非法输入
        return;
    }
    SearchTreeNode* new_node = CreateNode(key);
    if(*proot == NULL)
    {
        //空树
        //插入一个节点，value计数1
        new_node->value = 1;
        *proot = new_node;
        return;
    }

    SearchTreeNode* cur = *proot;
    while(1)
    {
        if(cur->lchild == NULL && cur->key > key)
        {
            new_node->value = 1;
            cur->lchild = new_node;
            return;
        }
        else if(cur->rchild == NULL && cur->key < key)
        {
            new_node->value = 1;
            cur->rchild = new_node;
            return;
        }
        if(key < cur->key)
        {
            cur = cur->lchild;
        }
        else if(key > cur->key)
        {
            cur = cur->rchild;
        }
        else
        {
            //当遇到重复的元素时，不进行插入，只对计数器value的值加加
            free(new_node);
            cur->value++;
            return;
        }
    }
}

void SearchTreePrint(SearchTreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    printf("%c:%d   ",root->key,root->value);
    SearchTreePrint(root->lchild);
    SearchTreePrint(root->rchild);
    return;
}


//根据搜索二叉树统计数组中的元素个数
void GetCount(SearchTreeKeyType array[],size_t size)
{
    if(array == NULL || size == 0)
    {
        //非法输入
        return;
    }
    SearchTreeNode* root;//定义一个树的根节点的指针
    SearchTreeInit(&root);//初始化树
    size_t index = 0;
    //根据将数组元素插入到二叉搜索树中
    for(;index < size;++index)
    {
        SearchTreeInsert(&root,array[index]);
    }

    //打印二叉搜索树
    SearchTreePrint(root);
    printf("\n");
    return;
}

/////////////////////
//测试代码
/////////////////////

#define TEST_HANDLE printf("================%s===============\n",__FUNCTION__);
#include<stdio.h>

//测试初始化
void TestInit()
{
    TEST_HANDLE;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    printf("expect null,actually %p\n",root);
    return;
}


//测试统计数组元素个数
void TestGetCount()
{
    TEST_HANDLE;
    SearchTreeKeyType array[] = {'s','d','e','d','s','r','d'};
    size_t size = sizeof(array)/sizeof(array[0]);

    GetCount(array,size);
    return;
}




int main()
{
    TestInit();
    TestGetCount();
    return 0;
}
