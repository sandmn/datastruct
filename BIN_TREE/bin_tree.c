//二叉树
#include "bin_tree.h"
#include"seqqueue.h"
#include"seqstack.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>



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

//按层打印二叉树
void PrintByLevelOrder(TreeNode* root)
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
        int size = queue.size;
        while(size--)
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
        }
        printf("\n");
        //6. 循环2.～5.
    }
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
        //  1）如果栈顶元素的右孩子为空或栈顶元素的右孩子与上一个访问的元素相同，
        //     则访问栈顶元素，并出栈，然后继续回到3取栈顶元素进行判断
        if(top->rchild == NULL || top->rchild == pre)
        {
            printf("%c ",top->data);
            pre = top;
            SeqStackPop(&stack);

        }
        //  2） 如果不为1)，则不做处理，使cur指向cur的右孩子
        else{
            cur = top->rchild;
        }

        //6. 循环2～5
    }
    return;
}

//求一棵树的镜像

void Swap(TreeNode** a,TreeNode** b)
{
    TreeNode* tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

//求一棵树的镜像
void TreeMirror(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    //通过先序遍历二叉树
    //此处的遍历操作变为交换该结点处的左右结点
    //当遍历到一个结点时，交换左右孩子结点的值
    //再接着遍历左右结点
    Swap(&root->lchild,&root->rchild);
    TreeMirror(root->lchild);
    TreeMirror(root->rchild);
    return;
}
//void TreeMirror(TreeNode* root)
//{
//    if(root == NULL)
//    {
//        //空树
//        return;
//    }
//
//    //先序遍历树的各节点，访问到一个节点，将该节点的左右孩子交换
//    //此时，访问操作为交换
//    Swap(&root->lchild,&root->rchild);
//    TreeMirror(root->lchild);
//    TreeMirror(root->rchild);
//    return;
//}
//非递归求一棵树的镜像:将树的三种非递归遍历中的打印操作改为交换操作即可
//这里采用层序遍历来实现非递归求镜像
void TreeMirrorByLoop(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return;
    }

    SeqQueue queue;//定义一个队列
    SeqQueueInit(&queue);

    //1. 将根节点入队列
    SeqQueuePush(&queue,root);

    while(1)
    {
        //2. 取队首元素，
        SeqQueueType top;
        int ret = SeqQueueTop(&queue,&top);
        //a)如果获取失败，表明队列为空，此时树遍历结束,直接返回即可
        if(ret == -1)
        {
            return;
        }
        //b)否则并出队列，访问队首元素:交换左右子树
        SeqQueuePop(&queue);
        Swap(&top->lchild,&top->rchild);

        //3. 如果队首元素的左右子树非空，就分别将左右子树入队列
        if(top->lchild != NULL)
        {
            SeqQueuePush(&queue,top->lchild);
        }
        if(top->rchild != NULL)
        {
            SeqQueuePush(&queue,top->rchild);
        }
        //4. 循环2～3

    }
}
//判断一棵树是否为完全二叉树(先序实现)
int IsCompleteByPre(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }

    //先序遍历判断每个节点是否满足以下条件，并得出相应结论
    //判断属于哪个阶段,为0为阶段1，为1为阶段2
    int which_flags = 0;
    //阶段一：
    if(which_flags == 0)
    {

        //1. 如果一个节点左右孩子均存在，还属于阶段1，则继续往后遍历
        if(root->lchild != NULL && root->rchild != NULL)
        {
            which_flags = 0;
        }
        //2. 如果一个节点只有右孩子，则该树不是完全二叉树，直接返回即可。
        else if(root->lchild == NULL && root->rchild != NULL)
        {
            return 0;
        }
        //3. 如果一个节点只有左子树，则进入阶段二
        else if(root->lchild != NULL && root->rchild == NULL)
        {
            which_flags = 1;
        }
        //4，如果一个节点没有左右孩子，则进入阶段二
        else
        {
            which_flags = 1;
        }
    }
    //阶段二：
    //该节点之后的节点如果都没有左右孩子，则是完全二叉树，否则不是
    else
    {
        if(root->lchild != NULL || root->rchild != NULL)
        {
            return 0;
        }
    }

    int lret = IsCompleteByPre(root->lchild);
    int rret = IsCompleteByPre(root->rchild);
    //if(lret == 1 && rret == 1)
    //{
        return 1;
    //}
    //return 0;
}
//判断一棵树是否为完全二叉树(中序实现)
int IsCompleteByIn(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }

    IsCompleteByIn(root->lchild);
    //先序遍历判断每个节点是否满足以下条件，并得出相应结论
    //判断属于哪个阶段,为0为阶段1，为1为阶段2
    int which_flags = 0;
    //阶段一：
    if(which_flags == 0)
    {

        //1. 如果一个节点左右孩子均存在，还属于阶段1，则继续往后遍历
        if(root->lchild != NULL && root->rchild != NULL)
        {
            which_flags = 0;
        }
        //2. 如果一个节点只有右孩子，则该树不是完全二叉树，直接返回即可。
        else if(root->lchild == NULL && root->rchild != NULL)
        {
            return 0;
        }
        //3. 如果一个节点只有左子树，则进入阶段二
        else if(root->lchild != NULL && root->rchild == NULL)
        {
            which_flags = 1;
        }
        //4，如果一个节点没有左右孩子，则进入阶段二
        else
        {
            which_flags = 1;
        }
    }
    //阶段二：
    //该节点之后的节点如果都没有左右孩子，则是完全二叉树，否则不是
    else
    {
        if(root->lchild != NULL || root->rchild != NULL)
        {
            return 0;
        }
    }

    IsCompleteByIn(root->rchild);
    return 1;
}
//判断一棵树是否为完全二叉树(后序实现)
int IsCompleteByPost(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }

    IsCompleteByPost(root->lchild);
    IsCompleteByPost(root->rchild);
    //先序遍历判断每个节点是否满足以下条件，并得出相应结论
    //判断属于哪个阶段,为0为阶段1，为1为阶段2
    int which_flags = 0;
    //阶段一：
    if(which_flags == 0)
    {

        //1. 如果一个节点左右孩子均存在，还属于阶段1，则继续往后遍历
        if(root->lchild != NULL && root->rchild != NULL)
        {
            which_flags = 0;
        }
        //2. 如果一个节点只有右孩子，则该树不是完全二叉树，直接返回即可。
        else if(root->lchild == NULL && root->rchild != NULL)
        {
            return 0;
        }
        //3. 如果一个节点只有左子树，则进入阶段二
        else if(root->lchild != NULL && root->rchild == NULL)
        {
            which_flags = 1;
        }
        //4，如果一个节点没有左右孩子，则进入阶段二
        else
        {
            which_flags = 1;
        }
    }
    //阶段二：
    //该节点之后的节点如果都没有左右孩子，则是完全二叉树，否则不是
    else
    {
        if(root->lchild != NULL || root->rchild != NULL)
        {
            return 0;
        }
    }

    return 1;
}
//判断一棵树是否为完全二叉树(层序实现)
int IsCompleteByLevel(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }

    SeqQueue queue;
    SeqQueueInit(&queue);

    SeqQueuePush(&queue,root);

    SeqQueueType top;
    int which_flags = 0;//用于判断某个节点应该进入哪个分支，根节点首先进入分支一进行判断，所以初始为0
    while(1)
    {
        int ret = SeqQueueTop(&queue,&top);
        if(ret == -1)
        {
            return 1;//当队列为空时，即所有节点都已经遍历并判断结束，还没有退出，说明是完全二叉树
        }
        
        //出栈
        SeqQueuePop(&queue);
        
        //访问该节点，这里的访问操作实际为对该节点进行如下判断
        //分支一
        if(which_flags == 0)
        {

            //1. 如果一个节点左右孩子均存在，则后面的节点还进入分支1进行判断
            if(top->lchild != NULL && top->rchild != NULL)
            {
                which_flags = 0;
            }
            //2. 如果一个节点只有右孩子，则该树不是完全二叉树，直接返回即可。
            else if(top->lchild == NULL && top->rchild != NULL)
            {
                return 0;
            }
            //3. 如果一个节点只有左子树，则后面的节点进入分支二
            else if(top->lchild != NULL && top->rchild == NULL)
            {
                which_flags = 1;
            }
            //4，如果一个节点没有左右孩子，则后面的节点进入分支二
            else
            {
                which_flags = 1;
            }
        }
        //分支二：
        //如果某个节点进入了分支2，则它后面的节点都应进入该分支
        //进入分支2的所有节点如果左右孩子都没有，则为完全二叉树
        else
        {
            //如果进入该分支的某个节点左孩子或右孩子不为空，则必然不是完全二叉树，直接返回即可
            if(top->lchild != NULL || top->rchild != NULL)
            {
                return 0;
            }
        }

        if(top->lchild != NULL)
        {
            SeqQueuePush(&queue,top->lchild);
        }
        if(top->rchild != NULL)
        {
            SeqQueuePush(&queue,top->rchild);
        }
    }
}

