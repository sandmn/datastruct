
//利用一个数组实现共享栈
#include<stdio.h>

#define MAX_SIZE 8//定义数组的最大长度
typedef char ShareStackType;//数组中元素类型

//规定栈1：[0,top1)
//规定栈2：[top2,MAX_SIZE)
//栈1为空时:[0,0)
//栈2为空时：[MAX_SIZE,MAX_SIZE);

//共享栈的结构
typedef struct ShareStack
{
    ShareStackType data[MAX_SIZE]; //数组
    int top1;//栈1的栈定元素
    int top2;//栈2的栈顶元素
}ShareStack;

//共享栈的初始化
void ShareStackInit(ShareStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    stack->top1 = 0;
    stack->top2 = MAX_SIZE;
    return;
}

//栈1入栈
void ShareStackPush1(ShareStack* stack,ShareStackType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    //数组判满
    if(stack->top1 == stack->top2)
    {
        //此时数组已满，无法入栈
        return;
    }
    stack->data[stack->top1++] = value;
    return;
}

//栈2入栈
void ShareStackPush2(ShareStack* stack,ShareStackType value)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->top1 == stack->top2)
    {
        //此时数组已满
        return;
    }
    stack->data[--stack->top2] = value;
    return;
}

//栈1出栈
void ShareStackPop1(ShareStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->top1 == 0)
    {
        //栈1为空
        return;
    }
    --stack->top1;
    return;
}

//栈2出栈
void ShareStackPop2(ShareStack* stack)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    if(stack->top2 == MAX_SIZE)
    {
        //栈2为空时
        return;
    }
    ++stack->top2;
    return;
}

//栈1取栈顶元素
int ShareStackTop1(ShareStack* stack,ShareStackType* value)
{
    if(stack == NULL)
    {
        //非法输入
        return -1;
    }
    if(stack->top1 == 0)
    {
        //栈1为空时
        return -1;
    }

    *value = stack->data[stack->top1 - 1];
    return 0;
}

//栈2取栈顶元素
int ShareStackTop2(ShareStack* stack,ShareStackType* value)
{
    if(stack == NULL)
    {
        //非法输入
        return -1;
    }
    if(stack->top2 == MAX_SIZE)
    {
        //栈2为空
        return -1;
    }
    *value = stack->data[stack->top2];
    return 0;
}

/////////////////////////////////
//测试代码
/////////////////////////////////

#define HANDLE_TEST printf("=================%s=================\n",__FUNCTION__)

void Test()
{
    HANDLE_TEST;
    ShareStack stack;
    ShareStackInit(&stack);
    printf("top1 expect 0,actually %d\n",stack.top1);
    printf("top2 expect 8,actually %d\n",stack.top2);


    ShareStackPush1(&stack,'a');
    ShareStackPush1(&stack,'b');
    ShareStackPush1(&stack,'c');
    ShareStackPush1(&stack,'d');

    ShareStackPush2(&stack,'e');
    ShareStackPush2(&stack,'f');
    ShareStackPush2(&stack,'g');
    ShareStackPush2(&stack,'h');
    int ret1;
    ShareStackType value1;
    int ret2;
    ShareStackType value2;

    ShareStackPush1(&stack,'m');//数组已满时对栈1进行入栈
    ret1 = ShareStackTop1(&stack,&value1);
    printf("expect 0,actually %d\n",ret1);
    printf("expect d,actually %c\n",value1);

    ShareStackPush2(&stack,'n');//数组已满时对栈2进行入栈
    ret2 = ShareStackTop2(&stack,&value2);
    printf("expect 0,actually %d\n",ret2);
    printf("expect h,actually %c\n",value2);



    ret1 = ShareStackTop1(&stack,&value1);
    printf("expect 0,actually %d\n",ret1);
    printf("expect d,actually %c\n",value1);
    ShareStackPop1(&stack);

    ret1 = ShareStackTop1(&stack,&value1);
    printf("expect 0,actually %d\n",ret1);
    printf("expect c,actually %c\n",value1);
    ShareStackPop1(&stack);

    ret1 = ShareStackTop1(&stack,&value1);
    printf("expect 0,actually %d\n",ret1);
    printf("expect b,actually %c\n",value1);
    ShareStackPop1(&stack);

    ret1 = ShareStackTop1(&stack,&value1);
    printf("expect 0,actually %d\n",ret1);
    printf("expect a,actually %c\n",value1);
    ShareStackPop1(&stack);

    ret1 = ShareStackTop1(&stack,&value1);//取空栈1的栈顶元素
    printf("expect -1,actually %d\n",ret1);


    ret2 = ShareStackTop2(&stack,&value2);
    printf("expect 0,actually %d\n",ret2);
    printf("expect h,actually %c\n",value2);
    ShareStackPop2(&stack);

    ret2 = ShareStackTop2(&stack,&value2);
    printf("expect 0,actually %d\n",ret2);
    printf("expect g,actually %c\n",value2);
    ShareStackPop2(&stack);

    ret2 = ShareStackTop2(&stack,&value2);
    printf("expect 0,actually %d\n",ret2);
    printf("expect f,actually %c\n",value2);
    ShareStackPop2(&stack);

    ret2 = ShareStackTop2(&stack,&value2);
    printf("expect 0,actually %d\n",ret2);
    printf("expect e,actually %c\n",value2);
    ShareStackPop2(&stack);

    ret2 = ShareStackTop2(&stack,&value2);//取空栈2的栈顶元素
    printf("expect -1,actually %d\n",ret2);
}


int main()
{
    Test();
    return 0;
}


