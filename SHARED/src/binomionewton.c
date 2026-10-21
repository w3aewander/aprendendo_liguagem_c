#include <stdio.h>
#include <stdlib.h>

#include "wsmath.h"


int main(int argc, char **argv){

  if ( argc != 4 ){
     printf("Informe os parámetros a, b e n\n");
     return -1;
  } 

  int a  = atoi(argv[1]);
  int b  = atoi(argv[2]);
  int n  = atoi(argv[3]);

  binNewton(a, b, n );


  return 0;
}