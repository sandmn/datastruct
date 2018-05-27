
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

void Print(int arr[],uint64_t size)
{
    int index = 0;
    for(;index < size;index++)
    {
        printf("%d ",arr[index]);
    }
    printf("\n");
}

///////////////////////////////
//冒泡排序（升序）（从后往前冒）
//时间复杂度：O(n^2),空间复杂度：O(1),稳定性：稳定
/////////////////////////////

void Swap(int* a,int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}


void BubbleSort(int arr[],uint64_t size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    int bound = 0;
    for(;bound < size - 1;bound++)
    {
        int cur = size - 1;
        for(;cur > bound;cur--)
        {
            if(arr[cur] < arr[cur - 1])
            {
                Swap(&arr[cur],&arr[cur - 1]);
            }
        }
    }
    return;
}

//void BubbleSort(int arr[],uint64_t size)
//{
//    if(arr == NULL || size <= 1)
//    {
//        return;
//    }
//    int bound = 0;
//    //[0,bound)表示已排好序的区间
//    //[bound,size)表示未排序区间
//    for(;bound < size;++bound)
//    {
//        int cur = size - 1;
//        for(;cur > bound;--cur)
//        {
//            if(arr[cur] < arr[cur - 1])
//            {
//                Swap(&arr[cur],&arr[cur - 1]);
//            }
//        }
//    }
//    return;
//}
//


////////////////////////////////
//冒泡排序：升序（从前往后冒）
///////////////////////////////

void BubbleSortEx(int arr[],uint64_t size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    int bound = 0;
    for(;bound < size - 1;bound++)
    {
        int cur = 0;
        for(;cur < size - 1 - bound;++cur)
        {
            if(arr[cur] > arr[cur + 1])
            {
                Swap(&arr[cur],&arr[cur + 1]);
            }
        }
    }
    return;
}


////////////////////////
//选择排序:打擂主，边界值每次做擂主，使边界后的各元素与擂主比较
//如果不满足条件，就交换
//时间复杂度：O(n^2),空间复杂度：O(1),稳定性：不稳定
//////////////////////////

void SelectSort(int arr[],uint64_t size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    //[0,bound）：表示已排好序的区间
    //[bound,size):表示未排好序的区间
    int bound = 0;
    for(;bound < size - 1;bound++)
    {
        int cur = bound + 1;
        for(;cur < size;cur++)
        {
            if(arr[bound] > arr[cur])
            {
                Swap(&arr[bound],&arr[cur]);
            }
        }
    }
    return;
}

////////////////////////
//插入排序：时间复杂度：O(n^2),空间复杂度：O(1),稳定性：稳定
//插入排序的特点：1. 在元素比较少时，排序效率比较高
//                2. 在元素有序性比较高的情况下，排序效率比较高
////////////////////////

void InsertSort(int arr[],uint64_t size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    //[0,bound)：表示已排好序的区间
    //[bound,size):表示未排序区间
    //每次取bound处的值，为bound_value找到合适的位置进行插入
    //利用cur进行辅助查找
    //如果cur-1处的值大于bound_value,将cur-1处的值后移，
    //此时，逻辑上cur -1 是bound_value暂时的位置
    //当cur - 1处的值小于bound_value时，此时cur的位置就是bound_value的最终位置
    //当cur遍历到0处时，cur的位置也是bound_value的最终位置
    int bound = 1;
    for(;bound < size;bound++)
    {
        int cur = bound;
        int bound_value = arr[bound];
        for(;cur > 0;cur--)
        {
            if(arr[cur - 1] > bound_value)
            {
                arr[cur] = arr[cur - 1];
            }
            else
            {
                break;
            }
        }
        arr[cur] = bound_value;
    }
    return;
}

//////////////////////////
//堆排序
//如果是升序，则构建大堆
/////////////////////////

void AdjustUp(int arr[],uint64_t size,int index)
{
    if(index >= size || index < 0)
    {
        return;
    }
    //上浮式调整时：
    //比较孩子节点与其父节点的大小关系，
    //如果不满足条件（此处条件为父节点应该大于字节点的值），则进行交换
    //如果满足条件，则停止调整:有问题
    int child = index;
    int parent = (child - 1)/2;
    while(child > 0)
    {
        if(arr[parent] < arr[child])
        {
            Swap(&arr[parent],&arr[child]);
        }
        else
        {
            break;
        }
        child = parent;
        parent = (child - 1)/2;
    }
}

//对堆顶元素进行下沉式调整
void AdjustDown(int arr[],uint64_t heap_size,int index)
{
    int parent = index;
    int child = parent*2 + 1;
    while(child < heap_size)
    {
        if(child + 1 < heap_size && arr[child] < arr[child + 1])
        {
            child = child + 1;
        }
        if(arr[child] > arr[parent])
        {
            Swap(&arr[child],&arr[parent]);
            parent = child;
            child = parent*2 + 1;
        }
        else
        {
            break;
        }
    }
    return;
}

//创建堆
void CreateHeap(int arr[],uint64_t size)
{

    //根据下沉式调整创建堆
    //从第一个非叶子节点开始下沉，依次往前，每次下沉一个
    //第一个非叶子节点为最后一个节点的父节点
    int index = ((size - 1) - 1)/2;//第一个非叶子节点
    for(;index >= 0;index--)//注意
    {
        AdjustDown(arr,size,index);
    }
    

    ////根据上浮式调整创建
    ////将数组中的元素从后往前一个个的进行上浮时调整

    //int index = 0;
    //for(;index < size;index++)
    //{
    //    //每次从index处向上进行调整
    //    AdjustUp(arr,size,index);
    //}
    return;
}

