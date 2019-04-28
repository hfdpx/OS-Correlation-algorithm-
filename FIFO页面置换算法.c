//FIFOҳ���û��㷨
#include <stdio.h>
#include <stdlib.h>
//���ݽṹ  ҳʽ���� FIFO �Ƚ��ȳ�  ������

#define MEMORY_MAX_BLOCKS 10//����������������
#define PROGRESS_MAX_PAGE 20  //��������ҳ����������
#define PROGRESS_MAX_LENGTH 30  //������̵���󳤶�

//��ǰ���̵������Ϣ
int curProPages;//��ǰ��������ҳ
int curMemoryBlocks;//��ǰ���������
int proLength;// ����ִ�г���
int proSort[PROGRESS_MAX_LENGTH];//����ҳִ��˳������

typedef struct PageItem
{
    int vpage;//����ҳ�ı��
    int mblock;//��Ӧ�������  Ĭ�ϲ����ڶ�Ӧ���ڴ��-1
    int loadTime;//��ҳ�����ڴ��д��ڵ�ʱ��
} PageItem;

PageItem pageList[PROGRESS_MAX_PAGE];//ҳ��

int memoryAllocInfo[MEMORY_MAX_BLOCKS];//�ڴ�����������Ϣ��ĳ���ڴ���ĳ��ҳ��

//��ʼ������
void init()
{
    int i=0;
    curProPages=5;//����ҳ������
    curMemoryBlocks=3;//�ڴ������
    proLength=7;//����ҳִ��˳�����鳤��
    proSort[0]=2;//��ŵ�������ҳ�ı��
    proSort[1]=4;
    proSort[2]=3;
    proSort[3]=0;
    proSort[4]=1;
    proSort[5]=2;
    proSort[6]=4;
    for(i=0; i<curProPages; i++) //ҳ��ĳ�ʼ��
    {
        pageList[i].vpage=i;
        pageList[i].mblock=-1;
        pageList[i].loadTime=0;
    }
    for(i=0; i<curMemoryBlocks; i++) //�ڴ��ĳ�ʼ��
    {
        memoryAllocInfo[i]=-1;
    }
}

void showInfo()
{
    //ҳ����Ϣ��ӡ
    printf("-------------------------------------------------------------\n");
    printf("ҳ����Ϣ��\n");
    printf("ҳ��\tҳ��Ӧ���ڴ����\tҳ�����ڴ��д���ʱ��\n");
    int i;
    for(i=0; i<curProPages; i++)
    {
        printf("%d\t\t%d\t\t\t%d\n",pageList[i].vpage,pageList[i].mblock,pageList[i].loadTime);
    }
    printf("\n");
    printf("�ڴ����Ϣ��:\n");
    printf("�ڴ���ַ\t����ڴ˵�ҳ��\n");
    for(i=0; i<curMemoryBlocks; i++)
    {
        printf("%d\t\t%d\n",i,memoryAllocInfo[i]);
    }
    printf("-------------------------------------------------------------\n\n\n");
}

//ҳ�����Ѿ��������ڴ������ҳ��ʱ���һ����
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

//��������ڴ����Ƿ��п��еĿ�
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
    return -1;//����-1��ʾ�����ڿ����ڴ��
}

//FIFO��̭
//�ҵ����ڴ���д��ʱ����õ�ҳ��
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
    //��ʼ����ִ�У����������
    int index;
    int vpage;
    int fpage;
    int freeIndex;
    for(index=0; index<proLength; index++)
    {
        vpage=proSort[index];
        //����Ƿ��Ѿ���������ҳ
        if(pageList[vpage].mblock!=-1)
        {
            //�����Ѿ��������ڴ������ҳ�������һ��ʱ���
            extnedTime();
        }
        else
        {
            //˵������ҳû�����ڴ���
            //����ڴ����Ƿ��п��п�
            freeIndex=findFreeBlock();
            if(freeIndex!=-1)
            {
                memoryAllocInfo[freeIndex]=vpage;
                pageList[vpage].mblock=freeIndex;
                extnedTime();
            }
            else
            {
                //������û��
                //��ҳ����̭�ʱ��
                fpage=fifoPage();
                //�ҵ����ڴ�����ռ�е������
                freeIndex=pageList[fpage].mblock;
                //������̭������ҳ�������Ϣ
                pageList[fpage].loadTime=0;
                pageList[fpage].mblock=-1;
                //���·������
                memoryAllocInfo[freeIndex]=vpage;
                //���µ�ǰ�����ڴ��е���ҳ����Ϣ
                pageList[vpage].mblock=freeIndex;
                extnedTime();
            }
        }
        showInfo();
    }
}

int main()
{
    //��ʼ��(����)
    init();
    //��ʾ����
    showInfo();
    //�����߼�����
    fifo();
    return 0;
}
