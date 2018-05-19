#include"hash_bucket.h"
#include<stdlib.h>
#include<stdio.h>

//初始化哈希表
void HashInit(HashTable* ht,HashFunc func)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    //哈希表中的元素有两种表示方法：
    //1. 直接存放节点的指针，表示不带头节点的链表，此时，初始化时，将所有数组元素即链表头指针置为NULL即可
    //2. 存放节点，表示带头节点的链表。初始化时，将头节点的指针域置为NULL，数据域任意
    //此处，选用不带头节点的链表
    ht->size = 0;
    ht->func = func;
    size_t i = 0;
    for(;i < HASHMAXSIZE;++i)
    {
        ht->data[i] = NULL;
    }
    return;
}

//销毁节点
void DestroyNode(HashElemNode* node)
{
    free(node);
    return;
}

//销毁哈希表
void HashDestroy(HashTable* ht)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    //遍历哈希表中的每个元素所表示的单链表，将各个单链表中的元素节点进行释放
    size_t i = 0 ;
    for(;i < HASHMAXSIZE;++i)
    {
        HashElemNode* next = NULL;
        HashElemNode* cur = ht->data[i];
        while(cur != NULL)
        {
            next = cur->next;
            DestroyNode(cur);
            cur = next;
        }
    }
    ht->size = 0;
    ht->func = NULL;
    return;
}

