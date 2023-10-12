#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>

//Para estos casos, la función en cada sub-intervalo k, fk=akx²+bkx+ck  con k=0, ··· , n-1


void fIntervalo(double* y,double* x,double xSombrerito,int intervalo,double m){
    printf("F%d(%lf)=%lf+%lf(x-%lf)\n",intervalo,xSombrerito,y[intervalo],m,x[intervalo]);
    double resultado=y[intervalo]+m*(xSombrerito-x[intervalo]);
    printf("RESULTADO F(%lf)=%lf",xSombrerito,resultado);
}
int main(int argc, char const *argv[])
{
    int size=0;
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

    double xSombrerito=0;
    int intervalo=0;
    printf("Ingresar x sombrerito a buscar\n");
    scanf("%lf",&xSombrerito);
    //buscamos en que intervalo esta:
    for (int i=0;i<size-1;i++){
        if(xSombrerito>x[i]&&xSombrerito<x[i+1]){
            intervalo=i;
        }
    }

    printf("Esta en en intervalo f%d\n",intervalo);
 
    //ARMADO DE MATRIZ

    //es 3* size-1 debido a que hay 3n incognitas, siendo n los intervalos y el -1 por la imposicion a0=0
    int cantidadIntervalos=size-1;
    double **a = (double **)malloc((3*cantidadIntervalos) * sizeof(double *));
    double *b = (double *)malloc((3*cantidadIntervalos) * sizeof(double));

	for (int i = 0; i < (3*cantidadIntervalos); i++)
	{
		a[i] = (double *)malloc((3*cantidadIntervalos) * sizeof(double));
	
    }

//primeras 2n filas, rellenado de matrices f0(x0)=f1(x0)
//z[3k]=ak,z[3k+1]=bk,z[3k+2]=ck
    for(int k=0;k<(cantidadIntervalos-1);k++){
       for(int j=0;j<2;j++){
        a[2*k][3*k+j]=pow(x[k],2-j);
        a[2*k][3*j+k]=pow(x[k+1],2-j);
       }
       b[2*k]=y[k];
       b[2*k+1]=y[k+1];
    }

//Derivadas primeras(n-1 puntos interiores)
for(int i=2*cantidadIntervalos;i<3*cantidadIntervalos-2;i++){
    for(int k=0;k<cantidadIntervalos-2;k++){
        for(int j=0;j<1;j++){
            a[i][3*k+j]=(2-j)*pow(x[k],1-j);
            a[i][(3*k+1)+j]=-(2-j)*pow(x[k+1],1-j);
        }
    }
    b[i]=0;
}
printf("\nMatriz A: \n");
	for (int i = 0; i < 3*cantidadIntervalos-2; i++)
	{
		for (int j = 0; j < 3*cantidadIntervalos; j++)
		{
			printf(" %0.2lf	", a[i][j]);
		}
		printf("\n");
	}
}
