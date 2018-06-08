#pragma once

typedef char LinkListType;

//定义链表结点结构体
//每个链表节点包含一个数据元素data和指向下一个节点的指针next
typedef struct LinkListNode
{
	LinkListType data;
	struct LinkListNode* next;
}LinkListNode,*pLinkListNode;//将链表节点结构体重新命名

typedef struct LinkList
{
	pLinkListNode head;
}LinkList;
//复杂链表的结构题定义
typedef char ComplexType;
typedef struct ComplexNode
{
	ComplexType data;
	struct ComplexNode* next;
	struct ComplexNode* random;
}ComplexNode;

//初始化单链表，phead为头节点的指针即地址
void LinkListInit(LinkListNode** phead);

//在单链表phead中尾插一个元素value
void LinkListPushBack(LinkListNode** phead,LinkListType value);

//在单链表phead中尾删一个元素
void LinkListPopBack1(LinkListNode** phead);
void LinkListPopBack2(LinkListNode** phead);

//在单链表phead中头插一个元素value
void LinkListPushFront(LinkListNode** phead,LinkListType value);

//在单链表phead中头删一个元素
void LinkListPopFront(LinkListNode** phead);

// 查找元素在链表中的位置 
//to_find 要查找的值 
//return 这个值对应的节点的地址 
LinkListNode* LinkListFind(LinkListNode* head, LinkListType to_find); 

//在单链表phead的pos之前插入元素value
void LinkListInsert(LinkListNode** phead,LinkListNode* pos,LinkListType value);
void LinkListInsertEx(LinkListNode** phead,LinkListNode* pos,LinkListType value);

//在单链表phead的pos之后插入元素value
//void LinkListInsertAfter(LinkListNode** phead,LinkListNode* pos,LinkListType value);
void LinkListInsertAfter(LinkListNode* head,LinkListNode* pos,LinkListType value);

//删除指定位置pos处的元素
void LinkListErase(LinkListNode** phead, LinkListNode* pos); 

//删除指定位置的元素
void LinkListErase2(LinkListNode** phead, LinkListNode* pos); 

//删除指定值的元素
void LinkListRemove(LinkListNode** phead,LinkListType to_delete);

//删除指定值的所有元素
void LinkListRemoveAll(LinkListNode** phead,LinkListType to_delete);

//删除指定值的所有元素(优化)
void LinkListRemoveAllEx(LinkListNode** phead,LinkListType to_delete);

 //判定链表为空 
 //return 链表为空, 返回1, 否则返回0 
 int LinkListEmpty(LinkListNode* head); 

//求链表元素节点数
size_t LinkListSize(LinkListNode* head); 

//取最后一个节点的地址
LinkListNode* LinkListBack(LinkListNode* head);


//销毁链表
void LinkListDestory(LinkListNode** phead);

//逆序打印单链表
void LinkListReversePrint(LinkListNode* head);

//不允许遍历链表, 在 pos之前插入value
void LinkListInsertBefore(LinkListNode** phead, LinkListNode* pos, LinkListType value); 

//实现约瑟夫环
LinkListNode* JosephCircle(LinkListNode** phead,int m);

//逆置单链表1
void LinkListReverse(LinkListNode** phead);
//逆置单链表2
void LinkListReverse1(LinkListNode** phead);

//对单链表进行冒泡排序
void LinkListBubbleSort(LinkListNode* head);
//利用回调函数对单链表进行冒泡排序
void LinkListBubbleSort1(LinkListNode* head,int (*Cmp)(LinkListType,LinkListType));

//合并两个有序单链表使之继续有序
LinkListNode* LinkListMerge(LinkListNode* head1,LinkListNode* head2);

//方法1：先遍历链表求出节点的个数，在遍历寻找中间的节点
//方法二：查找中间节点，只遍历一次（利用快慢指针查找快指针每次走两步，慢指针每次走一步）
LinkListNode* LinkListFindMidNode(LinkListNode* head);

//方法1：先遍历链表求出及节点的个数size，在查找第size-k个节点
//方法2：查找倒数第k个节点，只遍历一次：快指针先走k步，然后快慢指针每次各走一步，快指针走完，慢指针的指向即为倒数第k个节点
LinkListNode* LinkListFindLastKNode(LinkListNode* head,int k);

//删除倒数第k个节点（相当于找到倒数第k+1个节点）
void LinkListEraseLastKNode(LinkListNode** phead,int k);

//判断链表是否带环
//方法1：附加一个顺序表存放各节点的地址
//方法2：定义快慢指针，快指针走两步，满指针走一步，当快慢指针可以相遇，说明有环
int LinkListHasCircle(LinkListNode* head);
//int LinkListHasCircle1(LinkListNode* head);

//求带环链表的环长:从相遇点开始，每走一步，计数器加1，直到再次回到相遇点即即为环长
size_t LinkListCircleLength(LinkListNode* head);

//求环的入口点
LinkListNode* LinkListCircleEntry(LinkListNode* head);

//判定链表是否相交(假设两链表不带环)
int LinkListHasCross(LinkListNode* head1,LinkListNode* head2);

//判相交，求交点(假设两链表不带环)
LinkListNode* LinkListCrossPos(LinkListNode* head1,LinkListNode* head2);

//判相交(两链表可能带环)
int LinkListHasCrossWithCircle(LinkListNode* head1,LinkListNode* head2);

//判相交，求交点(两链表可能带环)
LinkListNode* LinkListCrossPosWithCircle(LinkListNode* head1,LinkListNode* head2);

//求两排序链表中相同的数据(即求交集，若有多个相同元素，只取一个)
//对原链表会造成破坏，会造成内存泄漏,假定一个链表中没有重复的元素
LinkListNode* LinkListUnionSet(LinkListNode* head1,LinkListNode* head2);

//求两排序链表中相同的数据(即求交集，若有多个相同元素，只取一个)
//不破坏原链表，并且一个链表中允许有多个相同的元素
LinkListNode* LinkListUnionSetEx(LinkListNode* head1,LinkListNode* head2);

//若两链表无序，求两链表的交集
LinkListNode* LinkListUnionSetNoSort(LinkListNode* head1,LinkListNode* head2);

//复杂链表的复制(复杂)
ComplexNode* CopyComplexList(ComplexNode* head);

//复杂链表的复制(简单)
ComplexNode* CopyComplexListEx(ComplexNode* head);

//先打印倒数第k个节点之后的节点，在打印倒数第k个节点之前的节点
LinkListNode *rotateRight(LinkListNode *head,int k);

////////////////////////////
//头文件
//////////////////////////s
