#include<stdio.h>
#include"seqstack.h"

//定义迷宫地图的最大行列数
#define MAX_ROW 6
#define MAX_COL 6

typedef int MazeType;//迷宫地图由整型数字表示

//定义迷宫的结构
typedef struct Maze
{
    //通过数组来存放迷宫的地图
    MazeType map[MAX_ROW][MAX_COL];
}Maze;


//typedef struct Point
//{
//    int row;//某个位置所在的行数
//    int col;//某个位置所在的列数
//}Point;

//初始化迷宫地图
void MazeInit(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }

    MazeType tmp[MAX_ROW][MAX_COL] = 
    {
        {0,0,1,0,0,0},
        {0,0,1,1,0,0},
        {0,0,1,1,0,0},
        {0,0,1,1,1,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0}
    };


    int row = 0;
    for(;row < MAX_ROW;++row)
    {
        int col = 0;
        for(;col < MAX_COL;++col)
        {
            maze->map[row][col] = tmp[row][col];
        }
    }
    return;
}
void MazeInit1(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }

    MazeType tmp[MAX_ROW][MAX_COL] = 
    {
        {0,0,1,0,0,0},
        {0,0,1,1,1,0},
        {1,1,1,0,0,0},
        {0,0,1,0,1,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0}
    };


    int row = 0;
    for(;row < MAX_ROW;++row)
    {
        int col = 0;
        for(;col < MAX_COL;++col)
        {
            maze->map[row][col] = tmp[row][col];
        }
    }
    return;
}

//输出迷宫地图
void MazePrint(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    int row = 0;
    for(;row < MAX_ROW;++row)
    {
        int col = 0;
        for(;col < MAX_COL;++col)
        {
            printf("%2d ",maze->map[row][col]);
        }
        printf("\n");
    }
    return;
}

//判断是否为落脚点函数
int CanStay(Maze* maze,Point fp)
{
    if(maze == NULL)
    {
        //非法输入
        return 0;
    }

    //如果当前点不在地图范围内，一定不能落脚
    if(fp.row < 0 || fp.row >= MAX_ROW || fp.col < 0 || fp.col >= MAX_COL)
    {
        return 0;
    }
    
    //如果当前点为1，表示能落脚
    if(maze->map[fp.row][fp.col] == 1)
    {
        return 1;
    }
    //为0或为2表示不能落脚
    else
    {
        return 0;
    }
}

//标记当前点
void Mark(Maze* maze,Point fp)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    //如果当前点不在地图范围内，一定不能标记
    if(fp.row < 0 || fp.row >= MAX_ROW || fp.col < 0 || fp.col >= MAX_COL)
    {
        return;
    }
    maze->map[fp.row][fp.col] = 2;
    return;
}

//判断是否为出口点
int IsExit(Maze* maze,Point fp,Point entry)
{
    if(maze == NULL)
    {
        //非法输入
        return 0;
    }
    //入口点一定不是出口点
    if(fp.row == entry.row && fp.col == entry.col)
    {
        return 0;
    }

    //如果当前点在边界上，说明是出口点
    if(fp.row == 0 || fp.row == MAX_ROW - 1 || fp.col == 0 || fp.col == MAX_COL - 1)
    {
        return 1;
    }
    //否则不是出口点
    return 0;
}


///////////////////////////////////////////
//方法一：利用递归的调用栈对走过的路进行压栈
///////////////////////////////////////////

//cur表示当前点，entry表示入口点
void _Path(Maze* maze,Point cur,Point entry)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    printf("cur:%d %d\n",cur.row,cur.col);
    //1.首先判断当前点内否落脚，不能落脚，直接返回上一级函数，相当于出栈回溯
    if(CanStay(maze,cur) == 0)//当前点不能落脚
    {
        return;
    }
    //2.如果能落脚，标记当前点
    Mark(maze,cur);
    //3.判断当前点是否为出口点，为出口点则打印消息直接返回
    if(IsExit(maze,cur,entry) == 1)
    {
        printf("find a path\n");
        return;
    }
    //4.不是出口点，探测当前点的四周点，将当前点的四周点作为新的当前点递归调用该函数
    Point up = cur;
    up.row = up.row - 1;
    _Path(maze,up,entry);

    Point right = cur;
    right.col = right.col + 1;
    _Path(maze,right,entry);

    Point down = cur;
    down.row = down.row + 1;
    _Path(maze,down,entry);

    Point left = cur;
    left.col = left.col - 1;
    _Path(maze,left,entry);
    //5.如果四周点都不能走，就直接返回，相当于出栈回溯
    return;
}


