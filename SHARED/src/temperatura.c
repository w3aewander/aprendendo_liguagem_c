/************************************************************
* Conversão entre temperaturas Celsius e Fahrenheith
* @author Wanderlei Silva do Carmo <wander.silva@gmail.com>
*************************************************************/

/****************************************************
 * Converte temperatura em Celsius para Fahrenheith
 ****************************************************/
float celsiusToFahrenheith(float c){
   return  1.8*c + 32; 
}

/***************************************************
 * Converte temperatura em Fahrenheith to Celsius
 **************************************************/
float fahrenheithToCelsius(float f){
  
	return  (f - 32) /1.8;
}
