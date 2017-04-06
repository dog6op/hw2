#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "util.h"


int main (int argc, char *argv[]){
    
    int n, max, i, j, k;
    double *u0, *u1;
    double h;
    
    
    if (argc != 3){
        fprintf(stderr, "Function needs array size and maximum of iterations!\n");
        abort();
    }
    
    n = atoi(argv[1]);
    max = atoi(argv[2]);
    h = 1.0/(n+1);
    
    u0 = (double *) malloc(sizeof(double) * (n + 2) * (n + 2));
    u1 = (double *) malloc(sizeof(double) * (n + 2) * (n + 2));
    
    for (i = 0; i <= n + 1; i++){
        for(j = 0; j <= n + 1; j++){
            u0[i][j] = 0.0;
            u1[i][j] = 0.0;
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
#pragma omp parallel for default(none) shared(n,u0,u1,h)
        for(i = 1; i <= n; i++){
            for(j = 1; j <= n; j++){
                u1[i][j] = (h * h * 1.0 + u[i-1][j] + u[i][j-1] + u[i+1][j] + u[i][j+1]) * 0.25;
            }
        }
        
#pragma omp parallel for default(none) shared(n,u0,u1,h)
        for(i = 1; i <= n; i++){
            for(j = 1; j <= n; j++){
                u0[i][j] = u1[i][j];
            }
        }
    }

    
    get_timestamp(&t1);
    double t = timestamp_diff_in_seconds(t0, t1);
    printf("Number of iterations is %d\n", max);
    printf("Time elapsed is %f seconds.\n", t);
    
    free(u0);
    free(u1);
    
    return 0;
}