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
    c = a;
    a = b;
    b = c;
return(0);
}


int main()
{double **a,*b,*x,*c;
    int i,j,k,n;
    int maxi;
double max,h,s,t;
cout<<"please input n"<<endl;
cin>>n;
    a=new double*[n];  //用指针的形式定义动态数组
    for(i=0;i<n;i++)  
    {  
        a[i]=new double[n+1];  
    }; 
  b=new double[n];
  x=new double[n];
  c=new double[n];
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
a[i][n]=h;
h=0;
}
    
for(k=0;k<n-1;k++)
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
    for (i = 0; i < n ; i++)
       { cout << " x" << "[" << i << "]=" << x[i] << endl;
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



