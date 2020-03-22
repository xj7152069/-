#include "mpi.h"
#include<stdio.h>
#include<iostream>
using namespace std;

int main()
{
int argc;
char **argv;
MPI_Init(&argc,&argv);
printf("hellow world!\n");
MPI_Finalize();
return 0;
}
