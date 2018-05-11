#include<stdio.h>
#include"seqstack.h"

typedef struct QueueBy2Stack
{
    SeqStack input;//用于入队列的栈
    SeqStack output;//用于出队列的栈
}QueueBy2Stack;

//初始化
void QueueBy2StackInit(QueueBy2Stack* queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    InitSeqStack(&queue->input);
    InitSeqStack(&queue->output);
    return;
}

//入队列
void QueueBy2StackPush(QueueBy2Stack* queue,SeqStackType value)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }

    int ret;
    SeqStackType top;
    //将output中的所有元素入栈到input中，然后在对output出栈
    while(1)
    {
        ret = SeqStackTop(&queue->output,&top);
        if(ret == -1)
        {
            break;
        }
        SeqStackPush(&queue->input,top);
        SeqStackPop(&queue->output);
    }

    //对input进行入栈即入队列操作 
    SeqStackPush(&queue->input,value);
    return;
}


//出队列
void QueueBy2StackPop(QueueBy2Stack* queue)
{
    if(queue == NULL)
    {
        //非法输入 
        return;
    }
    if(queue->input.size == 0 && queue->output.size == 0)
    {
        //空队列
        return;
    }
    int ret;
    SeqStackType top;
    while(1)
    {
        ret = SeqStackTop(&queue->input,&top);
        if(ret == -1)
        {
            break;
        }
        SeqStackPush(&queue->output,top);
        SeqStackPop(&queue->input);
    }
    SeqStackPop(&queue->output);
}

//取栈顶元素
int QueueBy2StackTop(QueueBy2Stack* queue,SeqStackType* value)
{
    if(queue == NULL || value == NULL)
    {
        //非法输入
        return -1;
    }
    if(queue->input.size == 0 && queue->output.size == 0)
    {
        //空队列
        return -1;
    }
    int ret;
    SeqStackType top;
    while(1)
    {
        ret = SeqStackTop(&queue->input,&top);
        if(ret == -1)
        {
            break;
        }
        SeqStackPush(&queue->output,top);
        SeqStackPop(&queue->input);
    }
    SeqStackTop(&queue->output,value);
    return 0;
   // if(ret == -1)
   // {
   //     return -1;
   // }
   // else
   // {
   //     return 0;
   // }
}


void Test()
{
    QueueBy2Stack queue;
    QueueBy2StackInit(&queue);

    QueueBy2StackPush(&queue,'a');
    QueueBy2StackPush(&queue,'b');
    QueueBy2StackPush(&queue,'c');
    QueueBy2StackPush(&queue,'d');

    int ret;
    SeqStackType value;
    ret = QueueBy2StackTop(&queue,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect a,actually %c\n",value);
    QueueBy2StackPop(&queue);

    ret = QueueBy2StackTop(&queue,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect b,actually %c\n",value);
    QueueBy2StackPop(&queue);

    ret = QueueBy2StackTop(&queue,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect c,actually %c\n",value);
    QueueBy2StackPop(&queue);

    ret = QueueBy2StackTop(&queue,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect d,actually %c\n",value);
    QueueBy2StackPop(&queue);

    ret = QueueBy2StackTop(&queue,&value);
    printf("expect -1,actually %d\n",ret);
}

int main()
{
    Test();
    return 0;
}
