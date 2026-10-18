#include <stdio.h>
#include <stdlib.h>

int main(){

  int *p;
  
  // Correção: atribui ao ponteiro 'p' e faz o cast para (int*)
  p = (int*) malloc(3 * sizeof(int));

  // Boa prática: verificar se a memória foi alocada com sucesso
  if (p == NULL) {
      return 1;
  }

  // Para atribuir um valor ao conteúdo apontado por p, use *p = valor
  *p = 10; 
  *(p +1) = 20;
  *(p + 2) = 30;
  
  //Mostra o endereço e o valor
  printf("Valores : %d %d %d\n", *p,  *(p +1), *(p + 2)  ); 

  // Libera a memória
  free(p);



  return 0;

}

