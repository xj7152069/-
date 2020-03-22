
//动态定义二维数组，并用函数调用范例

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
using namespace std;

float **p3;  //
float **sy(float **a,int n1,int n2)
{   

    int i,j;
    p3=new float*[n1]; //动态数组p3   
    for(j=0;j<n1;j++)  
    {  
        p3[j]=new float[n2];  
    };
    for(i=0;i<n1;i++)
    {for(j=0;j<n2;j++)
     {p3[i][j]=*((float *)a+n2*i+j);}  //将指针空间a的值的值赋给p3
    }
    
    float **p2 =(float **)malloc(n1*sizeof(float *));//先申请n1个指针型字节的空间
    for (i=0;i<n1;i++)
        p2[i]=(float *)malloc(n2*sizeof(float)); //然后依次按一维申请
        
    for(i=0;i<n1;i++)
      for(j=0;j<n2;j++)
      {*((float *)p2+n2*i+j)=p3[i][j];} //将动态p3数组的值赋给p2指针空间
      
     return p2; //将p2指针空间地址返回
}

int main()
{
  int i,j,n1(3),n2(4);
  
  /*****动态定义的二维数组，并赋值****/
    float **p;
    p=new float*[n1];    
    for(j=0;j<n1;j++)  
    {  
        p[j]=new float[n2];  
    };
    
    for(i=0;i<n1;i++)
    {for(j=0;j<n2;j++)
     {p[i][j]=(i+1)*(j+1);}
    }
   
  /****指针申请的内存空间****/
    float **p1 =(float **)malloc(n1*sizeof(float *));//先申请M个指针型字节的空间
    for (i=0;i<n1;i++)
        p1[i]=(float *)malloc(n2*sizeof(float));//然后依次按一维申请

  for(i=0;i<n1;i++)
    {for(j=0;j<n2;j++)
     {*((float *)p1+n2*i+j)=p[i][j];}  //将动态p数组的值赋给p1指针空间
    }

  float **p2=sy((float **)p1,n1,n2);  //将p1空间地址传给函数，输出指针空间p2的地址
  //cout<<"ok"<<endl;
  for(i=0;i<n1;i++)
    {for(j=0;j<n2;j++)
     {cout<<"{"<<p[i][j]<<","<<*((float *)p2+n2*i+j)<<"}"<<" ";
     }cout<<endl;
    }
    
return 0;
}




