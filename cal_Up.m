function Up=cal_Up(data,tool_d,cal_d,B_type)
%data 数据，1*n矩阵
%tool_d 仪器误差，1*n矩阵
%cal_d 最小分度或0（数字仪器）
%B_type 正态分布1 均匀分布为2
%返回的Up为4*1矩阵对应四个置信概率
clear;
A=data;
percentage_A=[...
    1.32, 1.20, 1.14, 1.11, 1.09, 1.08, 1.07, 1.06, 1.00;...
    2.92, 2.35, 2.13, 2.02, 1.94, 1.86, 1.83, 1.76, 1.65;...
    4.30, 3.18, 2.78, 2.57, 2.46, 2.37, 2.31, 2.26, 1.96;...
    9.93, 5.84, 4.60, 4.03, 3.71, 3.50, 3.36, 3.25, 2.58];
percentage_B=[...
    1.000,1.183;...
    1.650,1.559;...
    1.960,1.645;...
    2.580,1.715;];
percentage_B(:,1)=percentage_B(:,1)/3;
percentage_B(:,2)=percentage_B(:,2)/(3^0.5);
A_mean=mean(A,2);
Ua=std(A,0,2)/sqrt(length(A));
Da=Ua*percentage_A(:,min(length(A)-2,9));
tool_d=input('输入仪器误差或0\n');
cal_d=input('机械仪表输入最小分度，数字仪表输入0\n');
Ub=(tool_d^2+(cal_d/2)^2)^0.5;
B_type=input('正态分布输入1，均匀分布输入2\n');
Db=Ub*percentage_B(:,B_type);
Up=power((power(Da,2)+power(Db,2)),0.5);
Up(:,4)=Up;
Up(:,1)=[0.68;0.90;0.95;0.99];Up(:,2)=Da;Up(:,3)=Db;
clc;
fprintf('数据');
disp(A);
fprintf('平均值  %f\n',A_mean);
fprintf('平均值的标准差UA  %f\n',Ua);
fprintf('B类不确定度最大值UB  %f\n',Ub);
fprintf('   可信概率     A类       B类    合成不确定度\n');
disp(Up)
Up=Up(:,4);