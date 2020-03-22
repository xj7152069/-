#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#include"mpi.h"
using namespace std;
float s1[1000][2000],s2[1000][2000],s3[1000][2000],s4[10000][2000],p1[1000][2000],p2[1000][2000],sx11[1000][2000],sx12[1000][2000],sx13[1000][2000],sx21[1000][2000],sx22[1000][2000],sx23[1000][2000],sx32[1000][2000],sx33[1000][2000],sx31[1000][2000],sx24[1000][2000];
int main()
{   //定义变量，并初始化
   float X,Y,T,DX,DY,DT,a1,a2,a3,a4,a5,a6,a7,a8,xf,t,x,z,dx,dy,ddx,ddy,snx1,sny1,snx2,sny2,t2,t5;
    int i,j,k,n,n1,i1,j1,t3,t4,N,N1,N2,D,m;
    float xs2[5]={1.666667,-0.238095,0.039683,-0.004960,0.000317};
    float xs1[10]={-0.0007926,0.00991800,-0.0595200,0.238080,-0.833333,0.833333,-0.238080,0.0595200,-0.00991800,0.0007926};
    float f,u0(0),u1(0),u2(0),u3(0),u4(0),u5(0),u(0),ux(0),uy(0);

  int cpuid,sumcpu;
  int argc;
  char **argv;

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&sumcpu);
  MPI_Comm_rank(MPI_COMM_WORLD,&cpuid);

