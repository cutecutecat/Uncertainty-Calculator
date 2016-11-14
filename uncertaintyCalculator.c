#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const double percentage[4][9]={
    1.32, 1.20, 1.14, 1.11, 1.09, 1.08, 1.07, 1.06, 1.00,
    2.92, 2.35, 2.13, 2.02, 1.94, 1.86, 1.83, 1.76, 1.65,
    4.30, 3.18, 2.78, 2.57, 2.46, 2.37, 2.31, 2.26, 1.96,
    9.93, 5.84, 4.60, 4.03, 3.71, 3.50, 3.36, 3.25, 2.58};

double input(double * item,int num){
    double aver;
    int i;
    printf("����ʵ������:\n");
    for(i=0;i<num;i++){
        scanf("%lf", item+i);
        aver += *(item+i);
    }
    aver /= num;
    return aver;
}

int findallMax(double * item,int num){
    int i, n=0, max=0;
    double m;
    for(i=0;i<num;i++){
        m=*(item+i);
        n = findMax(m);
        if(n>max)
            max=n;
    }
    return max;
}

int findMax(double m){
    int n=0, tail, head;
    char *s=malloc(50);
    sprintf(s,"%lf",m);
    for(n=7;n>0;n--){
        if(s[n]!='0'){
            tail=n;
            break;
        }
    }
     head=strchr(s,'.')-s+1;
return tail-head+1;
}

double calA(double * item, int num, double aver){
    double St, add=0;
    int i;
    for(i=0;i<num;i++){
        add += pow((*(item+i)- aver),2);
    }
    St = sqrt(add/(num-1));
    return St;
}

double calB(void){
    double p1, p2, c;
    printf("����B�಻ȷ���ȣ���������������������0:\n");
    scanf("%lf", &p1);
    if(p1==0)
        return 0;
    printf("����Ϊģ��ʽ�������С�ֶȣ�����ʽ����0��\n");
    scanf("%lf", &p2);
    printf("ѡ������ϵ����\n1=>3\n2=>��3\n3=>��6\n");
    scanf("%lf", &c);
    switch((int)c){
    case 1:
        c=3;
        break;
    case 2:
        c=sqrt(3);
        break;
    case 3:
        c=sqrt(6);
        break;
    }
    return sqrt(pow(p1,2)+pow(p2,2))/c;
}

double ensure(double uA,int num){
    int t;
    double uT;
    printf("����A�಻ȷ���ȣ������������:\n1=>0.68\n2=>0.90\n3=>0.95\n4=>0.99\n");
    scanf("%d",&t);
    if(num<=10){
        uT = uA*percentage[t-1][num-3];
    }else{
        uT *= uA*percentage[t-1][8];
    }
    return uT;
}

int main(void){
    double item[20]={0},A[2]={0};
    int num, max;
    double aver, uA, uB=0, St, uT,u;
    printf("����ʵ�����ݸ���:\n");
    scanf("%d",&num);
    while(num<3){
        printf("ʵ�����ݱ��벻����3����������:\n");
        scanf("%d",&num);
    }
    aver = input(item,num);
    max = findallMax(item,num);
    St = calA(item,num,aver);
    uA=St/sqrt(num);
    uT=ensure(uA,num);

    uB = calB();
    printf("ƽ��ֵ:%.*lf\n��׼��:%.*lf\nA�಻ȷ����:%.*lf\n",max, aver, max,  uA, max, uT);
    if(uB != 0){
        u=sqrt(uT*uT+uB*uB);
        printf("B�಻ȷ����:%.*lf\n�ϳɲ�ȷ����:%.*lf\n",max, uB, max, u);
    }
    system("pause");
    return 0;
}

