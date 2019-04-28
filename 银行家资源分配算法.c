//���м���Դ�����㷨
#include<stdio.h>
#define PNUMBER 5//���̸���
#define SNUMBER 3//��Դ�������

//��Դ�����࣬����
char stype[SNUMBER]={'A','B','C'};

//������Դ����������a����Դ��10��b����Դ��5��c����Դ��7
int avalable[SNUMBER]={10,5,7};

//ÿ�����̶�Ӧ����ɽ�����Ҫ�ĸ������͵���Դ����������ֵ̬
int pmax[PNUMBER][SNUMBER]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};

//ÿ�������Ѿ��������Դ�������ֵ̬
int allocation[PNUMBER][SNUMBER]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

//ÿһ�����̻���Ҫ����Դ
int pneed[PNUMBER][SNUMBER]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};

//��ʱ������
int request[SNUMBER];

//��ǰ���ڷ�����Դ�Ľ���
int pindex=0;

//��ʾÿһ�����̶���Դӵ�е���״
void showdate();

//���ܽ��̷��������
void accepetRequest();

//ģ�����
void SimMllocation(int pindex);

//�ع�
void rollback(int pindex);

//��ȫ�Լ��
int checkIsSafe();

int main()
{
    //���߼�

    int exit=0;

    //��ʾÿһ��������״
    showdate();

    do
    {
        //���ܽ��̷��������
        accepetRequest();

        //ģ�������Դ
        SimMllocation(pindex);

        //��ʾ������Դ��״
        showdate();

        //����Ƿ���ڰ�ȫ���У�����Ҫ��֤����һ����������ɷ���
        if(checkIsSafe()==0)
        {
            //��ǰ���̲����ڰ�ȫ���У���ǰ�������ݻع�
            rollback(pindex);
        }
        printf("�Ƿ����0/1\n");
        scanf("%d",&exit);
    }while(exit==1);
    return 0;
}

//��ʾÿһ�����̶���Դӵ�е���״
void showdate()
{
    int index=0;
    int index_=0;
    printf("��ǰ��Դ���.....\n");
    printf("��Դ������\t��Դ����\n");
    for(index=0;index<SNUMBER;index++)
    {
        printf("%c\t\t%d\n",stype[index],avalable[index]);
    }

    printf("\n\nÿһ����������Ҫ��Դ�����ֵ.........\n\n");
    printf("���̱��\t��Դ����A\t��Դ����B\t��Դ����C\n");
    for(index=0;index<PNUMBER;index++)
    {
        printf("%d\t\t",index);
        for(index_=0;index_<SNUMBER;index_++)
        {
            printf("%d\t\t",pmax[index][index_]);
        }
        printf("\n");
    }

    printf("\n\nÿһ����������������......\n\n");
    printf("���̱��\t��Դ����A\t��Դ����B\t��Դ����C\n");
    for(index=0;index<PNUMBER;index++)
    {
        printf("%d\t\t",index);
        for(index_=0;index_<SNUMBER;index_++)
        {
            printf("%d\t\t",allocation[index][index_]);
        }
        printf("\n");
    }

    printf("\n\nÿһ�����̻���Ҫ����Դ�����......\n\n");
    printf("���̱��\t��Դ����A\t��Դ����\t��Դ����C\n");
    for(index=0;index<PNUMBER;index++)
    {
        printf("%d\t\t",index);
        for(index_=0;index_<SNUMBER;index_++)
        {
            printf("%d\t\t",pneed[index][index_]);
        }
        printf("\n");
    }
    printf("---------------------------------------------------------------------------------------------\n");
}

void accepetRequest()
{
    int index=0;
    printf("��������Ҫ������Դ�Ľ��̱��(0~%d)\n",PNUMBER-1);
    //��Ҫ������Դ�Ľ���
    scanf("%d",&pindex);
    //������Ҫ������Դ�ľ�������
    for(index=0;index<SNUMBER;)
    {
        printf("������%c����Դ������\n",stype[index]);
        scanf("%d",&request[index]);
        //С�ڽ��̶���Դ�����Ҫ��
        if(request[index]<=pmax[pindex][index]&&request[index]<=avalable[index])
        {
            index++;
        }
    }
}

//ģ�����
void SimMllocation(int pindex)
{
     int index=0;
     for(index=0;index<SNUMBER;index++)
     {
         //����Դ����
         avalable[index]-=request[index];
         //��ǰ�����Ѿ��������Դ
         allocation[pindex][index]+=request[index];
         //����Ҫ����Դ
         pneed[pindex][index]-=request[index];
     }
}

//�ع�
void rollback(int pindex)
{
    int index=0;
    for(index=0;index<SNUMBER;index++)
    {
        avalable[index]+=request[index];
        allocation[pindex][index]-=request[index];
        pneed[pindex][index]+=request[index];
    }//�ع���ģ�����պ��෴
}

int checkIsSafe()
{
    int index=0;
    int index_=0;
    int count=0;
    int k=0;
    int temp[PNUMBER];
    //���µ���ԴҪ��֤ÿһ�����̶��ܵõ���Դ
    int finish[PNUMBER]={0,0,0,0,0};
    //��Դ
    int work[SNUMBER];
    for(index=0;index<SNUMBER;index++)
    {
        work[index]=avalable[index];
    }
    //���н����ҵ�
    for(index=0;index<PNUMBER;index++)
    {
        count=0;
        if(finish[index]==1)
            continue;
        //���µ���Դ�Ƿ�������ĳһ���̵���Ҫ
        for(index_=0;index_<SNUMBER;index_++)
        {
            if(pneed[index][index_]<=work[index_])
            {
                count++;
            }
            if(count==SNUMBER)
            {
                //���µ���Դ�������һ�����̵���Ҫ��Ҳ���ܻ���
                finish[index]=1;
                for(index_=0;index_<SNUMBER;index_++)
                {
                    work[index_]+=allocation[index][index_];
                }
                //���´˽��̵ı��
                temp[k]=index;
                k++;
                //��Ϊ����Դ����,���������н������Կ��ܲ������·���
                index=-1;
            }
        }
    }
        //�ж����н����������Ƿ��ܷ��䵽��Դ
        for(index=0;index<PNUMBER;index++)
        {
            //ֻҪ��һ�����̷��䲻����Դ���򲻴��ڰ�ȫ����
            if(finish[index]==0)
            {
                printf("***�����ڰ�ȫ����***");
                return 0;
            }
        }
        printf("��ȫ����............\n");
        for(index=0;index<PNUMBER;index++)
        {
            printf("%d--->",temp[index]);
        }
        printf("\n");
        return 1;
}
