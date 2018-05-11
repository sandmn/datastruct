
#include "bin_tree.h"
#include"seqqueue.h"
#include"seqstack.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>



void TreeInit(TreeNode** proot)
{
    if(proot == NULL)
    {
        //非法输入
        return;
    }

    *proot = NULL;
    return;
}

//先序遍历树
void PreOrder(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        printf("# ");//输出#表示空节点
        return;
    }

    //输出根节点
    printf("%c ",root->data);
    //递归遍历左子树
    PreOrder(root->lchild);
    //递归遍历右子树
    PreOrder(root->rchild);
    return;
}

//创建树的节点
TreeNode* CreateNode(TreeType value)
{
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

//中序遍历
void InOrder(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        printf("# ");
        return;
    }

    //中序遍历左子树
    InOrder(root->lchild);
    //输出根节点
    printf("%c ",root->data);
    //中序遍历右子树
    InOrder(root->rchild);
    return;
}
//后序遍历
void PostOrder(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        printf("# ");
        return;
    }
    //后序遍历左子树
    PostOrder(root->lchild);
    //后序遍历右子树
    PostOrder(root->rchild);
    ////输出根节点
    printf("%c ",root->data);
    return;
}

//层序遍历
void LevelOrder(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return;
    }

    //借助队列来完成层序遍历
    SeqQueue queue;//定义一个顺序队列
    SeqQueueInit(&queue);//初始化队列
    
    //1. 现将根节点的指针入队列
    SeqQueuePush(&queue,root);
    int ret;
    SeqQueueType front;
    while(1)
    {
        //2. 取队首元素，如果队列为空，说明已经遍历结束
        ret = SeqQueueTop(&queue,&front);
        if(ret == -1)
        {
            //队列已空，树已经遍历完
            break;
        }
        //3. 打印队首元素
        printf("%c ",front->data);
        //4. 队首元素出对列
        SeqQueuePop(&queue);
        //5. 如果队首元素的左右节点非空，则将左右节点的指针入队
        if(front->lchild != NULL)
        {
            SeqQueuePush(&queue,front->lchild);
        }
        if(front->rchild != NULL)
        {
            SeqQueuePush(&queue,front->rchild);
        }
        //6. 循环2.～5.
    }
    return;
}

//根据先序遍历的结果创建一棵树
//arr为带#的先序序列字符串，size为字符串的长度，index为位置下标，null_flag为空树的标志
TreeNode* _TreeCreate(TreeType arr[],size_t size,size_t* index,char null_flag)
{
    if(arr == NULL ||  size < 0 || index == NULL)
    {
        //非法输入
        return NULL;
    }
    
    if(*index >= size)
    {
        //数组已遍历结束,树创建完成
        return NULL;
    }
    if(arr[*index] == null_flag)//null_flag是空树的标志，这里为#
    {
        //空树
        return NULL;
    }
    //创建根节点
    TreeNode* root = CreateNode(arr[*index]);
    (*index)++;
    //递归创建左子树
    root->lchild = _TreeCreate(arr,size,index,null_flag);
    (*index)++;
    //递归创建右子树
    root->rchild = _TreeCreate(arr,size,index,null_flag);
    return root;
}

TreeNode* TreeCreate(TreeType arr[],size_t size,char null_flag)
{
    if(arr == NULL || size < 0)
    {
        //非法输入
        return NULL;
    }
    size_t index = 0;
    TreeNode* root =  _TreeCreate(arr,size,&index,null_flag);
    return root;
}

//克隆一棵树
TreeNode* TreeClone(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }

    TreeNode* new_root;
    //克隆根节点
    new_root = CreateNode(root->data);
    //递归克隆左子树
    new_root->lchild = TreeClone(root->lchild);
    //递归克隆右子树
    new_root->rchild = TreeClone(root->rchild);
    return new_root;
}

void DestroyNode(TreeNode* node)
{
    free(node);
    return;
}

//void TreeDestroy(TreeNode** root);
//二叉树的销毁(后序遍历销毁)
void TreeDestroy(TreeNode** root)//有问题
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    if(*root == NULL)
    {
        //空树
        return;
    }
    TreeDestroy(&((*root)->lchild));
    TreeDestroy(&((*root)->rchild));
    
    DestroyNode(*root);
    *root = NULL;
    return;
}

