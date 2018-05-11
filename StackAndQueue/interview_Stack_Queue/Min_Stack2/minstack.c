#include<stdio.h>
#include"seqstack.h"

typedef struct MinStack
{
   SeqStack norstack;//该栈用于存放正常出入栈的元素
   SeqStack topstack;//该栈栈顶永远为最小元素，两栈的元素一直相同
}MinStack;

//栈的初始化
void MinStackInit(MinStack* minstack)
{
    if(minstack == NULL)
    {
        //非法输入
        return;
    }

    InitSeqStack(&minstack->norstack);//初始化正常栈
    InitSeqStack(&minstack->topstack);//初始化保存最小值的栈
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

    SeqStackPush(&minstack->norstack,value);//对正常栈进行正常入栈
   
    SeqStackType top;
    SeqStackType min = value;
    int ret = SeqStackTop(&minstack->topstack,&top);//在最小栈中取栈顶元素
    if(ret == 0 && top < value)
    {
        min = top;
    }
    SeqStackPush(&minstack->topstack,min);
    return;
}

//出栈操作
void MinStackPop(MinStack* minstack)
{
    if(minstack == NULL)
    {
        //非法输入
        return;
    }
    if(minstack->norstack.size == 0)
    {
        //空栈
        return;
    }

    SeqStackPop(&minstack->norstack);
    SeqStackPop(&minstack->topstack);
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
    if(minstack->topstack.size == 0)
    {
        //空栈
        return -1;
    }

    return SeqStackTop(&minstack->topstack,value);
    //int ret = SeqStackTop(&minstack->topstack,value);
    //if(ret == 0)
    //{
    //    return 0;
    //}
    //else
    //{
    //    return -1;
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
