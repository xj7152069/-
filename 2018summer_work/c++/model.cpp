#include <iostream>
#include <stdio.h>
#include <fstream>
#include<iomanip>
#include<cmath>
using namespace std;
float p[1000][1000];
int main()
{while(1)
{ofstream outf;
outf.open("m1.txt");
double pi=3.1415926;
int i,j,k,n,i1,j1;
   
for(j=0;j<400;j++)
  {for(i=0;i<900;i++)
    { if(j<100)
       {p[j][i]=3000;}
       else  if(j>=100 && j<0.1*i+150)
        p[j][i]=3500;
       else  if(j<400 && j>=300-50*sin(pi*i/450.0))
        p[j][i]=4500;
       else 
        p[j][i]=4000;
     }
   }
     
 for(j=0;j<400;j++)
   {for(i=0;i<900;i++)
      {
         outf<<p[j][i]<<" ";
       }
         outf<<endl;
    }

outf.close(); 
cout<<"finished"<<endl;
cin>>n;
if(n!=68768776)
break;
}
return (0);
}
