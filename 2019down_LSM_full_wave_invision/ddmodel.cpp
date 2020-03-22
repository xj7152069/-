
#include <iostream>
#include <stdio.h>
#include <fstream>
#include<iomanip>
#include<cmath>
using namespace std;
float **model,**zdj;
int main()
{
ofstream outf;
double pi=3.1415926;
int i,j,k,n,i1,j1,X,Y;

cout<<"please input the X"<<endl;
cin>>X;
cout<<"please input the Y"<<endl;
cin>>Y;

    model=new float*[Y];    
    zdj=new float*[Y];  
    for(j=0;j<Y;j++)  
    {  
        model[j]=new float[X];  
        zdj[j]=new float[X]; 
    };

     ifstream infile;
    infile.open("model.dat",ios::binary);
     if(!infile) cout<<"error"<<endl;
      for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
      infile.read(( char *)&model[i][j],sizeof(model[i][j]));  
       }
      }
     infile.close();
     
     infile.open("zdj1",ios::binary);
     if(!infile) cout<<"error"<<endl;
      for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
      infile.read(( char *)&zdj[i][j],sizeof(zdj[i][j]));  
       }
      }
     infile.close();
    
     for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
       if(i>40)
       { model[i][j]=model[i][j]+(zdj[i][j]);}  
        if(model[i][j]<2500)
           { model[i][j]=2500;}
        if(model[i][j]>5500)
           { model[i][j]=5500;}
       }
      }

    outf.open("model.dat");
 for(j=0;j<X;j++)
   {for(i=0;i<Y;i++)
      {
         outf.write((char*)&model[i][j],sizeof(model[i][j]));
       }
    }
outf.close(); 
cout<<"finished"<<endl;

    return 0;
}








