#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>
using namespace std;

//PARA MATRIZ
void triangularMatriz(int filas, double **&a, double *&b)
{
	double factor = 0;
	int p = 0;
	double swap = 0;
	for (int j = 0; j < (filas - 1); j++)
	{
		for (int i = (j + 1); i < filas; i++)
		{

			// ver si ajj es 0
			p = j;
			if (fabs(a[j][j]) < 0.00001)
			{
				for (int l = (j + 1); l < filas; l++)
				{
					if (fabs(a[l][j]) > fabs(a[j][j]))
					{
						p = l;
					}
				}
				for (int n = 0; n < filas; n++)
				{
					swap = a[p][n];
					a[p][n] = a[j][n];
					a[j][n] = swap;
				}
				swap = b[p];
				b[p] = b[j];
				b[j] = swap;
			}

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

void retrorestitucion(double **&a, double *&b, int filas,double *&coeficientes)
{
triangularMatriz(filas,a,b);
if(checkInvertible(a,filas)){
    double suma = 0;
	coeficientes = (double *)malloc(filas * sizeof(double));

    //printf("\nP%d(x)=",filas-1);
	
	coeficientes[filas-1]=b[filas-1]/a[filas-1][filas-1];
	printf("x[%d]=%0.2lf\n", filas-1, coeficientes[filas-1]);
	for (int i = (filas - 2); i >= 0; --i)
	{
		suma = 0;
		
		for (int k = (i + 1); k < filas; ++k)
		{
			suma = suma + a[i][k]*coeficientes[k];
		}
		coeficientes[i] = (b[i]-suma) / a[i][i];
		printf("x[%d]=%0.2lf\n", i, coeficientes[i]);
	}
    }
    else{
        printf("Matriz no invertible");
        exit(0);
    }
	
}
//fin para matriz

void obtenerValor(double* x,double* y,double xSombrerito,int size){
  //calculo de ysombrerito
    double suma=0;
    double prod=0;
    for(int k=0;k<size;k++){
      prod=1;
        for(int j=0;j<size;j++){
            if(j!=k){
                prod=prod*(xSombrerito-x[j])/(x[k]-x[j]);
            }
        }
        suma=suma+y[k]*prod;
    }
    printf("Valor interpolado=%lf",suma);
}

	
	void obtenerPolinomioValuado(double xSombrerito,double* &coeficientes,int size){
		double suma=0;
		printf("P(%d)= ",size-1);
		for(int i =0;i<size;i++){
			printf("%lf X^%d+ ",coeficientes[i],i);
			suma=suma+coeficientes[i]*pow(xSombrerito,i);
		}
		printf("\nPolinomio valuado en xsombrerito:\nP(%lf)=%lf\n",xSombrerito,suma);
	}	

void obtenerPolinomio(double* x,double* y,double xSombrerito,int size){
    double **a= (double**)malloc(size*sizeof(double*)); 
    	for (int i = 0; i < size; i++)
	{
		a[i] = (double *)malloc(size * sizeof(double));
	}
    double *b= (double*)malloc(size*sizeof(double)); 
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            a[i][j]=pow(x[i],(j));
            b[i]=y[i];
        }
      
    }

	
    printf("\nMatriz Original: \n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf(" %0.2lf	", a[i][j]);
		}
		printf("|%0.2lf", b[i]);
		printf("\n");
	}
	double *coeficientes=NULL;
    retrorestitucion(a,b,size,coeficientes);
	obtenerPolinomioValuado(xSombrerito,coeficientes,size);
	
  
}


int main(int argc, char const *argv[])
{
    int size=0;
    int respuesta=0;
    double xSombrerito=0;
    double *coeficientes=NULL;

   int opcion=0;
    printf("Ingrese la cantidad de x a ingresar\n");
    scanf("%d",&size);

    double *x= (double*)malloc(size*sizeof(double)); 
    double *y= (double*)malloc(size*sizeof(double)); 

    for(int i=0;i<size;i++){
        printf("\n Ingrese el valor del  x%d:",i );
        scanf("%lf",&x[i]);
        printf("\n Ingrese el valor del  y%d:",i );
        scanf("%lf",&y[i]);
    }

    printf("\nIngresar x sombrerito\n");
    scanf("%lf",&xSombrerito);

    
    do
    {
       printf("Que deseas realizar?\n 1:Obtener el polinomio\t\n2:Obtener un valor interpolado\t\n");
       scanf("%d",&opcion);
       switch(opcion){
        case 1:
			obtenerPolinomio(x,y,xSombrerito,size);
			break;
        case 2:
			obtenerValor(x,y,xSombrerito,size);
			break;
       }
      
    } while (opcion!=0);
    
   
}
