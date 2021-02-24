// #define VERBOSE

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void cec20_test_func(double*, double*, int, int, int);

double *OShift, *M, *y, *z, *x_bound; // Las variables globales hacen llorar al niño Jesús
int ini_flag = 0, n_flag, func_flag, *SS;

double cec20_bench(const size_t m, const size_t n, double *x) {

#ifdef VERBOSE
	unsigned short int i;
#endif

	unsigned short int func_num;
	double *f;

	FILE *archivo;

	f = (double*) malloc(sizeof(double) * m);

	if(f == NULL) {
		printf("\nError: there is insufficient memory available!\n");

		return NAN;
	}
	else if((archivo = fopen("func_num.txt", "r")) == NULL) {
		printf("\nError: cannot load configuration file\n");

		return NAN;
	}
	else {
		fscanf(archivo, "%hu", &func_num);

		fclose(archivo);

		cec20_test_func(x, f, n, m, func_num);

#ifdef VERBOSE
		for(i = 0; i < 2; i++) {
			printf(" f%d(x[%d]) = %lf,", func_num, i + 1, f[i]);
		}

		printf("\n");
#endif

		free(f);
		// free(y);
		// free(z);
		// free(M);
		// free(OShift);
		// free(x_bound);

		return f[2];
	}
}
