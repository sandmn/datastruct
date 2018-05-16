
//搜索二叉树的基本操作(递归和非递归)
#include"search_tree.h"
#include<stdio.h>
#include<stdlib.h>

//初始化二叉搜索树
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

SearchTreeNode* CreateNode(SearchTreeType value)
{
    SearchTreeNode* new_node = (SearchTreeNode*)malloc(sizeof(SearchTreeNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

//在二叉搜索树中插入元素
void SearchTreeInsert(SearchTreeNode** proot,SearchTreeType value)
{
    if(proot == NULL)
    {
        //非法输入
        return;
    }

    SearchTreeNode* new_node = CreateNode(value);
    if(*proot == NULL)
    {
        //插入之前树为空，则将根节点的指针指向新创建的节点
        *proot = new_node;
        return;
    }
    //插入之前树不为空，则从根节点开始遍历查找应该插入的位置
    //如果新节点的值小于根节点的值，则新节点应插入到左子树中
    if(value < (*proot)->data)
    {
        //然后递归遍历左子树进行插入
        SearchTreeInsert(&(*proot)->lchild,value);
    }
    //如果新节点的值大于根节点的值，则新节点应插入到右子树中
    else if(value > (*proot)->data)
    {
        //然后递归遍历右子树进行插入
        SearchTreeInsert(&(*proot)->rchild,value);
    }
    else
    {
        //如果相等，作如下规定：二叉搜索树中不允许有相等的节点
        //此时，直接返回即可
        return;
    }
    return;
}

//在二叉搜索树中查找指定元素
SearchTreeNode* SearchTreeFind(SearchTreeNode* root,SearchTreeType to_find)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    //首先判断根节点处的值与所要查找元素的大小关系，如果相等，则直接返回根节点的指针
    if(root->data == to_find)
    {
        return root;
    }
    else if(to_find < root->data)//如果要查找节点的值小于根节点的值
    {
        //则在左子树中递归遍历查找
        return SearchTreeFind(root->lchild,to_find);
    }
    else//如果要查找节点的值大于根节点的值
    {
        //则在右子树中递归遍历查找
        return SearchTreeFind(root->rchild,to_find);
    }
}

void DestroyNode(SearchTreeNode* node)
{
    free(node);
}
SearchTreeNode* Parent(SearchTreeNode* root,SearchTreeNode* child)
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
    SearchTreeNode* lret = Parent(root->lchild,child);
    SearchTreeNode* rret = Parent(root->rchild,child);
    return (lret != NULL)? lret : rret;

}

//在二叉搜索树中删除指定元素（递归）
void SearchTreeRemove(SearchTreeNode** proot,SearchTreeType to_remove)
{
    if(proot == NULL)
    {
        //非法输入
        return;
    }
    if(*proot == NULL)
    {
        //空树，删除失败
        //该语句还表示，如果最后最后遍历到空的根节点，说明没有找到要删除的节点，此时也是删除失败
        return;
    }
    //接下来在左右子树中遍历查找要删除元素所在的位置
    
    SearchTreeNode* root = *proot;

    //如果要删除元素小于根节点，则在左子树中递归遍历查找
    if(to_remove < root->data)
    {
        SearchTreeRemove(&root->lchild,to_remove);  
    }
    else if(to_remove > root->data)//如果要删除元素大于根节点的值，则在右子树中递归遍历查找
    {
        SearchTreeRemove(&root->rchild,to_remove);
    }
    else//此时说明找到了要删除的节点了
    {
        //此时root便是要删除的节点，根据要删除节点的状态可分为如下四种情况讨论
        //1. 如果要删除的节点没有左右子树
        if(root->lchild == NULL && root->rchild == NULL)
        {
            //此时直接将该处的节点指针置为空，并释放内存即可
            //该处的指针为root，要改变root的指向，即改变root的值
            //此时就需要通过二级指针来改变指针的指向
            //在该层递归函数中，如果直接改变行参root的值，并不会真正改变实际内存中的值，
            //所以要是用二级指针来找到真正的内存空间，再将其内容置为空即可
            //这里不用区分要删除的节点是其父节点的左子树还是右子树
            //因为父节点就是通过指针的指针来找到它的该孩子节点所在的位置
            //然后在对其进行判断其左右子树是否为空的，所以直接通过二级指针来改变该节点处的值即可
            *proot = NULL;
            DestroyNode(root);
        }
        //2. 如果要删除的节点只有左子树
        else if(root->lchild != NULL && root->rchild == NULL)
        {
            //将要删除节点的左子树放在要删除节点的位置，再将要删除的节点释放即可
            //*proot相当于要删除节点指针所存放的内存空间
            //root相当于该空间中存放的值
            //所以如果要删除的元素为父节点的左子树，只需将该空间中的值替换为要删除节点的左子树的指针
            //然后释放要删除节点的值即可
            //如果要删除元素为父节点的左子树，也就是说*proot中存放的就是父节点左子树的值
            *proot = root->lchild;//*proot 作右值时表示的是值的大小，作左值时表示的是空间的大小
            DestroyNode(root);
        }
        //3. 如果要删除的节点只有右子树
        else if(root->lchild == NULL && root->rchild != NULL)
        {
            *proot = root->rchild;
            DestroyNode(root);
        }
        //4. 如果要删除的节点左右子树都有
        else
        {
            //此时，需要现在要删除节点的右子树中找到到最小值，将最小值赋值给要删除节点的数据域
            //然后再递归删除最小值即可
            SearchTreeNode* min = root->rchild;
            while(min->lchild != NULL)
            {
                min = min->lchild;
            }
            //当循环结束时，说明min即为要删除元素右子树中的最小值
            root->data = min->data;
            SearchTreeRemove(&root->rchild,min->data);
            //SearchTreeRemove(&min,min->data);
        }
    }
    return;
    //2. 如果找不到，则删除失败
    //3. 如果找到了该节点，可分为以下几种情形讨论
    //  a）该节点没有左右子树
    //      i）如果该节点是根节点，则直接将根节点置空即可
    //      ii)如果该节点不是根节点，那么该节点就是叶子节点
    //          如果要删除的节点是其父节点的右子树，则将父节点的右子树置为空
    //          如果要删除节点是其父节点的左子树，则将父节点的左子树置为空
    //      最后将该节点释放即可
    //  b）该节点只有左子树
    //      i）如果要删除的节点是父节点，则将父节点的左子树作为新的根节点
    //      ii）如果要删除的元素不是父节点
    //          如果要删除的元素是其父节点的左子树，则将要删除的节点的左子树作为其父节点的左子树
    //          如果要删除节点是其父节点的右子树，则将要删除节点的左子树作为其父节点的右子树
    //      最后，释放该节点
    //  c）该节点只有右子树
    //      i）如果要删除的节点是根节点，则删除节点的右子树作为新的根节点
    //      ii）如果要删除节点不是根节点
    //          如果要删除节点是其父节点的左子树，则将要删除节点的右子树作为其父节点的左子树
    //          如果要删除节点是其父节点的右子树，则将要删除节点的右子树作为其父节点的右子树
    //      最后释放要删除节点
    //  d）该节点有左右节点
    //      先在要删除节点的右子树中找到最小值，同时记录最小值的父节点
    //      然后将最小值赋值给要删除节点的值，则现在要删除的就是最小值节点了
    //      i）如果要最小值是要删除节点的右子树，则该右子树一定没有左子树，
    //         因此将最小值的右子树赋值给要删除节点的右子树
    //      ii）如果最小值不是要删除节点的右子树，则该最小值一定也没有左子树
    //          则将最小值的右子树赋值给最小值父节点的左子树
    //          
    //


}
//在二叉搜索树中删除指定元素(非递归)
void SearchTreeRemoveByLoop(SearchTreeNode** proot,SearchTreeType to_remove)
{
    if(proot == NULL)
    {
        //非法输入
        return;
    }
    if(*proot == NULL)
    {
        //空树，删除失败
        return;
    }
    //1. 首先查找要删除元素和其父节点所在的位置
    SearchTreeNode* to_remove_node = *proot;
    SearchTreeNode* pre = NULL;
    while(1)
    {
        if(to_remove_node == NULL)
        {
            //2. 如果找不到，则删除失败
            //此时说明没有找到要删除的节点，说明删除失败，直接返回即可
            return;
        }
        if(to_remove_node->data == to_remove)
        {
            break;//此时to_remove_node即为要删除的节点
        }
        else if(to_remove < to_remove_node->data)
        {
            //说明要删除的节点可能在to_remove_node的左子树中
            pre = to_remove_node;
            to_remove_node = to_remove_node->lchild;
        }
        else
        {
            //说明要删除的节点可能在to_remove_node的右子树中
            pre = to_remove_node;
            to_remove_node = to_remove_node->rchild;
        }
    }

    //走到这里，说明to_remove_node就是要删除节点的指针
    //3. 如果找到了该节点，可分为以下几种情形讨论

    //  a）该节点没有左右子树
    if(to_remove_node->lchild == NULL && to_remove_node->rchild == NULL)
    {
        //      i）如果该节点是根节点，则直接将根节点置空即可
        if(to_remove_node == *proot)
        {
            *proot = NULL;
        }
        //      ii)如果该节点不是根节点，那么该节点就是叶子节点
        else 
        {
            //          如果要删除的节点是其父节点的右子树，则将父节点的右子树置为空
            if(to_remove_node == pre->rchild)
            {
                pre->rchild = NULL;
            }
            //          如果要删除节点是其父节点的左子树，则将父节点的左子树置为空
            else if(to_remove_node == pre->lchild)
            {
                pre->lchild = NULL;
            }
        }
        //      最后将该节点释放即可
        DestroyNode(to_remove_node);
    }

    //  b）该节点只有左子树
    else if(to_remove_node->lchild != NULL && to_remove_node->rchild == NULL)
    {
        //      i）如果要删除的节点是跟节点，则将跟节点的左子树作为新的根节点
        if(to_remove_node == *proot)
        {
            *proot = to_remove_node->lchild;
        }
        //      ii）如果要删除的元素不是父节点
        else
        {
            //          如果要删除的元素是其父节点的左子树，则将要删除的节点的左子树作为其父节点的左子树
            if(to_remove_node == pre->lchild)
            {
                pre->lchild = to_remove_node->lchild;
            }
            //          如果要删除节点是其父节点的右子树，则将要删除节点的左子树作为其父节点的右子树
            else if(to_remove_node == pre->rchild)
            {
                pre->rchild = to_remove_node->lchild;
            }
        }
        //      最后，释放该节点
        DestroyNode(to_remove_node);
    }

    //  c）该节点只有右子树
    else if(to_remove_node->lchild == NULL && to_remove_node->rchild != NULL)
    {
        //      i）如果要删除的节点是根节点，则将要删除节点的右子树作为新的根节点
        if(to_remove_node == *proot)
        {
            *proot = to_remove_node->rchild;
        }
        //      ii）如果要删除节点不是根节点
        else
        {
            //          如果要删除节点是其父节点的左子树，则将要删除节点的右子树作为其父节点的左子树
            if(to_remove_node == pre->lchild)
            {
                pre->lchild = to_remove_node->rchild;
            }
            //          如果要删除节点是其父节点的右子树，则将要删除节点的右子树作为其父节点的右子树
            else if(to_remove_node == pre->rchild)
            {
                pre->rchild = to_remove_node->rchild;
            }
        }
        //      最后释放要删除节点
        DestroyNode(to_remove_node);
    }

    //  d）该节点有左右节点
    else
    {
        //      先在要删除节点的右子树中找到最小值，同时记录最小值的父节点
        SearchTreeNode* min = to_remove_node->rchild;
        SearchTreeNode* min_pre = to_remove_node;
        while(min->lchild != NULL)
        {
            min_pre = min;
            min = min->lchild;
        }
        //此时，min即为要删除元素右子树中的最小值
        //      然后将最小值赋值给要删除节点的值，则现在要删除的就是最小值节点了
        to_remove_node->data = min->data;
        //  i)如果最小值是要删除节点的右子树，则最小值的父节点一定是要删除的节点则该右子树一定没有左子树，
        if(min == to_remove_node->rchild)
        {
            //         因此将最小值的右子树赋值给要删除节点的右子树
            to_remove_node->rchild = min->rchild;
        }
        //      ii）如果最小值不是要删除节点的右子树，则该最小值一定也没有左子树
        else
        {
            //          则将最小值的右子树赋值给最小值父节点的左子树
            min_pre->lchild = min->rchild;
        }
        //      最后释放要最小值节点
        DestroyNode(min);
    }

    //2. 如果找不到，则删除失败
    //3. 如果找到了该节点，可分为以下几种情形讨论
    //  a）该节点没有左右子树
    //      i）如果该节点是根节点，则直接将根节点置空即可
    //      ii)如果该节点不是根节点，那么该节点就是叶子节点
    //          如果要删除的节点是其父节点的右子树，则将父节点的右子树置为空
    //          如果要删除节点是其父节点的左子树，则将父节点的左子树置为空
    //      最后将该节点释放即可
    //  b）该节点只有左子树
    //      i）如果要删除的节点是父节点，则将父节点的左子树作为新的根节点
    //      ii）如果要删除的元素不是父节点
    //          如果要删除的元素是其父节点的左子树，则将要删除的节点的左子树作为其父节点的左子树
    //          如果要删除节点是其父节点的右子树，则将要删除节点的左子树作为其父节点的右子树
    //      最后，释放该节点
    //  c）该节点只有右子树
    //      i）如果要删除的节点是根节点，则删除节点的右子树作为新的根节点
    //      ii）如果要删除节点不是根节点
    //          如果要删除节点是其父节点的左子树，则将要删除节点的右子树作为其父节点的左子树
    //          如果要删除节点是其父节点的右子树，则将要删除节点的右子树作为其父节点的右子树
    //      最后释放要删除节点
    //  d）该节点有左右节点
    //      先在要删除节点的右子树中找到最小值，同时记录最小值的父节点
    //      然后将最小值赋值给要删除节点的值，则现在要删除的就是最小值节点了
    //      i）如果要最小值是要删除节点的右子树，则该右子树一定没有左子树，
    //         因此将最小值的右子树赋值给要删除节点的右子树
    //      ii）如果最小值不是要删除节点的右子树，则该最小值一定也没有左子树
    //          则将最小值的右子树赋值给最小值父节点的左子树
    //          
    //
}
////在二叉搜索树中删除指定元素
//void SearchTreeRemove(SearchTreeNode** proot,SearchTreeType to_remove)
//{
//    if(proot == NULL)
//    {
//        //非法输入
//        return;
//    }
//    if(*proot == NULL)
//    {
//        //空树
//        return;
//    }
//    //1.先根据上述的Find找到指定元素所在的位置
//    //2.如果没有找到，则直接返回
//    //3.如果找到了，且为根节点
//    //  a）如果根节点的右子树为空，则直接将左子树的根节点作为新的根节点，然后删原即可
//    //  b）如果根节点的右子树不为空，则在右子树的根节点中找到最小值，将该最小值作为新的根节点
//    //      i)如果最小值不为右子树的根节点
//    //      ii）若最小值为右子树的根节点
//    //4.如果找到了，且不为根节点
//    //  a）如果要删除的节点的右子树为空，直接删除该节点，将该节点的左子树作为该节点父节点的左子树
//    //  b）如果要删除节点的右子树不为空，找到右子树中的最小值，将要删除节点的左子树作为最小值的左子树
//
//    //1.先根据上述的Find找到指定元素所在的位置
//    SearchTreeNode* remove_pos = SearchTreeFind(*proot,to_remove);
//    //2.如果没有找到，则直接返回
//    if(remove_pos == NULL)
//    {
//        return;
//    }
//    //3.如果找到了，且为根节点
//    if(remove_pos == *proot)
//    {
//        //  a）如果根节点的右子树为空，则直接将左子树的根节点作为新的根节点，然后删原即可
//        if(remove_pos->rchild == NULL)
//        {
//            *proot = remove_pos->lchild;
//            DestroyNode(remove_pos);
//            return;
//        }
//        //  b）如果根节点的右子树不为空，则在右子树的根节点中找到最小值，将该最小值作为新的根节点
//        //      i）若最小值为右子树的根节点
//        if(remove_pos->rchild->lchild == NULL)
//        {
//            *proot = remove_pos->rchild;
//            (*proot)->lchild = remove_pos->lchild;
//            DestroyNode(remove_pos);
//            return;
//        }
//        //  ii)如果最小值不为右子树的根节点,循环寻找左子树中的最小值
//        SearchTreeNode* min = remove_pos->rchild;
//        while(min->lchild->lchild != NULL)
//        {
//            min = min->lchild;
//        }
//        SearchTreeNode* min_parent = min;
//        min = min->lchild;
//    //    //如果最小值的右子树为空
//    //    if(min->rchild == NULL)
//    //    {
//    //        min->rchild = min_parent;
//    //        min->lchild = remove_pos->lchild;
//    //        *proot = min;
//    //        DestroyNode(min);
//    //        return;
//    //    }
//        //如果最小值的右子树不为空,循环寻找右子树中的最大值
//        SearchTreeNode* max = min->rchild;
//
//        while(max->rchild != NULL)
//        {
//            max = max->rchild;
//        }
//        max->rchild = min_parent;
//        min->lchild = remove_pos->rchild;
//        *proot = min;
//        DestroyNode(remove_pos);
//        return;
//    }
//    //4.如果找到了，且不为根节点
//    SearchTreeNode* remove_parent = Parent(*proot,remove_pos);
//    //  a）如果要删除的节点的右子树为空，直接删除该节点，将该节点的左子树作为该节点父节点的右子树
//    if(remove_pos->rchild == NULL)
//    {
//        if(remove_parent->lchild == remove_pos)
//        {
//            remove_parent->lchild = remove_pos->lchild;
//        }
//        else
//        {
//            remove_parent->rchild = remove_pos->lchild;
//        }
//        DestroyNode(remove_pos);
//        return;
//    }
//    //  b）如果要删除节点的右子树不为空，找到右子树中的最小值，将要删除节点的左子树作为最小值的左子树
//    SearchTreeNode* no_root_min = remove_pos->rchild;
//    while(no_root_min->lchild != NULL)
//    {
//        no_root_min = no_root_min->lchild;
//    }
//
//    SearchTreeNode* no_root_max = no_root_min;
//    while(no_root_max->rchild != NULL)
//    {
//        no_root_max = no_root_max->rchild;
//    }
//    SearchTreeNode* min_parent = Parent(*proot,no_root_min);
//    if(min_parent != remove_pos)
//    {
//        no_root_max->rchild = min_parent;
//    }
//
//    no_root_min->lchild = remove_pos->lchild;
//    
//    if(remove_parent->lchild == remove_pos)
//    {
//        remove_parent->lchild = no_root_min;
//    }
//    else
//    {
//        remove_parent->rchild = no_root_min;
//    }
//    DestroyNode(remove_pos);
//    return;
//}
//在二叉搜索树中插入指定元素（非递归）
void SearchTreeInsertByLoop(SearchTreeNode** proot,SearchTreeType value)
{
    if(proot == NULL)
    {
        //非法输入
        return;
    }
    //创建新节点
    SearchTreeNode* new_node = CreateNode(value);
    //如果根节点为空，直接使根节点的指针指向新节点
    if(*proot == NULL)
    {
        *proot = new_node;
        return;
    }
    //从根节点开始循环遍历寻找新节点要插入的节点，该节点的左右子树必须至少有一个为空，
    //且与新节点的大小关系满足搜索二叉树的定义
    //在插入新节点时，要一层一层的往下遍历直到找到可以插入的节点
    SearchTreeNode* cur = *proot;
    while(1)
    {
        //如果某个节点的左子树为空，且value的值小于该节点的值
        //将新节点作为该节点的左子树
        if(cur->lchild == NULL && value < cur->data)
        {
            cur->lchild = new_node;
            break;
        }
        //如果某个节点的右子树为空，且value的值大于该节点的值
        //将新节点作为该节点的右子树
        if(cur->rchild == NULL && value > cur->data)
        {
            cur->rchild = new_node;
            break;
        }
        //如果某个节点的左子树不为空,且value的值小于该节点的值
        //则在该节点的左子树中继续循环遍历查找
        if(value < cur->data)
        {
            cur = cur->lchild;
        }
        //如果某个节点的右子树不为空，且value的值大于该节点的值
        //则在该节点的右子树中继续循环遍历查找
        else if(value > cur->data)
        {
            cur = cur->rchild;
        }
        //如果遇到与某个节点的值相等，则直接结束，不进行插入
        else
        {
            DestroyNode(new_node);//释放新创建的节点
            break;
        }
    }
    return;
}
//在二叉搜索树中查找指定元素（非递归）
SearchTreeNode* SearchTreeFindByLoop(SearchTreeNode* root,SearchTreeType to_find)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    //从根节点开始遍历查找，待找到某个节点
    SearchTreeNode* cur = root;
    while(1)
    {   
        //如果遍历到某个节点时，该节点为空，则说明要查找的值不存在
        if(cur == NULL)
        {
            break;
        }
        //如果要查找节点的值小于根节点的值，则在左子树中循环遍历查找
        if(to_find < cur->data)
        {
            cur = cur->lchild;
        }
        //rug要查找节点的值大于根节点的值，则在该节点的右子树中继续循环遍历查找
        else if(to_find > cur->data)
        {
            cur = cur->rchild;
        }
        else
        {
            return cur;
        }
    }
    return NULL;
}
//给定一个数组，查找某个数字是否在数组中
int SearchNumInArray(SearchTreeType array[],size_t size,SearchTreeType to_find)
{
    if(array == NULL || size < 0)
    {
        //非法输入，查找失败
        return 0;
    }
    //1. 首先根据数组元素建立一个二叉搜索树
    SearchTreeNode* root;
    SearchTreeInit(&root);//初始化二叉搜索树

    int index = 0;
    for(;index < size;++index)
    {
        SearchTreeInsert(&root,array[index]);
    }
    //2. 然后在该二叉搜索树中查找指定值
    SearchTreeNode* to_find_node = SearchTreeFind(root,to_find);
    //3. 如果找到，返回1
    if(to_find_node == NULL)
    {
        return 0;
    }
    //4. 如果没找到，返回0
    else
    {
        return 1;
    }
}
//////////////////////////
//测试代码
//////////////////////////

