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
    printf("Ingrese el primer número: ");
    scanf("%lf", &a);

    printf("Ingrese el segundo número: ");
    scanf("%lf", &b);

   // c=(a+b)/2;
    printf("Ingrese la tolerancia: ");
    scanf("%lf", &tolerancia);

     double x = 0;
     double fc=0;
     double fx=0;
     double fa=0;
     double fb=0;
     int i=0;
   do
    {
       // c=(a*funcion(b)-b*funcion(a))/(funcion(b)-funcion(a));
        i++;
     x=b-a;
     fb=funcion(b);
     fa=funcion(a);
     fx=funcion(x);
    c=a-(fa*x)/(fb-fa);
     fc=funcion(c);
     // c=funcion(a);
      
    if(fa*fc>0){
        a=c;
          
    }
    else if(fa*fc<0){
        b=c;
        
    }
    
    else
    {
        printf("La raiz seria %lf",c);
        break;
    }
    error=(b-a)/2;
    } while (error>tolerancia);
    
    printf("La raiz seria %0.5lf, iteraciones:%d",c,i);
}

double funcion(double x){
   return pow(x,10)-1;}