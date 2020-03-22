
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#include<vector>

//定义矩阵，变量
#define X 30
#define Z 30
#define source_num 60
#define N 900
#define M 1800
#define I1 0.1
#define eps1 0.00000001
#define bs 2

double **a,**p,**a2,**l,**u;
char *str_firstarrival,*str_raypath,*str_id;
double G[M][N]={0.0},T[M][1]={0.0},GT[N][M]={0.0},GTG[N][N]={0.0},G_1[N][M]={0.0},U[N][N]={0.0},UT[N][N]={0.0},AU[N][N]={0.0},K_1[N][N]={0.0},K_1_GT[N][M]={0.0},model[N][1]={0.0},GTd[N][1]={0.0};
float model1[X][Z],model2[X][Z];
using namespace std;

/***雅克比方法对对称矩阵进行特征值分解***/
double **Jacobi_tzz(double **G,int n,int T,double eps)
{
int i,j,k;
int s(0);  //SIZE为矩阵规模
double PI=3.1415926;

    a=new double*[n]; //动态数组
    p=new double*[n]; 
    for(j=0;j<n;j++)  
    {  
        a[j]=new double[n];
        p[j]=new double[n];  
    };
    
    a2=new double*[n+1]; //动态数组  
    for(j=0;j<n+1;j++)  
    {  
        a2[j]=new double[n]; 
    };
    
    for(i=0;i<n;i++)
    {for(j=0;j<n;j++)
     {a[i][j]=*((double *)G+n*i+j);}  //将指针空间G的值的值赋给a
    }

/********计算部分*********/
double max=a[0][1];
int row=0;
int col=0;
double Ptemp[3][3];
int ite_num=0;
for (i=0;i<n;i++)
p[i][i]=1;
while (1)
{
if((ite_num%1000)==0)
{printf("m.nd : %5.5d\n", ite_num);} 
max=fabs(a[0][1]);
row=0;
col=1;
for(i=0;i<n;i++)
for(j=0;j<n;j++)
if (i!=j&&fabs(a[i][j])>max)
{
max=fabs(a[i][j]);
row=i;
col=j;
}
if(max<eps || ite_num>T)
{
s=7;
break;
}

double theta;
if(a[row][row]==a[col][col])
theta=PI/4;
else
theta=0.5*atan(2*a[row][col]/(a[row][row]-a[col][col]));
double aii=a[row][row];
double ajj=a[col][col];
double aij=a[row][col];
double sin_theta=sin(theta);
double cos_theta=cos(theta);
double sin_2theta=sin(2*theta);
double cos_2theta=cos(2*theta);
a[row][row]=aii*cos_theta*cos_theta+ajj*sin_theta*sin_theta+aij*sin_2theta;
a[col][col]=aii*sin_theta*sin_theta+ajj*cos_theta*cos_theta-aij*sin_2theta;
a[row][col]=0.5*(ajj-aii)*sin_2theta+aij*cos_2theta;
a[col][row]=a[row][col];
for(k=0;k<n;k++)
{
if(k!=row && k!=col)
{
double arowk=a[row][k];
double acolk=a[col][k];
a[row][k]=arowk*cos_theta+acolk*sin_theta;
a[k][row]=a[row][k];
a[col][k]=acolk*cos_theta-arowk*sin_theta;
a[k][col]=a[col][k];
}
}
if(ite_num==0)
{
p[row][row]=cos_theta;
p[row][col]=-sin_theta;
p[col][row]=sin_theta;
p[col][col]=cos_theta;
}
else
{
for(k=0;k<n;k++)
{
double pki=p[k][row];
double pkj=p[k][col];
p[k][row]=pki*cos_theta+pkj*sin_theta;
p[k][col]=pkj*cos_theta-pki*sin_theta;
}
}
ite_num++;

}    

/********输出部分*******/
if(s==7)
{
for(int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
if (i==j)  
{a2[n][j]=a[i][j];}      
}

for (int i = 0; i < n; i++)
{
for (int j=0;j<n;j++)
{a2[i][j]=p[i][j];}
}
}

    double **tzz =(double **)malloc((n+1)*sizeof(double *));//先申请n+1个指针型字节的空间
    for (i=0;i<n+1;i++)
        tzz[i]=(double *)malloc(n*sizeof(double)); //然后依次按一维申请

    for(i=0;i<n+1;i++)
      for(j=0;j<n;j++)
      {*((double *)tzz+n*i+j)=a2[i][j];} //
return tzz;
}
/////////////////////

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

