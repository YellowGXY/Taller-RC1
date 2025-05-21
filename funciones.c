#include <stdio.h>
#include <string.h>
#include "funciones.h"

// Limpia el buffer de entrada hasta encontrar un salto de línea.
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n');
}

// Lee un entero positivo.
// Muestra un mensaje, valida la entrada y repite hasta que sea válida y positiva.
void leerEnteroPositivo(char *mensaje, int *destino) {
    int valido;
    char c;
    do {
        valido = 1;
        printf("%s", mensaje);
        // Intenta leer un entero
        if (scanf("%d", destino) != 1) {
            printf("Entrada no valida. Intente nuevamente.\n\n");
            valido = 0;
        }
        limpiarBuffer();
        // Verifica que el valor sea positivo
        if (valido && *destino <= 0) {
            printf("El valor debe ser positivo.\n\n");
            valido = 0;
        }
    } while (!valido || *destino <= 0);
}

// Lee un entero no negativo.
// Similar a leerEnteroPositivo, pero permite el valor cero.
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

// Lee un número flotante positivo.
// Valida que la entrada sea un número y que sea mayor a cero.
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

// Lee una cadena de caracteres.
// Elimina espacios al inicio y al final, y valida que la entrada no esté vacía.
void leerCadena(char* mensaje, char* destino, int max) {
    int valido = 0;
    while (!valido) {
        printf("%s", mensaje);
        if (fgets(destino, max, stdin) != 0) {
            // Elimina el salto de línea final
            destino[strcspn(destino, "\n")] = '\0';

            // Elimina espacios al inicio
            char* inicio = destino;
            while (*inicio == ' ') {
                inicio++;
            }	

            // Elimina espacios al final
            char* fin = destino + strlen(destino) - 1;
            while (fin >= inicio && *fin == ' ') {
                *fin = '\0';
                fin--;
            }

            // Valida que la cadena no esté vacía
            if (strlen(inicio) == 0) {
                printf("Invalido. Intente de nuevo.\n");
            } else {
                // Si hubo espacios al inicio, mueve la cadena al principio
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

// Lee un solo caracter.
// Valida que no sea un salto de línea, vacío ni un espacio.
void leerCaracter(char* mensaje, char* destino) {
    int valido = 0;
    int ch;
    int siguiente;

    while (!valido) {
        printf("%s", mensaje);
        ch = getchar();

        if (ch != '\n' && ch != ' ') {
            siguiente = getchar();
            if (siguiente == '\n') {
                *destino = ch;  
                valido = 1;
            } else {
                printf("Ingrese solo un caracter valido (sin espacios).\n");
                limpiarBuffer();
            }
        } else {
            limpiarBuffer();
            printf("Ingrese solo un caracter valido (sin espacios).\n");
        }
    }
}

// Recalcula el tiempo total de fabricación de cada producto sumando los tiempos de sus piezas.
// Actualiza el arreglo productosFTiempo con la suma de los tiempos de cada pieza.
void recalcularTiemposProductos(int *productosFTiempo, int (*tiemposPiezas)[MAX_PIEZAS_FIJO], int totalProductos, int maxPiezas) {
    for (int i = 0; i < totalProductos; i++) {
        int suma = 0;
        for (int j = 0; j < maxPiezas; j++) {
            suma += tiemposPiezas[i][j];
        }
        productosFTiempo[i] = suma;
    }
}

// Muestra el tiempo total en años, meses, semanas, días, horas y minutos.
void mostrarTiempo(int minutosTotales) {
    int anios = minutosTotales / 525600; // 525600 minutos en un año (365 días)
    minutosTotales = minutosTotales % 525600;

    int meses = minutosTotales / 43200; // 43200 minutos en un mes (30 días)
    minutosTotales = minutosTotales % 43200;

    int semanas = minutosTotales / 10080; // 10080 minutos en una semana
    minutosTotales = minutosTotales % 10080;

    int dias = minutosTotales / 1440; // 1440 minutos en un día
    minutosTotales = minutosTotales % 1440;

    int horas = minutosTotales / 60; // 60 minutos en una hora
    int minutos = minutosTotales % 60;

    printf("   ");

    // Imprime años si corresponde
    if (anios > 0) {
        printf("%d ", anios);
        if (anios == 1) {
            printf("anio ");
        } else {
            printf("anios ");
        }
    }

    // Imprime meses si corresponde
    if (meses > 0) {
        printf("%d ", meses);
        if (meses == 1) {
            printf("mes ");
        } else {
            printf("meses ");
        }
    }

    // Imprime semanas si corresponde
    if (semanas > 0) {
        printf("%d ", semanas);
        if (semanas == 1) {
            printf("semana ");
        } else {
            printf("semanas ");
        }
    }

    // Imprime días si corresponde
    if (dias > 0) {
        printf("%d ", dias);
        if (dias == 1) {
            printf("dia ");
        } else {
            printf("dias ");
        }
    }

    // Imprime horas si corresponde
    if (horas > 0) {
        printf("%d ", horas);
        if (horas == 1) {
            printf("hora ");
        } else {
            printf("horas ");
        }
    }

    // Imprime minutos si corresponde
    if (minutos > 0) {
        printf("%d ", minutos);
        if (minutos == 1) {
            printf("minuto");
        } else {
            printf("minutos");
        }
    }

    // Si todo es cero, imprime "0 minutos"
    if (anios == 0 && meses == 0 && semanas == 0 && dias == 0 && horas == 0 && minutos == 0) {
        printf("0 minutos (posiblemente sin tiempo agregado)");
    }

    printf("\n");
}

// Muestra una tabla con la información de las piezas necesarias para un producto.
// Incluye identificador, nombre, cantidad, stock y tiempo de instalación de cada pieza.
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

// Genera un identificador único para una pieza de un producto.
// Usa la primera letra del producto, las dos primeras de la pieza y la cantidad.
// Si ya existe, agrega un número incremental hasta que sea único.
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

    // Primera letra del producto
    base[len++] = nombreProducto[0];

    // Dos primeras letras de la pieza
    if (strlen(nombrePieza) >= 2) {
        base[len++] = nombrePieza[0];
        base[len++] = nombrePieza[1];
    } else if (strlen(nombrePieza) == 1) {
        base[len++] = nombrePieza[0];
        base[len++] = 'X'; // agrega un carácter de relleno si el nombre es corto
    } else {
        base[len++] = 'X'; // agrega un carácter de relleno si el nombre es vacío
        base[len++] = 'X'; // agrega un carácter de relleno si el nombre es vacío
    }

    // Convierte la cantidad a string y la agrega
    char cantidadStr[12];
    int cantidad = cantidadPiezas;
    int cantidadLen = 0;
    if (cantidad == 0) {
        cantidadStr[cantidadLen++] = '0'; // si la cantidad es cero
    } else {
        int temp = cantidad; 
        char rev[12];
        int revLen = 0;
        while (temp > 0) {
            rev[revLen++] = (temp % 10) + '0'; // convierte a char
            temp /= 10;
        }
        for (int i = revLen - 1; i >= 0; i--) {
            cantidadStr[cantidadLen++] = rev[i]; // invierte el orden
        }
    }
    cantidadStr[cantidadLen] = '\0'; // termina la cadena

    for (int i = 0; i < cantidadLen; i++) {
        base[len++] = cantidadStr[i]; // agrega la cantidad al identificador
    }
    base[len] = '\0';

    // Busca un identificador único
    int repetido = 1;
    char tempID[MAX_NOMBRE];

    while (1) {
        int tempLen = 0;
        for (int i = 0; base[i] != '\0'; i++) {
            tempID[tempLen++] = base[i]; // copia la base
        }
        int rep = repetido;
        char repStr[12];
        int repLen = 0;
        if (rep == 0) {
            repStr[repLen++] = '0'; // si no hay repetidos
        } else {
            char revRep[12];
            int revRepLen = 0;
            while (rep > 0) {
                revRep[revRepLen++] = (rep % 10) + '0'; // convierte a char
                rep /= 10; 
            }
            for (int i = revRepLen - 1; i >= 0; i--) {
                repStr[repLen++] = revRep[i]; // invierte el orden
            }
        }
        repStr[repLen] = '\0';
        for (int i = 0; i < repLen; i++) {
            tempID[tempLen++] = repStr[i]; // agrega el número de repetidos
        }
        tempID[tempLen] = '\0';

        // Verifica si el identificador ya existe
        int existe = 0;
        for (int i = 0; i < totalProductos; i++) {
            for (int j = 0; j < MAX_PIEZAS_FIJO; j++) {
                if (strcmp(identificadoresGlobal[i][j], tempID) == 0) { // compara cadenas
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

    // Copia el identificador generado al destino
    strcpy(identificadorGenerado, tempID);
}

// Busca una pieza por su identificador (o prefijo) en el arreglo de piezas.
// Si hay varias coincidencias, permite al usuario seleccionar una.
int buscarPiezaPorIdentificador(int productoIndex, char (*piezas)[50], char *identificadorBuscado, int maxPiezas) {
    int coincidencias[maxPiezas];
    int count = 0;
    int seleccion;

    // Busca coincidencias por prefijo
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
                printf("%d. %s\n", count + 1, piezas[i]); // Muestra la coincidencia
                coincidencias[count++] = i;
            }
        }
    }

    // Si no hay coincidencias, retorna -1
    if (count == 0) {
        printf("No se encontraron coincidencias con ese prefijo.\n");
        return -1;
    }

    // Si solo hay una coincidencia, la retorna
    if (count == 1) {
        return coincidencias[0];
    }

    // Si hay varias, pide al usuario seleccionar una
    do {
        leerEnteroNoNegativo("Seleccione el numero del elemento (0 para cancelar): ", &seleccion);
    } while (seleccion < 0 || seleccion > count);

    if (seleccion == 0){
        return -1; 
    }

    return coincidencias[seleccion - 1]; // Retorna la coincidencia seleccionada
}

// Lee una cadena de caracteres (permitiendo espacios vacios).
void leerCadenaConEspacios(char* mensaje, char* destino, int max) {
    int valido = 0;
    while (!valido) {
        printf("%s", mensaje);
        if (fgets(destino, max, stdin) != 0) {
            destino[strcspn(destino, "\n")] = '\0';

            char* inicio = destino;
            while (*inicio == ' ') {
                inicio++; // Elimina espacios al inicio
            }	

            char* fin = destino + strlen(destino) - 1;
            while (fin >= inicio && *fin == ' ') { // Elimina espacios al final
                *fin = '\0'; 
                fin--;
            }

            if (inicio != destino) {
                int i = 0;
                while (inicio[i]) {
                    destino[i] = inicio[i]; // Mueve la cadena al principio
                    i++;
                }
                destino[i] = '\0'; // Termina la cadena
            }
            valido = 1;
        }
    }
}

// Agrega un identificador al nombre de un producto, en el formato " -Pr#NNN".
// Retorna 1 si se pudo agregar, 0 si el nombre resultante sería demasiado largo.
int agregarIdentificadorProducto(char* nombreProducto, int numero) {
    char identificador[15];
    int len = 0;

    identificador[len++] = ' ';
    identificador[len++] = '-';
    identificador[len++] = 'P';
    identificador[len++] = 'r';
    identificador[len++] = '#';

    // Convierte el número a string de 3 caracteres
    char numStr[5];
    int n = numero;
    numStr[0] = (n / 100) % 10 + '0'; // Primer carácter
    numStr[1] = (n / 10) % 10 + '0'; // Segundo carácter
    numStr[2] = n % 10 + '0'; // Tercer carácter
    numStr[3] = '\0'; // Termina la cadena

    for (int i = 0; numStr[i] != '\0'; i++) {
        identificador[len++] = numStr[i]; // Agrega el número al identificador
    }

    identificador[len] = '\0';

    // Verifica que el nombre resultante no exceda el máximo permitido
    if (strlen(nombreProducto) + strlen(identificador) < MAX_NOMBRE) {
        strcat(nombreProducto, identificador); // Agrega el identificador al nombre del producto
        return 1;
    } else {
        printf("No se pudo agregar identificador al nombre del producto (demasiado largo).\n");
        return 0;
    }
}
