
#include"heap.h"
#include<stdio.h>
#include<string.h>

int Less(HeapType a,HeapType b)
{
    return a < b? 1:0;//如果a小于b表示是小堆
}

int Greater(HeapType a,HeapType b)
{
    return a > b? 1:0;
}
//堆的初始化:初始化时说明该堆是大堆还是小堆
void HeapInit(Heap* heap,Compare cmp)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    heap->size = 0;//初始时堆中节点个数为0
    heap->cmp = cmp;//该堆是大堆还是小堆由用户传入的参数决定
    return;
}

void Swap(HeapType* a,HeapType* b)
{
    //交换堆中的元素
    HeapType tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

//对堆中元素进行上浮式调整:时间复杂度为：logn
void AdjustUp(Heap* heap,size_t start_loc)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    //在调整的过程中，需要不断的比较树的根节点与孩子节点的大小
    //如果不满足比较条件，就一直往上浮
    //如果满足条件，就停止调整
    //直到到达树的根节点为止
    size_t child = start_loc;
    size_t parent = (child - 1)/2;
    while(1)
    {
        if(child == 0)
        {
            //已经调整的树的根节点位置
            break;
        }
        //不满足比较条件
        if(heap->cmp(heap->data[parent],heap->data[child]) == 0)
        {
            //交换孩子与根节点的元素
            Swap(&heap->data[parent],&heap->data[child]);
            //更新孩子节点与根节点的位置下标，判断是否要继续上浮
            child = parent;
            parent = (child - 1)/2;
        }
        else
        {
            //此时满足了比较条件，就不需要再进行交换并上浮了，所以直接返回即可
            break;
        }
    }
    return;
}
//时间复杂度为：logn
void HeapInsert(Heap* heap,HeapType value)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    //直接对数组进行尾插，尾插完已经保证还是完全二叉树
    heap->data[heap->size++] = value;
    //接下来要做的就是保证堆中任意树的根节点比左右子树大或小，
    //因此需要将新插入的节点进行上浮式调整，调整的初始位置为新插入的节点位置
    AdjustUp(heap,heap->size - 1);
    //调整结束之后就保证了该二叉树还是一个堆
    return;
}

//取堆顶元素,0代表获取成功，1代表获取失败
int HeapTop(Heap* heap,HeapType* top)
{
    if(heap == NULL)
    {
        //非法输入
        return 0;
    }
    if(heap->size == 0)
    {
        //空堆
        return 0;
    }
    *top = heap->data[0];
    return 1;
}
//对堆进行下沉式调整
//时间复杂度为：logn
void AdjustDown(Heap* heap,size_t start_loc)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    //如果是大堆，堆顶元素应为根节点，左，右孩子中的最大值
    //所以先比较找到左，右孩子中的最大值，
    //然后再将根节点和孩子中的最大值进行比较，如果根节点比最大值小，就交换这两个节点的值
    //否则，说明已经满足要求，直接返回即可
    //一直往下比较，直到比较到最后一行
    
    size_t parent = start_loc;
    size_t child = parent*2 + 1;

    while(1)
    {
        //parent节点最多交换到树的最后一层，则停止交换，此时，child一定大于或等于size
        if(child >= heap->size)
        {
            //说明parent已交换到最后一层
            break;
        }
        //如果右节点存在，在大跟堆中，找左右节点的最大值，小跟堆找左右节点的最小值
        //如果是大跟堆，如果左节点元素小于右节点元素
        if(child + 1 < heap->size && heap->cmp(heap->data[child],heap->data[child + 1]) == 0)
        {
            //此时取右节点元素与根节点元素进行比较
            child = child + 1;
        }
        //大跟堆将根节点与孩子节点的最大值进行比较，小跟堆将根节点与左右孩子节点的最小值进行比较
        //如果是大跟堆，如果根节点比孩子节点的最大值小，就进行交换
        if(heap->cmp(heap->data[parent],heap->data[child]) == 0)
        {
            //交换
            Swap(&heap->data[parent],&heap->data[child]);
            //然后更新parent与child的值，继续比较下沉
            parent = child;
            child = parent*2 + 1;
        }
        else
        {
            //此时满足了比较条件，直接返回即可
            break;
        }
    }
    return;
}
//时间复杂度为：logn
void HeapErase(Heap* heap)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    if(heap->size == 0)
    {
        //空堆无法进行删除
        return;
    }
    //先将堆顶元素与堆尾元素交换，再尾删堆顶元素
    Swap(&heap->data[0],&heap->data[heap->size - 1]);
    --heap->size;
    //再对新的堆顶元素进行下沉式调整,从堆顶位置开始调整
    AdjustDown(heap,0);
    //调整结束之后就保证了该二叉树还是一个堆
    return;
}
//销毁堆
int HeapDestroy(Heap* heap)
{
    if(heap == NULL)
    {
        //堆已销毁
        return 0;
    }
    heap->size = 0;
    heap->cmp = NULL;
    return 1;
}
//统计堆中元素个数
size_t HeapSize(Heap* heap)
{
    if(heap == NULL)
    {
        //非法输入
        return (size_t)-1; 
    }
    return heap->size;    
}

