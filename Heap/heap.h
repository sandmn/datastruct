#pragma once

#include<stddef.h>
//堆是一棵完全二叉树，所以可以用数组的方式来存储堆中的节点
//堆分为大跟堆和小跟堆
//大跟堆：任意一个树的根节点大于它的左右子树，所以大堆的根节点是树中的最大值
//小跟堆：任意一棵树的根节点小于它的左右子树，所以小堆的根节点是树中的最小值

typedef char HeapType;

#define MAXSIZE 100

typedef int (*Compare)(HeapType a,HeapType b);//定义一个函数指针用于表示是大堆还是小堆

typedef struct Heap
{
    HeapType data[MAXSIZE];
    size_t size;//堆中实际的节点个数
    Compare cmp;//该参数用于判断是大堆还是小堆
}Heap;

//堆的初始化:初始化时说明该堆是大堆还是小堆
void HeapInit(Heap* heap,Compare cmp);

//往堆中插入元素：因为堆是用数组进行存储的，所以利用尾插来实现
//堆在插入元素前后还应该是堆，即保持堆的性质
//根据数组实际最后元素的下标进行尾插已经保证了在插入后还是完全二叉树
//所以在插入元素后还需保证堆中任意树的根节点比它的左右子树大或小
void HeapInsert(Heap* heap,HeapType value);

//取堆顶元素
int HeapTop(Heap* heap,HeapType* top);

//删除堆顶元素：因为堆是用数组进行存储的，所以尾删比较方便
//但是首先要将堆顶元素放到数组的尾部在对其进行删除，尾删之后，堆还是一棵完全二叉树
//删除堆顶元素之后，要保证堆满足大堆或小堆的要求
//此时如果是大堆，堆顶元素可能比它下面的节点小，所以要进行下沉式调整
void HeapErase(Heap* heap);

//销毁堆
int HeapDestroy(Heap* heap);

//统计堆中元素个数
size_t HeapSize(Heap* heap);

//清空堆
void HeapEmpty(Heap* heap);

//根据堆对数组进行排序
void HeapSort(HeapType array[],size_t size,int sort_flag);
