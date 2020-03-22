
//输出地下速度模型

#include <iostream>
#include <stdio.h>
#include <fstream>
#include<iomanip>
#include<cmath>
using namespace std;
float p[801][200],p2[801][200];
int main()
{
ofstream outf;
double pi=3.1415926;
int i,j,k,n,i1,j1;
   
for(i=0;i<801;i++)
  {for(j=0;j<200;j++)
    {  	
       p[i][j]=3000;
        if (j>100+10*sin(2*pi*i/800))
            p[i][j]=3500;
        
        if (j>130+20*sin(2*pi*i/800))
            p[i][j]=4000;
        
        if (j>160)
            p[i][j]=4500;
            
      p2[i][j]= p[i][j];
        
     }
   }


for(k=0;k<99;k++)  
{for(i=1;i<800;i++)
  {for(j=1;j<199;j++)
    {p2[i][j]=0.2*(p[i][j]+p[i-1][j-1]+p[i-1][j+1]+p[i+1][j-1]+p[i+1][j+1]);}}
     for(i=1;i<800;i++)
  {for(j=1;j<199;j++)
    {p[i][j]=p2[i][j];}}
     
     } 
     
    outf.open("model.dat");
 for(i=0;i<801;i++)
   {for(j=0;j<200;j++)
      {
         outf.write((char*)&p2[i][j],sizeof(p2[i][j]));
       }
    }

outf.close(); 
cout<<"finished"<<endl;

return (0);
}
