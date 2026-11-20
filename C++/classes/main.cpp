#include <iostream>
#include "pessoa.h"

int main(void){

  Pessoa *pessoa = new Pessoa();

  pessoa->nome = "Wanderlei Silva";
  pessoa->idade = 62;

  std::cout << "Nome..........: " << pessoa->nome << std::endl;
  std::cout << "Idade.........: " << pessoa->idade << std::endl;
  std::cout << "Ano nascimento: " << pessoa->anoNascimento() << std::endl;

  delete pessoa;

  return 0;

}







