
//顺序表的基本操作
#include "seqlist.h"


void SeqListInit(SeqList *seqlist)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	seqlist->size = 0;//将数组长度初始化为0
	return;
}


void SeqListPushBack(SeqList *seqlist,SeqListType value)
{
	//指针判空
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	//顺序表判满
	if(seqlist->size >= SeqListMaxSize)
	{
		//顺序表满
		return;
	}

	seqlist->data[seqlist->size] = value;
	seqlist->size++;
	return;
}


void SeqListPopBack(SeqList *seqlist)
{
	//指针判空
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	//顺序表判空
	if(seqlist->size == 0)
	{
		//顺序表为空
		return;
	}
	
	seqlist->size--;
	return;
}


void SeqListPushFront(SeqList *seqlist,SeqListType value)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}
    
	if(seqlist->size >= SeqListMaxSize)
	{
		//顺序表满
		return;
	}

	int i = seqlist->size;
	for(i = seqlist->size;i > 0;i--)
	{
		seqlist->data[i] = seqlist->data[i-1];
	}
	seqlist->data[0] = value;
	seqlist->size++;
	return;
}


void SeqListPopFront(SeqList *seqlist)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	if(seqlist->size == 0)
	{
		//顺序表已空
		return;
	}
	
	int i = 0;
	for(i = 0;i <= (seqlist->size) - 2;i++)
	{
		seqlist->data[i] = seqlist->data[i+1];
	}
	seqlist->size--;
	return;
}


void SeqListInsert(SeqList *seqlist,int Pos,SeqListType value)
{
	//指针判空
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	//顺序表判满
	if(seqlist->size == SeqListMaxSize)
	{
		//顺序表已满
		return;
	}

	//判断插入位置是否合法
	if(Pos < 0 || Pos > seqlist->size)
	{
		//插入位置不合法
		return;
	}

	int i = seqlist->size;
	for(;i > Pos;i--)
	{
		seqlist->data[i] = seqlist->data[i-1];
	}
	seqlist->data[Pos] = value;
	seqlist->size++;
	return;
}
void SeqListGet(SeqList *seqlist,int Pos,SeqListType *c)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	if(seqlist->size == 0)
	{
		//顺序表已空
		return;
	}

	if(Pos < 0 || Pos > seqlist->size-1)
	{
		//读取位置不合法
		return;
	}
	*c = seqlist->data[Pos];
	return;
}

void SeqListSet(SeqList *seqlist,int Pos,SeqListType value)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	if(seqlist->size == 0)
	{
		//顺序表已空
		return;
	}
	
	if(Pos < 0 || Pos > seqlist->size - 1)
	{
		//修改位置不合法
		return;
	}

	seqlist->data[Pos] = value;
	return;
}
void SeqListFind(SeqList *seqlist,SeqListType value,int *Pos)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}
	
	if(seqlist->size == 0)
	{
		//顺序表为空
		return;
	}

	int i = 0;
	for(i = 0;i < seqlist->size;i++)
	{
		if(seqlist->data[i] == value)
		{
			*Pos = i;
			return;
		}
	}
	*Pos = -1;
	return;
}


void SeqListErase(SeqList *seqlist,int Pos)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	if(seqlist->size == 0)
	{
		//顺序表为空
		return;
	}

	if(Pos < 0 || Pos > seqlist->size - 1)
	{
		//删除位置不合法
		return;
	}

	int i = Pos;
	for(i = Pos;i < seqlist->size - 1;i++)
	{
		seqlist->data[i] = seqlist->data[i+1];
	}
	seqlist->size--;
	return;
}

//删除指定的元素，如果有重复，只删除一个
void SeqListRemove(SeqList* seqlist, SeqListType to_delete)
{
	//指针判空
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	int pos = -1;
	SeqListFind(seqlist,to_delete,&pos);
	SeqListErase(seqlist,pos);
	return;
}

//删除所有重复的指定元素
void SeqListRemoveAll(SeqList* seqlist, SeqListType to_delete)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	int pos = -1;
	SeqListFind(seqlist,to_delete,&pos);
	while(pos != -1)
	{
		SeqListErase(seqlist,pos);
		SeqListFind(seqlist,to_delete,&pos);
	}
	return;
}


