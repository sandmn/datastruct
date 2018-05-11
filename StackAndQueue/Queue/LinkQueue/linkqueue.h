#pragma once

//用单链表实现链式队列
#include<stdlib.h>

typedef char LinkQueueType;

//定义链式队列的节点结构
typedef struct LinkQueueNode
{
    LinkQueueType data;//节点的数据域
    struct LinkQueueNode* next;//指向下一个节点的指针
}LinkQueueNode;

//定义链式队列
typedef struct LinkQueue
{
    LinkQueueNode* head;//指向链式队列的头节点
    LinkQueueNode* tail;//指向链式队列的尾指针
}LinkQueue;

//初始化链式队列
void LinkQueueInit(LinkQueue* queue);

//尾插入队列
void LinkQueuePush(LinkQueue* queue,LinkQueueType value);

//头删出队列
void LinkQueuePop(LinkQueue* queue);

//取队首元素:出错返回-1，成功返回0
int LinkQueueTop(LinkQueue queue,LinkQueueType* value);

//销毁队列
void LinkQueueDestory(LinkQueue* queue);