//利用递归的调用栈对走过的路进行压栈
void Path1(Maze* maze,Point entry)
{
    _Path(maze,entry,entry);
    return;
}


///////////////////////////////
//方法2：手动设置栈
///////////////////////////////


void Path2(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }

    SeqStack seqstack;
    InitSeqStack(&seqstack);

    //1.首先判定入口点能不能落脚，不能落脚就直接返回
    if(CanStay(maze,entry) == 0)
    {
        return;
    }
    //2.能落脚，就标记并入栈
    Mark(maze,entry);
    SeqStackPush(&seqstack,entry);
    int ret;
    Point top;
    while(1)
    {
        //3.取栈顶元素
        ret = SeqStackTop(&seqstack,&top);
        if(ret == -1)
        {
            //回溯结束，还没找到出口
            return;
        }
        printf("top %d %d\n",top.row,top.col);
        if(ret == -1)//如果栈为空
        {
            //说明无路可走
            printf("no find path\n");
            return;
        }
        //3.判定栈顶元素是否为出口点，为出口点则打印消息直接返回
        if(IsExit(maze,top,entry) == 1)
        {
            printf("find a path\n");
            return;
        }
        //4.不是出口点，探测当前点的四周点能否落脚，不能落脚就继续往下走
        //5.能落脚，则标记并入栈，然会回到3进行判定
        Point up = top;
        up.row -= 1;
        if(CanStay(maze,up) == 1)
        {
            Mark(maze,up);
            SeqStackPush(&seqstack,up);
            continue;
        }

        Point right = top;
        right.col += 1;
        if(CanStay(maze,right) == 1)
        {
            Mark(maze,right);
            SeqStackPush(&seqstack,right);
            continue;
        }

        Point down = top;
        down.row += 1;
        if(CanStay(maze,down) == 1)
        {
            Mark(maze,down);
            SeqStackPush(&seqstack,down);
            continue;
        }

        Point left = top;
        left.col -= 1;
        if(CanStay(maze,left) == 1)
        {
            Mark(maze,left);
            SeqStackPush(&seqstack,left);
            continue;
        }
        //如果四周点都不能走，说明无路可走，即要出栈回溯
        SeqStackPop(&seqstack);
    }
}


/////////////////////////////
//round3 多条路径找最短路
/////////////////////////////

