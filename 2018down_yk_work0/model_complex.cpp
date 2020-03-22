
//输出地下速度模型

#include <iostream>
#include <stdio.h>
#include <fstream>
#include<iomanip>
#include<cmath>
using namespace std;
float p[900][200];
int main()
{while(1)
{ofstream outf;
outf.open("complex.txt");
double pi=3.1415926;
int i,j,k,n,i1,j1;
   
for(i=0;i<900;i++)
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
		if(i>350 && i<=380 && j>=100)
			p[i][j]=4000;
		if(i>380 && i<=425 && j>=120)
			p[i][j]=4000;
		if(i>425 && i<=605 && j>=-20.0*sin((i-425)*(pi/90.0))+120)
			p[i][j]=4000;
		if(i>605 && i<=635 && j>=120)
			p[i][j]=4000;
		if(i>635 && i<=695 && j>=(-1.0/3.0)*i+100+(695.0/3.0))
			p[i][j]=4000;
		if(i>695 && i<=725 && j>=(-1.0/3.0)*i+100+(725.0/3.0))
			p[i][j]=4000;
		if(i>725 && i<=755 && j>=(-1.0/3.0)*i+100+(755.0/3.0))
			p[i][j]=4000;
		if(i>755 && i<=815 && j>=(1.0/3.0)*i+100-(755.0/3.0))
			p[i][j]=4000;
		if(i>815 && i<=900 && j>=120)
			p[i][j]=4000;
        
		if(i>70 && i<160 && j<120 && j>-15*sin((i-70)*(pi/90.0))+120)
            p[i][j]=3500;
		if((i-400)*(i-400)+(j-160)*(j-160)<400)
            p[i][j]=4500;
		if(i>650 && i<750 && j<160 && j>145)
            p[i][j]=3500;		

     }
   }
     



 for(j=0;j<200;j++)
   {for(i=0;i<900;i++)
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
