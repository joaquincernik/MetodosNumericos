#include <stdio.h>
#include <math.h>

double funcion(double x);

int main() {
    double a=0;
    double b=0;
    double c=0;
    double tolerancia=0;
    double error=0;
    error=1;
    int iteraciones=0;
    printf("Ingrese el primer número: ");
    scanf("%lf", &a);

    printf("Ingrese el segundo número: ");
    scanf("%lf", &b);

   // c=(a+b)/2;
    printf("Ingrese la tolerancia: ");
    scanf("%lf", &tolerancia);

   do
    {
        iteraciones++;
        c=(a+b)/2;
      
    if(funcion(a)*funcion(c)>0){
        a=c;
          
    }
    else if(funcion(a)*funcion(c)<0){
        b=c;
        
    }
    
    else
    {
        printf("La raiz seria %lf",c);
        break;
    }
    error=(b-a)/2;
    } while (error>tolerancia);
    
    printf("La raiz seria %0.5lf",c);
    printf("\nError=%lf\tIteraciones=%d",error,iteraciones);
}

double funcion(double x){
    return -3+4.23*x-1.35*pow(x,2)+0.11*pow(x,3);
}