
//输出地下速度模型

#include <iostream>
#include <stdio.h>
#include <fstream>
#include<iomanip>
#include<cmath>
using namespace std;
float p[801][200];
int main()
{ofstream outf;
outf.open("srs.txt");
double pi=3.1415926;
int i,j,ki,kj,n,i1,j1;
ki=1;
i1=0;
j1=0;
   
outf<<60<<endl;
 for(i=0;i<30;i++)
   {
         outf<<i*10<<" "<<0<<" "<<30<<endl;
       for(j=0;j<30;j++)
        {outf<<j*10<<" "<<290<<endl;}
    }
 for(i=0;i<30;i++)
   {
         outf<<0<<" "<<i*10<<" "<<20<<endl;
       for(j=0;j<30;j++)
        {outf<<290<<" "<<j*10<<endl;}
    }
    


outf.close(); 
cout<<"finished"<<endl;

return (0);
}
