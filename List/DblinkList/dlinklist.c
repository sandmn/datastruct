#include "dlinklist.h"

//创建结点
DlinkNode* CreateNode(DlinklistType value)
{
    DlinkNode* new_node = (DlinkNode*)malloc(sizeof(DlinkNode));
    new_node->data = value;
    new_node->next = new_node;//初始时，使节点的两个指针域均指向自身
    new_node->prev = new_node;
    return new_node;
}

//初始化双向链表
void InitDlinklist(DlinkNode** phead)
{
    if(phead == NULL)
    {
        //非法输入
        return;
    }
    //申请头结点,使头指针指向新节点
    *phead = CreateNode(0);
    return;
}


//对双向链表进行尾插
//head为双向链表的头指针，value为要插入的值
void DlinklistPushBack(DlinkNode* head,DlinklistType value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }

    DlinkNode* new_node = CreateNode(value);//创建新节点
    DlinkNode* tail = head->prev;//找到尾节点

    //一共要修改四个指针，两两一组进行修改
    //tail和new_node
    tail->next = new_node;
    new_node->prev = tail;

    //new_node和head
    head->prev = new_node;
    new_node->next = head;
    return;
}


//销毁节点
void DestoryNode(DlinkNode* node)
{
    free(node);
    return;
}

//对双向链表进行尾删
//head为双向链表的头指针
void DlinklistPopBack(DlinkNode* head)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    if(head->next == head)
    {
        //空链表
        return;
    }
    
    //根据头节点找到尾节点
    DlinkNode* to_delete = head->prev;
    //根据尾节点找到它的前一个节点
    DlinkNode* prev_node = to_delete->prev;
    //修改两个指针的指向，使上一个节点作为新的尾节点
    prev_node->next = head;
    head->prev = prev_node;
    //释放原来的尾节点
    DestoryNode(to_delete);
    return;
}


//头插
//head为双向链表的头指针，value为要插入的值
void DlinklistPushFront(DlinkNode* head,DlinklistType value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }

    //创建新节点
    DlinkNode* new_node = CreateNode(value);
    //找到第一个节点
    DlinkNode* next_node = head->next;

    //需要修改四个指针的指向
    //head和new_node
    head->next = new_node;
    new_node->prev = head;

    //new_node和next_node
    new_node->next = next_node;
    next_node->prev = new_node;
    return;
}

//头删，head为双向链表的头指针
void DlinklistPopFront(DlinkNode* head)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }

    if(head->next == head)
    {
        //空链表
        return;
    }
    //根据头节点找到要删除的第一个节点
    DlinkNode* to_delete = head->next;
    //根据要删除的节点找到他的下一个节点
    DlinkNode* next_node = to_delete->next;
    //只需改变两个指针，将下一个节点作为新的第一个节点
    head->next = next_node;
    next_node->prev = head;
    //释放要删除的节点
    DestoryNode(to_delete);
    return;
}

//在指定位置pos之前插入节点
void DlinklistInsert(DlinkNode* head,DlinkNode* pos,DlinklistType value)
{
    if(head == NULL || pos == NULL)
    {
        //非法输入
        return;
    }
    //根据pos找到他的前一个节点
    DlinkNode* prev_node = pos->prev;
    DlinkNode* new_node = CreateNode(value);//创建新节点

    //prev_node/new_node
    prev_node->next = new_node;
    new_node->prev = prev_node;

    //new_node/pos
    new_node->next = pos;
    pos->prev = new_node;
    return;
}
//在指定位置之后插入节点
void DlinklistInsertAfter(DlinkNode* head,DlinkNode* pos,DlinklistType value)
{
    if(head == NULL || pos == NULL)
    {
        //非法输入
        return;
    }

    //创建新节点
    DlinkNode* new_node = CreateNode(value);
   //根据pos找到他的下一个节点
    DlinkNode* next_node = pos->next;

    //pos/new_node
    pos->next = new_node;
    new_node->prev = pos;

    //new_node/next_node
    new_node->next = next_node;
    next_node->prev = new_node;
    return;
}

