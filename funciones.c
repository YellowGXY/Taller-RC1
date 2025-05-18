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
            while (*inicio == ' ') {
                inicio++;
            }	

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

void recalcularTiemposProductos(int *productosFTiempo, int (*tiemposPiezas)[MAX_PIEZAS], int totalProductos) {
    for (int i = 0; i < totalProductos; i++) {
        int suma = 0;
        for (int j = 0; j < MAX_PIEZAS; j++) {
            suma += tiemposPiezas[i][j];
        }
        productosFTiempo[i] = suma;
    }
}

void mostrarTiempo(int minutosTotales) {
    int semanas = minutosTotales / 10080;
    minutosTotales = minutosTotales % 10080;

    int dias = minutosTotales / 1440;
    minutosTotales = minutosTotales % 1440;

    int horas = minutosTotales / 60;
    int minutos = minutosTotales % 60;

    printf("   ");
    
    if (semanas > 0) {
        printf("%d ", semanas);
        if (semanas == 1) {
            printf("semana ");
        } else {
            printf("semanas ");
        }
    }

    if (dias > 0) {
        printf("%d ", dias);
        if (dias == 1) {
            printf("dia ");
        } else {
            printf("dias ");
        }
    }

    if (horas > 0) {
        printf("%d ", horas);
        if (horas == 1) {
            printf("hora ");
        } else {
            printf("horas ");
        }
    }

    if (minutos > 0) {
        printf("%d ", minutos);
        if (minutos == 1) {
            printf("minuto");
        } else {
            printf("minutos");
        }
    }

    if (semanas == 0 && dias == 0 && horas == 0 && minutos == 0) {
        printf("0 minutos");
    }

    printf("\n");
}

void mostrarTablaProductosPiezas(
    int producto, 
    char productos[MAX_PRODUCTO][MAX_NOMBRE],
    int stockProductos[MAX_PRODUCTO], 
    int totalProductos, 
    int productosFTiempo[MAX_PRODUCTO], 
    int piezasNecesarias[MAX_PRODUCTO][MAX_PIEZAS], 
    char piezasProductos[MAX_PRODUCTO][MAX_PIEZAS][MAX_NOMBRE],
    int stockPiezas[MAX_PRODUCTO][MAX_PIEZAS],
    int tiemposPiezas[MAX_PRODUCTO][MAX_PIEZAS]
    ) {

    printf("Producto seleccionado: %s\n", productos[producto]);
    printf("Stock actual de unidades terminadas: %d\n", stockProductos[producto]);
    printf("Tiempo de fabricacion promedio: %d minutos\n", productosFTiempo[producto]);

    printf("+----------+-------------------------+---------+-------------------------+\n");
    printf("| Cantidad | Nombre                  |  Stock  |  Tiempo de Instalacion  |\n");
    printf("+----------+-------------------------+---------+-------------------------+\n");
    for (int j = 0; j < MAX_PIEZAS; j++) {
        if (strlen(piezasProductos[producto][j]) != 0) {
            printf("| %8d | %-23s | %-7d | %19d min |\n",
            piezasNecesarias[producto][j],
            piezasProductos[producto][j],
            stockPiezas[producto][j],
            tiemposPiezas[producto][j]
            );
        }
    }
    printf("+----------+-------------------------+---------+-------------------------+\n");
}
