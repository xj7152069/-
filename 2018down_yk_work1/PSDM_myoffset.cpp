
//我的模型地表共偏移距记录的PSDM

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#include<vector>
 
using namespace std;
int main()
{   
ofstream outf;
ifstream infile;
int X,X1,T,Y,i,j,i1,j1,k,n1,h1;
float fy1,fy2,fy3,v,dt,dx,dy,jd,n,N1,N2,D,h;
char *str1,*str2,*str3;
n1=26;
float wj,jl;
float **s,**s1;

N1=-50;
N2=50;
X=350;
X1=300;
Y=200;
T=1500;
D=10;
v=3000;
dt=0.001;
dx=10;
dy=dx;
jd=0;

    s=new float*[T];    
    for(j=0;j<T;j++)  
    {  
        s[j]=new float[X1];  
    };
    
    s1=new float*[Y];    
    for(j=0;j<Y;j++)  
    {  
        s1[j]=new float[X];  
    };

for(i=0;i<Y;i++)
  {for(j=0;j<X;j++)
     {s1[i][j]=0.0;}}

     infile.open("mycoff",ios::binary);
     if(!infile) cout<<"error"<<endl;



cout<<"begin: "<<endl;
//vector<vector<float> > s(T,vector<float>(X));
//vector<vector<float> > s1(X,vector<float>(X));

for(k=N1;k<N2;k++)
{
cout<<k<<endl;
h=fabs(k)*D*0.5;
h1=k*0.5;

      for(j=0;j<X1;j++)
     {for(i=0;i<T;i++)
      {
      infile.read(( char *)&s[i][j],sizeof(s[i][j]));    
      if(i<300)
       s[i][j]=0.0;  
       }
      }

/////////////////PSDM/////////////////////
    // cout<<"the check has been saved as :"<<endl;
for(i=1;i<Y;i++)
    {//cout<<i1<<endl;
     for(j=25+h1;j<325+h1;j++)
     {
       {for(j1=0;j1<X1;j1++)
         {
          i1=int((1.0/(v*dt))*(sqrt((j1-(j-h))*dx*dx*(j1-(j-h))+i*i*dx*dx)+sqrt((j1-(j+h))*(j1-(j+h))*dx*dx+i*i*dx*dx)));
          if(i1<T)
           {s1[i][j]=s1[i][j]+s[i1][j1];}
         }
       }
     }
   }

}

     outf.open("my");
for(i=0;i<X;i++)
  {for(j=0;j<Y;j++)
     {outf.write((char*)&s1[j][i],sizeof(s1[j][i]));}}
     outf.close();
     cout<<"the data has been saved as: "<<endl;    

     infile.close();
    for(int i=0;i<Y;i++)  
        delete []s1[i];  
    delete []s1;

    for(int i=0;i<T;i++)  
        delete []s[i];  
    delete []s;
return 0;
}







