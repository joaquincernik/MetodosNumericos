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
printf("\nMatriz Original: \n");
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < filas; j++)
		{
			printf(" %0.2lf	", a[i][j]);
		}
		printf("|%0.2lf", b[i]);
		printf("\n");
	}
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


int main(int argc, char const *argv[])
{
    int size=0;
    int respuesta=0;
    double *coeficientes=NULL;
    int p=0;
    int opcion=0;
    double sumaxy=0;
    double sumax=0;

    printf("Ingrese la cantidad de x a ingresar\n");
    scanf("%d",&size);
    printf("\nIngresar p\n");
    scanf("%d",&p);

    if(size<p){
        printf("La cantidad debe ser mayor que el grado del polinomio\n");
        exit(0);
    }

    double *x= (double*)malloc(size*sizeof(double)); 
    double *y= (double*)malloc(size*sizeof(double)); 

    double **a= (double**)malloc((p+1)*sizeof(double*)); 
    	for (int i = 0; i <= (p); i++)
	{
		a[i] = (double *)malloc((p+1) * sizeof(double));
	}
    double *b= (double*)malloc(size*sizeof(double)); 
    for(int i=0;i<size;i++){
        printf("\n Ingrese el valor del  x%d:",i );
        scanf("%lf",&x[i]);
        printf("\n Ingrese el valor del  y%d:",i );
        scanf("%lf",&y[i]);
    }

    
   
  /**/  for(int l=0;l<p+1;l++){
        sumaxy=0;
        for(int i=0;i<size;i++){
            sumaxy=sumaxy+pow(x[i],l)*y[i];
            b[l]=sumaxy;
          
        }
        //recorro las columnas
        for(int m=0;m<(p+1);m++){
            sumax=0;
            
            for(int o=0;o<size;o++){
                sumax=sumax+pow(x[o],l+m);
            }
           // printf("L=%d,M=%d",l,m);
             a[l][m]=sumax;
        }
    }
    retrorestitucion(a,b,p+1,coeficientes);
	printf("Y=");
    for(int i=0;i<p+1;i++){
        printf("%lf X^%d+ ",coeficientes[i],i);
    }

    //calculo error:
    double sr=0;
    //error estandar de estimacion
    double syx=0;
    double r=0;
	double st=0;
    double suma=0;
    double ymedia=0;
    for(int i=0;i<size;i++){
        suma=0;
        for(int c=0;c<(p+1);c++){
            suma=suma+pow(x[i],c)*coeficientes[c];
        }
        sr=sr+pow(y[i]-suma,2);
        //aprovecho el for para calcular el ymedia
        ymedia=ymedia+y[i];
    }
    ymedia=ymedia/size;
	for(int i=0;i<size;i++){
		st=st+pow(y[i]-ymedia,2);
	}
    syx=sqrt(sr/(size-(p+1)));
	r=sqrt((st-sr)/st);
	printf("\n\tErr Estandar(Syx).:%lf \n\t r(Coeficiente de correlacion):%lf \n\t",syx,r);
}
