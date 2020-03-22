
//绕射扫描偏移成像

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


vector<vector<float> > s(T,vector<float>(X));
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

/////////////////绕射扫描偏移/////////////////////

for(i=0;i<X;i++)
  {for(j=0;j<X;j++)
     {s1[i][j]=0.0;}}

for(i=0;i<X;i++)
  {cout<<i<<endl;
   for(j=0;j<X;j++)
     {for(j1=0;j1<X;j1++)
        {i1=int(sqrt((i*i*dx*dx+(j-j1)*(j-j1)*dx*dx))/(v*dt));  
         if(i1<T)
         s1[i][j]=s1[i][j]-(s[i1][j1]);}}}

     outf.open("rspy");
for(i=0;i<X;i++)
  {for(j=0;j<X;j++)
     {outf.write((char*)&s1[j][i],sizeof(s1[j][i]));}}
     outf.close();
     cout<<"the data has been saved as 'rspy' "<<endl;

return 0;
}