#include<stdio.h>
#define TEST_HANDLE printf("====================%s===============\n",__FUNCTION__)

//测试初始化
void TestInit()
{
    TEST_HANDLE;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    printf("expect null,actually %p\n",root);
    return;
}

void PrePrint(SearchTreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    printf("%c ",root->data);
    PrePrint(root->lchild);
    PrePrint(root->rchild);
    return;
}
void InPrint(SearchTreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    InPrint(root->lchild);
    printf("%c ",root->data);
    InPrint(root->rchild);
    return;
}

//打印搜索二叉树的先序和中序遍历
void SearchTreePrint(SearchTreeNode* root,const char* msg)
{
    printf("%s\n",msg);
    printf("打印先序序列\n");
    PrePrint(root);
    printf("\n");
    printf("打印中序序列\n");
    InPrint(root);
    printf("\n");
    return;
}
//测试插入函数
void TestInsert()
{
    TEST_HANDLE;
    
    SearchTreeInsert(NULL,'a');//测试非法输入

    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');//测试在空树中插入节点
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'e');//测试插入已有的值

    SearchTreePrint(root,"打印搜索二叉树的先序和中序遍历");
    return;

}

//测试查找函数
void TestFind()
{
    TEST_HANDLE;
    SearchTreeNode* root;
    SearchTreeInit(&root);

    SearchTreeNode* to_find;
    to_find = SearchTreeFind(root,'a');//测试在空树中查找
    printf("expect null,actually %p\n",to_find);

    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'e');

    to_find = SearchTreeFind(root,'a');//测试在非空树中查找存在的元素
    printf("expect %p,actually %p\n",root,to_find);
    printf("expect a,actually %c\n",to_find->data);

    to_find = SearchTreeFind(root,'g');//测试在非空树中查找不存在的元素
    printf("expect null,actually %p\n",to_find);

    return;
}