int main()
{
     double x1,x2,y1,y2,sx_a,sx_b,Lx1,Lx2,Ly1,Ly2,I,eps;
     double raypath[9999][3]={-1.0};
     ifstream infile;
     ofstream outf;
     double num_of_raypath;
     char str_of_raypath[2];
     int G1(-1),G2,G3(-1),i1,j1,i,j,k,dx(10),dz(10);
     int ddcs;
     ddcs=int(N*N*bs);
     I=I1;
     eps=eps1;
    double source_id,wavephone_id;
    str_firstarrival=new char[99];  
    str_raypath=new char[99];  
    str_id=new char[9];  
  //cout<<"input I:";cin>>I;
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
        }
        
     if(raypath[k+1][0]==0.0)
     {
       Lx1=raypath[k][1];
       Lx2=raypath[k+1][1];
       Ly1=raypath[k][2];
       Ly2=raypath[k+1][2];
       
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
        T[G3][0]=num_of_raypath;
       }
      else if(j>=3 && (j%3)==1)      
       {
        infile>>num_of_raypath;
       }
      j++;
     }
     infile.close();
     
   }      
        //生成矩阵G的转置GT
    for(i=0;i<M;i++)
    {for(j=0;j<N;j++)
      {
       GT[j][i]=G[i][j];
      }
    }
    
    //(GT)*G+I
    for(i=0;i<N;i++)
      {for(j=0;j<N;j++)
        {if(i==j)
         {GTG[i][j]=GTG[i][j]+I;
         if((i%100)==0)
          cout<<i<<endl;}
         for(k=0;k<M;k++)
            {
             GTG[i][j]=GTG[i][j]+GT[i][k]*G[k][j];
            }
        }
      }

//////////////此处尝试用Jacobi特征值分解求解，迭代次数较大////////      
     
     double **G_zz =(double **)malloc((N)*sizeof(double *));
    for (i=0;i<N;i++)
        G_zz[i]=(double *)malloc(N*sizeof(double)); //然后依次按一维申请

    for(i=0;i<N;i++)
      for(j=0;j<N;j++)
      {*((double *)G_zz+N*i+j)=GTG[i][j];} //

   //(GT)*G+I的特征值分解
    double **G_1_zz=Jacobi_tzz((double **)G_zz,N,ddcs,eps);
    
    //得到U,AU,UT
    for(i=0;i<N;i++)
      for(j=0;j<N;j++)
      {U[i][j]=*((double *)G_1_zz+N*i+j);
       if(i==j)
       {AU[i][j]=1.0/(*((double *)G_1_zz+N*N+j));
       //cout<<(*((double *)G_1_zz+N*N+j))<<" ";
       }
      } 
    
    for(i=0;i<N;i++)
      for(j=0;j<N;j++)
      {UT[i][j]=U[j][i];}
      
      
    //k_1=U*(AU_1)*UT  
     for(i=0;i<N;i++)
      {for(j=0;j<N;j++)
        {if(i==j && (i%100)==0)
          {cout<<i<<endl;}
         for(k=0;k<N;k++)
            {
             K_1[i][j]=K_1[i][j]+U[i][k]*(AU[k][j]);
            }
        }
      }//cout<<endl;
      
     for(i=0;i<N;i++)
      {for(j=0;j<N;j++)
        {U[i][j]=K_1[i][j];K_1[i][j]=0.0;}}
      
     for(i=0;i<N;i++)
      {for(j=0;j<N;j++)
        {if(i==j && (i%100)==0)
          {cout<<i<<endl;}
         for(k=0;k<N;k++)
            {
             K_1[i][j]=K_1[i][j]+U[i][k]*UT[k][j];
            }
        }
      }//cout<<endl;
      
      //m=(K_1)*(GT)*d
     for(i=0;i<N;i++)
      {for(j=0;j<M;j++)
        {if(i==j && (i%100)==0)
          {cout<<i<<endl;}
         for(k=0;k<N;k++)
            {
             K_1_GT[i][j]=K_1_GT[i][j]+K_1[i][k]*GT[k][j];
            }
        }
      }//cout<<endl;
    
      for(i=0;i<N;i++)
        {
         for(k=0;k<M;k++)
            {
             model[i][0]=model[i][0]+K_1_GT[i][k]*(T[k][0]);
            }
        }
//////////////////////////////////////////
  for(i=0;i<X;i++)
   {for(j=0;j<Z;j++)
    {   model1[i][j]=1.0/(model[X*(j)+i][0]);
       if(model1[i][j]<1000)
       model1[i][j]=1000;
       if(model1[i][j]>6000)
       model1[i][j]=6000;
       model2[i][j]=model1[i][j];
    }
   }
     
 for(k=1;k<1;k++)
  {for(i=1;i<X-1;i++)
   {for(j=1;j<Z-1;j++)
      {model2[i][j]=0.2*(model1[i][j]+model1[i-1][j-1]+model1[i+1][j+1]+model1[i+1][j-1]+model1[i-1][j+1]);
      }
   }
  for(i=0;i<X;i++)
   {for(j=0;j<Z;j++)
      {
         model1[i][j]=model2[i][j];
       }
    }
  }

  outf.open("model.dat");
  for(i=0;i<X;i++)
    {for(j=0;j<Z;j++)
      {
         outf.write((char*)&model2[i][j],sizeof(model2[i][j]));
       }
    }
   outf.close(); ///
    /**/
  outf.open("zG.txt");
  for(i=0;i<M;i++)
    {for(j=0;j<N;j++)
      {
         outf<<G[i][j]<<" ";
       }
         outf<<endl;
    }
   outf.close();  
   
   k=0;
   outf.open("zT.txt");
    for(i=0;i<M;i++)
      {k++;
         outf<<(T[i][0])<<endl;
         
       }
   outf.close();  
   
   cout<<"ok"<<endl;
return 0;
}
























