

//三种迷宫相关的问题

#include<stdio.h>

#include "seqstack.h"

//1. 首先要设置一张迷宫地图，然后将其打印出来
//   迷宫地图包括两部分，一部分是迷宫的位置坐标，另一部分是该位置处的状态：是墙还是路
//   所以该迷宫地图可由一个二维数组来表示，二位数组的横纵坐标表示迷宫各处的位置坐标，数组元素表示各位置处的状态
//   为了提取迷宫中各处的状态或对各处的状态进行操作，还需一个结构体表示迷宫各处的位置信息，即行列坐标位置
//   其中，迷宫地图用6*6的二位数组进行表示
//   其次，在迷宫中用0表示墙，1表示路
#define ROW 6//迷宫的行数
#define COL 6//迷宫的列数

//该结构体用于表示迷宫的地图,数组中存放墙和路
typedef struct Maze
{
    int map[ROW][COL];
}Maze;

//该结构体用于表示迷宫各处的行，列坐标
//typedef struct Point
//{
//    int row;//横坐标
//    int col;//列坐标
//}Point;

//初始化迷宫地图
void MazeInit(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    //因为二维数组只有在初始化是才能对数组元素全部赋值
    //在赋值时只能单个赋值
    int temp[ROW][COL] = 
    {
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,1,0,0,0},
        {0,1,0,1,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0}
    };

    int row = 0;
    for(;row < ROW;++row)
    {
        int col = 0;
        for(;col < COL;++col)
        {
            maze->map[row][col] = temp[row][col];
        }
    }
}

//打印迷宫地图
void MazePrint(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    int row = 0;
    for(;row < ROW;++row)
    {
        int col = 0;
        for(;col < COL;++col)
        {
            printf("%2d ",maze->map[row][col]);
        }
        printf("\n");
    }
}

//2. 开始进入迷宫寻找出口，此时要探索迷宫需要知道迷宫各处的状态信息，所以需要传参迷宫
//   同时，要从迷宫入口进入，所以还需要传参迷宫的入口点位置
//   因为迷宫中各处的位置信息有行列两个坐标，所以需要两个变量来表示，
//   为方便起见，将横总坐标封装在一个结构体中，用一个结构体变量表示位置信息

/////////////////////////////////////////////////////////////////
//round1:寻找迷宫出口(利用递归函数的调用栈来存放探索过的位置信息)
/////////////////////////////////////////////////////////////////

//判断当前点能否落脚
int CanStay(Maze* maze,Point cur)
{
    if(cur.row < 0 || cur.row >= ROW || cur.col < 0 || cur.col >= COL)
    {
        //当前点的位置在地图之外，所以不能落脚
        return 0;
    }

    if(maze->map[cur.row][cur.col] == 1)
    {
        //说明是路，且是未走过的路，说明可以落脚
        return 1;
    }
    else
    {
        return 0;
    }
}

//标记走过的路
void Mark(Maze* maze,Point cur)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }

    maze->map[cur.row][cur.col] = 2;
    return;
}

//判断是否为出口点
int IsExit(Point cur,Point entry)
{
    if(cur.row == entry.row && cur.col == entry.col)
    {
        //出口点为入口点
        return 0;
    }
    if(cur.row == 0 || cur.row == ROW - 1 || cur.col == 0 || cur.col == COL - 1)
    {
        //当前点在边界上,说明是出口点
        return 1;
    }
    else
    {
        return 0;
    }
}




//递归辅助函数，不断判断当前点是否满足要求，来找到出口点
void _Path(Maze* maze,Point cur,Point entry)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }

    printf("(%d,%d)\n",cur.row,cur.col);
    //1. 首先判断当前点能否落脚，如果当前点不能落脚，直接回溯出函数的调用栈
    if(CanStay(maze,cur) == 0)
    {
        return;
    }
    //2. 如果能落脚，表示该位置可以走，就对其进行标记表示已经走过
    Mark(maze,cur);
    //3. 判断当前点是否是出口，如果是出口，说明找到了出口，直接打印消息返回即可
    if(IsExit(cur,entry) == 1)
    {
        printf("找到一条出路\n");
        return;
    }
    //4. 如果不是出口，就从当前的四周点进行深度优先探索(上，右，下，左顺时针进行)
    Point up = cur;
    up.row -= 1;
    _Path(maze,up,entry);

    Point right = cur;
    right.col += 1;
    _Path(maze,right,entry);

    Point down = cur;
    down.row += 1;
    _Path(maze,down,entry);

    Point left = cur;
    left.col -= 1;
    _Path(maze,left,entry);
    //5. 如果四周点都已经探索完，就回溯探索其他的路
    return;
}


