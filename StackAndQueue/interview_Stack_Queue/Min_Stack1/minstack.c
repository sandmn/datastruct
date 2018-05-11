

#include "seqstack.h"
#include<stdio.h>

//栈顶元素始终为最小值的栈结构定义
typedef struct MinStack
{
    SeqStack stack;
}MinStack;

//栈的初始化
void MinStackInit(MinStack* minstack)
{
    if(minstack == NULL)
    {
        //非法输入
        return;
    }
    InitSeqStack(&minstack->stack);
    return;
}

//入栈操作
void MinStackPush(MinStack* minstack,SeqStackType value)
{
    if(minstack == NULL)
    {
        //非法输入
        return;
    }

    SeqStackType min = value;

    SeqStackType top;
    int ret = SeqStackTop(&minstack->stack,&top);//取入栈前的栈顶元素即栈中最小值
    if(ret == 0 && top < value)//取原栈顶元素与要入栈的正常元素的最小值作为新的最小值即新的栈顶元素
    {
        min = top; 
    }
    SeqStackPush(&minstack->stack,value);//入栈正常元素
    SeqStackPush(&minstack->stack,min);//入栈新的最小值
}

//出栈操作
void MinStackPop(MinStack* minstack)
{
    if(minstack == NULL)
    {
        //非法输入
        return;
    }

    if(minstack->stack.size == 0)
    {
        //空栈
        return;
    }

    SeqStackPop(&minstack->stack);//出栈栈顶元素
    SeqStackPop(&minstack->stack);//出栈正常元素

    return;
}

//取栈顶元素
int MinStackTop(MinStack* minstack,SeqStackType* value)
{
    if(minstack == NULL || value == NULL)
    {
        //非法输入
        return -1;
    }

    if(minstack->stack.size == 0)
    {
        //空栈
        return -1;
    }

    return SeqStackTop(&minstack->stack,value);//取栈顶元素

    //int ret = SeqStackTop(&minstack->stack,value);//取栈顶元素
    //if(ret == -1)
    //{
    //    return -1;
    //}
    //else
    //{
    //    return 0;
    //}
}

void Test()
{
    MinStack minstack;
    MinStackInit(&minstack);

    MinStackPush(&minstack,'a');
    MinStackPush(&minstack,'b');
    MinStackPush(&minstack,'c');
    MinStackPush(&minstack,'d');

    int ret;
    SeqStackType value;
    ret = MinStackTop(&minstack,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect a,actually %c\n",value);
    MinStackPop(&minstack);

    ret = MinStackTop(&minstack,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect a,actually %c\n",value);
    MinStackPop(&minstack);

    ret = MinStackTop(&minstack,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect a,actually %c\n",value);
    MinStackPop(&minstack);

    ret = MinStackTop(&minstack,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect a,actually %c\n",value);
    MinStackPop(&minstack);

    ret = MinStackTop(&minstack,&value);
    printf("expect -1,actually %d\n",ret);
}

int main()
{
    Test();
    return 0;
}
