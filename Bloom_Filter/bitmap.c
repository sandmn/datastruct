
#include"bitmap.h"
#include<stdlib.h>
#include<string.h>

//位图的初始化
void BitMapInit(BitMap* bm,uint64_t capacity)
{
    if(bm == NULL)
    {
        //非法输入
        return;
    }
    
    bm->capacity = capacity;
    //如果位图最大表示100个数字，则需要2个64位的内存
    //如果位图最大表示200个数字，则需要4个64位的内存
    //如果位图最大表示300个数字，则需要5个64位的内存
    //malloc以字节为单位进行内存申请

    //需要申请多少的64位内存
    uint64_t size = bm->capacity/(sizeof(BitMapType)*8) + 1;

    bm->data = (BitMapType*)malloc(size * sizeof(BitMapType));
    //初始化时要将位图中的各个位均置为0，以便后续的操作
    memset(bm->data,0,size*sizeof(BitMapType));
    return;
}

//销毁位图
void BitMapDestroy(BitMap* bm)
{
    if(bm == NULL)
    {
        //非法输入
        return;
    }

    bm->capacity = 0;
    free(bm->data);
    return;
}

//设置偏移量
void GetOffset(uint64_t index,uint64_t* n,uint64_t* offset)
{
    //首先计算该位在哪个数组元素内（数组元素以64为为一个单元）
    //计算完之后的n表示该位在下标为n的数组元素内（数组下标从0开始计数）
    *n = index/(sizeof(BitMapType)*8);

    //在计算该位在该元素的哪个位上
    //计算完之后的offset表示index在下标为的数组元素的哪一位（从0开始计算）
    *offset = index % (sizeof(BitMapType)*8); 
    return;
}

//测试某一位是否为1
int BitMapTest(BitMap* bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        //非法输入
        return 0;
    }


    //首先计算该位在哪个数组元素内（数组元素以64为为一个单元）
    //计算完之后的n表示该位在下标为n的数组元素内（数组下标从0开始计数）
    uint64_t n = index/(sizeof(BitMapType)*8);
    //在计算该位在该元素的哪个位上
    //计算完之后的offset表示index在下标为的数组元素的哪一位（从0开始计算）
    uint64_t offset = index % (sizeof(BitMapType)*8);

    //用1与之按位与，如果结果为0，则该位为0，否则为1
    //如果该位为1时，按位与完的结果必定只有该位为1，其余位为0，所以对结果进行判断时
    //只能跟0进行比较，不能跟1进行比较

    uint64_t ret = bm->data[n] & (0x1ul << offset);
    if(ret == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
//给某一位设置为1
void BitMapSet(BitMap* bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        //非法输入
        return;
    }

    //首先计算该位所在的数组下标及偏移量
    uint64_t n;
    uint64_t offset;
    GetOffset(index,&n,&offset);

    //再将该位设置为1
    //将该位置为1时要保证其他其他位不变，此时就要使其他位与0进行按位或
    //因此，该位要与1进行按位或，才能保证将该位置为1，而其他位也能保持不变

    //按位操作后的结果不会改变原来的值，所以要对其进行赋值
    bm->data[n] = bm->data[n] | (0x1ul << offset);
    return;

}

//给某一位设置为0
void BitMapSet0(BitMap* bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        //非法输入
        return;
    }
    //首先计算index所在的数组元素下标以及在在该下标处的偏移量
    uint64_t n;
    uint64_t offset;
    GetOffset(index,&n,&offset);

    //在根据数组元素下标和偏移量将该位设置为0
    //在将该位设置为0时，要保证其他位保持不变
    //所以，其他位要与1进行按位与（其他位也可以与0进行按位或但是index所在的为要置为0，只能进行按位与运算）
    //该位要与0进行按位与
    bm->data[n] = bm->data[n] & ~(0x1ul << offset);
}
//将位图的所有位均置为1
void BitMapFill(BitMap* bm)
{
    if(bm == NULL)
    {
        //非法输入
        return;
    }
    //将位图所占的内存区域中的所有位均置为1
    //使用memset来进行置1，位图有多少字节，就值多少个0xff

    //首先计算位图中共有多少64为的内存单元
    uint64_t size = bm->capacity/(sizeof(BitMapType)*8) + 1;
    memset(bm->data,0xff,size*sizeof(BitMapType));
    return;
}
//将位图的所有位均置为0
void BitMapClear(BitMap* bm)
{
    if(bm == NULL)
    {
        //非法输入
        return;
    }
    //将位图中的所有比特位均置为0
    //首先，计算位图中共占用了多少个64位的内存单元
    uint64_t size = bm->capacity/(sizeof(BitMapType)*8) + 1;
    //然后按字节将所有的比特位均置为0
    memset(bm->data,0x0,size*sizeof(BitMapType));
    return;
}
///////////////////////////
//测试代码
////////////////////////////

