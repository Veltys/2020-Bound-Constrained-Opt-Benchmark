#include <stdlib.h>

#include "entry_point.h"

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
	size_t m = 1;
	size_t n = 10;

	double x[10] = { 71.54520879576108, -66.44079060809807, -96.83962805179851, 50.1524759355562, -33.29732291043301, -86.11110162310239, -87.23414884503609, -95.37891852530484, -6.7244833347367035, -10.795441573642478 };

	const unsigned short int func_num = 1;

	double *res;

	res = cec20_bench(m, n, x, func_num);

	free_array(res);

	return EXIT_SUCCESS;
}
