#include <iostream>
#include<math.h>
using namespace std;
double f1(double x)   //n代表小区间数量
{ double y;
y=sqrt(x);
 return(y);
}

double f2(double x)
{double y;
 y=1.0/(1+x);
  return(y);
}

double f3(double x)
{ double y;
  y=2.0/(2+sin(10*3.1415926*x));
  return(y);
}

int main()
{ cout<<"自适应方法"<<endl;
  
  double a,b,a1,b1,s,s1,s2,e,h;
  a=0,b=1,a1=0,b1=0,s=0;
  h=abs(a-b);
cout<<"please input the fault"<<endl;
cin>>e;
  while(h!=0)
   { 
     b1=b;s1=0;s2=e*20;
     while(abs(s1-s2)>e*15)
    {
     s1=(h/6)*(f1(a1)+4*f1(a1+h/2)+f1(a1+h));
     s2=(h/12)*(f1(a1)+4*f1(a1+h/4)+2*f1(a1+h/2)+4*f1(a1+3*h/4)+f1(a1+h));
     h=h/2; 
     }
     h=h*2;
     a1=a1+h;
     h=abs(a1-b);
     s=s+s2;
   }
cout<<"第1个方程的积分是"<<s<<endl;
 
a1=0,b1=0,s=0;
  h=abs(a-b);
  while(h!=0)
   { 
     b1=b;s1=0;s2=e*20;
     while(abs(s1-s2)>15*e)
    {
     s1=(h/6)*(f2(a1)+4*f2(a1+h/2)+f2(a1+h));
     s2=(h/12)*(f2(a1)+4*f2(a1+h/4)+2*f2(a1+h/2)+4*f2(a1+3*h/4)+f2(a1+h));
     h=h/2; 
     }
     h=h*2;
     a1=a1+h;
     h=abs(a1-b);
     s=s+s2;
   }
cout<<"第2个方程的积分是"<<s<<endl;

a1=0,b1=0,s=0;
  h=abs(a-b);
  while(h!=0)
   { 
     b1=b;s1=0;s2=e*20;
     while(abs(s1-s2)>15*e)
    {
     s1=(h/6)*(f3(a1)+4*f3(a1+h/2)+f3(a1+h));
     s2=(h/12)*(f3(a1)+4*f3(a1+h/4)+2*f3(a1+h/2)+4*f3(a1+3*h/4)+f3(a1+h));
     h=h/2; 
     }
     h=h*2;
     a1=a1+h;
     h=abs(a1-b);
     s=s+s2;
   }
cout<<"第3个方程的积分是"<<s<<endl;
cout<<endl<<endl<<"there is another calculation, while the fault e=0.0000000001"<<endl;
a1=0,b1=0,s=0;
  h=abs(a-b);
e=0.00000000001;
  while(h!=0)
   { 
     b1=b;s1=0;s2=e*20;
     while(abs(s1-s2)>15*e)
    {
     s1=(h/6)*(f1(a1)+4*f1(a1+h/2)+f1(a1+h));
     s2=(h/12)*(f1(a1)+4*f1(a1+h/4)+2*f1(a1+h/2)+4*f1(a1+3*h/4)+f1(a1+h));
     h=h/2; 
     }
     h=h*2;
     a1=a1+h;
     h=abs(a1-b);
     s=s+s2;
   }
cout<<"第1个方程的积分是"<<s<<endl;
 
a1=0,b1=0,s=0;
  h=abs(a-b);
  while(h!=0)
   { 
     b1=b;s1=0;s2=e*20;
     while(abs(s1-s2)>15*e)
    {
     s1=(h/6)*(f2(a1)+4*f2(a1+h/2)+f2(a1+h));
     s2=(h/12)*(f2(a1)+4*f2(a1+h/4)+2*f2(a1+h/2)+4*f2(a1+3*h/4)+f2(a1+h));
     h=h/2; 
     }
     h=h*2;
     a1=a1+h;
     h=abs(a1-b);
     s=s+s2;
   }
cout<<"第2个方程的积分是"<<s<<endl;

a1=0,b1=0,s=0;
  h=abs(a-b);
  while(h!=0)
   { 
     b1=b;s1=0;s2=e*20;
     while(abs(s1-s2)>15*e)
    {
     s1=(h/6)*(f3(a1)+4*f3(a1+h/2)+f3(a1+h));
     s2=(h/12)*(f3(a1)+4*f3(a1+h/4)+2*f3(a1+h/2)+4*f3(a1+3*h/4)+f3(a1+h));
     h=h/2; 
     }
     h=h*2;
     a1=a1+h;
     h=abs(a1-b);
     s=s+s2;
   }
cout<<"第3个方程的积分是"<<s<<endl;
  cin>>h;
return(0);
}

