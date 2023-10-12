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

bool checkInvertible(double **a, int filas)
{
	double determinante = 1;
	for (int i = 0; i < filas; i++)
	{
		determinante = determinante * a[i][i];
	}
	return determinante != 0 ? true : false;
}

		
void jacobi(double **a,double *b,double *&xnuevo,double *&xviejo,int filas,double tolerancia){
	//declaracion de x
	xnuevo = (double*)malloc(filas * sizeof(double));
	xviejo = (double*)malloc(filas * sizeof(double));
	
	if(xnuevo == NULL || xviejo == NULL){
		printf("Error: No se pudo asignar memoria.\n");
		exit(1);
	}
	
	for(int k=0;k<filas;k++){
		xviejo[k]=0;
		xnuevo[k]=0;
		
	}
	
	double suma=0;
	double error=1;
	
	//error
	for(int i=0;i<filas;i++){
		for(int j=0;j<filas;j++){
			if(j!=i){
				suma=suma+a[i][j];
			}
		}
		if(suma>a[i][i]){
			printf("Matriz no diagonal dominante, fila:%d\n",i);
		}
		if(a[i][i]==0){
			printf("Cero en diagonal");
			exit(1);
		}
	}


	//metodo
int iteraciones=0;
	while(teraciones<7){
		for(int i=0;i<filas;i++){
			
			suma=0;
			//printf("g");
			for(int j=0;j<filas;j++){
				if(j!=i){
					//printf("s");
					suma=suma+a[i][j]*xviejo[j];
					
				}
			
			}
			
			xnuevo[i]=(b[i]-suma)/a[i][i];
			
		}
		
		suma=0;
		for(int i=0;i<filas;i++){
			suma=suma+(xnuevo[i]-xviejo[i])*(xnuevo[i]-xviejo[i]);
		}
		error= sqrt(suma);
		iteraciones++;
		//printf("error= %lf",error);
		printf("Iteracion %d: x[%d]=%lf, error absoluto exacto: %lf, error absoluto estimado: %lf\n",iteraciones,i,xnuevo[i],error,error);
		//asignacion del vector viejo al nuevo para la proxima pasada
		for(int i=0;i<filas;i++){
			xviejo[i]=xnuevo[i];
		}
		
	}
	
	//impresion
	for(int i=0;i<filas;i++){
		printf("x[%d]=%0.2lf\n",i,xnuevo[i]);
	}
	printf("error=%lf",error);
}


int main(int argc, char *argv[])
{
	//por si error
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

	
	double *xnuevo= NULL;
	double *xviejo= NULL;
	//jacobi
	jacobi(a,b,xnuevo,xviejo,filas,0.1);
	
	// Liberar la memoria de la matriz
	
	for (int i = 0; i < filas; i++)
	{
		free(matriz[i]);
	}
	free(matriz);

	return 0;
}
