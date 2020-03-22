
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "su.h"
#include "segy.h"
#include "alloc.h"
#include "author.h"
/**计算区域参数设置**/
#define nx 501
#define nz 501
#define nt 1000
#define dx 10.0
#define dz 10.0
#define dt 0.001
/**震源子波参数设置(Richer wavelet)**/
#define A 1.0
#define f0 30
#define t0 20
#define pi 3.14159
using namespace std;

/**获取对应波数函数**/
float getK(int i,int nfft,float d)
{
	float deltak;
	deltak=2.0*pi/(nfft*d);
	if(i<=nfft/2)
		return i*deltak;
	else
		return (i-nfft)*deltak;
}

/**震源子波函数f(t)(Richer wavelet)**/
float F(int t)
{
	return A*exp(-pow(pi*f0*(t-t0)*dt,2.0))*(1-2*pow(pi*f0*(t-t0)*dt,2.0));
}

/**主函数**/
int main()
{
	int i,j,t;
	int nxfft,nzfft;
	float kx,kz;
	float P1[nx][nz]={0.0},P2[nx][nz]={0.0},P3[nx][nz]={0.0};
	float v[nx][nz]={0.0},o[nx][nz]={0.0},f[nt];
	register complex **ct;	// complex FFT workspace
	FILE *fp1,*fp2;
	fp1=fopen("movie_modeling.dat","wb");
	fp2=fopen("image_modeling.dat","wb");
	nxfft=npfa(nx);
	nzfft=npfa(nz);
	ct=alloc2complex(nxfft,nzfft);
        /**震源位置**/
        o[(nx-1)/2][(nz-1)/2]=1.0;
	/**速度模型**/
        for(i=0;i<nx;i++)
		for(j=0;j<nz;j++)
                	v[i][j]=3000.0;
	/**时间片的计算与推进**/
	for(t=0;t<nt;t++)
	{
       		f[t]=F(t);
		memset( (void *) ct[0], 0, sizeof(complex)*nxfft*nzfft);
		for(i=0;i<nx;i++)
			for(j=0;j<nz;j++)
				ct[i][j].r=P2[i][j];
		//正变换
		pfa2cc(-1,1,nxfft,nzfft,ct[0]);
		pfa2cc(-1,2,nxfft,nzfft,ct[0]);
		for(i=0;i<nxfft;i++)
			for(j=0;j<nzfft;j++)
			{	    
				kx=getK(i,nxfft,dx);
				kz=getK(j,nzfft,dz);
				ct[i][j]=-(kx*kx+kz*kz)*ct[i][j];
			}
		//反变换
		pfa2cc(1,1,nxfft,nzfft,ct[0]);
		pfa2cc(1,2,nxfft,nzfft,ct[0]);
		for(i=0;i<nxfft;i++)
		    	for(j=0;j<nzfft;j++)
				ct[i][j]=ct[i][j]/nxfft/nzfft;
		for(i=0;i<nx;i++)
			for(j=0;j<nz;j++)
			{	
				P3[i][j]=ct[i][j].r*pow(v[i][j]*dt,2.0)+f[t]*o[i][j]+2*P2[i][j]-P1[i][j];
				fwrite(&P3[i][j],sizeof(float),1,fp1);
				if(t==500)
					fwrite(&P3[i][j],sizeof(float),1,fp2);
			}	
		//时间片前进
		for(i=0;i<nx;i++)
			for(j=0;j<nz;j++)
			{
				P1[i][j]=P2[i][j];
				P2[i][j]=P3[i][j];
			}
	}
	fclose(fp1);
	fclose(fp2);
	free2complex(ct);
        return 0;
}
