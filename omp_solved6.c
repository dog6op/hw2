/******************************************************************************
* FILE: omp_bug6.c
* DESCRIPTION:
*   This program compiles and runs fine, but produces the wrong result.
*   Compare to omp_orphan.c.
* AUTHOR: Blaise Barney  6/05
* LAST REVISED: 06/30/05
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 100

float a[VECLEN], b[VECLEN];
float global_sum;

float dotprod ()
{
int i,tid;


tid = omp_get_thread_num();
#pragma omp parallel for reduction(+:global_sum) private(i)
    // parallel & private(i)
  for (i=0; i < VECLEN; i++)
    {
    global_sum = global_sum + (a[i]*b[i]);
        
    printf("  tid= %d i=%d\n",tid,i);
    }
}


int main (int argc, char *argv[]) {
int i;

    
    
for (i=0; i < VECLEN; i++)
  a[i] = b[i] = 1.0 * i;
    
#pragma omp parallel shared(global_sum)

  dotprod();

#pragma omp barrier
printf("Sum = %f\n",global_sum);

}

