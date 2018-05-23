
//位图：有多少数据就申请多少的内存位，不会发生哈希冲突
//布隆过滤器：申请的哈希表的比特位长度可能比实际所表示的字符串所对应的数字（一般这样的数字非常大）少
//所以要用哈希函数比如除留余数法 对字符串进行重新的 下标计算
//不同字符串计算的下标可能会相同，因此一个比特位可能会表示不同的字符串，此时，就发生了哈希冲突
//所以，为区分不同的字符串，可以根据不同的字符串哈希算法计算出该字符串对应的不同数字
//在利用除留余数法计算出不同的比特位下标，用两个或以上的比特位来表示一个字符串
//所选用的字符串哈希算法越多，表示一个字符串所用的比特位就越多，此时，发生哈希冲突的概率就越小
//
//由于一个字符串由多个比特位组成，所以不能对字符串进行删除操作
//因为一个比特位可能被多个字符串共用，删除一个字符串，就会删除该比特位，其他共用该比特位的字符串也会受到影响


//布隆过滤器:哈希表的变形
//布隆过滤器用于判断字符串的存在有无
//首先根据字符串哈希算法计算字符串对应的数字
//由于所选取的字符串哈希算法的局限性，
//可能导致不同字符串所计算得到的数字相同或者该数字所对应的哈希表的数组比特位下标相同
//因此两个或以上的字符串可能对应同一比特位，
//因此选用多个字符串哈希算法计算多个比特位下标来表示同一字符串来避免哈希冲突
#pragma once
#include<stdint.h>
#include<stdlib.h>
#include"bitmap.h"

//以64位8字节作为一个数组元素的内存大小
typedef uint64_t BloomFilterType;

#define MAXSIZE 1000//定义布隆过滤器最多有1000个比特位可以使用

//布隆过滤器的结构定义
//首先需要一个数组来存放字符串是否存在
//然后需要知道布隆过滤器最多能表示的实际比特位长度
//由于布隆过滤器实现的是字符串的状态
//所以需要多个哈希算法将字符串转化为数字

typedef size_t (*BloomFunc)(const char* str);//定义字符串哈希算法
#define FUNCMAXSIZE 2//定义需要两个字符串哈希算法来标识一个字符串


typedef struct BloomFilter
{
//    BloomFilterType* data;
//    uint64_t capacity;//布隆过滤器的实际长度
    //上述的两个成员实际表示的就是一个位图，这里，直接调用位图的结构将其封装在布隆过滤器中即可
    BitMap bm;//在布隆过滤器中封装一个位图
    BloomFunc bloomfunc[FUNCMAXSIZE];//定义字符串哈希算法
}BloomFilter;

//字符串哈希算法1
size_t BKDRHash(const char *str);

//字符串哈希算法2
size_t SDBMHash(const char *str);

//布隆过滤器的初始化
void BloomFilterInit(BloomFilter* bf,BloomFunc func1,BloomFunc func2);

//布隆过滤器的销毁
void BloomFilterDestroy(BloomFilter* bf);

//布隆过滤器的插入
void BloomFilterInsert(BloomFilter* bf,const char* str);

//在布隆过滤器中判断一个字符串是否存在
int BloomFilterTest(BloomFilter* bf,const char* str);

