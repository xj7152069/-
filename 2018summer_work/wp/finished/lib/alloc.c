/******************************************************************
ALLOC - Allocate and free multi-dimensional arrays
alloc1		allocate a 1-d array
free1		free a 1-d array
alloc2		allocate a 2-d array
free2		free a 2-d array

alloc1float	allocate a 1-d array of floats
free1float	free a 1-d array of floats
alloc2float	allocate a 2-d array of floats
free2float	free a 2-d array of floats

***********************************************************************/

#include "alloc.h"

/* allocate a 1-d array of floats */
float *alloc1float(size_t n1)
{
	return (float*)alloc1(n1,sizeof(float));
}

/* allocate a 2-d array of floats */
/*  n1: fast dimension; n2: slow dimension */
float **alloc2float(size_t n1, size_t n2)
{
	return (float**)alloc2(n1,n2,sizeof(float));
}

/* free a 1-d array of floats */
void free1float(float *p)
{
	free1(p);
}

/* free a 2-d array of floats */
void free2float(float **p)
{
	free2((void**)p);
}

/* allocate a 1-d array */
void *alloc1 (size_t n1, size_t size)
{
	void *p;

	if ((p=malloc(n1*size))==NULL)
		return NULL;
	return p;
}


/* allocate a 2-d array */
void **alloc2 (size_t n1, size_t n2, size_t size)
{
	size_t i2;
	void **p;

	if ((p=(void**)malloc(n2*sizeof(void*)))==NULL) 
		return NULL;
	if ((p[0]=(void*)malloc(n2*n1*size))==NULL) {
		free(p);
		return NULL;
	}
	for (i2=0; i2<n2; i2++)
		p[i2] = (char*)p[0]+size*n1*i2;
	return p;
}
/* free a 1-d array */
void free1 (void *p)
{
	free(p);
}

/* free a 2-d array */
void free2 (void **p)
{
	free(p[0]);
	free(p);
}
