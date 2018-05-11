#pragma once

//用不带头节点不带环的单链表实现链栈
#include<stdlib.h>

typedef char LinkStackType;
//定义链栈的节点结构
typedef struct LinkStackNode
{
    LinkStackType data;
    struct LinkStackNode* next;
}LinkStackNode;

//初始化链栈
void LinkStackInit(LinkStackNode** pstack);

//头插入栈
void LinkStackPush(LinkStackNode** pstack,LinkStackType value);

//头删出栈
void LinkStackPop(LinkStackNode** pstack);

//取栈顶元素
int LinkStackTop(LinkStackNode* stack,LinkStackType* value);

//销毁链式栈
void LinkStackDestory(LinkStackNode** stack);
