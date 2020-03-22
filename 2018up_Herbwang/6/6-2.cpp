#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
double f(double x)
{double r;
r=pow(x,3)-x-1;
return r;}
double df(double x)
{double dr;
dr=3*pow(x,2)-1;
return dr;}
int main()
{   int i,j;
double a,b,e,x,x1,f0,df0,m,k(0);
e=0.00001;k=0;
a=-3;b=3;
cout<<"input the x1"<<endl;
cin>>x1;
cout<<"input the max times of calculation:"<<endl;
cin>>m;

for(i=0;i<m;i++)
{k++;
x=x1;
f0=f(x);
df0=df(x);
x1=x-f0/df0;
if(abs(x-x1)<=e)
break;
}
if(i>=m)
cout<<"over range"<<endl;
else
{
cout<<"the result is:"<<x<<endl;
cout<<"the times of calculation is:"<<k<<endl;}
cin>>k;
return(0);
}
