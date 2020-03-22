#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
int main()
{   int r(0);
int i,j,k,n;
double h;
double **a,*b,*x,*c,*y;
cout<<"please input n"<<endl;
cin>>n;

    a=new double*[n];  
    for(i=0;i<n;i++)  
    {  
        a[i]=new double[n];  //用指针的形式定义动态数组
    }; 
  b=new double[n];
  x=new double[n];
  c=new double[n];
  y=new double[n];
for(i=0;i<n;i++)
{x[i]=0.0;
y[i]=0.0;
c[i]=0.0;
}
for(i=0;i<n;i++)
{for(j=0;j<n;j++)
{if(i>j)
 h=i+1;
else 
 h=j+1;
a[i][j]=h;
}}
h=0;
for(i=0;i<n;i++)
{for(j=0;j<n;j++)
{h=h+a[i][j];
}
b[i]=h;
h=0;
}
double **l,**u;
    l=new double*[n];  
    for(i=0;i<n;i++)  
    {  
        l[i]=new double[n];  
    }; 
    u=new double*[n];  
    for(i=0;i<n;i++)  
    {  
        u[i]=new double[n];  
    }; 
for(i=0;i<n;i++)
{for(j=0;j<n;j++)
{l[i][j]=0.0;
u[i][j]=0.0;
}}
for(i=0;i<n;i++)
{u[0][i] = a[0][i];
}
for (i = 1; i<n; i++)
{l[i][0] = a[i][0] / u[0][0];
}
for(r=1;r<n;r++)
{for(i=r;i<n;i++)
{double sum1 = 0;
 for(k=0;k<r;k++)
{sum1+=l[r][k]*u[k][i];
}
u[r][i]=a[r][i]-sum1;
}
if(r!=n)
for(i=r+1;i<n;i++)
{double sum2=0;
for(k=0;k<r;k++)
{sum2+=l[i][k]*u[k][r];
}
l[i][r]=(a[i][r]-sum2)/u[r][r];
}
}
y[0]=b[0];
for(i=1;i<n;i++)
{double sum3=0;
  for(k=0;k<i;k++)
 sum3+=l[i][k]*y[k];
 y[i]=b[i]-sum3;
}   
x[n-1]=y[n-1]/u[n-1][n-1];
for(i=n-2;i>=0;i--)
{double sum4=0;
 for(k=i+1;k<n;k++)
 sum4+=u[i][k]*x[k];
x[i]=(y[i]-sum4)/u[i][i];
}
for(i=0;i<n;i++)
cout<<"x["<<i+1<<"]="<<x[i]<<endl;
    for(int i=0;i<n;i++)  
        delete []a[i];//先单独释放第一维中每个数组的内存  
    delete []a;
  delete []b;
  delete []x;
  delete []c;
  delete []y;
    for(int i=0;i<n;i++)  
        delete []l[i]; 
    delete []l;
    for(int i=0;i<n;i++)  
        delete []u[i];
    delete []u;
cin>>r;

return(0);
}
