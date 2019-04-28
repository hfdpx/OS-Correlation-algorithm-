//�����ҵ�����㷨

#include<bits/stdc++.h>
using namespace std;
#define TAKEIN "takein"//��Ӧ�Ľ���״̬
#define WAIT "wait"
#define RUN "run"
#define FINISH "finish"
#define PNUMBER 5//���̸���

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
} pcb;

pcb pcbs[PNUMBER];//��������

int currentTime=0;//ʱ��

int processIndex=0;//���̵ı��

void createPcbs()//���̳�ʼ������
{
    freopen("input.txt","r",stdin);//��ֻ���������ļ�
    printf("������\t����ʱ��\t����ʱ��\n");
    for(int index=0; index<PNUMBER; index++)//�������н��̣������̸���ֵ
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
void printfPcbsInfo()//��ӡ���н��̵�������Ϣ
{
    printf("��ǰʱ��Ϊ:%dʱ�����̵���Ϣ.....\n\n",currentTime);
    printf("������\t����ʱ��\t����ʱ��\t��ʼʱ��\t����ʱ��\t��תʱ��\t��Ȩ��תʱ��\t״̬\n");
    for(int index=0; index<PNUMBER; index++)
    {
        printf("%s\t%8d\t%8d\t%8d\t%8d\t%8d\t%8d\t%4s\n",pcbs[index].processName,pcbs[index].arriveTime,pcbs[index].runTime,pcbs[index].startTime,pcbs[index].endTime,pcbs[index].turnOverTime,pcbs[index].userweightTurnOverTime,pcbs[index].provessStatus);
    }
}
void sortPcbs()//������ʱ�����������
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
                minValue=pcbs[j].arriveTime;//������С��
                minIndex=j;
            }
        }
        pcb temp=pcbs[minIndex];//����
        pcbs[minIndex]=pcbs[i];
        pcbs[i]=temp;
    }
}
int selNectProcess()//��һ�����̵�ѡ���������ȴ�״̬&&����ʱ�����
{
    int result=-1;
    int minTime=100;
    for(int index=0; index<PNUMBER; index++)
    {
        if(strcmp(pcbs[index].provessStatus,WAIT)==0)//���̴��ڵȴ�״̬
        {
            if(pcbs[index].runTime<minTime)//������ʱ�����
            {
                minTime=pcbs[index].runTime;
                result=index;
            }
        }
    }
    return result;//������һ�����еĽ��̵ı��
}
int isHasProcessArrive()//�����ĳһ��ʱ�����û�н��̵���
{
    int result=-1;
    for(int index=0; index<PNUMBER; index++)
    {
        if(pcbs[index].arriveTime==currentTime)//ĳ�����̵ĵ���ʱ����ڵ�ǰʱ��
        {
            result=index;
            strcpy(pcbs[index].provessStatus,WAIT);//�ı����״̬
        }
    }
    return result;
}

void runProcess(int pindex)
{
    int runTime=pcbs[pindex].runTime;
    //���̿�ʼ����Ҫ�ı���̵������Ϣ
    pcbs[pindex].startTime=currentTime;
    pcbs[pindex].endTime=pcbs[pindex].startTime+pcbs[pindex].runTime;
    strcpy(pcbs[pindex].provessStatus,RUN);
    printfPcbsInfo();//�����ʱ���̵���Ϣ
    for(int k=1; k<=runTime; k++) //����������
    {
        currentTime++;//ʱ��ת��
        isHasProcessArrive();
        if(k==runTime)//���̽�������
        {
            //�ı���������Ϣ
            strcpy(pcbs[pindex].provessStatus,FINISH);
            pcbs[pindex].turnOverTime=pcbs[pindex].endTime-pcbs[pindex].arriveTime;
            pcbs[pindex].userweightTurnOverTime=pcbs[pindex].turnOverTime*1.0/pcbs[pindex].runTime;
        }
        printfPcbsInfo();//��ӡ���̴�ʱ��Ϣ
    }
    processIndex++;//׼��������һ������
    currentTime--;//�ջ�һ��ʱ�̣���Ϊ��һ�������ڴ�ʱ����
}
void startProcess()//��ʼ���̵ĵ���
{
    int firstArriveTime=pcbs[0].arriveTime;//��һ������Ľ���
    int nextIndex=0;
    printfPcbsInfo();
    while(1)
    {
        currentTime++;//ʱ������
        isHasProcessArrive();//������ʱ����û���µ���Ľ���
        if(currentTime<firstArriveTime)//��һ�����̶�û�е�
        {
            printfPcbsInfo();
        }
        else if(currentTime==firstArriveTime)
        {
            runProcess(0);//ִ�н���
        }
        else //��һ������ִ����ϣ�ѡ����һ������
        {
            nextIndex=selNectProcess();
            if(nextIndex!=-1)//������һ����Ҫִ�еĽ���
            {
                runProcess(nextIndex);
            }
            if(processIndex==PNUMBER)//���н���ִ�����
                break;//����ѭ��
        }
    }
}
int main()
{
    createPcbs();//���������Ϣ�ĳ�ʼ��
    sortPcbs();//���̰��յ���ʱ����������
    startProcess();//��ʼ���̵ĵ���
    return 0;
}
