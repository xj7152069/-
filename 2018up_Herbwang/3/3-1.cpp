#include <iostream>
#include<math.h>
using namespace std;
double f(double x)
{
  double y;
  y=1/(1+x);
  return(y);
}
int main()
{cout<<"Simpson积分方法"<<endl;
 while(1)
 {
  float pi(3.1415926);
  double i,n;
  n=1;
  double s=0,ss=0,s0=0,s1=0,h=1.0/n;
  for(i=1;i<n;i++)
   {
    s0=s0+f(i*h);
   }
  for(i=1;i<n+1;i++)
   {
    s1=s1+f((2*i-1)*h/2);
   }
    s1=s1*4;
    s0=s0*2;
    s=s1+s0+f(0)+f(1);
    s=s*h/6;
    s1=0,s0=0;
    n=n*2,h=1.0/n;
   for(i=1;i<n;i++)
    {
     s0=s0+f(i*h);
    }
   for(i=1;i<n+1;i++)
    {
     s1=s1+f((2*i-1)*h/2);
    }
     s1=s1*4;
     s0=s0*2;
     ss=s1+s0+f(0)+f(1);
     ss=ss*h/6;
    while(abs(ss-s)>0.000001)
    {   s=ss;
        s1=0,s0=0;
        n=n*2,h=1.0/n;
      for(i=1;i<n;i++)
     {
      s0=s0+f(i*h);
     }
    for(i=1;i<n+1;i++)
     {
      s1=s1+f((2*i-1)*h/2);
     }
      s1=s1*4;
      s0=s0*2;
      ss=s1+s0+f(0)+f(1);
      ss=ss*h/6;
     }
  cout<<"近似值为"<<ss<<endl;
  cout<<"n个区间与2n个区间之间的差为"<<ss-s<<endl;
  cin>>h;
  if(h!=98989)
   break;
 }
return(0);
}

