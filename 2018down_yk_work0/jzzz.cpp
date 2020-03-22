
//矩阵转置，调整数据矩阵的方向，方便程序正确读取数据

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
 

vector<vector<float> > s(T,vector<float>(X));
vector<vector<float> > r(T,vector<float>(X));
vector<vector<float> > s1(X,vector<float>(T));

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

    /* ofstream outf;
     outf.open("fy1");
     for(i=0;i<T;i++)
       {for(j=0;j<X;j++)
         {outf.write((char*)&s[i][j],sizeof(s[i][j]));}}
     outf.close();
     cout<<"the data has been saved as 'fy1' "<<endl;*/



     ofstream outf;
     outf.open("zz");
     for(j=0;j<X;j++)
       {for(i=0;i<T;i++)
         {outf.write((char*)&s[i][j],sizeof(s[i][j]));}}
     outf.close();
     cout<<"the data has been saved as 'zz' "<<endl;



return 0;
}


