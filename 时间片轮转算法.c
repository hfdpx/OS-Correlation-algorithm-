//ʱ��Ƭ��ת�㷨
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TAKEIN "takein"//��Ӧ�Ľ���״̬
#define WAIT "wait"
#define RUN "run"
#define FINISH "finish"
#define PNUMBER 5//���̸���
#define TRUE 1
#define FALSE 0

typedef struct pcb
{
    char processName[20];//��������
    int arriveTime;//���̵���ʱ��
    int startTime;//���̿�ʼʱ��
    int endTime;//���̽���ʱ��
    int runTime;//��������ʱ���С
    int turnOverTime;//��תʱ��
    int userweightTurnOverTime;//��Ȩ��תʱ��
    char provessStatus[10];//����״̬
    int runTimeed; //�����Ѿ����е�ʱ��
} pcb;

pcb pcbs[PNUMBER];//��������

int currentTime=0;//ʱ��

int processIndex=0;//���̵ı��

int cpuTime=2;//ʱ��Ƭ

int size=PNUMBER;//���������е���Чֵ

void createPcbs()//���̳�ʼ������
{
    freopen("input.txt","r",stdin);//��ֻ���������ļ�
    printf("������\t����ʱ��\t����ʱ��\n");
    int index;
    for(index=0; index<PNUMBER; index++)//�������н��̣������̸���ֵ
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
    pcb temp=pcbs[pindex];//��Ҫ�ƶ��Ľ���
    for(index=pindex;index<size-1;index++)
    {
        pcbs[index]=pcbs[index+1];//����Ľ���ȫ��ǰ��һλ
    }
    pcbs[size-1]=temp;//Ŀ������Ƶ�����β��
}//���ܹ�cpu����Ľ����Ƶ����������β�������ö���ʵ��

void printfPcbsInfo()//��ӡ���н��̵�������Ϣ
{
    int index=0;
    printf("��ǰʱ��Ϊ:%dʱ�����̵���Ϣ.....\n\n",currentTime);
    printf("������\t����ʱ��\t����ʱ��\t��ʼʱ��\t����ʱ��\t��תʱ��\t��Ȩ��תʱ��\t״̬\n");
    for(index=0; index<PNUMBER; index++)
    {
        printf("%s\t%8d\t%8d\t%8d\t%8d\t%8d\t%8d\t%4s\n",pcbs[index].processName,pcbs[index].arriveTime,pcbs[index].runTime,pcbs[index].startTime,pcbs[index].endTime,pcbs[index].turnOverTime,pcbs[index].userweightTurnOverTime,pcbs[index].provessStatus);
    }
}

void sortPcbs()//������ʱ�����������
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
                minValue=pcbs[j].arriveTime;//������С��
                minIndex=j;
            }
        }
        pcb temp=pcbs[minIndex];//����
        pcbs[minIndex]=pcbs[i];
        pcbs[i]=temp;
    }
}

int selNextProcess()//ѡ����һ�����̣�Ҫ������ĵȴ�����
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

void removeFromPcbs(int pindex)//ɾ���������Ľ���
{
    movePcbs(pindex);
    size--;//�����߼�������С���ﵽ�Ƴ�Ч��
}

int isHasProcessArrive()//�����ĳһ��ʱ�����û�н��̵���
{
    int result=-1;
    int index=0;
    for(index=0; index<PNUMBER; index++)
    {
        if(pcbs[index].arriveTime==currentTime)//ĳ�����̵ĵ���ʱ����ڵ�ǰʱ��
        {
            result=index;
            strcpy(pcbs[index].provessStatus,WAIT);//�ı����״̬
        }
    }
    return result;
}

int proIsEnd(int pindex)//�ж�һ�������Ƿ����
{
    if(pcbs[pindex].runTime==pcbs[pindex].runTimeed)
    {
        currentTime++;//��ǰʱ���ߵ�
        isHasProcessArrive();//�ж��Ƿ����µ������
        strcpy(pcbs[pindex].provessStatus,FINISH);//���������Ϣ�ĸı�
        pcbs[pindex].turnOverTime=pcbs[pindex].endTime-pcbs[pindex].arriveTime;
        pcbs[pindex].userweightTurnOverTime=pcbs[pindex].turnOverTime*1.0/pcbs[pindex].runTime;
        removeFromPcbs(pindex);//������ɵĽ���
        processIndex++;//׼����һ������
        printfPcbsInfo();//��ӡ��ʱ���н��̵���Ϣ
        return TRUE;
    }
    return FALSE;
}

void runProcess(int pindex)
{
    int index=0;
    int end=FALSE;
    pcbs[pindex].startTime=currentTime;//���̿�ʼ����ʱ��Ϊ��ǰʱ��
    strcpy(pcbs[pindex].provessStatus,RUN);//����״̬��Ϊ����̬
    pcbs[pindex].runTimeed++;//�����Ѿ�����ʱ���һ
    printfPcbsInfo();

    if(proIsEnd(pindex)==TRUE)//����ڵ�ǰʱ��Ƭ�½����Ƿ��Ѿ�����
    {
        currentTime--;
        return ;
    }

    if(cpuTime-1>=1)//ʱ��Ƭû������
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
    if(end==FALSE)//����ڵ�ǰʱ��Ƭ�������û�н���
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
        isHasProcessArrive();//��鵱ǰʱ����û�н��̵���
        if(currentTime<firstArriveTime)
        {
            printfPcbsInfo();
        }else if(currentTime==firstArriveTime)
        {
            runProcess(0);//ִ�н���
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
