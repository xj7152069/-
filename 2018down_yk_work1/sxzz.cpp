
//射线层析

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#include<vector>

double sxa(double x1,double x2,double y1,double y2)  //计算直射线斜率
{
double a;
a=(y1-y2)/(x1-x2);
return a;
}

double sxb(double x1,double x2,double y1,double y2,double a)  //计算直射线截距
{
double b;
b=((y1+y2)-a*(x1+x2))/2.0;
return b;
}

//统计直射线在模型任意小方块中的长度
//x1,x2,y1,y2为方块四角坐标，注意：要求有x1<x2;y1<y2;
double cd(double x1,double x2,double y1,double y2,double a,double b)
{
double x01,x02,y01,y02;
double l,s1,s2,s3,s4;
{x01=1;
 x02=1;
 y01=1;
 y02=1;}
s1=a*x1+b-y1;
s2=a*x1+b-y2;
s3=a*x2+b-y1;
s4=a*x2+b-y2;
if(s1*s4<0)
{
   if(s2*s3>0)
    {y01=a*x1+b;
      if(y01<y2)
      {x01=x1;
       y02=y1;
       x02=(y02-b)/a;
      }
      else if(y01>y2)
      {x01=x2;
       y01=a*x01+b;
       y02=y2;
       x02=(y02-b)/a;
      }
    }
   else if(s2*s3<0 && fabs(a)<1.0)
     {
      x01=x1;
      y01=a*x01+b;
      x02=x2;
      y02=a*x02+b;
     }
   else if(s2*s3==0)
    {y01=a*x1+b;
       if(y01==y2)
        {x01=x1;
         if(fabs(a)==1)
          {x02=x2;
           y02=y1;}
         else if(fabs(a)>1)
          {y02=y1;
           x02=(y02-b)/a;}
         else
          {x02=x2;
           y02=a*x02+b;}
         }
        else
         {y02=y1;
          x02=x2;
          if(fabs(a)>1)
           {y01=y2;
            x01=(y01-b)/a;}
          else 
           {x01=x1;
            y01=a*x01+b;}
         } 
     }
}

if(s2*s3<0)
{
  if(s1*s4>0)
   {y01=a*x1+b;
     if(y01>y1)
     {x01=x1;
      y02=y2;
      x02=(y02-b)/a;
      }
      else if(y01<y1)
      {x01=x2;
       y01=a*x01+b;
       y02=y1;
       x02=(y02-b)/a;
      }
    }
   else if(s1*s4<0 && fabs(a)>1.0)
    {
      y01=y1;
      x01=(y01-b)/a;
      y02=y2;
      x02=(y02-b)/a;
    }
   else if(s1*s4==0)
    {y01=a*x1+b;
       if(y01==y1)
        {x01=x1;
          if(a==1)
            {x02=x2;
             y02=y2;}
          else if(fabs(a)>1)
            {y02=y2;
             x02=(y02-b)/a;}
          else
            {x02=x2;
             y02=a*x02+b;}
         }
        else
         { y02=y2;
           x02=x2;
           if(fabs(a)>1)
             {y01=y1;
              x01=(y01-b)/a;}
           else
             {x01=x1;
              y01=a*x01+b;}
         } 
     }
}

l=sqrt((x01-x02)*(x01-x02)+(y01-y02)*(y01-y02));
return l;
}

using namespace std;
int main()
{
     ofstream outf;
     outf.open("sx");
double xx1,xx2,yy1,yy2;
int X,Y,i,j,i1,j1,n,t1;
double x1,x2,y1,y2,l1,l2,a,b,dx,t2,**L,*T,so1,so2;
float **m;

cout<<"please input the X"<<endl;
cin>>X;
cout<<"please input the Y"<<endl;
cin>>Y;
cout<<"please input the dx"<<endl;
cin>>dx;

so2=X;


//l1=cd(0,1,0,1,160,0);
//cout<<l1;


    m=new float*[Y];    
    for(j=0;j<Y;j++)  
    {  
        m[j]=new float[X];  
    };

    L=new double*[X*X+Y*Y];    
    for(j=0;j<X*X+Y*Y;j++)  
    {  
        L[j]=new double[X*Y];  
    };

    T=new double[X*X+Y*Y];    

   for(i1=0;i1<X*X+Y*Y;i1++)
     {for(j1=0;j1<X*Y;j1++)
       {L[i1][j1]=0.0;}}

     ifstream infile;
     infile.open("model",ios::binary);
     if(!infile) cout<<"error"<<endl;
     for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
      infile.read(( char *)&m[i][j],sizeof(m[i][j]));       
       }
      }
     infile.close();