void TestRemoveByLoop()
{
    TEST_HANDLE;

    SearchTreeRemoveByLoop(NULL,'a');//测试非法输入

    SearchTreeNode* root;
    SearchTreeInit(&root);

    SearchTreeRemoveByLoop(&root,'a');//测试删除空树

    SearchTreeInsert(&root,'a');
    SearchTreeRemoveByLoop(&root,'a');//测试a)i)
    SearchTreePrint(root,"删除只有一个根节点a的情况");

    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'c');
    SearchTreeRemoveByLoop(&root,'a');//测试a)ii)1
    SearchTreePrint(root,"删除节点a的情况");

    SearchTreeInsert(&root,'a');
    SearchTreeRemoveByLoop(&root,'c');//测试a)ii)2
    SearchTreePrint(root,"删除节点c的情况");

    SearchTreeRemoveByLoop(&root,'b');//测试b)i)
    SearchTreePrint(root,"删除节点b的情况");

    SearchTreeRemoveByLoop(&root,'a');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'a');
    SearchTreeRemoveByLoop(&root,'b');//测试删除b)ii)1
    SearchTreePrint(root,"删除节点b的情况");
    
    SearchTreeRemoveByLoop(&root,'a');
    SearchTreeRemoveByLoop(&root,'c');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'d');
    SearchTreeRemoveByLoop(&root,'e');//测试b)ii)2
    SearchTreePrint(root,"删除节点e的情况");

    SearchTreeRemoveByLoop(&root,'c');
    SearchTreeRemoveByLoop(&root,'d');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeRemoveByLoop(&root,'a');//测试c)i)
    SearchTreePrint(root,"删除节点a的情况");
    
    SearchTreeRemoveByLoop(&root,'b');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'c');
    SearchTreeRemoveByLoop(&root,'b');//测试c)ii)1
    SearchTreePrint(root,"删除节点b的情况");
    
    SearchTreeRemoveByLoop(&root,'d');
    SearchTreeRemoveByLoop(&root,'c');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'c');
    SearchTreeRemoveByLoop(&root,'b');//测试c)ii)2
    SearchTreePrint(root,"删除节点b的情况");

    SearchTreeRemoveByLoop(&root,'a');
    SearchTreeRemoveByLoop(&root,'c');
    SearchTreeInsert(&root,'g');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'f');
    SearchTreeRemoveByLoop(&root,'d');//测试d)i)
    SearchTreePrint(root,"删除节点d的情况");

    SearchTreeRemoveByLoop(&root,'g');
    SearchTreeRemoveByLoop(&root,'c');
    SearchTreeRemoveByLoop(&root,'e');
    SearchTreeRemoveByLoop(&root,'f');
    SearchTreeInsert(&root,'g');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'f');
    SearchTreeRemoveByLoop(&root,'c');//测试d)ii)
    SearchTreePrint(root,"删除节点c的情况");
    

    SearchTreeRemoveByLoop(&root,'o');
    SearchTreePrint(root,"删除不存在的节点o");
}
//测试删除元素
void TestRemove()
{
    TEST_HANDLE;

    SearchTreeRemove(NULL,'a');//测试非法输入

    SearchTreeNode* root;
    SearchTreeInit(&root);

    SearchTreeRemove(&root,'a');//测试删除空树

    SearchTreeInsert(&root,'a');
    SearchTreeRemove(&root,'a');//测试a)i)
    SearchTreePrint(root,"删除只有一个根节点a的情况");

    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'c');
    SearchTreeRemove(&root,'a');//测试a)ii)1
    SearchTreePrint(root,"删除节点a的情况");

    SearchTreeInsert(&root,'a');
    SearchTreeRemove(&root,'c');//测试a)ii)2
    SearchTreePrint(root,"删除节点c的情况");

    SearchTreeRemove(&root,'b');//测试b)i)
    SearchTreePrint(root,"删除节点b的情况");

    SearchTreeRemove(&root,'a');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'a');
    SearchTreeRemove(&root,'b');//测试删除b)ii)1
    SearchTreePrint(root,"删除节点b的情况");
    
    SearchTreeRemove(&root,'a');
    SearchTreeRemove(&root,'c');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'d');
    SearchTreeRemove(&root,'e');//测试b)ii)2
    SearchTreePrint(root,"删除节点e的情况");

    SearchTreeRemove(&root,'c');
    SearchTreeRemove(&root,'d');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeRemove(&root,'a');//测试c)i)
    SearchTreePrint(root,"删除节点a的情况");
    
    SearchTreeRemove(&root,'b');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'c');
    SearchTreeRemove(&root,'b');//测试c)ii)1
    SearchTreePrint(root,"删除节点b的情况");
    
    SearchTreeRemove(&root,'d');
    SearchTreeRemove(&root,'c');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'c');
    SearchTreeRemove(&root,'b');//测试c)ii)2
    SearchTreePrint(root,"删除节点b的情况");

    SearchTreeRemove(&root,'a');
    SearchTreeRemove(&root,'c');
    SearchTreeInsert(&root,'g');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'f');
    SearchTreeRemove(&root,'d');//测试d)i)
    SearchTreePrint(root,"删除节点d的情况");

    SearchTreeRemove(&root,'g');
    SearchTreeRemove(&root,'c');
    SearchTreeRemove(&root,'e');
    SearchTreeRemove(&root,'f');
    SearchTreeInsert(&root,'g');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'f');
    SearchTreeRemove(&root,'c');//测试d)ii)
    SearchTreePrint(root,"删除节点c的情况");
    

    SearchTreeRemove(&root,'o');
    SearchTreePrint(root,"删除不存在的节点o");
}

