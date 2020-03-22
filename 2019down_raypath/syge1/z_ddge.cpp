
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#include<stdlib.h>
//定义矩阵，变量
#define X 30
#define Z 30
#define source_num 60
#define source_num1 30
#define wavephone_num1 30
#define source_num2 30
#define wavephone_num2 30
#define tz 1
#define N 900
#define M 1800
#define I1 0.1
#define eps1 0.000000001
#define bs 2

double **a,**p,**a2;
char *str_firstarrival,*str_raypath,*str_id;
double G[M][N]={0.0},T[M][1]={0.0},T2[M][1]={0.0},DT[M][1]={0.0},GT[N][M]={0.0},GTG[N][N]={0.0},G_1[N][M]={0.0},U[N][N]={0.0},UT[N][N]={0.0},AU[N][N]={0.0},K_1[N][N]={0.0},K_1_GT[N][M]={0.0},model[N][1]={0.0},P[N][1]={0.0},P1[N][1]={0.0},GTd[N][1]={0.0};
float model1[X][Z],model2[X][Z],modeldd[X][Z];
using namespace std;

double distance(double x1,double y1,double x2,double y2)  
{
double L;
L=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
return L;
}

//统计直射线在模型任意小方块中的长度
//x1,x2,y1,y2为方块四角坐标，注意：要求有x1<x2;y1<y2;
double cd(double x1,double x2,double y1,double y2,double Lx1,double Lx2,double Ly1,double Ly2)
{
if((Lx1-Lx2)==0 && Lx1<(X*0.5))
 {Lx2=Lx2+0.000001;}
else if((Lx1-Lx2)==0 && Lx1>=(X*0.5))
 {Lx2=Lx2-0.000001;}

if((Ly1-Ly2)==0 && Ly1<(Z*0.5))
 {Ly2=Ly2+0.000001;}
else if((Ly1-Ly2)==0 && Ly1>=(Z*0.5))
 {Ly2=Ly2-0.000001;}
 
int jd_id(0);
double jd[6][2];
double k,lena,lenb;
double jd_x,jd_y;
k=(Ly1-Ly2)/(Lx1-Lx2);
//(x1,y1);((x1,y2))
jd_x=x1;
jd_y=Ly1+k*(jd_x-Lx1);
lena=distance(jd_x,jd_y,Lx1,Ly1);
lenb=distance(jd_x,jd_y,Lx2,Ly2);
if((jd_y-y1)*(jd_y-y2)<=0)
{if(lena<0.001 || lenb<0.001 || (jd_x-Lx1)*(jd_x-Lx2)<=0)
{
jd[jd_id][0]=jd_x;
jd[jd_id][1]=jd_y;
jd_id++;
}
}
//(x2,y1);((x2,y2))
jd_x=x2;
jd_y=Ly1+k*(jd_x-Lx1);
lena=distance(jd_x,jd_y,Lx1,Ly1);
lenb=distance(jd_x,jd_y,Lx2,Ly2);
if((jd_y-y1)*(jd_y-y2)<=0)
{
if(lena<0.001 || lenb<0.001 || (jd_x-Lx1)*(jd_x-Lx2)<=0)
{
jd[jd_id][0]=jd_x;
jd[jd_id][1]=jd_y;
jd_id++;
}
}
//(x1,y1);((x2,y1))
jd_y=y1;
jd_x=Lx1+(1.0/k)*(jd_y-Ly1);
lena=distance(jd_x,jd_y,Lx1,Ly1);
lenb=distance(jd_x,jd_y,Lx2,Ly2);
if((jd_x-x1)*(jd_x-x2)<=0)
{
if(lena<0.001 || lenb<0.001 || (jd_x-Lx1)*(jd_x-Lx2)<=0)
{
jd[jd_id][0]=jd_x;
jd[jd_id][1]=jd_y;
jd_id++;
}
}
//(x1,y2);((x2,y2))
jd_y=y2;
jd_x=Lx1+(1.0/k)*(jd_y-Ly1);
lena=distance(jd_x,jd_y,Lx1,Ly1);
lenb=distance(jd_x,jd_y,Lx2,Ly2);
if((jd_x-x1)*(jd_x-x2)<=0)
{
if(lena<0.001 || lenb<0.001 || (jd_x-Lx1)*(jd_x-Lx2)<=0)
{
jd[jd_id][0]=jd_x;
jd[jd_id][1]=jd_y;
jd_id++;
}
}
//////////////////
if((Lx1-x1)*(Lx1-x2)<0 && (Ly1-y1)*(Ly1-y2)<0)
{
jd[jd_id][0]=Lx1;
jd[jd_id][1]=Ly1;
jd_id++; 
}
//////////////////
if((Lx2-x1)*(Lx2-x2)<0 && (Ly2-y1)*(Ly2-y2)<0)
{
jd[jd_id][0]=Lx2;
jd[jd_id][1]=Ly2;
jd_id++; 
}
///////////////////
int i,j;
double cd1(0),cd2(0);
if(jd_id>1)
{for(i=0;i<jd_id-1;i++)
{cd2=distance(jd[jd_id-1][0],jd[jd_id-1][1],jd[i][0],jd[i][1]);
 if(cd2>cd1)
 {cd1=cd2;}
}
}
return cd1;
}

