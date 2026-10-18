package main

/*
#cgo LDFLAGS: -L./lib -lminha_lib -Wl,-rpath,$ORIGIN/lib
double somar(double a, double b);
double subtrair(double a, double b);
double multiplicar(double a, double b);
double dividir(double a, double b);
*/
import "C"

import "fmt"

func main() {
    var a float64
    var b float64
    //var resSomar float64 
    //var resSubtrair float64
    //var resMultiplicar float64
    //var resDividir float64

    fmt.Printf("\nDigite o primeiro número: ")	
    fmt.Scanf("%f", &a);

    fmt.Printf("\nDigite o segundo número: ")
    fmt.Scanf("%f", &b);

    
    // Atribuindo os cálculos
    resSomar, resSubtrair, resMultiplicar, resDividir := C.somar(C.double(a), C.double(b)), 
							C.subtrair(C.double(a), C.double(b)), 
							C.multiplicar(C.double(a), C.double(b)), 
							C.dividir(C.double(a), C.double(b)) 

   // Formatando a saida							
   fmt.Printf("Soma: %f\nSubtração: %f\nMultiplicação:%f\nDivisão: %f\n",  
		float64(resSomar), 
		float64(resSubtrair), 
		float64(resMultiplicar), 
		float64(resDividir) )


}