void _TreeSize(TreeNode* root,size_t* count)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    if(count == NULL)
    {
        //非法输入
        return;
    }
    (*count)++;
    _TreeSize(root->lchild,count);
    _TreeSize(root->rchild,count);
    return;
}

//求二叉树中的结点个数
size_t TreeSize(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }
    size_t count = 0;
    _TreeSize(root,&count);
    return count;
}
//求二叉树中的结点个数
//size_t TreeSize(TreeNode* root)
//{
//    if(root == NULL)
//    {
//        //空树
//        return 0;
//    }
//    //统计左子树的节点个数
//    size_t lsize = TreeSize(root->lchild);
//    //统计右子树的节点个数
//    size_t rsize = TreeSize(root->rchild);
//    //整棵树的节点个数为左子树加右子树加根节点的个数
//    return 1 + lsize + rsize;
//}


void _TreeLeafCount(TreeNode* root,size_t* count)
{
    if(root == NULL)
    {
        return;
    }
    if(count == NULL)
    {
        //非法输入
        return;
    }
    if(root->lchild == NULL && root->rchild == NULL)
    {
        (*count)++;
    }
    _TreeLeafCount(root->lchild,count);
    _TreeLeafCount(root->rchild,count);
}

//求二叉树中叶子节点个数
size_t TreeLeafCount(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }
    size_t count = 0;
    _TreeLeafCount(root,&count);
    return count;
}

//求二叉树中叶子节点个数
//size_t TreeLeafCount(TreeNode* root)
//{
//    if(root == NULL)
//    {
//        //空树
//        return 0;
//    }
//    if(root->lchild == NULL && root->rchild == NULL)
//    {
//        return 1;
//    }
//    //递归统计左子树的叶子节点个数
//    size_t lcount = TreeLeafCount(root->lchild);
//    //递归统计右子树的叶子节点个数
//    size_t rcount = TreeLeafCount(root->rchild);
//    //左右子树的叶子节点个数求和
//    return lcount + rcount;
//}


//求二叉树第k层节点的个数
size_t TreeKLevelSize(TreeNode* root,int K)
{
    if(K < 1)
    {
        return 0;
    }
    if(root == NULL)
    {
        //空树
        return 0;
    }
    if(K == 1)
    {
        return 1;
    }
    return TreeKLevelSize(root->lchild,K-1) + TreeKLevelSize(root->rchild,K-1);
}

//求二叉树的深度或高度
size_t TreeHeight(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }
    if(root->lchild == NULL && root->rchild == NULL)
    {
        return 1;
    }
    //统计左子树的深度
    size_t lheight = TreeHeight(root->lchild);
    //统计右子树的深度
    size_t rheight = TreeHeight(root->rchild);
    //左右子树的最大值加1
    return (lheight > rheight)? 1+lheight : 1+rheight;
}
//在二叉树中查找节点(给定数值，求对应节点的指针，假设二叉树中的节点是不重复的)
//空间复杂度为O(n),时间复杂度为O(n),因为n个节点，需要比较n次，递归n次
TreeNode* TreeFind(TreeNode* root,TreeType to_find)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    if(root->data == to_find)
    {
        return root;
    }
    //递归遍历左子树进行查找
    TreeNode* lret = TreeFind(root->lchild,to_find);
    //递归遍历右子树进行查找
    TreeNode* rret = TreeFind(root->rchild,to_find);
    return (lret == NULL)? rret : lret;
}
//求当前节点的父节点
TreeNode* Parent(TreeNode* root,TreeNode* child)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    if(child == NULL)
    {
        //非法输入
        return NULL;
    }
    if(root->lchild == child || root->rchild == child)
    {
        return root;
    }
    TreeNode* lret = Parent(root->lchild,child);
    TreeNode* rret = Parent(root->rchild,child);
    return (lret != NULL)? lret : rret;

}
//查找指定节点的左孩子
TreeNode* LChild(TreeNode* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->lchild;
}
//查找指定节点的右孩子
TreeNode* RChild(TreeNode* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->rchild;
}



/////////////////////////////////
//以下为树的面试题
/////////////////////////////////

