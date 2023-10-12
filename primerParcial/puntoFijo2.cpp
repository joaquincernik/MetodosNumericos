#include <stdio.h>
#include <math.h>

double g(double x);


int main(int argc, char const *argv[])
{

double xviejo=0;
double xnuevo=0;
int i=0;
double error=1;
double tolerancia=0;
 printf("Ingrese el primer número: ");
    scanf("%lf", &xviejo);

 printf("Ingrese la tolerancia: ");
    scanf("%lf", &tolerancia);

do
{
    //if((fabs(g(xviejo+(0.0001))-g(xviejo))/(0.0001))>=1){
        if((fabs(g(xviejo + 0.0001) - g(xviejo)) / 0.0001)>=1){
        printf("No se cumole con el criterio de convergenicia");
        exit(0);
    }
    else
    {
        i++;
        xnuevo=g(xviejo);
        error=fabs(xnuevo-xviejo);
        printf("Punto fijo de la iteracion %d: %lf,error absoluto exacto:%lf, error absoluto estimado: %lf\n",i,xnuevo,fabs(1.8508-xnuevo),error);
        xviejo=xnuevo;
    }
    
} while (i<7);

printf("punto fijo:%lf \t error:%lf \t iteracion:%d",xnuevo,error,i);
}


double g(double x){
   //return 2*exp(pow(x,2))/5;
   //return exp(x);
   //return cos(sin(x));
   return sqrt((x+5)/2);
}