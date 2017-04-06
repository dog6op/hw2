#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "util.h"


int main (int argc, char *argv[]){
    
    int n, max, i, j, k;
    double *u;
    double h;
    
    
    if (argc != 3){
        fprintf(stderr, "Function needs array size and maximum of iterations!\n");
        abort();
    }
    
    n = atoi(argv[1]);
    max = atoi(argv[2]);
    h = 1.0/(n+1);
    
    u = (double *) malloc(sizeof(double) * (n + 2) * (n + 2));
    
    for (i = 0; i <= n + 1; i++){
        for(j = 0; j <= n + 1; j++){
            u[i][j] = 0.0;
        }
    }
    
#pragma omp parallel
    {
        printf("Hello hello. I'm thread %d of %d\n",
               omp_get_thread_num(),
               omp_get_num_threads());
    }
    timestamp_type t0, t1;
    get_timestamp(&t0);
    
    for(k = 0; k < max; k++)
    {
#pragma omp parallel for private(i,j)
        for(i = 1; i <= n/2; i++){
            for(j = 1; j <= n/2; j++){
                u[i][j] = (h * h * 1.0 + u[i-1＋n/2][j+n/2] + u[i+n/2][j-1+n/2] + u[i+1+n/2][j+n/2] + u[i+n/2][j+1+n/2]) * 0.25;
            }
        }
        
#pragma omp parallel for private(i,j)
        for(i = 1; i <= n/2; i++){
            for(j = 1; j <= n/2; j++){
                u[i + n/2][j + n/2] = (h * h * 1.0 + u[i-1][j] + u[i][j-1] + u[i+1][j] + u[i][j+1]) * 0.25;
            }
        }
    }

    
    get_timestamp(&t1);
    double t = timestamp_diff_in_seconds(t0, t1);
    printf("Number of iterations is %d\n", max);
    printf("Time elapsed is %f seconds.\n", t);;
    
    free(u);
    
    return 0;
}