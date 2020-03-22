#include<iostream>
using namespace std;
int main()
{double sh(0),s1(0),s2(0),s3(0);
int i1(0),i2(0),i3(0),n(0);
double *h,x5[5],x3[3],p5[5],f5[5],f3[3],wucha[5];
while(1)
{
cout<<"（逐步插值法）请输入插值节点的间隔"<<endl;
cin>>sh;
n=1/sh+2;         //保证至少有三个节点
h=new double[n];  //动态
cout<<"插值点"<<"        "<<"px"<<"        "<<"fx"<<"        "<<"误差"<<endl;
x5[0]=0.03,x5[1]=0.17,x5[2]=0.65,x5[3]=1.1,x5[4]=1.3;
while(i1<5)
{	f5[i1]=1/(1+25*x5[i1]*x5[i1]);
	i1++;
}
i1=0,h[0]=0;
while(i1<n)
{if ((i1+1)*sh<=1)
  {h[i1+1]=(i1+1)*sh;
  }
 else {s1=i1;break;}
     i1++;
}
i1=0;
while(i1<5)
{if(x5[i1]<=1.5*sh)
	{x3[0]=0,x3[1]=sh,x3[2]=2*sh;}
	else if(x5[i1]>=1-1.5*sh)
	{x3[0]=1-2*sh,x3[1]=1-sh,x3[2]=1;}
	else
	{while(i2<=s1)
	   {if(x5[i1]<=(i2+1)*sh && x5[i1]>=i2*sh)
		 {if (x5[i1]>=(i2+0.5)*sh)
		  {x3[0]=h[i2],x3[1]=h[i2+1],x3[2]=h[i2+2];
		  }
		  else if(x5[i1]<=(i2+0.5)*sh)
		  {x3[0]=h[i2-1],x3[1]=h[i2],x3[2]=h[i2+1];
		  }
		  i2=s1;}i2++;}}i2=0;
	while (i3<3)
	{f3[i3]=1/(1+25*x3[i3]*x3[i3]);
	i3++;}i3=0;
	
	{s2=((x5[i1]-x3[1])/(x3[0]-x3[1]))*f3[0]+((x5[i1]-x3[0])/(x3[1]-x3[0]))*f3[1];
	s3=((x5[i1]-x3[2])/(x3[0]-x3[2]))*f3[0]+((x5[i1]-x3[0])/(x3[2]-x3[0]))*f3[2];
		p5[i1]=s2+((s2-s3)/(x3[1]-x3[2]))*(x5[i1]-x3[1]);
	 f5[i1]=1/(1+25*x5[i1]*x5[i1]);
	 wucha [i1]=f5[i1]-p5[i1];
	 cout<<x5[i1]<<"     "<<p5[i1]<<"     "<<f5[i1]<<"     ";printf("%e",wucha[i1]);cout<<endl;
	} //目前已知x3[3],x5[5],f3[3],sh,i1,在这里输入插值多项式，求p5[5],f5[5],wucha[5]

	i1++;
 }
cout<<endl;}
 delete []h; 
return(0);
}
