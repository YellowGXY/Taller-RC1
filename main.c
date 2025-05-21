#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    char productos[MAX_PRODUCTO_FIJO][MAX_NOMBRE] = {"Celular - 1", "Laptop - 1", "Tablet - 1", "Audifonos - 1", "Smartwatch - 1"};

    char piezasProductos[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO][MAX_NOMBRE] = {
        {"Pantalla", "Bateria", "Carcasa", "Procesador", "Camara"},
        {"Pantalla", "Teclado", "Bateria", "Placa Base", "Ventilador"},
        {"Pantalla", "Bateria", "Procesador", "Carcasa", "Puerto USB-C"},
        {"Auri Izq", "Auri Der", "Bateria", "Bluetooth", "Microfono"},
        {"Pantalla", "Bateria", "Correa", "Sensor", "Procesador"}
    };

    char identificadoresUsados[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO][MAX_NOMBRE] = {
        {"CPa1", "CBa2", "CCa3", "CPr4", "CCa5"},
        {"LPa1", "LTe2", "LBa3", "LPl4", "LVe5"},
        {"TPa1", "TBa2", "TPr3", "TCa4", "TPu5"},
        {"AAu1", "AAu2", "ABa3", "ABl4", "AMi5"},
        {"SPa1", "SBa2", "SCo3", "SSe4", "SPr5"}
    };

    int tiemposPiezas[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO] = {
        {10, 5, 7, 8, 5},
        {12, 6, 8, 10, 6},
        {10, 5, 7, 6, 4},
        {3, 3, 2, 4, 3},
        {5, 4, 3, 4, 5}
    };

    int stockPiezas[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO] = {
        {100, 80, 90, 85, 70},
        {60, 65, 55, 50, 45},
        {75, 80, 70, 65, 60},
        {100, 100, 100, 90, 80},
        {85, 90, 95, 70, 65}
    };

    int piezasNecesarias[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO] = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };

    int totalProductos = 5;
    int stockProductos[MAX_PRODUCTO_FIJO] = {0, 0, 0, 0, 0};
    int stockFProductos[MAX_PRODUCTO_FIJO] = {0, 0, 0, 0, 0};
    int totalPiezas[MAX_PRODUCTO_FIJO] = {5, 5, 5, 5, 5};
    int productosFTiempo[MAX_PRODUCTO_FIJO] = {35, 42, 32, 15, 21};
    int opcion;
    char USUARIO[MAX_NOMBRE] = "admin";
    char PASSWORD[MAX_NOMBRE] = "admin";

    int MAX_PRODUCTO = 20;
    int MAX_PIEZAS = 10;

    do {
        char usuario[MAX_NOMBRE];
        char pass[MAX_NOMBRE];
        printf("================================================\n");
        printf("Bienvenido al sistema de gestion de fabricacion\n");
        printf("================================================\n");
        printf("Por favor, inicie sesion para continuar.\n");
        printf("================================================\n");
        do {
            leerCadena("Usuario: ", usuario, MAX_NOMBRE);
            leerCadena("Contrasenia: ", pass, MAX_NOMBRE);
            if (strcmp(usuario, USUARIO) != 0 || strcmp(pass, PASSWORD) != 0) {
                printf("Usuario o contrasenia incorrectos. Intente de nuevo.\n");
            }
        } while (strcmp(usuario, USUARIO) != 0 || strcmp(pass, PASSWORD) != 0);
        printf("================================================\n");
        printf("Sesion iniciada con exito.\n");
        do {
            printf("\n====================================\n");
            printf("========= MENU DE OPCIONES =========\n");
            printf("1. Registrar producto\n");
            printf("2. Editar productos\n");
            printf("3. Eliminar producto\n");
            printf("4. Mostrar productos\n");
            printf("5. Analizar produccion\n");
            printf("6. Agregar stock de piezas\n");
            printf("7. Ver stock de productos\n");
            printf("8. Configuraciones\n");
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

                    leerEnteroNoNegativo("Ingrese el stock actual del producto: ", &stockFProductos[totalProductos]);
                
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

                        char identificador[MAX_NOMBRE];
                        generarIdentificador(productos[totalProductos], piezasProductos[totalProductos][j], j + 1, identificadoresUsados[totalProductos], identificador);
                        strcpy(piezasProductos[totalProductos][j], identificador);

                        strcpy(identificadoresUsados[totalProductos][j], identificador);
                        printf("Identificador generado: %s\n", identificador);


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
                    recalcularTiemposProductos(productosFTiempo, tiemposPiezas, totalProductos + 1, MAX_PIEZAS);
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

                        if (producto == 0 || producto > totalProductos) {
                            salirEdicion = 1;
                            break;
                        }
                        producto--;

                        printf("=====================================\n");

                        printf("Producto seleccionado: %s\n", productos[producto]);

                        printf("=====================================\n");
                        printf("Opciones de edicion:\n");
                        printf("1. Cambiar nombre del producto\n");
                        printf("2. Editar/Agregar piezas\n");
                        printf("3. Cambiar cantidad de piezas necesarias por unidad\n");
                        printf("4. Cambiar stock del producto\n");
                        printf("5. Eliminar una pieza del producto\n");
                        printf("0. Cancelar\n");
                        printf("=====================================\n");

                        int ed;
                        leerEnteroNoNegativo("Seleccione opcion: ", &ed);
                        if (ed == 0) {
                            printf("Edicion cancelada.\n");
                            break;
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
                            mostrarTablaProductosPiezas(
                                producto,
                                productos,
                                stockProductos,
                                totalProductos,
                                productosFTiempo,
                                piezasNecesarias,
                                piezasProductos,
                                stockPiezas,
                                tiemposPiezas,
                                identificadoresUsados
                            , MAX_PIEZAS
                            );

                            char idBuscar[MAX_NOMBRE];
                            leerCadenaConEspacios("Ingrese identificador de pieza (vacio para agregar nueva): ", idBuscar, MAX_NOMBRE);

                            int pieza = -1;
                            int esNueva = 0;

                            if (strlen(idBuscar) == 0) {
                                for (int i = 0; i < MAX_PIEZAS; i++) {
                                    if (strlen(piezasProductos[producto][i]) == 0) {
                                        pieza = i;
                                        esNueva = 1;
                                        break;
                                    }
                                }

                                if (pieza == -1) {
                                    printf("No hay espacio disponible para nuevas piezas.\n");
                                    break;
                                }
                                pieza = buscarPiezaPorIdentificador(producto, identificadoresUsados[producto], idBuscar, MAX_PIEZAS);
                                if (pieza < 0 || pieza >= MAX_PIEZAS || strlen(piezasProductos[producto][pieza]) == 0) {
                                    printf("Pieza no valida o no encontrada.\n");
                                    break;
                                }
                            }

                            if (esNueva) {
                                printf("== Agregando nueva pieza ==\n");

                                char nombreTemp[MAX_NOMBRE];
                                leerCadena("Nombre de la pieza: ", nombreTemp, MAX_NOMBRE);

                                char nuevoID[MAX_NOMBRE];
                                generarIdentificador(productos[producto], nombreTemp, pieza + 1, identificadoresUsados[producto], nuevoID);

                                strcpy(piezasProductos[producto][pieza], nombreTemp);
                                strcpy(identificadoresUsados[producto][pieza], nuevoID);

                                printf("Identificador generado: %s\n", nuevoID);

                                leerEnteroPositivo("Tiempo de instalacion (minutos): ", &tiemposPiezas[producto][pieza]);
                                leerEnteroNoNegativo("Stock inicial: ", &stockPiezas[producto][pieza]);
                                leerEnteroPositivo("Cantidad necesaria por unidad: ", &piezasNecesarias[producto][pieza]);
                                recalcularTiemposProductos(productosFTiempo, tiemposPiezas, totalProductos, MAX_PIEZAS);
                                printf("Nueva pieza agregada correctamente.\n");
                            } else {
                                printf("Pieza seleccionada: %s (ID: %s)\n", piezasProductos[producto][pieza], identificadoresUsados[producto][pieza]);

                                printf("Opciones de edicion para la pieza:\n");
                                printf("1. Cambiar nombre\n");
                                printf("2. Cambiar tiempo de instalacion\n");
                                printf("3. Cambiar cantidad necesaria por unidad\n");
                                printf("4. Cambiar TODO\n");
                                printf("0. Cancelar\n");

                                int opPieza;
                                do {
                                    leerEnteroNoNegativo("Seleccione opcion: ", &opPieza);
                                } while (opPieza < 0 || opPieza > 4);

                                if (opPieza == 0) {
                                    printf("Edicion cancelada.\n");
                                    break;
                                }

                                if (opPieza == 1 || opPieza == 4) {
                                    leerCadena("Nuevo nombre: ", piezasProductos[producto][pieza], MAX_NOMBRE);
                                }
                                if (opPieza == 2 || opPieza == 4) {
                                    leerEnteroPositivo("Nuevo tiempo de instalacion: ", &tiemposPiezas[producto][pieza]);
                                }
                                if (opPieza == 3 || opPieza == 4) {
                                    leerEnteroPositivo("Nueva cantidad necesaria por unidad: ", &piezasNecesarias[producto][pieza]);
                                }

                                recalcularTiemposProductos(productosFTiempo, tiemposPiezas, totalProductos, MAX_PIEZAS);
                                printf("Pieza modificada correctamente.\n");
                            }
                        } else if (ed == 3) {
                            printf("Seleccione la pieza para cambiar la cantidad necesaria:\n");
                            for (int j = 0; j < MAX_PIEZAS; j++) {
                                if (strlen(piezasProductos[producto][j]) != 0) {
                                    printf("%d. %s (Cantidad actual: %d)\n", j + 1, piezasProductos[producto][j], piezasNecesarias[producto][j]);
                                }
                            }
                            int pieza;
                            leerEnteroNoNegativo("Numero de pieza (0 para cancelar): ", &pieza);
                            if (pieza == 0 || pieza > MAX_PIEZAS) {
                                printf("Edicion cancelada.\n");
                                break;
                            }
                            pieza--;
                            leerEnteroPositivo("Nueva cantidad necesaria por unidad: ", &piezasNecesarias[producto][pieza]);

                        } else if (ed == 4) {
                            printf("Stock actual: %d\n", stockProductos[producto]);
                            leerEnteroNoNegativo("Nuevo stock para el producto: ", &stockProductos[producto]);

                        } else if (ed == 5) {
                            printf("Seleccione la pieza que desea eliminar:\n");
                            for (int j = 0; j < MAX_PIEZAS; j++) {
                                if (strlen(piezasProductos[producto][j]) != 0) {
                                    printf("%d. %s\n", j + 1, piezasProductos[producto][j]);
                                }
                            }
                            int pieza;
                            leerEnteroNoNegativo("Numero de pieza (0 para cancelar): ", &pieza);
                            if (pieza == 0 || pieza > MAX_PIEZAS) {
                                printf("Cancelado.\n");
                                break;
                            }
                            pieza--;

                            printf("Confirmar eliminacion de %s? (S/N): ", piezasProductos[producto][pieza]);
                            char confirmacion;
                            leerCaracter("Confirmar: ", &confirmacion);
                            if (confirmacion == 'S' || confirmacion == 's') {
                                for (int j = pieza; j < MAX_PIEZAS - 1; j++) {
                                    strcpy(piezasProductos[producto][j], piezasProductos[producto][j + 1]);
                                    piezasNecesarias[producto][j] = piezasNecesarias[producto][j + 1];
                                    tiemposPiezas[producto][j] = tiemposPiezas[producto][j + 1];
                                    stockPiezas[producto][j] = stockPiezas[producto][j + 1];
                                }
                                strcpy(piezasProductos[producto][MAX_PIEZAS - 1], "");
                                piezasNecesarias[producto][MAX_PIEZAS - 1] = 0;
                                tiemposPiezas[producto][MAX_PIEZAS - 1] = 0;
                                stockPiezas[producto][MAX_PIEZAS - 1] = 0;

                                printf("Pieza eliminada.\n");
                                recalcularTiemposProductos(productosFTiempo, tiemposPiezas, totalProductos, MAX_PIEZAS);
                            } else {
                                printf("Eliminacion cancelada.\n");
                            }

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
                    fgets(busqueda, MAX_NOMBRE, stdin);
                    int len = strlen(busqueda);
                    if (len > 0 && busqueda[len - 1] == '\n') {
                        busqueda[len - 1] = '\0';
                    }

                    int encontrados[MAX_PRODUCTO];
                    int cantidadEncontrados = 0;

                    for (int i = 0; i < totalProductos; i++) {
                        if (strlen(busqueda) == 0) {
                            encontrados[cantidadEncontrados++] = i;
                        } else {
                            int lenProd = strlen(productos[i]);
                            int lenBusq = strlen(busqueda);
                            for (int j = 0; j <= lenProd - lenBusq; j++) {
                                int k = 0;
                                while (k < lenBusq && productos[i][j + k] == busqueda[k]) {
                                    k++;
                                }
                                if (k == lenBusq) {
                                    encontrados[cantidadEncontrados++] = i;
                                    break; 
                                }
                            }
                        }
                    }

                    if (cantidadEncontrados == 0) {
                        printf("No se encontraron productos con ese nombre.\n");
                        break;
                    }

                    printf("Productos encontrados:\n");
                    for (int i = 0; i < cantidadEncontrados; i++) {
                        printf("%d. %s\n", i + 1, productos[encontrados[i]]);
                    }

                    int seleccion;
                    leerEnteroNoNegativo("Seleccione el numero del producto a eliminar (0 para cancelar): ", &seleccion);
                    if (seleccion == 0 || seleccion > cantidadEncontrados) {
                        printf("Eliminacion cancelada.\n");
                        break;
                    }

                    int producto = encontrados[seleccion - 1];
                    char confirmacion;
                    leerCaracter("Esta seguro que desea eliminar el producto? (S/N): ", &confirmacion);
                    if (confirmacion != 'S' && confirmacion != 's') {
                        printf("Eliminacion cancelada.\n");
                        break;
                    }

                    for (int i = producto; i < totalProductos - 1; i++) {
                        strcpy(productos[i], productos[i + 1]);
                        productosFTiempo[i] = productosFTiempo[i + 1];
                        stockProductos[i] = stockProductos[i + 1];
                        stockFProductos[i] = stockFProductos[i + 1];
                        totalPiezas[i] = totalPiezas[i + 1];
                        for (int j = 0; j < MAX_PIEZAS; j++) {
                            strcpy(piezasProductos[i][j], piezasProductos[i + 1][j]);
                            tiemposPiezas[i][j] = tiemposPiezas[i + 1][j];
                            stockPiezas[i][j] = stockPiezas[i + 1][j];
                            piezasNecesarias[i][j] = piezasNecesarias[i + 1][j];
                        }
                    }

                    strcpy(productos[totalProductos - 1], "");
                    productosFTiempo[totalProductos - 1] = 0;
                    stockProductos[totalProductos - 1] = 0;
                    stockFProductos[totalProductos - 1] = 0;
                    totalPiezas[totalProductos - 1] = 0;
                    for (int j = 0; j < MAX_PIEZAS; j++) {
                        strcpy(piezasProductos[totalProductos - 1][j], "");
                        tiemposPiezas[totalProductos - 1][j] = 0;
                        stockPiezas[totalProductos - 1][j] = 0;
                        piezasNecesarias[totalProductos - 1][j] = 0;
                    }

                    totalProductos--;
                    printf("Producto eliminado exitosamente.\n");
                    break;
                }

                case 4: {
                    if (totalProductos == 0) {
                        printf("No hay productos registrados. Registre al menos uno primero.\n");
                        break;
                    }

                    printf("===== PRODUCTOS REGISTRADOS =====\n");
                    printf("+-----+-------------------------------+--------------------+---------------------+\n");
                    printf("| No. | Nombre del producto           | Tiempo (minutos)   | Stock de productos  |\n");
                    printf("+-----+-------------------------------+--------------------+---------------------+\n");

                    for (int i = 0; i < totalProductos; i++) {
                        printf("| %-3d | %-29s | %-18d | %-19d |\n",
                            i + 1,
                            productos[i],
                            productosFTiempo[i],
                            stockFProductos[i]);
                    }

                    printf("+-----+-------------------------------+--------------------+---------------------+\n");

                    int seleccion;
                    leerEnteroNoNegativo("Seleccione el numero del producto para ver detalles (0 para cancelar): ", &seleccion);
                    if (seleccion == 0 || seleccion > totalProductos) {
                        printf("Cancelado.\n");
                        break;
                    }

                    int producto = seleccion - 1;

                    mostrarTablaProductosPiezas(
                        producto,
                        productos,
                        stockProductos,
                        totalProductos,
                        productosFTiempo,
                        piezasNecesarias,
                        piezasProductos,
                        stockPiezas,
                        tiemposPiezas,
                        identificadoresUsados,
                        MAX_PIEZAS
                    );

                    break;
                }

                case 5: {
                    if (totalProductos == 0) {
                        printf("No hay productos registrados. Registre al menos uno primero.\n");
                        break;
                    }

                    printf("===== ANALISIS DE PRODUCCION =====\n");

                    printf("+-----+-------------------------------+--------------------+\n");
                    printf("| No. | Nombre del producto           | Stock Fabricable   |\n");
                    printf("+-----+-------------------------------+--------------------+\n");

                    for (int i = 0; i < totalProductos; i++) {
                        int minStock = 100000;
                        for (int j = 0; j < MAX_PIEZAS; j++) {
                            if (piezasNecesarias[i][j] > 0) {
                                int posibles = stockPiezas[i][j] / piezasNecesarias[i][j];
                                if (posibles < minStock) minStock = posibles;
                            }
                        }
                        stockProductos[i] = minStock;
                        printf("| %-3d | %-29s | %-18d |\n", i + 1, productos[i], stockProductos[i]);
                    }

                    printf("+-----+-------------------------------+--------------------+\n");


                    int producto;
                    leerEnteroNoNegativo("Seleccione producto (0 para salir): ", &producto);
                    if (producto == 0 || producto > totalProductos) {
                        break;
                    }
                    producto--;

                    int tiempoUnidad = productosFTiempo[producto];
                    printf("-> Tiempo por unidad: %d minutos\n", tiempoUnidad);

                    int minStock = 100000;
                    for (int j = 0; j < MAX_PIEZAS; j++) {
                        if (piezasNecesarias[producto][j] > 0) {
                            int posibles = stockPiezas[producto][j] / piezasNecesarias[producto][j];
                            if (posibles < minStock) minStock = posibles;
                        }
                    }
                    stockProductos[producto] = minStock;

                    char agregarStock;
                    int agregarOpcion = -1;
                    if (stockProductos[producto] == 0) {
                        printf("-> No hay stock disponible para fabricar.\n");
                        printf("-> No se puede fabricar el producto %s.\n", productos[producto]);
                        
                        leerCaracter("Desea agregar mas piezas a su stock? (S/N): ", &agregarStock);
                        if (agregarStock == 'S' || agregarStock == 's') {
                            printf("1. Agregar por pieza\n");
                            printf("2. Agregar a todas las piezas\n");
                            printf("0. Cancelar\n");
                            
                            leerEnteroNoNegativo("Seleccione opcion: ", &agregarOpcion);
                            if (agregarOpcion == 0) {
                                printf("Agregado de stock cancelado.\n");
                                break;
                            }
                            if (agregarOpcion == 1) {
                                printf("Seleccione la pieza a agregar stock:\n");
                                for (int i = 0; i < MAX_PIEZAS; i++) {
                                    if (strlen(piezasProductos[producto][i]) != 0) {
                                        printf("%d. %s\n", i + 1, piezasProductos[producto][i]);
                                    }
                                }
                                int pieza;
                                leerEnteroNoNegativo("Seleccione pieza (0 para salir): ", &pieza);
                                if (pieza == 0 || pieza > MAX_PIEZAS) {
                                    printf("Agregado de stock cancelado.\n");
                                    break;
                                }
                                pieza--;
                                printf("Pieza seleccionada: %s\n", piezasProductos[producto][pieza]);
                                printf("Stock actual: %d\n", stockPiezas[producto][pieza]);
                                int agregarCantidad;
                                leerEnteroPositivo("Cantidad a agregar: ", &agregarCantidad);
                                stockPiezas[producto][pieza] += agregarCantidad;
                                printf("-> Stock actualizado.\n");
                            } else if (agregarOpcion == 2) {
                                int agregarCantidad;
                                leerEnteroPositivo("Cantidad a agregar: ", &agregarCantidad);
                                for (int i = 0; i < MAX_PIEZAS; i++) {
                                    stockPiezas[producto][i] += agregarCantidad;
                                }
                                printf("-> Stock actualizado.\n");
                            } else {
                                printf("-> No se agrego stock.\n");
                                break;
                            }
                        }
                        if (agregarStock == 'N' || agregarStock == 'n' || agregarOpcion == 0) {
                            printf("-> No se agrego stock.\n");
                            break;
                        }
                        
                    }

                    if (agregarStock == 'N' || agregarStock == 'n' || agregarOpcion == 0) {
                        break;
                    }
                    

                    printf("-> Actualmente se pueden fabricar %d unidades en un tiempo de: \n", stockProductos[producto]);
                    mostrarTiempo(stockProductos[producto] * productosFTiempo[producto]);

                    int opcionModo;
                    printf("\n1. Ingresar cantidad a fabricar\n");
                    printf("2. Ingresar tiempo disponible\n");
                    leerEnteroNoNegativo("Seleccione una opcion: ", &opcionModo);

                    int cantidadFabricar = 0;
                    int tiempoDisponible = 0;
                    int posiblesPorStock = 100000;

                    for (int i = 0; i < MAX_PIEZAS; i++) {
                        if (piezasNecesarias[producto][i] > 0) {
                            int posibles = stockPiezas[producto][i] / piezasNecesarias[producto][i];
                            if (posibles < posiblesPorStock) {
                                posiblesPorStock = posibles;
                            }
                        }
                    }

                    if (opcionModo == 1) {
                        leerEnteroPositivo("Ingrese la cantidad que desea fabricar: ", &cantidadFabricar);
                        int tiempoTotal = cantidadFabricar * tiempoUnidad;

                        if (cantidadFabricar <= posiblesPorStock) {
                            printf("-> Fabricar %d unidades tomaria:\n", cantidadFabricar);
                            mostrarTiempo(tiempoTotal);
                        } else {
                            printf("-> No hay suficiente stock para fabricar %d unidades.\n", cantidadFabricar);
                            printf("-> Con el stock actual solo se pueden fabricar %d unidades.\n", posiblesPorStock);
                            int tiempoMaximo = posiblesPorStock * tiempoUnidad;
                            printf("-> Tiempo para fabricar %d unidades (maximo posible):\n", posiblesPorStock);
                            mostrarTiempo(tiempoMaximo);

                            printf("-> Faltan las siguientes piezas:\n");
                            for (int i = 0; i < MAX_PIEZAS; i++) {
                                int faltan = cantidadFabricar * piezasNecesarias[producto][i] - stockPiezas[producto][i];
                                if (faltan > 0) {
                                    printf("   - %s: faltan %d unidades\n", piezasProductos[producto][i], faltan);
                                }
                            }

                            char reponer;
                            leerCaracter("Desea reponer las piezas faltantes? (S/N): ", &reponer);
                            if (reponer == 'S' || reponer == 's') {
                                char modo;
                                leerCaracter("Desea reponer individualmente (I) o automaticamente todas (A)? ", &modo);
                                if (modo == 'A' || modo == 'a') {
                                    for (int i = 0; i < MAX_PIEZAS; i++) {
                                        int faltan = cantidadFabricar * piezasNecesarias[producto][i] - stockPiezas[producto][i];
                                        if (faltan > 0) {
                                            stockPiezas[producto][i] += faltan;
                                        }
                                    }
                                    printf("-> Piezas repuestas automaticamente.\n");
                                } else if (modo == 'I' || modo == 'i') {
                                    for (int i = 0; i < MAX_PIEZAS; i++) {
                                        int faltan = cantidadFabricar * piezasNecesarias[producto][i] - stockPiezas[producto][i];
                                        if (faltan > 0) {
                                            printf("-> Falta %s: %d unidades\n", piezasProductos[producto][i], faltan);
                                            int agregar = 0;
                                            leerEnteroNoNegativo("Cuantas desea agregar?: ", &agregar);
                                            stockPiezas[producto][i] += agregar;
                                        }
                                    }
                                }
                            } else {
                                printf("-> No se repusieron piezas.\n");
                                printf("-> Pedido cancelado.\n");
                                break;
                            }
                        }

                    } else if (opcionModo == 2) {
                        leerEnteroPositivo("Ingrese tiempo disponible (en minutos): ", &tiempoDisponible);

                        int porTiempo = tiempoDisponible / tiempoUnidad;
                        int fabricablesFinal;
                        if (porTiempo < posiblesPorStock) {
                            fabricablesFinal = porTiempo;
                        } else {
                            fabricablesFinal = posiblesPorStock;
                        }

                        if (fabricablesFinal == 0) {
                            printf("-> No es posible fabricar unidades con el tiempo y stock actuales.\n");
                            
                            break;
                        }

                        

                        if (porTiempo > posiblesPorStock) {
                            printf("-> No hay suficiente stock para fabricar %d unidades en un tiempo de: \n", porTiempo);
                            mostrarTiempo(porTiempo * tiempoUnidad);
                            printf("\n");
                            printf("-> Faltan las siguientes piezas:\n");
                            for (int i = 0; i < MAX_PIEZAS; i++) {
                                int faltan = (porTiempo * piezasNecesarias[producto][i]) - stockPiezas[producto][i];
                                if (faltan > 0) {
                                    printf("   - %s: faltan %d unidades\n", piezasProductos[producto][i], faltan);
                                }
                            }
                            char reponer;
                            leerCaracter("Desea agregar las piezas faltantes? (S/N): ", &reponer);
                            if (reponer == 'S' || reponer == 's') {
                                char modo;
                                leerCaracter("Desea reponer individualmente (I) o automaticamente todas (A)? ", &modo);
                                if (modo == 'A' || modo == 'a') {
                                    for (int i = 0; i < MAX_PIEZAS; i++) {
                                        int faltan = (porTiempo * piezasNecesarias[producto][i]) - stockPiezas[producto][i];
                                        if (faltan > 0) {
                                            stockPiezas[producto][i] += faltan;
                                        }
                                    }
                                    printf("-> Piezas repuestas automaticamente.\n");
                                } else if (modo == 'I' || modo == 'i') {
                                    for (int i = 0; i < MAX_PIEZAS; i++) {
                                        int faltan = (porTiempo * piezasNecesarias[producto][i]) - stockPiezas[producto][i];
                                        if (faltan > 0) {
                                            printf("-> Falta %s: %d unidades\n", piezasProductos[producto][i], faltan);
                                            int agregar = 0;
                                            leerEnteroNoNegativo("Cuantas desea agregar?: ", &agregar);
                                            stockPiezas[producto][i] += agregar;
                                        }
                                    }
                                }
                            } else {
                                printf("-> No se repusieron piezas.\n");
                                break;
                            }
                        } else {
                            printf("-> Se pueden fabricar %d unidades en un tiempo de: \n", fabricablesFinal);
                            mostrarTiempo(fabricablesFinal * tiempoUnidad);
                        }

                        cantidadFabricar = fabricablesFinal;
                    }

                    char confirmar;
                    int tiempoFinal = cantidadFabricar * tiempoUnidad;
                    leerCaracter("Desea realizar el pedido? (S/N): ", &confirmar);
                    if (confirmar == 'S' || confirmar == 's') {
                        for (int i = 0; i < MAX_PIEZAS; i++) {
                            stockPiezas[producto][i] -= piezasNecesarias[producto][i] * cantidadFabricar;
                        }
                        stockFProductos[producto] += cantidadFabricar;
                        printf("-> Pedido confirmado. \n\tSe ha enviado el pedido para la fabricacion de %d unidades de [%s].\n", cantidadFabricar, productos[producto]);
                        printf("-> Tiempo estimado de produccion:\n");
                        mostrarTiempo(tiempoFinal);
                    } else {
                        printf("-> Pedido cancelado.\n");
                    }

                    break;
                }



                case 6: {
                    if (totalProductos == 0) {
                        printf("No hay productos registrados. Registre al menos uno primero.\n");
                        break;
                    }
                    printf("===== ANADIR STOCK DE PIEZAS =====\n");

                    for (int i = 0; i < totalProductos; i++) {
                        printf("%d. \t%s\n", i + 1, productos[i]);
                    }

                    int producto;
                    leerEnteroNoNegativo("Seleccione producto (0 para salir): ", &producto);
                    if (producto == 0 || producto > totalProductos) {
                        break;
                    }
                    producto--;

                    printf("Producto seleccionado: %s\n", productos[producto]);

                    printf("Seleccione la pieza a agregar stock:\n");
                    for (int j = 0; j < MAX_PIEZAS; j++) {
                        if (strlen(piezasProductos[producto][j]) != 0) {
                            printf("%d. \t%s\n", j + 1, piezasProductos[producto][j]);
                        }
                    }
                    printf("0. \tCancelar\n");
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
                    int add;
                    leerEnteroPositivo("Cantidad a agregar: ", &add);
                    if (piezasAgregable[pieza] > 0) {
                        stockPiezas[producto][pieza] += add;
                    } else {
                        printf("No se puede agregar stock a una pieza no registrada.\n");
                    }
                    break;
                }

                case 7: {
                    if (totalProductos == 0) {
                        printf("No hay productos registrados.\n");
                        break;
                    }

                    printf("===== STOCK DE PRODUCTOS =====\n");
                    printf("+-----+-------------------------------+--------------------+\n");
                    printf("| No. | Nombre del producto           | Stock Actual       |\n");
                    printf("+-----+-------------------------------+--------------------+\n");
                    for (int i = 0; i < totalProductos; i++) {
                        printf("| %-3d | %-29s | %-18d |\n", i + 1, productos[i], stockFProductos[i]);
                    }
                    printf("+-----+-------------------------------+--------------------+\n");

                    break;
                }

                case 8: {
                    printf("Para cambiar las configuraciones, ingrese el nombre de usuario y contrasenia actuales.\n");
                    leerCadena("Nombre de usuario: ", usuario, MAX_NOMBRE);
                    leerCadena("Contrasenia: ", pass, MAX_NOMBRE);
                    if (strcmp(usuario, USUARIO) != 0 || strcmp(pass, PASSWORD) != 0) {
                        printf("Credenciales incorrectas.\n");
                        break;
                    } else {
                        printf("Credenciales correctas.\n");
                        printf("\n");
                    }
                    printf("===== CONFIGURACIONES =====\n");
                    printf("1. Cambiar Credenciales\n");
                    printf("2. Cambiar valores maximos\n");
                    printf("0. Cancelar\n");
                    int configuracion;
                    leerEnteroNoNegativo("Seleccione una opcion: ", &configuracion);
                    if (configuracion == 0) {
                        printf("Configuracion cancelada.\n");
                        break;
                    }

                    if (configuracion == 2) {
                        leerEnteroPositivo("Nuevo valor maximo de productos: ", &MAX_PRODUCTO);
                        if (MAX_PRODUCTO > MAX_PRODUCTO_FIJO) {
                            MAX_PRODUCTO = MAX_PRODUCTO_FIJO;
                            printf("Limitado a %d productos.\n", MAX_PRODUCTO_FIJO);
                        } else if (MAX_PRODUCTO < 5) {
                            MAX_PRODUCTO = 5;
                            printf("Limitado a %d productos.\n", MAX_PRODUCTO);
                        }
                        leerEnteroPositivo("Nuevo valor maximo de piezas: ", &MAX_PIEZAS);
                        if (MAX_PIEZAS > MAX_PIEZAS_FIJO) {
                            MAX_PIEZAS = MAX_PIEZAS_FIJO;
                            printf("Limitado a %d piezas.\n", MAX_PIEZAS_FIJO);
                        } else if (MAX_PIEZAS < 5) {
                            MAX_PIEZAS = 5;
                            printf("Limitado a %d piezas.\n", MAX_PIEZAS);
                        }
                        printf("Valores maximos cambiados a: %d productos y %d piezas.\n", MAX_PRODUCTO, MAX_PIEZAS);
                        break;
                    }
                    
                    printf("===== CAMBIO DE CREDENCIALES =====\n");
                    printf("1. Cambiar nombre de usuario\n");
                    printf("2. Cambiar contrasenia\n");
                    printf("3. Cambiar ambas\n");
                    printf("0. Cancelar\n");
                    int credenciales;
                    leerEnteroNoNegativo("Seleccione una opcion: ", &credenciales);
                    if (credenciales == 0 || credenciales > 3) {
                        printf("Cambio de credenciales cancelado.\n");
                        break;
                    }
                    switch (credenciales) {
                        case 1:
                            leerCadena("Ingrese el nuevo nombre de usuario: ", USUARIO, MAX_NOMBRE);
                            printf("Nombre de usuario cambiado a: %s\n", USUARIO);
                            break;
                        case 2:
                            leerCadena("Ingrese la nueva contrasenia: ", PASSWORD, MAX_NOMBRE);
                            printf("Contrasenia cambiada a: %s\n", PASSWORD);
                            break;
                        case 3:
                            leerCadena("Ingrese el nuevo nombre de usuario: ", USUARIO, MAX_NOMBRE);
                            printf("Nombre de usuario cambiado a: %s\n", USUARIO);
                            leerCadena("Ingrese la nueva contrasenia: ", PASSWORD, MAX_NOMBRE);
                            printf("Contrasenia cambiada a: %s\n", PASSWORD);
                            break;
                    }
                    break;
                }

                case 0:
                    break;
                default:
                    printf("Opcion invalida.\n");
            }

        } while (opcion != 0);

        char cerrar;
        leerCaracter("Desea cerrar el programa? (S/N): ", &cerrar);
        if (cerrar == 'S' || cerrar == 's') {
            break;
        }
        printf("Volviendo al menu principal...\n");
        printf("\n");
        printf("\n");
        printf("\n");
    } while (1);

    return 0;
}