
//半椭圆叠前偏移

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
int X,T,i,j,i1,j1,k,n1;
float fy1,fy2,fy3,v,dt,dx,dy,jd,n,N1,N2;
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
cout<<"please input the T"<<endl;
cin>>T;

cout<<"please input the v"<<endl;
cin>>v;
cout<<"please input the dt"<<endl;
cin>>dt;
cout<<"please input the dx&dy"<<endl;
cin>>dx;
dy=dx;
cout<<"please input the jd"<<endl;
cin>>jd;

cout<<"begin: "<<endl;
//vector<vector<float> > s(T,vector<float>(X));
//vector<vector<float> > s1(X,vector<float>(X));

for(k=N1;k<N2;k++)
{
//char str1[]="final_model_common_offset_",str3[]="_km.dat",str2[];

    s=new float*[T];    
    for(j=0;j<T;j++)  
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

strcpy(str1,"final_model_common_offset_");
strcpy(str3,"_km.dat");

wj=k*0.1;
sprintf(str2, "%f", wj); 
str2[3]='\0';
str1[26]='\0';
strcat(str1,str2);
strcat(str1,str3);


     infile.open(str1,ios::binary);
     cout<<str2[2];
     if(!infile) cout<<"error"<<endl;
     else cout<<endl;

      for(j=0;j<X;j++)
     {for(i=0;i<T;i++)
      {
      infile.read(( char *)&s[i][j],sizeof(s[i][j]));           
       }
      }
     infile.close();

    if(k==2)
    {
     outf.open(str3);
     for(j=0;j<X;j++)
       {for(i=0;i<T;i++)
         {outf.write((char*)&s[i][j],sizeof(s[i][j]));}}
     outf.close();
     cout<<"the check has been saved as :"<<str2[2]<<endl;}

/////////////////PSDM/////////////////////
    // cout<<"the check has been saved as :"<<endl;
for(i1=1;i1<T;i1++)
    {//cout<<i1<<endl;
     for(j1=0;j1<X;j1++)
     {if(fabs(s[i1][j1])>jd)
      {//cout<<i1<<","<<j1<<endl;
       {for(j=0;j<X;j++)
         {
          jl=(1-(dx*dx*(j-j1)*(j-j1))/(v*v*dt*dt*i1*i1*0.5*0.5))*((v*v*dt*dt*i1*i1*0.5*0.5)-k*k*100*100*0.5*0.5);
          if(jl>=0)
           {i=int(sqrt(jl)/dx);}
          if(i<X)
           {s1[i][j]=s1[i][j]+s[i1][j1];}
         }
       }
     }
   }
 }

     outf.open(str2);
for(i=0;i<X;i++)
  {for(j=0;j<X;j++)
     {outf.write((char*)&s1[j][i],sizeof(s1[j][i]));}}
     outf.close();
     cout<<"the data has been saved as: "<<str2[2]<<endl;    

    delete []str1;
    delete []str2;
    delete []str3;

    for(int i=0;i<X;i++)  
        delete []s1[i];  
    delete []s1;

    for(int i=0;i<T;i++)  
        delete []s[i];  
    delete []s;

}

return 0;
}