void SeqListRemoveAllEx(SeqList* seqlist, SeqListType to_delete)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	if(seqlist->size == 0)
	{
		//顺序表为空
		return;
	}

	//统计要删除元素的重复个数
//	SeqListType tmp[seqlist->size];
	int count = 0;
	int cur = 0;
	for(cur = 0;cur < seqlist->size;++cur)
	{
		if(seqlist->data[cur] != to_delete)
		{
			seqlist->data[count++] = seqlist->data[cur];

		//	tmp[count] = cur;//存储要删除元素的下标
		//	count++;
		}
		else
		{
			seqlist->size--;
		}
	}
	return;

//	//根据数组中的下标一个个删除
//	cur = 0;
//	for(cur = 0;cur < count;++cur)
//	{
//		SeqListRemove(seqlist,to_delete);
//	}


}

//统计顺序表中的元素个数
int SeqListSize(SeqList* seqlist)
{
	if(seqlist == NULL)
	{
		//非法输入
		return -1;
	}
	return seqlist->size;
}

//判断顺序表是否为空
int SeqListEmpty(SeqList* seqlist)
{
	if(seqlist == NULL)
	{
		//非法输入
		return -1;
	}
	if(seqlist->size == 0)
	{
		return 1;//数组元素个数为0，返回1
	}
	else
	{
		return 0;//数组元素个数不为0，返回0
	}
}
//交换函数
void swap(SeqListType* a,SeqListType* b)
{
	SeqListType tmp = *a;
	*a = *b;
	*b = tmp;
}
//冒泡排序顺序表
void SeqListBubbleSort(SeqList* seqlist)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	if(seqlist->size <= 1)
	{
		return;
	}

	int count = 0;
	for(count = 0;count < seqlist->size-1;++count)
	{
		int cur = 0;
		int flag = 0;
		for(cur = 0;cur < seqlist->size-count-1;++cur)
		{
			if(seqlist->data[cur] > seqlist->data[cur+1])
			{
				swap(&seqlist->data[cur],&seqlist->data[cur+1]);
				flag = 1;
			}
		}
		if(flag == 0)
		{
			break;
		}
	}
	return;
}

int cmp_char(SeqListType a,SeqListType b)
{
	if(a > b)
	{
		return 1;
	}
	else if(a == b)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

void SeqListBubbleSortEx(SeqList* seqlist,Cmp cmp)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	if(seqlist->size <= 1)
	{
		return;
	}

	int count = 0;
	for(count = 0;count < seqlist->size-1;++count)
	{
		int flag = 0;
		int cur = 0;
		for(cur = 0;cur <seqlist->size-1-count;++cur)
		{
			if(cmp(seqlist->data[cur],seqlist->data[cur+1]) > 0)
			{
				swap(&seqlist->data[cur],&seqlist->data[cur+1]);
				flag = 1;
			}
		}
		if(flag == 0)
		{
			break;
		}
	}
}


void SeqListSelectSort(SeqList* seqlist,Cmp cmp)
{
	if(seqlist == NULL)
	{
		//非法输入
		return;
	}

	if(seqlist->size <= 1)
	{
		return;
	}

	int bound = 0;
	for(bound = 0;bound < seqlist->size-1;++bound)
	{
		int cur = bound + 1;
		for(;cur < seqlist->size;++cur)
		{
			if(cmp(seqlist->data[bound],seqlist->data[cur]))
			{
				swap(&seqlist->data[bound],&seqlist->data[cur]);
			}
		}
	}
}
///////////////////////////////////////
//测试代码
//////////////////////////////////////

#include<stdio.h>
//#include<stdlib.h>
#define TEST_HANDLE printf("\n================%s==============\n",__FUNCTION__)

void TestInit()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);

void TestInit()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListInit(&seqlist);
	printf("expect 0,actually %d\n",seqlist.size);
	return;
}
void SeqListPrint(SeqList *seqlist,const char *str)
{
	printf(str);
	int i = 0;
	for(i = 0;i<seqlist->size;i++)
	{
		printf("%c ",seqlist->data[i]);
	}
	printf("\n");
	return;
}

void TestPushBack()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'d');
	SeqListPrint(&seqlist,"尾插插入四个元素\n");
	return;
}

void TestPopBack()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushBack(&seqlist,'a');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'d');
	
	SeqListPopBack(&seqlist);
	SeqListPopBack(&seqlist);

	SeqListPrint(&seqlist,"尾删两个元素\n");
}

