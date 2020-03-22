
//速度谱分析

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#include<vector>
 
using namespace std;
float **s,**s1;
int main()
{   
ofstream outf;
ifstream infile;
int offset,T,i,j,k,t,sumv;
float Tor,vmin,vmax,Ti,dt,dx,n;


cout<<"please input the number of offset"<<endl;
cin>>offset;
cout<<"please input the T"<<endl;
cin>>T;
cout<<"please input the vmin"<<endl;
cin>>vmin;
cout<<"please input the vmax"<<endl;
cin>>vmax;
cout<<"please input the dt"<<endl;
cin>>dt;
cout<<"please input the dx(the gap of offset)"<<endl;
cin>>dx;

sumv=int(vmax-vmin);

    s=new float*[T];    
    for(j=0;j<T;j++)  
    {  
        s[j]=new float[offset];  
    };
    
    s1=new float*[T];    
    for(j=0;j<T;j++)  
    {  
        s1[j]=new float[sumv];  
    };


for(i=0;i<T;i++)
  {for(j=0;j<sumv;j++)
     {s1[i][j]=0.0;}}


     infile.open("cmp",ios::binary);
     if(!infile) cout<<"error"<<endl;

      for(j=0;j<offset;j++)
     {for(i=0;i<T;i++)
      {
      infile.read(( char *)&s[i][j],sizeof(s[i][j]));           
       }
      }
     infile.close();


for(i=1;i<T;i++)
  {for(j=1;j<sumv;j++)
    { 
       for(k=0;k<offset;k++)
         {
            Tor=i*dt;
            Ti=sqrt((Tor*Tor+k*dx*k*dx/((j+vmin)*(j+vmin))));
            t=Ti/dt;
            if(t<T)
            {s1[i][j]=s1[i][j]+fabs(s[t][k]);}
         }
       }
    }

     outf.open("v.dat");
for(j=0;j<sumv;j++)
  {for(i=0;i<T;i++)
     {outf.write((char*)&s1[i][j],sizeof(s1[i][j]));}}
     outf.close();
     cout<<"the data has been saved as: v.dat"<<endl;    


    for(int i=0;i<T;i++)  
        delete []s1[i];  
    delete []s1;

    for(int i=0;i<T;i++)  
        delete []s[i];  
    delete []s;

return 0;
}



