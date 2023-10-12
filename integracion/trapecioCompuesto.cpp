#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

double f(double x){
    return pow(x,2)+1;
}
int main(int argc, char const *argv[])
{
    double a,b,suma,integral;
    int subintervalos=0;
    //insercion de limites:
    printf("INGRESAR LOS LIMITES DE CONVERGENCIA\n");
    printf("a:");scanf("%lf",&a);    
    printf("\nb:");scanf("%lf",&b);

    printf("Ingresar cantidad de subintervalos\n",&subintervalos);
    scanf("%d",&subintervalos);

    suma=f(a)+f(b);
    for(int i=1;i<subintervalos;i++){
        suma=suma+2*f(a+i*(b-a)/subintervalos);
    }
    integral=(b-a)/(2*subintervalos)*suma;

    int opcion=0;
    double error=0;
    double integralExcacta=0;
    printf("I=%lf",integral);
    printf("\nIngresar 1 si tenes el valor exacto de la integral para el calculo del error:\n");
    scanf("%d",&opcion);
    if(opcion==1){
        printf("Ingresar valor:");
        scanf("%lf",&integralExcacta);
        error=fabs(integralExcacta-integral);
        printf("Error=%lf",error);
    }

}


