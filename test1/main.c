#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define N1 30
#define N2 6
void input1(char name1[N1][10],char name2[N1][10],char subject[][10],long int ID1[],long int ID2[],float score1[][N2],float score2[][N2],int *n1,int *n2)//输入ID、分数的数组及其复制数组、输入人数n
{
    int ret;
    printf("Please input the students' number and the subjects's number:\n");
    ret=scanf("%d %d",n1,n2);
    while(ret!=2||*n1>N1||*n1<1)                           //对输入数据类型及范围进行检验
    {
        while(getchar()!='\n');
        printf("Please input a right students' number and right subject's number!\n");
        ret=scanf("%d %d",n1,n2);
    }
    printf("Input the subject's name:");
    for(int i=0;i<*n2;i++){
        while(getchar()!='\n');
        scanf("%s",subject[i]);
    }
    for(int i=0; i<*n1; i++)
    {
        while(getchar()!='\n');
        printf("Please input the students' name and ID \n");
        gets(name1[i]);
        strcpy(name2[i],name1[i]);
        scanf("%ld",&ID1[i]);
        for(int j=0; j<i; j++){
            while(ID1[i]==ID1[j]){
                printf("Please input a right ID:");     //对输入ID不重复进行检验
                scanf("%ld",&ID1[i]);
            }
        }
        ID2[i]=ID1[i];
        printf("Please input the students' scores:");
        for(int j=0;j<*n2;j++){
            scanf("%f",&score1[i][j]);
            score2[i][j]=score1[i][j];
        }
    }
}
void print2(char subject[][10],char name1[N1][10],long int ID[],float score[][N2],float total[],int n1,int n2)      //打印科目名字分数与ID的函数
{
    printf("name\tID\t");
    for(int i=0;i<n2;i++)
        printf("%s\t",subject[i]);
    printf("\n");
    for(int i=0; i<=n1-1; i++)
    {
        printf("%s\t%ld\t",name1[i],ID[i]);
        for(int j=0;j<n2;j++)
            printf("%.2f\t",score[i][j]);
        printf("sum:%.2f\taver:%.2f\t\n",total[i],total[i]/n2);
    }
}
void calculate3(char subject[][10],float score1[][N2],int n1,int n2)     //计算科目均值、总分
{
    int j;
    float sum=0;
    for(j=0; j<n2;j++){
        sum=0;
        for(int i=0;i<n1;i++)
            sum=sum+score1[i][j];
        printf("The subject \t%s\tsum:%.1f\t\taverage score:%.2f\n",subject[j],sum,sum/(float)n1);
    }
}
void calculate4a(float score1[][N2],float total1[N1],float total2[N1],int n1,int n2)//计算每个学生总分并储存在total数组中
{
    for(int i=0;i<n1;i++)
        for(int j=0;j<n2;j++){
            total1[i]=total1[i]+score1[i][j];
            total2[i]=total1[i];
        }
}
void calculate4b(long int ID1[],char name1[][10],float total[],int n1)//打印每个学生的总分和平均分
{
    for(int i=0;i<n1;i++)
        printf("%ld\t%s:\tsum:%.lf\taverage score:%.2f\n",ID1[i],name1[i],total[i],total[i]/n1);
}
int scoresJX5(long int ID1,long int ID2,float total1,float total2,char name1[10],char name2[10])//总分降序判断条件
{
    if(total1<=total2)
        return 1;
    else
        return 0;
}
int scoresSX6(long int ID1,long int ID2,float total1,float total2,char name1[10],char name2[10])//总分升序判断条件
{
    if(total1>total2)
        return 1;
    else
        return 0;
}
int IDSX7(long int ID1,long int ID2,float total1,float total2,char name1[10],char name2[10])//ID升序判断条件
{
    if(ID1>ID2)
        return 1;
    else
        return 0;
}
int nameSX8(long int ID1,long int ID2,float total1,float total2,char name1[10],char name2[10])//名字按字母表升序判断条件
{
    if(strcmp(name1,name2)>=0)
        return 1;
    else
        return 0;
}
void RANK(char name1[30][10],long int ID1[],float score1[][N2],float total[],int n1,int n2,int (*compare)(long int ID1,long int ID2,float total1,float total2,char name1[10],char name2[10]))//冒泡排序的函数
{
    long int term1;
    float term2;
    char term3[10];
    for(int j=n1-1;j>0;j--)
        for(int i=0;i<j;i++){
            if((*compare)(ID1[i],ID1[i+1],total[i],total[i+1],name1[i],name1[i+1])){
                term1=ID1[i];
                ID1[i]=ID1[i+1];
                ID1[i+1]=term1;
                for(int k=0;k<n2;k++){
                    term2=score1[i][k];
                    score1[i][k]=score1[i+1][k];
                    score1[i+1][k]=term2;
                }
                term2=total[i];
                total[i]=total[i+1];
                total[i+1]=term2;
                strcpy(term3,name1[i]);
                strcpy(name1[i],name1[i+1]);
                strcpy(name1[i+1],term3);
            }
        }
}
void search9(char subject[][10],char name1[N1][10],long int ID1[],float score1[][N2],int n1,int n2)//搜索ID
{
    long int ID;
    printf("Please input the student's ID:");
    scanf("%ld",&ID);
    for(int j=0;j<n1;j++){
        if(ID==ID1[j]){
            printf("name\tID\t");
            for(int i=0;i<n2;i++)
                printf("%s\t",subject[i]);
            printf("rank\t");
            printf("\n");
            printf("%s\t%ld\t",name1[j],ID1[j]);
            for(int i=0;i<n2;i++)
                printf("%.2f\t",score1[j][i]);
            printf("%d\n",j+1);
            return;
        }
    }
    printf("Can't find the ID\n");
}
void search10(char subject[][10],char name1[N1][10],long int ID1[],float score1[][N2],int n1,int n2)//搜索姓名
{
    char search[10];
    while(getchar()!='\n');
    printf("Please input the search name:");
    gets(search);
    for(int j=0;j<n1;j++){
        if(strcmp(search,name1[j])==0){
            printf("name\tID\t");
            for(int i=0;i<n2;i++)
                printf("%s\t",subject[i]);
            printf("rank\t");
            printf("\n");
            printf("%s\t%ld\t",name1[j],ID1[j]);
            for(int i=0;i<n2;i++)
                printf("%.2f\t",score1[j][i]);
            printf("%d\n",j+1);
            return;
        }
    }
    printf("Can't find the name\n");
}
void analysis11(char subject[][10],float score1[][N2],int n1,int n2)//各科分数分析
{
    int i=0,counter=0;
    for(int k=0;k<n2;k++){
        printf("%s\n",subject[k]);
        for(i=0,counter=0;i<n1;i++){
            if(score1[i][k]>=90)
            counter++;
        }
        printf("A:%.2f%%, %d people\n",(float)100*counter/n1,counter);
        for(i=0,counter=0;i<n1;i++){
            if(score1[i][k]<90&&score1[i][k]>=80)
                counter++;
        }
        printf("B:%.2f%%, %d people\n",(float)100*counter/n1,counter);
        for(i=0,counter=0;i<n1;i++){
            if(score1[i][k]<80&&score1[i][k]>=70)
                counter++;
        }
        printf("C:%.2f%%, %d people\n",(float)100*counter/n1,counter);
        for(i=0,counter=0;i<n1;i++){
            if(score1[i][k]<70&&score1[i][k]>=60)
                counter++;
        }
        printf("D:%.2f%%, %d people\n",(float)100*counter/n1,counter);
        for(i=0,counter=0;i<n1;i++){
            if(score1[i][k]<60)
                counter++;
        }
        printf("D:%.2f%%, %d people\n",(float)100*counter/n1,counter);
    }

}
void print1()//打印目录
{
    printf("1.Input record\n");
    printf("2.List record\n");
    printf("3.Calculate total and average score of every course\n");
    printf("4.Calculate total and average score of every student\n");
    printf("5.Sort in descending order by total score of every student\n");
    printf("6.Sort in ascending order by total score of every student\n");
    printf("7.Sort in ascending order by StudentID\n");
    printf("8.Sort in ascending order by name\n");
    printf("9.Search by students ID\n");
    printf("10.Search by students name\n");
    printf("11.Statistic analysis for every course\n");
    printf("0.Exit\nPlease enter your choice:");
}
int main()
{
    int inumebr=0,ichoice=0,iret=0,isubject=0;//学生人数n、选择数choice、判断数ret
    long int lID1[N1]={0},lID2[N1]={0};//ID数组及复制数组
    float fscores1[N1][N2]={0},fscores2[N1][N2]={0},total[N1]={0},total1[N1]={0};//分数数组及其复制数组
    char name1[N1][10],name2[N1][10],subject[N2][10];
    input1(name1,name2,subject,lID1,lID2,fscores1,fscores2,&inumebr,&isubject);//强制先输入学生数据
    calculate4a(fscores1,total,total1,inumebr,isubject);//先计算总分并存入数组total
    print1();//打印目录
    iret=scanf("%d",&ichoice);
    for(int i=0;;i++)
    {
        while(iret!=1||ichoice>11||ichoice<0){
            while(getchar()!='\n');
            printf("Please input a right number!\n");
            iret=scanf("%d",&ichoice);
        }
        switch(ichoice)
        {
        case 1:
            input1(name1,name2,subject,lID1,lID2,fscores1,fscores2,&inumebr,&isubject);
            break;
        case 2:
            print2(subject,name2,lID2,fscores2,total1,inumebr,isubject);
            break;
        case 3:
            calculate3(subject,fscores2,inumebr,isubject);
            break;
        case 4:
            calculate4b(lID1,name1,total,inumebr);
            break;
        case 5:
            RANK(name1,lID1,fscores1,total,inumebr,isubject,scoresJX5);
            print2(subject,name1,lID1,fscores1,total,inumebr,isubject);
            break;
        case 6:
            RANK(name1,lID1,fscores1,total,inumebr,isubject,scoresSX6);
            print2(subject,name1,lID1,fscores1,total,inumebr,isubject);
            break;
        case 7:
            RANK(name1,lID1,fscores1,total,inumebr,isubject,IDSX7);
            print2(subject,name1,lID1,fscores1,total,inumebr,isubject);
            break;
        case 8:
            RANK(name1,lID1,fscores1,total,inumebr,isubject,nameSX8);
            print2(subject,name1,lID1,fscores1,total,inumebr,isubject);
            break;
        case 9:
            RANK(name1,lID1,fscores1,total,inumebr,isubject,scoresJX5);
            search9(subject,name1,lID1,fscores1,inumebr,isubject);
            break;
        case 10:
            RANK(name1,lID1,fscores1,total,inumebr,isubject,scoresJX5);
            search10(subject,name1,lID1,fscores1,inumebr,isubject);
            break;
        case 11:
            analysis11(subject,fscores1,inumebr,isubject);
            break;
        case 0:
            return 0;
        }
        printf("Next step:");
        iret=scanf("%d",&ichoice);
    }
}