//查找指定值所在的位置
DlinkNode* DlinklistFind(DlinkNode* head,DlinklistType to_find)
{
    if(head == NULL)
    {
        //非法输入
        return NULL;
    }

    if(head->next == head)
    {
        //空链表
        return NULL;
    }
    //定义cur为当前指针遍历来遍历链表，初始从真正的第一个节点开始
    DlinkNode* cur = head->next;
    while(cur != head)//当未遍历完链表时
    {
        if(cur->data == to_find)//当找到指定值时
        {
            return cur;//返回指定值所在节点的位置
        }
        cur = cur->next;//若没找到，继续后移
    }
    return NULL;//遍历完链表还没找到
}
//删除指定位置的节点
void DlinklistErase(DlinkNode* head,DlinkNode* pos)
{
    if(head == NULL || pos == NULL)
    {
        //非法输入
        return;
    }
    if(head->next == head)
    {
        //空链表
        return;
    }

    if(head == pos)
    {
        //不能删除头节点
        return;
    }
    //找到指定位置处的下一个节点
    DlinkNode* next_node = pos->next;
    //找到指定位置处的上一个节点
    DlinkNode* prev_node = pos->prev;

    //修改相应指针的指向
    next_node->prev = prev_node;
    prev_node->next = next_node;
    //释放指定位置处的节点
    DestoryNode(pos);
    return;
}
//按值删除
void DlinklistRemove(DlinkNode* head,DlinklistType to_delete_value)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    if(head->next == head)
    {
        //空链表
        return;
    }

    //找到指定值所在的位置
    DlinkNode* to_delete =  DlinklistFind(head,to_delete_value);
    if(to_delete == NULL)
    {
        //没找到该节点
        return;
    }
    //根据指定位置删除节点
    DlinklistErase(head,to_delete);
    return;
}

//按值删除所有
void DlinklistRemoveAll(DlinkNode* head,DlinklistType to_delete_value)
{
    
    if(head == NULL)
    {
        //非法输入
        return;
    }
    
    if(head->next == head)
    {
        //空链表
        return;
    }
    //根据指定值找所在的位置
    DlinkNode* to_delete = DlinklistFind(head,to_delete_value);
    while(to_delete != NULL)//如果一直能找到指定值所在的位置
    {
        DlinklistErase(head,to_delete);//则对其进行删除
        to_delete = DlinklistFind(head,to_delete_value);
    }
    return;//此时，所有指定值所在的节点已全部删除
}
//销毁链表
void DestoryDlinklist(DlinkNode** phead)
{
    if(phead == NULL)
    {
        //非法输入
        return;
    }

    //遍历链表对各节点进行释放
    DlinkNode* to_delete = (*phead)->next;
    while(to_delete != *phead)
    {
        DlinkNode* next_node = to_delete->next;
        DestoryNode(to_delete);
        to_delete = next_node;
    }
    //释放头节点
    DestoryNode(*phead);
    //头指针置空
    *phead = NULL;

}
//统计双向链表的长度
int DlinklistSize(DlinkNode*head)
{
    if(head == NULL)
    {
        //非法输入
        return -1;
    }
    if(head->next == head)
    {
        //空链表
        return 0;
    }

    //从第一个节点开始遍历，遍历一个，长度加1，直到回到头节点
    DlinkNode* cur = head->next;
    int size = 0;
    while(cur != head)
    {
        size++;
        cur = cur->next;
    }
    return size;
}
///////////////////////////////////
//测试代码
//////////////////////////////////

#include<stdio.h>

#define TEST_HANDLE printf("======================%s==================\n",__FUNCTION__);

void DlinklistPrint(DlinkNode* head,const char* msg)
{
    if(head == NULL)
    {
        //非法输入
        return;
    }
    printf("%s\n",msg);
 
    //正向打印
    DlinkNode* cur = head->next;
    while(cur != head)
    {
        printf("%c ",cur->data);
        cur = cur->next;
    }
    printf("\n");

    //反向打印
    cur = head->prev;
    while(cur != head)
    {
        printf("%c ",cur->data);
        cur = cur->prev;
    }
    printf("\n");
    return;
    
}
//测试初始化函数
void TestInit()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    printf("expect 0,actually %d\n",(int)head->data);
    return;
}

//测试尾插函数
void TestPushBack()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    DlinklistPushBack(head,'a');
    DlinklistPushBack(head,'b');
    DlinklistPushBack(head,'c');
    DlinklistPushBack(head,'d');
    DlinklistPrint(head,"尾插四个节点");
    return;
}

//测试尾删
void TestPopBack()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    DlinklistPushBack(head,'a');
    DlinklistPushBack(head,'b');
    DlinklistPushBack(head,'c');
    DlinklistPushBack(head,'d');
    DlinklistPrint(head,"尾插四个节点");

    DlinklistPopBack(head);
    DlinklistPrint(head,"尾删一个元素");
    DlinklistPopBack(head);
    DlinklistPopBack(head);
    DlinklistPrint(head,"尾删两个元素");
    DlinklistPopBack(head);
    DlinklistPrint(head,"尾删一个元素");
    DlinklistPopBack(head);
    DlinklistPrint(head,"尾删空链表");
    return;

}