//根据入口点找迷宫的出口
void Path(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    //从入口处开始探索，判断当前点是否满足继续走下去的要求
    //需要一个辅助函数判断到当前点是否满足要求
    _Path(maze,entry,entry);//其中第一个entry表示当前点的位置信息，第二个entry表示入口点的位置信息
    return;
}

///////////////////////////////////////////////////
//round2:在迷宫中找到出口，自己设置栈来保存走过的路
///////////////////////////////////////////////////

void PathStack(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        return;
    }

    SeqStack stack;
    InitSeqStack(&stack);
    //1. 首先判断入口点能不能落脚，如果不能落脚，直接退出返回即可
    if(CanStay(maze,entry) == 0)
    {
        return;
    }
    //2. 入口点能落脚，说明入口点可以走，然后对入口点进行标记，将入口点入栈
    Mark(maze,entry);
    SeqStackPush(&stack,entry);
    //3. 判断入口点是否为出口点，如果满足出口点的条件，就说明找到了一条出口，直接退出即可
    while(1)
    {
        Point cur;
        int ret = SeqStackTop(&stack,&cur);
        if(ret == -1)
        {
            //栈为空，说明回溯结束，没有出口
            printf("没有出口\n");
            return;
        }
        printf("(%d,%d)\n",cur.row,cur.col);
        if(IsExit(cur,entry) == 1)
        {
            printf("找到了一个出口\n");
            return;
        }
        //4. 如果不是出口，就顺时针探测入口点的四周点，将四周点作为新的当前点就行探索
        //5. 如果新的当前点能够落脚，就进行标记并入栈，然后判断当前点是否为出口等等
        Point up = cur;
        up.row -= 1;
        if(CanStay(maze,up) == 1)
        {
            Mark(maze,up);
            SeqStackPush(&stack,up);
            continue;
        }

        //6. 如果当前点不能落脚，就探测下一个四周点
        Point right = cur;
        right.col += 1;
        if(CanStay(maze,right) == 1)
        {
            Mark(maze,right);
            SeqStackPush(&stack,right);
            continue;
        }

        Point down = cur;
        down.row += 1;
        if(CanStay(maze,down) == 1)
        {
            Mark(maze,down);
            SeqStackPush(&stack,down);
            continue;
        }

        Point left = cur;
        left.col -= 1;
        if(CanStay(maze,left) == 1)
        {
            Mark(maze,left);
            SeqStackPush(&stack,left);
            continue;
        }
        //6. 如果当前点能落脚，就将当前点入栈，并标记，然后判断当前点是否为出口
        //7. 如果四周点都已经探索完，就将当前点出栈，探索其他路径
        SeqStackPop(&stack);
    }
}

////////////////////////////////////////////////////////////////////////////
//round3:找到多出口路径中的最短路，利用递归函数的调用栈来存放探索过的位置信息
////////////////////////////////////////////////////////////////////////////

//初始化迷宫地图
void MazeInit1(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    //因为二维数组只有在初始化是才能对数组元素全部赋值
    //在赋值时只能单个赋值
    int temp[ROW][COL] = 
    {
        {0,1,0,0,0,0},
        {0,1,0,0,0,0},
        {1,1,1,1,1,1},
        {0,1,0,1,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0}
    };

    int row = 0;
    for(;row < ROW;++row)
    {
        int col = 0;
        for(;col < COL;++col)
        {
            maze->map[row][col] = temp[row][col];
        }
    }
}

void PathCopy(SeqStack* from,SeqStack* to)
{
    if(from == NULL || to == NULL)
    {
        //非法输入
        return;
    }

    //1. from比to长
    if(from->size > to->capacity)
    {
        Destory(to);
        to->capacity = from->capacity;
        to->size = from->size;
        to->data = (SeqStackType*)malloc(to->capacity*sizeof(SeqStackType));

    }
    //2. from比to短
    //3. from和to相等
    //此时不做处理

    //赋值位置信息
    int i = 0;
    for(;i < from->size;++i)
    {
        to->data[i] = from->data[i];
    }
    return;
}

