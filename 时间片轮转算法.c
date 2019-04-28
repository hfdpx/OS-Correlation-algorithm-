//时间片轮转算法
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TAKEIN "takein"//对应的进程状态
#define WAIT "wait"
#define RUN "run"
#define FINISH "finish"
#define PNUMBER 5//进程个数
#define TRUE 1
#define FALSE 0

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
    int runTimeed; //进程已经运行的时间
} pcb;

pcb pcbs[PNUMBER];//进程数组

int currentTime=0;//时间

int processIndex=0;//进程的编号

int cpuTime=2;//时间片

int size=PNUMBER;//进程数组中的有效值

void createPcbs()//进程初始化函数
{
    freopen("input.txt","r",stdin);//以只读操作读文件
    printf("进程名\t到达时间\t运行时间\n");
    int index;
    for(index=0; index<PNUMBER; index++)//遍历所有进程，给进程赋初值
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

void movePcbs(int pindex)
{
    int index=0;
    pcb temp=pcbs[pindex];//需要移动的进程
    for(index=pindex;index<size-1;index++)
    {
        pcbs[index]=pcbs[index+1];//后面的进程全部前移一位
    }
    pcbs[size-1]=temp;//目标进程移到数组尾部
}//享受过cpu服务的进程移到进程数组的尾部，采用队列实现

void printfPcbsInfo()//打印所有进程的所有信息
{
    int index=0;
    printf("当前时间为:%d时各进程的信息.....\n\n",currentTime);
    printf("进程名\t到达时间\t运行时间\t开始时间\t结束时间\t周转时间\t带权周转时间\t状态\n");
    for(index=0; index<PNUMBER; index++)
    {
        printf("%s\t%8d\t%8d\t%8d\t%8d\t%8d\t%8d\t%4s\n",pcbs[index].processName,pcbs[index].arriveTime,pcbs[index].runTime,pcbs[index].startTime,pcbs[index].endTime,pcbs[index].turnOverTime,pcbs[index].userweightTurnOverTime,pcbs[index].provessStatus);
    }
}

void sortPcbs()//按到达时间的升序排序
{
    int minIndex=0,minValue=0,i,j;
    for(i=0; i<PNUMBER; i++)
    {
        minIndex=i;
        minValue=pcbs[i].arriveTime;
        for(j=i; j<PNUMBER; j++)
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

int selNextProcess()//选择下一个进程，要求，最近的等待进程
{
    int result=-1;
    int index=0;
    for(index=0;index<size;index++)
    {
        if(strcmp(pcbs[index].provessStatus,WAIT)==0)
        {
            return index;
        }
    }
    return result;
}

void removeFromPcbs(int pindex)//删除完成任务的进程
{
    movePcbs(pindex);
    size--;//数组逻辑长度缩小，达到移除效果
}

int isHasProcessArrive()//检查在某一个时间点有没有进程到达
{
    int result=-1;
    int index=0;
    for(index=0; index<PNUMBER; index++)
    {
        if(pcbs[index].arriveTime==currentTime)//某个进程的到达时间等于当前时间
        {
            result=index;
            strcpy(pcbs[index].provessStatus,WAIT);//改变进程状态
        }
    }
    return result;
}

int proIsEnd(int pindex)//判断一个进程是否完成
{
    if(pcbs[pindex].runTime==pcbs[pindex].runTimeed)
    {
        currentTime++;//当前时间走到
        isHasProcessArrive();//判断是否有新到达进程
        strcpy(pcbs[pindex].provessStatus,FINISH);//进程相关信息的改变
        pcbs[pindex].turnOverTime=pcbs[pindex].endTime-pcbs[pindex].arriveTime;
        pcbs[pindex].userweightTurnOverTime=pcbs[pindex].turnOverTime*1.0/pcbs[pindex].runTime;
        removeFromPcbs(pindex);//移走完成的进程
        processIndex++;//准备下一个进程
        printfPcbsInfo();//打印此时所有进程的信息
        return TRUE;
    }
    return FALSE;
}

void runProcess(int pindex)
{
    int index=0;
    int end=FALSE;
    pcbs[pindex].startTime=currentTime;//进程开始运行时间为当前时间
    strcpy(pcbs[pindex].provessStatus,RUN);//进程状态改为运行态
    pcbs[pindex].runTimeed++;//进程已经运行时间加一
    printfPcbsInfo();

    if(proIsEnd(pindex)==TRUE)//检查在当前时间片下进程是否已经结束
    {
        currentTime--;
        return ;
    }

    if(cpuTime-1>=1)//时间片没有用完
    {
        for(index=0;index<cpuTime-1;index++)
        {
            currentTime++;
            isHasProcessArrive();
            pcbs[index].runTimeed++;
            printfPcbsInfo();
            if(proIsEnd(pindex)==TRUE)
            {
                pindex=size;
                end=TRUE;
            }
        }
    }
    if(end==FALSE)//如果在当前时间片下面进程没有结束
    {
        currentTime++;
        strcpy(pcbs[pindex].provessStatus,WAIT);
        movePcbs(pindex);
        printfPcbsInfo();
    }
    currentTime--;
}

void startProcess()
{
    int firstArriveTime=pcbs[0].arriveTime;
    int nextIndex=0;
    while(1)
    {
        currentTime++;
        isHasProcessArrive();//检查当前时间有没有进程到达
        if(currentTime<firstArriveTime)
        {
            printfPcbsInfo();
        }else if(currentTime==firstArriveTime)
        {
            runProcess(0);//执行进程
        }else
        {
            nextIndex=selNextProcess();
            if(nextIndex!=-1)
            {
                runProcess(nextIndex);
            }else
            {
                printfPcbsInfo();
            }
        }
        if(processIndex==PNUMBER)
            break;
    }
}

int main()
{
    createPcbs();
    sortPcbs();
    startProcess();
    return 0;
}
