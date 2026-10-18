#include <stdio.h>
#include <stdlib.h>
#include "minha_lib.h"

double somar(double a, double b) {
    return a + b;
}

double multiplicar(double a, double b) {
    return a * b;
}

double dividir(double a, double b){
  if ( b != 0  ){
     return a / b;
  }
  else{
	printf("\nDivisão por Zero\n");

	exit(1);
  }

}


double subtrair(double a, double b){
  return a - b;
}
