
#include<stdio.h>
#include<stdlib.h>
#include"linklist.h"
#include"seqstack.c"

//void LinkListInit1(LinkList* linklist)
//{
//	if(linklist == NULL)
//	{
//		return;
//	}
//	linklist->head = NULL;
//	return;
//}

void LinkListInit(LinkListNode** phead)
{
	if(phead == NULL)
	{
		//非法输入
		return;
	}

	*phead = NULL;
	return;
}

//int CreateNode(LinkListNode** phead,LinkListType value)
//{
//	*phead = (LinkListNode*)malloc(sizeof(LinkListNode));
//	if(*phead == NULL)
//	{
//		//malloc错误
//		return 1;
//	}
//	(*phead)->data = value;
//	(*phead)->next = NULL;
//	return 0;
//
//
//}
//

//创建新节点，value是新节点的数据域
LinkListNode* CreateNode(LinkListType value)
{
	LinkListNode* new_node = (LinkListNode*)malloc(sizeof(LinkListNode));//动态申请节点
	new_node->data = value;//使新节点的数据域为value
	new_node->next = NULL;//指针域置为空
	return new_node;//如果申请成功，返回新节点的地址，如果失败，返回NULL
}
//在单链表尾部插入一个新节点，节点的数据为value
void LinkListPushBack(LinkListNode** phead,LinkListType value)
{
	if(phead == NULL)
	{
		//非法输入,对空指针解引用程序会异常终止，所以这里需要判断一下
		return;
	}

	if(*phead == NULL)
	{
		//空链表,需改变头指针的指向
		*phead = CreateNode(value);
		return;
	}
	
	//链表非空
	LinkListNode* cur = *phead;//定义cur为当前节点的指针，初始为头节点的指针即头指针	
	while(cur->next != NULL)//遍历寻找最后一个节点
	{
		cur = cur->next;
	}
	//此时，cur为最后一个节点，所以新节点只需插入在cur之后即可
	cur->next = CreateNode(value);
	return;
}
//销毁单链表中的一个节点node
//这里，封装为函数，可以提高代码的维护性
void LinkListNodeDestory(LinkListNode* node)
{
	free(node);//free释放节点
}
//在单链表尾部删除一个节点（不创建新结点）
void LinkListPopBack1(LinkListNode** phead)
{
	if(phead == NULL)
	{
		//非法输入
		return;
	}
	if(*phead == NULL)
	{
		//空链表
		return;
	}

	if((*phead)->next == NULL)
	{
		//只有一个节点，删除后需要改变头指针的指向
		LinkListNodeDestory(*phead);//销毁头节点*phead
		*phead = NULL;//再使头指针置为空
		return;
	}
	
	LinkListNode* cur = *phead;//定义当前节点指针cur
		while(cur->next->next != NULL)//遍历查找倒数第二个节点
		{
			cur = cur->next;
		}
		//此时，cur为倒数第二个节点
		LinkListNode* to_delete = cur->next; 
		cur->next = NULL;//将倒数第二个节点的next域置为空
		LinkListNodeDestory(to_delete);//销毁最后一个节点to_delete
		return;
	}

	//创建新节点来尾删
	void LinkListPopBack2(LinkListNode** phead)
	{
		if(phead == NULL)
		{
			//非法输入
			return;
		}
		if(*phead == NULL)
		{
			//空链表
			return;
		}
		if((*phead)->next == NULL)
		{
			//链表中只有一个节点，此时，需要改变头指针的指向
			LinkListNodeDestory(*phead);//销毁头节点*phead
			*phead = NULL;
			return;
		}

		LinkListNode* cur = (*phead)->next;//定义当前节点查找最后一个节点
		LinkListNode* pre = *phead;//定义当前节点的前一个节点
		while(cur->next != NULL)
		{
			pre = cur;//当前节点不是最后一个节点，就使前一个节点先指向当前节点
			cur = cur->next;//当前节点在后移
		}
		//当前节点cur是最后一个节点
		pre->next = NULL;//使倒数第二个节点的next域置为空
		LinkListNodeDestory(cur);//销毁最后一个节点
		return;
	}

	//头插节点,新节点的数据域为value
	void LinkListPushFront(LinkListNode** phead,LinkListType value)
	{
		if(phead == NULL)
		{
			//非法输入
			return;
		}
		
		LinkListNode* new_node = CreateNode(value);//创建新节点
		new_node->next = *phead;//使新节点的next域指向原来的头节点，如果链表初始为空，即指向NULL
		*phead = new_node;//再使头指针指向新节点
		//if(*phead == NULL)
		//{
		//	//空链表，此时需要改变头指针的值
		//	*phead = CreateNode(value);
		//	return;
		//}
		////不是空链表时
		//LinkListNode* tmp = *phead;
		//*phead = CreateNode(value);
		//(*phead)->next = tmp;
		return;
	}

	//头删节点
	void LinkListPopFront(LinkListNode** phead)
	{
		if(phead == NULL)
		{
			//非法输入
			return;
		}

		if(*phead == NULL)
		{
			//空链表
			return;
		}

	//	if((*phead)->next == NULL)
	//	{
	//		//只有一个节点，此时需要对头指针进行修改
	//		LinkListNodeDestory(*phead);//释放头节点
	//		*phead = NULL;//使头指针置为空
	//		return;
	//	}

		//链表中有多个节点的情形
		LinkListNode* tmp = (*phead)->next;//保存第二个节点的地址,如果链表中只有一个节点，则此时tmp即为NULL
		LinkListNodeDestory(*phead);//销毁第一个节点
		*phead = tmp;//使头指针指向第二个节点
	}

	//查找指定元素to_find所在的地址,如果没找到，返回NULL
	LinkListNode* LinkListFind(LinkListNode* head, LinkListType to_find)
	{
		if(head == NULL)
		{
			//链表为空，找不到指定元素
			return NULL;//直接返回NULL即可
		}
		//设置cur为当前指针，初始指向头节点
		LinkListNode* cur = head;
		//遍历链表寻找要查找的元素
		while(cur != NULL)
		{
			if(cur->data == to_find)
			{
				return cur;//当找到要查找的元素，返回该元素的地址
			}
			cur = cur->next;//指针后移，继续往后遍历
		}
		return NULL;//链表遍历完，还没有找到，说明要查找的元素不再该链表中，返回NULL

	}
	////在单链表任意位置pos之后插入节点value
	//void LinkListInsertAfter(LinkListNode** phead,LinkListNode* pos,LinkListType value)
	//{
	//	if(phead == NULL || pos == NULL)
	//	{
	//		//非法输入
	//		return;
	//	}
	//
	//	if(*phead == NULL)
	//	{
	//		//空链表
	//		return;
	//	}
	//
	//	LinkListNode* cur = *phead;
	//	while(cur != NULL)
	//	{
	//		if(cur == pos)
	//		{
	//			LinkListNode* node = CreateNode(value);
	//			node->next = cur->next;
	//			cur->next = node;
	//			return;
	//		}
	//		cur = cur->next;
	//	}
	//	return;
	//}
	//在单链表任意位置pos之后插入节点value
	void LinkListInsertAfter(LinkListNode* head,LinkListNode* pos,LinkListType value)
	{
		if(pos == NULL)
		{
			//非法输入
			return;
		}

		if(head == NULL)
		{
			//空链表,插入失败
			return;
		}

		//定义cur为当前指针，初始指向头节点
		LinkListNode* cur = head;
		//遍历链表，判断插入的位置pos是否在链表中
		while(cur != NULL)
		{
			if(cur == pos)//如果插入的位置在链表中
			{
				LinkListNode* node = CreateNode(value);//动态申请新节点
				node->next = pos->next;//使新节点的next指向pos的下个节点
				pos->next = node;//再使pos的next域指向新节点
				return;
			}
			cur = cur->next;//如果没找到插入的位置就一直往后遍历
		}
		return;//遍历完整个链表都没找到要插入的位置，说明该位置不在该链表中，则插入失败
	}

	//在单链表任意位置pos之前插入节点value
	void LinkListInsert(LinkListNode** phead,LinkListNode* pos,LinkListType value)
	{
		if(phead == NULL || pos == NULL)
		{
			//非法输入
			return;
		}
		if(*phead == NULL)
		{
			//空链表，插入失败
			return;
		}
		//如果在第一个节点前插入新节点
		if(pos == *phead)
		{
			//直接调用头插函数
			LinkListPushFront(phead,value);
			return;
		}

		//定义cur为当前位置指针来表示指定位置的上一个节点，初始为头指针
		LinkListNode* cur = *phead;
		//遍历链表，判断插入的位置是否在链表中
		while(cur != NULL)
		{
			if(cur->next == pos)//如果插入的位置在链表中
			{
				break;//跳出循环
			}
			cur = cur->next;//还未找到要插入的位置，一直往后遍历
		}
		if(cur == NULL)//当遍历完整个链表还没找到指定的位置，则插入失败
		{
			return;
		}
	//		LinkListNode* node = CreateNode(value);
	//		cur->next = node;
	//		node->next = pos;

		LinkListInsertAfter(*phead,cur,value);//此时cur为指定位置的上一个节点，在指定位置之前插入，即在cur之后插入节点
		return;
	}
	//在任意位置pos之前插入节点，数据域为value
	void LinkListInsertEx(LinkListNode** phead,LinkListNode* pos,LinkListType value)
	{
		if(phead == NULL || pos == NULL)
		{
			//非法输入
			return;
		}
		if(*phead == NULL)
		{
			//空链表
			return;
		}
		if(*phead == pos)
		{
			//指定位置为头节点，相当于头插
			LinkListPushFront(phead,value);//调用头插函数
			return;
		}
	//	LinkListInsertAfter(phead,pos,pos->data);//在指定位置之后插入节点，数据域为指定位置的数据
	//	pos->data = value;//将指定位置的数据替换为value
		LinkListNode* cur = *phead;
		while(cur != NULL)
		{
			if(cur == pos)
			{
				LinkListNode* new_node = CreateNode(pos->data);
				new_node->next = pos->next;
				pos->next = new_node;
				pos->data = value;
			}
			cur = cur->next;
		}
		return;
	}


	//void LinkListErase(LinkListNode** phead, LinkListNode* pos)
	//{
	//
	//	if(phead == NULL || pos == NULL)
	//	{
	//		//非法输入
	//		return;
	//	}
	//	if(*phead == NULL)
	//	{
	//		//链表为空
	//		return;
	//	}
	//	if(pos == *phead)
	//	{
	//		//删除位置为第一个节点
	//		*phead = pos->next;
	//		LinkListNodeDestory(pos);
	//		return;
	//	}
	//	LinkListNode* cur = *phead;
	//	for(;cur != NULL;cur = cur->next)
	//	{
	//		if(cur->next == pos)
	//		{
	//			break;
	//		}
	//	}
	//	if(cur == NULL)
	//	{
	//		return;
	//	}
	//	cur->next = pos->next;
	//	LinkListNodeDestory(pos);
	//	return;
	//}
	//删除任意位置处的节点
	void LinkListErase(LinkListNode** phead, LinkListNode* pos)
	{
		if(phead == NULL || pos == NULL)
		{
			//非法输入
			return;
		}
		if(*phead == NULL)
		{
			//链表为空，删除失败
			return;
		}
		if(pos == *phead)
		{
			//删除位置为第一个节点
			*phead = pos->next;//使头指针指向第二个节点
			LinkListNodeDestory(pos);//删除头节点
			return;
		}
		
		//定义cur为当前指针变量来表示指定位置的上一个节点，初始为头节点
		LinkListNode* cur = *phead;
		while(cur != NULL)
		{
			if(cur->next == pos)//如果删除的位置在链表中
			{
				break;
			}
			cur = cur->next;//还没找到要是删除的位置，就继续往后遍历
		}
		if(cur == NULL)//如果遍历完整个链表还没找到指定位置，说明指点位置不再链表中
		{
			return;
		}

		//删除的位置在链表中，cur表示指定位置的上一个节点
		cur->next = pos->next;//使cur指向指定位置的下一个节点
		LinkListNodeDestory(pos);//删除指定位置出的节点
		return;
	}

	//不适用于删除最后一个元素
	void LinkListErase2(LinkListNode** phead, LinkListNode* pos) 
	{
		if(phead == NULL || pos ==NULL)
		{
			//非法输入
			return;
		}
		if(*phead == NULL)
		{
			//空链表
			return;
		}
	//不能删除最后一个节点，且不能用于pos不再链表中的情况	
	//	LinkListNode* to_delete = pos->next;
	//	pos->data = to_delete->data;
	//	pos->next = to_delete->next;
	//	LinkListNodeDestory(to_delete);

		//有问题
		if(*phead == pos)
		{
			//删除的为第一个节点
			*phead = pos->next;
			LinkListNodeDestory(pos);
			return;
		}
		LinkListNode* cur = *phead;//定义cur为当前节点，遍历寻找pos是否在链表中
		while(cur != NULL)//cur未到达链表结尾，就一直往后遍历
		{
			if(cur == pos)//如果找到pos，就跳出循环，执行删除操作
			{
				break;
			}
			cur = cur->next;//没找到，就一直往后遍历
		}
		if(cur == NULL)//遍历完链表后，还没找到pos
		{
			return;
		}
		//此时，cur为找到的pos
		cur->data = pos->next->data;
		cur->next = pos->next->next;
		LinkListNodeDestory(pos->next);
		return;	
	}

	//删除指定元素to_delete的节点，如果有多个，只删除一个
	void LinkListRemove(LinkListNode** phead,LinkListType to_delete)
	{
		if(phead == NULL)
		{
			//非法输入
			return;
		}
		if(*phead == NULL)
		{
			//空链表
			return;
		}
		if((*phead)->data == to_delete)
		{
			//删除头节点,此时，需要改变头指针的指向
			LinkListNode* tmp = (*phead)->next;//保存要删除节点的下一个节点的地址
			LinkListNodeDestory(*phead);//删除要删除的节点
			*phead = tmp;//使头指针指向下个节点
			return;
		}

		//定义cur为当前节点的地址，初始为头指针
		LinkListNode* cur = *phead;
		while(cur->next != NULL)//遍历查找要删除的节点
		{
			if(cur->next->data == to_delete)//如果找到了
			{
				LinkListNode* tmp = cur->next->next;//保存要删除节点的下一个节点的地址
				LinkListNodeDestory(cur->next);//删除要删除的节点
				cur->next = tmp;//使cur的next指向下个节点
				return;
			}
			cur = cur->next;//没找到，继续往后遍历
		}
		return;//当遍历完链表还没找到，说明链表中不存在该节点
	}
	//删除指定元素的所有节点
	void LinkListRemoveAll(LinkListNode** phead,LinkListType to_delete)
	{
		if(phead == NULL)
		{
			//非法输入
			return;
		}
		//找到删除节点的位置(一次只能找一个)
		LinkListNode* pos = LinkListFind(*phead,to_delete);
		while(pos != NULL)//如果链表中还有要删除的节点
		{
			LinkListErase(phead,pos);//根据节点的位置将其删除
			pos = LinkListFind(*phead,to_delete);//继续查找指定元素的下一个节点所在位置
		}
		return;
	}

	//RemoveAll函数优化,不能删除最后一个节点
	void LinkListRemoveAllEx(LinkListNode** phead,LinkListType to_delete)
	{
		if(phead == NULL)
		{
			//非法输入
			return;
		}
		if(*phead == NULL)
		{
			//链表为空
			return;
		}

		//if((*phead)->data == to_delete)
		//{
		//	//头删
		//	LinkListPopFront(*phead);
		//}
		LinkListNode* cur = *phead;
		while(cur->next != NULL)
		{
			if(cur->next->data == to_delete)
			{
				LinkListNode* tmp = cur->next;
				cur->data = tmp->data;
				cur->next = tmp->next;
				LinkListNodeDestory(tmp);
			}
			else
			{
				cur = cur->next;
			}
		}
		return;
	}

	//链表判空，如果为空，返回1，否则返回0
	int LinkListEmpty(LinkListNode* head)
	{
		if(head == NULL)
		{
			//链表为空
			return 1;
		}
		return 0;
	}
	//统计链表中的节点个数
	size_t LinkListSize(LinkListNode* head)
	{
		//头指针指向NULL，链表为空
		if(head == NULL)
		{
			return 0;
		}

		size_t count = 0;//定义计数器变量用于记录节点的个数，初始为0
		LinkListNode* cur = head;//定义当前指针变量，初始指向头节点
		while(cur != NULL)//当cur不为空时
		{
			count++;//节点个数加1
			cur = cur->next;//cur后移
		}
		return count;
	}

	//取链表最后一个节点的地址
	LinkListNode* LinkListBack(LinkListNode* head)
	{
		if(head == NULL)
		{
			//链表为空
			return NULL;
		}


		LinkListNode* cur = head;//定义cur为当前指针变量，初始指向头节点
		while(cur->next != NULL)//当为找到最后一个节点时，指针一直往后移，直到找到为止
		{
			cur = cur->next;
		}
		//此时，cur为最后一个节点的地址
		return cur;
	}

	//销毁链表
	void LinkListDestory(LinkListNode** phead)
	{
		if(phead == NULL)
		{
			//非法输入
			return;
		}
		if(*phead == NULL)
		{
			//链表为空
			return;
		}
		//定义cur为当前指针变量，初始指向头节点
		LinkListNode* cur = *phead;
		while(cur != NULL)//如果cur不为NULL，就要对其进行销毁
		{
			LinkListNode* to_delete = cur;//保存要销毁的节点地址
			cur = to_delete->next;//使cur指向要销毁节点的下一个节点
			LinkListNodeDestory(to_delete);//销毁节点
		}
		*phead = NULL;//全部销毁结束后，使头指针置为NULL
		return;
	}

