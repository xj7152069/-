#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
int main()
{
int n,i,j,k(10),t(0);
double h,e;
h=0;e=0.00001;
cout<<"please input the size (n)"<<endl;
cin>>n;
cout<<"input the most times of calculation"<<endl;
cin>>k;
cout<<"input the fault"<<endl;
cin>>e;
   double** a;  
    a=new double*[n];  
    for(i=0;i<n;i++)  
    {  
        a[i]=new double[n];  
    }; 
  double* b;
  b=new double[n];

for(i=0;i<n;i++)
{for(j=0;j<n;j++)
{if(i>j)
 h=i+1;
else if(i<j) 
 h=j+1;
else if(i==j)
h=(n+2)*10;    //由于作业中所给的矩阵迭代不收敛，所以修改了矩阵
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
for(i=0;i<n;i++)
{for(j=0;j<n;j++)
{cout<<a[i][j]<<" ";
}cout<<endl;}
for(i=0;i<n;i++)
{cout<<b[i]<<" ";}
cout<<endl;
 double *x1,*x2,sum,max,cha;
 x1=new double[n];
 x2=new double[n];
 for(i=0;i<n;i++)
  x1[i]=0;
 do
 {   for(i=0;i<n;i++)
    x2[i]=x1[i];
  t++;
     for(i=0;i<n;i++)    
{    
 sum=0;    
for(j=0;j<n;j++)    
{    
    if(j==i) continue;   
    sum+=a[i][j]*x1[j];    
}    
x1[i]=(b[i]-sum)/a[i][i];    
}    
cout<<"the result is the following"<<endl;    
for (i=0;i<n;i++)    
    cout<<x1[i]<<' ';    
    cout<<endl;  

 max=abs(x1[0]-x2[0]);
   for(i=1;i<n;i++)
    {if(max<(cha=abs(x1[i]-x2[i]))) 
       max=cha;}
 
 }while(max>e && t<=k);
cout<<"the times is:"<<t<<endl;

    for(int i=0;i<n;i++)  
        delete []a[i];//先单独释放第一维中每个数组的内存  
    delete []a;
  delete []b;
 delete []x1;
 delete []x2;
 return 0;
}

