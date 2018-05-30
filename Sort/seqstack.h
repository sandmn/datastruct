#pragma once

//实现可扩容的顺序栈
#include<stdlib.h>
#include<string.h>

//typedef char SeqStackType;

typedef int SeqStackType;

//定义顺序栈的结构
typedef struct SeqStack
{
    SeqStackType* data;//动态申请顺序栈的内存空间
    int size;//顺序栈的实际长度
    int capacity;//顺序栈的最大长度
}SeqStack;

//销毁顺序栈
void Destory(SeqStack* stack);
//初始化顺序栈，stack为顺序栈的的指针
void InitSeqStack(SeqStack* stack);

//尾插入栈
void SeqStackPush(SeqStack* stack,SeqStackType value);

//尾删出栈
void SeqStackPop(SeqStack* stack);

//取栈顶元素,-1代表出错返回，0代表成功返回
int SeqStackTop(SeqStack* stack,SeqStackType* value);
