
//半圆响应偏移成像

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#include<vector>
 
using namespace std;
int main()
{   
ofstream outf;
ifstream infilez;
ifstream infilef;
ifstream infile;

int D,T,T1,X,Y,i,j,i1,j1,k,n1,wz_cdp,k3,k4,N1,N2;
float fy1,fy2,fy3,v,dt,dx,dy,jd,n;
char *str1,*str2,*str3,*str4,*str5;


float jl;
float **s,**s1,**dj,**la;

cout<<"please input the beginning site (N1)"<<endl;
cin>>N1;
cout<<"please input the number of movie(N2)"<<endl;
cin>>N2;
cout<<"please input the gap(D)"<<endl;
cin>>D;
cout<<"please input the X"<<endl;
cin>>X;
cout<<"please input the Y"<<endl;
cin>>Y;
cout<<"please input the T"<<endl;
cin>>T;



cout<<"begin"<<endl;

    dj=new float*[Y];    
    for(j=0;j<Y;j++)  
    {  
        dj[j]=new float[X];  
    };

    la=new float*[Y];    
    for(j=0;j<Y;j++)  
    {  
       la[j]=new float[X];  
    };

for(i=0;i<Y;i++)
  {for(j=0;j<X;j++)
    {dj[i][j]=0.0;
     la[i][j]=0.0;}}

     char *str11,*str12,*str13;
     double wj;
     int k2;

 /*infile.open("zdj",ios::binary);
     if(!infile) cout<<"error"<<endl;
      for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
      infile.read(( char *)&dj[i][j],sizeof(dj[i][j]));           
       }
      }
 infile.close();*/

for(k2=0;k2<N2;k2++)
{

cout<<endl;

    str11=new char[20];
    str12=new char[5];
    str13=new char[20];

wj=(N1+D*k2)*1.0;
sprintf(str12, "%f", wj); 
str12[4]='\0';
strcpy(str11,"movie");
strcat(str11,str12);
strcpy(str13,"nsmovie");
strcat(str13,str12);
cout<<wj<<"_";
////////////////////正演视频处理///////////////

 infilez.open(str11,ios::binary);
     if(!infilez) cout<<"error"<<endl;
for(k=0;k<T;k++)
{
//char str1[]="final_model_common_offset_",str3[]="_km.dat",str2[];

    s=new float*[Y];    
    for(j=0;j<Y;j++)  
    {  
        s[j]=new float[X];  
    };
    s1=new float*[Y];    
    for(j=0;j<Y;j++)  
    {  
        s1[j]=new float[X];  
    };

    


      for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
          infilez.read(( char *)&s[i][j],sizeof(s[i][j]));       
       }
      }

k4=T-k-1;
 infilef.open(str13,ios::binary);
     if(!infilef) cout<<"error"<<endl;
 infilef.seekg(sizeof(jl)*X*Y*(k4),ios::cur);

      for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
      infilef.read(( char *)&s1[i][j],sizeof(s1[i][j]));           
       }
      }
 infilef.close();


      for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
      s[i][j]=s[i][j]*s1[i][j];     
      dj[i][j]=dj[i][j]+s[i][j];      
       }
      }

    for( i=0;i<Y;i++)  
        delete []s1[i];  
    delete []s1;

    for( i=0;i<Y;i++)  
        delete []s[i];  
    delete []s;

}
     infilez.close();
    delete []str11;
    delete []str12;
    delete []str13;
}
/////////////////////////////////////////////////////

/*叠加并作Laplace变换*/
 outf.open("zdj1");
for(j=0;j<X;j++)
  {for(i=0;i<Y;i++)
     {outf.write((char*)&dj[i][j],sizeof(dj[i][j]));}}
     outf.close();
     cout<<"the data has been saved as: zdj"<<endl; 

      for(j=1;j<X-1;j++)
     {for(i=1;i<Y-1;i++)
      {
      la[i][j]=(dj[i-1][j-1]-dj[i][j]+dj[i-1][j+1]-dj[i][j]+dj[i+1][j-1]-dj[i][j]+dj[i+1][j+1]-dj[i][j]);  
       }
      }
      for(j=1;j<X-1;j++)
     {for(i=1;i<Y-1;i++)
      {dj[i][j]=la[i][j];}}

 outf.open("zdj_la1");
for(j=0;j<X;j++)
  {for(i=0;i<Y;i++)
     {outf.write((char*)&dj[i][j],sizeof(dj[i][j]));}}
     outf.close();
     cout<<"the data has been saved as: zdj_la"<<endl; 

    for( i=0;i<Y;i++)  
        delete []dj[i];  
    delete []dj;

///////////////////////////////////////////////////////

return 0;
}



