
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <math.h>
#include "mpi.h"

using namespace std;
float **s1,**s2,**s3,**s4,**sx11,**sx12,**sx13,**sx21,**sx22,**sx23,**sx24,**sx31,**sx32,**sx33,*dr;
float p2[2000][2000];
int main()
{   

//////////defined variable////////////////////
  
    float DX,DY,DT,a1,a2,a3,a4,a5,a6,a7,a8,xf,t,x,z,dx,dy,ddx,ddy,snx1,sny1,snx2,sny2,t2,t5,nw;
    int T,i,j,k,n,n1,i1,j1,t3,t4,N,D,m,X,Y,sumcpu,cpuid;
    float C3;
    ofstream outf8;
    ifstream infile;
    float xs2[5]={1.666667,-0.238095,0.039683,-0.004960,0.000317};
    float xs1[10]={-0.0007926,0.00991800,-0.0595200,0.238080,-0.833333,0.833333,-0.238080,0.0595200,-0.00991800,0.0007926};
    float f,u0(0),u1(0),u2(0),u3(0),u4(0),u5(0),u(0),ux(0),uy(0);
    t=0.001,t2=0,x=0,z=0,xf=200,X=400,Y=200,T=800,DX=10,DY=10,DT=0.001,a1=-9,a2=-9,a3=-9,a4=-9,a5=-9,a6=1,a7=-9,a8=-9;   
        
//////////////////////////////////////////////
          
  int argc;
  char **argv;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&sumcpu);
  MPI_Comm_rank(MPI_COMM_WORLD,&cpuid);
  
//////////input parameter/////////////////////
     
  if(cpuid==0)
  {while(a1!=0)
   {   
     cout<<"please input the separation distance of seismic focus"<<endl;
     cin>>D;
     cout<<"the data will be saved as da"<<endl<<endl;;  
    {
     cout<<"please inpout the range X, but the X can't over 1980"<<endl;
     cin>>X;
     while(X>1980)
    {
     cout<<"the X has over the range, please input again"<<endl;
     cin>>X;
    }
     cout<<"please inpout the range Y, but the Y can't over 1980"<<endl;
     cin>>Y;
     while(Y>1980)
    {
     cout<<"the Y has over the range, please input again"<<endl;
     cin>>Y;
    }
     cout<<"please inpout the T, but the T can't over 10000"<<endl;
     cin>>T;
     while(T>10000)
    {
     cout<<"the T has over the range, please input again"<<endl;
     cin>>T;
    }
     cout<<"please inpout the DX&DY:";
     cin>>DX;
     DY=DX;
     cout<<"please inpout the DT:";
     cin>>DT;
     cout<<"OK"<<endl;
     xf=0.5*(X);
    }
    
    cout<<"you can input 0 to begin now; or input other number to change"<<endl;
    cin>>a1;
    if(a1==0)
    {cout<<"the simulation has begin, please wait a moment"<<endl;}
   }
     
     C3=3.0/2/(30)/DX*log(1000)/(30)/DX/(30)/DX;
     t5=double(Y)/X;
  }
  
 ////////////////////pass parameter/////////////////////    
     
       MPI_Bcast(&C3,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
       MPI_Bcast(&t5,1,MPI_DOUBLE,0,MPI_COMM_WORLD);  
       MPI_Bcast(&X,1,MPI_INT,0,MPI_COMM_WORLD);  
       MPI_Bcast(&Y,1,MPI_INT,0,MPI_COMM_WORLD);  
       MPI_Bcast(&DX,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
       MPI_Bcast(&DY,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
       MPI_Bcast(&DT,1,MPI_FLOAT,0,MPI_COMM_WORLD);  
       MPI_Bcast(&T,1,MPI_INT,0,MPI_COMM_WORLD);  
       MPI_Bcast(&D,1,MPI_INT,0,MPI_COMM_WORLD);  
       MPI_Bcast(&xs2[0],5,MPI_FLOAT,0,MPI_COMM_WORLD);  
       MPI_Bcast(&xs1[0],10,MPI_FLOAT,0,MPI_COMM_WORLD);  
     
 ///////////////defined dynamic array//////////////////////    
   
    dr=new float[T]; 
    
    s1=new float*[Y+20];    
    for(j=0;j<Y+20;j++)  
    {  
        s1[j]=new float[X+20];  
    };
    
    s2=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        s2[j]=new float[X+20];  
    };
    
    s3=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        s3[j]=new float[X+20];  
    };
    
    s4=new float*[T];     
    for(j=0;j<T;j++)  
    {  
        s4[j]=new float[X+20];  
    };
    
    sx11=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx11[j]=new float[X+20];  
    };
    
    sx12=new float*[Y+20];    
    for(j=0;j<Y+20;j++)  
    {  
        sx12[j]=new float[X+20];  
    };
    
    sx13=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx13[j]=new float[X+20];  
    };
    
    sx21=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx21[j]=new float[X+20];  
    };
    
    sx22=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx22[j]=new float[X+20];  
    };
    
    sx23=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx23[j]=new float[X+20];  
    };
    
    sx24=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx24[j]=new float[X+20];  
    };
    
    sx31=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx31[j]=new float[X+20];  
    };
    
     
    sx32=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx32[j]=new float[X+20];  
    };
    
    sx33=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx33[j]=new float[X+20];  
    };
    
     for(j=0;j<Y+20;j++)
      {
        for(i=0;i<X+20;i++)
         {
           s1[j][i]=0.0;s2[j][i]=0.0;s3[j][i]=0.0;
           sx11[j][i]=0.0;sx12[j][i]=0.0;sx13[j][i]=0.0;
           sx21[j][i]=0.0;sx22[j][i]=0.0;sx23[j][i]=0.0;sx24[j][i]=0.0;
           sx31[j][i]=0.0;sx32[j][i]=0.0;sx33[j][i]=0.0;
         }
      }
           
