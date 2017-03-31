CC=gcc-6
CFLAGS=-fopenmp -O3 

all: omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6
 
omp_solved2: omp_solved2.c
	$(CC) $(CFLAGS) omp_solved2.c -o omp_solved2

omp_solved3: omp_solved3.c
	$(CC) $(CFLAGS) omp_solved3.c -o omp_solved3

omp_solved3: omp_solved4.c
	$(CC) $(CFLAGS) omp_solved4.c -o omp_solved4

omp_solved5: omp solved5.c
	$(CC) $(CFLAGS) omp solved5.c -o omp_solved5

omp_solved6: omp solved6.c
	$(CC) $(CFLAGS) omp solved6.c -o omp_solved6

clean:
	rm -rf omp_solved2 omp_solved3 omp_solved4 omp_solved5 omp_solved6
