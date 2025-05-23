#include <stdio.h>

#define MAX_NOMBRE 50 // Tamaño máximo para nombres de productos y piezas
#define MAX_PRODUCTO_FIJO 100 // Tamaño máximo para productos
#define MAX_PIEZAS_FIJO 100 // Tamaño máximo para piezas

void limpiarBuffer();
void leerEnteroPositivo(char *mensaje, int *valor);
void leerEnteroNoNegativo(char *mensaje, int *valor);
void leerFlotantePositivo(char *mensaje, float *valor);
void leerCadena(char *mensaje, char *cadena, int max);
void leerCaracter(char *mensaje, char *caracter);

void recalcularTiemposProductos(
    int *productosFTiempo,
    int tiemposPiezas[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO],
    int totalProductos,
    int maxPiezas
);

void mostrarTiempo(int tiempo);

void mostrarTablaProductosPiezas(
    int producto, 
    char productos[MAX_PRODUCTO_FIJO][MAX_NOMBRE],
    int stockProductos[MAX_PRODUCTO_FIJO], 
    int totalProductos,
    int productosFTiempo[MAX_PRODUCTO_FIJO],
    int piezasNecesarias[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO],
    char piezasProductos[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO][MAX_NOMBRE],
    int stockPiezas[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO],
    int tiemposPiezas[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO],
    char identificadoresUsados[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO][MAX_NOMBRE],
    int maxPiezas
);

void generarIdentificador(
    char* nombreProducto,
    char* nombrePieza,
    int cantidadPiezas,
    char identificadoresGlobal[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO][MAX_NOMBRE],
    int totalProductos,
    char* identificadorGenerado
);


int buscarPiezaPorIdentificador(
    int productoIndex,
    char (*piezas)[MAX_NOMBRE],
    char* identificadorBuscado,
    int maxPiezas
);

void leerCadenaConEspacios(char* mensaje, char* destino, int max);
int agregarIdentificadorProducto(char* nombreProducto, int numero);
