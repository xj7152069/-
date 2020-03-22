#include <iostream>
#include<math.h>
using namespace std;
double f1(int n)   //n代表小区间数量
{ int i;
  double y,h=1.0/n;
  double s0=0;
  for(i=1;i<n;i++)
   {
    s0=s0+sqrt(h*i); 
   }
y=(s0+0.5*sqrt(0)+0.5*sqrt(1))*h;
 return(y);
}

double f2(int n)
{int i;
  double y,h=1.0/n;
  double s0=0;
  for(i=1;i<n;i++)
   {
    s0=s0+(1/(1+h*i)); 
   }
  y=(s0+0.5*(1/(1+0))+0.5*(1/(1+1)))*h;
  return(y);
}

double f3(int n)
{ int i;
  double y,h=1.0/n;
  double s0=0;
  for(i=1;i<n;i++)
   {
    s0=s0+2.0/(2+sin(10*3.1415926*h*i)); 
   }
  y=(s0+2.0/(2+sin(10*3.1415926*0))+2.0/(2+sin(10*3.1415926*1)))*h;
  return(y);
}

int main()
{ cout<<"Romberg积分方法"<<endl;
  while(1)
 {
  double i,n,rr,r;
  n=1;
  r=f1(n);
  n=n*2;
  rr=f1(n);
    while(abs(rr-r)>0.000001)
    {   r=rr;
        n=n*2;
        rr=f1(n);
     }
  cout<<"第1个积分的近似值为"<<rr<<endl;
  cout<<"n个区间与2n个区间之间的差为"<<rr-r<<endl<<endl;

  n=1;
  r=f2(n);
  n=n*2;
  rr=f2(n);
    while(abs(rr-r)>0.000001)
    {   r=rr;
        n=n*2;
        rr=f2(n);
     }
  cout<<"第2个积分的近似值为"<<rr<<endl;
  cout<<"n个区间与2n个区间之间的差为"<<rr-r<<endl<<endl;

  n=1;
  r=f3(n);
  n=n*2;
  rr=f3(n);
    while(abs(rr-r)>0.000001)
    {   r=rr;
        n=n*2;
        rr=f3(n);
     }
  cout<<"第3个积分的近似值为"<<rr<<endl;
  cout<<"n个区间与2n个区间之间的差为"<<rr-r<<endl<<endl;


  cin>>r;
  if(r!=98989)
   break;
 }
return(0);
}

