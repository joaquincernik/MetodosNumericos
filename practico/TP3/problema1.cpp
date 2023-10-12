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
    if(fabs((g(xviejo+(0.01))-g(xviejo))/(0.01))>=1){
        printf("No se cumole con el criterio de convergenicia");
        exit(0);
    }
    else
    {
        i++;
        xnuevo=g(xviejo);
        error=fabs(xviejo-xnuevo);
        xviejo=xnuevo;
    }
    
} while (error>tolerancia);

printf("punto fijo:%lf\t error:%lf\t iteracion:%d\t",xnuevo,error,i);
}








double g(double x){
//return ((pow(x,5)-3*pow(x,3)+2*pow(x,2)+2)/2)+x;
//return 4-pow(x,2);
//return pow(x,x-cos(x))+x;
}