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
{    cout<<"Euler算法"<<endl;
       ofstream outf1;
       ofstream outf3;
       ofstream outf2;
       outf1.open("/home/dell/my/dat1");
  outf2.open("/home/dell/my/dat2");
  outf3.open("/home/dell/my/dat3");  //打开指定目录下的文件，以写入数据
while(1)
{    double i,x,y,h=0.001,s;
      y=1,x=0;
     int x1,x2;
    cout<<"第1个方程的数值解为"<<endl<<y<<" ";
     x1=0;x2=0;
    for(i=h;i<=0.5;i=i+h)
    { 
      s=y+f1(x,y)*h;
      s=y+0.5*h*(f1(x,y)+f1(x+h,s));
      cout<<s<<" ";
      x1++;
      if(x1%5==0)
      {outf1.write((char*)&x,sizeof(x));
      outf1.write((char*)&s,sizeof(s));
       x2++;}
      y=s,x=x+h;
     }
cout<<endl<<x1<<endl;
 y=1,x=0;cout<<endl<<"第2个方程的数值解为"<<endl<<y<<" ";
   x1=0;
    for(i=h;i<=1;i=i+h)
    { x1++;
      s=y+f2(x,y)*h;
      s=y+0.5*h*(f2(x,y)+f2(x+h,s));
      cout<<s<<" ";
      if(x1%5==0)
      {outf2.write((char*)&x,sizeof(x));
     outf2.write((char*)&s,sizeof(s));}
      y=s,x=x+h;
    }

   y=1,x=0;cout<<endl<<"比较函数的值为"<<endl<<y<<" ";
   x1=0;
    for(i=h;i<=1;i=i+h)
    { x1++;
      x=x+h;
      s=exp(-x)+x;
      cout<<s<<" ";
      if(x1%5==0)
     { outf3.write((char*)&x,sizeof(x));
      outf3.write((char*)&s,sizeof(s));}
    }
    double s2;
   y=1,x=0;cout<<endl<<"与比较函数的误差为"<<endl<<0<<" ";
    
    for(i=h;i<=1;i=i+h)
    {  s=y+f2(x,y)*h;
      s=y+0.5*h*(f2(x,y)+f2(x+h,s));
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


      
