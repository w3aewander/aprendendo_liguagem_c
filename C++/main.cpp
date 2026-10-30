#include <cstdlib>
#include <cstdio>
#include "points_calc.h"


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


  //A velha histórioa de pegar o valor inicial e começando com 1 
  // ir somando com o dobro do proximo numero até uma quantidade predeterminada
  // 1 * valor + 2 * valor + 4 * valor + 8 * valor, etc... 
  // Pega o numero de dedos das mão e pés e vai dobrando o valor a cada dedo
  // veja o valor final se considerar o valor inicial de R$0,01 (1 centavo)
  printf("O somatório dos dobros de %.2f,  %d vezes é %.2f\n",
         0.01, 20,
         somatorioDobros(0.01, 20)
        );

  return 0;

}







