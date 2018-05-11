
#include "linkqueue.h"

//初始化链式队列
void LinkQueueInit(LinkQueue* queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    queue->head = NULL;
    queue->tail = NULL;
}

//创建节点
LinkQueueNode* CreateNode(LinkQueueType value)
{
    LinkQueueNode* new_node = (LinkQueueNode*)\
                              malloc(sizeof(LinkQueueNode));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

//尾插入队列
void LinkQueuePush(LinkQueue* queue,LinkQueueType value)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    //创建一个新节点
    LinkQueueNode* new_node = CreateNode(value);
    //对新节点进行尾插
    if(queue->head == NULL)//如果原队列为空
    {
        queue->head = queue->tail = new_node;
    }
    else//如果原队列不为空
    {
        queue->tail->next = new_node;
        queue->tail = queue->tail->next;
    }
    return;

}

//销毁节点
void DestoryNode(LinkQueueNode* node)
{
    free(node);
}

//头删出队列
void LinkQueuePop(LinkQueue* queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    if(queue->head == NULL)
    {
        //空队列
        return;
    }
    //头删
    LinkQueueNode* to_delete = queue->head;//保存要销毁的队首节点
    queue->head = to_delete->next;//使队头指针指向要销毁节点的下一个节点
    DestoryNode(to_delete);//销毁原队首节点
    return;
}
//取队首元素:出错返回-1，成功返回0
int LinkQueueTop(LinkQueue queue,LinkQueueType* value)
{
    if(value == NULL)
    {
        //非法输入
        return -1;
    }
    if(queue.head == NULL)
    {
        //空队列
        return -1;
    }

    *value = queue.head->data;
    return 0;
}
//销毁队列
void LinkQueueDestory(LinkQueue* queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }

    //从队头开始遍历队列
    LinkQueueNode* to_delete = queue->head;
    while(to_delete != NULL)
    {
        LinkQueueNode* next_node = to_delete->next;//保存要销毁节点的下一个节点
        free(to_delete);//销毁节点
        to_delete = next_node;
    }
    //使队首指针，队尾指针置空
    queue->head = NULL;
    queue->tail = NULL;
    return;
}
/////////////////////////////
//测试函数
////////////////////////////

#include<stdio.h>

#define TEST_HANDLE printf("==================%s================\n",__FUNCTION__)

//测试初始化函数
void TestInit()
{
    TEST_HANDLE;
    LinkQueue queue;
    LinkQueueInit(&queue);

    printf("expect null,actually %p\n",queue.head);
    printf("expect null,actually %p\n",queue.tail);
    return;
}

//输出函数
void LinkQueuePrint(LinkQueue queue,const char* msg)
{
    printf("%s\n",msg);
    LinkQueueNode* cur = queue.head;
    while(cur != NULL)
    {
        printf("%c ",cur->data);
        cur = cur->next;
    }
    printf("\n");
    return;
}
//测试尾插
void TestPush()
{
    TEST_HANDLE;
    LinkQueue queue;
    LinkQueueInit(&queue);

    LinkQueuePush(&queue,'a');
    LinkQueuePush(&queue,'b');
    LinkQueuePush(&queue,'c');
    LinkQueuePush(&queue,'d');

    LinkQueuePrint(queue,"尾插四个元素");
    return;
}

//测试头删出队
void TestPop()
{
    TEST_HANDLE;
    LinkQueue queue;
    LinkQueueInit(&queue);

    LinkQueuePush(&queue,'a');
    LinkQueuePush(&queue,'b');
    LinkQueuePush(&queue,'c');
    LinkQueuePush(&queue,'d');
    LinkQueuePrint(queue,"尾插四个元素");

    LinkQueuePop(&queue);
    LinkQueuePrint(queue,"头删一个元素");
    LinkQueuePop(&queue);
    LinkQueuePop(&queue);
    LinkQueuePrint(queue,"头删两个元素");
    LinkQueuePop(&queue);
    LinkQueuePrint(queue,"头删一个元素");
    LinkQueuePop(&queue);
    LinkQueuePrint(queue,"头删空队列");
    return;

}

//测试取队首元素
void TestTop()
{
    TEST_HANDLE;
    LinkQueue queue;
    LinkQueueInit(&queue);

    LinkQueuePush(&queue,'a');
    LinkQueuePush(&queue,'b');
    LinkQueuePush(&queue,'c');
    LinkQueuePush(&queue,'d');
    LinkQueuePrint(queue,"尾插四个元素");
  
    LinkQueueType value;
    int ret = LinkQueueTop(queue,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect a,actually %c\n",value);

    LinkQueuePop(&queue);
    LinkQueuePrint(queue,"头删一个元素");
    ret = LinkQueueTop(queue,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect b,actually %c\n",value);

    LinkQueuePop(&queue);
    LinkQueuePop(&queue);
    LinkQueuePrint(queue,"头删两个元素");
    ret =  LinkQueueTop(queue,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect d,actually %c\n",value);
   
    LinkQueuePop(&queue);
    LinkQueuePrint(queue,"头删一个元素");
    ret = LinkQueueTop(queue,&value);
    printf("expect -1,actually %d\n",ret);
    return;

}

void TestDestory()
{
    TEST_HANDLE;
    LinkQueue queue;
    LinkQueueInit(&queue);

    LinkQueuePush(&queue,'a');
    LinkQueuePush(&queue,'b');
    LinkQueuePush(&queue,'c');
    LinkQueuePush(&queue,'d');
    LinkQueuePrint(queue,"尾插四个元素");

    LinkQueueDestory(&queue);
    LinkQueuePrint(queue,"销毁队列");
    return;

}

int main()
{
    TestInit();
    TestPush();
    TestPop();
    TestTop();
    TestDestory();
    return 0;
}
