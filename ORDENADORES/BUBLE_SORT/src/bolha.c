#include <stdio.h>

// Bolhar - bubblesort
void ordenar(int arr[], int count) {
    int aux;
    int ordenado;

    do {
        ordenado = 1;

        for (int i = 0; i < count - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                aux = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = aux;
                ordenado = 0;
            }
        }

    } while (!ordenado);
}

void print_array(int arr[], int count) {
    
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

