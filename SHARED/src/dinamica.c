#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    void *handle;
    double (*func)(double, double);
    char *error;

    handle = dlopen("./lib/libminha_lib.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Erro ao carregar: %s\n", dlerror());
        return 1;
    }

    dlerror(); // limpa erros pendentes

    func = (double (*)(double, double)) dlsym(handle, "somar");

    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Erro ao localizar função: %s\n", error);
        dlclose(handle);
        return 1;
    }

    double a=0;
    double b=0;

    if ( argc > 1 && argc <=3  ){
      a = atof(argv[1]);
      b = atof(argv[2]);
    } else {
      printf("Entre com o primeiro número: ");	    
      scanf("%lf", &a); 
      printf("Entre com o segundo número: ");
      scanf("%lf", &b);
    }

    double resultado = func(a, b);
    printf("Resultado da soma: %.2f\n", resultado);

    dlclose(handle);


    return 0;
}