//非递归实现树的先序遍历
void TreePreOrderByLoop(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return;
    }

    SeqStack stack;//定义一个顺序栈
    InitSeqStack(&stack);//初始化顺序栈
    
    SeqStackPush(&stack,root);//入栈根节点

    SeqQueueType top;//top用于存放栈顶元素
    while(1)
    {
        int ret = SeqStackTop(&stack,&top);//取栈顶元素
        if(ret == -1)
        {
            //此时栈为空,树已经遍历完成
            return;
        }
        //访问栈顶元素
        printf("%c ",top->data);
        //出栈栈顶元素
        SeqStackPop(&stack);

        //栈顶元素的右子树非空时，入栈右子树
        if(top->rchild != NULL)
        {
            SeqStackPush(&stack,top->rchild);
        }

        //栈顶元素的左子树非空时，入栈左子树
        if(top->lchild != NULL)
        {
            SeqStackPush(&stack,top->lchild);
        }
    }
    return;
}


//非递归实现树的中序遍历
void TreeInOrderByLoop(TreeNode* root)
{
    if(root ==  NULL)
    {
        //空树
        return;
    }

    SeqStack stack;
    InitSeqStack(&stack);

    //1. 定义cur为当前指针变量，初始指向root；
    TreeNode* cur = root;

    while(1)
    {
        //2. 当cur不为空时，
        while(cur != NULL)
        {
            //   a)将cur入栈，
            SeqStackPush(&stack,cur);
            //   b)并使cur指向cur的左子树，
            cur = cur->lchild;
            //   c)循环a)b)
        }
        //3. 当cur为空时，取栈顶元素，使cur指向栈顶元素
        int ret = SeqStackTop(&stack,&cur);
        //  a)栈顶元素为空时，遍历结束
        if(ret == -1)
        {
            return;
        }
        //  b)栈顶元素不为空时，访问栈顶元素，并出栈
        printf("%c ",cur->data);
        SeqStackPop(&stack);

        //4. 使cur指向cur的右子树
        cur = cur->rchild;
        //5.循环2~4
    }
    return;
}

////非递归实现树的后序遍历
//void TreePostOrderByLoop(TreeNode* root)
//{
//    if(root ==  NULL)
//    {
//        return;
//    }
//
//    SeqStack stack;
//    InitSeqStack(&stack);
//
//
//    //1. 定义cur为当前指针变量，初始为root
//    TreeNode* cur = root;
//    TreeNode* pre = NULL;
//
//    while(1)
//    {
//        //2. 当cur不为空时，
//        while(cur != NULL)
//        {
//            //  a) 将cur入栈
//            SeqStackPush(&stack,cur);
//            //  b）cur指向cur的左孩子
//            cur = cur->lchild;
//            //  c) 循环a)b)
//        }
//        //3. 当cur为空时，取栈顶元素，由cur指向
//        int ret = SeqStackTop(&stack,&cur);
//        //4. 如果栈顶元素为空，则遍历完程，直接返回即可
//        if(ret == -1)
//        {
//            return;
//        }
//        //5. 若栈顶元素不为空
//        //  1）如果栈顶元素的右孩子为空，
//        if(cur->rchild == NULL)
//        {
//            //   a) 则访问栈顶元素，并出栈
//            printf("%c ",cur->data);
//            pre = cur;
//            SeqStackPop(&stack);
//            //   b) 将cur指向cur的右孩子
//            cur = cur->rchild;
//        }
//        //  2） 如果栈顶元素的右孩子已经访问过（已经访问过，是指栈顶元素的右孩子与上一次访问过的元素相同）
//        else if(cur->rchild == pre)
//        {
//            //   a) 则访问栈顶元素，并出栈
//            printf("%c ",cur->data);
//            SeqStackPop(&stack);
//            pre = cur;
//            cur = NULL;
//            //   b) 回到3
//
//        }
//        else 
//        {
//            //  3） 如果不为4.5，则不做处理，使cur指向cur的右孩子
//            cur = cur->rchild;
//        }
//        //6. 循环2～5
//    }
//    return;
//}

//非递归实现树的后序遍历
void TreePostOrderByLoop(TreeNode* root)
{
    if(root ==  NULL)
    {
        return;
    }

    SeqStack stack;
    InitSeqStack(&stack);


    //1. 定义cur为当前指针变量，初始为root
    TreeNode* cur = root;
    TreeNode* pre = NULL;

    while(1)
    {
        //2. 当cur不为空时，
        while(cur != NULL)
        {
            //  a) 将cur入栈
            SeqStackPush(&stack,cur);
            //  b）cur指向cur的左孩子
            cur = cur->lchild;
            //  c) 循环a)b)
        }
        //3. 当cur为空时，取栈顶元素，由cur指向
        TreeNode* top = NULL;
        int ret = SeqStackTop(&stack,&top);
        //4. 如果栈顶元素为空，则遍历完程，直接返回即可
        if(ret == -1)
        {
            return;
        }
        //5. 若栈顶元素不为空
        //  1）如果栈顶元素的右孩子为空，
        if(top->rchild == NULL || top->rchild == pre)
        {
            printf("%c ",top->data);
            pre = top;
            SeqStackPop(&stack);

        }
        //  3） 如果不为4.5，则不做处理，使cur指向cur的右孩子
        else{
            cur = top->rchild;
        }

        //6. 循环2～5
    }
    return;
}