if(cpuid==0)
{
    t=0.001,t2=0,x=0,z=0,xf=200,X=400,Y=200,T=800,DX=10,DY=10,DT=0.001,a1=-9,a2=-9,a3=-9,a4=-9,a5=-9,a6=1,a7=-9,a8=-9;
     xf=0.5*(X);
      for(j=0;j<1000;j++)
       {for(i=0;i<2000;i++)
         {p2[j][i]=3000;
          p1[j][i]=3000;}}

     //功能选择
  while(a1!=0)
 {  cout<<endl;cout<<endl;
    cout<<"************************************************"<<endl;
    cout<<"you can input the number to choose the following function"<<endl;
    cout<<"1--self-strike and self-receive pattern(may spend long time)"<<endl;
    cout<<"2--change the defaults parameters and input the underground model from your file"<<endl;
    cout<<"3--output the seismic record of horizontal profile(x-t)"<<endl;
    cout<<"4--output the seismic record of vertical profile(y-t)"<<endl;
    cout<<"5--output a wave front"<<endl;
    cout<<"6--change the seismic focus model"<<endl;
    cout<<"7--output the seismic movie(the file may be large)"<<endl;
    cout<<"0--quit the function chose and output the data"<<endl;
    cout<<"************************************************"<<endl;
    cin>>a1;
     if(a1==1)
    {a8=1;
     cout<<"please input the separation distance of seismic focus"<<endl;
     cin>>D;
     cout<<"the data will be saved as da"<<endl;
     cout<<"input a number to continue:";
     cin>>n1;}

    //改变参数值
     if(a1==2)
    {
     cout<<"please inpout the range X, but the X can't over 1980"<<endl;
     cin>>X;
     while(X>1980)
    {cout<<"the X has over the range, please input again"<<endl;
     cin>>X;}
     cout<<"please inpout the range Y, but the Y can't over 980"<<endl;
     cin>>Y;
     while(Y>980)
    {cout<<"the Y has over the range, please input again"<<endl;
     cin>>Y;}
     cout<<"please inpout the T, but the T can't over 10000"<<endl;
     cin>>T;
     while(T>10000)
    {cout<<"the T has over the range, please input again"<<endl;
     cin>>T;}
     cout<<"please inpout the DX&DY:";
     cin>>DX;
     DY=DX;
     cout<<"please inpout the DT:";
     cin>>DT;
     cout<<"OK"<<endl;

    //输入速度模型
     ifstream infile;
     infile.open("/home/dell/my/sm/m.txt");
     if(!infile) cout<<"error"<<endl;
     float t1;
     float*p=&p2[0][0];
      for(j=0;j<Y;j++)
     {for(i=0;i<X;i++)
      {
       if(infile>>t1)           
       {*p=t1;
         p++;}
       }
       for(i1=0;i1<2000-X;i1++)
       p++;
      }
     infile.close();

     cout<<"the input of model has finished"<<endl;
     cout<<"your underground model will be saved as dat2"<<endl;
     a2=1; xf=0.5*(X);
     cout<<"input a number to continue:";
     cin>>n1;
    }
    if(a1==3)
    {cout<<"please input the z"<<endl;
     cin>>z;
     while(z>Y || z<0)
    {cout<<"the z has over the range, please input again"<<endl;
     cin>>z;}
     a3=1;
     cout<<"the data will be saved as dat3"<<endl;
     cout<<"input a number to continue:";
     cin>>n1;}
     if(a1==4)
    {cout<<"please input the x"<<endl;
     cin>>x;
     while(x>X || x<0)
    {cout<<"the x has over the range, please input again"<<endl;
     cin>>x;}
     a4=1;
     cout<<"the data will be saved as dat4"<<endl;
     cout<<"input a number to continue:";
     cin>>n1;}
     if(a1==5)
    {cout<<"please input the t"<<endl;
     cin>>t2;a5=1;
     cout<<"the data will be saved as dat5"<<endl;
     cout<<"input a number to continue:";
     cin>>n1;}
     if(a1==6)
    { cout<<"1--change the site of single seismic focus"<<endl;
      cout<<"2--the surface is filled with seismic focus"<<endl;
      cin>>a6;
      if(a6==1)
      {cout<<"please input the site of seismic focus"<<endl;
       cin>>xf;}
       cout<<"OK"<<endl;
       cout<<"input a number to continue:";
       cin>>n1;}
     if(a1==7)
    {cout<<"your movie data will be saved as dat1"<<endl;
     a7=1;
     cout<<"input a number to continue:";
     cin>>n1;}
    if(a1==0)
    {cout<<"the simulation has begin, please wait a moment"<<endl;}
     }

     float C3=3.0/2/(30)/DX*log(1000)/(30)/DX/(30)/DX;
       t5=Y/X;
}

  MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);  
  MPI_Bcast(&t5,1,MPI_FLOAT,0,MPI_COMM_WORLD);  

  MPI_Bcast(&T,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
  MPI_Bcast(&X,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
      //自己自守模式
  MPI_Bcast(&Y,1,MPI_FLOAT,0,MPI_COMM_WORLD);  

  MPI_Bcast(&DX,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
  MPI_Bcast(&DY,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
  MPI_Bcast(&DT,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
  MPI_Bcast(&D,1,MPI_INT,0,MPI_COMM_WORLD);  
  MPI_Bcast(&Y,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
  MPI_Bcast(&Y,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
  MPI_Bcast(&Y,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
          if(a8==1)
          {ofstream outf8;
           outf8.open("/home/dell/my/sm/s1.txt");               

       for(m=cpuid;m<N;m+=sumcpu)
       {
    for(j=0;j<1000;j++)
    {for(i=0;i<2000;i++)
     { 
      s1[j][i]=0.0;s2[j][i]=0.0;s3[j][i]=0.0;
      sx11[j][i]=0.0;sx12[j][i]=0.0;sx13[j][i]=0.0;
      sx21[j][i]=0.0;sx22[j][i]=0.0;sx23[j][i]=0.0;
      sx31[j][i]=0.0;sx32[j][i]=0.0;sx33[j][i]=0.0;
      sx24[j][i]=0.0;
     }
    }
        for(k=1;k<T;k++)
       {
        for(j=5;j<Y+5;j++)
       {for(i=5;i<X+5;i++)
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
           if(j==40 && i==35+m*D)
{f=(3.1415926)*(3.1415926)*900*(k*DT-0.04)*exp((-3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04)))*(3-2*3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04));}
           else {f=0;}
           u3=(p2[j-5][i-5]*p2[j-5][i-5]*(DT/DX)*(DT/DX));
           s3[j][i]=(u1+u2-2*u*s2[j][i])*u3+2*s2[j][i]-s1[j][i]+f;
           snx1=0.0;snx2=0.0;
           sny1=0.0;sny2=0.0;
           dx=0;ddx=0;dy=0;ddy=0;
           if(i>=X-26 && j<=t5*i+5*(1-t5) && j>=-t5*i+Y+5+5*t5)	   //角落处理	
	   snx1=i-(X-26);
           if(i<=34 && j>=t5*i+5*(1-t5) && j<=-t5*i+Y+5+t5*5)		
	   snx2=34-i;
           if(j>=Y-26 && j>t5*i+5*(1-t5) && j>-t5*i+Y+5+5*t5)		
	   sny1=j-(Y-26);
           if(j<=34 && j<t5*i+5*(1-t5) && j<-t5*i+Y+5+5*t5)		
	   sny2=34-j;		
           if(sny1 !=0)
          {dy=p2[j][i]*C3*sny1*sny1*DY*DY;
	   ddy=p2[j][i]*C3*2*sny1*DY;	
           }
          if(sny2 !=0)
          {dy=p2[j][i]*C3*sny2*sny2*DY*DY;
	   ddy=p2[j][i]*C3*2*sny2*DY;	
           }
          if(snx1 !=0)
          {dx=p2[j][i]*C3*snx1*snx1*DX*DX;
	   ddx=p2[j][i]*C3*2*snx1*DX;	
           }
          if(snx2 !=0)
          {dx=p2[j][i]*C3*snx2*snx2*DX*DX;
	   ddx=p2[j][i]*C3*2*snx2*DX;	
           }
         if(i>=0.5*(X+5))
           t3=1;
         else
           t3=-1;
         if(j>=40)
           t4=1;
         else
           t4=-1;
if(snx1!=0 || snx2!=0)
{sx11[j][i]=p2[j][i]*p2[j][i]*DT*DT*(u2-u*s2[j][i])*(1.0/(DX*DX))-dx*dx*DT*DT*sx12[j][i]+(2*sx12[j][i]-sx13[j][i])+DT*(2*dx*(sx13[j][i]-sx12[j][i]));
sx21[j][i]=(-p2[j][i]*p2[j][i]*ddx*(1.0/(DX))*(ux*t3)-dx*dx*dx*sx22[j][i]+3*dx*dx*(sx23[j][i]-sx22[j][i])/DT+3*dx*(2*sx23[j][i]-sx22[j][i]-sx24[j][i])/(DT*DT)+(3*sx22[j][i]-3*sx23[j][i]+sx24[j][i])/(DT*DT*DT))*(DT*DT*DT);
sx31[j][i]=DT*DT*p2[j][i]*p2[j][i]*(1.0/(DX*DX))*(u1-u*s2[j][i])+2*sx32[j][i]-sx33[j][i];}
else    
{sx11[j][i]=p2[j][i]*p2[j][i]*DT*DT*(u1-u*s2[j][i])*(1.0/(DX*DX))-dy*dy*DT*DT*sx12[j][i]+(2*sx12[j][i]-sx13[j][i])+DT*(2*dy*(sx13[j][i]-sx12[j][i]));
sx21[j][i]=(-p2[j][i]*p2[j][i]*ddy*(1.0/(DX))*(uy*t4)-dy*dy*dy*sx22[j][i]+3*dy*dy*(sx23[j][i]-sx22[j][i])/DT+3*dy*(2*sx23[j][i]-sx22[j][i]-sx24[j][i])/(DT*DT)+(3*sx22[j][i]-3*sx23[j][i]+sx24[j][i])/(DT*DT*DT))*(DT*DT*DT);
sx31[j][i]=DT*DT*p2[j][i]*p2[j][i]*(1.0/(DX*DX))*(u2-u*s2[j][i])+2*sx32[j][i]-sx33[j][i];}     
              
     // if(snx1!=0 || snx2!=0 || sny1!=0 || sny2!=0)
        s3[j][i]=sx11[j][i]+sx21[j][i]+sx31[j][i]+f;


        if(j==41 && i==35+m*D)
        {s4[k][i]=s3[j][i];}
       
      
         u1=0,u2=0,u3=0,u4=0,u=0,ux=0,uy=0;
        }
       }
          for(j1=0;j1<1000;j1++)
         {for(i1=0;i1<2000;i1++)
         {s1[j1][i1]=s2[j1][i1];s2[j1][i1]=s3[j1][i1];
          sx13[j1][i1]=sx12[j1][i1],sx12[j1][i1]=sx11[j1][i1];
          sx33[j1][i1]=sx32[j1][i1],sx32[j1][i1]=sx31[j1][i1];
          sx24[j1][i1]=sx23[j1][i1],sx23[j1][i1]=sx22[j1][i1],sx22[j1][i1]=sx21[j1][i1];
        }
          } 
       }
      cout<<m<<endl;
      }   
for(i1=N1;i1<N2;i1++)
{for(j1=1;j1<T;j1++)
 {    outf8<<s4[j1][35+i1*D]<<" ";  }
   outf8<<endl;
}
cout<<"the number of seismic trace is:"<<N<<endl;
outf8.close(); 
}
    
    for(j=0;j<1000;j++)
    {for(i=0;i<2000;i++)
     { 
      s1[j][i]=0.0;s2[j][i]=0.0;s3[j][i]=0.0;
      sx11[j][i]=0.0;sx12[j][i]=0.0;sx13[j][i]=0.0;
      sx21[j][i]=0.0;sx22[j][i]=0.0;sx23[j][i]=0.0;
      sx31[j][i]=0.0;sx32[j][i]=0.0;sx33[j][i]=0.0;
      sx24[j][i]=0.0;
     }
    }
    
cout<<endl<<"finished"<<endl;
cin>>n;

 MPI_Finalize();
return(0);
}
