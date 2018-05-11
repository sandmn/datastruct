#include<stdio.h>
#include<string.h>
#include"seqstack.h"

//判断是否按照顺序出栈
int IsSeqPop(char src[],int size1,char dst[],int size2)
{
    if(src == NULL || dst == NULL)
    {
        //非法输入
        return -1;
    }
    if(size1 != size2)
    {
        //两串的长度不相同，一定不是按顺序出栈的
        return -1;
    }

    SeqStack stack;
    InitSeqStack(&stack);//每次要初始化栈
    int src_cur = 0;
    int dst_cur = 0;
    //1. 原串一个一个元素循环入栈
    while(src_cur != size1)//保证原串中所有元素最终均入栈
    {
        SeqStackPush(&stack,src[src_cur]);//入栈当前元素
        //2. 取栈顶元素与目标串当前位置元素进行比较
        SeqStackType top;
        int ret;
        while(dst_cur != size2)//保证目标串中所有元素均有对应的栈顶元素
        {
            ret = SeqStackTop(&stack,&top);//取栈顶元素
            if(ret == -1)//栈为空
            {
                break;//跳出循环后，继续入栈
            }
            //栈顶元素与目标串当前位置元素不相同，要对原串继续入栈
            if(top != dst[dst_cur])
            {
                break;
            }
            else// 栈顶元素域目标串当前元素相同
            {
                SeqStackPop(&stack);//出栈一个元素
                dst_cur++;//目标串当前位置后移，继续比较栈顶元素域目标串当前位置元素
            }
        }
        src_cur++;//原串后移，继续入栈
    }
    //5. 当原串所有元素均已入栈，此时目标串走到最后，并且栈为空时，表示按照顺序出栈
    if(dst_cur == size2 && stack.size == 0)
    {
        return 0;
    }
    //6. 当原串所有元素均已入栈
    //此时目标串未走到最后(目标串比原串长或不按顺序出栈)，或栈不为空时(不按顺序出栈或原串比目标串长)
    else
    {
        return -1;
    }
}
void Test()
{
    int ret;
    char src[] = "abcde";
    char dst[] = "abcde";
    ret = IsSeqPop(src,strlen(src),dst,strlen(dst));
    printf("expect 0,actually %d\n",ret);

    strcpy(dst,"cabed");
    ret = IsSeqPop(src,strlen(src),dst,strlen(dst));
    printf("expect -1,actually %d\n",ret);

    return;

}


//int StackOrder(char input[],size_t input_size,char output[],size_t output_size)
//{
//    size_t i = 0;
//    size_t output_index = 0;
//    SeqStack stack;
//    for(;i < input_size;++i)
//    {
//        SeqStackPush(&stack,input[i]);
//        char top;
//        int ret = SeqStackTop(&stack,&top);
//        if(ret == 0)
//        {
//            break;
//        }
//        while(1)
//        {
//            if(output_index >= output_size)
//            {
//                break;
//            }
//            if(top != output[output_index])
//            {
//                break;
//            }
//            ++output_index;
//            SeqStackPop(&stack);
//        }
//        if(stack.size == 0 && output_index == output_size)
//        {
//            return 1;
//        }
//        else
//        {
//            return 0;
//        }
//    }
//}
//
//void Test()
//{
//    int ret;
//    char src[] = "abcde";
//    char dst[] = "cabed";
//    ret = StackOrder(src,strlen(src),dst,strlen(dst));
//    printf("expect 0 ,actually %d\n",ret);
//
//
//    strcpy(dst, "abcde");
//    ret = StackOrder(src,strlen(src),dst,strlen(dst));
//    printf("expect 1 ,actually %d\n",ret);
//
////    char dst1[] = "abcde";
////    ret = StackOrder(src,strlen(src),dst1,strlen(dst1));
////    printf("expect 1 ,actually %d\n",ret);
////
//}


int main()
{
    Test();
    return 0;
}