/////////////////////////////////////
//测试代码
///////////////////////////////////////


#include<stdio.h>

#define TEST_HANDLE printf("======================%s==================\n",__FUNCTION__)

//测试初始化
void TestInit()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    printf("expect null,actually %p\n",root);
    return;
}


//测试先序遍历
void TestPreOrder()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    TreeNode* a = CreateNode('a');
    TreeNode* b = CreateNode('b');
    TreeNode* c = CreateNode('c');
    TreeNode* d = CreateNode('d');
    TreeNode* e = CreateNode('e');
    TreeNode* f = CreateNode('f');
    TreeNode* g = CreateNode('g');

    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->rchild = f;
    c->lchild = g;

    PreOrder(a);
    printf("\n");
    return;
    
}

//测试中序遍历
void TestInOrder()
{

    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    TreeNode* a = CreateNode('a');
    TreeNode* b = CreateNode('b');
    TreeNode* c = CreateNode('c');
    TreeNode* d = CreateNode('d');
    TreeNode* e = CreateNode('e');
    TreeNode* f = CreateNode('f');
    TreeNode* g = CreateNode('g');

    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->rchild = f;
    c->lchild = g;

    InOrder(a);
    printf("\n");
    return;
}

//测试后序遍历
void TestPostOrder()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    TreeNode* a = CreateNode('a');
    TreeNode* b = CreateNode('b');
    TreeNode* c = CreateNode('c');
    TreeNode* d = CreateNode('d');
    TreeNode* e = CreateNode('e');
    TreeNode* f = CreateNode('f');
    TreeNode* g = CreateNode('g');

    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->rchild = f;
    c->lchild = g;

    PostOrder(a);
    printf("\n");
    return;

}

void TestLevelOrder()
{
    TEST_HANDLE;

    TreeNode* root;
    TreeInit(&root);

    TreeNode* a = CreateNode('a');
    TreeNode* b = CreateNode('b');
    TreeNode* c = CreateNode('c');
    TreeNode* d = CreateNode('d');
    TreeNode* e = CreateNode('e');
    TreeNode* f = CreateNode('f');
    TreeNode* g = CreateNode('g');

    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->rchild = f;
    c->lchild = g;

    LevelOrder(a);
    printf("\n");
    return;

}

void TestCreateTree()
{
    TEST_HANDLE;
    char arr[] = "abd##e#f##cg###";
    TreeNode* root;
    TreeInit(&root);
    root = TreeCreate(arr,strlen(arr),'#');
    PreOrder(root);
    printf("\n");
    InOrder(root);
    printf("\n");
    PostOrder(root);
    printf("\n");
    LevelOrder(root);
    printf("\n");
    return;
}

void TestTreeClone()
{
    TEST_HANDLE;
    char arr[] = "abd##e#f##cg###";
    TreeNode* root;
    TreeInit(&root);
    root = TreeCreate(arr,strlen(arr),'#');
    TreeNode* new_root = TreeClone(root);
    PreOrder(new_root);
    printf("\n");
    InOrder(new_root);
    printf("\n");
    PostOrder(new_root);
    printf("\n");
    LevelOrder(new_root);
    printf("\n");
    return;

}

//测试销毁树
void TestDestroy()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    TreeDestroy(&root);
    printf("expect null,actually %p\n",root);
    
    char arr[] = "abd##e#f##cg###";
    root = TreeCreate(arr,strlen(arr),'#');
    PreOrder(root);
    printf("\n");
    InOrder(root);
    printf("\n");
    PostOrder(root);
    printf("\n");
    LevelOrder(root);
    printf("\n");

    TreeDestroy(&root);
    printf("expect null,actually %p\n",root);
    PreOrder(root);
    printf("\n");
    InOrder(root);
    printf("\n");
    PostOrder(root);
    printf("\n");
    LevelOrder(root);
    printf("\n");
    return;
}