//寻找根节点在中序序列中的下标
int Find(char in_order[],size_t in_order_left,size_t in_order_right,TreeType to_find)
{
    int cur = in_order_left;
    for(;cur < in_order_right;cur++)
    {
        if(in_order[cur] == to_find)
        {
            return cur;
        }
    }
    return -1;
}

TreeNode* _TreeRebuild(char pre_order[],size_t* pre_order_index,size_t size,\
        char in_order[],size_t in_order_left,size_t in_order_right)
{
    if(pre_order_index == NULL)
    {
        //非法输入
        return NULL;
    }
    if(*pre_order_index >= size)
    {
        //先序序列遍历结束
        return NULL;
    }
    if(in_order_left >= in_order_right)
    {
        //空树
        return NULL;
    }

    TreeNode* root = CreateNode(pre_order[*pre_order_index]);//创建当前节点

    //寻找当前节点在中序遍历中的位置下标
    size_t cur_index_in_order = Find(in_order,in_order_left,in_order_right,pre_order[*pre_order_index]);

    (*pre_order_index)++;//遍历到后一个节点

    //判断当前节点的左子树是否为空，不为空则后一个节点为当前节点的左子树，创建即可
    root->lchild = _TreeRebuild(pre_order,pre_order_index,size,in_order,in_order_left,cur_index_in_order);

    //当前节点的左子树为空，判断当前节点的右子树是否为空，不为空则后一个节点为当前节点的右子树，创建即可
    root->rchild = _TreeRebuild(pre_order,pre_order_index,size,in_order,cur_index_in_order + 1,in_order_right);

    //如果当前节点的左右子树都为空，则返回到当前节点的上一层节点
    //当前节点的左右子树都创建完毕后，返回当前节点所在的子树
    return root;
}

