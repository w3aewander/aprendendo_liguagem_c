#include <cstdlib>
#include <cstdio>
#include "points_calc.h"

// Compile com:
// g++ -o distancia main.cpp -fPIC -lm

int main(int argc, char** argv){


  if ( argc != 5 ) {
    printf("Necessário 5 parâmetros para o cálculo da distância.\n");
    return -1;
  }

  Point p1;
  p1.x = atoi(argv[1]);
  p1.y = atoi(argv[2]);

  Point p2;
  p2.x = atoi(argv[3]);
  p2.y = atoi(argv[4]);

  double d = distancia(p1, p2); 

  printf("A distância entre os pontos: P1(%d,%d) e P2(%d,%d) é de: %.4f\n", p1.x, p1.y, p2.x,p2.y,d ); 
  printf("A aŕea do triangulo formado pela reta entre os dois pontos é de %.4f\n", area(p1,p2) );

  return 0;

}