//测试非递归插入
void TestInsertByLoop()
{
    TEST_HANDLE;
    
    SearchTreeInsertByLoop(NULL,'a');//测试非法输入

    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsertByLoop(&root,'a');//测试在空树中插入节点
    SearchTreeInsertByLoop(&root,'b');
    SearchTreeInsertByLoop(&root,'c');
    SearchTreeInsertByLoop(&root,'f');
    SearchTreeInsertByLoop(&root,'d');
    SearchTreeInsertByLoop(&root,'e');
    SearchTreeInsertByLoop(&root,'e');//测试插入已有的值

    SearchTreePrint(root,"打印搜索二叉树的先序和中序遍历");
    return;

}

//测试非递归查找
void TestFindByLoop()
{
    TEST_HANDLE;
    SearchTreeNode* root;
    SearchTreeInit(&root);

    SearchTreeNode* to_find;
    to_find = SearchTreeFindByLoop(root,'a');//测试在空树中查找
    printf("expect null,actually %p\n",to_find);

    SearchTreeInsertByLoop(&root,'a');
    SearchTreeInsertByLoop(&root,'b');
    SearchTreeInsertByLoop(&root,'c');
    SearchTreeInsertByLoop(&root,'f');
    SearchTreeInsertByLoop(&root,'d');
    SearchTreeInsertByLoop(&root,'e');

    to_find = SearchTreeFindByLoop(root,'a');//测试在非空树中查找存在的元素
    printf("expect %p,actually %p\n",root,to_find);
    printf("expect a,actually %c\n",to_find->data);

    to_find = SearchTreeFindByLoop(root,'g');//测试在非空树中查找不存在的元素
    printf("expect null,actually %p\n",to_find);

}

//测试根据一棵二叉搜索树在树组中查找元素
void TestFindInArray()
{
    TEST_HANDLE;
    SearchTreeType array[] = {'s','d','f','y','e'};
    
    int ret;

    ret = SearchNumInArray(NULL,0,'f');//测试非法输入
    printf("expect 0,actually %d\n",ret);

    size_t size = sizeof(array)/sizeof(array[0]);
    ret = SearchNumInArray(array,size,'e');//测试数组中存在的元素
    printf("expect 1,actually %d\n",ret);

    ret = SearchNumInArray(array,size,'t');//测试数组中不存在的元素
    printf("expect 0,actually %d\n",ret);

    return;

}

int main()
{
    TestInit();
    TestInsert();
    TestFind();
    TestRemove();
    TestRemoveByLoop();
    TestInsertByLoop();
    TestFindByLoop();
    TestFindInArray();
    return 0;
}