////从尾到头打印单链表：利用递归来实现
//void LinkListReversePrint(LinkListNode* head)
//{
//    if(head == NULL)
//    {
//        //链表为空
//        return;
//    }
//    LinkListReversePrint(head->next);
//    printf("%c ",head->data);
//    return;
//}
//
//
//逆序打印单链表：利用栈来实现
void LinkListReversePrint(LinkListNode* head)
{
    if(head == NULL)
    {
        //空链表
        return;
    }
    LinkListNode* cur = head;


    SeqStack stack;   //一定要初始化             
    InitSeqStack(&stack); 
    while(cur != NULL)
    {
        SeqStackPush(&stack,cur->data);
        cur = cur->next;
    }
    while(1)
    {
        SeqStackType value;
        int ret = SeqStackTop(&stack,&value);
        if(ret == -1)
        {
            return;
        }
        printf("%c ",value);
        SeqStackPop(&stack);
    }
}


	////从尾到头打印单链表
	//void LinkListReversePrint(LinkListNode* head)
	//{
	//	if(head == NULL)
	//	{
	//		return;
	//	}
	//	LinkListReversePrint(head->next);
	//	printf("%c ",head->data);
	//	return;
	//}

	//单链表实现约瑟夫环,m为指定的数字
	LinkListNode* JosephCircle(LinkListNode** phead,int m)
	{
		if(phead == NULL)
		{
			//非法输入
			return NULL;
		}
		if(*phead == NULL)
		{
			//空链表
			return NULL;
		}
		//下面的代码已经包含该情况
		//if((*phead)->next == *phead)
		//{
		//	//链表中只有一个节点
		//	return *phead;
		//}
		LinkListNode* cur = *phead;//定义cur为当前指针变量，查找第m个节点
		while(cur->next != cur)//如果未删除到只剩一个节点
		{
			int i = 1;
			for(;i < m;i++)//找到从删除位置下一个节点开始（或从头开始）的第m个节点
			{
				cur = cur->next;
			}

			//下列操作与上述不遍历链表删除链表节点的原理相同
			printf("%c \n",cur->data);//此时，cur为要第m个节点
			LinkListNode* to_delete = cur->next;//删除第m+1个节点
			cur->data = to_delete->data;//将第m个节点处的数据替换为第m+1个节点的数据
			cur->next = to_delete->next;//使第m个节点指向第m+2个节点
			LinkListNodeDestory(to_delete);//删除第m+1个节点
			//此时，cur相当于指向实际要删除的节点（第m个节点）的下一个节点:第m+1个节点
			//然后，再从cur开始找第m个节点对其进行删除
		}
		return cur;
	}
	//逆置单链表:循环头插法
	void LinkListReverse(LinkListNode** phead)
	{
		if(phead == NULL)
		{
			//非法输入
			return;
		}
		if(*phead == NULL)
		{
			//空链表
			return;
		}
		//包含在下述代码中
		//if((*phead)->next == NULL)
		//{
		//	//链表中只有一个节点
		//	return;
		//}
		LinkListNode* cur = *phead;//定义cur为当前指针变量，每次头插他之后的节点
		while(cur->next != NULL)//当cur的下个节点一直不为空时，就一直头插
		{
			LinkListNode* to_delete = cur->next;//将cur的下个节点作为头插的节点
			cur->next = to_delete->next;//使cur的next域指向下下个节点
			//头插cur的下个节点
			to_delete->next = *phead;
			*phead = to_delete;
		}
		return;
	}
	//逆置单链表：三指针循环法
	void LinkListReverse1(LinkListNode** phead)
	{
		if(phead == NULL)
		{
			//非法输入
			return;
		}
		if(*phead == NULL)
		{
			//空链表
			return;
		}
		if((*phead)->next == NULL)
		{
			//只有一个节点
			return;
		}
		
		LinkListNode* pre = *phead;
		LinkListNode* cur = (*phead)->next;
		pre->next = NULL;
		//在移动过程中，从pre开始的链表都是已经逆置好的链表，而cur是待逆置的链表
		//当cur为空时，整个链表逆置完成
		while(cur != NULL)
		{
			LinkListNode* next = cur->next;//保存next的next域
			cur->next = pre;//使cur的next域指向pre
			pre = cur;//pre指向cur的位置
			cur = next;//cur后移
		}
		*phead = pre;//整个链表逆置完成后，头节点由pre指向，所以使头指针在指向pre即可
		return;
	//	LinkListNode* pre = *phead;
	//	LinkListNode* cur = (*phead)->next;
	//	LinkListNode* next = cur->next;
	//	pre->next = NULL;
	//	while(cur != NULL)
	//	{
	//		cur->next = pre;
	//		pre = cur;
	//		cur = next;
	//		if(cur == NULL)
	//		{
	//			break;
	//		}
	//		next = cur->next;
	//	}
	//	*phead = pre;
	//	return;
	}
	//交换函数:交换两节点的数据域
	void Swap(LinkListType* a,LinkListType* b)
	{
		LinkListType temp;
		temp = *a;
		*a = *b;
		*b = temp;
		return;
	}
	void LinkListBubbleSort(LinkListNode* head)
	{
		if(head == NULL)
		{
			//空链表
			return;
		}
		if(head->next == NULL)
		{
			//链表中只有一个节点
			return;
		}
		
		LinkListNode* count = head;//比较的趟数
		LinkListNode* tail = NULL;//尾指针
		for(;count->next !=	NULL;count = count->next)
		{
			LinkListNode* cur = head;
			for(;cur->next != tail;cur = cur->next)
			{
				if(cur->data > cur->next->data)
				{
					Swap(&(cur->data),&(cur->next->data));
				}
			}
			tail = cur;
		}
		return;
	}

	//回调函数：用于比较两数据域的大小
	int cmp_char(LinkListType a,LinkListType b)
	{
		if(a > b)
		{
			return 1;
		}
		else if(a < b)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
	//利用回调函数来进行冒泡排序
	void LinkListBubbleSort1(LinkListNode* head,int (*Cmp)(LinkListType,LinkListType))
	{
		if(head == NULL)
		{
			//空链表
			return;
		}
		if(head->next == NULL)
		{
			//链表中只有一个节点
			return;
		}
		
		LinkListNode* count = head;//比较的趟数
		LinkListNode* tail = NULL;//尾指针，记录每一论比较时的结束条件
		for(;count->next !=	NULL;count = count->next)
		{
			LinkListNode* cur = head;//定义当前指针变量，来比较相邻两节点的数据域
			for(;cur->next != tail;cur = cur->next)
			{
				if(Cmp(cur->data,cur->next->data) > 0)//调用回调函数来比较两数据域的大小
				{
					Swap(&(cur->data),&(cur->next->data));//交换两数据域
				}
			}
			tail = cur;//每一论比较过后，更新尾指针的指向
		}
		return;
	}

	//合并两个有序链表使之继续有序
	LinkListNode* LinkListMerge(LinkListNode* head1,LinkListNode* head2)
	{
		if(head1 == NULL)
		{
			//链表1为空
			return head2;
		}
		if(head2 == NULL)
		{
			//链表2为空
			return head1;
		}
		LinkListNode* cur1 = head1;//cur1用于遍历链表1
		LinkListNode* cur2 = head2;//cur2用于遍历链表2
		LinkListNode* new_head = NULL;//新链表的头指针
		LinkListNode* new_tail = NULL;//新链表的尾指针
		while(cur1 != NULL && cur2 != NULL)
		{
			if(cur1->data < cur2->data)//cur1的数据域小
			{
				if(new_tail == NULL)//如果新链表为空
				{
					new_head  = cur1;//头尾指针直接指向数据小的节点
					new_tail  = cur1;
				}
				else//如果不为空
				{
					new_tail->next = cur1;//使数据小的节点插入新链表的尾部
					new_tail = new_tail->next;//尾指针后移
				}
				cur1 = cur1->next;//cur1后移
			}
			else//cur1的数据不小于cur2的，重复与上述类似的操作
			{
				if(new_tail == NULL)
				{
					new_head = cur2;
					new_tail = cur2;
				}
				else
				{
					new_tail->next = cur2;
					new_tail = new_tail->next;
				}
				cur2 = cur2->next;
			}
		}
		if(cur1 != NULL)//如果cur1未遍历完，将cur1的剩余节点插入新链表的尾部
		{
			new_tail->next = cur1;
		}
		else
		{
			new_tail->next = cur2;
		}
		return new_head;
	}

	//查找中间节点，只遍历一次
	LinkListNode* LinkListFindMidNode(LinkListNode* head)
	{
		if(head == NULL)
		{
			//空链表
			return NULL;
		}
		if(head->next == NULL)
		{
			//只有一个节点
			return head;
		}

		LinkListNode* slow = head;//定义慢指针从头开始遍历
		LinkListNode* fast = head;//定义快指针从头开始遍历
		while(fast->next != NULL && fast->next->next != NULL)//如果快指针为满足结束条件
		{
			fast = fast->next->next;//则快指针一次往后走两步
			slow = slow->next;//满指针一次往后走一步
		}
		return slow;//快指针满足结束条件后，满指针正好指向中间节点
	}
	//查找中间节点，只遍历一次
	LinkListNode* LinkListFindMidNode1(LinkListNode* head)
	{
		if(head == NULL)
		{
			//空链表
			return NULL;
		}
		if(head->next == NULL)
		{
			//只有一个节点
			return head;
		}

		LinkListNode* slow = head;
		LinkListNode* fast = head;
		while(fast != NULL && fast->next != NULL)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow;
	}

	//查找倒数第k个节点，只遍历一次
	LinkListNode* LinkListFindLastKNode(LinkListNode* head,int k)
	{
		if(head == NULL)
		{
			//空链表
			return NULL;
		}
		LinkListNode* fast = head;//定义快指针
		LinkListNode* slow = head;//定义满指针
		int i =0;
		for(;i < k;i++)//使快指针先走k步
		{
			if(fast == NULL)//说明此时k大于等于链表的长度
			{
				break;
			}
			fast = fast->next;
		}
		if(i < k)//如果k大于链表的长度
		{
			return NULL;
		}
		while(fast != NULL)//再使快慢指针同时走，一次走一步，直到快指针走向结尾
		{
			fast = fast->next;
			slow = slow->next;
		}
		return slow;
	}

//删除倒数第k个节点
void LinkListEraseLastKNode(LinkListNode** phead,int k)
{
	if(phead == NULL)
	{
		//非法输入
		return;
	}
	if(*phead == NULL)
	{
		//空链表
		return;
	}
	if(k <= 0)
	{
		return;
	}
	int size = LinkListSize(*phead);//计算链表的长度
	if(k > size)//如果查找的节点不在该链表内
	{
		return;
	}
	if(k == size)
	{
		//第k个节点为第一个节点:头删
		LinkListNode* to_delete = *phead;
		*phead = (*phead)->next;
		LinkListNodeDestory(to_delete);
		return;
	}
	//查找倒数第k+1个节点
	LinkListNode* pre_k = LinkListFindLastKNode(*phead,k+1);
	//然后删除倒数第k个节点
	LinkListNode* to_delete = pre_k->next;
	pre_k->next = to_delete->next;
	LinkListNodeDestory(to_delete);
	return;
	//LinkListNode* cur = *phead;
	//int i = 0;
	//for(;i < size - k - 1;i++)//寻找倒数第k+1个节点
	//{
	//	cur = cur->next;	
	//}
	////此时，cur即为倒数第k+1个节点
	//LinkListNode* to_delete = cur->next;
	//cur->next = to_delete->next;
	//LinkListNodeDestory(to_delete);
	//return;
}

//判断链表是否带环:1表示有环，0表示没有
//方法2：定义快慢指针，快指针走两步，满指针走一步，当快慢指针可以相遇，说明有环
int LinkListHasCircle(LinkListNode* head)
{
	if(head == NULL)
	{
		//空链表
		return 0;
	}
	LinkListNode* fast = head;//定义快指针
	LinkListNode* slow = head;//定义满指针
	while(fast->next != NULL && fast->next->next != NULL)//如果有环该条件不可能成立
	{
		fast = fast->next->next;//快指针一次走两步
		slow = slow->next;//满指针一次走一步
		if(fast == slow)//如果快慢指针相遇了，说明有环
		{
			return 1;
		}
	}
	return 0;//while循环的条件不成立，说明没环
}
//求环的相遇点
LinkListNode* LinkListHasCircle1(LinkListNode* head)
{
	if(head == NULL)
	{
		//空链表
		return NULL;
	}
	LinkListNode* fast = head;
	LinkListNode* slow = head;
	while(fast->next != NULL && fast->next->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow)
		{
			return slow;
		}
	}
	return NULL;

}
//球带环链表的环长
size_t LinkListCircleLength(LinkListNode* head)
{
	if(head == NULL)
	{
		//链表为空
		return 0;
	}
	LinkListNode* fast = head;
	LinkListNode* slow = head;
	while(fast->next != NULL && fast->next->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if(slow == fast)//如果带环
		{
			LinkListNode* cur = slow->next;//从相遇点开始
			int count = 1;//设置计数器变量
			while(cur != slow)//绕环一周，再次回到相遇点，即为环长
			{
				count++;
				cur = cur->next;
			}
			return count;
		}
	}
	return 0;
}
////球带环链表的环长
//size_t LinkListCircleLength(LinkListNode* head)
//{
//	if(head == NULL)
//	{
//		//空链表
//		return 0;
//	}
//	LinkListNode* meet_node = LinkListHasCircle1(head);
//	if(meet_node == NULL)
//	{
//		return 0;
//	}
//	LinkListNode* cur = meet_node->next;
//	int count = 1;
//	while(cur != meet_node)
//	{
//		cur = cur->next;
//		count = count + 1;
//	}
//	return count;
//}