void _PathShort(Maze* maze,Point cur,Point entry,SeqStack* cur_path,SeqStack* short_path)
{
    if(maze == NULL || cur_path == NULL || short_path == NULL)
    {
        //非法输入
        return;
    }

    //1. 首先判断当前点能否落脚，如果当前点不能落脚,则回溯退出当前的调用栈
    if(CanStay(maze,cur) == 0)
    {
        return;
    }
    //2. 如果能落脚，就标记当前点表示走过该点，并将该当前点入栈到当前路径中
    Mark(maze,cur);
    SeqStackPush(cur_path,cur);
    //3. 判断当前点是否是出口，如果是出口点,说明找到了一个出口
    if(IsExit(cur,entry) == 1)
    {
        printf("找到了一个出口\n");
        //   a）如果当前路径比最短路径短或最短路径为空，就将当前路径赋值给最短路径
        if(short_path->size == 0 || cur_path->size < short_path->size)
        {
            PathCopy(cur_path,short_path);
        }
        //   b）如果当前路径比最短路径长，最不做处理
        //   c）将当前点从当前路径中出栈，再进行回溯探测其他的路
        SeqStackPop(cur_path);
        return;
    }
    //4. 如果当前点不是出口，就顺时针探测当前点的四周点，将四周点作为新的当前点传给回调函数
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

    //5. 探测完四周点后，就将当前点从当前路径中出栈，回溯探测其他的路径
    SeqStackPop(cur_path);
    return;
}


void PrintShortPath(SeqStack* short_path,const char* msg)
{
    if(short_path == NULL)
    {
        return;
    }
    printf("%s\n",msg);

    int i = 0;
    for(;i < short_path->size;++i)
    {
        printf("(%d,%d)\n",short_path->data[i].row,short_path->data[i].col);
    }
}

void PathShort(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }

    //因为要找最短路径，所以需要保存当前已经走过的路径和最短路径，
    //如果当前路径比最短路径短，则将当前路径替换为最短路径
    //所以需要维护两个栈，来保存当前路径走过的位置信息和最短路径中的位置信息

    SeqStack cur_path;
    SeqStack short_path;
    InitSeqStack(&cur_path);
    InitSeqStack(&short_path);

    _PathShort(maze,entry,entry,&cur_path,&short_path);
    PrintShortPath(&short_path,"打印最短路径");
}


////////////////////////////////////////
//round4:带环多出口求最短路径
////////////////////////////////////////


//初始化迷宫地图
void MazeInit2(Maze* maze)
{
    if(maze == NULL)
    {
        //非法输入
        return;
    }
    //因为二维数组只有在初始化是才能对数组元素全部赋值
    //在赋值时只能单个赋值
    int temp[ROW][COL] = 
    {
        {0,1,0,0,0,0},
        {0,1,1,1,1,1},
        {1,1,0,1,0,0},
        {0,1,1,1,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0}
    };

    int row = 0;
    for(;row < ROW;++row)
    {
        int col = 0;
        for(;col < COL;++col)
        {
            maze->map[row][col] = temp[row][col];
        }
    }
}
//判断带环迷宫当前点能否落脚
int CanStayWithCycle(Maze* maze,Point cur,Point pre)
{
    //如果当前点在地图之外，就不能落脚
    if(cur.row < 0 || cur.row >= ROW || cur.col < 0 || cur.col >= COL)
    {
        return 0;
    }
    int cur_value = maze->map[cur.row][cur.col];
    //如果当点位置是墙，则不能落脚
    if(cur_value == 0)
    {
        return 0;
    }
    //如果当前位置是没有走过的路
    if(cur_value == 1)
    {
        return 1;
    }
    //如果当前位置已经探索过，并且它的先前点的值加1小于当前点的值，就可以落脚，否则不能落脚
    
    //如果是入口点，那它的先前点位置坐标是非法值，不能取值。此时入口点有三种状态
    //a) 在地图之外
    //b) 是墙
    //c) 是路
    //而以上三种情况在上面已经判读过，所以这里不需要在重复判断，也就是说，
    //如果使入口点，就不会走到这一步，一定属于上面三种情况，而提前返回。能走到这一步，说明当前点一定不是入口点
    //所以，就不用考虑先前点的位置非法的问题

    int pre_value = maze->map[pre.row][pre.col];
    if(pre_value + 1 < cur_value)
    {

        return 1;
    }
    else
    {
        return 0;
    }

}

