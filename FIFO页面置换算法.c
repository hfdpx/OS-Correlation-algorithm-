//FIFO页面置换算法
#include <stdio.h>
#include <stdlib.h>
//数据结构  页式管理 FIFO 先进先出  单进程

#define MEMORY_MAX_BLOCKS 10//定义物理块最大数量
#define PROGRESS_MAX_PAGE 20  //定义虚拟页面的最大数量
#define PROGRESS_MAX_LENGTH 30  //定义进程的最大长度

//当前进程的相关信息
int curProPages;//当前进程虚拟页
int curMemoryBlocks;//当前进程物理块
int proLength;// 进程执行长度
int proSort[PROGRESS_MAX_LENGTH];//虚拟页执行顺序数组

typedef struct PageItem
{
    int vpage;//虚拟页的编号
    int mblock;//对应的物理号  默认不存在对应的内存块-1
    int loadTime;//该页面在内存中存在的时间
} PageItem;

PageItem pageList[PROGRESS_MAX_PAGE];//页表：

int memoryAllocInfo[MEMORY_MAX_BLOCKS];//内存物理块分配信息，某个内存块放某个页面

//初始化函数
void init()
{
    int i=0;
    curProPages=5;//虚拟页面数量
    curMemoryBlocks=3;//内存块数量
    proLength=7;//虚拟页执行顺序数组长度
    proSort[0]=2;//存放的是虚拟页的编号
    proSort[1]=4;
    proSort[2]=3;
    proSort[3]=0;
    proSort[4]=1;
    proSort[5]=2;
    proSort[6]=4;
    for(i=0; i<curProPages; i++) //页表的初始化
    {
        pageList[i].vpage=i;
        pageList[i].mblock=-1;
        pageList[i].loadTime=0;
    }
    for(i=0; i<curMemoryBlocks; i++) //内存块的初始化
    {
        memoryAllocInfo[i]=-1;
    }
}

void showInfo()
{
    //页表信息打印
    printf("-------------------------------------------------------------\n");
    printf("页表信息：\n");
    printf("页号\t页对应的内存块编号\t页面在内存中存活的时间\n");
    int i;
    for(i=0; i<curProPages; i++)
    {
        printf("%d\t\t%d\t\t\t%d\n",pageList[i].vpage,pageList[i].mblock,pageList[i].loadTime);
    }
    printf("\n");
    printf("内存块信息表:\n");
    printf("内存块地址\t存放在此的页面\n");
    for(i=0; i<curMemoryBlocks; i++)
    {
        printf("%d\t\t%d\n",i,memoryAllocInfo[i]);
    }
    printf("-------------------------------------------------------------\n\n\n");
}

//页表中已经存在于内存的虚拟页的时间加一个点
void extnedTime()
{
    int i=0;
    for(i=0; i<curProPages; i++)
    {
        if(pageList[i].mblock!=-1)
        {
            pageList[i].loadTime+=1;
        }

    }
}

//检查物理内存中是否有空闲的块
int  findFreeBlock()
{
    int i=0;
    for(i=0; i<curMemoryBlocks; i++)
    {
        if(memoryAllocInfo[i]==-1)
        {
            return i;
        }
    }
    return -1;//返回-1表示不存在空闲内存块
}

//FIFO淘汰
//找到在内存块中存活时间最久的页面
int fifoPage()
{

    int i=0;
    int maxTime=-1;
    int vpage=-1;
    for(i=0; i<curProPages; i++)
    {
        if(pageList[i].mblock==-1)
        {
            continue;
        }
        if(pageList[i].loadTime>maxTime)
        {
            maxTime=pageList[i].loadTime;
            vpage=i;
        }
    }
    return vpage;
}

void fifo()
{
    //开始程序执行，调用虚拟机
    int index;
    int vpage;
    int fpage;
    int freeIndex;
    for(index=0; index<proLength; index++)
    {
        vpage=proSort[index];
        //检查是否已经分配物理页
        if(pageList[vpage].mblock!=-1)
        {
            //对于已经存在于内存的虚拟页都必须加一个时间点
            extnedTime();
        }
        else
        {
            //说明虚拟页没有在内存中
            //检查内存中是否有空闲块
            freeIndex=findFreeBlock();
            if(freeIndex!=-1)
            {
                memoryAllocInfo[freeIndex]=vpage;
                pageList[vpage].mblock=freeIndex;
                extnedTime();
            }
            else
            {
                //空闲区没有
                //查页表：淘汰最长时间
                fpage=fifoPage();
                //找到在内存中所占有的物理块
                freeIndex=pageList[fpage].mblock;
                //更新淘汰的虚拟页的相关信息
                pageList[fpage].loadTime=0;
                pageList[fpage].mblock=-1;
                //更新分配情况
                memoryAllocInfo[freeIndex]=vpage;
                //更新当前调到内存中的虚页的信息
                pageList[vpage].mblock=freeIndex;
                extnedTime();
            }
        }
        showInfo();
    }
}

int main()
{
    //初始化(交互)
    init();
    //显示（）
    showInfo();
    //核心逻辑（）
    fifo();
    return 0;
}
