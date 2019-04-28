//最短作业优先算法

#include<bits/stdc++.h>
using namespace std;
#define TAKEIN "takein"//对应的进程状态
#define WAIT "wait"
#define RUN "run"
#define FINISH "finish"
#define PNUMBER 5//进程个数

typedef struct pcb
{
    char processName[20];//进程名称
    int arriveTime;//进程到达时间
    int startTime;//进程开始时间
    int endTime;//进程结束时间
    int runTime;//进程运行时间大小
    int turnOverTime;//周转时间
    int userweightTurnOverTime;//带权周转时间
    char provessStatus[10];//进程状态
} pcb;

pcb pcbs[PNUMBER];//进程数组

int currentTime=0;//时间

int processIndex=0;//进程的编号

void createPcbs()//进程初始化函数
{
    freopen("input.txt","r",stdin);//以只读操作读文件
    printf("进程名\t到达时间\t运行时间\n");
    for(int index=0; index<PNUMBER; index++)//遍历所有进程，给进程赋初值
    {
        scanf("%s",pcbs[index].processName);
        scanf("%d",&pcbs[index].arriveTime);
        scanf("%d",&pcbs[index].runTime);
        pcbs[index].endTime=0;
        pcbs[index].startTime=0;
        pcbs[index].turnOverTime=0;
        pcbs[index].userweightTurnOverTime=0;
        strcpy( pcbs[index].provessStatus,TAKEIN);
        printf("%s  \t%d             \t%d\n", pcbs[index].processName, pcbs[index].arriveTime, pcbs[index].runTime);
    }
    printf("\n***********************************************\n");
}
void printfPcbsInfo()//打印所有进程的所有信息
{
    printf("当前时间为:%d时各进程的信息.....\n\n",currentTime);
    printf("进程名\t到达时间\t运行时间\t开始时间\t结束时间\t周转时间\t带权周转时间\t状态\n");
    for(int index=0; index<PNUMBER; index++)
    {
        printf("%s\t%8d\t%8d\t%8d\t%8d\t%8d\t%8d\t%4s\n",pcbs[index].processName,pcbs[index].arriveTime,pcbs[index].runTime,pcbs[index].startTime,pcbs[index].endTime,pcbs[index].turnOverTime,pcbs[index].userweightTurnOverTime,pcbs[index].provessStatus);
    }
}
void sortPcbs()//按到达时间的升序排序
{
    int minIndex=0,minValue=0;
    for(int i=0; i<PNUMBER; i++)
    {
        minIndex=i;
        minValue=pcbs[i].arriveTime;
        for(int j=i; j<PNUMBER; j++)
        {
            if(pcbs[j].arriveTime<minValue)
            {
                minValue=pcbs[j].arriveTime;//保存最小的
                minIndex=j;
            }
        }
        pcb temp=pcbs[minIndex];//交换
        pcbs[minIndex]=pcbs[i];
        pcbs[i]=temp;
    }
}
int selNectProcess()//下一个进程的选择，条件：等待状态&&运行时间最短
{
    int result=-1;
    int minTime=100;
    for(int index=0; index<PNUMBER; index++)
    {
        if(strcmp(pcbs[index].provessStatus,WAIT)==0)//进程处于等待状态
        {
            if(pcbs[index].runTime<minTime)//且运行时间最短
            {
                minTime=pcbs[index].runTime;
                result=index;
            }
        }
    }
    return result;//返回下一个运行的进程的编号
}
int isHasProcessArrive()//检查在某一个时间点有没有进程到达
{
    int result=-1;
    for(int index=0; index<PNUMBER; index++)
    {
        if(pcbs[index].arriveTime==currentTime)//某个进程的到达时间等于当前时间
        {
            result=index;
            strcpy(pcbs[index].provessStatus,WAIT);//改变进程状态
        }
    }
    return result;
}

void runProcess(int pindex)
{
    int runTime=pcbs[pindex].runTime;
    //进程开始，需要改变进程的相关信息
    pcbs[pindex].startTime=currentTime;
    pcbs[pindex].endTime=pcbs[pindex].startTime+pcbs[pindex].runTime;
    strcpy(pcbs[pindex].provessStatus,RUN);
    printfPcbsInfo();//输出此时进程的信息
    for(int k=1; k<=runTime; k++) //进程运行中
    {
        currentTime++;//时间转动
        isHasProcessArrive();
        if(k==runTime)//进程结束条件
        {
            //改变进程相关信息
            strcpy(pcbs[pindex].provessStatus,FINISH);
            pcbs[pindex].turnOverTime=pcbs[pindex].endTime-pcbs[pindex].arriveTime;
            pcbs[pindex].userweightTurnOverTime=pcbs[pindex].turnOverTime*1.0/pcbs[pindex].runTime;
        }
        printfPcbsInfo();//打印进程此时信息
    }
    processIndex++;//准备运行下一个进程
    currentTime--;//收回一个时刻，因为下一个进程在此时运行
}
void startProcess()//开始进程的调度
{
    int firstArriveTime=pcbs[0].arriveTime;//第一个到达的进程
    int nextIndex=0;
    printfPcbsInfo();
    while(1)
    {
        currentTime++;//时间流动
        isHasProcessArrive();//检查这个时候有没有新到达的进程
        if(currentTime<firstArriveTime)//第一个进程都没有到
        {
            printfPcbsInfo();
        }
        else if(currentTime==firstArriveTime)
        {
            runProcess(0);//执行进程
        }
        else //第一个进程执行完毕，选择下一个进程
        {
            nextIndex=selNectProcess();
            if(nextIndex!=-1)//存在下一个将要执行的进程
            {
                runProcess(nextIndex);
            }
            if(processIndex==PNUMBER)//所有进程执行完毕
                break;//跳出循环
        }
    }
}
int main()
{
    createPcbs();//进程相关信息的初始化
    sortPcbs();//进程按照到达时间升序排序
    startProcess();//开始进程的调度
    return 0;
}
