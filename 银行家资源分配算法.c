//银行家资源分配算法
#include<stdio.h>
#define PNUMBER 5//进程个数
#define SNUMBER 3//资源种类个数

//资源的种类，三种
char stype[SNUMBER]={'A','B','C'};

//各种资源的总数量，a种资源总10，b种资源总5，c种资源总7
int avalable[SNUMBER]={10,5,7};

//每个进程对应的完成进程需要的各种类型的资源需求量，静态值
int pmax[PNUMBER][SNUMBER]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};

//每个进程已经分配的资源情况，动态值
int allocation[PNUMBER][SNUMBER]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

//每一个进程还需要的资源
int pneed[PNUMBER][SNUMBER]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};

//临时的数组
int request[SNUMBER];

//当前正在分配资源的进程
int pindex=0;

//显示每一个进程对资源拥有的现状
void showdate();

//接受进程分配的请求
void accepetRequest();

//模拟分配
void SimMllocation(int pindex);

//回滚
void rollback(int pindex);

//安全性检查
int checkIsSafe();

int main()
{
    //主逻辑

    int exit=0;

    //显示每一个进程现状
    showdate();

    do
    {
        //接受进程分配的请求
        accepetRequest();

        //模拟分配资源
        SimMllocation(pindex);

        //显示现在资源现状
        showdate();

        //检查是否存在安全序列，数据要保证至少一个进程能完成分配
        if(checkIsSafe()==0)
        {
            //当前进程不存在安全序列，当前进程数据回滚
            rollback(pindex);
        }
        printf("是否继续0/1\n");
        scanf("%d",&exit);
    }while(exit==1);
    return 0;
}

//显示每一个进程对资源拥有的现状
void showdate()
{
    int index=0;
    int index_=0;
    printf("当前资源情况.....\n");
    printf("资源类类型\t资源数量\n");
    for(index=0;index<SNUMBER;index++)
    {
        printf("%c\t\t%d\n",stype[index],avalable[index]);
    }

    printf("\n\n每一个进程所需要资源的最大值.........\n\n");
    printf("进程编号\t资源类型A\t资源类型B\t资源类型C\n");
    for(index=0;index<PNUMBER;index++)
    {
        printf("%d\t\t",index);
        for(index_=0;index_<SNUMBER;index_++)
        {
            printf("%d\t\t",pmax[index][index_]);
        }
        printf("\n");
    }

    printf("\n\n每一个进程所分配的情况......\n\n");
    printf("进程编号\t资源类型A\t资源类型B\t资源类型C\n");
    for(index=0;index<PNUMBER;index++)
    {
        printf("%d\t\t",index);
        for(index_=0;index_<SNUMBER;index_++)
        {
            printf("%d\t\t",allocation[index][index_]);
        }
        printf("\n");
    }

    printf("\n\n每一个进程还需要的资源的情况......\n\n");
    printf("进程编号\t资源类型A\t资源类型\t资源类型C\n");
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
    printf("请输入你要分配资源的进程编号(0~%d)\n",PNUMBER-1);
    //需要分配资源的进程
    scanf("%d",&pindex);
    //输入需要各种资源的具体数量
    for(index=0;index<SNUMBER;)
    {
        printf("请输入%c类资源的数量\n",stype[index]);
        scanf("%d",&request[index]);
        //小于进程对资源的最大要求
        if(request[index]<=pmax[pindex][index]&&request[index]<=avalable[index])
        {
            index++;
        }
    }
}

//模拟分配
void SimMllocation(int pindex)
{
     int index=0;
     for(index=0;index<SNUMBER;index++)
     {
         //总资源减少
         avalable[index]-=request[index];
         //当前进程已经分配的资源
         allocation[pindex][index]+=request[index];
         //还需要的资源
         pneed[pindex][index]-=request[index];
     }
}

//回滚
void rollback(int pindex)
{
    int index=0;
    for(index=0;index<SNUMBER;index++)
    {
        avalable[index]+=request[index];
        allocation[pindex][index]-=request[index];
        pneed[pindex][index]+=request[index];
    }//回滚与模拟分配刚好相反
}

int checkIsSafe()
{
    int index=0;
    int index_=0;
    int count=0;
    int k=0;
    int temp[PNUMBER];
    //余下的资源要保证每一个进程都能得到资源
    int finish[PNUMBER]={0,0,0,0,0};
    //资源
    int work[SNUMBER];
    for(index=0;index<SNUMBER;index++)
    {
        work[index]=avalable[index];
    }
    //所有进程找到
    for(index=0;index<PNUMBER;index++)
    {
        count=0;
        if(finish[index]==1)
            continue;
        //余下的资源是否能满足某一进程的需要
        for(index_=0;index_<SNUMBER;index_++)
        {
            if(pneed[index][index_]<=work[index_])
            {
                count++;
            }
            if(count==SNUMBER)
            {
                //余下的资源如果满足一个进程的需要，也就能回收
                finish[index]=1;
                for(index_=0;index_<SNUMBER;index_++)
                {
                    work[index_]+=allocation[index][index_];
                }
                //记下此进程的编号
                temp[k]=index;
                k++;
                //因为有资源回收,所以让所有进程试试看能不能重新分配
                index=-1;
            }
        }
    }
        //判断所有进程理论上是否能分配到资源
        for(index=0;index<PNUMBER;index++)
        {
            //只要有一个进程分配不到资源，则不存在安全序列
            if(finish[index]==0)
            {
                printf("***不存在安全序列***");
                return 0;
            }
        }
        printf("安全序列............\n");
        for(index=0;index<PNUMBER;index++)
        {
            printf("%d--->",temp[index]);
        }
        printf("\n");
        return 1;
}
