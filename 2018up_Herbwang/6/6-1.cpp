#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
double f(double x)
{double r;
r=pow(x,4)-3*x-1;
return r;}
int main()
{   
double a,b,e,x,m,k(0);
e=0.0000005;k=0;
a=0.3;b=0.4;
if(f(a)==0)
x=a;
else if(f(b)==0)
x=b;
else
{
while((b-a)/2.0>e)
{k++;
m=(b+a)/2.0;
if(f(m)==0)
break;
else if(f(a)*f(m)>0)
a=m;
else
b=m;
}
x=(a+b)/2;
}
cout<<"the result is:"<<x<<endl;
cout<<"the times of calculation is:"<<k<<endl;
cin>>k;
return(0);
}
