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
    printf("+-----------------+-------------------------+--------------------+---------+-------------------------+\n");
    printf("| Identificador   | Nombre                  | Cantidad Necesaria |  Stock  |  Tiempo de Instalacion  |\n");
    printf("+-----------------+-------------------------+--------------------+---------+-------------------------+\n");
    for (int j = 0; j < maxPiezas; j++) {
        if (strlen(piezasProductos[producto][j]) != 0) {
            printf("| %-15s | %-23s | %-18d | %-7d | %19d min |\n",
                identificadoresUsados[producto][j],
                piezasProductos[producto][j],
                piezasNecesarias[producto][j],
                stockPiezas[producto][j],
                tiemposPiezas[producto][j]
            );
        }
    }
    printf("+-----------------+-------------------------+--------------------+---------+-------------------------+\n");
}

void generarIdentificador(
    char* nombreProducto,
    char* nombrePieza,
    int cantidadPiezas,
    char identificadoresGlobal[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO][MAX_NOMBRE],
    int totalProductos,
    char* identificadorGenerado
) {
    char base[20];
    int len = 0;

    base[len++] = nombreProducto[0];

    if (strlen(nombrePieza) >= 2) {
        base[len++] = nombrePieza[0];
        base[len++] = nombrePieza[1];
    } else if (strlen(nombrePieza) == 1) {
        base[len++] = nombrePieza[0];
        base[len++] = 'X';
    } else {
        base[len++] = 'X';
        base[len++] = 'X';
    }

    char cantidadStr[12];
    int cantidad = cantidadPiezas;
    int cantidadLen = 0;
    if (cantidad == 0) {
        cantidadStr[cantidadLen++] = '0';
    } else {
        int temp = cantidad;
        char rev[12];
        int revLen = 0;
        while (temp > 0) {
            rev[revLen++] = (temp % 10) + '0';
            temp /= 10;
        }
        for (int i = revLen - 1; i >= 0; i--) {
            cantidadStr[cantidadLen++] = rev[i];
        }
    }
    cantidadStr[cantidadLen] = '\0';

    for (int i = 0; i < cantidadLen; i++) {
        base[len++] = cantidadStr[i];
    }
    base[len] = '\0';

    int repetido = 1;
    char tempID[MAX_NOMBRE];

    while (1) {
        int tempLen = 0;
        for (int i = 0; base[i] != '\0'; i++) {
            tempID[tempLen++] = base[i];
        }
        int rep = repetido;
        char repStr[12];
        int repLen = 0;
        if (rep == 0) {
            repStr[repLen++] = '0';
        } else {
            char revRep[12];
            int revRepLen = 0;
            while (rep > 0) {
                revRep[revRepLen++] = (rep % 10) + '0';
                rep /= 10;
            }
            for (int i = revRepLen - 1; i >= 0; i--) {
                repStr[repLen++] = revRep[i];
            }
        }
        repStr[repLen] = '\0';
        for (int i = 0; i < repLen; i++) {
            tempID[tempLen++] = repStr[i];
        }
        tempID[tempLen] = '\0';

        int existe = 0;
        for (int i = 0; i < totalProductos; i++) {
            for (int j = 0; j < MAX_PIEZAS_FIJO; j++) {
                if (strcmp(identificadoresGlobal[i][j], tempID) == 0) {
                    existe = 1;
                    break;
                }
            }
            if (existe) break;
        }

        if (!existe) {
            break;
        }
        repetido++;
    }

    strcpy(identificadorGenerado, tempID);
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
        leerEnteroNoNegativo("Seleccione el numero del elemento (0 para cancelar): ", &seleccion);
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

int agregarIdentificadorProducto(char* nombreProducto, int numero) {
    char identificador[15];
    int len = 0;

    identificador[len++] = ' ';
    identificador[len++] = '-';
    identificador[len++] = 'P';
    identificador[len++] = 'r';
    identificador[len++] = '#';

    char numStr[5];
    int n = numero;
    numStr[0] = (n / 100) % 10 + '0';
    numStr[1] = (n / 10) % 10 + '0';
    numStr[2] = n % 10 + '0';
    numStr[3] = '\0';

    for (int i = 0; numStr[i] != '\0'; i++) {
        identificador[len++] = numStr[i];
    }

    identificador[len] = '\0';

    if (strlen(nombreProducto) + strlen(identificador) < MAX_NOMBRE) {
        strcat(nombreProducto, identificador);
        return 1;
    } else {
        printf("No se pudo agregar identificador al nombre del producto (demasiado largo).\n");
        return 0;
    }
}
