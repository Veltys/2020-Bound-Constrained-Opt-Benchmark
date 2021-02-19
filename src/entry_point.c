#define D 10

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void cec20_test_func(double*, double*, int, int, int);

double *OShift, *M, *y, *z, *x_bound; // Las variables globales hacen llorar al niño Jesús
int ini_flag = 0, n_flag, func_flag, *SS;

void cec20_bench(unsigned int m, unsigned int n, double *x,
		unsigned short int max_ejecuciones) {
	unsigned short int i, j, k;
	unsigned short int func_num = 1;
	double *f;

	f = (double*) malloc(sizeof(double) * m);

	for(i = 0; i < max_ejecuciones; i++) {
		if(x == NULL) {
			printf("\nError: there is insufficient memory available!\n");

			exit(EXIT_FAILURE);
		}

		for(j = 0; j < D; j++) {
			cec20_test_func(x, f, n, m, func_num);

			for(k = 0; k < 2; k++) {
				printf(" f%d(x[%d]) = %lf,", func_num, k + 1, f[k]);
			}
			printf("\n");
		}

	}
	free(f);
	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);
}

