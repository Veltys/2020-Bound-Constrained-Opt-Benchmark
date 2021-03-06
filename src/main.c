/*
 * CEC20 Test Function Suite for Single Objective Bound Constrained Numerical Optimization
 */

// #include <WINDOWS.H>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void cec20_test_func(double*, double*, int, int, int);

double *OShift, *M, *y, *z, *x_bound;
int ini_flag = 0, n_flag, func_flag, *SS;

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
	int i, j, n, m, func_num;
	double *f, *x;
	FILE *fpt;
	char FileName[30];
	m = 2;
	n = 10;
	x = (double*) malloc(m * n * sizeof(double));
	f = (double*) malloc(sizeof(double) * m);

	for(i = 0; i < 30; i++) {
		func_num = i + 1;
		sprintf(FileName, "input_data/shift_data_%d.txt", func_num);

		fpt = fopen(FileName, "r");
		if(fpt == NULL) {
			printf("\n Error: Cannot open input file for reading \n");
		}

		if(x == NULL) {
			printf("\nError: there is insufficient memory available!\n");

			return EXIT_FAILURE;
		}

		for(j = 0; j < n; j++) {
			fscanf(fpt, "%lf", &x[j]);
			// printf("%Lf\n",x[k]);
		}

		fclose(fpt);

		for(j = 0; j < n; j++) {
			x[1 * n + j] = 0.0;
			// printf("%Lf\n",x[1*n+j]);
		}

		cec20_test_func(x, f, n, m, func_num);
		for(j = 0; j < m; j++) {
			printf(" f%d(x[%d]) = %lf,", func_num, j + 1, f[j]);
		}
		printf("\n");

	}

	free(x);
	free(f);
	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);

	return EXIT_SUCCESS;
}

