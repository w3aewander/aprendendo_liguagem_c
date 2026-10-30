#include <iostream>
#include <dlfcn.h>
#include "somatorio_dobros.h"

//usando shared objetct no código c++

int main(void){

    double value=0.0;
    int count=1;

    std::cout << "Informe o valor inicial: ";
    std::cin >> value;

    std::cout << "Informe a quantidade: " ;
    std::cin >> count;

    std::cout << "Montante aculumulado: " << somatorioDobros(value, count) << std::endl;

    
}