//测试头插
void TestPushFront()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);

    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'b');
    DlinklistPushFront(head,'c');
    DlinklistPushFront(head,'d');
    DlinklistPrint(head,"头插四个节点");
    return;
}

//测试头删
void TestPopFront()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);

    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'b');
    DlinklistPushFront(head,'c');
    DlinklistPushFront(head,'d');
    DlinklistPrint(head,"头插四个节点");

    DlinklistPopFront(head);
    DlinklistPrint(head,"头删一个元素");
    DlinklistPopFront(head);
    DlinklistPopFront(head);
    DlinklistPrint(head,"头删两个元素");
    DlinklistPopFront(head);
    DlinklistPrint(head,"头删一个元素");
    DlinklistPopFront(head);
    DlinklistPrint(head,"头删空链表");
    return;
}

//测试在指定位置之前插入
void TestInsert()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'b');
    DlinklistPushFront(head,'c');
    DlinklistPushFront(head,'d');
    DlinklistPrint(head,"头插四个节点");

    DlinklistInsert(head,head->next->next,'m');
    DlinklistPrint(head,"在c之前插入m");
    DlinklistInsert(head,head->next,'n');
    DlinklistPrint(head,"在d之前插入n");
    return;

}

//测试在任意位置之后插入节点
void TestInsertAfter()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'b');
    DlinklistPushFront(head,'c');
    DlinklistPushFront(head,'d');
    DlinklistPrint(head,"头插四个节点");

    DlinklistInsertAfter(head,head->next->next,'m');
    DlinklistPrint(head,"在c之后插入m");
    DlinklistInsertAfter(head,head->next,'n');
    DlinklistPrint(head,"在d之后插入n");
    return;

}

//测试指定值所在的位置
void TestFind()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    DlinkNode* ret = DlinklistFind(head,'a');
    printf("expect null,actually %p\n",ret);
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'b');
    DlinklistPushFront(head,'c');
    DlinklistPushFront(head,'d');
    DlinklistPrint(head,"头插四个节点");
    ret = DlinklistFind(head,'a');
    printf("expect %p,actually %p\n",head->next,ret);
    ret = DlinklistFind(head,'d');
    printf("expect %p,actually %p\n",head->prev,ret);
}

//测试删除指定位置处的值
void TestErase()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    DlinklistErase(head,head->next);
    DlinklistPrint(head,"尝试对空链表进行删除");
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'b');
    DlinklistPushFront(head,'c');
    DlinklistPushFront(head,'d');
    DlinklistPrint(head,"头插四个节点");
    DlinklistErase(head,head->next);
    DlinklistPrint(head,"删除d");
    DlinklistErase(head,head->prev);
    DlinklistPrint(head,"删除a");
    return;


}
//测试按值删除
void TestRemove()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    DlinklistRemove(head,'a');
    DlinklistPrint(head,"尝试对空链表进行删除");
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'b');
    DlinklistPushFront(head,'c');
    DlinklistPushFront(head,'d');
    DlinklistPrint(head,"头插四个节点");
    DlinklistRemove(head,'d');
    DlinklistPrint(head,"删除d");
    DlinklistRemove(head,'m');
    DlinklistPrint(head,"删除找不到的元素");
    return;


}

//测试按值删除所有
void TestRemoveAll()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    DlinklistRemoveAll(head,'a');
    DlinklistPrint(head,"尝试对空链表进行删除");
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'b');
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'d');
    DlinklistPrint(head,"头插四个节点");
    DlinklistRemoveAll(head,'a');
    DlinklistPrint(head,"删除a");
    DlinklistRemoveAll(head,'m');
    DlinklistPrint(head,"删除找不到的元素");
    return;

}
//测试销毁函数
void TestDestory()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'b');
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'d');
    DlinklistPrint(head,"头插四个节点");
    DestoryDlinklist(&head);
    printf("expect null,actually %p\n",head);
    return;
}

//测试长度函数
void TestSize()
{
    TEST_HANDLE;
    DlinkNode* head;
    InitDlinklist(&head);
    int size = DlinklistSize(head);
    printf("expect 0,actually %d\n",size);
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'b');
    DlinklistPushFront(head,'a');
    DlinklistPushFront(head,'d');
    DlinklistPrint(head,"头插四个节点");
    size = DlinklistSize(head);
    printf("expect 4,actually %d\n",size);
    return;

}
int main()
{

    TestInit();
    TestPushBack();
    TestPopBack();
    TestPushFront();
    TestPopFront();
    TestInsert();
    TestInsertAfter();
    TestFind();
    TestErase();
    TestRemove();
    TestRemoveAll();
    TestDestory();
    TestSize();
    return 0;
}