TreeNode* TreeRebuild(char pre_order[],char in_order[],size_t size)
{
    if(pre_order == NULL || in_order == NULL || size <= 0)
    {
        //空树
        return NULL;
    }

    //先序序列的当前遍历下标
    size_t pre_order_index = 0;

    //当前树在中序序列中的下标范围,前闭后开：[0,size)
    size_t in_order_left = 0;
    size_t in_order_right = size;

    //进入递归函数，判断树是否为空，为空，则直接返回，不为空则创建节点
    return _TreeRebuild(pre_order,&pre_order_index,size,in_order,in_order_left,in_order_right);
}

//TreeNode* _TreeRebuild(TreeType* pre_order,size_t size,size_t* pre_order_index,\
//        TreeType* in_order,size_t in_order_left,size_t in_order_right)
//{
//    if(pre_order == NULL || in_order == NULL || size <= 0) 
//    {
//        //空树
//        return NULL;
//    }
//    if(pre_order_index == NULL)
//    {
//        //非法输入
//        return NULL;
//    }
//    if(*pre_order_index >= size)
//    {
//        //遍历完成
//        return NULL;
//    }
//
//    if(in_order_left >= in_order_right)
//    {
//        //某棵子树为空
//        return NULL;
//    }
//
//    TreeNode* new_node = CreateNode(pre_order[*pre_order_index]);//创建根节点
//    int cur_index_in_order = Find(in_order,in_order_left,in_order_right,pre_order[*pre_order_index]);
//    (*pre_order_index)++;
//
//    //查找当前节点在中序序列中所在的下标
//    assert(cur_index_in_order != -1);
//
//    //如果某个节点有左子树(left < right)，则先序序列中在其之后的节点必在左子树中
//    //如果没有左子树，则先序序列中在其之后的节点必在右子树中
//
//    //创建当前节点的左子树
//    new_node->lchild = _TreeRebuild(pre_order,size,pre_order_index,in_order,in_order_left,cur_index_in_order);
//    //创建当前节点的右子树
//    new_node->rchild = _TreeRebuild(pre_order,size,pre_order_index,in_order,cur_index_in_order + 1,in_order_right);
//    return new_node;
//}
//
////利用先序和中序遍历结果还原一棵二叉树
//TreeNode* TreeRebuild(TreeType pre_order[],TreeType in_order[],size_t size)
//{
//    if(pre_order == NULL || in_order == NULL || size <= 0)
//    {
//        //空树0
//        return NULL;
//    }
//    //先序遍历序列的下标
//    size_t pre_order_index = 0;
//
//    //某个树在中序序列中的下标取值范围
//    size_t in_order_left = 0;
//    size_t in_order_right = size;
//
//    return _TreeRebuild(pre_order,size,&pre_order_index,in_order,in_order_left,in_order_right);
//
//}

