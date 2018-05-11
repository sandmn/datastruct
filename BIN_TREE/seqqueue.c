
#include "seqqueue.h"

//初始化顺序队列
void SeqQueueInit(SeqQueue* queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }

    queue->size = 0;//初始时队列为空
    queue->capacity =1000;//设置有效长度为1000
    queue->data = (SeqQueueType*)malloc(queue->capacity*sizeof(SeqQueueType));//动态申请内存,由data指向
    queue->head = 0;//初始时，队列为空
    queue->tail = 0;
}

//扩容函数
void Expanding(SeqQueue* queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    //重新设置新内存的有效长度
    queue->capacity = 2*(queue->capacity) + 1;
    //重新申请新的内存
    SeqQueueType* new_data = (SeqQueueType*)malloc(queue->capacity*sizeof(SeqQueueType));
    
    //将原内存中的数据复制到新内存中
    
    //如果尾节点在头节点之后
    int i;
    if(queue->head < queue->tail) //注意没有"="
    {
        i = queue->head;
        for(;i < queue->tail;++i)//按对应下标复制即可
        {
            new_data[i] = queue->data[i];
        }
    }
    else//如果尾节点在头节点之前
    {
        i = queue->head;
        //先拷贝队首到原capacity的数据
        for(;i < queue->size;++i)//此时size等于原capacity
        {
            new_data[i] = queue->data[i];
        }

        //在拷贝0到队尾的数据
        i = 0;
        for(;i < queue->tail;++i)
        {
            new_data[queue->size + i] = queue->data[i];
        }

        queue->tail = queue->head + queue->size;//修改扩容后的tail值
    }
    //释放原内存
    free(queue->data);
    //将队列结构中的data指针指向新内存
    queue->data = new_data;
    return;
}

//入队,queue为顺序队列的指针
void SeqQueuePush(SeqQueue* queue,SeqQueueType value)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }

    //原内存已满，需要扩容
    if(queue->size >= queue->capacity)
    {
        //扩容函数
        Expanding(queue);
    }
    //如果尾节点为数组最后一个元素，但是数组前面还有空余的地方
  
    //方法一
    // if(queue->tail%queue->capacity == 0)
    //方法二
    if(queue->tail == queue->capacity)
    {
        queue->tail = 0;
        queue->data[queue->tail++] = value;
        queue->size++;
        return;
    }
    //尾节点不为数组最后一个节点且数组还有空余的地方
    queue->data[queue->tail++] = value;
    queue->size++;
    return;
}

//出队
void SeqQueuePop(SeqQueue* queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    if(queue->size == 0)
    {
        //空队列
        return;
    }

    //如果出队元素为最大数组下标处的元素
    if(queue->head == queue->capacity - 1)
    {
        queue->head = 0;
        queue->size--;
    }
    else//如果不是最大数组下标处的元素
    {
        queue->head++;
        queue->size--;
    }
    return;
}

//取队首元素:-1出错返回，0成功返回
int SeqQueueTop(SeqQueue* queue,SeqQueueType* value)
{
    if(queue == NULL || value == NULL)
    {
        //非法输入
        return -1;
    }

    if(queue->size == 0)
    {
        //空队列
        return -1;
    }
    //取队首元素
    *value = queue->data[queue->head];
    return 0;
}
//销毁队列
void SeqQueueDestory(SeqQueue* queue)
{
    if(queue == NULL)
    {
        //非法输入
        return;
    }
    free(queue->data);
    queue->size = 0;
    queue->capacity = 0;
    queue->head = 0;
    queue->tail = 0;
    return;
}
/////////////////////////////////
//测试代码
////////////////////////////////

#if 0

#include<stdio.h>
#define TEST_HANDLE printf("=================%s==================\n",__FUNCTION__);

//测试初始化
void TestInit()
{
    TEST_HANDLE;
    SeqQueue queue;
    SeqQueueInit(&queue);

    printf("expect 0,actually %d\n",queue.size);
    printf("expect 0,actually %d\n",queue.head);
    printf("expect 0,actually %d\n",queue.tail);
    printf("expect 1000,actually %d\n",queue.capacity);

}

//输出函数
void SeqQueuePrint(SeqQueue* queue,const char* msg)
{
    printf("%s\n",msg);
    int i;
    if(queue->head < queue->tail) //注意没有"="
    {
        i = queue->head;
        for(;i < queue->tail;++i)
        {
            printf("%c ",queue->data[i]);
        }
    }
    else
    {
        i = queue->head;
        for(;i < queue->capacity;++i)
        {
            printf("%c ",queue->data[i]);
        }
        i = 0;
        for(;i < queue->tail;++i)
        {
            printf("%c ",queue->data[i]);
        }
    }
    printf("\n");
    return;
}