///////////secsmic simulation//////////////////////////
           
       /* input model */
     infile.open("m1.txt");
     if(!infile) cout<<"error"<<endl;
     float t1;
     float*p=&p2[0][0];
     for(j=0;j<Y;j++)
     {for(i=0;i<X;i++)
      {
       if(infile>>t1)           
       {*p=t1;
         p++;}
       }
       for(i1=0;i1<2000-X;i1++)
        p++;
      }
     infile.close();
     cout<<"the input of model has finished"<<endl;
     
       outf8.open("da");
       outf8.seekp(cpuid*sizeof(float)*T,ios::beg);
       N=(X-70)/D+1;
       if(cpuid==0)
       {cout<<"N= "<<N<<endl;}
       for(m=cpuid;m<N;m+=sumcpu) 
        {
         for(i=5;i<X+5;i++)
         {
          for(j=5;j<Y+5;j++)
          { 
           s1[j][i]=0.0;s2[j][i]=0.0;s3[j][i]=0.0;
           sx11[j][i]=0.0;sx12[j][i]=0.0;sx13[j][i]=0.0;
           sx21[j][i]=0.0;sx22[j][i]=0.0;sx23[j][i]=0.0;
           sx31[j][i]=0.0;sx32[j][i]=0.0;sx33[j][i]=0.0;
           sx24[j][i]=0.0;
          }
         }
        for(k=1;k<T;k++)
         { 
          for(j=5;j<Y+5;j++)
           {
            for(i=5;i<X+5;i++)
             {
              for(n=0;n<5;n++)
               {  
                u=u+2*xs2[n];
                u1=u1+xs2[n]*(s2[j-n-1][i]+s2[j+n+1][i]);
                u2=u2+xs2[n]*(s2[j][i-n-1]+s2[j][i+n+1]);
               }
              for(n=0;n<10;n++)
              {
               if(n<5)
               {ux=ux+s2[j][i+n-5]*xs1[n];
                uy=uy+s2[j+n-5][i]*xs1[n];}
               else
               {ux=ux+s2[j][i+n-4]*xs1[n];
                uy=uy+s2[j+n-4][i]*xs1[n];}
              }
           if(j==40 && i==35+m*D)
            {f=(3.1415926)*(3.1415926)*900*(k*DT-0.02)*exp((-3.1415*3.1415*900*(k*DT-0.02)*(DT*k-0.02)))*(3-2*3.1415*3.1415*900*(k*DT-0.02)*(DT*k-0.02));}
           else {f=0;}
           u3=(p2[j-5][i-5]*p2[j-5][i-5]*(DT/DX)*(DT/DX));
           s3[j][i]=(u1+u2-2*u*s2[j][i])*u3+2*s2[j][i]-s1[j][i]+f;
           snx1=0.0;snx2=0.0;
           sny1=0.0;sny2=0.0;
           dx=0;ddx=0;dy=0;ddy=0;
           if(i>=X-26 && j<=t5*i+5*(1-t5) && j>=-t5*i+Y+5+5*t5)	   	
	       snx1=i-(X-26);
           if(i<=34 && j>=t5*i+5*(1-t5) && j<=-t5*i+Y+5+t5*5)		
	       snx2=34-i;
           if(j>=Y-26 && j>t5*i+5*(1-t5) && j>-t5*i+Y+5+5*t5)		
	       sny1=j-(Y-26);
           if(j<=34 && j<t5*i+5*(1-t5) && j<-t5*i+Y+5+5*t5)		
	       sny2=34-j;		
           if(sny1 !=0)
           {dy=p2[j][i]*C3*sny1*sny1*DY*DY;
	        ddy=p2[j][i]*C3*2*sny1*DY;}
           if(sny2 !=0)
           {dy=p2[j][i]*C3*sny2*sny2*DY*DY;
	        ddy=p2[j][i]*C3*2*sny2*DY;}
           if(snx1 !=0)
           {dx=p2[j][i]*C3*snx1*snx1*DX*DX;
	        ddx=p2[j][i]*C3*2*snx1*DX;}
           if(snx2 !=0)
           {dx=p2[j][i]*C3*snx2*snx2*DX*DX;
	        ddx=p2[j][i]*C3*2*snx2*DX;}
           if(i>=0.5*(X+5))
           t3=1;
           else
           t3=-1;
           if(j>=40)
           t4=1;
           else
           t4=-1;
if(snx1!=0 || snx2!=0)
{sx11[j][i]=p2[j][i]*p2[j][i]*DT*DT*(u2-u*s2[j][i])*(1.0/(DX*DX))-dx*dx*DT*DT*sx12[j][i]+(2*sx12[j][i]-sx13[j][i])+DT*(2*dx*(sx13[j][i]-sx12[j][i]));
sx21[j][i]=(-p2[j][i]*p2[j][i]*ddx*(1.0/(DX))*(ux*t3)-dx*dx*dx*sx22[j][i]+3*dx*dx*(sx23[j][i]-sx22[j][i])/DT+3*dx*(2*sx23[j][i]-sx22[j][i]-sx24[j][i])/(DT*DT)+(3*sx22[j][i]-3*sx23[j][i]+sx24[j][i])/(DT*DT*DT))*(DT*DT*DT);
sx31[j][i]=DT*DT*p2[j][i]*p2[j][i]*(1.0/(DX*DX))*(u1-u*s2[j][i])+2*sx32[j][i]-sx33[j][i];}
else    
{sx11[j][i]=p2[j][i]*p2[j][i]*DT*DT*(u1-u*s2[j][i])*(1.0/(DX*DX))-dy*dy*DT*DT*sx12[j][i]+(2*sx12[j][i]-sx13[j][i])+DT*(2*dy*(sx13[j][i]-sx12[j][i]));
sx21[j][i]=(-p2[j][i]*p2[j][i]*ddy*(1.0/(DX))*(uy*t4)-dy*dy*dy*sx22[j][i]+3*dy*dy*(sx23[j][i]-sx22[j][i])/DT+3*dy*(2*sx23[j][i]-sx22[j][i]-sx24[j][i])/(DT*DT)+(3*sx22[j][i]-3*sx23[j][i]+sx24[j][i])/(DT*DT*DT))*(DT*DT*DT);
sx31[j][i]=DT*DT*p2[j][i]*p2[j][i]*(1.0/(DX*DX))*(u2-u*s2[j][i])+2*sx32[j][i]-sx33[j][i];}     
              
        s3[j][i]=sx11[j][i]+sx21[j][i]+sx31[j][i]+f;

        if(i==35+m*D && j==40)
        {s4[k][i]=s3[j][i];}
       
      
         u1=0,u2=0,u3=0,u4=0,u=0,ux=0,uy=0;
        }
       }
          for(j1=0;j1<Y+20;j1++)
         {for(i1=0;i1<X+20;i1++)
         {s1[j1][i1]=s2[j1][i1];s2[j1][i1]=s3[j1][i1];
          sx13[j1][i1]=sx12[j1][i1],sx12[j1][i1]=sx11[j1][i1];
          sx33[j1][i1]=sx32[j1][i1],sx32[j1][i1]=sx31[j1][i1];
          sx24[j1][i1]=sx23[j1][i1],sx23[j1][i1]=sx22[j1][i1],sx22[j1][i1]=sx21[j1][i1];
         }
        } 
      }
       
        for(j1=0;j1<T;j1++)
        outf8.write((char*)&s4[j1][35+m*D],sizeof(s4[j1][35+m*D]));

        if(m<N-sumcpu)
        outf8.seekp((sumcpu-1)*sizeof(float)*T,ios::cur);
  
        cout<<m<<endl;
      }   

      outf8.close(); 
      MPI_Finalize();   
 
///////////////release memory///////////////////////////////  
    
    for(int i=0;i<Y+20;i++)  
        delete []s1[i]; 
    delete []s1;
    
    for(int i=0;i<Y+20;i++)  
        delete []s2[i];
    delete []s2;
    
    for(int i=0;i<Y+20;i++)  
        delete []s3[i]; 
    delete []s3;
    
    for(int i=0;i<T;i++)  
        delete []s4[i]; 
    delete []s4;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx11[i]; 
    delete []sx11;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx12[i]; 
    delete []sx12;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx13[i];  
    delete []sx13;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx21[i];  
    delete []sx21;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx22[i]; 
    delete []sx22;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx23[i]; 
    delete []sx23;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx24[i];  
    delete []sx24;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx31[i];  
    delete []sx31;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx32[i]; 
    delete []sx32;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx33[i]; 
    delete []sx33;
    
///////////////////////////////////////////////////

if(cpuid==0)
cout<<endl<<"finished::"<<"N-"<<N<<"::"<<"T-"<<T<<endl;

return(0);
}
