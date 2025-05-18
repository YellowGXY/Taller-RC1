#include <stdio.h>

#define MAX_NOMBRE 50
#define MAX_PRODUCTO 20
#define MAX_PIEZAS 20

void limpiarBuffer();
void leerEnteroPositivo(char *mensaje, int *valor);
void leerEnteroNoNegativo(char *mensaje, int *valor);
void leerFlotantePositivo(char *mensaje, float *valor);
void leerCadena(char *mensaje, char *cadena, int max);
void leerCaracter(char *mensaje, char *caracter);
void recalcularTiemposProductos(int *productosFTiempo, int (*tiemposPiezas)[MAX_PIEZAS], int totalProductos);
void mostrarTiempo(int tiempo);