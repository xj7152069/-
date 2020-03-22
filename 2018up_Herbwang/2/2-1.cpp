#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
template<class T>
int SWAP(T& a, T& b)
{
    T c;
    c=a;
    a=b;
    b=c;
return(0);
}


int main()
{cout<<"曲线拟合"<<endl;
double wz[9]={-100,-75,-50,-25,0,25,50,75,100},sj[9]={4.06,6.78,9.49,16.27,40.67,97.62,146.43,151.85,162.7}; //输入数据和位置
double **a,*b,*x,*c;
    int i,j,k,n(5);
    int maxi,h;
double max,s,t;
    a=new double*[n]; 
    for(i=0;i<n;i++)  
    {  
        a[i]=new double[n+1];  
    }; 
  b=new double[n];
  x=new double[n];
  c=new double[n];
for(i=0;i<n;i++)
{for(j=0;j<n;j++)
{for(h=0;h<9;h++)
a[i][j]=a[i][j]+pow(wz[h],i+j);
}}

for(i=0;i<n;i++)
{for(h=0;h<9;h++)
a[i][n]=a[i][n]+pow(wz[h],i)*sj[h];
}
    
for(k=0;k<n-1;k++)    //线性方程组求解
{
max=a[k][k];maxi=k;
for(i=k+1;i<=n-1;i++)
{
if(abs(a[i][k])>abs(max))
{max=a[i][k];maxi=i;}
}
if(max==0)
break;
if(maxi!=k)
{
for(j=k;j<=n;j++)
{SWAP(a[k][j],a[maxi][j]);}
}
for(i=k+1;i<n;i++)
{
a[i][k]=a[i][k]/(-a[k][k]);
for(j=k+1;j<=n;j++)
a[i][j]=a[i][j]+a[i][k]*a[k][j];
}
}
if(max==0)
cout<<"error!"<<endl;
else
{
for(k=n-1;k>=0;k--)
{
s=0;
for(j=k+1;j<n;j++)
s=s+a[k][j]*x[j];
x[k]=(a[k][n]-s)/a[k][k];
}
}

    //打印输出
for(i=0;i<n;i++)
{cout<<"x"<<"["<<i<<"]="<<x[i]<<endl;
}
    for(int i=0;i<n;i++)  
        delete []a[i];//先单独释放第一维中每个数组的内存  
    delete []a;
  delete []b;
  delete []x;
  delete []c;
cin>>n;
return(0);
}