t1=0;
for(j=0;j<X;j++)
{so1=j;
 cout<<so1<<endl;

for(i=0;i<X;i++)
 {
  if(i==so1)
  {t2=0;
   for(i1=0;i1<Y;i1++)
    {L[i+j*X][i1*X+i]+=2.0*dx;
     t2+=L[i+j*X][i1*X+i]/m[i1][i];
     T[i+j*X]=t2;
    }
  }

  else
  {t2=0;
   n=0;
   x1=so1;
   y1=0;
   x2=so1+(i-so1)/2.0;
   y2=Y;
   a=sxa(x1,x2,y1,y2);
   b=sxb(x1,x2,y1,y2,a);
   outf<<a<<" "<<b<<" "<<endl;
   for(i1=0;i1<Y;i1++)
     {for(j1=0;j1<X;j1++)
       {  
         xx1=double(j1);
         xx2=double(j1)+1.0;
         yy1=double(i1);
         yy2=double(i1)+1.0;
         L[i+j*X][n]+=cd(xx1,xx2,yy1,yy2,a,b)*dx;
          //cout<<"check"<<l1<<endl;
         n++;
        }
      }

   n=0;
   x1=x2;
   y1=y2;
   x2=so1+(i-so1);
   y2=0;
   a=sxa(x1,x2,y1,y2);
   b=sxb(x1,x2,y1,y2,a);
   outf<<a<<" "<<b<<" "<<endl;
   for(i1=0;i1<Y;i1++)
     {for(j1=0;j1<X;j1++)
       {  
         xx1=j1;
         xx2=j1+1.0;
         yy1=i1;
         yy2=i1+1.0;
         L[i+j*X][n]+=cd(xx1,xx2,yy1,yy2,a,b)*dx;
         t2=t2+L[i+j*X][n]/m[i1][j1];
         n++;
        }
      }
   T[i+j*X]=t2;
 }
 }
}



for(j=0;j<Y;j++)
{so1=j;
 cout<<so1<<endl;
for(i=0;i<Y;i++)
 {
  if(i==so1)
  {t2=0;
   for(i1=0;i1<X;i1++)
    {L[X*X+i+j*Y][i*X+i1]+=dx;
     t2+=L[X*X+i+j*Y][i*X+i1]/m[i][i1];
    }
        T[X*X+i+j*Y]=t2;
  }

  else
  {t2=0;
   n=0;
   y1=so1;
   x1=0;
   y2=so1+(i-so1);
   x2=X;
   a=sxa(x1,x2,y1,y2);
   b=sxb(x1,x2,y1,y2,a);
   outf<<a<<" "<<b<<" "<<endl;
   for(i1=0;i1<Y;i1++)
     {for(j1=0;j1<X;j1++)
       {  
         xx1=double(j1);
         xx2=double(j1)+1.0;
         yy1=double(i1);
         yy2=double(i1)+1.0;
         L[X*X+i+j*Y][n]+=cd(xx1,xx2,yy1,yy2,a,b)*dx;
         t2=t2+L[X*X+i+j*Y][n]/m[i1][j1];
         n++;
        }
      }
   T[X*X+i+j*Y]=t2;
 }
 }
}

outf.close();

outf.open("v");
   for(i1=0;i1<Y;i1++)
     {for(j1=0;j1<X;j1++)
       {  outf<<m[i1][j1]<<" ";
       }
         outf<<endl;
     }
outf.close();

outf.open("L");
   for(i1=0;i1<X*X+Y*Y;i1++)
     {for(j1=0;j1<X*Y;j1++)
       {  outf<<L[i1][j1]<<" ";
       }
         outf<<endl;
     }
outf.close();

outf.open("T");
     for(i1=0;i1<X*X+Y*Y;i1++)
       {  outf<<T[i1]<<" "<<endl;
       }
outf.close();


    for(int i=0;i<X*X+Y*Y;i++)  
        delete []L[i];  
    delete []L;

    for(int i=0;i<Y;i++)  
        delete []m[i];  
    delete []m;
 
    delete []T;

return 0;
}










