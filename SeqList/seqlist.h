#pragma once

#define SeqListMaxSize 1000//顺序表中数组的最大元素个数
typedef char SeqListType;//顺序表中数组数据的类型
typedef int(*Cmp)(SeqListType a,SeqListType b);

#include<stdio.h>

//定义顺序表的结构体数组
typedef struct SeqList
{
	SeqListType data[SeqListMaxSize];
	int size;//数组的实际长度
}SeqList;//将结构体重命名


//初始化顺序表
//顺序表为seqlist
void SeqListInit(SeqList *seqlist);


//向顺序表seqlist中尾插数据value
void SeqListPushBack(SeqList *seqlist,SeqListType value);


//在数据表seqlist中尾删数据value
void SeqListPopBack(SeqList *seqlist);

//向数据表seqlist中头插数据value
void SeqListPushFront(SeqList *seqlist,SeqListType value);


//从顺序表中seqlist头删数据value
void SeqListPopFront(SeqList *seqlist);

//在顺序表seqlist中任意位置插入元素value
//Pos是插入元素的位置下标
void SeqListInsert(SeqList *seqlist,int Pos,SeqListType value);

//在顺序表seqlist中任意位置读取数据
//Pos为读取元素的位置下标，读取的数据放入c中
void SeqListGet(SeqList *seqlist,int Pos,SeqListType *c);

//将顺序表seqlist中任意位置的元素修改为value
//Pos为修改位置的下标
void SeqListSet(SeqList *seqlist,int Pos,SeqListType value);

//在顺序表seqlist中查找指定元素value所在的下标
//将下标放在Pos中
void SeqListFind(SeqList *seqlist,SeqListType value,int *Pos);

//在顺序表seqlist的任意位置删除元素
//Pos为要删除元素所在的下标
void SeqListErase(SeqList *seqlist,int Pos);

//在顺序表seqlist中删除指定元素to_delete，如果有多个，只删除一个
void SeqListRemove(SeqList* seqlist, SeqListType to_delete); 


//在顺序表seqlist中删除指定的元素to_detele,如果有重复，就全部删除
void SeqListRemoveAll(SeqList* seqlist, SeqListType to_delete); 


//扩展优化：在顺序表seqlist中删除指定的元素to_detele,如果有重复，就全部删除
void SeqListRemoveAllEx(SeqList* seqlist, SeqListType to_delete); 

//返回顺序表seqlist中的元素个数
int SeqListSize(SeqList* seqlist);

//判断顺序表是否为空，为空，返回1，否则，返回0
int SeqListEmpty(SeqList* seqlist);

//冒泡排序顺序表seqlist
void SeqListBubbleSort(SeqList* seqlist);

//扩展冒泡排序顺序表seqlist
void SeqListBubbleSortEx(SeqList* seqlist,Cmp cmp);

//选择排序顺序表seqlist
void SeqListSelectSort(SeqList* seqlist,Cmp cmp);

