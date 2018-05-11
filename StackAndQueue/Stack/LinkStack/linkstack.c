
//链式栈的基本操作
#include "linkstack.h"



//初始化链栈
void LinkStackInit(LinkStackNode** pstack)
{
    if(pstack == NULL)
    {
        //非法输入
        return;
    }
    *pstack = NULL;
}
//创建节点
LinkStackNode* CreateNode(LinkStackType value)
{
    LinkStackNode* new_node = (LinkStackNode*)malloc(sizeof(LinkStackNode));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

//头插入栈
void LinkStackPush(LinkStackNode** pstack,LinkStackType value)
{
    if(pstack == NULL)
    {
        //非法输入
        return;
    }

    //创建节点
    LinkStackNode* new_node = CreateNode(value);
   //将新节点的next指向原来的首原节点来做为新的首原节点
    new_node->next = *pstack;
    //使头指针指向新的首原节点
    *pstack = new_node;
    return;
}

//销毁节点
void DestoryNode(LinkStackNode* node)
{
    free(node);
}

//头删出栈
void LinkStackPop(LinkStackNode** pstack)
{
    if(pstack == NULL)
    {
        //非法输入
        return;
    }
    if(*pstack == NULL)
    {
        //空链栈
        return;
    }
    //保存要删除的首原节点
    LinkStackNode* to_delete = *pstack;
    //使头指针指向第二个节点
    *pstack = to_delete->next;
    //释放要删除的节点
    DestoryNode(to_delete);
    return;
}
//取栈顶元素
int LinkStackTop(LinkStackNode* stack,LinkStackType* value)
{
    if(stack == NULL)
    {
        //空链表
        return -1;
    }
    *value = stack->data;
    return 0;

}
//销毁链式栈
void LinkStackDetory(LinkStackNode** stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    //遍历链表各节点对其进行释放
    LinkStackNode* to_delete = *stack;
    while(to_delete != NULL)
    {
        LinkStackNode* next_node = to_delete->next;
        free(to_delete);
        to_delete = next_node;
    }
    //将头指针置空
    *stack = NULL;
    return;
}
///////////////////////////////
//测试函数
//////////////////////////////

#include<stdio.h>

#define TEST_HANDLE printf("================%s================\n",__FUNCTION__)

//测试初始化函数
void TestInit()
{
    TEST_HANDLE;
    LinkStackNode* stack;
    LinkStackInit(&stack);
    printf("expect null,actually %p\n",stack);
    return;
}

//输出函数
void LinkStackPrint(LinkStackNode* stack,const char* msg)
{
    printf("%s\n",msg);
    LinkStackNode* cur = stack;
    while(cur != NULL)
    {
        printf("%c ",cur->data);
        cur = cur->next;
    }
    printf("\n");
    return;
}

//测试头插入栈
void TestPush()
{
    TEST_HANDLE;
    LinkStackNode* stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack,'a');
    LinkStackPush(&stack,'b');
    LinkStackPush(&stack,'c');
    LinkStackPush(&stack,'d');

    LinkStackPrint(stack,"头插入栈四个元素");
    return;

}

//测试头删出栈
void TestPop()
{
    TEST_HANDLE;
    LinkStackNode* stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack,'a');
    LinkStackPush(&stack,'b');
    LinkStackPush(&stack,'c');
    LinkStackPush(&stack,'d');
    LinkStackPrint(stack,"头插入栈四个元素");
    
    LinkStackPop(&stack);
    LinkStackPop(&stack);
    LinkStackPrint(stack,"头删d,c");
    LinkStackPop(&stack);
    LinkStackPop(&stack);
    LinkStackPrint(stack,"头删d,a");
    LinkStackPop(&stack);
    LinkStackPrint(stack,"头删空链栈");
    return;

}

//测试取栈顶元素
void TestTop()
{
    TEST_HANDLE;
    LinkStackNode* stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack,'a');
    LinkStackPush(&stack,'b');
    LinkStackPush(&stack,'c');
    LinkStackPush(&stack,'d');
    LinkStackPrint(stack,"头插入栈四个元素");
    LinkStackType value;
    int ret = LinkStackTop(stack,&value);
    printf("expect 0,actualy %d\n",ret);
    printf("expect d,actually %c\n",value);
    
    LinkStackPop(&stack);
    LinkStackPop(&stack);
    LinkStackPrint(stack,"头删d,c");
    ret = LinkStackTop(stack,&value);
    printf("expect 0,actualy %d\n",ret);
    printf("expect b,actually %c\n",value);
   
    LinkStackPop(&stack);
    LinkStackPop(&stack);
    LinkStackPrint(stack,"头删d,a");
    ret = LinkStackTop(stack,&value);
    printf("expect -1,actualy %d\n",ret);
    return;

}

//测试销毁函数
void TestDestory()
{
    TEST_HANDLE;
    LinkStackNode* stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack,'a');
    LinkStackPush(&stack,'b');
    LinkStackPush(&stack,'c');
    LinkStackPush(&stack,'d');
    LinkStackPrint(stack,"头插入栈四个元素");

    LinkStackDestory(&stack);
    LinkStackPrint(stack,"销毁链式栈");

}
int main()
{
    TestInit();
    TestPush();
    TestPop();
    TestTop();
    TestDestory();
    return 0;
}
