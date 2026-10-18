#include <stdio.h>
#include <stdlib.h>
#include "minha_lib.h"


void imprimeResultado(double a, double b){


      printf("Soma: %f\n", somar(a, b));
      printf("Multiplicação: %f\n", multiplicar(a, b));
      printf("Divisão: %f\n", dividir(a, b));
      printf("Subtração: %f\n", subtrair(a, b));

}

int main(int argc, char **argv) {


    double a, b;	

    if ( argc > 3) {
      printf("Este comando recebe no máximo dois parâmetros\n"); 
      exit(0);	    

    } else if ( argc == 3 ) {
      a = atof( argv[1]);
      b = atof( argv[2]);

    } else if (argc == 2) {
      printf("Você deve informar dois parâmetros\n");		    
      printf("====================================\n");

      printf("Entre com a primeiro número: ");
      scanf("%lf", &a);

      printf("Entre com o segundo número: ");
      scanf("%lf", &b);
    } 

    imprimeResultado(a, b);

    return 0;
}
