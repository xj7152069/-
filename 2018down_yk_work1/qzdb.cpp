
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
int X,Y,i,j,i1,j1,k,n1,wz_cdp,N1,N2,D,N;
float fy1,fy2,fy3,v,dt,dx,dy,jd,n;
char *str1,*str2,*str3,*str4;
n1=26;
float wj,jl;
float **s,**s1,**s2;

cout<<"please input the N(begin site)"<<endl;
cin>>N;

cout<<"please input the N1(time)"<<endl;
cin>>N1;
cout<<"please input the N2(number)"<<endl;
cin>>N2;
cout<<"please input the X"<<endl;
cin>>X;
cout<<"please input the Y"<<endl;
cin>>Y;
cout<<"please input the D"<<endl;
cin>>D;
cout<<"please input the v"<<endl;
cin>>v;
cout<<"please input the dt"<<endl;
cin>>dt;
cout<<"please input the dx"<<endl;
cin>>dx;



for(k=0;k<N2;k++)
{
//char str1[]="final_model_common_offset_",str3[]="_km.dat",str2[];

    s=new float*[Y];    
    for(j=0;j<Y;j++)  
    {  
        s[j]=new float[X];  
    };
    
    s1=new float*[Y];    
    for(j=0;j<Y;j++)  
    {  
        s1[j]=new float[X];  
    };


    str1=new char[20];  
    str2=new char[10];  
    str3=new char[20];  
    str4=new char[20];

for(i=0;i<X;i++)
  {for(j=0;j<X;j++)
     {s1[i][j]=0.0;}}

strcpy(str1,"surface");
strcpy(str3,"asurface");
strcpy(str4,"zdb");

wj=N+k*D;
sprintf(str2, "%f", wj); 
str2[4]='\0';

strcat(str1,str2);
strcat(str3,str2);
strcat(str4,str2);

     infile.open(str1,ios::binary);
     cout<<str2[2];
     if(!infile) cout<<"error"<<endl;
     else cout<<endl;

      for(i=0;i<Y;i++)
     {for(j=0;j<X;j++)
      {
      infile.read(( char *)&s[i][j],sizeof(s[i][j]));           
       }
      }
     infile.close();

     infile.open(str4,ios::binary);
     cout<<str2[2];
     if(!infile) cout<<"error"<<endl;
     else cout<<endl;

      for(i=0;i<Y;i++)
     {for(j=0;j<X;j++)
      {
      infile.read(( char *)&s1[i][j],sizeof(s1[i][j])); 
       //s1[i][j]=0.0;          
       }
      }
     infile.close();

for(i=0;i<Y;i++)
  {for(j=0;j<X;j++)
     {
       s[i][j]=s[i][j]-s1[i][j];
      }}

     outf.open(str3);
for(j=0;j<X;j++)
  {for(i=0;i<Y;i++)
     {outf.write((char*)&s[i][j],sizeof(s[i][j]));}}
     outf.close();
     cout<<"the data has been saved as: cmp"<<endl;   

    delete []str1;
    delete []str2;
    delete []str3;
    delete []str4;
    for(int i=0;i<Y;i++)  
        delete []s1[i];  
    delete []s1;

    for(int i=0;i<Y;i++)  
        delete []s[i];  
    delete []s;

}

 

return 0;
}



