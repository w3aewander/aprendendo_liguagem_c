#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void)
{
    printf("Implementação do algoritmo de ordenação BubbleSort\n");

    /* Carrega a biblioteca */
    void *handle = dlopen("./lib/libbolha.so", RTLD_LAZY);

    if (handle == NULL) {
        fprintf(stderr, "Erro ao carregar biblioteca: %s\n", dlerror());
        return 1;
    }

    /* Define o tipo da função */
    typedef void (*ordenar_t)(int *, int);

    /* Obtém o endereço da função */
    ordenar_t ordenar = (ordenar_t)dlsym(handle, "ordenar");

    char *erro = dlerror();
    if (erro != NULL) {
        fprintf(stderr, "Erro ao localizar símbolo: %s\n", erro);
        dlclose(handle);
        return 1;
    }

    /* Exemplo de uso */
    int v[] = {5, 3, 8, 1, 2};
    int n = sizeof(v) / sizeof(v[0]);

    ordenar(v, n);

    printf("Vetor ordenado: ");
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");

    dlclose(handle);
    return 0;
}