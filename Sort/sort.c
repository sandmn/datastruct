
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include"seqstack.h"

typedef int(*Compare)(int a,int b);

//升序比较规则
int Greater(int a,int b)
{
    return a > b? 1 : 0;
}

//降序比较规则
int Less(int a,int b)
{
    return a < b? 1 : 0;
}

//void Print(int arr[],uint64_t size)
//{
//    int index = 0;
//    for(;index < size;index++)
//    {
//        printf("%d ",arr[index]);
//    }
//    printf("\n");
//}

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


//从后往前冒
void BubbleSort(int arr[],uint64_t size,Compare cmp)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    int bound = 0;
    for(;bound < size - 1;bound++)
    {
        //在每一轮排序中从往前比较
        int cur = size - 1;
        for(;cur > bound;cur--)
        {
            if(cmp(arr[cur - 1],arr[cur]) == 1)
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

//从前往后冒
void BubbleSortEx(int arr[],uint64_t size,Compare cmp)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }

    //此时，[0,bound]为带排序区间,(bound,size)为已排序区间
    int bound = size - 1;
    for(;bound > 0;bound--)
    {
        int cur = 0;
        for(;cur < bound;cur++)
        {
            if(cmp(arr[cur],arr[cur + 1]) == 1)
            {
                Swap(&arr[cur],&arr[cur + 1]);
            }
        }
    }
    return;
   // int bound = 0;
   // for(;bound < size - 1;bound++)
   // {
   //     int cur = 0;
   //     for(;cur < size - 1 - bound;++cur)
   //     {
   //         if(arr[cur] > arr[cur + 1])
   //         {
   //             Swap(&arr[cur],&arr[cur + 1]);
   //         }
   //     }
   // }
   // return;
}


////////////////////////
//选择排序:打擂主，边界值每次做擂主，使边界后的各元素与擂主比较
//如果不满足条件，就交换
//时间复杂度：O(n^2),空间复杂度：O(1),稳定性：不稳定
//////////////////////////

//选择排序:打擂主，边界值每次做擂主，使边界后的各元素与擂主比较
void SelectSort(int arr[],uint64_t size,Compare cmp)
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
            if(cmp(arr[bound],arr[cur]) == 1)
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

void InsertSort(int arr[],uint64_t size,Compare cmp)
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
            if(cmp(arr[cur - 1],bound_value) == 1)
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

//上浮式调整
void AdjustUp(int arr[],uint64_t size,int index,Compare cmp)
{
    if(index >= size || index < 0)
    {
        return;
    }
    //上浮式调整时：
    //比较孩子节点与其父节点的大小关系，
    //如果不满足条件（此处条件为父节点应该大于子节点的值），则进行交换
    //如果满足条件，则停止调整
    int child = index;
    int parent = (child - 1)/2;
    while(child > 0)
    {
        if(cmp(arr[child],arr[parent] == 1))
        {
            Swap(&arr[parent],&arr[child]);
            child = parent;
            parent = (child - 1)/2;
        }
        else
        {
            break;
        }
    }
}

