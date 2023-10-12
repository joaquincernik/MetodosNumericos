#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

// Funci�n para contar las filas en el archivo
int contarFilas(FILE *fp)
{
	int filas = 0;
	char c;

	while ((c = fgetc(fp)) != EOF)
	{
		if (c == '\n')
		{
			filas++;
		}
	}

	return filas;
}

// Funci�n para leer la matriz desde el archivo
void leerMatriz(FILE *fp, double **&matriz, int filas, int &columnas)
{
	char c;

	matriz = (double **)malloc(filas * sizeof(double *));
	for (int i = 0; i < filas; i++)
	{
		matriz[i] = (double *)malloc(100 * sizeof(double)); // Asumiendo un m�ximo de 100 columnas
	}

	int i, j;
	for (i = 0; i < filas; i++)
	{
		j = 0;
		do
		{
			fscanf(fp, "%lf", &(matriz[i][j]));
			j++;
		} while ((c = fgetc(fp)) != '\n');
	}

	columnas = j;
}

// Funci�n para crear y usar la matriz 'a'
void crearYUsarMatrizA(double **&a, double **matriz, int filas, int columnas)
{
	int num1 = filas;
	int num2 = columnas - 1;

	a = (double **)malloc(num1 * sizeof(double *));

	for (int i = 0; i < num1; i++)
	{
		a[i] = (double *)malloc(num2 * sizeof(double));
	}

	// Inicializaci�n y uso del arreglo 'a'
	printf("\nMatriz A: \n");
	for (int i = 0; i < num1; i++)
	{
		for (int j = 0; j < num2; j++)
		{
			a[i][j] = matriz[i][j];
			printf(" %0.2lf	", a[i][j]);
		}
		printf("\n");
	}
}

// Funci�n para crear y usar el arreglo 'b'
void crearYUsarArregloB(double *&b, double **matriz, int filas, int columnas)
{
	int size = filas;

	b = (double *)malloc(size * sizeof(double));

	// Inicializaci�n y uso del arreglo 'b'
	printf("\nArreglo B: \n");
	for (int i = 0; i < size; i++)
	{
		b[i] = matriz[i][columnas - 1];
		printf(" %0.2f\n", b[i]);
	}
	printf("\n");
}

void imprimirMatrizCompleta(int filas, double *b, double **a)
{
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < filas; j++)
		{
			printf(" %0.2lf	", a[i][j]);
		}
		printf("|%0.2lf", b[i]);
		printf("\n");
	}
}

void pivot(double** &a, double* &b, int filas, int i){
	
	if (fabs(a[i][i]) < 0.001) {
		printf("SE REALIZO PIVOTEO\n");
		for (int j = i + 1; j < filas; j++) {
			if (fabs(a[j][i]) > fabs(a[i][i])) {
				for (int k = i; k < filas; ++k) {
					printf("Se realizo pivoteo\n");
					double swap = a[i][k];
					a[i][k] = a[j][k];
					a[j][k] = swap;
				}
				double swap = b[i];
				b[i] = b[j];
				b[j] = swap;
			}
		}
		
	}
	imprimirMatrizCompleta(filas,b,a);
}

void triangularMatriz(int filas, double **&a, double *&b)
{
	
	double factor = 0;
	//para swapear
	int p = 0;
	double swap = 0;
	for (int j = 0; j < (filas - 1); j++)
	{
		pivot(a,b,filas,j);
		for (int i = (j + 1); i < filas; i++){
		
		factor = (-a[i][j]) / a[j][j];

		for (int k = 0; k < filas; k++)
			{
				a[i][k] = a[i][k] + factor * a[j][k];
			}
			b[i] = b[i] + factor * b[j];
		}

		// printf("%d,%d",filas,j);
	}

	printf("\nMatriz Triangular: \n");
	for (int i = 0; i < (filas); i++)
	{
		for (int j = 0; j < filas; j++)
		{
			printf(" %0.2lf	", a[i][j]);
		}
		printf("|%0.2lf", b[i]);
		printf("\n");
	}
}

bool checkInvertible(double **a, int filas)
{
	double determinante = 1;
	for (int i = 0; i < filas; i++)
	{
		determinante = determinante * a[i][i];
	}
	return determinante != 0 ? true : false;
}

void retrorestitucion(double **&a, double *&b, int filas, double *&x)
{
	double suma = 0;

	x = (double *)malloc(filas * sizeof(double));

	
	x[filas-1]=b[filas-1]/a[filas-1][filas-1];
	printf("x[%d]=%0.2lf\n", filas-1, x[filas-1]);
	for (int i = (filas - 2); i >= 0; --i)
	{
		suma = 0;

		for (int k = (i + 1); k < filas; ++k)
		{
			suma = suma + a[i][k]*x[k];
		}
		x[i] = (b[i]-suma) / a[i][i];
		printf("x[%d]=%0.2lf\n", i, x[i]);
	}
}
int main(int argc, char *argv[])
{
	FILE *fp;
	fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		puts("No se puede abrir el archivo");
		return 1;
	}

	// Contar filas en el archivo
	int filas = contarFilas(fp);
	printf("numero de filas = %i\n", filas);

	// Cerramos y reabrimos el archivo para resetear el puntero
	fclose(fp);
	fp = fopen("data.txt", "r");

	int columnas;
	double **matriz = NULL;

	// Leer la matriz desde el archivo
	leerMatriz(fp, matriz, filas, columnas);
	fclose(fp);

	// Imprimir la matriz le�da
	printf("\nMatriz leida: \n");
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			printf("%lf ", matriz[i][j]);
		}
		printf("\n");
	}

	// Crear y usar la matriz 'a'
	double **a = NULL;
	crearYUsarMatrizA(a, matriz, filas, columnas);

	// Crear y usar el arreglo 'b'
	double *b = NULL;
	crearYUsarArregloB(b, matriz, filas, columnas);

	printf(" Matriz completa\n");
	imprimirMatrizCompleta(filas, b, a);
	// matriz traingular
	triangularMatriz(filas, a, b);
	// Liberar la memoria de la matriz

	double *x = NULL;
	if (checkInvertible(a, filas))
	{
		retrorestitucion(a, b, filas, x);
	}
	else
	{
		printf("Matriz no invertible!!");
	}

	for (int i = 0; i < filas; i++)
	{
		free(matriz[i]);
	}
	free(matriz);

	return 0;
}