#if 0
#include<stdio.h>

#define TEST_HANDLE printf("==================%s==============\n",__FUNCTION__)

//测试初始化
void TestInit()
{
    TEST_HANDLE;
    BitMap bm;
    BitMapInit(&bm,MAXSIZE);
    printf("expect 1000,actually %lu\n",bm.capacity);
    return;
}

//测试某一位是否为1
void TestTest()
{
    TEST_HANDLE;
    BitMap bm;
    BitMapInit(&bm,MAXSIZE);
    int ret;
    ret = BitMapTest(&bm,500);
    printf("expect 0,actually %d\n",ret);
    return;
}

//测试将某一位设置为1
void TestSet()
{
    TEST_HANDLE;
    BitMap bm;
    BitMapInit(&bm,MAXSIZE);
    int ret;

    BitMapSet(NULL,78);//测试非法输入
    ret = BitMapTest(&bm,78);
    printf("expect 0,actually %d\n",ret);

    BitMapSet(&bm,7000);//测试非法输入
    ret = BitMapTest(&bm,7000);
    printf("expect 0,actually %d\n",ret);

    BitMapSet(&bm,0);
    ret = BitMapTest(&bm,0);
    printf("expect 1,actually %d\n",ret);

    BitMapSet(&bm,500);
    ret = BitMapTest(&bm,500);
    printf("expect 1,actually %d\n",ret);
    
    BitMapSet(&bm,999);
    ret = BitMapTest(&bm,999);
    printf("expect 1,actually %d\n",ret);
    
    return;

}

//测试将某一为设置为0
void TestSet0()
{
    TEST_HANDLE;
    BitMap bm;
    BitMapInit(&bm,MAXSIZE);
    int ret;

    BitMapSet(&bm,0);
    ret = BitMapTest(&bm,0);
    printf("expect 1,actually %d\n",ret);
    BitMapSet0(&bm,0);
    ret = BitMapTest(&bm,0);
    printf("expect 0,actually %d\n",ret);

    BitMapSet(&bm,500);
    ret = BitMapTest(&bm,500);
    printf("expect 1,actually %d\n",ret);
    BitMapSet0(&bm,500);
    ret = BitMapTest(&bm,500);
    printf("expect 0,actually %d\n",ret);
    
    BitMapSet(&bm,999);
    ret = BitMapTest(&bm,999);
    printf("expect 1,actually %d\n",ret);
    BitMapSet0(&bm,999);
    ret = BitMapTest(&bm,999);
    printf("expect 0,actually %d\n",ret);
    
    return;

}

//测试将所有的位均置为1
void TestFill()
{
    TEST_HANDLE;
    BitMap bm;
    BitMapInit(&bm,MAXSIZE);

    BitMapFill(&bm);

    int ret;
    ret = BitMapTest(&bm,0);
    printf("expect 1,actually %d\n",ret);

    ret = BitMapTest(&bm,999);
    printf("expect 1,actually %d\n",ret);

    ret = BitMapTest(&bm,500);
    printf("expect 1,actually %d\n",ret);
}

//测试将所有的位均置为0
void TestClear()
{
    TEST_HANDLE;
    BitMap bm;
    BitMapInit(&bm,MAXSIZE);
    int ret;

    BitMapFill(&bm);
    ret = BitMapTest(&bm,0);
    printf("expect 1,actually %d\n",ret);

    ret = BitMapTest(&bm,999);
    printf("expect 1,actually %d\n",ret);

    ret = BitMapTest(&bm,500);
    printf("expect 1,actually %d\n",ret);
    BitMapClear(&bm);
    ret = BitMapTest(&bm,0);
    printf("expect 0,actually %d\n",ret);

    ret = BitMapTest(&bm,999);
    printf("expect 0,actually %d\n",ret);

    ret = BitMapTest(&bm,500);
    printf("expect 0,actually %d\n",ret);
    return;

}

int main()
{
    TestInit();
    TestTest();
    TestSet();
    TestSet0();
    TestFill();
    TestClear();
    return 0;
}
#endif
