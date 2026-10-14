#ifndef WSCUTIL_H
#define WSCUTIL_H

/************************************
* Author: Wanderlei Silva do Carmo
* Version; 0.1
* Licence: GPLv3
*************************************/

/*
typedef struct (
    float valor_origem;
    float to_range_top;
    float to_range_bottom;
    float from_range_top;
    float to_range_bottom;
) range
*/


/** 
 * Faz a transposição de uma escala para outra 
 * Exempo: de 0 - 100  para 0 - 5
 * 
 * @param  float vo input_value, 
 *         float t_rb to range bottom.   float t_rt to range top, 
 *         float f_rb from range bottom, float f_rt from range top  
 *           
 * @return result float valor convertido
 */
float map(float vo, float t_rb, float t_rt, float f_rb, float f_rt){

   
   float new_valor = ( (f_rt - f_rb ) * (  vo / (t_rt - t_rb) ) );
	  
   if ( new_valor > f_rt ) {
   
      printf("Error: %s\n", "Range Overflow");
  
         printf("Escala de destino é de %.4f até %.4f\n", f_rb, f_rt);        

         exit( -1 );
      }
   
   return new_valor;

}

/**
 * Farenheit to Celsius Temperature Conversiion
 * @param Farenheit float Farenheit Temperature
 * @return Celsius float Celsius Temperature
 */
float FahrenheitToCelsius(float Fahrenheit){


   float Celsius = (Fahrenheit - 32 ) / 1.8;

   return Celsius; 

}

/**
 * Celsius To Farenheit Temperature Conversiion
 * @param Celsius float Farenheit Temperature
 * @return Farenheit float Celsius Temperature
 */
float CelsiusToFahrenheit(float Celsius){

   float Fahrenheit = (Celsius * 1.8 ) + 32 ;

   return Fahrenheit; 

}


#endif