//求环的入口点
LinkListNode* LinkListCircleEntry(LinkListNode* head)
{
	if(head == NULL)
	{
		//链表为空
		return NULL;
	}
	LinkListNode* meet_node = LinkListHasCircle1(head);//求快慢指针的相遇点
	if(meet_node == NULL)
	{
		return NULL;//如果相遇点为空，说明链表不带环
	}
	LinkListNode* cur1 = head;//使cur1从头开始走
	LinkListNode* cur2 = meet_node;//cur2从相遇点开始走
	while(cur1 != cur2)//当两指针未相遇时，即未走到入口点
	{
		cur1 = cur1->next;//一次一步往前走
		cur2 = cur2->next;
	}
	return cur1;//两指针相遇的地方即为相遇点
}


//判相交，求交点(假设两链表不带环)
LinkListNode* LinkListCrossPos(LinkListNode* head1,LinkListNode* head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		//任意一个链表为空，都没有交点
		return NULL;
	}
	size_t size1 = LinkListSize(head1);//求链表1的长度
	size_t size2 = LinkListSize(head2);//求链表2的长度
	LinkListNode* cur1 = head1;//使cur1初始指向链表1的头节点
	LinkListNode* cur2 = head2;//使cur2初始指向链表2的头节点
	size_t i = 0;
    if(size1 > size2)//如果链表1比链表2长
    {
        for(;i < size1 - size2;++i)
        {
            cur1 = cur1->next;//如果链表1比链表2长，让链表1先走多余的部分
        }

    }
    else 
    {
        for(i = 0;i < size2 - size1;++i)
        {
            cur2 = cur2->next;//如果链表2比链表1长，让链表2先走多余的部分
        }
    }
	while(cur1 != NULL && cur2 != NULL)
	{
		if(cur1 == cur2)//相遇点即为两链表相交的点
		{
			return cur1;
		}
		cur1 = cur1->next;//两个指针同时后移
		cur2 = cur2->next;
	}
	return NULL;//两连表不相交
}