TreeNode*  CreateTree(TreeNode* root)
{
    //如果二叉树为空
    if(root == NULL)
    {
        return NULL;
    }
    //如果二叉树不为空，则遍历到一个结点，创建该结点
   TreeNode* rootmirror =  CreateNode(root->data);
   if(root->lchild != NULL)
   {
       rootmirror->lchild = CreateTree(root->lchild);
   }
   if(root->rchild != NULL)
   {
       rootmirror->rchild = CreateTree(root->rchild);
   }
   return rootmirror;

}

//判断两棵树是否相同
int isequal(TreeNode* root1,TreeNode* root2)
{
    if(root1 == NULL && root2 ==NULL)
    {
        return 1;
    }
    if(root1->data == root2->data)
    {
        int ret1 = isequal(root1->lchild,root2->lchild);
        int ret2 = isequal(root1->rchild,root2->rchild);
        if(ret1 == 1 && ret2 == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
//判断一棵二叉树是否对称，对称就是该二叉树的镜像与其相同
int isSymmetrical(TreeNode* root)
{
    if(root == NULL)
    {
        return 1;
    }
    //先原样创建一棵二叉树
    TreeNode* rootmirror = CreateTree(root);
    //将新创建的二叉树转换为其镜像
    TreeMirror(rootmirror);
    //判断原二叉树与镜像是否相同
    return isequal(root,rootmirror);

}

//判断两棵子树是否对称
//如果两棵树对称，则
//1.这两棵树的根节点的值相同
//2.一棵树的左子树与另一棵树的右子树对称
//3.一棵树的右子树与另一棵树的左子树对称
int isTreeSymmetrical(TreeNode* root1,TreeNode* root2)
{
    //如果两棵树均为空，则相等
    if(root1 == NULL && root2 == NULL)
    {
        return 1;
    }
    if(root1 == NULL || root2 == NULL)
    {
        return 0;
    }
    if(root1->data == root2->data)
    {
        int ret1 = isTreeSymmetrical(root1->lchild,root2->rchild);
        int ret2 = isTreeSymmetrical(root1->rchild,root2->lchild);
        if(ret1 == 1 && ret2 == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
//判断一棵二叉树是否对称，对称就是该二叉树的镜像与其相同
//不额外创建二叉树
int isSymmetricalEx(TreeNode* root)
{
    //如果根节点为空，则二叉树对称
    if(root == NULL)
    {
        return 1;
    }
    //如果根节点不为空，则判断根节点的左右子树是否对称
    return isTreeSymmetrical(root->lchild,root->rchild);
}
///////////////////////////////////////
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

void TestMirror()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    TreeMirror(root);
    TreePreOrderByLoop(root);
    printf("\n");

    char arr[] = "abd#fg####c#e##";
    root = TreeCreate(arr,strlen(arr),'#');
    TreeMirror(root);

    TreePreOrderByLoop(root);
    printf("\n");
    PreOrder(root);
    printf("\n");
}

void TestMirrorByLoop()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    TreeMirrorByLoop(root);
    TreePreOrderByLoop(root);
    printf("\n");

    char arr[] = "abd#fg####c#e##";
    root = TreeCreate(arr,strlen(arr),'#');
    TreeMirrorByLoop(root);

    TreePreOrderByLoop(root);
    printf("\n");
    PreOrder(root);
    printf("\n");

}

void TestIsCompleteByPre()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    int ret;
    ret = IsCompleteByPre(root);
    printf("expect 0,actually %d\n",ret);

    char arr[] = "abd#fg####c#e##";
    root = TreeCreate(arr,strlen(arr),'#');
    printf("expect 0,actually %d\n",ret);

    char arr1[] = "ab##c##";
    TreeNode* root1 = TreeCreate(arr1,strlen(arr1),'#');
    ret = IsCompleteByPre(root1);
    printf("expect 1,actually %d\n",ret);

    char arr2[] = "abd###c##";
    TreeNode* root2 = TreeCreate(arr2,strlen(arr2),'#');
    ret = IsCompleteByPre(root2);
    printf("expect 1,actually %d\n",ret);

    char arr3[] = "abd##e##c##";
    TreeNode* root3 = TreeCreate(arr3,strlen(arr3),'#');
    ret = IsCompleteByPre(root3);
    printf("expect 1,actually %d\n",ret);

    char arr4[] = "abd##e##cf###";
    TreeNode* root4 = TreeCreate(arr4,strlen(arr4),'#');
    ret = IsCompleteByPre(root4);
    printf("expect 1,actually %d\n",ret);

    char arr5[] = "abd###c#f##";
    TreeNode* root5 = TreeCreate(arr5,strlen(arr5),'#');
    ret = IsCompleteByLevel(root5);
    printf("expect 0,actually %d\n",ret);

    char arr6[] = "abdf####c#g###";
    TreeNode* root6 = TreeCreate(arr6,strlen(arr6),'#');
    ret = IsCompleteByLevel(root6);
    printf("expect 0,actually %d\n",ret);

    char arr7[] = "abdh###e##cf##g##";
    TreeNode* root7 = TreeCreate(arr7,strlen(arr7),'#');
    ret = IsCompleteByLevel(root7);
    printf("expect 1,actually %d\n",ret);
}
void TestIsCompleteByIn()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    int ret;
    ret = IsCompleteByIn(root);
    printf("expect 0,actually %d\n",ret);

    char arr[] = "abd#fg####c#e##";
    root = TreeCreate(arr,strlen(arr),'#');
    printf("expect 0,actually %d\n",ret);

    char arr1[] = "ab##c##";
    TreeNode* root1 = TreeCreate(arr1,strlen(arr1),'#');
    ret = IsCompleteByIn(root1);
    printf("expect 1,actually %d\n",ret);

    char arr2[] = "abd###c##";
    TreeNode* root2 = TreeCreate(arr2,strlen(arr2),'#');
    ret = IsCompleteByIn(root2);
    printf("expect 1,actually %d\n",ret);

    char arr3[] = "abd##e##c##";
    TreeNode* root3 = TreeCreate(arr3,strlen(arr3),'#');
    ret = IsCompleteByIn(root3);
    printf("expect 1,actually %d\n",ret);

    char arr4[] = "abd##e##cf###";
    TreeNode* root4 = TreeCreate(arr4,strlen(arr4),'#');
    ret = IsCompleteByIn(root4);
    printf("expect 1,actually %d\n",ret);

    char arr5[] = "abd###c#f##";
    TreeNode* root5 = TreeCreate(arr5,strlen(arr5),'#');
    ret = IsCompleteByLevel(root5);
    printf("expect 0,actually %d\n",ret);

    char arr6[] = "abdf####c#g###";
    TreeNode* root6 = TreeCreate(arr6,strlen(arr6),'#');
    ret = IsCompleteByLevel(root6);
    printf("expect 0,actually %d\n",ret);

    char arr7[] = "abdh###e##cf##g##";
    TreeNode* root7 = TreeCreate(arr7,strlen(arr7),'#');
    ret = IsCompleteByLevel(root7);
    printf("expect 1,actually %d\n",ret);
}

void TestIsCompleteByPost()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    int ret;
    ret = IsCompleteByPost(root);
    printf("expect 0,actually %d\n",ret);

    char arr[] = "abd#fg####c#e##";
    root = TreeCreate(arr,strlen(arr),'#');
    printf("expect 0,actually %d\n",ret);

    char arr1[] = "ab##c##";
    TreeNode* root1 = TreeCreate(arr1,strlen(arr1),'#');
    ret = IsCompleteByPost(root1);
    printf("expect 1,actually %d\n",ret);

    char arr2[] = "abd###c##";
    TreeNode* root2 = TreeCreate(arr2,strlen(arr2),'#');
    ret = IsCompleteByPost(root2);
    printf("expect 1,actually %d\n",ret);

    char arr3[] = "abd##e##c##";
    TreeNode* root3 = TreeCreate(arr3,strlen(arr3),'#');
    ret = IsCompleteByPost(root3);
    printf("expect 1,actually %d\n",ret);

    char arr4[] = "abd##e##cf###";
    TreeNode* root4 = TreeCreate(arr4,strlen(arr4),'#');
    ret = IsCompleteByPost(root4);
    printf("expect 1,actually %d\n",ret);

    char arr5[] = "abd###c#f##";
    TreeNode* root5 = TreeCreate(arr5,strlen(arr5),'#');
    ret = IsCompleteByLevel(root5);
    printf("expect 0,actually %d\n",ret);

    char arr6[] = "abdf####c#g###";
    TreeNode* root6 = TreeCreate(arr6,strlen(arr6),'#');
    ret = IsCompleteByLevel(root6);
    printf("expect 0,actually %d\n",ret);

    char arr7[] = "abdh###e##cf##g##";
    TreeNode* root7 = TreeCreate(arr7,strlen(arr7),'#');
    ret = IsCompleteByLevel(root7);
    printf("expect 1,actually %d\n",ret);
}

void TestIsCompleteByLevel()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    int ret;
    ret = IsCompleteByLevel(root);
    printf("expect 0,actually %d\n",ret);

    char arr[] = "abd#fg####c#e##";
    root = TreeCreate(arr,strlen(arr),'#');
    printf("expect 0,actually %d\n",ret);

    char arr1[] = "ab##c##";
    TreeNode* root1 = TreeCreate(arr1,strlen(arr1),'#');
    ret = IsCompleteByLevel(root1);
    printf("expect 1,actually %d\n",ret);

    char arr2[] = "abd###c##";
    TreeNode* root2 = TreeCreate(arr2,strlen(arr2),'#');
    ret = IsCompleteByLevel(root2);
    printf("expect 1,actually %d\n",ret);

    char arr3[] = "abd##e##c##";
    TreeNode* root3 = TreeCreate(arr3,strlen(arr3),'#');
    ret = IsCompleteByLevel(root3);
    printf("expect 1,actually %d\n",ret);

    char arr4[] = "abd##e##cf###";
    TreeNode* root4 = TreeCreate(arr4,strlen(arr4),'#');
    ret = IsCompleteByLevel(root4);
    printf("expect 1,actually %d\n",ret);

    char arr5[] = "abd###c#f##";
    TreeNode* root5 = TreeCreate(arr5,strlen(arr5),'#');
    ret = IsCompleteByLevel(root5);
    printf("expect 0,actually %d\n",ret);

    char arr6[] = "abdf####c#g###";
    TreeNode* root6 = TreeCreate(arr6,strlen(arr6),'#');
    ret = IsCompleteByLevel(root6);
    printf("expect 0,actually %d\n",ret);

    char arr7[] = "abdh###e##cf##g##";
    TreeNode* root7 = TreeCreate(arr7,strlen(arr7),'#');
    ret = IsCompleteByLevel(root7);
    printf("expect 1,actually %d\n",ret);
}

