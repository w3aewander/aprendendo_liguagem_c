#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>


float fToc(float f) {
    void *handle;
    float (*func)(float);
    char *error;

    handle = dlopen("./lib/libtemperatura.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Erro ao carregar: %s\n", dlerror());
        return 1.0f;
    }

    // limpa erro anterior
    dlerror();

    func = (float (*)(float)) dlsym(handle, "fahrenheithToCelsius");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Erro ao localizar função: %s\n", error);
        dlclose(handle);
        return 1.0f;
    }

    float resultado = func(f);
    dlclose(handle);
    return resultado;
}

float cTof(float c) {
    void *handle;
    float (*func)(float);
    char *error;

    handle = dlopen("./lib/libtemperatura.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Erro ao carregar: %s\n", dlerror());
        return 1.0f;
    }

    // limpa erro anterior
    dlerror();

    func = (float (*)(float)) dlsym(handle, "celsiusToFahrenheith");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Erro ao localizar função: %s\n", error);
        dlclose(handle);
        return 1.0f;
    }

    float resultado = func(c);
    dlclose(handle);
    return resultado;
}

int main(int argc, char **argv) {

    float c=0;
    float f=0;

    printf("Convertendo temperatura Celsius para Fahrenheith\n");
    printf("Temperatura em ºC:" ); scanf("%f",&c);    
    printf("%fºC em Fahrenheith = %fºF\n", c, cTof(c));


    printf("Convertendo temperatura Fahrenheith para Celsius\n");
    printf("Temperatura em ºF:" ); scanf("%f",&f);    
    printf("%f ºF em Fahrenheith = %fºC\n", f, fToc(f));

  
    return 0;
}
