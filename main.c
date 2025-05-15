#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    char productos[MAX_PRODUCTO][MAX_NOMBRE] = {"Celulares", "Laptops", "Tablets", "Audifonos Inalambricos", "Smartwatches"};
    int productosFTiempo[MAX_PRODUCTO] = {30, 60, 45, 20, 25};

    char piezasProductos[MAX_PRODUCTO][MAX_PIEZAS][MAX_NOMBRE] = {
        {"Pantalla", "Bateria", "Carcasa", "Procesador", "Camara"},
        {"Pantalla", "Teclado", "Bateria", "Placa Base", "Ventilador"},
        {"Pantalla", "Bateria", "Procesador", "Carcasa", "Puerto USB-C"},
        {"Auri Izq", "Auri Der", "Bateria", "Bluetooth", "Microfono"},
        {"Pantalla", "Bateria", "Correa", "Sensor", "Procesador"}
    };

    int tiemposPiezas[MAX_PRODUCTO][MAX_PIEZAS] = {
        {10, 5, 7, 8, 5},
        {12, 6, 8, 10, 6},
        {10, 5, 7, 6, 4},
        {3, 3, 2, 4, 3},
        {5, 4, 3, 4, 5}
    };

    int stockPiezas[MAX_PRODUCTO][MAX_PIEZAS] = {
        {100, 80, 90, 85, 70},
        {60, 65, 55, 50, 45},
        {75, 80, 70, 65, 60},
        {100, 100, 100, 90, 80},
        {85, 90, 95, 70, 65}
    };

    int piezasNecesarias[MAX_PRODUCTO][MAX_PIEZAS] = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };

    int totalProductos = 5;
    int totalPiezas[MAX_PRODUCTO] = {5, 5, 5, 5, 5};
    int opcion;

    do {
        printf("\n====================================\n");
        printf("========= MENU DE OPCIONES =========\n");
        printf("1. Registrar producto\n");
        printf("2. Editar productos\n");
        printf("3. Eliminar producto\n");
        printf("4. Mostrar productos\n");
        printf("5. Analizar produccion\n");
        printf("6. Agregar stock de piezas\n");
        printf("0. Salir\n");
        printf("====================================\n");

        leerEnteroNoNegativo("Seleccione una opcion: ", &opcion);

        printf("=====================================\n");
        switch (opcion) {
            case 1: {
                if (totalProductos >= MAX_PRODUCTO) {
                    printf("No se pueden registrar mas productos.\n");
                    break;
                }

                printf("\n===== REGISTRAR NUEVO PRODUCTO =====\n");

                printf("Productos actuales:\n");
                for (int i = 0; i < totalProductos; i++) {
                    printf("%d. %s\n", i + 1, productos[i]);
                }

                printf("Espacios disponibles: %d de %d\n", MAX_PRODUCTO - totalProductos, MAX_PRODUCTO);

                int cantidad;
                leerEnteroNoNegativo("Cuantos productos desea registrar? (0 para salir) ", &cantidad);

                if (cantidad == 0) {
                    printf("Registro de productos cancelado.\n");
                    break;
                }

                if (cantidad > MAX_PRODUCTO - totalProductos) {
                    printf("No hay suficiente espacio para registrar %d productos.\n", cantidad);
                    break;
                }

                printf("Se registrara %d productos.\n", cantidad);
                for (int i = 0; i < cantidad && totalProductos < MAX_PRODUCTO; i++, totalProductos++) {
                int nombreValido;
                do {
                    nombreValido = 1;
                    leerCadena("Ingrese nombre del nuevo producto: ", productos[totalProductos], MAX_NOMBRE);

                    for (int j = 0; j < totalProductos; j++) {
                        if (strcmp(productos[totalProductos], productos[j]) == 0) {
                            printf("Ya existe un producto con ese nombre. Intente otro.\n");
                            nombreValido = 0;
                            break;
                        }
                    }
                } while (!nombreValido);

                int piezas;
                leerEnteroPositivo("Cuantas piezas desea registrar para el producto? (10 maximo): ", &piezas);
                printf("Se registraran %d piezas.\n", piezas);
                if (piezas > 10) {
                    printf("No se pueden registrar mas de 10 piezas.\n");
                    break;
                } else if (piezas <= 0) {
                    printf("No se pueden registrar menos de 1 pieza.\n");
                    break;
                }

                int tiempoTotal = 0;
                for (int j = 0; j < piezas; j++) {
                    printf("Pieza %d:\n", j + 1);
                    leerCadena("Nombre de la pieza: ", piezasProductos[totalProductos][j], MAX_NOMBRE);

                    leerEnteroPositivo("Tiempo de instalacion (minutos): ", &tiemposPiezas[totalProductos][j]);
                    leerEnteroNoNegativo("Stock inicial: ", &stockPiezas[totalProductos][j]);
                    leerEnteroPositivo("Cantidad necesaria por unidad: ", &piezasNecesarias[totalProductos][j]);

                    tiempoTotal += tiemposPiezas[totalProductos][j];
                    totalPiezas[totalProductos]++;
                    if (totalPiezas[totalProductos] > 10) {
                        printf("Solo se pueden registrar hasta 10 piezas por producto.\n");
                        break;
                    }
                }
                productosFTiempo[totalProductos] = tiempoTotal;  
                printf("Producto registrado exitosamente.\n");
                
                char respuesta;
                leerCaracter("Desea registrar otro producto? (S para continuar, N para salir):", &respuesta);
                totalProductos++;
                if (respuesta == 'N' || respuesta == 'n') {
                    printf("Registro de productos finalizado.\n");
                    break;
                }
            }
            printf("=====================================\n");
                break;
            }

            case 2: {
                if (totalProductos == 0) {
                    printf("No hay productos registrados.\n");
                    break;
                }

                int salirEdicion = 0;
                do {
                    printf("===== EDITAR PRODUCTOS =====\n");
                    for (int i = 0; i < totalProductos; i++) {
                        printf("%d. %s\n", i + 1, productos[i]);
                    }

                    int producto;
                    leerEnteroNoNegativo("Seleccione producto a editar (0 para salir): ", &producto);

                    if (producto == 0 || producto > totalProductos){
                        salirEdicion = 1;
                        break;
                    }
                    producto--;
                    printf("Producto seleccionado: %s\n", productos[producto]);
                    printf("Tiempo de fabricacion promedio: %d minutos\n", productosFTiempo[producto]);
                    printf("+----------+-------------------------+---------+-------------------------+\n");
                    printf("| Cantidad | Nombre                  |  Stock  |  Tiempo de Instalacion  |\n");
                    printf("+----------+-------------------------+---------+-------------------------+\n");
                    for (int j = 0; j < MAX_PIEZAS; j++) {
                        if (strlen(piezasProductos[producto][j]) != 0){ 
                            printf("| %8d | %-23s | %6d | %22d |\n",
                                piezasNecesarias[producto][j],
                                piezasProductos[producto][j],
                                stockPiezas[producto][j],
                                tiemposPiezas[producto][j]
                            );
                        }
                    }
                    printf("+----------+--------------------------+---------+-------------------------+\n");
                    printf("=====================================\n");
                    printf("Opciones de edicion:\n");
                    printf("1. Cambiar nombre\n");
                    printf("2. Editar/Agregar piezas\n");
                    printf("3. Cambiar cantidad de piezas necesarias por unidad\n");
                    printf("0. Cancelar\n");
                    printf("=====================================\n");
                    int ed;
                    leerEnteroNoNegativo("Seleccione opcion: ", &ed);
                    if (ed == 0) {
                        printf("Edicion cancelada.\n");
                        continue;
                    }

                    if (ed == 1) {
                        char nuevoNombre[MAX_NOMBRE];
                        int nombreValido;
                        do {
                            nombreValido = 1;
                            leerCadena("Nuevo nombre: ", nuevoNombre, MAX_NOMBRE);

                            for (int i = 0; i < totalProductos; i++) {
                                if (i != producto && strcmp(nuevoNombre, productos[i]) == 0) {
                                    printf("Ya existe un producto con ese nombre. Intente otro.\n");
                                    nombreValido = 0;
                                    break;
                                }
                            }
                        } while (!nombreValido);
                        strcpy(productos[producto], nuevoNombre);
                    } else if (ed == 2) {
                        printf("Seleccione la pieza a editar:\n");
                        for (int j = 0; j < MAX_PIEZAS; j++) {
                            if (strlen(piezasProductos[producto][j]) != 0) {
                                printf("%d. %s\n", j + 1, piezasProductos[producto][j]);
                            } else {
                                char dis[MAX_NOMBRE] = "--Espacio Disponible--";
                                printf("%d. %s\n", j + 1, dis);
                            }
                        }
                        int pieza;
                        leerEnteroNoNegativo("Numero de pieza (0 para cancelar): ", &pieza);
                        if (pieza == 0 || pieza > MAX_PIEZAS) {
                            printf("Edicion de pieza cancelada.\n");
                            continue;
                        }
                        pieza--;
                        printf("Pieza seleccionada: %s\n", piezasProductos[producto][pieza]);
                        printf("Opciones de edicion para la pieza:\n");
                        printf("1. Cambiar nombre\n");
                        printf("2. Cambiar tiempo de instalacion\n");
                        printf("3. Cambiar Piezas necesarias por unidad\n");
                        printf("4. Cambiar TODO\n");
                        printf("0. Cancelar\n");
                        int opPieza;
                        do {
                            leerEnteroNoNegativo("Seleccione opcion: ", &opPieza);
                            if (opPieza < 0 || opPieza > 4) {
                                printf("Opcion invalida. Intente nuevamente.\n");
                            }
                        } while (opPieza < 0 || opPieza > 4);
                        if (opPieza == 0) {
                            printf("Edicion de pieza cancelada.\n");
                            continue;
                        }
                        if (opPieza == 1) {
                            leerCadena("Nuevo nombre: ", piezasProductos[producto][pieza], MAX_NOMBRE);
                        } else if (opPieza == 2) {
                            leerEnteroPositivo("Nuevo tiempo de instalacion: ", &tiemposPiezas[producto][pieza]);
                        } else if (opPieza == 3) {
                            leerEnteroPositivo("Nueva cantidad necesaria por unidad: ", &piezasNecesarias[producto][pieza]);
                        } else if (opPieza == 4) {
                            leerCadena("Nuevo nombre: ", piezasProductos[producto][pieza], MAX_NOMBRE);
                            leerEnteroPositivo("Nuevo tiempo de instalacion: ", &tiemposPiezas[producto][pieza]);
                            leerEnteroPositivo("Nueva cantidad necesaria por unidad: ", &piezasNecesarias[producto][pieza]);
                        } else {
                            printf("Opcion invalida.\n");
                            continue;
                        }
                        int nuevoTiempoTotal = 0;
                        for (int j = 0; j < MAX_PIEZAS; j++) {
                            nuevoTiempoTotal += tiemposPiezas[producto][j];
                        }
                        productosFTiempo[producto] = nuevoTiempoTotal;
                        printf("Tiempo promedio de fabricacion actualizado automaticamente: %d minutos\n", nuevoTiempoTotal);
                    } else if (ed == 3) {
                        printf("Seleccione la pieza para cambiar la cantidad necesaria:\n");
                        for (int j = 0; j < MAX_PIEZAS; j++) {
                            printf("%d. %s (Cantidad actual: %d)\n", j + 1, piezasProductos[producto][j], piezasNecesarias[producto][j]);
                        }
                        int pieza;
                        leerEnteroNoNegativo("Numero de pieza (0 para cancelar): ", &pieza);
                        if (pieza == 0 || pieza > MAX_PIEZAS) {
                            printf("Edicion de cantidad cancelada.\n");
                            break;
                        }
                        pieza--;
                        printf("Pieza seleccionada: %s\n", piezasProductos[producto][pieza]);
                        leerEnteroPositivo("Nueva cantidad necesaria por unidad: ", &piezasNecesarias[producto][pieza]);
                    } else {
                        printf("Opcion invalida.\n");
                    }
                } while (!salirEdicion);

                break;
            }

            case 3: {
                if (totalProductos == 0) {
                    printf("No hay productos registrados. Registre al menos uno primero.\n");
                    break;
                }

                char busqueda[MAX_NOMBRE];
                printf("Ingrese el nombre del producto a buscar (deje vacio para ver todos): ");
                fgets(busqueda, sizeof(busqueda), stdin);
                int len = strlen(busqueda);
                if (len > 0 && busqueda[len - 1] == '\n') {
                    busqueda[len - 1] = '\0';
                }

                int encontrados[MAX_PRODUCTO];
                int cantidadEncontrados = 0;

                if (strlen(busqueda) == 0) {
                    printf("Lista de todos los productos:\n");
                    for (int i = 0; i < totalProductos; i++) {
                        printf("%d. %s\n", i + 1, productos[i]);
                        encontrados[cantidadEncontrados++] = i;
                    }
                } else {
                    for (int i = 0; i < totalProductos; i++) {
                        if (strcmp(productos[i], busqueda) == 0) {
                            encontrados[cantidadEncontrados++] = i;
                        }
                    }
                }

                if (cantidadEncontrados == 0) {
                    printf("No se encontraron productos con ese nombre.\n");
                    break;
                }

                if (strlen(busqueda) != 0) {
                    printf("Productos encontrados:\n");
                    for (int i = 0; i < cantidadEncontrados; i++) {
                        printf("%d. %s\n", i + 1, productos[encontrados[i]]);
                    }
                }

                int seleccion;
                printf("Seleccione el numero del producto a eliminar (0 para salir): ");
                leerEnteroNoNegativo("Numero de producto: ", &seleccion);

                if (seleccion == 0 || seleccion > cantidadEncontrados) {
                    break;
                }

                printf("Desea eliminar piezas o el producto?\n");
                printf("1. Eliminar piezas\n");
                printf("2. Eliminar producto\n");
                printf("0. Salir\n");
                int eliminar;
                leerEnteroNoNegativo("Seleccione opcion: ", &eliminar);
                if (eliminar == 0) {
                    printf("Eliminacion cancelada.\n");
                    break;
                } else if (eliminar == 1) {

                    printf("Que pieza desea eliminar?\n");
                    for (int i = 0; i < MAX_PIEZAS; i++) {
                        if (strlen(piezasProductos[encontrados[seleccion - 1]][i]) > 0) {
                            printf("%d. %s\n", i + 1, piezasProductos[encontrados[seleccion - 1]][i]);
                        }
                    }

                    int pieza;
                    leerEnteroNoNegativo("Seleccione pieza a eliminar (0 para salir): ", &pieza);
                    if (pieza == 0 || pieza > MAX_PIEZAS) {
                        printf("Eliminacion de pieza cancelada.\n");
                        break;
                    }
                    pieza--;

                    printf("Esta seguro que desea eliminar la pieza %s? (S para confirmar, N para cancelar): ", piezasProductos[encontrados[seleccion - 1]][pieza]);
                    char confirmacion;
                    leerCaracter("Confirmacion: ", &confirmacion);
                    if (confirmacion != 'S' && confirmacion != 's') {
                        printf("Eliminacion de pieza cancelada.\n");
                        break;
                    }

                    printf("Pieza seleccionada: %s\n", piezasProductos[encontrados[seleccion - 1]][pieza]);
                    strcpy(piezasProductos[encontrados[seleccion - 1]][pieza], "");
                    tiemposPiezas[encontrados[seleccion - 1]][pieza] = 0;
                    stockPiezas[encontrados[seleccion - 1]][pieza] = 0;
                    piezasNecesarias[encontrados[seleccion - 1]][pieza] = 0;
                    totalPiezas[encontrados[seleccion - 1]]--;
                    printf("Pieza eliminada.\n");
                    break;
                } else if (eliminar == 2) {
                    printf("Esta seguro que desea eliminar el producto %s? (S para confirmar, N para cancelar): ", productos[encontrados[seleccion - 1]]);
                    char confirmacion;
                    leerCaracter("Confirmacion: ", &confirmacion);
                    if (confirmacion != 'S' && confirmacion != 's') {
                        printf("Eliminacion de producto cancelada.\n");
                        break;
                    }
                    int producto = encontrados[seleccion - 1];

                    if (producto >= 0 && producto < totalProductos) {
                        for (int i = producto; i < totalProductos - 1; i++) {
                            strcpy(productos[i], productos[i + 1]);
                            productosFTiempo[i] = productosFTiempo[i + 1];
                            for (int j = 0; j < MAX_PIEZAS; j++) {
                                strcpy(piezasProductos[i][j], piezasProductos[i + 1][j]);
                                tiemposPiezas[i][j] = tiemposPiezas[i + 1][j];
                                stockPiezas[i][j] = stockPiezas[i + 1][j];
                                piezasNecesarias[i][j] = piezasNecesarias[i + 1][j];
                            }
                        }
                        strcpy(productos[totalProductos - 1], "");
                        productosFTiempo[totalProductos - 1] = 0;
                        for (int j = 0; j < MAX_PIEZAS; j++) {
                            strcpy(piezasProductos[totalProductos - 1][j], "");
                            tiemposPiezas[totalProductos - 1][j] = 0;
                            stockPiezas[totalProductos - 1][j] = 0;
                            piezasNecesarias[totalProductos - 1][j] = 0;
                        }
                        totalProductos--;
                        printf("Producto eliminado.\n");
                    }

                } else {
                    printf("Producto seleccionado no es valido.\n");
                }
                break;
            }

            case 4: {
                if (totalProductos == 0) {
                    printf("No hay productos registrados. Registre al menos uno primero.\n");
                    break;
                }
                printf("===== PRODUCTOS =====\n");
                for (int i = 0; i < totalProductos; i++) {
                    printf("\n%d. %s\n", i + 1, productos[i]);
                    printf("   Tiempo de fabricacion promedio: %d minutos\n", productosFTiempo[i]);
                    printf("+----------+-------------------------+---------+-------------------------+\n");
                    printf("| Cantidad | Nombre                  |  Stock  |  Tiempo de Instalacion  |\n");
                    printf("+----------+-------------------------+---------+-------------------------+\n");
                    for (int j = 0; j < MAX_PIEZAS; j++) {
                        if (strlen(piezasProductos[i][j]) != 0) {
                            printf("| %8d | %-23s | %6d | %22d |\n",
                                piezasNecesarias[i][j],
                                piezasProductos[i][j],
                                stockPiezas[i][j],
                                tiemposPiezas[i][j]
                            );
                        }
                    }
                    printf("+----------+--------------------------+---------+-------------------------+\n");
                }
                break;
            }

            case 5: {
                if (totalProductos == 0) {
                    printf("No hay productos registrados. Registre al menos uno primero.\n");
                    break;
                }
                printf("===== ANALISIS DE PRODUCCION =====\n");

                for (int i = 0; i < totalProductos; i++) {
                    printf("%d. %s\n", i + 1, productos[i]);
                }

                int producto;
                leerEnteroNoNegativo("Seleccione producto (0 para salir): ", &producto);
                if (producto == 0 || producto > totalProductos) {
                    break;
               
                }
                producto--;

                int minFabricables = -1;
                for (int p = 0; p < MAX_PIEZAS; p++) {
                    int necesarias = piezasNecesarias[producto][p];
                    if (necesarias == 0){
                        necesarias = 1;
                    }
                    int posibles = stockPiezas[producto][p] / necesarias;
                    if (posibles > minFabricables) {
                        minFabricables = posibles;
                    }
                }

                int tiempoTotal = 0;
                for (int p = 0; p < MAX_PIEZAS; p++) {
                    tiempoTotal += tiemposPiezas[producto][p];
                }

                if (minFabricables <= 0) {
                    printf("No es posible fabricar unidades con el stock actual.\n");
                } else {
                    printf("-> Tiempo total por unidad: %d minutos\n", tiempoTotal);

                    int tiempoDisponible;
                    leerEnteroNoNegativo("Ingrese tiempo disponible (en minutos): ", &tiempoDisponible);
                    int porTiempo;
                    if (tiempoTotal > 0) {
                        porTiempo = tiempoDisponible / tiempoTotal;
                    } else {
                        porTiempo = 0;
                    }

                    int maxFinal = (porTiempo < minFabricables) ? porTiempo : minFabricables;
                    printf("-> Unidades maximas en ese tiempo: %d\n", maxFinal);

                    if (maxFinal < porTiempo) {
                        printf("-> Faltan piezas para producir mas:\n");
                        for (int p = 0; p < MAX_PIEZAS; p++) {
                            int faltan = (porTiempo * piezasNecesarias[producto][p]) - stockPiezas[producto][p];
                            if (faltan > 0) {
                                printf("   - %s: faltan %d piezas\n", piezasProductos[producto][p], faltan);
                            }
                        }
                    }
                    break;
                }

            }

            case 6: {
                if (totalProductos == 0) {
                    printf("No hay productos registrados. Registre al menos uno primero.\n");
                    break;
                }
                printf("===== ANADIR STOCK DE PIEZAS =====\n");

                for (int i = 0; i < totalProductos; i++) {
                    printf("%d. %s\n", i + 1, productos[i]);
                }

                int producto;
                leerEnteroNoNegativo("Seleccione producto (0 para salir): ", &producto);
                if (producto == 0 || producto > totalProductos) break;
                producto--;

                printf("Producto seleccionado: %s\n", productos[producto]);

                printf("Seleccione la pieza a agregar stock:\n");
                for (int j = 0; j < MAX_PIEZAS; j++) {
                    if (strlen(piezasProductos[producto][j]) != 0) {
                        printf("%d. %s\n", j + 1, piezasProductos[producto][j]);
                    } else {
                        char dis[MAX_NOMBRE] = "--No Registrado--";
                        printf("%d. %s\n", j + 1, dis);
                    }
                }
                printf("0. Cancelar\n");
                int piezasAgregable[MAX_PIEZAS];
                for (int j = 0; j < MAX_PIEZAS; j++) {
                    if (strlen(piezasProductos[producto][j]) != 0) {
                        piezasAgregable[j] = 1;
                    } else {
                        piezasAgregable[j] = 0;
                    }
                }
                int pieza;
                leerEnteroNoNegativo("Seleccione pieza (0 para salir): ", &pieza);
                if (pieza == 0 || pieza > MAX_PIEZAS) {
                    printf("Edicion de stock cancelada.\n");
                    break;
                }
                pieza--;
                printf("Pieza seleccionada: %s\n", piezasProductos[producto][pieza]);
                printf("Stock actual: %d\n", stockPiezas[producto][pieza]);
                printf("Cantidad a agregar: ");
                int add;
                leerEnteroPositivo("Cantidad a agregar: ", &add);
                if (piezasAgregable[pieza] > 0) {
                    stockPiezas[producto][pieza] += add;
                } else {
                    printf("No se puede agregar stock a una pieza no registrada.\n");
                }
                break;
            }

            case 0:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 0);

    return 0;
}
