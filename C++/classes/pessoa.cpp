#include <iostream>
#include "pessoa.h"


int Pessoa::anoNascimento() const {
  int anoAtual;
  int anoNasc;

  anoAtual = 2026;
  anoNasc = anoAtual - this->idade;
  return anoNasc;
}

