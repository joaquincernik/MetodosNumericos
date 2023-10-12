#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    double a1=0;
    double a0=0;
    int size=0;
    double xSumatoria=0;
    double xSumatoriaDeCuadrados=0;
    double ySumatoriaDeCuadrados=0;
    double ySumatoria=0;
    double xMedia=0;
    double yMedia=0;
    double xy=0;
    double aux=0;
     printf("Ingrese la cantidad de x a ingresar\n");
    scanf("%d",&size);
    double *x= (double*)malloc(size*sizeof(double)); 
    double *y= (double*)malloc(size*sizeof(double)); 

    for(int i=0;i<size;i++){
        printf("\n Ingrese el valor del  x%d:",i );
        scanf("%lf",&aux);
        x[i]=exp(pow(aux,2));
        printf("\n Ingrese el valor del  y%d:",i );
        scanf("%lf",&y[i]);
    }

    for(int i=0;i<size;i++){
        xSumatoria=xSumatoria+x[i];
        xSumatoriaDeCuadrados=xSumatoriaDeCuadrados+x[i]*x[i];
        ySumatoriaDeCuadrados=ySumatoriaDeCuadrados+y[i]*y[i];
        ySumatoria=ySumatoria+y[i];
        xy=xy+x[i]*y[i];
    }
    xMedia=xSumatoria/size;
    yMedia=ySumatoria/size;

    a1=((size*xy)-(xSumatoria*ySumatoria))/(size*xSumatoriaDeCuadrados-pow(xSumatoria,2));
    a0=(yMedia-(a1*(xMedia)));

    printf("\nn=%d\t SumXY=%lf\t SumDeCuadrados=%lf\t SumX=%lf\t Xmedia=%lf\t Ymedia=%lf\t SumY=%lf\t\n ",size,xy,xSumatoriaDeCuadrados,xSumatoria,xMedia,yMedia,ySumatoria);
    printf("El ajuste lineal seria la funcion: y=%lf+%0.2lf X",a0,a1);

    //errores
    double sr=0;
    double syx=0;
    double r=0;
    //desviacion estandar
    for(int i=0;i<size;i++){
        sr+= pow(((a1)*(x[i])+a0)-y[i],2) ;
    }

    //Error estandar de la estimacion
    syx=sqrt((sr)/(size-1));
    //Coeficiente de correlacion
   r=  ((size*xy)-(xSumatoria*ySumatoria))/(sqrt(size*xSumatoriaDeCuadrados-pow(xSumatoria,2))*sqrt(size*ySumatoriaDeCuadrados-pow(ySumatoria,2)));

    printf("\nDesviacion estandar=%lf \n Error estandar (Syx)=%lf\n Coeficiente de correlacion (r)=%lf",sr,syx,r);
}
