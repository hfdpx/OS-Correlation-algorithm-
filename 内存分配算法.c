//�ڴ�����㷨���״���Ӧ�㷨�������Ӧ�㷨�����Ӧ�㷨
#include<bits/stdc++.h>
using namespace std;
/*�����ڴ�Ĵ�СΪ100*/
#define MEMSIZE 100
/*���С�ڴ�ֵ�������ٷָ��ڴ�*/
#define MINSIZE 2

/*�ڴ�����ռ��ṹ*/
typedef struct _MemoryInfomation
{
    /*��ʼ��ַ*/
    int start;
    /*��С*/
    int Size;
    /*״̬ F:����(Free) U:ռ��(Used) E ����(End)*/
    char status;
} MEMINFO;

/*�ڴ�ռ���Ϣ��*/
MEMINFO MemList[MEMSIZE];

/*��ʾ�ڴ�״̬*/
void Display()
{
    int i,used=0;//��¼����ʹ�õ��ܿռ���
    printf("\n---------------------------------------------------\n");
    printf("%5s%15s%15s%15s","Number","start","size","status");
    printf("\n---------------------------------------------------\n");
    for(i=0; i<MEMSIZE&&MemList[i].status!='e'; i++)
    {
        if(MemList[i].status=='u')
        {
            used+=MemList[i].Size;
        }
        printf("%5d%15d%15d%15s\n",i,MemList[i].start,MemList[i].Size,MemList[i].status=='u'?"USED":"FREE");
    }
    printf("\n----------------------------------------------\n");
    printf("Totalsize:%-10d Used:%-10d Free:%-10d\n",MEMSIZE,used,MEMSIZE-used);
}

/*��ʼ�����б���*/
void InitMemList()
{
    int i;
    MEMINFO temp= {0,0,'e'};
    //��ʼ���ռ���Ϣ��
    for(i=0; i<MEMSIZE; i++)
    {
        MemList[i]=temp;
    }
    //��ʼ��ַΪ0
    MemList[0].start=0;
    //�ռ��ʼΪ���
    MemList[0].Size=MEMSIZE;
    //״̬Ϊ����
    MemList[0].status='f';
}

/*������Ӧ�㷨*/

/*�㷨ԭ�������
�����е��ڴ��������ڴ���ռ��е���ʼ��ַ������˳�����У�Ϊ��ҵ���䴢��ռ�ʱ���ӿ���������ʼ�˿�ʼ���ң�ѡ���һ������Ҫ��Ŀ��������������������ж��

�ŵ�:
1.���ͷ��ڴ������ʱ����������ڵĿհ����ͽ��кϲ���ʹ���Ϊһ���ϴ�Ŀհ���
2.���㷨��ʵ���Ǿ����ܵ����ô������ĵ͵�ַ���֣��ڸߵ�ַ����������Ļ�ϴ�Ŀհ������Ժ������Ҫ�ϴ�Ŀհ���������������

ȱ�㣺
1.�ڵ͵�ַ���ֺܿ켯�������ǳ�С�Ŀհ���������ڿհ�������ʱ�������������ӣ�Ӱ�칤��Ч�ʡ�*/


void FirstFit_new()
{
    int i,j,flag=0;
    int request;
    printf("FirstFit_new:How Many MEMORY requir?\n");
    scanf("%d",&request);
    //��������
    for(i=0; i<MEMSIZE&&MemList[i].status!='e'; i++)
    {
        //��������Ҫ�Ĵ�С,���ǿ��пռ�
        if(MemList[i].Size>=request&&MemList[i].status=='f')
        {
            //���С�ڹ涨����С���������ռ�����ȥ
            if(MemList[i].Size-request<=MINSIZE)
            {
                MemList[i].status='u';
            }
            else
            {
                //��i�����Ϣ��Ԫ�غ���
                for(j=MEMSIZE-2; j>i; j--)
                {
                    MemList[j+1]=MemList[j];
                }

                //��i�ֳ������֣�ʹ�õ͵�ַ����
                MemList[i+1].start=MemList[i].start+request;
                MemList[i+1].Size=MemList[i].Size-request;
                MemList[i+1].status='f';
                MemList[i].Size=request;
                MemList[i].status='u';
                flag=1;
            }
            break;
        }
    }
    //û���ҵ����Ϸ���Ŀռ�
    if(flag!=1||i==MEMSIZE||MemList[i].status=='e')
    {
        printf("Not Enough Memory!!\n");
    }
    Display();
}
/*���Ӧ�㷨

�㷨ԭ�������
ɨ���������з�����������������ѡһ�����Ŀ��з����ָ����ҵʹ��

�ŵ㣺����ʹ��ʣ�µĿ��з���������̫С��������Ƭ�ļ�����С������С��ҵ������ͬʱ���㷨�Ĳ���Ч�ʺܸ�

ȱ�㣺��ʹ�ô�������ȱ����Ŀ��з���
*/
void BadFit_new()
{
    int i,j,k,flag,request;
    printf("BadFit_new:How Many MEMORY requir?\n");
    scanf("%d",&request);
    j=0;
    flag=0;
    k=0;
    //��������Ҫ������ռ�
    for(i=0;i<MEMSIZE-1&&MemList[i].status!='e';i++)
    {
        if(MemList[i].Size>=request&&MemList[i].status=='f')
        {
            flag=1;
            if(MemList[i].Size>k)
            {
                k=MemList[i].Size;
                j=i;
            }
        }
    }
    i=j;
    if(flag==0)
    {
        printf("Not Enough Memory!\n");
        j=i;
    }else if(MemList[i].Size-request<=MINSIZE)
    {
        MemList[i].status='u';
    }else
    {
        for(j=MEMSIZE-2;j>i;j--)
        {
            MemList[j+1]=MemList[j];
        }
        MemList[i+1].start=MemList[i].start+request;
        MemList[i+1].Size=MemList[i].Size-request;
        MemList[i+1].status='f';
        MemList[i].Size=request;
        MemList[i].status='u';
    }
    Display();
}


