
//去除直达波
//用变速度模型的结果减去常速模型的直达波记录

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#include<vector>
 float **vmo2,**vmo,**vRMS,**tRMS,wj;
using namespace std;
int main()
{      ofstream outf;
    outf.open("vmo.bin");
ifstream infile;
int Nvt,X,Z,Ncdp,Dcdp,N1cdp,i,j,k,wz;
float DX,DZ,X1cdp,DXcdp,H,ti,vi,hi,numread,vzuo,vyou,xzuo,xyou,vxx,V_fin;
char *str1,*str2,*str3,*str4;
// n1=26;
// float ;


cout<<"please input the Ncdp(number of cdp)"<<endl;
cin>>Ncdp;
cout<<"please input the N1cdp(the begin cdp)"<<endl;
cin>>N1cdp;
cout<<"please input the Dcdp(the gap of cdp)"<<endl;
cin>>Dcdp;
cout<<"please input the X(model lenth)"<<endl;
cin>>X;
cout<<"please input the Z(model depth)"<<endl;
cin>>Z;
cout<<"please input the DX("<<endl;
cin>>DX;
cout<<"please input the DZ("<<endl;
cin>>DZ;
cout<<"please input the DXcdp("<<endl;
cin>>DXcdp;
cout<<"please input the X1cdp("<<endl;
cin>>X1cdp;
cout<<"please input the Nvt(max number of Vrms)"<<endl;
cin>>Nvt;
cout<<"please input the bottom Velocity of model"<<endl;
cin>>V_fin;

    vmo=new float*[Z];    
    for(j=0;j<Z;j++)  
    {  
        vmo[j]=new float[X];  
    };
    vmo2=new float*[Z];    
    for(j=0;j<Z;j++)  
    {  
        vmo2[j]=new float[X];  
    };
    vRMS=new float*[Nvt];    
    for(j=0;j<Nvt;j++)  
    {  
        vRMS[j]=new float[Ncdp];  
    };
    tRMS=new float*[Nvt];    
    for(j=0;j<Nvt;j++)  
    {  
        tRMS[j]=new float[Ncdp];  
    };
    k=0;
    for(i=0;i<Nvt;i++)
        {for(j=0;j<Ncdp;j++)
            {vRMS[i][j]=0;
             tRMS[i][j]=0;}}
    for(i=0;i<Z;i++)
        {for(j=0;j<X;j++)
            {vmo[i][j]=0;}}
cout<<k;
for(k=0;k<Ncdp;k++)
{
    str1=new char[20];  
    str2=new char[10];  
//     str3=new char[20];  
//     str4=new char[20];

// for(i=0;i<X;i++)
//   {for(j=0;j<X;j++)
//      {s1[i][j]=0.0;}}

strcpy(str1,"binmpicks.");
// strcpy(str3,"asurface");
// strcpy(str4,"zdb");

wj=N1cdp+k*Dcdp;
sprintf(str2, "%f",wj); 
if(wj<10)
str2[1]='\0';
if(wj<100 && wj>=10)
str2[2]='\0';
if(wj>=100 && wj<1000)
str2[3]='\0';
if(wj>=1000)
str2[4]='\0';

strcat(str1,str2);
     
     infile.open(str1,ios::binary);
     cout<<str1;
     if(!infile) cout<<"error"<<endl;
     else cout<<endl;
      for(i=0;i<Nvt;i++)
     {for(j=0;j<2;j++)
      {
      if(j==0)
       {infile.read(( char *)&tRMS[i][k],sizeof(tRMS[i][k])); }
      if(j==1)
       {infile.read(( char *)&vRMS[i][k],sizeof(vRMS[i][k]));}
      }
      }
     infile.close();
}

//     for(i=0;i<Nvt;i++)
//         {for(j=0;j<Ncdp;j++)
//             {cout<<tRMS[i][j]<<" ";}}

for(k=0;k<Ncdp;k++)
{
    H=tRMS[0][k]*vRMS[0][k]*0.5;
    for(j=0;j<Z;j++)
        {if(j*DZ<int(H))
           {wz=int(X1cdp+DXcdp*(N1cdp-1+k*Dcdp)*(1/DX));
            if(wz<X)
              vmo[j][wz]=vRMS[0][k];
            else
              cout<<"???";}}

    for(i=1;i<Nvt;i++)
        {if(tRMS[i][k]!=0)
            {ti=0.5*(tRMS[i][k]-tRMS[i-1][k]);
             vi=sqrt((tRMS[i][k]*vRMS[i][k]*vRMS[i][k]-tRMS[i-1][k]*vRMS[i-1][k]*vRMS[i-1][k])/(tRMS[i][k]-tRMS[i-1][k]));
             hi=vi*ti;
    for(j=0;j<Z;j++)
        {if(j*DZ<int(hi+H) && j*DZ>=int(H))
           {wz=int(X1cdp+DXcdp*(N1cdp-1+k*Dcdp)*(1/DX));
            vmo[j][wz]=vi;}}
            }  
             H=int(hi+H);
    for(j=0;j<Z;j++)
        {if(j*DZ>=int(H))
           {wz=int(X1cdp+DXcdp*(N1cdp-1+k*Dcdp)*(1/DX));
            vmo[j][wz]=V_fin;}}
            }



    delete []str1;
    delete []str2;
//     delete []str3;
//     delete []str4;
}

//     for(i=0;i<Z;i++)
//         {for(j=0;j<X;j++)
//             {cout<<vmo[i][j]<<" ";}cout<<endl;}

for(i=0;i<Z;i++)
    {xzuo=0;vzuo=0;
     for(j=0;j<X;j++)
        {if(vmo[i][j]!=0)
            {xyou=j;
             vyou=vmo[i][j];
             if(vzuo==0)
                {for(k=xzuo;k<xyou;k++)
                    {vmo[i][k]=vyou;}
                  xzuo=xyou;vzuo=vyou;}
             else
                {vxx=(vyou-vzuo)/(xyou-xzuo);
                 for(k=xzuo;k<xyou;k++)
                    {vmo[i][k]=vzuo+vxx*(k-xzuo);}
                 xzuo=xyou;vzuo=vyou;
                }
             }
            if(j==X-1)
                {for(k=xzuo;k<X;k++)
                    {vmo[i][k]=vzuo;}
                 }
            }
        }

//     for(j=0;j<1161;j++)
//     {for(i=0;i<Z;i++)
//         {if(i<=40)
//             {vmo2[i][j]=vmo[0][int(j/2)+110];}
//          else
//             {vmo2[i][j]=vmo[i-40][int(j/2)+110];}}}

    for(j=0;j<X;j++)
    {for(i=0;i<Z;i++)
     {outf.write((char*)&vmo[i][j],sizeof(vmo[i][j]));}}
     outf.close();

//    for(int i=0;i<Z;i++)  
//         delete []model[i];//先单独释放第一维中每个数组的内存  
//     delete []model;
//    for(int i=0;i<Nvt;i++)  
//         delete []vRMS[i];//先单独释放第一维中每个数组的内存  
//     delete []vRMS;
//    for(int i=0;i<Nvt;i++)  
//         delete []tRMS[i];//先单独释放第一维中每个数组的内存  
//     delete []tRMS;
//      outf.open(str3);
// for(j=0;j<X;j++)
//   {for(i=0;i<Y;i++)
//      {outf.write((char*)&s[i][j],sizeof(s[i][j]));}}
//      outf.close();
//      cout<<"the data has been saved as: cmp"<<endl;   

//     for(int i=0;i<Y;i++)  
//         delete []s1[i];  
//     delete []s1;

//     for(int i=0;i<Y;i++)  
//         delete []s[i];  
//     delete []s;

return 0;
}