//对堆顶元素进行下沉式调整
void AdjustDown(int arr[],uint64_t heap_size,int index,Compare cmp)
{
    int parent = index;
    int child = parent*2 + 1;
    while(child < heap_size)//左孩子节点存在
    {
        //右孩子节点存在，且右孩子节点的值大于右孩子节点的值
        if(child + 1 < heap_size && cmp(arr[child + 1],arr[child]) == 1)
        {
            child = child + 1;
        }
        if(cmp(arr[child],arr[parent]) == 1)
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
    for(;index >= 0;index--)//注意,下标为0的元素也需要进行下沉调整
    {
        AdjustDown(arr,size,index,Greater);
    }
    

    ////根据上浮式调整创建
    ////将数组中的元素从后往前一个个的进行上浮时调整

    //int index = 0;
    //for(;index < size;index++)
    //{
    //    //每次从index处向上进行调整
    //    AdjustUp(arr,size,index,Greater);
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
        //删除堆顶元素时：
        //1. 将堆的最后一个元素与堆顶元素进行交换，
        //   这里堆的最后一个元素下标为index,此时堆中的元素个数为index + 1
        //2. 然后使堆元素个数减1，此时堆中元素个数为index
        //3. 最后在新堆中对新堆顶元素进行下沉式调整，此时堆的元素个数依然为index
       
        //每次将最后一个堆元素与堆顶元素交换
        Swap(&arr[0],&arr[index]);
        //然后堆顶元素进行下沉式调整
        AdjustDown(arr,index,0,Greater);
        //这里的参数index表示的是堆中的元素个数，该步操作隐含了堆元素个数减1的操作
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
    //Print(arr,size);
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

//希尔排序
void ShellSort(int arr[],uint64_t size,Compare cmp)
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
            //这里注意cur的判断条件：假设步长取值为3
            //则对应的三个分组第一个元素分别为：0，1，2
            //对任一分组，cur减至每个分组的第一个元素下标时，停止前移
            //因为分组的不同，对应的第一个元素下标也不同，但是任一分组第一个元素下标都是小于步长3的
            //所以对任一分组，可以将条件设置为当cur的值小于步长3时停止前移
            //也就是说cur大于等于步长3时仍可以前移，所以这里的条件为：cur>=gap
            for(;cur >= gap;cur = cur - gap)
            {
                if(cmp(arr[cur - gap],bound_value) == 1)
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
//归幷排序（递归）
//////////////////////////////////


//合并两个有序数组使之成为新的有序数组
void MergeArray(int arr[],int left,int mid,int right,int temp[])
{
    //使合并后的新的有序数组的下标与两个有序数组的下标对应
    int index1 = left;
    int index2 = mid;
    int temp_index = left;//新数组中的有序元素从left到right

    //如果两个有序子数组没有遍历完，就一直遍历直到某个数组遍历结束
    while(index1 < mid && index2 < right)
    {
        //使值小的元素先复制到新的数组
        if(arr[index1] < arr[index2])
        {
            temp[temp_index++] = arr[index1++];
        }
        else
        {
            temp[temp_index++] = arr[index2++];
        }
    }
    //将还未遍历完子数组的剩余元素一个个的赋值到新数组中
    while(index1 < mid)
    {
        temp[temp_index++] = arr[index1++];
    }
    while(index2 < right)
    {
        temp[temp_index++] = arr[index2++];
    }
    //将temp中排好序的元素复制到arr中
    //以便下一次接着对arr进行合并
    int i = left;
    for(;i < right;i++)
    {
        arr[i] = temp[i];
    }
    return;
}

void _MergeSort(int arr[],int left,int right,int temp[])
{
    if(right - left <= 1)
    {
        //带排序区间中最多只有一个元素,此时不用在排序
        return;
    }

    //现将待排序序列一分为二，如果某一部分的元素个数小于等于1，则认为已经排好序
    int mid = left + (right - left)/2;
    //此时拆分的两个待区间为：[left,mid),[mid,right)

    //分别对这两部分进行排序
    _MergeSort(arr,left,mid,temp);
    _MergeSort(arr,mid,right,temp);
    //将排好序的两部分进行合并,即合并两个有序数组
    MergeArray(arr,left,mid,right,temp);
    return;
}


//递归进行归幷排序
void MergeSort(int arr[],uint64_t size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }

    //[left,right)为待排序区间
    int left = 0;
    int right = size;
    //定义temp来保存合并两个已经排好序的区间
    int* temp = (int*)malloc(size*sizeof(int));
    //使用递归函数来对带排序序列进行排序
    _MergeSort(arr,left,right,temp);
    return;
}

////////////////////////////
//归幷排序（非递归）
////////////////////////////

void MergeSortByLoop(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        //数组非法或者元素个数小于等于1，此时都不需要进行排序，直接返回即可
        return;
    }
    //1. 首先，取步长gap为1，
    //   合并区间：[0*gap,1*gap),[1*gap,2*gap)
    //             [2*gap,3*gap),[3*gap,4*gap)
    //             [4*gap,5*gap),[5*gap,6*gap).......
    //2.然后，取步长gap为2，
    //  合并区间：[0*gap,1*gap),[1*gap,2*gap)
    //            [2*gap,3*gap),[3*gap,4*gap]......
    //3.取步长gap为4，同理合并区间[0*gap,1*gap),[1*gap,2*gap).....
    //4.步长的改变为：1，2，4，8，...,直到步长gap最大为size,此时就不需要在合并了
    //上述过程中，需要两重循环来实现，第一重用于步长的改变，第二重用于区间的合并
    
    int* temp = (int*)malloc(size*sizeof(int));
    
    //步长的变化为：1，2，4，8,...后一次的步长是上一次的2倍
    int gap = 1;
    for(;gap < size;gap = 2*gap)
    {
        //每两个区间之间的间隔为：2*gap
        //即：0，2*gap,4*gap,8*gap,...
        //所以区间的增长差2*gap
        int index = 0;
        for(;index < size;index = index + 2*gap)
        {
            int left = index;
            int mid = index + gap;
            
            //防止最后只剩余一个区间，从而无法进行合并
            if(mid >= size)
            {
                mid = left;
            }
            int right = index + 2*gap;
            if(right >= size)
            {
                right = left;
            }
            MergeArray(arr,left,mid,right,temp);
        }
    }
}

/////////////////////////////
//快速排序（递归）
/////////////////////////////

//挖坑法
int Pattern2(int arr[],int left,int right)
{
    if(right - left <= 1)
    {
        return left;
    }
    int left_index = 0;
    int right_index = right - 1;
    //基准值为带排序序列的最后一个元素
    int basic_value = arr[right - 1];
    //当left_index和right_index没有相遇时
    while(left_index < right_index)
    {
        //如果没有相遇且left_index遇到小于等于基准值的元素，则left_index后移
        while(left_index < right_index && arr[left_index] <= basic_value)
        {
            left_index++;
        }
        //如果没有相遇且left_index遇到大于基准值的元素
        if(arr[left_index] > basic_value)
        {
            //将该元素赋值到坑所在位置
            arr[right_index] = arr[left_index];
        }
        //同理
        while(left_index < right_index && arr[right_index] >= basic_value)
        {
            right_index--;
        }
        if(arr[right_index] < basic_value)
        {
            arr[left_index] = arr[right_index];
        }
    }
    //当left_index与right_index相遇时，一定位于坑所在的位置
    //此时，将基准值赋值到该处即可
    arr[left_index] = basic_value;
    //返回基准值放置的位置
    return left_index;

}


//基准值为带排序序列的第一个元素，则后面的变量先开始往前找
int Pattern1(int arr[],int left,int right)
{
    if(right - left <= 1)
    {
        return right;
    }
    int back = right - 1;
    int front = left;
    int basic_value = arr[left];
    while(front < back)
    {
        while(front < back && arr[back] >= basic_value)
        {
            back--;
        }
        while(front < back && arr[front] <= basic_value)
        {
            front++;
        }
        if(front < back)
        {
            Swap(&arr[front],&arr[back]);
        }
        else
        {
            break;
        }
    }
    Swap(&arr[back],&arr[left]);
    return back;
}


//基准值为带排序序列的最后一个元素：则前面的变量开始往后找
//int Pattern1(int arr[],int left,int right)
//{
//    if(right - left <= 1)
//    {
//        return left;
//    }
//    //取基准值为最后一个元素
//    int basic_value = arr[right - 1];
//    //定义两个变量，一个从前往后找大于等于基准值的元素
//    //另一个从后往前找小于等于基准值的元素
//    int front = left;
//    int back = right - 1;
//    //当front与back相等的时候，查找结束，此时二者一定指向大于基准值的元素
//    while(front < back)
//    {
//        while(front < back && arr[front] <= basic_value)
//        {
//            front++;
//        }
//        while(front < back && arr[back] >= basic_value)
//        {
//            back--;
//        }
//        if(front < back)
//        {
//            //交换两个元素
//            Swap(&arr[front],&arr[back]);
//        }
//        else
//        {
//            break;
//        }
//    }
//    //因为最后front处的值一定大于基准值，所以将此处的值与基准值进行交换
//    Swap(&arr[front],&arr[right - 1]);
//    return front;
//}

void _QuickSort(int arr[],int left,int right)
{
    //排序数组中最多只有一个元素，则不用进行排序了
    if(arr == NULL || right - left <= 1)
    {
        return;
    }
    //对区间[left,right)中的元素利用交换法进行排序
    //在交换排序中，取一个基准值，使基准值之前的元素小于等于基准值，基准值之后的元素大于等于基准值
    //然后返回基准值所在的位置
    int mid = Pattern1(arr,left,right);
    //然后对基准值之前的元素再次进行交换排序
    _QuickSort(arr,left,mid);
    //对基准值之后的元素进行交换排序
    _QuickSort(arr,mid + 1,right);

}

//快速排序
void QuickSort(int arr[],int n)
{
    if(arr == NULL || n <= 1)
    {
        return;
    }
    //对整个区间的元素进行快速排序
    int left = 0;
    int right = n;
    _QuickSort(arr,left,right);
    return;
}

//交换法
//int Pattern1(int arr[],int left,int right)
//{
//    //该函数用于给基准值找一个合适的位置，
//    //使得在基准值之前的元素都小于等于基准值
//    //在基准值之后的元素都大于等于基准值
//    //所以要先从前往后遍历使数组前面的元素小于等于基准值
//    //从后往前遍历使后面的元素大于等于基准值
//    //当两个遍历索引相遇时，一定找到了小于基准值和大于据准值元素的分界点
//    //此时将分界点处的值替换为基准值即可保证上述的要求
//
//
//    //如果数组只有一个元素，则基准值直接放置在起始位置即可
//    if(right - left <= 1)
//    {
//        return left;
//    }
//    //从起始位置开始往后遍历寻找大于基准值的数组元素
//    int left_index = left;
//    int right_index = right - 1;
//    //从末尾位置开始往前遍历寻找小于基准值的数组元素
//    //将基准值设置为所在区间的最后一个元素值
//    int basic_value = arr[right - 1];
//
//    while(left_index < right_index)
//    {
//        //如果从前往后找到大于基准值的元素，就停下来
//        while(left_index < right_index && arr[left_index] <= basic_value)
//        {
//            left_index++;
//        }
//        //如果从后往前找到小于基准值的元素，就停下来
//        while(left_index < right_index && arr[right_index] >= basic_value)
//        {
//            right_index--;
//        }
//        //交换停下来的两个值
//        Swap(&arr[left_index],&arr[right_index]);
//    }
//    Swap(&arr[left_index],&arr[right - 1]);
//    return left_index;
//}

////递归函数
//void _QuickSort(int arr[],int left,int right)
//{
//    if(arr == NULL || right - left <= 1)
//    {
//        return;
//    }
//    //先找一个基准值，这里设置数组最后一个元素基准值
//    //找到放置基准值的位置，使得在该位置之前的数组元素小于等于基准值
//    //在该位置之后的数组元素大于等于基准值
//
//    //int mid = Pattern1(arr,left,right);
//    int mid = Pattern2(arr,left,right);
//   
//    _QuickSort(arr,left,mid);
//    _QuickSort(arr,mid + 1,right);
//}
//void QuickSort(int arr[],int size)
//{
//    if(arr == NULL || size <= 1)
//    {
//        return;
//    }
//    int left = 0;
//    int right = size;
//    
//    _QuickSort(arr,left,right);
//}

///////////////////////////
//快速排序（非递归）
///////////////////////////

void QuickSortByLoop(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }

    SeqStack stack;//定义栈
    InitSeqStack(&stack);//初始化栈
    //入栈整个待排序序列的首位坐标
    SeqStackPush(&stack,0);
    SeqStackPush(&stack,size);

    int left;
    int right;

    while(1)
    {
        //取栈顶元素作为带排序序列的尾坐标
        int ret = SeqStackTop(&stack,&right);
        if(ret == -1)//栈定为空，带排序序列处理完
        {
            return;
        }
        //出栈后再取栈顶元素
        SeqStackPop(&stack);
        //此时的栈定元素必为带排序序列的首坐标
        SeqStackTop(&stack,&left);
        //出栈栈顶元素
        SeqStackPop(&stack);
        //如果带排序序列元素个数小于等于1，则该序列必然已经排好序
        //且不能在分为更小的序列，也就不需要再进行排序再进行入栈了
        if(right - left <= 1)
        {
            continue;
        }
        //对带排序序列进行排序处理
        int mid = Pattern1(arr,left,right);
        //将带排序序列分为两部分分别入栈，进行处理
        SeqStackPush(&stack,left);
        SeqStackPush(&stack,mid);
        SeqStackPush(&stack,mid + 1);
        SeqStackPush(&stack,right);
    }
    return;
}

