#include <iostream>
#include <stdio.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
int main()
{while(1)
{
 int N,i,j,m;
cout<<"input the size"<<endl;
cin>>N;
 double **a,**b,**c,t,*d,s,h(0);
    b=new double*[N];  
    for(i=0;i<N;i++)  
    {  
        b[i]=new double[2*N];  //用指针的形式定义动态数组
    }; 
    a=new double*[N];  
    for(i=0;i<N;i++)  
    {  
        a[i]=new double[N];  
    }; 
    c=new double*[N];  
    for(i=0;i<N;i++)  
    {  
        c[i]=new double[N];  
    }; 
  d=new double[N];

for(i=0;i<N;i++)
{for(j=0;j<N;j++)
{if(i>j)
 h=i+1;
else 
 h=j+1;
a[i][j]=h;
}}
h=0;
for(i=0;i<N;i++)
{for(j=0;j<N;j++)
{cout<<a[i][j]<<" ";
}cout<<endl;}
 for(i=0;i<N;i++)
  for(j=0;j<N;j++)
   b[i][j]=a[i][j];
 for(i=0;i<N;i++)
  for(j=N;j<2*N;j++)
   b[i][j]=0;
 for(i=0;i<N;i++)
  b[i][N+i]=1;
for(m=0;m<N;m++)        
 { 
 t=b[m][m];                  
 i=m;                        
 while(b[m][m]==0)
 {    
  b[m][m]=b[i+1][m];
  i++;
 }
 if(i>m)
 {
 b[i][m]=t;                  
 for(j=0;j<m;j++)                     
 {
  t=b[m][j];
  b[m][j]=b[i][j];
  b[i][j]=t;
 }
 for(j=m+1;j<2*N;j++)                     
 {
  t=b[m][j];
  b[m][j]=b[i][j];
  b[i][j]=t;
 }
 }
for(i=m+1;i<N;i++)
     for(j=2*N-1;j>=m;j--)
   b[i][j]-=b[i][m]*b[m][j]/b[m][m]; 
    for(j=2*N-1;j>=m;j--)
     b[m][j]/=b[m][m];   
 }
m=N-1;
 while(m>0)
 {
  for(i=0;i<m;i++)
   for(j=2*N-1;j>=m;j--)         
    b[i][j]-=b[i][m]*b[m][j];
   m--;
 } 
 for(i=0;i<N;i++)                        
  for(j=0;j<N;j++)
   c[i][j]=b[i][N+j];
cout<<"the result is the following:"<<endl;
 for(i=0;i<N;i++)
 {
  for(j=0;j<N;j++)
   {cout<<c[i][j]<<" ";}
 cout<<endl;;   
 }
cout<<"the result is the following:"<<endl;
 for(i=0;i<N;i++)
 {
  for(j=0;j<N;j++)
   {if(abs(c[i][j])<0.000000001)
     c[i][j]=0;
cout<<c[i][j]<<" ";}
 cout<<endl;;   
 }
cin>>N;
if(N!=11221323)
break;
}
 return(0);
} 
