#include <stdio.h>
#include <string.h>
#include "funciones.h"

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n');
}

void leerEnteroPositivo(char *mensaje, int *destino) {
    int valido;
    char c;
    do {
        valido = 1;
        printf("%s", mensaje);
        if (scanf("%d", destino) != 1) {
            printf("Entrada no valida. Intente nuevamente.\n\n");
            valido = 0;
        }
        limpiarBuffer();
        if (valido && *destino <= 0) {
            printf("El valor debe ser positivo.\n\n");
            valido = 0;
        }
    } while (!valido || *destino <= 0);
}


void leerEnteroNoNegativo(char *mensaje, int *valor) {
    int valido;
    char c;
    do {
        valido = 1;
        printf("%s", mensaje);
        if (scanf("%d", valor) != 1) {
            printf("Entrada no valida. Intente nuevamente.\n\n");
            valido = 0;
        }
        limpiarBuffer();
        if (valido && *valor < 0) {
            printf("El valor no debe ser negativo.\n\n");
            valido = 0;
        }
    } while (!valido || *valor < 0);
}

void leerFlotantePositivo(char *mensaje, float *valor) {
    int valido;
    char c;
    do {
        valido = 1;
        printf("%s", mensaje);
        if (scanf("%f", valor) != 1) {
            printf("Entrada no valida. Intente nuevamente.\n\n");
            valido = 0;
        }
        limpiarBuffer();
        if (valido && *valor <= 0) {
            printf("El valor debe ser positivo.\n\n");
            valido = 0;
        }
    } while (!valido || *valor <= 0);
}

void leerCadena(char* mensaje, char* destino, int max) {
    int valido = 0;
    while (!valido) {
        printf("%s", mensaje);
        if (fgets(destino, max, stdin) != 0) {
            destino[strcspn(destino, "\n")] = '\0';

            char* inicio = destino;
            while (*inicio == ' ') inicio++;

            char* fin = destino + strlen(destino) - 1;
            while (fin >= inicio && *fin == ' ') {
                *fin = '\0';
                fin--;
            }

            if (strlen(inicio) == 0) {
                printf("Invalido. Intente de nuevo.\n");
            } else {
                if (inicio != destino) {
                    int i = 0;
                    while (inicio[i]) {
                        destino[i] = inicio[i];
                        i++;
                    }
                    destino[i] = '\0';
                }
                valido = 1;
            }
        }
    }
}

void leerCaracter(char* mensaje, char* destino) {
    int valido = 0;
    char c;
    while (!valido) {
        printf("%s", mensaje);
        c = getchar();
        limpiarBuffer();
        if (c != '\n') {
            *destino = c;
            valido = 1;
        } else {
            printf("Ingrese solo un caracter valido.\n");
        }
    }
}