/////////////////////////////
//测试代码
////////////////////////////

#include<stdio.h>
#define TEST_HANDLE printf("=================%s==============\n",__FUNCTION__)

void Print(int arr[],uint64_t size)
{
    int index = 0;
    for(;index < size;index++)
    {
        printf("%d ",arr[index]);
    }
    printf("\n");
}

//测试冒泡排序（从后往前冒）
void TestBubbleSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    BubbleSort(arr,size,Greater);
    Print(arr,size);


    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    BubbleSort(arr1,size1,Greater);
    Print(arr1,size1);
    return;
}
//测试冒泡排序（从后往前冒）
void TestBubbleSortEx()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    BubbleSortEx(arr,size,Greater);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    BubbleSortEx(arr1,size1,Greater);
    Print(arr1,size1);
    return;
}
//测试选择排序
void TestSelectSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    SelectSort(arr,size,Greater);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    SelectSort(arr1,size1,Greater);
    Print(arr1,size1);
    return;
}

//测试插入排序
void TestInsertSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    InsertSort(arr,size,Greater);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    InsertSort(arr1,size1,Greater);
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
    ShellSort(arr,size,Greater);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    ShellSort(arr1,size1,Greater);
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
//测试非递归归幷排序
void TestMergeByLoopSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    MergeSortByLoop(arr,size);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    MergeSortByLoop(arr1,size1);
    Print(arr1,size1);
    return;
}
//测试快速排序
void TestQuickSort()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    QuickSort(arr,size);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    QuickSort(arr1,size1);
    Print(arr1,size1);
    return;
}
//测试非递归快速排序
void TestQuickSortByLoop()
{
    TEST_HANDLE;
    int arr[] = {2,4,1,5,8};
    uint64_t size = sizeof(arr)/sizeof(arr[0]);
    QuickSortByLoop(arr,size);
    Print(arr,size);

    int arr1[] = {2};
    uint64_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    QuickSortByLoop(arr1,size1);
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
    TestMergeByLoopSort();
    TestQuickSort();
    TestQuickSortByLoop();
    return 0;
}