void HeapEmpty(Heap* heap)
{
    if(heap == NULL)
    {
        //非法输入
        return;
    }
    heap->size = 0;
    return;
}

//根据堆对数组进行排序,sort_flag等于1表示进行升序排序，等于0表示进行降序排序
//时间复杂度为：nlogn
void HeapSort(HeapType array[],size_t size,int sort_flag)
{
    if(array == NULL || size == 0)
    {
        //非法输入
        return;
    }
    //先根据数组元素创建一个堆
    //如果需要升序排序，就创建一个大堆，如果需要降序排序，就需要一个小堆
    //堆创建好之后，对堆中元素进行逐个删除
    //删除完之后，将堆中元素赋值给数组元素
    //此时，数组元素就已经排好序了
    //这里对数组进行降序排序
    
    //创建一个堆
    Heap heap;
    if(sort_flag == 1)
    {
        HeapInit(&heap,Greater);
    }
    else
    {
        HeapInit(&heap,Less);
    }
    //根据数组元素对堆进行插入元素
    size_t cur = 0;
    for(;cur < size;cur++)
    {
        HeapInsert(&heap,array[cur]);
    }

    //依次删除堆顶元素
    for(cur = 0;cur < size;++cur)
    {
        HeapErase(&heap);
    }
    //删除完成之后，堆中的元素已排好序,将排好序的堆元素在赋值给数组元素
    memcpy(array,heap.data,size*sizeof(HeapType));
}
//////////////////////////
//测试代码
//////////////////////////

#include<stdio.h>
#define TEST_HANDLE printf("=================%s==============\n",__FUNCTION__);


//测试初始化
void TestInit()
{
    TEST_HANDLE;
    Heap heap;
    HeapInit(&heap,Greater);
    printf("expect 0,actually %lu\n",heap.size);
    printf("expect %p,actually %p\n",Greater,heap.cmp);
    return;
}


//打印堆
void HeapPrint(Heap* heap,const char* msg)
{
    printf("%s\n",msg);
    size_t cur = 0;
    for(;cur < heap->size;++cur)
    {
        printf("%c ",heap->data[cur]);
    }
    printf("\n");
    return;
}


void TestInsert()
{
    TEST_HANDLE;
    Heap heap;
    HeapInit(&heap,Greater);

    HeapInsert(&heap,'a');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');

    HeapPrint(&heap,"打印堆");
    return;

}

