
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
    outf.open("model_stack.bin");
ifstream infile;
int N1,X,Z,N2,Dcdp,N1cdp,i,j,k,wz;
float DX,DZ,X1cdp,DXcdp,H,ti,vi,hi,numread,vzuo,vyou,xzuo,xyou,vxx;
char *str1,*str2,*str3,*str4;
// n1=26;
// float ;

cout<<"please input the X(model lenth)"<<endl;
cin>>X;
cout<<"please input the Z(model depth)"<<endl;
cin>>Z;
cout<<"please input the DX("<<endl;
cin>>DX;
cout<<"please input the DZ("<<endl;
cin>>DZ;
cout<<"please input the N1("<<endl;
cin>>N1;
cout<<"please input the N2("<<endl;
cin>>N2;

    vmo=new float*[Z];    
    for(j=0;j<Z;j++)  
    {  
        vmo[j]=new float[X];  
    };
    vmo2=new float*[Z];    
    for(j=0;j<Z;j++)  
    {  
        vmo2[j]=new float[(N2-N1)*2+1];  
    };

     infile.open("model.bin",ios::binary);
     if(!infile) cout<<"error"<<endl;
     else cout<<endl;
      for(i=0;i<X;i++)
     {for(j=0;j<Z;j++)
      {
       infile.read(( char *)&vmo[j][i],sizeof(vmo[j][i])); 
      }
      }
     infile.close();

    for(k=0;k<Z;k++)
        {for(i=0;i<(N2-N1)*2+1;i++)
            {vmo2[k][i]=vmo[k][N1+int(i/2.0)];}}

    for(j=0;j<(N2-N1)*2+1;j++)
    {for(i=0;i<Z;i++)
     {outf.write((char*)&vmo2[i][j],sizeof(vmo2[i][j]));}}
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



