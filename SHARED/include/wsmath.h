#ifndef WSMATH_H
#define WSMATH_H

#include <stdio.h>
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
long long binNewton(int n, int k) {
    return fatorial(n) / (fatorial(k) * fatorial(n - k));
}



#endif
