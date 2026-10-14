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
 * Exempo: de 0 <--> 100  para 0 <--> 5
 */
float map(float vo, float t_rb, float t_rt, float f_rb, float f_rt){

   
   float new_valor = ( (f_rt - f_rb ) * (  vo / (t_rt - t_rb) ) );
	  
   if ( new_valor > f_rt ) {
   
      printf("Error: %s\n", "Range Overflow");
  
         printf("Escala de destino é de %.4f até %.4f\n", f_rb, f_rt);        

         exit ( -1 );
      }
   
   return new_valor;

}

#endif