//测试取堆顶元素
void TestTop()
{
    TEST_HANDLE;

    HeapType top;
    int ret;
    
    ret = HeapTop(NULL,&top);//测试非法输入
    printf("expect 0,actually %d\n",ret);

    Heap heap;
    HeapInit(&heap,Greater);

    ret = HeapTop(&heap,&top);//测试空堆
    printf("expect 0,actually %d\n",ret);

    HeapInsert(&heap,'a');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');

    ret = HeapTop(&heap,&top);
    printf("expect 1,actually %d\n",ret);
    printf("expect f,actually %c\n",top);
    return;
}

//测试删除堆顶元素
void TestErase()
{
    TEST_HANDLE;
    
    HeapErase(NULL);//测试非法输入

    Heap heap;
    HeapInit(&heap,Greater);
    HeapErase(&heap);//测试空堆

    HeapInsert(&heap,'a');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');
    HeapPrint(&heap,"新建一个堆");

    HeapErase(&heap);//测试删除堆顶元素
    HeapPrint(&heap,"打印删除堆顶元素f之后的堆");

    HeapErase(&heap);//测试删除堆顶元素
    HeapPrint(&heap,"打印删除堆顶元素e之后的堆");

    HeapErase(&heap);//测试删除堆顶元素
    HeapPrint(&heap,"打印删除堆顶元素d之后的堆");

    HeapErase(&heap);//测试删除堆顶元素
    HeapPrint(&heap,"打印删除堆顶元素c之后的堆");

    HeapErase(&heap);//测试删除堆顶元素
    HeapPrint(&heap,"打印删除堆顶元素b之后的堆");

    HeapErase(&heap);//测试删除堆顶元素
    HeapPrint(&heap,"打印删除堆顶元素a之后的堆");
    return;
}

//测试清空堆
void TestDestroy()
{
    TEST_HANDLE;
    
    int ret;
    ret = HeapDestroy(NULL);//测试不存在的堆
    printf("expect 0,actually %d\n",ret);

    Heap heap;
    HeapInit(&heap,Greater);

    HeapInsert(&heap,'a');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');
    HeapPrint(&heap,"新建一个堆");

    ret = HeapDestroy(&heap);//测试非空堆
    printf("expect 0,actually %lu\n",heap.size);
    printf("expect null,actually %p\n",heap.cmp);
    printf("expect 1,actually %d\n",ret);
    
}

void TestSize()
{
    TEST_HANDLE;

    size_t size;
    size = HeapSize(NULL);//测试非法输入
    printf("expect -1,actually %d\n",(int)size);

    Heap heap;
    HeapInit(&heap,Greater);
    size = HeapSize(&heap);//测试空堆
    printf("expect 0,actually %d\n",(int)size);

    HeapInsert(&heap,'a');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');
    HeapPrint(&heap,"新建一个堆");

    size = HeapSize(&heap);//测试非空堆
    printf("expect 6,actually %d\n",(int)size);
}

//测试清空堆
void TestEmpty()
{
    TEST_HANDLE;
    HeapEmpty(NULL);//测试非法输入

    Heap heap;
    HeapInit(&heap,Greater);

    HeapInsert(&heap,'a');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'e');
    HeapInsert(&heap,'f');
    HeapPrint(&heap,"新建一个堆");
    
    HeapEmpty(&heap);//清空非空堆
    printf("expect 0,actually %lu\n",heap.size);
}

//测试根据堆对数组元素进行排序
void TestSort()
{
    TEST_HANDLE;
    HeapType array[] = {'d','a','e','a','f','s','b'};
    size_t size = sizeof(array)/sizeof(array[0]);
    HeapSort(array,size,1);//对数组元素进行升序排序
    int cur = 0;
    for(;cur < size;cur++)
    {
        printf("%c ",array[cur]);
    }
    printf("\n");

    HeapSort(array,size,0);//对数组元素进行降序排序
    cur = 0;
    for(;cur < size;cur++)
    {
        printf("%c ",array[cur]);
    }
    printf("\n");

    return;
}

int main()
{
    TestInit();
    TestInsert();
    TestTop();
    TestErase();
    TestDestroy();
    TestSize();
    TestEmpty();
    TestSort();
    return 0;
}
