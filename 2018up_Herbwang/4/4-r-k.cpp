#include <iostream>
#include <stdio.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
double f1(double x,double y)
 {double f;
  f=(-2)*y+2*x*x+2*x;
  return(f);}

double f2(double x,double y)
{ double f;
   f=(-1)*y+x+1;
  return(f);
}

int main()
{    cout<<"R-K算法"<<endl;
       ofstream outf1;
       ofstream outf3;
       ofstream outf2;
       outf1.open("/home/dell/my/dat1");
  outf2.open("/home/dell/my/dat2");
  outf3.open("/home/dell/my/dat3");  //打开指定目录下的文件，以写入数据用于绘图
while(1)
{    double i,x,y,h=0.001,s,k1,k2,k3,k4;
      y=1,x=0;
    cout<<"第1个方程的数值解为"<<endl<<y<<" ";
   
    for(i=h;i<=0.5;i=i+h)
    {
       k1=f1(x,y); 
       k2=f1(x+0.5*h,y+0.5*k1);
       k3=f1(x+0.5*h,y+0.5*k2);
       k4=f1(x+0.5*h,y+0.5*k3);
       s=y+(h/6)*(k1+2*k2+2*k3+k4);
      cout<<s<<" ";
      outf1.write((char*)&x,sizeof(x));
      outf1.write((char*)&s,sizeof(s));
      y=s,x=x+h;
     }

 y=1,x=0;cout<<endl<<"第2个方程的数值解为"<<endl<<y<<" ";
 
    for(i=h;i<=1;i=i+h)
    {
       k1=f2(x,y); 
       k2=f2(x+0.5*h,y+0.5*k1);
       k3=f2(x+0.5*h,y+0.5*k2);
       k4=f2(x+0.5*h,y+0.5*k3);
       s=y+(h/6)*(k1+2*k2+2*k3+k4);
      cout<<s<<" ";
      outf2.write((char*)&x,sizeof(x));
      outf2.write((char*)&s,sizeof(s));
      y=s,x=x+h;
    }

   y=1,x=0;cout<<endl<<"比较函数的值为"<<endl<<y<<" ";

    for(i=h;i<=1;i=i+h)
    { x=x+h;
      s=exp(-x)+x;
      cout<<s<<" ";
      outf3.write((char*)&x,sizeof(x));
      outf3.write((char*)&s,sizeof(s));
    }
    double s2;
   y=1,x=0;cout<<endl<<"与比较函数的误差为"<<endl<<0<<" ";
 
    for(i=h;i<=1;i=i+h)
    {   k1=f2(x,y); 
       k2=f2(x+0.5*h,y+0.5*k1);
       k3=f2(x+0.5*h,y+0.5*k2);
       k4=f2(x+0.5*h,y+0.5*k3);
       s=y+(h/6)*(k1+2*k2+2*k3+k4);
      y=s,x=x+h;
      s2=exp(-x)+x;
      cout<<s-s2<<" ";
  
    }

outf3.close();
outf2.close();
outf1.close();
cin>>h;
  if(h!=98989)
   break;
 }
    return(0);
}
