#include <stdio.h>
#include <stdlib.h>
#include "wsmath.h"

int main(int argc, char* argv[]){
  
  if ( argc == 1) {
    printf("\nUso: fatorial <numero>\n"); 
    exit(1);
  } 
  
  if (argc == 2){
    
    int num;
    num =  atoi(argv[1]);
    printf("Fatorial de %d: %ld\n", num, fatorial(num));	
    
  } 
  

  
  return 0;
}
