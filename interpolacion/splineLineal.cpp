#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>

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
 
    double m=(y[intervalo+1]-y[intervalo])/(x[intervalo+1]-x[intervalo]);
    fIntervalo(y,x,xSombrerito,intervalo,m);
}
