#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
template<class T>
int SWAP(T& a, T& b)  //交换两个变量
{
T c;
c = a;
a = b;
b = c;
return(0);
}


int main()
{
    int i,j,k,n(0);
    int maxi;
double max,h,s,t,e,cha(0);
h=0;
double **a,*b,*x,*c;
cout<<"please input the fault e"<<endl;
cin>>e;
while(cha<e)
{n++;
a=new double*[n];  
for(i=0;i<n;i++)  
{  
a[i]=new double[n+1];  //用指针的形式定义动态数组
}; 
b=new double[n];
x=new double[n];
c=new double[n];
for(i=0;i<n;i++)
{for(j=0;j<n;j++)
{
a[i][j]=1.0/(i+j+1);
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
cout<<"the result is the following"<<endl;   //打印输出
for (i=0;i<n;i++)
{cout<<"x"<<"["<<i<<"]="<<x[i]<<endl;
if(cha<abs(x[i]-1))
cha=abs(x[i]-1);
}
for(int i=0;i<n;i++)  
delete []a[i];//先单独释放第一维中每个数组的内存  
delete []a;
delete []b;
delete []x;
delete []c;}
cout<<endl<<"while the fault is "<<e<<", the n is "<<n<<endl;
cin>>n;
return(0);
}



