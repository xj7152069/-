
//RTM复杂模型
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<cmath>
using namespace std;
float p[400][200];

int main()
{
double s(9.9);
char s1[99]="ww",s2[]="ww",s3[]="ss",s4[4];
sprintf(s4, "%f", s); 
s4[3]='\0';
strcat(s1,s4);
strcat(s1,s3);
cout<<s4[1]<<endl;
while(1)
{ofstream outf;
outf.open("m1");
double pi=3.1415926;
int i,j,k,n,i1,j1;
   
for(i=0;i<400;i++)
  {for(j=0;j<200;j++)
    {   p[i][j]=3000;
        if(i>=0 && i<=50 && j>=120)
            p[i][j]=4000;
        if(i>50 && i<=95 && j>=(-20.0/45.0)*i+100.0+(380.0/9.0))
            p[i][j]=4000;
        if(i>95 && i<=155 && j>=100)
            p[i][j]=4000;
        if(i>155 && i<=185 && j>=(2.0/3.0)*i+100-(310.0/3.0))
            p[i][j]=4000;
        if(i>185 && i<=275 && j>=120.0+20.0*sin((i-185)*(pi/90.0)))
            p[i][j]=4000;
        if(i>275 && i<=305 && j>=120)
			p[i][j]=4000;
		if(i>305 && i<=320 && j>=(-2.0/3.0)*i+120+(610.0/3.0))
			p[i][j]=4000;
		if(i>320 && i<=335 && j>=110)
			p[i][j]=4000;
		if(i>335 && i<=350 && j>=(-2.0/3.0)*i+110+(670.0/3.0))
			p[i][j]=4000;
		if(i>350 && i<400 && j>=100)
			p[i][j]=4000;
        
		if(i>70 && i<160 && j<140 && j>-15*sin((i-70)*(pi/90.0))+140)
            p[i][j]=5000;
		if((i-330)*(i-330)+(j-140)*(j-140)<100)
            p[i][j]=5000;
	

     }
   }
     for(i=0;i<400;i++)
  {for(j=0;j<200;j++)
    { if(j>160)
         p[i][j]=5000;}}


 for(i=0;i<400;i++)
   {for(j=20;j<200;j++)
      {
         outf<<p[i][j]<<" ";
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
