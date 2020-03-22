
//半圆响应偏移成像

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
int X,T,i,j,i1,j1;
float fy1,fy2,fy3,v,dt,dx,jd;

cout<<"please save the data as 'txt3.txt' "<<endl;
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
cout<<"please input the jd"<<endl;
cin>>jd;

vector<vector<float> > s(T,vector<float>(X));
vector<vector<float> > r(T,vector<float>(X));
vector<vector<float> > s1(X,vector<float>(X));

     ifstream infile;
     infile.open("txt3.txt");
     if(!infile) cout<<"error"<<endl;
     float t1;
      for(i=0;i<T;i++)
     {for(j=0;j<X;j++)
      {
       if(infile>>t1)           
       {s[i][j]=t1;}
       }
      }
     infile.close();

     ofstream outf;
     outf.open("fy1");
     for(i=0;i<T;i++)
       {for(j=0;j<X;j++)
         {outf.write((char*)&s[i][j],sizeof(s[i][j]));}}
     outf.close();
     cout<<"the data has been saved as 'fy1' "<<endl;

/////////////////半圆响应偏移/////////////////////
for(i=0;i<T;i++)
  {for(j=0;j<X;j++)
     {r[i][j]=(v*dt*i)/dx;}}

for(i=0;i<X;i++)
  {for(j=0;j<X;j++)
     {s1[i][j]=0.0;}}


for(i1=0;i1<T;i1++)
    {cout<<i1<<endl;
     for(j1=0;j1<X;j1++)
     {if(fabs(s[i1][j1])>jd)
       {for(j=0;j<X;j++)
        {if((r[i1][j1]*r[i1][j1]-(j-j1)*(j-j1))>=0)
          {i=int(sqrt((r[i1][j1]*r[i1][j1]-(j-j1)*(j-j1))));
            if(i<X)
            s1[i][j]=s1[i][j]-s[i1][j1];}}}}}

     outf.open("bypy");
for(i=0;i<X;i++)
  {for(j=0;j<X;j++)
     {outf.write((char*)&s1[j][i],sizeof(s1[j][i]));}}
     outf.close();
     cout<<"the data has been saved as 'bypy' "<<endl;

return 0;
}







