#include "include/temperatura.h"

#include <stdio.h>


int main(void){

    float c=0.0, f=0.0;

    printf("Entre com a temperatura em ºC: ");
    scanf("%f", &c);


    f=CelsiusToFahrenheit(c);

    printf("\n%.2f °C = %.2f °F\n", c, f);

    return 0;

}