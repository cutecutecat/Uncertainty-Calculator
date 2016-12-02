#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const double percentage[4][9] = {
    1.32, 1.20, 1.14, 1.11, 1.09, 1.08, 1.07, 1.06, 1.00,
    2.92, 2.35, 2.13, 2.02, 1.94, 1.86, 1.83, 1.76, 1.65,
    4.30, 3.18, 2.78, 2.57, 2.46, 2.37, 2.31, 2.26, 1.96,
    9.93, 5.84, 4.60, 4.03, 3.71, 3.50, 3.36, 3.25, 2.58};

double input(double * item,int num){
    double aver;
    int i;
    printf("输入实验数据:\n");
    for(i=0;i<num;i++){
        scanf("%lf", item+i);
        aver += *(item+i);
    }
    aver /= num;
    return aver;
}

int findallMax(double * item,int num){
    int i, n = 0, max = 0;
    double m;
    for(i=0;i<num;i++){
        m =* (item+i);
        n = findMax(m);
        if(n > max)
            max = n;
    }
    return max;
}

int findMax(double m){
    int n = 0, tail, head;
    char *s = malloc(50);
    sprintf(s,"%lf",m);
    for(n=7;n>0;n--){
        if(s[n] != '0'){
            tail = n;
            break;
        }
    }
     head = strchr(s,'.')-s+1;
return tail-head+1;
}

double calA(double * item, int num, double aver){
    double St, add = 0;
    int i;
    for(i=0;i<num;i++){
        add += pow((*(item+i)- aver),2);
    }
    St = sqrt(add/(num-1));
    return St;
}

double calB(void){
    double p1, p2, c;
    printf("计算B类不确定度，键入仪器误差，无需计算键入0(简单处理，键入-1):\n");
    scanf("%lf", &c);
    if(c == 0)
        return 0;
    else if(c == -1)
        c=0;
    p1 = c;
    printf("仪器为模拟式请键入最小分度，数字式键入0：\n");
    scanf("%lf", &p2);
    if(p1 > 0)
        p2 *=0.5;
    printf("选择置信系数：\n1=>3\n2=>√3\n3=>√6\n");
    scanf("%lf", &c);
    switch((int)c){
    case 1:
        c = 3;
        break;
    case 2:
        c = sqrt(3);
        break;
    case 3:
        c = sqrt(6);
        break;
    }
    return sqrt(pow(p1,2)+pow(p2,2))/c;
}

double ensure(double uA,int num){
    int t;
    double uT;
    printf("计算A类不确定度，键入所需概率:\n1=>0.68\n2=>0.90\n3=>0.95\n4=>0.99\n");
    scanf("%d",&t);
    if(num <= 10){
        uT = uA*percentage[t-1][num-3];
    }else{
        uT = uA*percentage[t-1][8];
    }
    return uT;
}

int main(void){
    double item[20] = {0},A[2] = {0};
    int num, max;
    double aver, uA, uB = 0, St, uT,u;
    printf("输入实验数据个数:\n");
    scanf("%d",&num);
    while(num < 3){
        printf("实验数据必须不少于3，重新输入:\n");
        scanf("%d",&num);
    }
    aver = input(item,num);
    max = findallMax(item,num);
    St = calA(item,num,aver);
    uA = St/sqrt(num);
    uT = ensure(uA,num);

    uB = calB();
    printf("平均值:\n1/Xa=n*(ΣXn)=%.*lf        <= %.*lf\n标准差:\nδ=√[Σ(Xn-Xa)^2/(n-1)]=%.*lf        <= %.*lf\nA类不确定度:\nuA=δ/√(n)=%.*lf        <= %.*lf\n",max, aver, max+4, aver, max, uA, max+4, uA, max, uT, max+4, uT);
    if(uB != 0){
        u = sqrt(uT*uT+uB*uB);
        printf("B类不确定度:\nuB=%.*lf        <= %.*lf\n合成不确定度:\nn=√(uA^2+uB^2)=%.*lf        <= %.*lf\n",max, uB, max+4, uB, max, u, max+4, u);
    }
    system("pause");
    return 0;
}