//判定链表是否相交(假设两链表不带环)
int LinkListHasCross(LinkListNode* head1,LinkListNode* head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return 0;
	}
	LinkListNode* cur1 = head1;
	LinkListNode* cur2 = head2;
	for(;cur1->next != NULL;cur1 = cur1->next);
	for(;cur2->next != NULL;cur2 = cur2->next);
	if(cur1 == cur2)
	{
		return 1;
	}
	return 0;
}

//判相交(两链表可能带环)
int LinkListHasCrossWithCircle(LinkListNode* head1,LinkListNode* head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return 0;
	}

	LinkListNode* entry1 = LinkListCircleEntry(head1);
	LinkListNode* entry2 = LinkListCircleEntry(head2);
	if(entry1 == NULL && entry2 == NULL)//两链表不带环
	{
		int ret = LinkListHasCross(head1,head2);
		if(ret == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	if((entry1 == NULL && entry2 != NULL)||(entry1 != NULL && entry2 == NULL))//一个链表带环，一个不带
	{
		return 0;//不可能相交
	}

	//若两链表都带环
	if(entry1 == entry2)//入口点相同，环外相交
	{
		return 1;
	}
	LinkListNode* cur1 = entry1->next;
	while(cur1 != entry1)
	{
		if(cur1 == entry2)//环上相交
		{
			return 1;
		}
		cur1 = cur1->next;
	}
	return 0;//两带环链表不相交


}

//判相交，求交点(两链表可能带环)
LinkListNode* LinkListCrossPosWithCircle(LinkListNode* head1,LinkListNode* head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return NULL;
	}
	//求两链表的环的入口点
	LinkListNode* entry1 = LinkListCircleEntry(head1);
	LinkListNode* entry2 = LinkListCircleEntry(head2);

	//如果两链表均无环，则按照上述无环的情况处理
	if(entry1 == NULL && entry2 == NULL)
	{
		return LinkListCrossPos(head1,head2);
	}
	//若一个链表有环，一个没有环,则肯定不相交
	if((entry1 == NULL && entry2 != NULL)||(entry1 != NULL && entry2 == NULL))
	{
		return NULL;
	}
	//如果两链表都带环
	if(entry1 == entry2)//如果两环的入口点相同，则环外相交
	{
		//求两环从头到环入口点的长度
		LinkListNode* cur1 = head1;
		LinkListNode* cur2 = head2;
		int length1 = 1;
		int length2 = 1;
		while(cur1 != entry1)
		{
			length1++;
			cur1 = cur1->next;
		}
		while(cur2 != entry2)
		{
			++length2;
			cur2 = cur2->next;
		}
		cur1 = head1;//两当前位置指针要从头开始
		cur2 = head2;
		//使长链表先走偏移量步
        int i =0;
		if(length1 > length2)
		{
			for(i = 0;i < length1-length2;++i)
			{
				cur1 = cur1->next;
			}
		}
		else
		{
			for(;i < length2-length1;++i)
			{
				cur2 = cur2->next;
			}
		}
		//走完后，一个指针走一步，直到走到相遇点
		while(cur1 != cur2)
		{
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return cur1;
	}
	else//如果两环的环入口点不相同
	{
		LinkListNode* cur1 = entry1->next;
		while(cur1 != entry1)//从一个链表的环入口点出发，绕环一周，若能找到另一链表的环入口点，则两入口点即两交点
		{
			if(cur1 == entry2)
			{
				return entry2;//此时，entry1和entry2均为两交点，这里，只返回一个
			}
			cur1 = cur1->next;
		}
		return NULL;//绕环一周，没找到另一链表的环入口点，则两带环链表不相交
	}
}

//求两排序链表中相同的数据(即求交集，若有多个相同元素，只取一个)
//对原链表会造成破坏，会造成内存泄漏
LinkListNode* LinkListUnionSet(LinkListNode* head1,LinkListNode* head2)
{
	//如果任一链表为空，则交集为空
	if(head1 == NULL || head2 == NULL)
	{
		return NULL;
	}
	LinkListNode* cur1 = head1;
	LinkListNode* cur2 = head2;
	LinkListNode* new_head = NULL;
	LinkListNode* new_tail = NULL;
	while(cur1 != NULL && cur2 != NULL)
	{
		if(cur1->data < cur2->data)
		{
			cur1 = cur1->next;
		}
		else if(cur1->data > cur2->data)
		{
			cur2 = cur2->next;
		}
		else
		{
			if(new_tail == NULL)
			{
				new_head = new_tail = cur1;
			}
			else
			{
				new_tail->next = cur1;
				new_tail = new_tail->next;
			}
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
	}
	if(new_tail == NULL)
	{
		return NULL;
	}
	else
	{
		new_tail->next = NULL;
	}
	return new_head;
}

//求两排序链表中相同的数据(即求交集，若有多个相同元素，只取一个)
//不破坏原链表，并且一个链表中允许有多个相同的元素
LinkListNode* LinkListUnionSetEx(LinkListNode* head1,LinkListNode* head2)
{
	//如果任一链表为空，则交集为空
	if(head1 == NULL || head2 == NULL)
	{
		return NULL;
	}
	LinkListNode* cur1 = head1;//定义cur1遍历链表1
	LinkListNode* cur2 = head2;//定义cur2遍历链表2
	LinkListNode* new_head = NULL;//定义新链表的头指针
	LinkListNode* new_tail = NULL;//定义新链表的尾指针
	while(cur1 != NULL && cur2 != NULL)//如果两链表都没遍历完
	{
		if(cur1->data < cur2->data)//如果cur1的数据域小于cur2的
		{
			cur1 = cur1->next;//则cur1后移
		}
		else if(cur1->data > cur2->data)//如果cur1的数据域大于cur2的
		{
			cur2 = cur2->next;//则cur2后移
		}
		else//如果两指针的数据域相同，将相同的数据插入到新链表中
		{
			if(new_tail == NULL)//如果链表为空
			{
				new_head = new_tail = CreateNode(cur1->data);
			}
			else//如果链表不为空
			{
				if(new_tail->data != cur1->data)//如果交集中没有相同的元素，则执行插入操作
				{
					new_tail->next = CreateNode(cur1->data);
					new_tail = new_tail->next;
				}
			}
			cur1 = cur1->next;//使两指针同时后移
			cur2 = cur2->next;
		}
	}
	return new_head;//当遍历完其中一个链表后，另一链表中的剩余元素不可能为交集中的元素，所以直接返回新链表
}


//若两链表无序，求两链表的交集
LinkListNode* LinkListUnionSetNoSort(LinkListNode* head1,LinkListNode* head2)
{
	if(head1 == NULL || head2 == NULL)
	{
		return NULL;
	}
	LinkListBubbleSort(head1);
	LinkListBubbleSort(head2);
    LinkListNode* new_head = LinkListUnionSetEx(head1,head2);
	return new_head;
}

//创建复杂链表节点
ComplexNode* CreateComplexNode(ComplexType data)
{
	ComplexNode* new_node = (ComplexNode*)malloc(sizeof(ComplexNode));
	new_node->data = data;
	new_node->next = NULL;
	new_node->random = NULL;
	return new_node;
}

//求random域据头节点的偏移量
int Diff(ComplexNode* head,ComplexNode* random)
{
	ComplexNode* cur = head;
	int offset = 0;
	while(cur != random)
	{
		++offset;
		cur = cur->next;
	}
	return offset;
}

//设置复制后的节点的random值
ComplexNode* Step(ComplexNode* new_head,int offset)
{
	ComplexNode* cur = new_head;
	int i = 0;
	for(;i < offset;++i)
	{
		cur = cur->next;
	}
	return cur;
}
//复杂链表的复制
ComplexNode* CopyComplexList(ComplexNode* head)
{
	//原链表为空，则复制后的链表也为空
	if(head == NULL)
	{
		return NULL;
	}
	ComplexNode* cur = head;
	ComplexNode* new_head = NULL;
	ComplexNode* new_tail = NULL;
	//先复制各节点的数据域及next域
	while(cur != NULL)
	{
		if(new_head == NULL)
		{
			new_head = new_tail = CreateComplexNode(cur->data);
		}
		else
		{
			new_tail->next = CreateComplexNode(cur->data);
			new_tail = new_tail->next;
		}
		cur = cur->next;
	}
	//在再使两链表从头开始遍历，求原链表各节点的random域的偏移量，再设置新链表各节点的random的值
	cur = head;
	ComplexNode* new_cur = new_head;
	while(cur != NULL)
	{
		if(cur->random == NULL)
		{
			new_cur->random = NULL;
		}
		else
		{
			int offset = Diff(head,cur->random);//求偏移量
			new_cur->random = Step(new_head,offset);//设置新链表中各节点的random域
		}
		cur = cur->next;
		new_cur = new_cur->next;
	}
	return new_head;
}

//复杂链表的复制(简单)
ComplexNode* CopyComplexListEx(ComplexNode* head)
{
	if(head == NULL)
	{
		//原链表为空，则新链表也为空
		return NULL;
	}
	//首先，在原链表每个节点后面插入相同的节点
	ComplexNode* cur = head;
	for(;cur != NULL;cur = cur->next->next)//如果cur不为空，则一定可以在其后插入一个新元素，所以cur->next也一定不为空
	{
		ComplexNode* new_node = CreateComplexNode(cur->data);
		new_node->next = cur->next;
		cur->next = new_node;
	}
	//然后，根据原有节点的random域设置新插入的各节点的random域
	cur = head;
	for(;cur != NULL;cur = cur->next->next)
	{
		if(cur->random == NULL)
		{
			cur->next->random = NULL;
		}
		else
		{
			cur->next->random = cur->random->next;
		}
	}

	//最后，提取出插入的所有新节点
	ComplexNode* new_head = NULL;
	ComplexNode* new_tail = NULL;
	cur = head;
	while(cur != NULL)
	{
		ComplexNode* new_cur = cur->next;
		cur->next = new_cur->next;

		if(new_head == NULL)
		{
			new_head = new_tail = new_cur;
		}
		else
		{
			new_tail->next = new_cur;
			new_tail = new_tail->next;
		}
		cur = cur->next;
	}
	return new_head;
}
////////////////////////////////////
//测试代码
///////////////////////////////////

#include<stdio.h>
#define TEST_HANDLE printf("\n====================%s===================\n",__FUNCTION__)

	void TestInit()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);
		return;
	}

	void LinkListPrint(LinkListNode* head,const char* msg)
	{
		printf("%s\n",msg);
		LinkListNode* cur = head;

		while(cur != NULL)
		{
			printf("[%c] ",cur->data);
			cur = cur->next;
		}
		printf("\n\n");
		return;
	}

	void TestPushBack()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);
		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');

		LinkListPrint(head,"尾插四个元素\n");
		return;
	}
	//测试尾删1
	void TestPopBack1()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		LinkListPopBack1(&head);//尾删空链表
		LinkListPrint(head,"尾删空链表\n");

		LinkListPushBack(&head,'a');
		LinkListPopBack1(&head);//尾删只有一个节点的链表
		LinkListPrint(head,"尾删元素a\n");

		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');

		LinkListPopBack1(&head);
		LinkListPrint(head,"尾删一个元素\n");

		LinkListPopBack1(&head);
		LinkListPopBack1(&head);
		LinkListPrint(head,"尾删两个元素\n");
		return;
	}

	void TestPopBack2()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		LinkListPopBack2(&head);//尾删空链表
		LinkListPrint(head,"尾删空链表\n");

		LinkListPushBack(&head,'a');
		LinkListPopBack2(&head);//尾删只有一个节点的链表
		LinkListPrint(head,"尾删元素a\n");

		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');

		LinkListPopBack2(&head);
		LinkListPrint(head,"尾删一个元素\n");

		LinkListPopBack2(&head);
		LinkListPopBack2(&head);
		LinkListPrint(head,"尾删两个元素\n");
		return;
	}
	void TestPushFront()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		LinkListPushFront(&head,'a');
		LinkListPrint(head,"头插一个元素\n");
		LinkListPushFront(&head,'b');
		LinkListPushFront(&head,'c');
		LinkListPushFront(&head,'d');

		LinkListPrint(head,"头插三个元素\n");
		return;
	}

	void TestPopFront()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		LinkListPopFront(&head);//头删空链表
		LinkListPrint(head,"头删空链表\n");

		LinkListPushFront(&head,'a');
		LinkListPopFront(&head);
		LinkListPrint(head,"头删只有一个节点的链表\n");

		LinkListPushFront(&head,'b');
		LinkListPushFront(&head,'c');
		LinkListPushFront(&head,'d');
		LinkListPrint(head,"插入三个元素\n");

		LinkListPopFront(&head);
		LinkListPrint(head,"头删一个元素\n");
		LinkListPopFront(&head);
		LinkListPopFront(&head);
		LinkListPrint(head,"头删两个元素\n");
		return;
	}

	void TestFind()
	{

		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);
		printf("对空链表进行查找，a的地址为：%p\n",LinkListFind(head,'a'));

		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");

		printf("a的地址为：%p\n",LinkListFind(head,'a'));
		printf("b的地址为：%p\n",LinkListFind(head,'b'));
		printf("c的地址为：%p\n",LinkListFind(head,'c'));
		printf("d的地址为：%p\n",LinkListFind(head,'d'));
		printf("m的地址为：%p\n",LinkListFind(head,'m'));
		return;
	}

	void TestInsert()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		LinkListInsert(&head,head,'m');
		LinkListPrint(head,"在第一个节点前插入m\n");

		LinkListPushBack(&head,'a');
		LinkListInsert(&head,head,'m');
		LinkListPrint(head,"在a前插入m\n");

		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"链表中的元素\n");

		LinkListInsert(&head,head->next->next,'n');
		LinkListPrint(head,"在b前插入n\n");
		LinkListInsert(&head,(LinkListNode*)0x1778,'n');
		LinkListPrint(head,"在0x1778前插入n\n");
		return;
	}

	void TestInsertEx()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		LinkListInsert(&head,head,'m');
		LinkListPrint(head,"在第一个节点前插入m\n");

		LinkListPushBack(&head,'a');
		LinkListInsert(&head,head,'m');
		LinkListPrint(head,"在a前插入m\n");

		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"链表中的元素\n");

		LinkListInsert(&head,head->next->next,'n');
		LinkListPrint(head,"在b前插入n\n");
		LinkListInsert(&head,(LinkListNode*)0x1778,'n');
		LinkListPrint(head,"在0x1778前插入n\n");
		return;
	}
	//void TestInsertAfter()
	//{
	//	TEST_HANDLE;
	//	LinkListNode* head;
	//	LinkListInit(&head);
	//
	//	LinkListPushBack(&head,'a');
	//	LinkListPushBack(&head,'b');
	//	LinkListPushBack(&head,'c');
	//	LinkListPushBack(&head,'d');
	//	LinkListPrint(head,"尾插四个元素\n");
	//
	//	LinkListInsertAfter(&head,head,'m');
	//	LinkListPrint(head,"在第一个节点后插入m\n");
	//	LinkListInsertAfter(&head,head->next->next,'n');
	//	LinkListPrint(head,"在第三个节点后插入n\n");
	//	LinkListInsertAfter(&head,(LinkListNode*)0x1778,'n');
	//	LinkListPrint(head,"在0x1778前插入n\n");
	//	return;
	//
	//}
	void TestInsertAfter()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");

		LinkListInsertAfter(head,head,'m');
		LinkListPrint(head,"在第一个节点后插入m\n");
		LinkListInsertAfter(head,head->next->next,'n');
		LinkListPrint(head,"在第三个节点后插入n\n");
		LinkListInsertAfter(head,(LinkListNode*)0x1778,'n');
		LinkListPrint(head,"在0x1778前插入n\n");
		return;

	}

	void TestErase()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		LinkListErase(&head,head);
		LinkListPrint(head,"删除空链表\n");

		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");

		LinkListErase(&head,head);
		LinkListPrint(head,"删除第一个节点\n");

		LinkListErase(&head,head->next);
		LinkListPrint(head,"删除第二个节点\n");

		LinkListErase(&head,(LinkListNode*)0x77);
		LinkListPrint(head,"删除非链表元素\n");
		return;
	}

	void TestErase2()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		LinkListErase2(&head,head);
		LinkListPrint(head,"删除空链表\n");

		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");

		LinkListErase2(&head,head);
		LinkListPrint(head,"删除第一个节点\n");

		LinkListErase2(&head,head->next);
		LinkListPrint(head,"删除第二个节点\n");

