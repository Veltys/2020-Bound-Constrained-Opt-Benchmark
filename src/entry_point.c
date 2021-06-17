/**
 * @file		entry_point.c
 * @brief		Contiene las funciones necesarias como punto de entrada de la biblioteca de tests del CEC 2020
 *
 * @author		Rafael Carlos Méndez Rodríguez (i82meror)
 * @date		27/04/2021
 * @version		2.0.0
 */

// #define VERBOSE						// Constante del preprocesador para regular la salida por pantalla de los datos de diagnóstico
// #define LOG							// Constante del preprocesador para regular la salida por archivo de registro de los datos de diagnóstico

#ifdef LOG
#define LOG_FILE_NAME "benchmark"
#endif // LOG

#ifdef LOG
#include <time.h>
#endif // LOG

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void cec20_test_func(double*, double*, int, int, int);

double *OShift, *M, *y, *z, *x_bound;	// Las variables globales hacen llorar al niño Jesús
int ini_flag = 0, n_flag, func_flag, *SS;

#if defined(VERBOSE) || defined(LOG)
void export(FILE *dest __attribute__((unused)), char *text, ...) {
	/**
	 * Función export
	 * Muestra por pantalla, registra en un archivo o ambos el texto dado
	 *
	 * @param		dest		FILE *						Ruta del archivo de registro (NULL si no es necesario)
	 * @param		text		char *						Texto a registrar
	 * @param		...										Resto de parámetros para formato tipo printf
	 */

	va_list args;

	va_start(args, text);

#ifdef VERBOSE
	vprintf(text, args);
#endif // VERBOSE

#ifdef LOG
	vfprintf(dest, text, args);
#endif // LOG

	va_end(args);

}
#endif //  defined(VERBOSE) || defined(LOG)

double* cec20_bench(const size_t m, const size_t n, double *x, const unsigned short int func_num) {
	/**
	 * Función cec20_bench
	 * Actúa como punto de entrada de la biblioteca del benchmark, realizando todas las tareas necesarias para la inicialización, llamada y recogida de resultados
	 *
	 * @param		m			const size_t				Número de elementos a testear
	 * @param		n			const size_t				Dimensiones del espacio de búsqueda
	 * @param		x			double *					Vector de elementos
	 * @param		func_num	const unsigned short int	Número de función que se empleará
	 *
	 * @return					double *					Vector de resultados
	 */

	double *f;

#if defined(VERBOSE) || defined(LOG)
	unsigned int i, j;

	FILE *log = NULL;
#endif // defined(VERBOSE) || defined(LOG)

#ifdef LOG
	time_t t = time(NULL);

	struct tm tm = *localtime(&t);

	char filename[256];

	sprintf(filename, "%s_%hu_%zu_%d_%02d_%02d.log", LOG_FILE_NAME, func_num, n, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

	log = fopen(filename, "a");
#endif // LOG

	f = (double*) malloc(sizeof(double) * m);

#ifdef LOG
	if(log == NULL) {
		printf("Error: Cannot open file <%s>\n", filename);

		return NULL;
	}
	else  // No "{", it's intentional
#endif // LOG

	if(f == NULL) {
		printf("Error: There is not enough memory available\n");

#if defined(VERBOSE) || defined(LOG)
		export(log, "Error: There is not enough memory available\n");

		fclose(log);
#endif // defined(VERBOSE) || defined(LOG)

		return NULL;
	}
	else {

#if defined(VERBOSE) || defined(LOG)
		export(log, "Input data: ");

		export(log, "m = %zu, n = %zu, func_num = %hu, x = [", m, n, func_num);

		for(i = 0; i < m; i++) {
			export(log, "[");

			for(j = 0; j < n; j++) {
				export(log, "%f", x[m * i + j]);

				if(j < n - 1) {
					export(log, ", ");
				}
			}

			export(log, "]");
		}

		export(log, "]\n");
#endif // defined(VERBOSE) || defined(LOG)

		cec20_test_func(x, f, n, m, func_num);

#if defined(VERBOSE) || defined(LOG)
		export(log, "Output data: ");

		export(log, "f = [");

		for(j = 0; j < m; j++) {
			export(log, "%f", f[j]);
		}

		export(log, "]\n\n");
#endif // defined(VERBOSE) || defined(LOG)

#ifdef LOG
		fclose(log);
#endif // LOG

		// free(f);
		// free(y);
		// free(z);
		// free(M);
		// free(OShift);
		// free(x_bound);

		return f;
	}
}

void free_array(double *array) {
	/**
	 * Función free_array
	 * Libera la memoria del vector que recibe
	 *
	 * @param		array		double *					Vector a liberar
	 */

	free(array);
}
