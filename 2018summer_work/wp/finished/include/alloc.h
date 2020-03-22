#ifndef ALLOC_H
#define ALLOC_H

#include "cjb.h"

/* allocate and free multi-dimensional arrays */
void *alloc1 (size_t n1, size_t size);
void **alloc2 (size_t n1, size_t n2, size_t size);

float *alloc1float (size_t n1);
float **alloc2float (size_t n1, size_t n2);

void free1 (void *p);
void free2 (void **p);

void free1float (float *p);
void free2float (float **p);
#endif
