//在模拟主程序中都已经使用了变量
//正确定义了动态二维数组
//改变了数据的输出方向

#include "su.h"
#include "segy.h"
#include <signal.h>


#include <iostream>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#include<complex>
using namespace std;
float **s1,**s2,**s3,**s4,**sx11,**sx12,**sx13,**sx21,**sx22,**sx23,**sx24,**sx31,**sx32,**sx33,**s;
float p2[2000][2000];


complex<float> add(complex<float> a, complex<float> b)  //复数加法的定义  
{   complex<float> c;
	c.real() = a.real() + b.real();
	c.imag() = a.imag() + b.imag();
	return c;
}


complex<float> mul(complex<float> a, complex<float> b)  //复数乘法的定义  
{
    complex<float> c;
	c.real()= a.real()*b.real() - a.imag()*b.imag();
	c.imag()= a.real()*b.imag() + a.imag()*b.real();
	return c;
}

complex<float> muls(complex<float> a, float b)  //复数乘法的定义  
{
    complex<float> c;
	c.real()= a.real()*b;
	c.imag()= a.imag()*b;
	return c;
}

complex<float> ec(int k,int i,int M,int l,int j,int N) //!根据欧拉公式转换e指数函数
{
float pi;
float u;
pi=3.1415926;
u=2*pi*((((k*i)/float(M)))+(((l*j)/float(N))));
complex<float> ec(cos(u),sin(u));
return ec;
}

complex<float> e_c(int k,int i,int M,int l,int j,int N)
{
float pi;
float u;
pi=3.1415926;
u=2*pi*((((k*i)/float(M)))+(((l*j)/float(N))));
complex<float> e_c(cos(u),-sin(u));
return e_c;
}


int main()
{
  //////////////////////////////////////////////////////////////////定义变量，并初始化///////////////////////////////////////////////////////
   float T,DX,DY,DT,a1,a2,a3,a4,a5,a6,a7,a8,xf,t,x,z,dx,dy,ddx,ddy,snx1,sny1,snx2,sny2,t2,t5,r;
    int i,j,k,n,n1,i1,j1,t3,t4,N,D,m,X,Y;
	int mm,nn,MM,NN,uu,vv;
    float xs2[5]={1.666667,-0.238095,0.039683,-0.004960,0.000317};
    float xs1[10]={-0.0007926,0.00991800,-0.0595200,0.238080,-0.833333,0.833333,-0.238080,0.0595200,-0.00991800,0.0007926};
    float f,u0(0),u1(0),u2(0),u3(0),u4(0),u5(0),u(0),ux(0),uy(0),pi(3.1415926);
	complex<float> v[256][256],vf[256][256],b1,b2,b3,k1,k2,k3,k4;
    t=0.001,t2=298,x=0,z=0,xf=,X=236,Y=236,T=300,DX=10,DY=10,DT=0.001,a1=-9,a2=-9,a3=-9,a4=-9,a5=1,a6=1,a7=1,a8=-9,MM=X,NN=Y;
    for (i=0;i<236;i++)
      {for(j=0;j<236;j++)
        {p2[i][j]=3000;
         v[i][j]=0.0;
         vf[i][j]=0.0;}}
	r=1.0/sqrt(X*Y);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          
     
     
     
 //////////////////用指针的形式定义动态数组//////////////////////////////////////////////////////////////////////////////////////////    
    s=new float*[Y+20];    
    for(j=0;j<Y+20;j++)  
    {  
        s[j]=new float[X+20];  
    };
    
    s1=new float*[Y+20];    
    for(j=0;j<Y+20;j++)  
    {  
        s1[j]=new float[X+20];  
    };
    
    s2=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        s2[j]=new float[X+20];  
    };
    
    s3=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        s3[j]=new float[X+20];  
    };
    
    sx11=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx11[j]=new float[X+20];  
    };
    
    sx12=new float*[Y+20];    
    for(j=0;j<Y+20;j++)  
    {  
        sx12[j]=new float[X+20];  
    };
    
    sx13=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx13[j]=new float[X+20];  
    };
    
    sx21=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx21[j]=new float[X+20];  
    };
    
    sx22=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx22[j]=new float[X+20];  
    };
    
    sx23=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx23[j]=new float[X+20];  
    };
    
    sx24=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx24[j]=new float[X+20];  
    };
    
    sx31=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx31[j]=new float[X+20];  
    };
    
     
    sx32=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx32[j]=new float[X+20];  
    };
    
    sx33=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx33[j]=new float[X+20];  
    };
    
     for(j=0;j<Y+20;j++)
      {
      for(i=0;i<X+20;i++)
       {
       s1[j][i]=0.0;s2[j][i]=0.0;s3[j][i]=0.0;
     sx11[j][i]=0.0;sx12[j][i]=0.0;sx13[j][i]=0.0;
     sx21[j][i]=0.0;sx22[j][i]=0.0;sx23[j][i]=0.0;sx24[j][i]=0.0;
     sx31[j][i]=0.0;sx32[j][i]=0.0;sx33[j][i]=0.0;
     }
     }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     
     
