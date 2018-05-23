
//位图：变形的哈希表
//将每一个比特位作为哈希表的一个数据单元
//所以，位图中有多少比特位，就能表示多少的数字
//位图只能在他所表示的位数范围内某个数字存在与否。
//因为一个比特位只能存储0或1，
//所以在对位图进行插入某数字时，在位图表中将该数字所表示的位内容置为1
//在位图中查找某个数字时，如果该数字所在位的值为1，就表示该数字存在，否则不存在


//首先，利用数组来表示一个位图的结构，数组的元素类型可以自定义，只要该位图所能表示的位范围确定即可

//位图的结构表示

//在对位图中的内存申请时，不能一位一位进行申请，所以以64位8字节为一个单位进行申请
//之所以不用size_t或unsigned long是为了消除平台的差异性，
//因为size_t表示的就是unsigned long，该类型在32位平台下占4个字节，在64位平台下占8个字节
//而uint64_t无论在32 位还是在64位平台下都占8个字节


#pragma once
#include<stdint.h>

typedef uint64_t BitMapType;

//指定位图最大能表示的数字范围
#define MAXSIZE 1000


//位图的结构定义
typedef struct BitMap
{
    BitMapType* data;
    uint64_t capacity;//位图中最大能表示的比特位个数
    //1GB = 2^10MB = 2^20KB = 2^30B = 10亿B = 80亿b，一个位表示一个数字，所以1GB可以表示80亿个数字
    //如果有40亿个数字，则需要0.5GB的内存。
    //uint64_t 最多能表示的数字为2^64，即1600亿个数字
    //uint32_t 最多能表示的数字为2^32，即40亿个数字
}BitMap;

//位图的初始化
void BitMapInit(BitMap* bm,uint64_t capacity);

//销毁位图
void BitMapDestroy(BitMap* bm);

//测试某一位是否为1
int BitMapTest(BitMap* bm,uint64_t index);

//给某一位设置为1
void BitMapSet(BitMap* bm,uint64_t index);


//给某一位设置为0
void BitMapSet0(BitMap* bm,uint64_t index);

//将位图的所有位均置为1
void BitMapFill(BitMap* bm);

//将位图的所有位均置为0
void BitMapClear(BitMap* bm);

