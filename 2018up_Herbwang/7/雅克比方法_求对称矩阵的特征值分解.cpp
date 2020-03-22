
//所需头文件
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;

float **a,**p,**a2;
float **Jacobi_tzz(float **G,int n,int T,float eps)
{

int i,j,k;
int s(0);  //SIZE为矩阵规模
float PI=3.1415926;

    a=new float*[n]; //动态数组
    p=new float*[n]; 
    for(j=0;j<n;j++)  
    {  
        a[j]=new float[n];
        p[j]=new float[n];  
    };
    
    a2=new float*[n+1]; //动态数组  
    for(j=0;j<n+1;j++)  
    {  
        a2[j]=new float[n]; 
    };
    
    for(i=0;i<n;i++)
    {for(j=0;j<n;j++)
     {a[i][j]=*((float *)G+n*i+j);}  //将指针空间G的值的值赋给a
    }

/********计算部分*********/
float max=a[0][1];
int row=0;
int col=0;
float Ptemp[3][3];
int ite_num=0;
for (i=0;i<n;i++)
p[i][i]=1;
while (1)
{
{printf("m.nd : %5.5d\n", ite_num);} 
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
if(max<eps || ite_num>T)
{
s=7;
break;
}

float theta;
if(a[row][row]==a[col][col])
theta=PI/4;
else
theta=0.5*atan(2*a[row][col]/(a[row][row]-a[col][col]));
float aii=a[row][row];
float ajj=a[col][col];
float aij=a[row][col];
float sin_theta=sin(theta);
float cos_theta=cos(theta);
float sin_2theta=sin(2*theta);
float cos_2theta=cos(2*theta);
a[row][row]=aii*cos_theta*cos_theta+ajj*sin_theta*sin_theta+aij*sin_2theta;
a[col][col]=aii*sin_theta*sin_theta+ajj*cos_theta*cos_theta-aij*sin_2theta;
a[row][col]=0.5*(ajj-aii)*sin_2theta+aij*cos_2theta;
a[col][row]=a[row][col];
for(k=0;k<n;k++)
{
if(k!=row && k!=col)
{
float arowk=a[row][k];
float acolk=a[col][k];
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
float pki=p[k][row];
float pkj=p[k][col];
p[k][row]=pki*cos_theta+pkj*sin_theta;
p[k][col]=pkj*cos_theta-pki*sin_theta;
}
}
ite_num++;
}    

/********输出部分*******/
if(s==7)
{
for(int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
if (i==j)  
{a2[n][j]=a[i][j];}      
}

for (int i = 0; i < n; i++)
{
for (int j=0;j<n;j++)
{a2[i][j]=p[i][j];}
}
}

    float **tzz =(float **)malloc((n+1)*sizeof(float *));//先申请n+1个指针型字节的空间
    for (i=0;i<n+1;i++)
        tzz[i]=(float *)malloc(n*sizeof(float)); //然后依次按一维申请

    for(i=0;i<n+1;i++)
      for(j=0;j<n;j++)
      {*((float *)tzz+n*i+j)=a2[i][j];} //

return tzz;
}

int main()
{cout<<"计算特征值（1）"<<endl;
int n(3),i,j;
float a[3][3] = {112,105,114,105,137,110,114,110,123};
float eps=1e-9;
int T=10000;
float **tzz;
    float **G =(float **)malloc((n+1)*sizeof(float *));//先申请n+1个指针型字节的空间
    for (i=0;i<n;i++)
        G[i]=(float *)malloc(n*sizeof(float)); //然后依次按一维申请

    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
      {*((float *)G+n*i+j)=a[i][j];} //
      
      tzz=Jacobi_tzz((float **)G,n,T,eps);
      
    for(i=0;i<n+1;i++)
      {for(j=0;j<n;j++)
      {cout<<*((float *)tzz+n*i+j)<<" ";} //
        cout<<endl;
        }

return 0;
}