//		LinkListErase2(&head,(LinkListNode*)0x77);
//		LinkListPrint(head,"删除非链表元素\n");
		return;
	}

	void TestRemove()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);
		LinkListRemove(&head,'a');
		LinkListPrint(head,"对空链表进行删除");

		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");

		LinkListRemove(&head,'a');
		LinkListPrint(head,"删除头节点a\n");

		LinkListRemove(&head,'d');
		LinkListPrint(head,"删除元素d\n");
		LinkListRemove(&head,'m');
		LinkListPrint(head,"删除不存在的节点m\n");

		return;
	}

	void TestRemoveAll()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");

		LinkListRemoveAll(&head,'a');
		LinkListPrint(head,"删除元素a\n");
		LinkListRemoveAll(&head,'b');
		LinkListPrint(head,"删除元素b\n");
		return;

	}
	void TestRemoveAllEx()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);
		LinkListRemoveAllEx(&head,'b');
		LinkListPrint(head,"尾插空链表\n");

		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");

		LinkListRemoveAllEx(&head,'a');
		LinkListPrint(head,"删除元素a\n");
		LinkListRemoveAllEx(&head,'d');
		LinkListPrint(head,"删除元素d\n");
		return;

	}

	void TestEmpty()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		int ret = LinkListEmpty(head);
		printf("expect 1,actually %d\n",ret);
		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");

		ret = LinkListEmpty(head);
		printf("expect 0,actually %d\n",ret);
		
	}

	void TestSize()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		int count = LinkListSize(head);
		printf("expect 0,actually %lu\n",count);

		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");
		count = LinkListSize(head);
		printf("expect 4,actually %lu\n",count);
		return;
	}

	void TestReversePrint()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);
		LinkListReversePrint(head);
		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");
		LinkListReversePrint(head);
		printf("\n");
		return;
	}

	void TestJosephCircle()
	{
		TEST_HANDLE;
		LinkListNode* a = CreateNode('a');
		LinkListNode* b = CreateNode('b');
		LinkListNode* c = CreateNode('c');
		LinkListNode* d = CreateNode('d');
		LinkListNode* e = CreateNode('e');
		LinkListNode* f = CreateNode('f');
		LinkListNode* g = CreateNode('g');
		LinkListNode* h = CreateNode('h');
		a->next = b;
		b->next = c;
		c->next = d;
		d->next = e;
		e->next = f;
		f->next = g;
		g->next = h;
		h->next = a;
		LinkListNode* surviver = JosephCircle(&a,5);
		printf("surviver = %c\n",surviver->data);
		return;
	}

	void TestReverse()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);
		LinkListReverse(&head);
		LinkListPrint(head,"打印逆置后的空链表\n");
		LinkListPushBack(&head,'a');
		LinkListReverse(&head);
		LinkListPrint(head,"逆置只有一个节点的链表\n");
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");
		LinkListReverse(&head);
		LinkListPrint(head,"逆置多节点的链表\n");

	}
	void TestReverse1()
	{
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);
		LinkListReverse1(&head);
		LinkListPrint(head,"打印逆置后的空链表\n");
		LinkListPushBack(&head,'a');
		LinkListReverse1(&head);
		LinkListPrint(head,"逆置只有一个节点的链表\n");
		LinkListPushBack(&head,'b');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'d');
		LinkListPrint(head,"尾插四个元素\n");
		LinkListReverse1(&head);
		LinkListPrint(head,"逆置多节点的链表\n");

	}

	void TestBubbleSort()
	{

		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		//空链表
		LinkListBubbleSort(head);
		LinkListPrint(head,"打印空链表\n");

		//只有一个节点的链表
		LinkListPushBack(&head,'a');
		LinkListBubbleSort(head);
		LinkListPrint(head,"打印只有一个节点的链表\n");

		//多个节点的链表
		LinkListPushBack(&head,'d');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'b');
		LinkListBubbleSort(head);
		LinkListPrint(head,"打印只有多个节点的链表\n");
		return;
	}

	void TestBubbleSort1()
	{

		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		//空链表
		LinkListBubbleSort1(head,cmp_char);
		LinkListPrint(head,"打印空链表\n");

		//只有一个节点的链表
		LinkListPushBack(&head,'a');
		LinkListBubbleSort1(head,cmp_char);
		LinkListPrint(head,"打印只有一个节点的链表\n");

		//多个节点的链表
		LinkListPushBack(&head,'d');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'b');
		LinkListBubbleSort1(head,cmp_char);
		LinkListPrint(head,"打印只有多个节点的链表\n");
		return;
	}

	void TestMerge()
	{

		TEST_HANDLE;
		LinkListNode* head1;
		LinkListNode* head2;
		LinkListInit(&head1);
		LinkListInit(&head2);

		//空链表
		LinkListNode* new_head = LinkListMerge(head1,head2);
		LinkListPrint(new_head,"打印空链表\n");

		//打印链表1
		LinkListPushBack(&head1,'a');
		LinkListPushBack(&head1,'b');
		LinkListPushBack(&head1,'c');
		new_head = LinkListMerge(head1,head2);
		LinkListPrint(new_head,"打印链表1\n");

		//打印链表2
		LinkListPushBack(&head2,'b');
		LinkListPushBack(&head2,'c');
		LinkListPushBack(&head2,'d');
		new_head = LinkListMerge(head1,head2);
		LinkListPrint(new_head,"打印排序后的链表\n");
		
	}	

	void TestFindMidNode()
	{

		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		//空链表
		LinkListNode* mid_node = LinkListFindMidNode(head);
		printf("%p\n",mid_node);

		//只有一个节点的链表
		LinkListPushBack(&head,'a');
		mid_node = LinkListFindMidNode(head);
		printf("expect a,actually %c\n",mid_node->data);
		//多个节点的链表
		LinkListPushBack(&head,'d');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'b');
		mid_node = LinkListFindMidNode(head);
		printf("expect d,actually %c\n",mid_node->data);
		return;
	}
	void TestFindMidNode1()
	{

		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		//空链表
		LinkListNode* mid_node = LinkListFindMidNode1(head);
		printf("%p\n",mid_node);

		//只有一个节点的链表
		LinkListPushBack(&head,'a');
		mid_node = LinkListFindMidNode1(head);
		printf("expect a,actually %c\n",mid_node->data);
		//多个节点的链表
		LinkListPushBack(&head,'d');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'b');
		mid_node = LinkListFindMidNode1(head);
		printf("expect c,actually %c\n",mid_node->data);
		return;
	}
	void TestFindLastKNode()
	{

		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		//空链表
		LinkListNode* K_node = LinkListFindLastKNode(head,0);
		printf("%p\n",K_node);

		LinkListPushBack(&head,'d');
		K_node = LinkListFindLastKNode(head,1);
		printf("expect d,actually %c\n",K_node->data);
		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'e');
		K_node = LinkListFindLastKNode(head,2);
		printf("expect c,actually %c\n",K_node->data);
	}

