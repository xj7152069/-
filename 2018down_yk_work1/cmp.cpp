
//提取CMP道集

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
int X,Y,i,j,i1,j1,k,n1,wz_cdp,N1,N2;
float fy1,fy2,fy3,v,dt,dx,dy,jd,n;
char *str1,*str2,*str3;
n1=26;
float wj,jl;
float **s,**s1;

cout<<"please input the N1(begin with 0)"<<endl;
cin>>N1;
cout<<"please input the N2(won't include N2)"<<endl;
cin>>N2;
cout<<"please input the X"<<endl;
cin>>X;
cout<<"please input the Y"<<endl;
cin>>Y;
cout<<"please input the wz_cdp"<<endl;
cin>>wz_cdp;

vector<vector<float> > r(Y,vector<float>(N2-N1));

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

strcpy(str1,"INMO_");
strcpy(str3,"_km.dat");

wj=k*1.0;
sprintf(str2, "%f", wj); 
str2[4]='\0';
str1[26]='\0';
strcat(str1,str2);
//strcat(str1,str3);

     infile.open(str2,ios::binary);
     cout<<str2[2];
     if(!infile) cout<<"error"<<endl;
     else cout<<endl;

      for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
      infile.read(( char *)&s[i][j],sizeof(s[i][j]));           
       }
      }
     infile.close();

for(i=0;i<Y;i++)
   r[i][k-N1]=s[i][wz_cdp-int((k+1)/2.0)];

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

     outf.open("cmp");
for(j=0;j<N2-N1;j++)
  {for(i=0;i<Y;i++)
     {outf.write((char*)&r[i][j],sizeof(r[i][j]));}}
     outf.close();
     cout<<"the data has been saved as: cmp"<<endl;    

return 0;
}



