#include <stdio.h>
#include <stdlib.h>

#include "wsmath.h"

void  binomial(int a, int b, int n) {

    double resultado = 0;

    printf("\nExpansao de (a + b)^%d:\n", n);

    for (int k = 0; k <= n; k++) {
        long long coef = binNewton(n, k);
        double termo = coef * pow(a, n - k) * pow(b, k);

        printf("Termo %d: %lld * a^%d * b^%d = %.2f\n",
               k, coef, n - k, k, termo);

        resultado += termo;
    }

    printf("\nResultado final: %.2f\n", resultado);

    
}


int main(int argc, char **argv){

  if ( argc != 4 ){
     printf("Informe os parámetros a, b e n\n");
     return -1;
  } 

  int a = atoi(argv[1]);
  int b = atoi(argv[2]);
  int n  = atoi(argv[3]);

  binomial(a, b, n );


  return 0;
}