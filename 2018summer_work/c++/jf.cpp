#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<cmath>
#include "mpi.h"
#include<math.h>
using namespace std;
int main()
{
  int cpuid,sumcpu;
  int N,i;
  double e,n,pi,mypi,h;
  int argc;
  char **argv;
  
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&sumcpu);
  MPI_Comm_rank(MPI_COMM_WORLD,&cpuid);

  if(cpuid==0)
  {
  printf("input the N ");  
  scanf("%i",&N);  
  }
  
  MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);  
  n=0;
  for(i=cpuid;i<N;i+=sumcpu)
    {  
      n=n+(4.0/(1+((i+0.5)/double(N))*((i+0.5)/double(N))))*1.0/N;
    }

  MPI_Reduce(&n,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
  if(cpuid==0)
{
 printf("the pi is: ");
 printf("%.32f",pi);
 printf("\n");
 printf("the error is: ");
 e=abs(pi-4*atan(1.0));
 printf("%e",e);
 printf("\n");
}
 MPI_Finalize();

  return 0;
 }
