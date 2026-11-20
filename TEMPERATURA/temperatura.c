#include "include/temperatura.h"
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