//创建节点
HashElemNode* CreateNode(KeyType key,ValType value)
{
    HashElemNode* new_node = (HashElemNode*)malloc(sizeof(HashElemNode));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

HashElemNode* HashFind(HashElemNode* head,KeyType key)
{
    HashElemNode* cur = head;
    while(cur != NULL)
    {
        if(cur->key == key)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

//向哈希表中插入元素
void HashInsert(HashTable* ht,KeyType key,ValType value)
{
    if(ht == NULL)
    {
        //非法输入
        return;    
    }
    //1. 如果哈希表中链表的平均长度大于等于10，则插入失败
    if(ht->size >= 10*HASHMAXSIZE)
    {
        return;
    }
    //2. 根据key值计算offset
    size_t offset = ht->func(key);
    //3. 查找offset处的链表中有无要插入的key值，如果有，则插入失败
    HashElemNode* to_find = HashFind(ht->data[offset],key);
    if(to_find != NULL)//如果在哈希表中存在该元素
    {
        //插入失败
        return;
    }
    //4. 如果没有，则对该处的链表进行头插
    HashElemNode* new_node = CreateNode(key,value);
    new_node->next = ht->data[offset];
    ht->data[offset] = new_node;
    //5. ++size
    ++ht->size;
    return;
}
//在哈希表中中查找元素
int HashFindEx(HashTable* ht,KeyType key,ValType* value)
{
    if(ht == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }
    if(ht->size == 0)
    {
        //空表
        return 0;
    }

    //1. 根据key值计算offset值
    size_t offset = ht->func(key);
    //2. 在offset下标处的链表中查找指定的key值
    HashElemNode* to_find = HashFind(ht->data[offset],key);
    if(to_find == NULL)
    {
        return 0;
    }
    else
    {
        *value = to_find->value;
        return 1;
    }

}

int HashFindEx1(HashElemNode* head,KeyType key,HashElemNode** cur,HashElemNode** pre)
{
    HashElemNode* cur_node = head;
    HashElemNode* pre_node = NULL;
    while(cur_node != NULL)
    {
        if(cur_node->key == key)
        {
            *cur = cur_node;
            *pre = pre_node;
            return 1;
        }
        pre_node = cur_node;
        cur_node = cur_node->next;
    }
    return 0;
}

//在哈希表中删除元素
void HashDelete(HashTable* ht,KeyType key)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    if(ht->size == 0)
    {
        //空表
        return;
    }
    //1. 根据key计算offset
    size_t offset = ht->func(key);
    //2. 在offset处找到key值的指针，及其前一个节点处的指针
    HashElemNode* cur_node;
    HashElemNode* pre_node;
    int ret = HashFindEx1(ht->data[offset],key,&cur_node,&pre_node);
    if(ret == 0)
    {
        //没找到
        return;
    }
    if(ret == 1)//如果找到要删除的节点
    {
        if(pre_node == NULL)//如果要删除的节点为头节点
        {
            ht->data[offset] = cur_node->next;
        }
        else 
        {
            pre_node->next = cur_node->next;
        }
    }
    //3. 释放key处的节点
    DestroyNode(cur_node);
    //--size
    --ht->size;
    return;
}
////////////////////////////
//测试代码
////////////////////////////


#include<stdio.h>
#define TEST_HANDLE printf("===============%s===============\n",__FUNCTION__)

//定义哈希函数
size_t func(KeyType key)
{
    return key % HASHMAXSIZE;
}

//打印哈希表中的非空链表
void HashPrint(HashTable* ht,const char* msg)
{
    printf("%s\n",msg);
    size_t i = 0;
    for(;i < HASHMAXSIZE;++i)
    {
        if(ht->data[i] != NULL)
        {
            printf("%d:",i);
        }
        HashElemNode* cur = ht->data[i];
        while(cur != NULL)
        {
            printf("[%d][%d] ",cur->key,cur->value);
            cur = cur->next;
        }
        if(ht->data[i] != NULL)
        {
            ;printf("\n");
        }
    }
}

//测试初始化
void TestInit()
{
    TEST_HANDLE;
    HashTable ht;
    HashInit(&ht,func);
    printf("expect 0,actually %d\n",ht.size);
    printf("expect %p,actually %p\n",func,ht.func);
//    size_t i = 0;
 //   for(;i < HASHMAXSIZE;++i)
 //   {
 //       printf("%p ",ht.data[i]);
 //   }
 //   printf("\n");
}

//测试销毁函数
void TestDestroy()
{
    TEST_HANDLE;
    HashTable ht;
    HashInit(&ht,func);
    HashDestroy(&ht);
    printf("expect 0,actually %d\n",ht.size);
    printf("expect null,actually %p\n",ht.func);

}

//测试插入函数
void TestInsert()
{
    TEST_HANDLE;
    HashTable ht;
    HashInit(&ht,func);

    //HashInsert(NULL,1,5);//测试非法输入

    HashInsert(&ht,1,1);
    HashInsert(&ht,1,5);
    HashInsert(&ht,1001,5);
    HashInsert(&ht,5,4);
    HashPrint(&ht,"向哈希表中插入元素");
    return;
}

//测试查找
void TestFindEx()
{
    TEST_HANDLE;
    HashTable ht;
    HashInit(&ht,func);

    int ret;
    ValType value;
    ret = HashFindEx(NULL,1,&value);//测试非法输入
    printf("expect 0,actually %d\n",ret);

    ret = HashFindEx(&ht,1,&value);//测试空表
    printf("expect 0,actually %d\n",ret);

    HashInsert(&ht,1,1);
    HashInsert(&ht,1,5);
    HashInsert(&ht,1001,5);
    HashInsert(&ht,5,4);

    ret = HashFindEx(&ht,1,&value);//测试找到的情形
    printf("expect 1,actually %d\n",ret);
    printf("expect 1,actually %d\n",value);

    ret = HashFindEx(&ht,4,&value);//测试找不到的情形
    printf("expect 0,actually %d\n",ret);

    return;
}

//测试删除节点
void TestDelete()
{
    TEST_HANDLE;
    HashDelete(NULL,1);//测试非法输入

    HashTable ht;
    HashInit(&ht,func);

    HashDelete(&ht,1);//测试删除空表

    HashInsert(&ht,1,1);
    HashInsert(&ht,1,5);
    HashInsert(&ht,1001,5);
    HashInsert(&ht,5,4);

    HashDelete(&ht,1);//测试删除链表的非头节点
    HashPrint(&ht,"删除key为1的节点");

    HashDelete(&ht,5);//测试删除链表的头节点
    HashPrint(&ht,"删除key为5的节点");

    HashDelete(&ht,4);//测试删除链表中不存在的节点
    HashPrint(&ht,"删除不存在的节点");

}

int main()
{
    TestInit();
    TestDestroy();
    TestInsert();
    TestFindEx();
    TestDelete();
    return 0;
}