//�ͷ�һ���ڴ�
void del_t()
{
    int i,number;
    printf("\nplease input the NUMBER you want stop:\n");
    scanf("%d",&number);
    //����Ŀռ���ʹ�õ�
    if(MemList[number].status=='u')
    {
        MemList[number].status='f';//��־Ϊ����
        if(MemList[number+1].status=='f')//�Ҳ�ռ�Ϊ����ϲ�
        {
            MemList[number].Size+=MemList[number].Size;//��С�ϲ�
            for(i=number+1; i<MEMSIZE-1&&MemList[i].status!='e'; i++) //i����Ŀռ���Ϣ��Ԫ�غ���
            {
                if(i>0)
                {
                    MemList[i]=MemList[i+1];
                }
            }
        }
        //���ռ������ϲ�
        if(number>0&&MemList[number-1].status=='f')
        {
            MemList[number-1].Size+=MemList[number].Size;
            for(i=number; i<MEMSIZE-1&&MemList[i].status!='e'; i++)
            {
                MemList[i]=MemList[i+1];
            }
        }
    }
    else
    {
        printf("This Number is Not Exist or is Not Used��\n");
    }
    Display();
}

/*�����Ӧ�㷨

�㷨ԭ�������
��ȫ�����������ҳ�������ҵҪ��ģ��Ҵ�С��С�Ŀ��з�����һ�ּ��㷽�������ַ�����ʹ����Ƭ����С��Ϊ��Ӧ���㷨�����з������еĿ��з���Ҫ����С������������Ա�ͷ��ʼ���ҵ�һ������Ҫ������ɷ�������

�ŵ㣺��ʹ����Ƭ������С,��������������

ȱ�㣺��������С�Ŀ�����
*/
void BestFit_new()
{
    int i,j,t,flag,request;
    printf("BestFit_new How Many MEMORY requir?\n");
    scanf("%d",&request);
    j=0;
    flag=0;
    t=MEMSIZE;
    //��������Ҫ������ռ�
    for(i=0; i<MEMSIZE&&MemList[i].status!='e'; i++)
    {
        if(MemList[i].Size>=request&&MemList[i].status=='f')
        {
            flag=1;
            if(MemList[i].Size<t)
            {
                t=MemList[i].Size;
                j=i;
            }
        }
    }
    i=j;
    if(flag==0)
    {
        printf("Not Enough Memory!\n");
        j=i;
    }
    else if(MemList[i].Size-request<=MINSIZE)  //���С�ڹ涨����С���������ռ�����ȥ
    {
        MemList[i].status='u';
    }
    else
    {
        //��i�����Ϣ��Ԫ�غ���
        for(j=MEMSIZE-2; j>i; j--)
        {
            MemList[j+1]=MemList[j];
        }

        //��i�ֳ������֣�ʹ�õ͵�ַ����
        MemList[i+1].start=MemList[i].start+request;
        MemList[i+1].Size=MemList[i].Size-request;
        MemList[i+1].status='f';
        MemList[i].Size=request;
        MemList[i].status='u';
    }
    Display();
}

int main()
{
    int x;
    InitMemList();//������ʼ��
    while(1)
    {
        printf("=================================================\n");
        printf("         1.Get a block use the FIRSTFIT method\n");
        printf("         2.Get a block use the BESTFIT method\n");
        printf("         3.Get a block use the BadFIT method\n");
        printf("         4.Free a block\n");
        printf("         5.Dispaly Mem info \n");
        printf("         6.Exit \n");
        printf("=================================================\n");
        scanf("%d",&x);
        switch(x)
        {
        case 1:
            FirstFit_new();//�״���Ӧ�㷨
            break;
        case 2:
            BestFit_new();//�����Ӧ�㷨
            break;
        case 3:
            BadFit_new();//���Ӧ�㷨
            break;
        case 4:
            del_t();//ɾ���Ѿ�ʹ����ϵĿռ�
            break;
        case 5:
            Display();//��ʾ�ڴ�������
            break;
        case 6:
            exit(0);
        }
    }
    return 0;
}