void TestPushFront()
{

	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'c');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"头插插入四个元素\n");
	return;
}

void TestPopFront()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'c');
	SeqListPushFront(&seqlist,'d');

	SeqListPopFront(&seqlist);
	SeqListPopFront(&seqlist);

	SeqListPrint(&seqlist,"头删两个元素\n");
	return;
}

void TestInsert()
{

	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'c');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	SeqListInsert(&seqlist,2,'o');
	SeqListPrint(&seqlist,"在下标为2的位置插入元素\n");
	return;
}

void TestGet()
{	
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'c');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	char c;
	SeqListGet(&seqlist,2,&c);
	printf("下标为2的数组元素为：%c\n",c);
	return;
}

void TestSet()
{
	
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'c');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	SeqListSet(&seqlist,3,'m');
	SeqListPrint(&seqlist,"修改下标为3的数组元素为m\n");
	SeqListSet(&seqlist,4,'n');
	SeqListPrint(&seqlist,"修改下标为4的数组元素为n\n");
	return;
}

void TestFind()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'c');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	int Pos = 0;
	SeqListFind(&seqlist,'a',&Pos);
	printf("a所在的下标为%d\n",Pos);

	SeqListFind(&seqlist,'m',&Pos);
	printf("m所在的下标为%d\n",Pos);
	return;
}

void TestErase()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'c');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	SeqListErase(&seqlist,3);
	SeqListPrint(&seqlist,"删除下标为3的元素\n");

	SeqListErase(&seqlist,2);
	SeqListPrint(&seqlist,"删除下标为2的元素\n");
	return;
}

void TestRemove()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'c');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	SeqListRemove(&seqlist,'b');
	SeqListPrint(&seqlist,"删除元素‘b'\n");

	SeqListRemove(&seqlist,'m');
	SeqListPrint(&seqlist,"删除元素‘m'\n");
	return;
}

void TestRemoveAll()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	SeqListRemoveAll(&seqlist,'a');
	SeqListPrint(&seqlist,"删除所有的a\n");

	SeqListRemoveAll(&seqlist,'m');
	SeqListPrint(&seqlist,"删除所有的m\n");
	return;
}

void TestRemoveAllEx()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	SeqListRemoveAll(&seqlist,'a');
	SeqListPrint(&seqlist,"删除所有的a\n");

	SeqListRemoveAll(&seqlist,'m');
	SeqListPrint(&seqlist,"删除所有的m\n");
	return;
}
void TestSize()
{

	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);
	printf("expect 0,actually %d\n",SeqListSize(&seqlist));

	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	printf("expect 4,actually %d\n",SeqListSize(&seqlist));
	return;
}

void TestEmpty()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);

	printf("expect 1,actually %d\n",SeqListEmpty(&seqlist));

	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'b');
	SeqListPushFront(&seqlist,'a');
	SeqListPushFront(&seqlist,'d');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	printf("expect 0,actually %d\n",SeqListEmpty(&seqlist));
	return;
}

void TestBubbleSort()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);

	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'a');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	SeqListBubbleSort(&seqlist);
	SeqListPrint(&seqlist,"冒泡排序后的元素\n");
	return;
}

void TestBubbleSortEx()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);

	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'a');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	SeqListBubbleSortEx(&seqlist,cmp_char);
	SeqListPrint(&seqlist,"冒泡排序后的元素\n");
	return;

}

void TestSelectSort()
{
	TEST_HANDLE;
	SeqList seqlist;
	SeqListInit(&seqlist);

	SeqListPushBack(&seqlist,'d');
	SeqListPushBack(&seqlist,'c');
	SeqListPushBack(&seqlist,'b');
	SeqListPushBack(&seqlist,'a');
	SeqListPrint(&seqlist,"已插入的四个元素\n");

	SeqListSelectSort(&seqlist,cmp_char);
	SeqListPrint(&seqlist,"冒泡排序后的元素\n");
	return;
}

int main()
{
	TestInit();
	TestPushBack();
	TestErase();
	TestRemove();
	TestRemoveAll();
	TestRemoveAllEx();
	TestSize();
	TestEmpty();
	TestBubbleSort();
	TestBubbleSortEx();
	TestSelectSort();
	return 0;
}
