#include <stdio.h>
#include <stdlib.h>
#include "wscutil.h"

int main(int argc, char** argv){

	float vo=0, t_rt=0, t_rb=0, f_rt=0, f_rb=0, result=0;
	
	if ( argc < 2 || argc > 8 ){
		printf("\nError: %s\n", "Espero 5 parametros numéricos");
		printf("\nUsage: %s\n\n", "vo, t_rt, t_rb, f_rt, f_rb");
		exit(-1);
	} else {
		vo   = atof(argv[1]);
		t_rt = atof(argv[2]);
		t_rb = atof(argv[3]);
		f_rt = atof(argv[4]);
		f_rb = atof(argv[5]);

		
		result = map(vo, t_rt, t_rb, f_rt, f_rb);

		
	}

	printf("\nNovo valor na nova escala: %.4f\n\n", result);

	// testando as funções de conversão de temperatura.
	// printf("\nCelsius para Fahrenheit: %.2f : %8.2f\n", 10.0f, CelsiusToFahrenheit(10.0f) );
	// printf("\nFahrenheit to Celsius: %.2f : %8.2f\n", 50.0f, FahrenheitToCelsius(50.0f) );
	
	return 0;
}