cout<<"begin"<<endl;
   
///////////////////////////////绘制速度模型的声波传播过程（主程序）///////////////////////////////////////////////////////////////////   
       ofstream outf3;
       ofstream outf4;
       ofstream outf2;
       ofstream outf5;
       ofstream outf;
	if(a7==1)
        {
        outf.open("/home/dell/my/sm/dat1");}
        if(a2==1)
        {
        outf2.open("/home/dell/my/sm/dat2");}
        if(a5==1)
        {
        outf5.open("/home/dell/my/sm/dat5");}
        if(a3==1)
        {
        outf3.open("/home/dell/my/sm/dat3");}
        if(a4==1)
        {
        outf4.open("/home/dell/my/sm/dat4");}
   
       
        for(k=1;k<T;k++)
       { 
       
 /*for (uu=5;uu<MM+5;uu++)
  {
   cout<<"zheng"<<uu;
  for (vv=5;vv<NN+5;vv++)    //!正变换
    {for (mm=5;mm<MM+5;mm++)
      {for (nn=5;nn<NN+5;nn++)
         {
         b1=muls(e_c(uu,mm,MM,vv,nn,NN),s2[mm][nn]);
         b2=muls(b1,r);
         b3=add(v[uu][vv],b2);
         v[uu][vv]=b3;
      
         }
      }
    }
  }
  
     for (mm=5;mm<MM+5;mm++)
      {cout<<"fan"<<mm;
      for (nn=5;nn<NN+5;nn++)   //!反变换
        {for (uu=5;uu<MM+5;uu++)
          {for (vv=5;vv<NN+5;vv++)
            { 
            k1=mul(v[uu][vv],ec(uu,mm,MM,vv,nn,NN));
            k2=muls(k1,-(2*pi*float(mm)/MM+2*pi*float(nn)/NN));
            k3=muls(k2,r);
            k4=add(vf[mm][nn],k3);
            vf[mm][nn]=k4;
         
      }
     }
    }
   }
   
       for (mm=5;mm<X+5;mm++)
      {for(nn=5;nn<Y+5;nn++)
        {s[mm][nn]=abs(vf[mm][nn]);}}  */
        
       pfa2rc(-1,1,X,Y,s2[0],v[0]);
        
        pfa2cc(-1,2,X,Y,v[0]);
        
        for (uu=5;uu<MM+5;uu++)
          {for (vv=5;vv<NN+5;vv++)
            { 
            k2=muls(v[uu][vv],-(2*pi*float(mm)/MM+2*pi*float(nn)/NN));
            vf[mm][nn]=k2;
            }
          }
             
         pfa2cc(1,2,X,Y,v[0]);
        
        pfa2cr(1,1,X,Y,v[0],s[0]);
       
        for(i=5;i<X+5;i++)
       {for(j=5;j<Y+5;j++)
        {
           for(n=0;n<5;n++)
           {  
           u=u+2*xs2[n];
           u1=u1+xs2[n]*(s2[j-n-1][i]+s2[j+n+1][i]);
           u2=u2+xs2[n]*(s2[j][i-n-1]+s2[j][i+n+1]);
           }
           for(n=0;n<10;n++)
           {if(n<5)
            {ux=ux+s2[j][i+n-5]*xs1[n];
             uy=uy+s2[j+n-5][i]*xs1[n];}
            else
            {ux=ux+s2[j][i+n-4]*xs1[n];
             uy=uy+s2[j+n-4][i]*xs1[n];}
           }
           if(j==200 && a6==2 && i>=40 && i<=X-30) 
          {f=(3.1415926)*(3.1415926)*900*(k*DT-0.04)*exp((-3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04)))*(3-2*3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04));}
           else if(j==150 && i==xf && a6==1)
{f=(3.1415926)*(3.1415926)*900*(k*DT-0.04)*exp((-3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04)))*(3-2*3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04));}
           else {f=0;}




           u3=(p2[j-5][i-5]*p2[j-5][i-5]*(DT/DX)*(DT/DX));
           //s3[j][i]=(u1+u2-2*u*s2[j][i])*u3+2*s2[j][i]-s1[j][i]+f;
             s3[j][i]=s[j][i]*p2[j][i]*p2[j][i]*DT*DT+s1[j][i]-2*s2[j][i]+f;


        if(i==x && a4==1)
        {outf4.write((char*)&s3[j][i],sizeof(s3[j][i]));
         }
        if(j==z && a3==1)
        {outf3.write((char*)&s3[j][i],sizeof(s3[j][i]));
         }
        if(k==t2 && a5==1)
        {outf5.write((char*)&s3[j][i],sizeof(s3[j][i]));
         }
        if(k==1 && a2==1)
        {outf2.write((char*)&p2[j-5][i-5],sizeof(p2[j-5][i-5]));
         }
        if(k%4==0 && a7==1)
        {outf.write((char*)&s3[j][i],sizeof(s3[j][i]));}
      
         u1=0,u2=0,u3=0,u4=0,u=0,ux=0,uy=0;
        }
       }
          for(j1=0;j1<Y+20;j1++)
         {for(i1=0;i1<X+20;i1++)
         {s1[j1][i1]=s2[j1][i1];s2[j1][i1]=s3[j1][i1];
          sx13[j1][i1]=sx12[j1][i1],sx12[j1][i1]=sx11[j1][i1];
          sx33[j1][i1]=sx32[j1][i1],sx32[j1][i1]=sx31[j1][i1];
          sx24[j1][i1]=sx23[j1][i1],sx23[j1][i1]=sx22[j1][i1],sx22[j1][i1]=sx21[j1][i1];
        }
          }
          cout<<k<<endl;
       }