void PathCopy(SeqStack* from,SeqStack* to)
{
    if(from == NULL || to == NULL)
    {
        //非法输入
        return;
    }

    //1.如果from比to短或相等，直接赋值即可
    //2.如果from比to长，需要重新动态开辟内存来容纳from
        
    Destory(to);
    to->size = from->size;
    to->capacity = from->capacity;
    to->data = (SeqStackType*)malloc(to->capacity*sizeof(SeqStackType));

    int i = 0;
    for(;i < to->size;++i)
    {
        to->data[i] = from->data[i];
    }


}
void _PathShort(Maze* maze,Point cur,Point entry,SeqStack* cur_path,SeqStack* short_path)
{
    if(maze == NULL || cur_path == NULL || short_path == NULL)
    {
        //非法输入
        return;
    }

    //1.判断当前点能否落脚，不能落脚，直接返回上一级函数
    if(CanStay(maze,cur) != 1)
    {
        return;
    }

    //2.能落脚，标记当前点，并将当前点插入到当前路径中
    Mark(maze,cur);
    SeqStackPush(cur_path,cur);
    //3.如果当前点是出口点
    if(IsExit(maze,cur,entry) == 1)
    {
        printf("找到了一条路经\n");
    //  a)如果当前路径比最短路径短或者最短路径为空，就将当前路径赋值给最短路径
        if(short_path->size == 0 || cur_path->size < short_path->size)
        {
            printf("找到了一条较短的路径\n");
            PathCopy(cur_path,short_path);
        }
    //  b)如果当前路径比最短路径长，就不作处理
    //  c)然后，出栈当前路径中的点，进行回溯，继续探测其他的路径
        SeqStackPop(cur_path);
        return;
    }
    //4.如果当前点不是出口点，就继续探测当前点的四周点，以四周点为当前点递归调用该函数
    Point up = cur;
    up.row -= 1;
    _PathShort(maze,up,entry,cur_path,short_path);

    Point right = cur;
    right.col += 1;
    _PathShort(maze,right,entry,cur_path,short_path);

    Point down = cur;
    down.row += 1;
    _PathShort(maze,down,entry,cur_path,short_path);

    Point left = cur;
    left.col -= 1;
    _PathShort(maze,left,entry,cur_path,short_path);

    //5.探测完四周点后，将当前点出栈，进行回溯
    SeqStackPop(cur_path);
    return;
}

void MazeShortPathPrint(SeqStack* stack,const char* msg)
{
    if(stack == NULL)
    {
        //非法输入
        return;
    }
    printf("%s\n",msg);

    int index = 0;
    for(;index < stack->size;++index)
    {
        printf("(%d,%d)\n",stack->data[index].row,stack->data[index].col);
    }
    printf("\n");
    return;
}

void PathShort(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    SeqStack cur_path;
    SeqStack short_path;
    InitSeqStack(&cur_path);
    InitSeqStack(&short_path);

    _PathShort(maze,entry,entry,&cur_path,&short_path);
    MazeShortPathPrint(&short_path,"打印最短路径");
    return;
}

//////////////////////////////////
//round4:在带环路线中找最短路径
//////////////////////////////////
 
//初始化带环迷宫地图
void InitMazeWithCycle(Maze*maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    MazeType temp[MAX_ROW][MAX_COL] = 
    {
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,1,1},
        {1,1,1,1,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0}
    };
    int row = 0;
    for(;row < MAX_ROW;++row)
    {
        int col = 0;
        for(;col < MAX_COL;++col)
        {
            maze->map[row][col] = temp[row][col];
        }
    }
}

//打印带环迷宫地图：与上面打印函数相同

//判断带环迷宫中的点能否落脚
int CanStayWithCycle(Maze* maze,Point pre,Point cur)
{

    //1.如果当前点不在地图范围内，则不能落脚
    if(cur.row < 0 || cur.row >= MAX_ROW || cur.col < 0 || cur.col >= MAX_COL)
    {
        return 0;
    }
    //2.如果当前点的值为1,就可以落脚
    if(maze->map[cur.row][cur.col] == 1)
    {
        return 1;
    }
    //3.如果当前点的值为0，说明为墙，不可以落脚
    if(maze->map[cur.row][cur.col] == 0)
    {
        return 0;
    }
    //4.如果先前点的先前点的值非法，就说明是入口点，
    //此时入口点要么为1，要么为0，要么不在地图范围内，这几钟情况上述已经判断过，
    //所以，就不必在判断了

    //取先前点处的值和当前点处的值
    MazeType pre_value = maze->map[pre.row][pre.col];
    MazeType cur_value = maze->map[cur.row][cur.col];
    //5.如果先前点的值加1大于等于当前点的值，就不能落脚
    if(pre_value + 1 >= cur_value)
    {
        return 0;
    }
    //6.否则可以落脚
    else
    {
        return 1;
    }

}

//标记当前点的值
void MarkWithCycle(Maze* maze,Point pre,Point cur)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    if(pre.row == -1 && pre.col == -1)
    {
        maze->map[cur.row][cur.col] = 2;
        return ;
    }

    MazeType pre_value = maze->map[pre.row][pre.col];
    maze->map[cur.row][cur.col] = pre_value + 1;
    return;
}