void TestEraseLastKNode()
{
	
		TEST_HANDLE;
		LinkListNode* head;
		LinkListInit(&head);

		//空链表
		LinkListEraseLastKNode(&head,2);
		LinkListPrint(head,"打印空链表\n");

		LinkListPushBack(&head,'d');
		LinkListEraseLastKNode(&head,1);
		LinkListPrint(head,"删除第一个节点\n");

		LinkListPushBack(&head,'a');
		LinkListPushBack(&head,'c');
		LinkListPushBack(&head,'e');
		LinkListPrint(head,"头插三个元素\n");
		LinkListEraseLastKNode(&head,4);
		LinkListPrint(head,"删除不是链表中的节点");

		LinkListEraseLastKNode(&head,0);
		LinkListPrint(head,"删除节点c\n");
		return;
}

void TestHasCircle()
{
	TEST_HANDLE;
	LinkListNode* head;
	LinkListInit(&head);

	int circle = LinkListHasCircle(head);
	printf("expect 0,actually %d\n",circle);
//	LinkListPushBack(&head,'a');
//	head->next = head;
//	circle = LinkListHasCircle(head);
//	printf("expect 1,actually %d\n",circle);


	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'e');
	LinkListPushBack(&head,'f');
	LinkListPushBack(&head,'g');
	circle = LinkListHasCircle(head);
	printf("expect 0,actually %d\n",circle);

	LinkListNode* pos = LinkListFind(head,'g');
	pos->next = head->next->next;
	circle = LinkListHasCircle(head);
	printf("expect 1,actually %d\n",circle);
	return;

}
void TestCircleLength()
{
	TEST_HANDLE;
	LinkListNode* head;
	LinkListInit(&head);

	size_t length = LinkListCircleLength(head);
	printf("expect 0,actually %d\n",length);

	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'e');
	LinkListPushBack(&head,'f');
	LinkListPushBack(&head,'g');
	length = LinkListCircleLength(head);
	printf("expect 0,actually %d\n",length);

	LinkListNode* pos = LinkListFind(head,'g');
	pos->next = head->next->next;
	length = LinkListCircleLength(head);
	printf("expect 3,actually %d\n",length);
	return;


}
void TestCircleEntry()
{

	TEST_HANDLE;
	LinkListNode* head;
	LinkListInit(&head);

	LinkListNode* entry_node = LinkListCircleEntry(head);
	printf("expect null,actually %p\n",entry_node);

	LinkListPushBack(&head,'a');
	LinkListPushBack(&head,'c');
	LinkListPushBack(&head,'e');
	LinkListPushBack(&head,'f');
	LinkListPushBack(&head,'g');
	entry_node = LinkListCircleEntry(head);
	printf("expect null,actually %p\n",entry_node);

	LinkListNode* pos = LinkListFind(head,'g');
	pos->next = head->next->next;
	entry_node = LinkListCircleEntry(head);
	printf("expect e,actually %c\n",entry_node->data);
	return;
}

