
#include"bloom_filter.h"
#include<stdlib.h>

//布隆过滤器的初始化
void BloomFilterInit(BloomFilter* bf,BloomFunc func1,BloomFunc func2)
{
    if(bf == NULL || func1 == NULL || func2 == NULL)
    {
        //非法输入
        return;
    }
    //对布隆过滤器中的位图进行初始化
    BitMapInit(&bf->bm,MAXSIZE);
    bf->bloomfunc[0] = func1;
    bf->bloomfunc[1] = func2;
    return;
}

//布隆过滤器的销毁
void BloomFilterDestroy(BloomFilter* bf)
{
    if(bf == NULL)
    {
        //非法输入
        return;
    }

    //将布隆过滤器中的成员：位图进行销毁即可
    BitMapDestroy(&bf->bm);

    bf->bloomfunc[0] = NULL;
    bf->bloomfunc[1] = NULL;
    return;
}

//布隆过滤器的插入
void BloomFilterInsert(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        //非法输入
        return;
    }
    //首先根据字符串哈希算法计算字符串对应的数字
    //然后将计算出的数字根据除留余数法转化为实际对应的比特位下标
    uint64_t bloomnum[FUNCMAXSIZE];
    int i = 0;
    for(;i < FUNCMAXSIZE;i++)
    {
        bloomnum[i] = bf->bloomfunc[i](str) % MAXSIZE;
    }
    //再将该下标插入到布隆过滤器中的位图中，直接调用位图的插入函数即可
    for(i = 0;i < FUNCMAXSIZE;i++)
    {
        BitMapSet(&bf->bm,bloomnum[i]);
    }
    //uint64_t bloomnum1 = bf->bloomfunc[0](str) % MAXSIZE;
    //uint64_t bloomnum2 = bf->bloomfunc[1](str) % MAXSIZE;
    ////再将该下标插入到布隆过滤器中的位图中，直接调用位图的插入函数即可

    //BitMapSet(&bf->bm,bloomnum1);
    //BitMapSet(&bf->bm,bloomnum2);
    return;
}
//在布隆过滤器中判断一个字符串是否存在
int BloomFilterTest(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        //非法输入
        return 0;
    }
    //首先根据字符串哈希算法计算字符串对应的数字
    //在根据该数字计算根据除留余数法计算比特位所在的下标
    uint64_t bloomnum[FUNCMAXSIZE];
    int i = 0;
    for(;i < FUNCMAXSIZE;i++)
    {
        bloomnum[i] = bf->bloomfunc[i](str)%MAXSIZE; 
    }
    //然后在布隆过滤器中的位图结构中判断这两个比特位的状态
    //如果均为1，则表示该字符串存在
    //只要有一个为0，则表示该字符串不存在
    for(i = 0;i < FUNCMAXSIZE;i++)
    {
        if(BitMapTest(&bf->bm,bloomnum[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}
////////////////////////////
//测试代码
////////////////////////////

#include<stdio.h>
#define TEST_HANDLE printf("==================%s==============\n",__FUNCTION__)

//测试初始化
void TestInit()
{
    TEST_HANDLE;
    BloomFilter bf;
    BloomFilterInit(&bf,BKDRHash,SDBMHash);
    printf("expect 1000,actually %lu\n",bf.bm.capacity);
    printf("expect %p,actually %p\n",BKDRHash,bf.bloomfunc[0]);
    printf("expect %p,actually %p\n",SDBMHash,bf.bloomfunc[1]);
    return;
}

//测试销毁布隆过滤器
void TestDestroy()
{
    TEST_HANDLE;
    BloomFilter bf;
    BloomFilterInit(&bf,BKDRHash,SDBMHash);
    BloomFilterDestroy(&bf);
    printf("expect 0,actually %lu\n",bf.bm.capacity);
    printf("expect null,actually %p\n",bf.bloomfunc[0]);
    printf("expect null,actually %p\n",bf.bloomfunc[1]);
    return;
}

//测试字符串插入和判断字符串是否存在
void TestInsert_Test()
{
    TEST_HANDLE;
    BloomFilter bf;
    BloomFilterInit(&bf,BKDRHash,SDBMHash);
    
    char* str1 = "aaa";
    char* str2 = "bbb";
    BloomFilterInsert(&bf,str1);
    BloomFilterInsert(&bf,str2);

    int ret;
    ret = BloomFilterTest(&bf,str1);
    printf("expect 1，actually %d\n",ret);
    ret = BloomFilterTest(&bf,str2);
    printf("expect 1，actually %d\n",ret);

    ret = BloomFilterTest(&bf,"hello");
    printf("expect 0，actually %d\n",ret);


}

int main()
{
    TestInit();
    TestDestroy();
    TestInsert_Test();
    return 0;
}
