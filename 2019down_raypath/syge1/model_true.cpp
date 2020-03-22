
//输出地下速度模型

#include <iostream>
#include <stdio.h>
#include <fstream>
#include<iomanip>
#include<cmath>
using namespace std;
float p[801][200];
float p1[801][200];
int main()
{
ofstream outf;
double pi=3.1415926;
int i,j,ki,kj,n,i1,j1,N;
ki=1;
i1=0;
j1=0;
kj=1;

for(i=0;i<30;i++)
  {
    if(i1==10)
    {i1=0;ki=ki*(-1);}
    i1++;
    kj=-1;j1=0;
    for(j=0;j<30;j++)
    {  
    if(j1==10)
    {j1=0;kj=kj*(-1);}
      /*if(i>=10 && i<20 && j>=5 && j<15)
      {
      p[i][j]=3000;
      p1[i][j]=3000;}
      else
      {p[i][j]=3000;
      p1[i][j]=3000;} */
      p[i][j]=3500+1000*ki*kj;
      p1[i][j]=p[i][j];

       j1++;
     }
   }

     
    outf.open("model.dat");
  for(i=0;i<30;i++)
    {for(j=0;j<30;j++)
      {
       outf.write((char*)&p1[i][j],sizeof(p1[i][j]));
       }
    }
   outf.close(); ///  

outf.close(); 
cout<<"finished"<<endl;

return (0);
}
