
//最速下降法求解矩阵方程
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;
double f1(double a[],int n)//构造第一个求和函数，简化主函数
{
	double s=0;
	int i;
	for(i=0;i<n;i++)
	{
		s=s+a[i]*a[i];
	}
	return s;
}
double f2(double r[],double a[][1000],int n)//构造第二个求和函数，简化主函数
{
	double b[1000],m=0;
	int i,j;
	for(i=0;i<n;i++)
	{
		double s=0;
		for(j=0;j<n;j++)
		{
			s=s+r[j]*a[j][i];
		}
		b[i]=s;
	}
	for(i=0;i<n;i++)
	{
		m=m+b[i]*r[i];
	}
	return m;
}
double *f3(double a[][1000],double b[],int n)//构造输出列向量的函数
{
	double *r;
	r=new double[n];
	int i,j;
	for(i=0;i<n;i++)
	{
		double s=0;
		for(j=0;j<n;j++)
		{
			s=s+a[i][j]*b[j];
		}
		r[i]=s;
	}
	return r;
}

int main()
{
int n,i,j,k(10),t(0),t1(0);
double h,e,a,b;
e=0.00001;
h=0;
cout<<"please input the size (n)"<<endl;
cin>>n;
while(n>=1000)
{cout<<"the size is too large, please input again(can't over 1000)"<<endl;
cin>>n;}
cout<<"input the fault"<<endl;
cin>>e;
  double A[1000][1000],B[1000],x[1000],r[1000],r1[1000],d[1000];  
for(i=0;i<n;i++)
{for(j=0;j<n;j++)
{if(i>j)
 h=i+1;
if(i<j)
 h=j+1;
if(i==j)
h=n*(i+1);
A[i][j]=h;
}}
h=0;
for(i=0;i<n;i++)
{for(j=0;j<n;j++)
{h=h+A[i][j];
}
B[i]=h;
h=0;
}
for(i=0;i<n;i++)
{for(j=0;j<n;j++)
{cout<<A[i][j]<<" ";
}cout<<endl;}
for(i=0;i<n;i++)
{cout<<B[i]<<" ";}
cout<<endl;
for(i=0;i<n;i++)
{x[i]=0;}
	
	
	double *ax;

	
	ax=f3(A,x,n);
	for(i=0;i<n;i++)
	{
		r[i]=B[i]-ax[i];
		d[i]=r[i];
	}
	if(sqrt(f1(r,n))<=e)
	{
		for(i=0;i<n;i++)
		{
			cout<<x[i]<<'\t';
		}
	}
	else
	{
		for(k=0;k<n;k++)
		{t1++;
			a=f1(r,n)/f2(d,A,n);
			for(i=0;i<n;i++)
			{
				x[i]=x[i]+a*d[i];
			}
			ax=f3(A,x,n);
			for(i=0;i<n;i++)
			{
				r1[i]=B[i]-ax[i];
			}
			if(sqrt(f1(r1,n))<=e||k+1==n)
			{
				for(i=0;i<n;i++)
				{
					cout<<"x["<<i<<"]="<<x[i]<<'\n';
                                        
				}
				break;
			}
			else
			{
				b=f1(r1,n)/f1(r,n);
				for(i=0;i<n;i++)
				{
					d[i]=r1[i]+b*d[i];
					r[i]=r1[i];
				}
			}
		}
	}

cout<<"the times is:"<<t1<<endl;
  
 return 0;
}