void TestSize()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    size_t count = TreeSize(root);
    printf("expect 0,actually %d\n",count);

    char arr[] = "abd##e#f##cg###";
    root = TreeCreate(arr,strlen(arr),'#');
    count = TreeSize(root);
    printf("expect 7,actually %d\n",count);
    return;

}
void TestLeafCount()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    size_t count = TreeLeafCount(root);
    printf("expect 0,actually %d\n",count);

    char arr[] = "abd##e#f##cg###";
    root = TreeCreate(arr,strlen(arr),'#');
    count = TreeLeafCount(root);
    printf("expect 3,actually %d\n",count);
    return;

}

void TestKLevelSize()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    size_t count = TreeKLevelSize(root,0);
    printf("expect 0,actually %d\n",count);

    count = TreeKLevelSize(root,1);
    printf("expect 0,actually %d\n",count);

    char arr[] = "abd##e#f##cg###";
    root = TreeCreate(arr,strlen(arr),'#');
    count = TreeKLevelSize(root,1);
    printf("expect 1,actually %d\n",count);

    count = TreeKLevelSize(root,3);
    printf("expect 3,actually %d\n",count);
    return;

}

void TestHeight()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    size_t count = TreeHeight(root);
    printf("expect 0,actually %d\n",count);

    char arr[] = "abd##e#f##cg###";
    root = TreeCreate(arr,strlen(arr),'#');
    count = TreeHeight(root);
    printf("expect 4,actually %d\n",count);
}

void TestFind()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    
    TreeNode* ret = TreeFind(root,'g');
    printf("expect null,actuall %p\n",ret);

    char arr[] = "abd##e#f##cg###";
    root = TreeCreate(arr,strlen(arr),'#');
    ret = TreeFind(root,'g');
    printf("expect %p,actuall %p\n",root->rchild->lchild,ret);

    ret = TreeFind(root,'l');
    printf("expect null,actuall %p\n",ret);
}

void TestParent()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    
    TreeNode* ret = Parent(root,root);
    printf("expect null,actuall %p\n",ret);

    char arr[] = "abd##e#f##cg###";
    root = TreeCreate(arr,strlen(arr),'#');
    ret = Parent(root,root->lchild);
    printf("expect %p,actuall %p\n",root,ret);

    ret = Parent(root,root);
    printf("expect null,actuall %p\n",ret);

}

void TestLchild()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    
    TreeNode* ret = LChild(root);
    printf("expect null,actuall %p\n",ret);

    char arr[] = "abd##e#f##cg###";
    root = TreeCreate(arr,strlen(arr),'#');
    ret = LChild(root);
    printf("expect %p,actuall %p\n",root->lchild,ret);
    printf("expect b,actually %c\n",ret->data);

    ret = LChild(root->lchild->lchild);
    printf("expect null,actuall %p\n",ret);
}
void TestRchild()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    
    TreeNode* ret = RChild(root);
    printf("expect null,actuall %p\n",ret);

    char arr[] = "abd##e#f##cg###";
    root = TreeCreate(arr,strlen(arr),'#');
    ret = RChild(root);
    printf("expect %p,actuall %p\n",root->rchild,ret);
    printf("expect c,actually %c\n",ret->data);

    ret = RChild(root->lchild->lchild);
    printf("expect null,actuall %p\n",ret);
}

//测试非递归先序遍历
void TestPreOrderByLoop()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    char arr[] = "abd##e#f##cg###";

    root = TreeCreate(arr,strlen(arr),'#');
    TreePreOrderByLoop(root);
    printf("\n");
    return;
}

void TestInOrderByLoop()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    char arr[] = "abd##e#f##cg###";

    root = TreeCreate(arr,strlen(arr),'#');
    TreeInOrderByLoop(root);
    printf("\n");
    return;

}

void TestPostOrderByLoop()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);
    char arr[] = "abd#fg####c#e##";

    root = TreeCreate(arr,strlen(arr),'#');
    TreePostOrderByLoop(root);
    printf("\n");
    return;

}

int main()
{
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    TestLevelOrder();
    TestCreateTree();
    TestTreeClone();
    TestDestroy();
    TestSize();
    TestLeafCount();
    TestKLevelSize();
    TestHeight();
    TestFind();
    TestParent();
    TestLchild();
    TestRchild();
    TestPreOrderByLoop();
    TestInOrderByLoop();
    TestPostOrderByLoop();
    return 0;
}