//删除堆
void DeleteHeap(int arr[],uint64_t size)
{
    //对堆的删除进行下沉式调整
    int index = size - 1;
    //每次从最后一个堆元素开始
    for(;index > 0;index--)
    {
        //每次将最后一个堆元素与堆顶元素交换
        Swap(&arr[0],&arr[index]);
        //然后堆顶元素进行下沉式调整
        AdjustDown(arr,index,0);
    }

}
void HeapSort(int arr[],uint64_t size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    //首先根据数组构建大堆（在数组的基础上构建）
    //构建堆时，有两种方法：上浮式调整和下沉式调整
    CreateHeap(arr,size);
    Print(arr,size);
    //再对堆元素进行删除
    DeleteHeap(arr,size);
    //删除完之后的堆（数组）即为升序后的数组
    return;
}

////////////////////////////
//希尔排序:对带排序的序列进行分组，组内进行插入排序
//充分利用插入排序的两个特点。
//首先进行分组使元素个数减少，然后组内进行排序
//在有序性高的序列中再次使用插入排序
//希尔序列：n/2 n/4 n/8
///////////////////////////

void ShellSort(int arr[],uint64_t size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }

    int gap = size/2;

    //第一重循环，对待排序序列进行分组
    for(;gap >= 1;gap = gap/2)
    {
        //第二重循环：计算边界值
        int bound = gap;
        //第一次对第一组的第一个元素进行排序
        //第二次对第二组的第一个元素进行排序
        //......
        //对第一组的第二个元素进行排序
        //对第二组的第二个元素进行排序
        //。。。
        for(;bound < size;bound++)
        {
            //在组内定义cur进行插入排序
            int cur = bound;
            int bound_value = arr[bound];//保存bound处的值
            for(;cur >= gap;cur = cur - gap)
            {
                if(bound_value < arr[cur - gap])
                {
                    arr[cur] = arr[cur - gap];
                }
                else
                {
                    break;
                }
            }
            arr[cur] = bound_value;
        }
    }
}

///////////////////////////////////
//归幷排序
//////////////////////////////////

void MergeArray(int arr[],int left,int mid,int right,int temp[])
{
    int index1 = left;
    int index2 = mid + 1;
//    int* temp = (int*)malloc((right - left + 1)*sizeof(int));
//    int index = 0;
    while(index1 <= mid && index2 <= right)
    {
        if(arr[index1] < arr[index2])
        {
            *temp = arr[index1];
            index1++;
            temp++;
            //index++;
        }
        else /*if(arr[index1] > arr[index2])*/
        {
            *temp = arr[index2];
            index2++;
            temp++;
            //index++;
        }
    }
    if(index1 > mid)
    {
        int i = index2;
        for(;i <= right;i++)
        {
            *temp = arr[i];
            temp++;
            //index++;
        }
    }
    else
    {
        int i = index1;
        for(;i <= mid;i++)
        {
            *temp = arr[i];
            temp++;
            //index++;
        }
    }

   // int i = 0;
   // for(;i < right - left + 1;i++)
   // {
   //     arr[i] = *temp;
   //     temp++;
   // }
    return;
}

void _MergeSort(int arr[],int left,int right,int temp[])
{
    if(left >= right)
    {
        //带排序区间中最多只有一个元素
        return;
    }

    //现将带排序序列一分为二，如果某一部分的元素个数小于等于1，则认为已经排好序
    int mid = left + (right - left)/2;

    //分别对这两部分进行排序
    _MergeSort(arr,left,mid,temp);
    _MergeSort(arr,mid + 1,right,temp);
    //将排好序的两部分进行合并,即合并两个有序数组
    MergeArray(arr,left,mid,right,temp);
    return;
}


void MergeSort(int arr[],uint64_t size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }

    //[left,right)为待排序区间
    int left = 0;
    int right = size - 1;
    int* temp = (int*)malloc(size*sizeof(int));
    //int index = 0;
    _MergeSort(arr,left,right,temp);
    int i = 0;
    for(;i < size;i++)
    {
        arr[i] = temp[i];
    }
    return;
}

/////////////////////////////
//测试代码
////////////////////////////


#include<stdio.h>
#define TEST_HANDLE printf("=================%s==============\n",__FUNCTION__)

//void Print(int arr[],uint64_t size)
//{
//    int index = 0;
//    for(;index < size;index++)
//    {
//        printf("%d ",arr[index]);
//    }
//    printf("\n");
//}
//
//测试冒泡排序（从后往前冒）
void TestBubbleSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    BubbleSort(arr,size);
    Print(arr,size);


    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    BubbleSort(arr1,size1);
    Print(arr1,size1);
    return;
}
//测试冒泡排序（从后往前冒）
void TestBubbleSortEx()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    BubbleSortEx(arr,size);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    BubbleSortEx(arr1,size1);
    Print(arr1,size1);
    return;
}
//测试选择排序
void TestSelectSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    SelectSort(arr,size);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    SelectSort(arr1,size1);
    Print(arr1,size1);
    return;
}

//测试插入排序
void TestInsertSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    InsertSort(arr,size);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    InsertSort(arr1,size1);
    Print(arr1,size1);
    return;
}

//测试堆排序
void TestHeapSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    HeapSort(arr,size);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    HeapSort(arr1,size1);
    Print(arr1,size1);
    return;
}
//测试希尔排序
void TestShellSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    ShellSort(arr,size);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    ShellSort(arr1,size1);
    Print(arr1,size1);
    return;
}
//测试归幷排序
void TestMergeSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    MergeSort(arr,size);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    MergeSort(arr1,size1);
    Print(arr1,size1);
    return;
}
int main()
{
    TestBubbleSort();
    TestBubbleSortEx();
    TestSelectSort();
    TestInsertSort();
    TestHeapSort();
    TestShellSort();
    TestMergeSort();
    return 0;
}