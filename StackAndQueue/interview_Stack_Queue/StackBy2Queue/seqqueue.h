#pragma once

//实现可扩容的顺序队列
#include<stdlib.h>
#include<stdio.h>

typedef char SeqQueueType;

//顺序队列的结构
typedef struct SeqQueue
{
    SeqQueueType* data;//指向顺序队列的指针
    int size;//顺序队列的实际长度
    int capacity;//顺序队列的有效长度
    int head;//顺序队列的头节点所在的下标
    int tail;//顺序队列尾节点下个元素所在的下标,即[head,tail)
}SeqQueue;

//初始化顺序队列
void SeqQueueInit(SeqQueue* queue);

//入队,queue为顺序队列的指针
void SeqQueuePush(SeqQueue* queue,SeqQueueType value);

//出队
void SeqQueuePop(SeqQueue* queue);

//取队首元素:-1出错返回，0成功返回
int SeqQueueTop(SeqQueue* queue,SeqQueueType* value);

//销毁队列
void SeqQueueDestory(SeqQueue* queue);
