#include<stdio.h>
#include"seqqueue.h"

typedef struct StackBy2Queue
{
    SeqQueue queue1;
    SeqQueue queue2;
}StackBy2Queue;

//栈的初始化
void StackBy2QueueInit(StackBy2Queue* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }

    SeqQueueInit(&stack->queue1);
    SeqQueueInit(&stack->queue2);
    return;
}

//入栈
void StackBy2QueuePush(StackBy2Queue* stack,SeqQueueType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }

    SeqQueue* input;
    //queue2非空
    if(stack->queue1.size == 0)
    {
        input = &stack->queue2;
    }
    else//queue1非空
    {
        input = &stack->queue1;
    }
    //对非空队列入队
    SeqQueuePush(input,value);
    return;
}

//出栈
void StackBy2QueuePop(StackBy2Queue* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }

    if(stack->queue1.size == 0 && stack->queue2.size == 0)
    {
        //空栈
        return;
    }
    SeqQueue* from = NULL;//from为要出队的队列,此时from非空
    SeqQueue* to = NULL;//to为要入队的队列，此时to为空
    if(stack->queue1.size == 0)
    {
        to = &stack->queue1;
        from = &stack->queue2;
    }
    else
    {
        to = &stack->queue2;
        from = &stack->queue1;
    }

    SeqQueueType top;
    //将from中的元素入队到to中，只剩下一个元素为止
    while(1)
    {
        if(from->size == 1)
        {
            break;
        }
        SeqQueueTop(from,&top);
        SeqQueuePush(to,top);
        SeqQueuePop(from);
    }
    //将剩余的最后一个元素出队
    SeqQueuePop(from);
    return;
}


//取栈顶元素
int StackBy2QueueTop(StackBy2Queue* stack,SeqQueueType* value)
{
    if(stack == NULL || value == NULL)
    {
        //非法输入
        return -1;
    }


    if(stack->queue1.size == 0 && stack->queue2.size == 0)
    {
        //空栈
        return -1;
    }

    int ret;
    SeqQueueType top;
    SeqQueue* to;
    SeqQueue* from;
    if(stack->queue1.size != 0)
    {
        from = &stack->queue1;
        to = &stack->queue2;
    }
    else
    {
        from = &stack->queue2;
        to = &stack->queue1;
    }
    while(1)
    {
        ret = SeqQueueTop(from,value);
        if(ret == -1)
        {
            break;
        }
        SeqQueuePop(from);
        SeqQueuePush(to,*value);
    }
    return 0;
}


void Test()
{
    StackBy2Queue stack;
    StackBy2QueueInit(&stack);

    StackBy2QueuePush(&stack,'a');
    StackBy2QueuePush(&stack,'b');
    StackBy2QueuePush(&stack,'c');
    StackBy2QueuePush(&stack,'d');

    int ret;
    SeqQueueType value;
    ret = StackBy2QueueTop(&stack,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect d,actually %c\n",value);
    StackBy2QueuePop(&stack);
    
    ret = StackBy2QueueTop(&stack,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect c,actually %c\n",value);
    StackBy2QueuePop(&stack);

    ret = StackBy2QueueTop(&stack,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect b,actually %c\n",value);
    StackBy2QueuePop(&stack);

    ret = StackBy2QueueTop(&stack,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect a,actually %c\n",value);
    StackBy2QueuePop(&stack);

    ret = StackBy2QueueTop(&stack,&value);
    printf("expect -1,actually %d\n",ret);
}
int main()
{
    Test();
    return 0;
}