//测试入队函数
void TestPush()
{
    TEST_HANDLE;
    SeqQueue queue;
    SeqQueueInit(&queue);

    SeqQueuePush(&queue,'a');
    SeqQueuePush(&queue,'b');
    SeqQueuePush(&queue,'c');
    SeqQueuePush(&queue,'d');

    SeqQueuePrint(&queue,"入队四个元素");
    return;

}

//测试出队函数
void TestPop()
{
    TEST_HANDLE;
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,'a');
    SeqQueuePush(&queue,'b');
    SeqQueuePush(&queue,'c');
    SeqQueuePush(&queue,'d');
    SeqQueuePrint(&queue,"入队四个元素");

    SeqQueuePop(&queue);
    SeqQueuePrint(&queue,"出队一个元素");
    SeqQueuePop(&queue);
    SeqQueuePop(&queue);
    SeqQueuePrint(&queue,"出队两个元素");
    SeqQueuePop(&queue);
    SeqQueuePrint(&queue,"出队一个元素");
    SeqQueuePop(&queue);
    SeqQueuePrint(&queue,"出队空队列");
    return;
}

//测试取队首元素
void TestTop()
{
    TEST_HANDLE;
    SeqQueue queue;
    SeqQueueInit(&queue);
   
    SeqQueueType value;
    int ret = SeqQueueTop(&queue,&value);
    printf("expect -1,actually %d\n",ret);
    SeqQueuePush(&queue,'a');
    SeqQueuePush(&queue,'b');
    SeqQueuePush(&queue,'c');
    SeqQueuePush(&queue,'d');
    SeqQueuePrint(&queue,"入队四个元素");

    ret = SeqQueueTop(&queue,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect a,actually %c\n",value);
    return;
}

//测试销毁函数
void TestDestory()
{
    TEST_HANDLE;
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,'a');
    SeqQueuePush(&queue,'b');
    SeqQueuePush(&queue,'c');
    SeqQueuePush(&queue,'d');
    SeqQueuePrint(&queue,"入队四个元素");

    SeqQueueDestory(&queue);
    SeqQueuePrint(&queue,"销毁队列");
    return;
}

void Test()
{
    TEST_HANDLE;
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,'a');
    SeqQueuePush(&queue,'b');
    SeqQueuePush(&queue,'c');
    SeqQueuePush(&queue,'d');
    SeqQueuePrint(&queue,"入队四个元素");

    SeqQueuePop(&queue);
    SeqQueuePop(&queue);
    SeqQueuePrint(&queue,"出队两个元素");

    SeqQueuePush(&queue,'e');
    SeqQueuePrint(&queue,"再入队一个元素");

    SeqQueuePush(&queue,'f');
    SeqQueuePrint(&queue,"再入队一个元素");//测试在数组最大下标出入队

    SeqQueuePush(&queue,'g');
    SeqQueuePrint(&queue,"再入队一个元素");
    
    SeqQueuePush(&queue,'h');
    SeqQueuePrint(&queue,"再入队一个元素");//测试扩容后head在后的情况
    return;
    
}

//测试扩容后head在前的情况
void Test1()
{
    TEST_HANDLE;
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,'a');
    SeqQueuePush(&queue,'b');
    SeqQueuePush(&queue,'c');
    SeqQueuePush(&queue,'d');
    SeqQueuePush(&queue,'e');
    SeqQueuePrint(&queue,"入队五个元素");

    SeqQueuePush(&queue,'f');
    SeqQueuePrint(&queue,"再入队一个元素");
    return;
}

//测试最大数组下处出队
void Test2()
{
    TEST_HANDLE;
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,'a');
    SeqQueuePush(&queue,'b');
    SeqQueuePush(&queue,'c');
    SeqQueuePush(&queue,'d');
    SeqQueuePush(&queue,'e');
    SeqQueuePrint(&queue,"入队五个元素");

    SeqQueuePop(&queue);
    SeqQueuePop(&queue);
    SeqQueuePop(&queue);
    SeqQueuePop(&queue);
    SeqQueuePrint(&queue,"出队四个元素");

    SeqQueuePush(&queue,'f');
    SeqQueuePush(&queue,'g');
    SeqQueuePrint(&queue,"入队两个元素");

    SeqQueuePop(&queue);
    SeqQueuePrint(&queue,"出队一个元素");

    return;

}


int main()
{
    TestInit();
    TestPush();
    TestPop();
    TestTop();
    TestDestory();
    Test();
    Test1();
    Test2();
    return 0;
}
#endif
