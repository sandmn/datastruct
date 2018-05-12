
#include "seqstack.h"

//初始化顺序栈，stack为顺序栈的的指针
void InitSeqStack(SeqStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }

    stack->size = 0;//初始时实际长度为0
    stack->capacity = 1000;//初始使顺序栈的长度设置为1000
    //size已经表示哪部分内容有效，所以不需要对申请的内存进行初始化
    stack->data = (SeqStackType*)malloc(sizeof(SeqStackType)*(stack->capacity));//为顺序栈申请动态内存
}
//销毁顺序栈
void Destory(SeqStack* stack)
{
    stack->size = 0;
    stack->capacity = 0;
    free(stack->data);
    return;
}

//尾插入栈
void SeqStackPush(SeqStack* stack,SeqStackType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size >= stack->capacity)
    {
        //初始的顺序栈已满,此时需要扩容
        stack->capacity = stack->capacity*2 + 1;
        //申请扩容后的动态内存
        SeqStackType* new_data = (SeqStackType*)malloc(sizeof(SeqStackType)*(stack->capacity));
        //将原内存中的内容拷贝到新内存中
        //方法一
       // memcpy(new_data,stack->data,sizeof(SeqStackType)*(stack->capacity));
       //方法二
        int i = 0;
        for(;i < stack->size;i++)
        {
            new_data[i] = stack->data[i];
        }

        //释放原顺序栈中的内存
        free(stack->data);
        //将扩容后的内存保存在顺序栈的结构中
        stack->data = new_data;
    }
    //尾插入栈
    stack->data[stack->size++] = value; 
    return;
}

//尾删出栈
void SeqStackPop(SeqStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->size == 0)
    {
        //空顺序栈
        return;
    }
    //将尾元素设置为无效元素即可
    --stack->size;
}

//取栈顶元素,返回值：-1代表出错返回，0代表成功返回
int SeqStackTop(SeqStack* stack,SeqStackType* value)
{
    if(stack == NULL || value == NULL) 
    {
        //非法输入
        return -1;
    }

    if(stack->size == 0)
    {
        //空顺序栈
        return -1;
    }

    *value = stack->data[stack->size - 1];
    return 0;
}

///////////////////////////////////
//以下为测试代码
//////////////////////////////////

#if 0
#include<stdio.h>

#define TEST_HANDLE printf("====================%s=====================\n",__FUNCTION__)

//测试初始化顺序栈函数
void TestInit()
{
    TEST_HANDLE;
    SeqStack stack;//定义一个顺序栈
    InitSeqStack(&stack);//初始化顺序栈

    printf("expect 0,actually %d\n",stack.size);
    printf("expect 1000,actually %d\n",stack.capacity);
    return;
}

//输出函数
void SeqStackPrint(SeqStack* stack,const char* msg)
{
    printf("%s\n",msg);
    int i = 0;
    for(;i < stack->size;++i)
    {
        printf("%c ",stack->data[i]);
    }
    printf("\n");
    return;
}

//测试尾插入栈函数
void TestPush()
{
    TEST_HANDLE;
    SeqStack stack;
    InitSeqStack(&stack);
    
    SeqStackPush(&stack,'a');
    SeqStackPush(&stack,'b');
    SeqStackPush(&stack,'c');
    SeqStackPush(&stack,'d');

    SeqStackPrint(&stack,"尾插入栈四个元素");

    SeqStackPush(&stack,'e');
    SeqStackPush(&stack,'f');
    SeqStackPrint(&stack,"对扩容后的顺序栈在尾插两个元素");
    return;
}

//测试尾删出栈
void TestPop()
{
    TEST_HANDLE;
    SeqStack stack;
    InitSeqStack(&stack);
    
    SeqStackPush(&stack,'a');
    SeqStackPush(&stack,'b');
    SeqStackPush(&stack,'c');
    SeqStackPush(&stack,'d');
    SeqStackPrint(&stack,"尾插入栈四个元素");

    SeqStackPop(&stack);
    SeqStackPop(&stack);
    SeqStackPrint(&stack,"尾删出栈两个元素");
    SeqStackPop(&stack);
    SeqStackPop(&stack);
    SeqStackPrint(&stack,"再尾删出栈两个元素");
    SeqStackPop(&stack);
    SeqStackPrint(&stack,"对空顺序栈进行尾删");
    return;

}

//测试取栈顶元素函数
void TestTop()
{
    TEST_HANDLE;
    SeqStack stack;
    InitSeqStack(&stack);

    SeqStackType value;
    int ret = SeqStackTop(&stack,&value);
    printf("expect -1,actually %d\n",ret);
    
    SeqStackPush(&stack,'a');
    SeqStackPush(&stack,'b');
    SeqStackPush(&stack,'c');
    SeqStackPush(&stack,'d');
    SeqStackPrint(&stack,"尾插入栈四个元素");
    ret = SeqStackTop(&stack,&value);
    printf("expect 0,actually %d\n",ret);
    printf("expect d,actually %c\n",value);
    return;
}

int main()
{
    TestInit();
    TestPush();
    TestPop();
    TestTop();
    return 0;
}

#endif
