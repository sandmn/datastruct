

#include"hash_link.h"
#include<stdio.h>

//哈希表的初始化
void HashInit(HashTable* ht,HashFunc func)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }

    ht->size = 0;
    ht->func = func;
    size_t i = 0;
    for(;i < HASHMAXSIZE;++i)
    {
        ht->data[i].stat = Empty;
    }
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

    ht->size = 0;
    ht->func = NULL;
    return;
}

//向哈希表中插入元素
void HashInsert(HashTable* ht,KeyType key,ValType value)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }
    //首先判断哈希表中的元素个数是否达到负载因子，如果达到了，则插入失败
    if(ht->size >= 0.8*HASHMAXSIZE)
    {
        return;
    }
    //如果没有达到，
    //1. 根据key计算offset
    size_t offset = ht->func(key);

    while(1)
    {
        //2. 如果offset处的值为Empty，则将key和value的值插入到该处
        if(ht->data[offset].stat != Valid)
        {
            ht->data[offset].key = key;
            ht->data[offset].value = value;
            ht->data[offset].stat = Valid;
            break;
        }
        //3. 如果offset处的值为Valid,且该处的key值与要插入的key值相同，则插入失败
        else if(ht->data[offset].stat == Valid && ht->data[offset].key == key)
        {
            //插入失败
            return;
        }
        //4. 否则，++offset,继续判断offset处的值
        else
        {
            ++offset;
        //   如果offset的值等于HASHMAXSIZE,则将offset赋值为0
            if(offset >= HASHMAXSIZE)
            {
                offset = 0;
            }
        }
    }
    ++ht->size;
    return;
}
//在哈希表中查找元素
int HashFind(HashTable* ht,KeyType key,ValType* value)
{
    if(ht == NULL || value == NULL)
    {
        //非法输入
        return 0;
    }

    //1. 如果哈希表为空，则查找失败
    if(ht->size == 0)
    {
        return 0;
    }
    //2. 根据key值计算offset
    size_t offset = ht->func(key);
    while(1)
    {
        //3. 如果offset处的key值等于所给的key值，则返回value值
        if(ht->data[offset].stat == Valid && ht->data[offset].key == key)
        {
            *value = ht->data[offset].value;
            return 1;
        }
        //4. 如果offset处的状态为Empty,则说明要查找的元素不存在，查找失败
        else if(ht->data[offset].stat == Empty)
        {
            return 0;
        }
        //5. 如果，offset处的状态不为Empty，且不等与key，则offset++,往后遍历
        else
        {
            ++offset;
            if(offset >= HASHMAXSIZE)
            {
                offset = 0;
            }
        }
    }
}
//删除哈希表中的元素
void HashDelete(HashTable* ht,KeyType key)
{
    if(ht == NULL)
    {
        //非法输入
        return;
    }

    //1. 如果哈希表为空，则删除失败
    if(ht->size == 0)
    {
        return;
    }
    //2. 根据key计算offset
    size_t offset = ht->func(key);
    while(1)
    {
        //3. 如果offset处的值为key值，如果将该处的状态置为Empty，则在查找与该处下标相同的key值时就会查找失败
        //   但有可能要查找的元素在该下标的后面。所以不能将该处的状态设置为Empty
        //   所以在设置一个状态Delete，只有该处的状态为Empty时才会查找失败，
        //   当该处的状态不是Valid时才能进行插入
        if(ht->data[offset].stat == Valid && ht->data[offset].key == key)
        {
            ht->data[offset].stat = Deleted;
            break;
        }
        //4. 如果该处的状态为Empty，则哈希表中不存在该元素，删除失败
        else if(ht->data[offset].stat == Empty)
        {
            return;
        }
        //5. 否则，++offset,在往后进行遍历
        else
        {
            ++offset;
            if(offset >= HASHMAXSIZE)
            {
                offset = 0;
            }
        }
    }
    //6. --size
    --ht->size;
    return;
}
////////////////////////////////
//测试代码
//////////////////////////////////

#include<stdio.h>

#define TEST_HANDLE printf("=============%s==============\n",__FUNCTION__)

//打印哈希表
void HashPrint(HashTable* ht,const char* msg)
{
    printf("%s\n",msg);
    size_t i = 0;
    for(;i < HASHMAXSIZE;++i)
    {
        if(ht->data[i].stat == Valid)
        {
            printf("%d:[%d][%d]  ",i,ht->data[i].key,ht->data[i].value);
        }
    }
    printf("\n");
    return;
}


//哈希函数定义
size_t func(KeyType key)
{
    return key % HASHMAXSIZE;
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
 //   for(; i < HASHMAXSIZE;++i)
 //   {
 //       printf("%d ",ht.data[i].stat);
 //   }
    return;
}

//测试销毁
void TestDestroy()
{
    TEST_HANDLE;
    HashTable ht;
    HashInit(&ht,func);
    HashDestroy(&ht);
    printf("expect 0,actual %d\n",ht.size);
    printf("expect null,actual %p\n",ht.func);
    return;
}

//测试插入函数
void TestInsert()
{
    TEST_HANDLE;
    HashTable ht;
    HashInit(&ht,func);
    HashInsert(&ht,1,1);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,3);
    HashInsert(&ht,1001,5);
    HashInsert(&ht,1002,4);
    HashInsert(&ht,3,5);
    HashInsert(&ht,1003,6);
    HashPrint(&ht,"打印哈希表");
    return;
}

//测试查找函数
void TestFind()
{
    TEST_HANDLE;

    int ret;
    ValType value;
    ret = HashFind(NULL,1,&value);//测试非法输入
    printf("expect 0,actually %d\n",ret);

    HashTable ht;
    HashInit(&ht,func);

    ret = HashFind(&ht,1,&value);//测试空哈希表
    printf("expect 0,actually %d\n",ret);

    HashInsert(&ht,1,1);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,3);
    HashInsert(&ht,1001,5);
    HashInsert(&ht,1002,4);
    HashInsert(&ht,3,5);
    HashInsert(&ht,1003,6);

    ret = HashFind(&ht,5,&value);//测试找不到的情况
    printf("expect 0,actually %d\n",ret);
    
    ret = HashFind(&ht,2,&value);//测试一次就找到的情形
    printf("expect 1,actually %d\n",ret);
    printf("expect 2,actually %d\n",value);

    ret = HashFind(&ht,1001,&value);//测试找几次才找到的情形
    printf("expect 1,actually %d\n",ret);
    printf("expect 3,actually %d\n",value);

    return;


}

//测试删除函数
void TestDelete()
{
    TEST_HANDLE;
    HashDelete(NULL,2);//测试非法输入

    HashTable ht;
    HashInit(&ht,func);

    HashDelete(&ht,5);//测试删除空表

    HashInsert(&ht,1,1);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,3);
    HashInsert(&ht,1001,5);
    HashInsert(&ht,1002,4);
    HashInsert(&ht,3,5);
    HashInsert(&ht,1003,6);

    HashDelete(&ht,2);
    HashPrint(&ht,"删除ke值为2的元素");//测试删除一次就找到的元素

    HashDelete(&ht,3);
    HashPrint(&ht,"删除ke值为3的元素");//测试删除找几次才找到的元素
    HashInsert(&ht,3,10);//在删除的位置新插入一个元素
    HashPrint(&ht,"新插入一个元素");//测试删除找几次才找到的元素

    HashDelete(&ht,5);
    HashPrint(&ht,"删除ke值为5的元素");//测试找不到的元素


}

int main()
{
    TestInit();
    TestDestroy();
    TestInsert();
    TestFind();
    TestDelete();
    return 0;
}