void MarkWithCycle(Maze* maze,Point cur,Point pre)
{
    //如果最初是对入口点标记，直接将入口点标记为2即可
    if(pre.row == -1 && pre.col == -1)
    {
        maze->map[cur.row][cur.col] = 2;
        return;
    }
    //如果是对其他点进行标记，则将当前点的值设置为入口点的值加1即可
    int pre_value = maze->map[pre.row][pre.col];
    maze->map[cur.row][cur.col] = pre_value + 1;
    return;
}

void _PathShortWithCycle(Maze* maze,Point cur,Point entry,Point pre,SeqStack* cur_path,SeqStack* short_path)
{
    if(maze == NULL || cur_path == NULL || short_path == NULL)
    {
        //非法输入
        return;
    }

    //1. 判断当前点能否落脚，如果不能落脚，直接回溯出函数的调用栈
    if(CanStayWithCycle(maze,cur,pre) == 0)
    {
        return;
    }
    //2. 如果能落脚,就标记当前点表示走过该点，并将该当前点入栈到当前路径中
    MarkWithCycle(maze,cur,pre);
    SeqStackPush(cur_path,cur);
    //3. 判断当前点是否是出口，如果是出口
    if(IsExit(cur,entry) == 1)
    {
        printf("找到了一个出口\n");
        //  a) 如果当前路径比最短路径短或最短路径为空，就将当前路径赋值给最短路径
        if(short_path->size == 0 || cur_path->size < short_path->size)
        {
            PathCopy(cur_path,short_path);
        }
        //  b) 如果当前路径比最短路径长，就不做处理
        //  c) 然后将当前点从当前路径出栈，再回溯探索其他的路
        SeqStackPop(cur_path);
        return;
    }
    //4. 如果不是出口，就顺时针探测当前点的四周点
    Point up = cur;
    up.row -= 1;
    _PathShortWithCycle(maze,up,entry,cur,cur_path,short_path);

    Point right = cur;
    right.col += 1;
    _PathShortWithCycle(maze,right,entry,cur,cur_path,short_path);

    Point down = cur;
    down.row += 1;
    _PathShortWithCycle(maze,down,entry,cur,cur_path,short_path);

    Point left = cur;
    left.col -= 1;
    _PathShortWithCycle(maze,left,entry,cur,cur_path,short_path);


    //5. 如果四周点都已经探索完，就将当前点从当前路径中出栈，然后回溯探测其他的路
    SeqStackPop(cur_path);
    return;
}

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
    _PathShortWithCycle(maze,entry,entry,pre,&cur_path,&short_path);
    PrintShortPath(&short_path,"打印最短路径");
    return;
}



/////////////////////////
//测试代码
/////////////////////////

#define TEST_HANDLE printf("===============%s===============\n",__FUNCTION__)

void Test()
{
    TEST_HANDLE;
    Maze maze;
    MazeInit(&maze);
    Point entry = {0,1};
    Path(&maze,entry);
    MazePrint(&maze);
}
void Test1()
{
    TEST_HANDLE;
    Maze maze;
    MazeInit(&maze);
    Point entry = {0,1};
    PathStack(&maze,entry);
    MazePrint(&maze);
}
void TestPathShort()
{
    TEST_HANDLE;
    Maze maze;
    MazeInit1(&maze);
    Point entry = {0,1};
    PathShort(&maze,entry);
    MazePrint(&maze);
}


void TestPathShortWithCycle()
{
    TEST_HANDLE;
    Maze maze;
    MazeInit2(&maze);
    Point entry = {0,1};
    PathShortWithCycle(&maze,entry);
    MazePrint(&maze);
}

int main()
{
    Test();
    Test1();
    TestPathShort();
    TestPathShortWithCycle();
    return 0;
}

