#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
int main()
{  int r(0);

int i,j,k,n(0);
double h,cha(0),e;
h=0;
double **a,*b,*x,*c;
cout<<"please input fault e"<<endl;
cin>>e;
while(cha<e)    //输入最大误差，作为循环停止条件
  {n++;
  a=new double*[n];  //用指针的形式定义动态数组
    for(i=0;i<n;i++)  
    {  
        a[i]=new double[n];  
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
b[i]=h;
h=0;
}
for(k=0;k<n-1;k++)
{for(i=k+1;i<n;i++)
 c[i]=a[i][k]/a[k][k];
 for(i=k+1;i<n;i++)
 {for(j=0;j<n;j++)
{a[i][j]=a[i][j]-c[i]*a[k][j];
}
b[i]=b[i]-c[i]*b[k];
}}
x[n-1]=b[n-1]/a[n-1][n-1];
 for(i=n-2;i>=0;i--)
{double sum=0;
for(j=i+1;j<n;j++)
{sum+=a[i][j]*x[j];
 }
x[i]=(b[i]-sum)/a[i][i];
}
cout <<"the result is following:"<<endl;
for(i=0;i<n;i++)     
{cout<<"x"<<i+1<<"="<<x[i]<<endl;
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
cin>>r;
return(0);
}
