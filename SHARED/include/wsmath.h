#ifndef WSMATH_H
#define WSMATH_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long  fatorial(int n){

   if ( n < 0 ) {
     return -1;
   }

   if ( n == 0 || n == 1 ) {
     return 1;
   }

   return n * fatorial(n -1)  ;

}


// Coeficiente binomial: C(n, k) = n! / (k! * (n-k)!)
long long binominal(int n, int k) {
    return fatorial(n) / (fatorial(k) * fatorial(n - k));
}

/**
*  Obtem os termos no format (a, b)^n
*/
void binNewton(int a, int b, int n) {

    double resultado = 0;

    printf("\nExpansao de (a + b)^%d:\n", n);

    for (int k = 0; k <= n; k++) {
        long long coef = binominal(n, k);
        double termo = coef * pow(a, n - k) * pow(b, k);

        printf("Termo %d: %lld * a^%d * b^%d = %.2f\n",
               k, coef, n - k, k, termo);

        resultado += termo;
    }

    printf("\nResultado final: %.2f\n", resultado);

  }


#endif
