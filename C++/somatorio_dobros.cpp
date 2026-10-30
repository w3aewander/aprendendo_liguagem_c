#include "somatorio_dobros.h"
#include <math.h>

double somatorioDobros(double value, int n){

double newValue = value;

for(int i=0; i <= n; i++){
    newValue =  pow(2,i)/2 * value;  //pow(2, i - 1) * value;
}

return newValue;
}



