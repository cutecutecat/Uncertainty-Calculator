function Up=cal_Up(data,tool_d,cal_d,B_type)
%data ���ݣ�1*n����
%tool_d ������1*n����
%cal_d ��С�ֶȻ�0������������
%B_type ��̬�ֲ�1 ���ȷֲ�Ϊ2
%���ص�UpΪ4*1�����Ӧ�ĸ����Ÿ���
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
tool_d=input('������������0\n');
cal_d=input('��е�Ǳ�������С�ֶȣ������Ǳ�����0\n');
Ub=(tool_d^2+(cal_d/2)^2)^0.5;
B_type=input('��̬�ֲ�����1�����ȷֲ�����2\n');
Db=Ub*percentage_B(:,B_type);
Up=power((power(Da,2)+power(Db,2)),0.5);
Up(:,4)=Up;
Up(:,1)=[0.68;0.90;0.95;0.99];Up(:,2)=Da;Up(:,3)=Db;
clc;
fprintf('����');
disp(A);
fprintf('ƽ��ֵ  %f\n',A_mean);
fprintf('ƽ��ֵ�ı�׼��UA  %f\n',Ua);
fprintf('B�಻ȷ�������ֵUB  %f\n',Ub);
fprintf('   ���Ÿ���     A��       B��    �ϳɲ�ȷ����\n');
disp(Up)
Up=Up(:,4);