//判断当前点的特点，并保存当前路径和最短路径
void _PathShortWithCycle(Maze* maze,Point pre,Point cur,Point entry,SeqStack* cur_path,SeqStack* short_path)
{
    if(maze == NULL || cur_path == NULL || short_path == NULL)
    {
        //非法输入
        return;
    }

    //1. 首先判断当前点能否落脚，如果不能落脚，直接返回上一级函数
    if(CanStayWithCycle(maze,pre,cur) == 0)
    {
        return;
    }
    //2. 能落脚，标记当前点，并将当前点插入到当前路径中
    MarkWithCycle(maze,pre,cur);
    SeqStackPush(cur_path,cur);
    //3. 判断当前点是否为出口点
    //4. 如果当前点是出口点
    if(IsExit(maze,cur,entry) == 1)
    {
        printf("找到了一条路经\n");
        //   a)如果当前路径比最短路径短或者最短路径为空，就将当前路径赋值给最短路径
        if(short_path->size == 0 || cur_path->size < short_path->size)
        {
            printf("找到了一条较短的路径\n");
            PathCopy(cur_path,short_path);

        }
        //   b)否则不做处理
        //   c)然后将当前点从当前路径出栈，再回溯继续探测其他的路径
        SeqStackPop(cur_path);
        return;
    }
    //5. 如果当前点不是出口点，就继续探测当前点的四周点
    Point up = cur;
    up.row -= 1;
    _PathShortWithCycle(maze,cur,up,entry,cur_path,short_path);

    Point right = cur;
    right.col += 1;
    _PathShortWithCycle(maze,cur,right,entry,cur_path,short_path);

    Point down = cur;
    down.row += 1;
    _PathShortWithCycle(maze,cur,down,entry,cur_path,short_path);

    Point left = cur;
    left.col -= 1;
    _PathShortWithCycle(maze,cur,left,entry,cur_path,short_path);

    //6. 四周的点都探测完成，再将当前点从当前路径出栈回溯继续探测其他的路径
    SeqStackPop(cur_path);
    return;

}


//根据迷宫地图和入口点找到迷宫出口及最短路径
void PathShortWithCycle(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }

    SeqStack cur_path;
    SeqStack short_path;
    InitSeqStack(&cur_path);
    InitSeqStack(&short_path);

    Point pre = {-1,-1};
    //判断当前点，并保存当前路径和最短路径
    _PathShortWithCycle(maze,pre,entry,entry,&cur_path,&short_path);

    //打印最短路径
    MazeShortPathPrint(&short_path,"打印最短路径");
    
}




///////////////////////////////////
//测试代码
///////////////////////////////////

#define HANDLE_TEST printf("===============%s=============\n",__FUNCTION__)
void Test()
{
    HANDLE_TEST;
    Maze maze;
    MazeInit(&maze);
    MazePrint(&maze);
    return;
}

void Test1()
{
    HANDLE_TEST;
    Maze maze;
    MazeInit(&maze);
    Point entry = {0,2};
    Path1(&maze,entry);
    MazePrint(&maze);

    return;

}
void Test2()
{
    HANDLE_TEST;
    Maze maze;
    MazeInit(&maze);
    Point entry = {0,2};
    Path2(&maze,entry);
    MazePrint(&maze);

    return;

}
void TestShortPath()
{
    HANDLE_TEST;
    Maze maze;
    MazeInit1(&maze);
    Point entry = {0,2};
    PathShort(&maze,entry);
    MazePrint(&maze);
    return;

}

void TestShortPathWithCycle()
{
    HANDLE_TEST;
    Maze maze;
    InitMazeWithCycle(&maze);
    Point entry = {0,1};
    PathShortWithCycle(&maze,entry);
    MazePrint(&maze);
    return;
}

int main()
{
    Test();
    Test1();
    Test2();
    TestShortPath();
    TestShortPathWithCycle();
    return 0;
}

