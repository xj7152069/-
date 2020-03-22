#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
int main()
{cout<<"计算特征值（2）"<<endl;
int s(0);
double PI=3.1415926;
double a[5][5] = {5,-1,0,0,0,-1,4.5,0.2,0,0,0,0.2,1,-0.4,0,0,0,-0.4,3,1,0,0,0,1,3}; //题目所给的矩阵不是对称矩阵，对第二行第一列元素作了修改
int n = 5;
double eps = 1e-10;
int T = 10000;
double p[5][5] = { 0 };
cout<<"input the fault: ";cin>>eps;
cout<<"input the times of calculation: ";cin>>T;
{
int i,j,k;
double max=a[0][1];
int row=0;
int col=0;
double Ptemp[3][3];
int ite_num=0;
for (i=0;i<n;i++)
p[i][i]=1;
while (1)
{
max=fabs(a[0][1]);
row=0;
col=1;
for(i=0;i<n;i++)
for(j=0;j<n;j++)
if (i!=j&&fabs(a[i][j])>max)
{
max=fabs(a[i][j]);
row=i;
col=j;
}
if(max<eps)
{
cout<<"max:"<<max<<endl;
cout<<"t:"<<ite_num<<endl;
s=7;
break;
}
if (ite_num>T)
{
cout<<"max:"<<max<<endl;
cout<<"t:"<<ite_num<<endl;
break;
}
double theta;
if(a[row][row]==a[col][col])
theta=PI/4;
else
theta=0.5*atan(2*a[row][col]/(a[row][row]-a[col][col]));
double aii=a[row][row];
double ajj=a[col][col];
double aij=a[row][col];
double sin_theta=sin(theta);
double cos_theta=cos(theta);
double sin_2theta=sin(2*theta);
double cos_2theta=cos(2*theta);
a[row][row]=aii*cos_theta*cos_theta+ajj*sin_theta*sin_theta+aij*sin_2theta;
a[col][col]=aii*sin_theta*sin_theta+ajj*cos_theta*cos_theta-aij*sin_2theta;
a[row][col]=0.5*(ajj-aii)*sin_2theta+aij*cos_2theta;
a[col][row]=a[row][col];
for(k=0;k<n;k++)
{
if(k!=row && k!=col)
{
double arowk=a[row][k];
double acolk=a[col][k];
a[row][k]=arowk*cos_theta+acolk*sin_theta;
a[k][row]=a[row][k];
a[col][k]=acolk*cos_theta-arowk*sin_theta;
a[k][col]=a[col][k];
}
}
if(ite_num==0)
{
p[row][row]=cos_theta;
p[row][col]=-sin_theta;
p[col][row]=sin_theta;
p[col][col]=cos_theta;
}
else
{
for(k=0;k<n;k++)
{
double pki=p[k][row];
double pkj=p[k][col];
p[k][row]=pki*cos_theta+pkj*sin_theta;
p[k][col]=pkj*cos_theta-pki*sin_theta;
}
}
ite_num++;
}    
}
if(s==7)
{
cout<< "特征值是 a:"<<endl;
for(int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
if (i==j)   
cout<<setw(15)<<a[i][j];        
}
cout<<endl;
cout<<"对应的特征向量（列向量）p:"<<endl;
for (int i = 0; i < n; i++)
{
for (int j=0;j<n;j++)
cout<<setw(15)<<p[i][j];
cout<<endl;
}
}
else
cout<<"false"<<endl;
cin>>T;
return(0);
}

