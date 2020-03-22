#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
int main()
{  int i,j,k,n;
double h,l;
double a1[4]={-1,-2,-3,0},a2[4]={2,3,4,5},a3[4]={0,-1,-2,-3},s1[4],y[4],s3[4],f[4]={6,1,-2,1},x[4];
n=4;
s1[0]=a1[0]/a2[0];
for(i=1;i<n-1;i++)
{s1[i]=a1[i]/(a2[i]-a3[i]*s1[i-1]);
}
y[0]=f[0]/a2[0];
for(i=1;i<n;i++)
{y[i]=(f[i]-a2[i]*y[i-1])/(a2[i]-a3[i]*s1[i-1]);
}
x[n-1]=y[n-1];
for(i=n-2;i>=0;i--)
{x[i]=y[i]-s1[i]*x[i+1];}
cout<<"the result is the following:"<<endl;
for(i=0;i<n;i++)
{cout<<"x["<<i+1<<"]"<<x[i]<<endl;}
cin>>h;
return(0);
}