void TestTreeRebuild()
{
    TEST_HANDLE;
    char pre_order[] = "abdfgc";
    char in_order[] = "dbfgac";
    TreeNode* root = TreeRebuild(pre_order,in_order,strlen(pre_order));
    TreePreOrderByLoop(root);
    printf("\n");
    TreeInOrderByLoop(root);
    printf("\n");
    return;
}

void TestPrintByLevelOrder()
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

    PrintByLevelOrder(a);
    printf("\n");
    return;

}

void TestisSymmetrical()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    TreeNode* a = CreateNode('a');
    TreeNode* b = CreateNode('b');
    TreeNode* c = CreateNode('b');
    TreeNode* d = CreateNode('d');
    TreeNode* e = CreateNode('d');
  //  TreeNode* f = CreateNode('f');
  //  TreeNode* g = CreateNode('g');

    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
  //  b->rchild = e;
  //  e->rchild = f;
    c->rchild = e;

    int ret = isSymmetrical(a);
    printf("expect 1,actually %d\n",ret);
    printf("\n");
    return;
    
}
void TestisSymmetricalEx()
{
    TEST_HANDLE;
    TreeNode* root;
    TreeInit(&root);

    TreeNode* a = CreateNode('a');
    TreeNode* b = CreateNode('b');
    TreeNode* c = CreateNode('b');
    TreeNode* d = CreateNode('d');
    TreeNode* e = CreateNode('d');
  //  TreeNode* f = CreateNode('f');
  //  TreeNode* g = CreateNode('g');

    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
  //  b->rchild = e;
  //  e->rchild = f;
    c->rchild = e;

    int ret = isSymmetricalEx(a);
    printf("expect 1,actually %d\n",ret);
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
    TestMirror();
    TestMirrorByLoop();
    TestIsCompleteByPre();
    TestIsCompleteByIn();
    TestIsCompleteByPost();
    TestIsCompleteByLevel();
    TestTreeRebuild();
    TestPrintByLevelOrder();
    TestisSymmetrical();
    TestisSymmetricalEx();
    return 0;
}
