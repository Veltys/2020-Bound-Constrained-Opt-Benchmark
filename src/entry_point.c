#define D 10

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void cec20_test_func(double*, double*, int, int, int);

double *OShift, *M, *y, *z, *x_bound; // Las variables globales hacen llorar al niño Jesús
int ini_flag = 0, n_flag, func_flag, *SS;

void cec20_bench(const size_t m, const size_t n, double *x) {
	unsigned short int i, j;
	unsigned short int func_num = 1;
	double *f;

	f = (double*) malloc(sizeof(double) * m);

	if(x == NULL) {
		printf("\nError: there is insufficient memory available!\n");

		exit(EXIT_FAILURE);
	}

	for(i = 0; i < D; i++) {
		cec20_test_func(x, f, n, m, func_num);

		for(j = 0; j < 2; j++) {
			printf(" f%d(x[%d]) = %lf,", func_num, j + 1, f[j]);
		}
		printf("\n");

	}

	free(f);
	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);
}