void TestCrossPos()
{
	TEST_HANDLE;
	LinkListNode* head1;
	LinkListNode* head2;
	LinkListInit(&head1);
	LinkListInit(&head2);

	LinkListNode* cross_node = LinkListCrossPos(head1,head2);
	printf("except null,actually %p\n",cross_node);

	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'d');
	
	LinkListPushBack(&head2,'e');
	LinkListPushBack(&head2,'f');

	cross_node = LinkListCrossPos(head1,head2);
	printf("except null,actually %p\n",cross_node);

	LinkListNode* pos = LinkListFind(head1,'c');
	head2->next->next = pos;
	cross_node = LinkListCrossPos(head1,head2);
	printf("expect c,actually %c\n",cross_node->data);
	return;

}
void TestHasCross()
{
	
	TEST_HANDLE;
	LinkListNode* head1;
	LinkListNode* head2;
	LinkListInit(&head1);
	LinkListInit(&head2);

	int ret = LinkListHasCross(head1,head2);
	printf("except 0,actually %d\n",ret);

	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'d');
	
	LinkListPushBack(&head2,'e');
	LinkListPushBack(&head2,'f');

	ret = LinkListHasCross(head1,head2);
	printf("except 0,actually %d\n",ret);

	LinkListNode* pos = LinkListFind(head1,'c');
	head2->next->next = pos;
	ret = LinkListHasCross(head1,head2);
	printf("expect 1,actually %d\n",ret);
	return;
}

