
//从我的地变正演记录中提取共偏移距道集

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
int X,Y,i,j,i1,j1,k,n1,wz_cdp,N1,N2,k1,N;
float fy1,fy2,fy3,v,dt,dx,dy,jd,n;
char *str1,*str2,*str3,*str4,*str5;
n1=26;
float wj,jl;
float **s,**s1;

cout<<"please input the N(the gap of offset is 5m)"<<endl;
cin>>N;
cout<<"please input the N1(begin with 0)"<<endl;
cin>>N1;
cout<<"please input the N2(won't include N2)"<<endl;
cin>>N2;
cout<<"please input the X"<<endl;
cin>>X;
cout<<"please input the Y"<<endl;
cin>>Y;


vector<vector<float> > r(Y,vector<float>(N2-N1-1));

for(k1=0;k1<=50;k1++)
{
    str5=new char[6];  
    str4=new char[99];  
strcpy(str4,"mydata_offset_km_");
for(k=N1;k<N2;k++)
{
//char str1[]="final_model_common_offset_",str3[]="_km.dat",str2[];

    s=new float*[Y];    
    for(j=0;j<Y;j++)  
    {  
        s[j]=new float[X];  
    };
    
    s1=new float*[X];    
    for(j=0;j<X;j++)  
    {  
        s1[j]=new float[X];  
    };

    str1=new char[99];  
    str2=new char[5];  
    str3=new char[20];  

for(i=0;i<X;i++)
  {for(j=0;j<X;j++)
     {s1[i][j]=0.0;}}

wj=k;
sprintf(str2, "%f", wj); 

if(k<10)
{strcpy(str1,"shot_cnooc_fault_000");
str2[1]='\0';}
else if(k>=10 && k<100)
{strcpy(str1,"shot_cnooc_fault_00");
str2[2]='\0';}
else if(k>=100 && k<999)
{strcpy(str1,"shot_cnooc_fault_0");
str2[3]='\0';}

strcpy(str3,".dat");

//wj=k*0.1;
//sprintf(str2, "%f", wj); 
//str2[3]='\0';
//str1[26]='\0';
strcat(str1,str2);
strcat(str1,str3);

     infile.open(str1,ios::binary);
     if(!infile) cout<<"error"<<endl;

      for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
      infile.read(( char *)&s[i][j],sizeof(s[i][j]));           
       }
      }
     infile.close();

for(i=0;i<Y;i++)
   r[i][k]=s[i][k1+51];

    delete []str1;
    delete []str2;
    delete []str3;

    for(int i=0;i<X;i++)  
        delete []s1[i];  
    delete []s1;

    for(int i=0;i<Y;i++)  
        delete []s[i];  
    delete []s;

}

jl=k1*0.005;
sprintf(str5, "%f", jl); 
str5[5]='\0';
strcat(str4,str5);

     outf.open(str4);
for(j=0;j<N2-N1-1;j++)
  {for(i=0;i<Y;i++)
     {outf.write((char*)&r[i][j],sizeof(r[i][j]));}}
     outf.close();
     cout<<"the data has been saved as:"<<k1<<endl;   
    delete []str4;
    delete []str5; 
}
return 0;
}



