#pragma once

#include<stdlib.h>
//双向，带头节点的带环链表
typedef char DlinklistType;//将节点的数据域类型统一表示

//定义双向链表的节点结构
typedef struct DlinkNode
{
    DlinklistType data;//数据域
    struct DlinkNode* next;//指向下一个节点
    struct DlinkNode* prev;//指向上一个节点
}DlinkNode;

//初始化双向链表
void InitDlinklist(DlinkNode** phead);

//对双向链表进行尾插
//head为双向链表的头指针，value为要插入的值
void DlinklistPushBack(DlinkNode* head,DlinklistType value);

//对双向链表进行尾删
//head为双向链表的头指针
void DlinklistPopBack(DlinkNode* head);


//头插
//head为双向链表的头指针，value为要插入的值
void DlinklistPushFront(DlinkNode* head,DlinklistType value);

//头删，head为双向链表的头指针
void DlinklistPopFront(DlinkNode* head);

//在指定位置pos之前插入节点
void DlinklistInsert(DlinkNode* head,DlinkNode* pos,DlinklistType value);

//在指定位置之后插入节点
void DlinklistInsertAfter(DlinkNode* head,DlinkNode* pos,DlinklistType value);

//查找指定值所在的位置
DlinkNode* DlinklistFind(DlinkNode* head,DlinklistType to_find);

//删除指定位置的节点
void DlinklistErase(DlinkNode* head,DlinkNode* pos);

//按值删除
void DlinklistRemove(DlinkNode* head,DlinklistType to_delete_value);

//按值删除所有
void DlinklistRemoveAll(DlinkNode* head,DlinklistType to_delete_value);

//销毁链表
void DestoryDlinklist(DlinkNode** phead);

//统计双向链表的长度
int DlinklistSize(DlinkNode*head);