void TestHasCrossWithCircle()
{
	TEST_HANDLE;
	LinkListNode* head1;
	LinkListNode* head2;
	LinkListInit(&head1);
	LinkListInit(&head2);

	int ret = LinkListHasCrossWithCircle(head1,head2);
	printf("except 0,actually %d\n",ret);

	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'d');
	
	LinkListPushBack(&head2,'e');
	LinkListPushBack(&head2,'f');

	ret = LinkListHasCrossWithCircle(head1,head2);
	printf("except 0,actually %d\n",ret);//不带环链表不相交

	LinkListNode* pos_c = LinkListFind(head1,'c');
	head2->next->next = pos_c;
	ret = LinkListHasCrossWithCircle(head1,head2);
	printf("expect 1,actually %d\n",ret);//不带环链表相交

	LinkListNode* pos_d = LinkListFind(head1,'d');
	pos_d->next = pos_d;
	ret = LinkListHasCrossWithCircle(head1,head2);
	printf("expect 1,actually %d\n",ret);//环外相交

	pos_d->next = head1->next;
	ret = LinkListHasCrossWithCircle(head1,head2);
	printf("expect 1,actually %d\n",ret);//环内相交

	head2->next->next = head2->next;
	ret = LinkListHasCrossWithCircle(head1,head2);
	printf("expect 0,actually %d\n",ret);//两带环链表不相交

	head2->next->next == NULL;
	ret = LinkListHasCrossWithCircle(head1,head2);
	printf("expect 0,actually %d\n",ret);//一个带环，一个不带环
	return;
}

void TestCrossPosWithCircle()
{
	TEST_HANDLE;
	LinkListNode* head1;
	LinkListNode* head2;
	LinkListInit(&head1);
	LinkListInit(&head2);

	LinkListNode* ret = LinkListCrossPosWithCircle(head1,head2);
	printf("except null,actually %p\n",ret);

	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'d');
	
	LinkListPushBack(&head2,'e');
	LinkListPushBack(&head2,'f');

	ret = LinkListCrossPosWithCircle(head1,head2);
	printf("except null,actually %p\n",ret);//不带环链表不相交

	LinkListNode* pos_c = LinkListFind(head1,'c');
	head2->next->next = pos_c;
	ret = LinkListCrossPosWithCircle(head1,head2);
	printf("expect c,actually %c\n",ret->data);//不带环链表相交

	LinkListNode* pos_d = LinkListFind(head1,'d');
	pos_d->next = pos_d;
	ret = LinkListCrossPosWithCircle(head1,head2);
	printf("expect c,actually %c\n",ret->data);//环外相交

	pos_d->next = head1->next;
	ret = LinkListCrossPosWithCircle(head1,head2);
	printf("expect b,actually %c\n",ret->data);//环内相交

	head2->next->next = head2->next;
	ret = LinkListCrossPosWithCircle(head1,head2);
	printf("expect null,actually %p\n",ret);//两带环链表不相交

	head2->next->next == NULL;
	ret = LinkListCrossPosWithCircle(head1,head2);
	printf("expect null,actually %p\n",ret);//一个带环，一个不带环
	return;
}

void TestUnionSet()
{
	TEST_HANDLE;
	LinkListNode* head1;
	LinkListNode* head2;
	LinkListInit(&head1);
	LinkListInit(&head2);

	//两链表为空
	LinkListNode* new_head = LinkListUnionSet(head1,head2);
	printf("expect null,actually %p\n",new_head);

	
	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'c');
	LinkListPushBack(&head1,'d');

	LinkListPushBack(&head2,'e');
	LinkListPushBack(&head2,'f');
	LinkListPushBack(&head2,'g');
	LinkListPushBack(&head2,'h');

	new_head = LinkListUnionSet(head1,head2);
	LinkListPrint(new_head,"两链表的交集\n");
	return;
}

void TestUnionSetEx()
{
	TEST_HANDLE;
	LinkListNode* head1;
	LinkListNode* head2;
	LinkListInit(&head1);
	LinkListInit(&head2);

	//两链表为空
	LinkListNode* new_head = LinkListUnionSetEx(head1,head2);
	printf("expect null,actually %p\n",new_head);

	
	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head2,'e');
	new_head = LinkListUnionSetEx(head1,head2);
	printf("expect null,actually %p\n",new_head);

	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'e');
	LinkListPushBack(&head1,'f');

	LinkListPushBack(&head2,'f');
	LinkListPushBack(&head2,'g');
	LinkListPushBack(&head2,'h');

	new_head = LinkListUnionSetEx(head1,head2);
	LinkListPrint(new_head,"两链表的交集\n");
	LinkListPushBack(&head1,'f');
	new_head = LinkListUnionSetEx(head1,head2);
	LinkListPrint(new_head,"两链表的交集\n");
	return;
}

void TestUnionSetNoSort()
{
	TEST_HANDLE;
	LinkListNode* head1;
	LinkListNode* head2;
	LinkListInit(&head1);
	LinkListInit(&head2);

	//两链表为空
	LinkListNode* new_head = LinkListUnionSetNoSort(head1,head2);
	printf("expect null,actually %p\n",new_head);

	
	LinkListPushBack(&head1,'a');
	LinkListPushBack(&head2,'e');
	new_head = LinkListUnionSetNoSort(head1,head2);
	printf("expect null,actually %p\n",new_head);

	LinkListPushBack(&head1,'d');
	LinkListPushBack(&head1,'b');
	LinkListPushBack(&head1,'a');

	LinkListPushBack(&head2,'a');
	LinkListPushBack(&head2,'c');
	LinkListPushBack(&head2,'a');

	new_head = LinkListUnionSetNoSort(head1,head2);
	LinkListPrint(new_head,"两链表的交集\n");
	LinkListPushBack(&head1,'f');
	new_head = LinkListUnionSetNoSort(head1,head2);
	LinkListPrint(new_head,"两链表的交集\n");
	return;
}

//typedef ComplexType char;
//typedef struct ComplexNode
//{
//	ComplexType data;
//	struct ComplexNode* next;
//	struct ComplexNode* random;
//}ComplexNode;

void ComplexListPrint(ComplexNode* head,const char* arr)
{
	printf("%s\n",arr);
	ComplexNode* cur = head;
	while(cur != NULL)
	{
		printf("%c ",cur->data);
		cur = cur->next;
	}
	printf("\n");
	cur = head;
	while(cur != NULL)
	{
		if(cur->random == NULL)
		{
			printf("[%p] ",cur->random);
		}
		else
		{
			printf("%c[%p] ",cur->random->data,cur->random);
		}
		cur = cur->next;
	}
	printf("\n");
	return;
}

void TestCopyComplexList()
{
	TEST_HANDLE;
	ComplexNode* a= CreateComplexNode('a');
	ComplexNode* b= CreateComplexNode('b');
	ComplexNode* c= CreateComplexNode('c');
	ComplexNode* d= CreateComplexNode('d');
	a->next = b;
	b->next = c;
	c->next = d;
	a->random = c;
	b->random = a;
	c->random = NULL;
	d->random = d;
	ComplexNode* new_head = CopyComplexList(a);

	ComplexListPrint(a,"打印复杂链表\n");
	return;
}

void TestCopyComplexListEx()
{
	TEST_HANDLE;
	ComplexNode* a= CreateComplexNode('a');
	ComplexNode* b= CreateComplexNode('b');
	ComplexNode* c= CreateComplexNode('c');
	ComplexNode* d= CreateComplexNode('d');
	a->next = b;
	b->next = c;
	c->next = d;
	a->random = c;
	b->random = a;
	c->random = NULL;
	d->random = d;
	ComplexNode* new_head = CopyComplexListEx(a);

	ComplexListPrint(a,"打印复杂链表\n");
	return;
}

int main()
{
	TestInit();
	TestPushBack();
	TestPopBack1();
	TestPopBack2();
	TestPushFront();
	TestPopFront();
	TestFind();
	TestInsert();
	TestInsertEx();
	TestInsertAfter();
	TestErase();
	TestErase2();
	TestRemove();
	TestRemoveAll();
	TestRemoveAllEx();
	TestEmpty();
	TestSize();
	TestReversePrint();
	TestJosephCircle();
	TestReverse();
	TestReverse1();
	TestBubbleSort();
	TestBubbleSort1();
	TestMerge();
	TestFindMidNode();
	TestFindMidNode1();
	TestFindLastKNode();
	TestEraseLastKNode();
	TestHasCircle();
	TestCircleLength();
	TestCircleEntry();
	TestCrossPos();
	TestHasCross();
	TestHasCrossWithCircle();
	TestCrossPosWithCircle();
	TestUnionSet();
	TestUnionSetEx();
	TestUnionSetNoSort();
	TestCopyComplexList();
	TestCopyComplexListEx();
	return 0;
}