using namespace std;
int main()
{
     double x1,x2,y1,y2,sx_a,sx_b,Lx1,Lx2,Ly1,Ly2,I,eps,ddbc;
     double raypath[9999][3]={-1.0},maxdm,mindm,sum1,sum2;
     ifstream infile;
     ofstream outf;
     double num_of_raypath;
     char str_of_raypath[2];
     int G1(-1),G2,G3(-1),i1,j1,i,j,k,dx(10),dz(10);
     int ddcs(0);
     //ddcs=int(N*N*bs);
     I=I1;
     eps=eps1;
    double source_id,wavephone_id;
    str_firstarrival=new char[99];  
    str_raypath=new char[99];  
    str_id=new char[9];  
    eps=eps1+1;
///////////读入初始模型/////////////////////////////////
     infile.open("model.dat",ios::binary);
     if(!infile) cout<<"error"<<endl;
      for(i=0;i<X;i++)
     {for(j=0;j<Z;j++)
      {
      infile.read(( char *)&modeldd[i][j],sizeof(modeldd[i][j]));  
       }
      }
     infile.close();
    
   for(i1=0;i1<source_num;i1++)
   {
       source_id=i1;
    strcpy(str_firstarrival,"firstarrival.txt");
    strcpy(str_raypath,"raypath.txt");
    sprintf(str_id, "%f", source_id);  //source_id从0开始，直到炮数
    if(source_id<10)
        str_id[1]='\0';
    else if(source_id>=10 && source_id<100)
        str_id[2]='\0';
    else if(source_id>=100 && source_id<1000)
        str_id[3]='\0';
    else if(source_id>=1000 && source_id<10000)
        str_id[4]='\0';
    strcat(str_firstarrival,str_id);
    strcat(str_raypath,str_id);
   //读取观测数据走时文件
     j=0;
     infile.open(str_firstarrival);
     if(!infile) cout<<"error"<<str_firstarrival<<endl;
      while(1)
     {
      if(j<3)
      {infile>>num_of_raypath;}
      else if(j>=3 && (j%3)==0)
      {
       if(infile>>num_of_raypath)
        {G3=G3+1;
         //G1=((num_of_raypath/dx)-tz)+source_id*source_num;
        // cout<<G3<<"-2"<<endl;
         }
       else break;
      }      
      else if(j>=3 && (j%3)==2)
       {
        infile>>num_of_raypath;
        T[G3][0]=num_of_raypath;
       //cout<<num_of_raypath<<endl;
       }
      else if(j>=3 && (j%3)==1)      
       {
        infile>>num_of_raypath;
       }
      j++;
     }
     infile.close();
   }
system("mpirun -np 5 ./first_raytracing_liu \n");
//////////////////////////////////////////////////////
while(eps>eps1)
{ 
    G1=-1;G3=-1;
    for(i=0;i<M;i++)
      for(j=0;j<N;j++)
      {
       G[i][j]=0.0; //只适用于dx=dx情况
      }

  for(i1=0;i1<source_num;i1++)
   {
    source_id=i1;
    for(i=0;i<9999;i++)
      {for(j=0;j<3;j++)
        {raypath[i][j]=-1.0;}
      }
    strcpy(str_firstarrival,"firstarrival.txt");
    strcpy(str_raypath,"raypath.txt");
    sprintf(str_id, "%f", source_id);  //source_id从0开始，直到炮数
    if(source_id<10)
        str_id[1]='\0';
    else if(source_id>=10 && source_id<100)
        str_id[2]='\0';
    else if(source_id>=100 && source_id<1000)
        str_id[3]='\0';
    else if(source_id>=1000 && source_id<10000)
        str_id[4]='\0';
    strcat(str_firstarrival,str_id);
    strcat(str_raypath,str_id);

  //读取射线路径文件
     j=0;
     infile.open(str_raypath);
     if(!infile) cout<<"error"<<str_raypath<<endl;
      while(1)
     {
      k=int(j/4);
      if((j%4)>=2)
       {i=j%4;
        if(infile>>num_of_raypath)
         {raypath[k][i-1]=num_of_raypath;}
        else break;
       }
      else        
       {i=j%4;
        infile>>str_of_raypath[i];
        if(i==0 && str_of_raypath[i]=='M')
        {raypath[k][0]=1.0;}
        else if(i==0 && str_of_raypath[i]!='M')
        {raypath[k][0]=0.0;}
       }
      j++;
     }
     infile.close();
     
  //计算路径长度
    k=0;
    while(raypath[k+1][1]>=0)
    {
     if(raypath[k][0]==1.0)
        {G1=G1+1;
        //G1=((raypath[k][1]/dx)-tz)+source_id*(source_num);
        //cout<<G1<<endl;
        }
        
     if(raypath[k+1][0]==0.0)
     {
       Lx1=raypath[k][1];
       Lx2=raypath[k+1][1];
       Ly1=raypath[k][2];
       Ly2=raypath[k+1][2];
      // if(i1==0)
      // cout<<Lx1<<","<<Ly1<<"-"<<G1<<endl;
       
     for(i=0;i<X;i++)
      for(j=0;j<Z;j++)
      { 
       {x1=i*dx;x2=(i+1)*dx;y1=j*dx;y2=(j+1)*dx;}
       G2=X*j+i;
       G[G1][G2]+=cd(x1,x2,y1,y2,Lx1,Lx2,Ly1,Ly2); //只适用于dx=dx情况
      }
     }
     k++;
    }
     //cout<<"ok:";cin>>eps;
   // cout<<G1<<" "<<G2<<endl;
  //读取走时文件
     j=0;
     infile.open(str_firstarrival);
     if(!infile) cout<<"error"<<str_firstarrival<<endl;
      while(1)
     {
      if(j<3)
      {infile>>num_of_raypath;}
      else if(j>=3 && (j%3)==0)
      {
       if(infile>>num_of_raypath)
        {G3=G3+1;
         }
       else break;
      }      
      else if(j>=3 && (j%3)==2)
       {
        infile>>num_of_raypath;
        T2[G3][0]=num_of_raypath;
       //cout<<num_of_raypath<<endl;
       }
      else if(j>=3 && (j%3)==1)      
       {
        infile>>num_of_raypath;
       }
      j++;
     }
     infile.close();
   }
///////////以上读文件完毕/////////////

    for(i=0;i<M;i++)
    {for(j=0;j<N;j++)
      {
       GT[j][i]=G[i][j];
      }
    }
    
    for(i=0;i<M;i++)
     {DT[i][0]=T[i][0]-T2[i][0];
     }   //DT矩阵
     
    for(i=0;i<N;i++)
     {P[i][0]=P1[i][0];
      P1[i][0]=0.0;}
     
    for(i=0;i<N;i++)
    {for(j=0;j<M;j++)
     {P1[i][0]=P1[i][0]+GT[i][j]*DT[j][0];}
    }
    
    ddbc=10;
  if(ddcs==0)
  {  while(1)
  {
      maxdm=0;
    mindm=99999.0;
   for(i=0;i<X;i++)
   {for(j=0;j<Z;j++)
    {   
        model1[i][j]=modeldd[i][j]-ddbc*(P1[X*(j)+i][0]);
        if(model1[i][j]>maxdm && j<Z-1)
        maxdm=model1[i][j];   
        if(model1[i][j]<mindm && j<Z-1)
        mindm=model1[i][j];      
    }
   }
   if(maxdm>6000 || mindm<1000)
     ddbc=ddbc*0.5;
   else
     break;
  }
  }

  if(ddcs>0)
  {
   sum1=0;sum2=0;
   for(i=1;i<N;i++)
    {sum1+=P[i][0]*P[i][0];
     sum2+=P1[i][0]*P1[i][0];}
   while(1)
  {  
      maxdm=0;
    mindm=99999.0;
   for(i=0;i<X;i++)
   {for(j=0;j<Z;j++)
    {   
        model1[i][j]=modeldd[i][j]-ddbc*(P1[X*j+i][0]+(sum2/sum1)*P[X*j+i][0]);
        if(model1[i][j]>maxdm && j<Z-1)
        maxdm=model1[i][j];   
        if(model1[i][j]<mindm && j<Z-1)
        mindm=model1[i][j];      
    }
   }
   if(maxdm>6000 || mindm<1000)
     ddbc=ddbc*0.5;
   else
     break;
  }
  }
  
  eps=0.0;
    for(i=0;i<X;i++)
    {for(j=0;j<Z;j++)
      {model2[i][j]=model1[i][j];
        if(model2[i][j]>6000)
         {model2[i][j]=6000;}
        if(model2[i][j]<1000)
         {model2[i][j]=1000;}
       eps=eps+(model2[i][j]-modeldd[i][j])*(model2[i][j]-modeldd[i][j]); 
      }
    }
   
    outf.open("model.dat");
  for(i=0;i<X;i++)
    {for(j=0;j<Z;j++)
      {
       modeldd[i][j]=model2[i][j];
       outf.write((char*)&model2[i][j],sizeof(model2[i][j]));
       }
    }
   outf.close(); ///   
system("mpirun -np 5 ./first_raytracing_liu \n");
ddcs++;
cout<<eps<<" -- "<<ddcs<<endl;

}
      
   cout<<"ok"<<endl;
return 0;
}
























