#include <stdio.h>
#include <math.h>

double f(double x);
double derivada(double x);
void secante() {
    double cn, cv, cvv, tolerancia, e;
    int iteracion = 0;
    printf("Recuerde haber definido previamente la funcion y su derivada al inicio del codigo\nIngrese el valor de partida (cv)\n");
    scanf("%lf", &cv);
    printf("Ingrese el valor para Xi-1 (cvv)\n");
    scanf("%lf", &cvv);
    printf("Ingrese la cantidad de cifras decimales de error\n");
    scanf("%lf", &tolerancia);
    tolerancia = pow(10, -tolerancia);
    do {
        double aprox = (f(cvv) - f(cv)) / (cvv - cv);
        cn = cv - (f(cv) / aprox);
        e = fabs(cn - cv);
        cvv = cv;
        cv = cn;
        iteracion++;

    } while (e > tolerancia || iteracion >= 5000);

    printf("\nResultados Secante:\n");
    printf("El valor de la raiz es %lf con un error de %lf\n", cn, e);
    printf("La funcion en dicho punto vale %lf\n", f(cn));
    printf("El problema fue resuelto en %d iteraciones\n", iteracion);
}
int main(int argc, char const *argv[])
{

double xviejo=0;
double xnuevo=0;
int i=0;
double error=0;
double tolerancia=0;
 printf("Ingrese el primer número: ");
    scanf("%lf", &xviejo);

 printf("Ingrese la tolerancia: ");
    scanf("%lf", &tolerancia);

do
{
    if(fabs(derivada(xviejo))<0.00001){
        printf("DERIVADA MUY PEQUENA");
        exit(0);
    }
    else
    {
        i++;
        xnuevo=xviejo-(f(xviejo)/derivada(xviejo));
        error=fabs(xnuevo-xviejo);
        xviejo=xnuevo;
    }
    
} while (error>tolerancia);

printf("raiz:%lf \t error:%lf \t iteracion:%d",xnuevo,error,i);
}


double f(double x){
return pow(x,x)-5;
//return x;
}

double derivada(double x){
    //return 2+1/(x*log(10))-cos(3*x)*3;
    return exp(x*log(x))*(log(x)+1);
}