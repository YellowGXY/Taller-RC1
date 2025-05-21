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

void recalcularTiemposProductos(int *productosFTiempo, int (*tiemposPiezas)[MAX_PIEZAS_FIJO], int totalProductos, int maxPiezas) {
    for (int i = 0; i < totalProductos; i++) {
        int suma = 0;
        for (int j = 0; j < maxPiezas; j++) {
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
    char (*productos)[MAX_NOMBRE],
    int *stockProductos,
    int totalProductos,
    int *productosFTiempo,
    int (*piezasNecesarias)[MAX_PIEZAS_FIJO],
    char (*piezasProductos)[MAX_PIEZAS_FIJO][MAX_NOMBRE],
    int (*stockPiezas)[MAX_PIEZAS_FIJO],
    int (*tiemposPiezas)[MAX_PIEZAS_FIJO],
    char (*identificadoresUsados)[MAX_PIEZAS_FIJO][MAX_NOMBRE],
    int maxPiezas
    ) {
    printf("\n+--------------------------------------------------------------------------------------------+\n");
    printf("Producto seleccionado: %s\n", productos[producto]);
    printf("Stock actual de unidades terminadas: %d\n", stockProductos[producto]);
    printf("Tiempo de fabricacion promedio: %d minutos\n", productosFTiempo[producto]);
    printf("+----------+-------------------------+-------------------+---------+-------------------------+\n");
    printf("| Cantidad | Nombre                  | Identificador     |  Stock  |  Tiempo de Instalacion  |\n");
    printf("+----------+-------------------------+-------------------+---------+-------------------------+\n");
    for (int j = 0; j < maxPiezas; j++) {
        if (strlen(piezasProductos[producto][j]) != 0) {
            printf("| %8d | %-23s | %-17s | %-7d | %19d min |\n",
                piezasNecesarias[producto][j],
                piezasProductos[producto][j],
                identificadoresUsados[producto][j],
                stockPiezas[producto][j],
                tiemposPiezas[producto][j]
            );
        }
    }
    printf("+----------+-------------------------+-------------------+---------+-------------------------+\n");
}

void generarIdentificador(
    char* nombreProducto,
    char* nombrePieza,
    int cantidadPiezas,
    char identificadores[MAX_PIEZAS_FIJO][MAX_NOMBRE],
    char* identificadorGenerado
) {
    char base[10];
    int len = 0;

    base[len++] = nombreProducto[0];
    base[len++] = nombrePieza[0];
    base[len++] = nombrePieza[1];

    int tempCantidad = cantidadPiezas;
    char cantidadStr[6];
    int cantidadLen = 0;
    if (tempCantidad == 0) {
        cantidadStr[cantidadLen++] = '0';
    } else {
        int temp = tempCantidad, digits = 0;
        while (temp > 0) {
            temp /= 10;
            digits++;
        }
        cantidadLen = digits;
        cantidadStr[digits] = '\0';
        temp = tempCantidad;
        while (digits > 0) {
            cantidadStr[--digits] = (temp % 10) + '0';
            temp /= 10;
        }
    }
    for (int i = 0; i < cantidadLen; i++) {
        base[len++] = cantidadStr[i];
    }
    base[len] = '\0';

    int contador = 1;
    int duplicado = 0;
    char tempo[MAX_NOMBRE];

    do {
        int tempLen = 0;
        for (tempLen = 0; base[tempLen] != '\0'; tempLen++) {
            tempo[tempLen] = base[tempLen];
        }
        if (duplicado) {
            int c = contador;
            char numStri[6];
            int numLen = 0;
            if (c == 0) {
                numStri[numLen++] = '0';
            } else {
                int t = c, d = 0;
                while (t > 0) {
                    t /= 10;
                    d++;
                }
                numLen = d;
                numStri[d] = '\0';
                t = c;
                while (d > 0) {
                    numStri[--d] = (t % 10) + '0';
                    t /= 10;
                }
            }
            for (int i = 0; i < numLen; i++) {
                tempo[tempLen++] = numStri[i];
            }
        }
        tempo[tempLen] = '\0';

        duplicado = 0;
        for (int i = 0; i < cantidadPiezas; i++) {
            if (strcmp(tempo, identificadores[i]) == 0) {
                duplicado = 1;
                contador++;
                break;
            }
        }
    } while (duplicado);

    strcpy(identificadorGenerado, tempo);
}

int buscarPiezaPorIdentificador(int productoIndex, char (*piezas)[50], char *identificadorBuscado, int maxPiezas) {
    int coincidencias[maxPiezas];
    int count = 0;
    int seleccion;

    for (int i = 0; i < maxPiezas; i++) {
        if (strlen(piezas[i]) > 0) {
            int esPrefijo = 1;
            char *p1 = piezas[i];
            char *p2 = identificadorBuscado;
            while (*p2) {
                if (*p1 == '\0' || *p1 != *p2) {
                    esPrefijo = 0;
                    break;
                }
                p1++;
                p2++;
            }
            if (esPrefijo) {
                printf("%d. %s\n", count + 1, piezas[i]);
                coincidencias[count++] = i;
            }
        }
    }

    if (count == 0) {
        printf("No se encontraron coincidencias con ese prefijo.\n");
        return -1;
    }

    if (count == 1) {
        return coincidencias[0];
    }

    do {
        leerEnteroNoNegativo("Seleccione el número del elemento (0 para cancelar): ", &seleccion);
    } while (seleccion < 0 || seleccion > count);

    if (seleccion == 0){
        return -1;
    }

    return coincidencias[seleccion - 1];
}

void leerCadenaConEspacios(char* mensaje, char* destino, int max) {
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