if(a2==1)
outf2.close(); 
if(a7==1)
outf.close(); 
if(a5==1)
outf5.close(); 
if(a3==1)
outf3.close(); 
if(a4==1)
outf4.close(); 
   
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
   
   
   
   
   
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
    for(int i=0;i<Y+20;i++)  
        delete []s1[i];//先单独释放第一维中每个数组的内存  
    delete []s1;
    
    for(int i=0;i<Y+20;i++)  
        delete []s2[i];//先单独释放第一维中每个数组的内存  
    delete []s2;
    
    for(int i=0;i<Y+20;i++)  
        delete []s3[i];//先单独释放第一维中每个数组的内存  
    delete []s3;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx11[i];//先单独释放第一维中每个数组的内存  
    delete []sx11;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx12[i];//先单独释放第一维中每个数组的内存  
    delete []sx12;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx13[i];//先单独释放第一维中每个数组的内存  
    delete []sx13;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx21[i];//先单独释放第一维中每个数组的内存  
    delete []sx21;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx22[i];//先单独释放第一维中每个数组的内存  
    delete []sx22;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx23[i];//先单独释放第一维中每个数组的内存  
    delete []sx23;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx24[i];//先单独释放第一维中每个数组的内存  
    delete []sx24;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx31[i];//先单独释放第一维中每个数组的内存  
    delete []sx31;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx32[i];//先单独释放第一维中每个数组的内存  
    delete []sx32;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx33[i];//先单独释放第一维中每个数组的内存  
    delete []sx33;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   

cout<<endl<<"finished"<<endl;
cin>>n;
return(0);
}
