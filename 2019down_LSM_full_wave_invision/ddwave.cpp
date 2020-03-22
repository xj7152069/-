
//去除直达波
//用变速度模型的结果减去常速模型的直达波记录

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
int X,T,i,j,i1,j1,k,n1,wz_cdp,N1,N2,D;
float fy1,fy2,fy3,v,dt,dx,dy,jd,n;
char *str1,*str2,*str3,*str4;
n1=26;
float wj,jl,N;
float **s,**s1,**s2;

cout<<"please input the N(site)"<<endl;
cin>>N;
cout<<"please input the X"<<endl;
cin>>X;
cout<<"please input the T"<<endl;
cin>>T;

//char str1[]="final_model_common_offset_",str3[]="_km.dat",str2[];

    s=new float*[T];    
    for(j=0;j<T;j++)  
    {  
        s[j]=new float[X];  
    };
    
    s1=new float*[T];    
    for(j=0;j<T;j++)  
    {  
        s1[j]=new float[X];  
    };


    str1=new char[20];  
    str2=new char[10];  
    str3=new char[20];  
    str4=new char[20];

for(i=0;i<T;i++)
  {for(j=0;j<X;j++)
     {s1[i][j]=0.0;}}

strcpy(str1,"suface");
strcpy(str3,"asuface");
strcpy(str4,"nspy_source");
sprintf(str2, "%f", N); 
    if(N<10)
        str2[1]='\0';
    else if(N>=10 && N<100)
        str2[2]='\0';
    else if(N>=100 && N<1000)
        str2[3]='\0';
    else if(N>=1000 && N<10000)
        str2[4]='\0';

strcat(str1,str2);
strcat(str3,str2);
strcat(str4,str2);

     infile.open(str1,ios::binary);
     cout<<str2[1];
     if(!infile) cout<<"error"<<endl;
     else cout<<endl;

      for(j=0;j<X;j++)
     {for(i=0;i<T;i++)
      {
      infile.read(( char *)&s[i][j],sizeof(s[i][j]));           
       }
      }
     infile.close();

     infile.open(str3,ios::binary);
     cout<<str2[2];
     if(!infile) cout<<"error"<<endl;
     else cout<<endl;

      for(j=0;j<X;j++)
     {for(i=0;i<T;i++)
      {
      infile.read(( char *)&s1[i][j],sizeof(s1[i][j])); 
       //s1[i][j]=0.0;          
       }
      }
     infile.close();

for(i=0;i<T;i++)
  {for(j=0;j<X;j++)
     {
       s1[i][j]=s1[i][j]-s[i][j];
      }}

     outf.open(str4);
for(j=0;j<X;j++)
  {for(i=0;i<T;i++)
     {outf.write((char*)&s1[i][j],sizeof(s1[i][j]));}}
     outf.close();
     cout<<"the data has been saved as: cmp"<<endl;   

    delete []str1;
    delete []str2;
    delete []str3;
    delete []str4;
    for(int i=0;i<T;i++)  
        delete []s1[i];  
    delete []s1;

    for(int i=0;i<T;i++)  
        delete []s[i];  
    delete []s;

 

return 0;
}



