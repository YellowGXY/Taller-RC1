#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    // Inicialización de productos y piezas (datos de ejemplo)
    char productos[MAX_PRODUCTO_FIJO][MAX_NOMBRE] = {"Celular -Pr#001", "Laptop -Pr#002", "Tablet -Pr#003", "Audifonos -Pr#004", "Smartwatch -Pr#005"};

    char piezasProductos[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO][MAX_NOMBRE] = {
        {"Pantalla", "Bateria", "Carcasa", "Procesador", "Camara"},
        {"Pantalla", "Teclado", "Bateria", "Placa Base", "Ventilador"},
        {"Pantalla", "Bateria", "Procesador", "Carcasa", "Puerto USB-C"},
        {"Auri Izq", "Auri Der", "Bateria", "Bluetooth", "Microfono"},
        {"Pantalla", "Bateria", "Correa", "Sensor", "Procesador"}
    };

    char identificadoresUsados[MAX_PRODUCTO_FIJO][MAX_PIEZAS_FIJO][MAX_NOMBRE] = {
        {"CPa11", "CBa21", "CCa31", "CPr41", "CCa51"},
        {"LPa11", "LTe21", "LBa31", "LPl41", "LVe51"},
        {"TPa11", "TBa21", "TPr31", "TCa41", "TPu51"},
        {"AAu11", "AAu21", "ABa31", "ABl41", "AMi51"},
        {"SPa11", "SBa21", "SCo31", "SSe41", "SPr51"}
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

    // Bucle principal del sistema
    do {
        char usuario[MAX_NOMBRE];
        char pass[MAX_NOMBRE];
        printf("================================================\n");
        printf("Bienvenido al sistema de gestion de fabricacion\n");
        printf("================================================\n");
        printf("Por favor, inicie sesion para continuar.\n");
        printf("================================================\n");
        // Bucle de autenticación de usuario
        do {
            leerCadena("Usuario: ", usuario, MAX_NOMBRE);
            leerCadena("Contrasenia: ", pass, MAX_NOMBRE);
            if (strcmp(usuario, USUARIO) != 0 || strcmp(pass, PASSWORD) != 0) {
                printf("Usuario o contrasenia incorrectos. Intente de nuevo.\n");
            }
        } while (strcmp(usuario, USUARIO) != 0 || strcmp(pass, PASSWORD) != 0);
        printf("================================================\n");
        printf("Sesion iniciada con exito.\n");
        // Menú principal de opciones
        do {
            printf("\n====================================\n");
            printf("========= MENU DE OPCIONES =========\n");
            printf("1. Registrar Productos\n");
            printf("2. Editar Productos\n");
            printf("3. Eliminar Producto\n");
            printf("4. Informacion de Productos\n");
            printf("5. Produccion\n");
            printf("6. Agregar stock de Piezas\n");
            printf("7. Ver stock de Productos\n");
            printf("8. Configuraciones\n");
            printf("0. Salir\n");
            printf("====================================\n");

            leerEnteroNoNegativo("Seleccione una opcion: ", &opcion);

            printf("=====================================\n");
            switch (opcion) {
                case 1: {
                    // Registro de nuevos productos
                    if (totalProductos >= MAX_PRODUCTO) {
                        printf("No se pueden registrar mas productos.\n");
                        break;
                    }

                    printf("\n===== REGISTRAR NUEVO PRODUCTO =====\n");

                    if (totalProductos == 0) {
                        printf("No hay productos registrados actualmente.\n");
                    } else {
                        printf("Productos actuales:\n");
                        printf("+-----+-------------------------------+--------------------+\n");
                        printf("| No. | Nombre del producto           | Stock Actual       |\n");
                        printf("+-----+-------------------------------+--------------------+\n");
                        for (int i = 0; i < totalProductos; i++) {
                            printf("| %-3d | %-29s | %-18d |\n", i + 1, productos[i], stockFProductos[i]);
                        }
                        printf("+-----+-------------------------------+--------------------+\n");
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
                    int lleno = 0;
                    for (int i = 0; i < cantidad && totalProductos < MAX_PRODUCTO; i++, totalProductos++) {
                        // Validación de nombre único para el producto
                        int nombreValido;
                        int noseguir = 0;
                        do {
                            nombreValido = 1;
                            leerCadena("Ingrese nombre del nuevo producto: ", productos[totalProductos], MAX_NOMBRE);

                            for (int j = 0; j < totalProductos; j++) {
                                if (strcmp(productos[totalProductos], productos[j]) == 0) {
                                    printf("Ya existe un producto con ese nombre. Intente otro.\n");
                                    nombreValido = 0;
                                    noseguir = 1;
                                    break;
                                }
                            }
                            if (noseguir == 0) {
                                if (agregarIdentificadorProducto(productos[totalProductos], totalProductos + 1)) {
                                    printf("Identificador agregado exitosamente.\n");
                                    printf("Nombre del producto: %s\n", productos[totalProductos]);
                                } else {
                                    printf("No se pudo agregar identificador el nombre del producto es demasiado largo, ingrese uno mas corto.\n");
                                    lleno = 1;
                                }
                            }

                        } while (!nombreValido || lleno == 1);

                        leerEnteroNoNegativo("Ingrese el stock actual del producto: ", &stockFProductos[totalProductos]);
                    
                        int piezas;
                        leerEnteroPositivo("Cuantas piezas desea registrar para el producto? (10 maximo): ", &piezas);
                        printf("Se registraran %d piezas.\n", piezas);
                        if (piezas > MAX_PIEZAS) {
                            printf("No se pueden registrar mas de %d piezas.\n", MAX_PIEZAS);
                            break;
                        } else if (piezas <= 0) {
                            printf("No se pueden registrar menos de 1 pieza.\n");
                            break;
                        }

                        int tiempoTotal = 0;
                        for (int j = 0; j < piezas; j++) {
                            // Registro de cada pieza del producto
                            printf("Pieza %d:\n", j + 1);

                            leerCadena("Nombre de la pieza: ", piezasProductos[totalProductos][j], MAX_NOMBRE);

                            char identificador[MAX_NOMBRE];
                            generarIdentificador(productos[totalProductos], piezasProductos[totalProductos][j], j + 1, identificadoresUsados, totalProductos, identificador);
                            strcpy(identificadoresUsados[totalProductos][j], identificador);
                            printf("Identificador generado: %s\n", identificador);

                            leerEnteroPositivo("Tiempo de instalacion (minutos): ", &tiemposPiezas[totalProductos][j]);
                            leerEnteroNoNegativo("Stock inicial: ", &stockPiezas[totalProductos][j]);
                            leerEnteroPositivo("Cantidad necesaria por unidad: ", &piezasNecesarias[totalProductos][j]);

                            tiempoTotal += tiemposPiezas[totalProductos][j];
                            totalPiezas[totalProductos]++;
                            if (totalPiezas[totalProductos] > MAX_PIEZAS) {
                                printf("Solo se pueden registrar hasta %d piezas por producto.\n", MAX_PIEZAS);
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
                    // Edición de productos existentes
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

                        int seguirEditandoProducto = 1;
                        do {
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
                                // Cambiar nombre del producto
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
                                // Editar o agregar piezas al producto
                                int seguirPiezas = 1;
                                do {
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

                                    char idBuscar[MAX_NOMBRE];
                                    leerCadenaConEspacios("Ingrese identificador de pieza (deje vacio para agregar nueva): ", idBuscar, MAX_NOMBRE);

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
                                    } else {
                                        pieza = buscarPiezaPorIdentificador(producto, identificadoresUsados[producto], idBuscar, MAX_PIEZAS);
                                        if (pieza < 0 || pieza >= MAX_PIEZAS || strlen(piezasProductos[producto][pieza]) == 0) {
                                            printf("Debe ingresar un identificador valido de pieza existente.\n");
                                            continue;
                                        }
                                    }

                                    if (esNueva) {
                                        // Agregar nueva pieza
                                        printf("== Agregando nueva pieza ==\n");

                                        char nombreTemp[MAX_NOMBRE];
                                        leerCadena("Nombre de la pieza: ", nombreTemp, MAX_NOMBRE);

                                        strcpy(piezasProductos[producto][pieza], nombreTemp);

                                        char nuevoID[MAX_NOMBRE];
                                        generarIdentificador(productos[producto], piezasProductos[producto][pieza], pieza + 1, identificadoresUsados, producto, nuevoID);
                                        strcpy(identificadoresUsados[producto][pieza], nuevoID);

                                        printf("Identificador generado: %s\n", nuevoID);

                                        leerEnteroPositivo("Tiempo de instalacion (minutos): ", &tiemposPiezas[producto][pieza]);
                                        leerEnteroNoNegativo("Stock inicial: ", &stockPiezas[producto][pieza]);
                                        leerEnteroPositivo("Cantidad necesaria por unidad: ", &piezasNecesarias[producto][pieza]);
                                        recalcularTiemposProductos(productosFTiempo, tiemposPiezas, totalProductos, MAX_PIEZAS);
                                        printf("Nueva pieza agregada correctamente.\n");
                                    } else {
                                        // Editar pieza existente
                                        int seguirEditandoPieza = 1;
                                        do {
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
                                                generarIdentificador(productos[producto], piezasProductos[producto][pieza], pieza + 1, identificadoresUsados, producto, identificadoresUsados[producto][pieza]);
                                                printf("Nuevo identificador generado: %s\n", identificadoresUsados[producto][pieza]);
                                            }
                                            if (opPieza == 2 || opPieza == 4) {
                                                leerEnteroPositivo("Nuevo tiempo de instalacion: ", &tiemposPiezas[producto][pieza]);
                                            }
                                            if (opPieza == 3 || opPieza == 4) {
                                                leerEnteroPositivo("Nueva cantidad necesaria por unidad: ", &piezasNecesarias[producto][pieza]);
                                            }

                                            recalcularTiemposProductos(productosFTiempo, tiemposPiezas, totalProductos, MAX_PIEZAS);
                                            printf("Pieza modificada correctamente.\n");

                                            char respuesta;
                                            leerCaracter("Desea seguir editando esta pieza? (S/N): ", &respuesta);
                                            if (respuesta != 'S' && respuesta != 's') {
                                                seguirEditandoPieza = 0;
                                            }
                                        } while (seguirEditandoPieza);
                                    }

                                    char otraPieza;
                                    leerCaracter("Desea editar/agregar otra pieza de este producto? (S/N): ", &otraPieza);
                                    if (otraPieza != 'S' && otraPieza != 's') {
                                        seguirPiezas = 0;
                                    }
                                } while (seguirPiezas);

                            } else if (ed == 3) {
                                // Cambiar cantidad necesaria por unidad de una pieza
                                int seguirEditando = 1;
                                do {
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

                                    char idBuscar[MAX_NOMBRE];
                                    do {
                                        leerCadenaConEspacios("Ingrese identificador de pieza (vacio para cancelar): ", idBuscar, MAX_NOMBRE);
                                        if (strlen(idBuscar) == 0) {
                                            printf("Edicion cancelada.\n");
                                            seguirEditando = 0;
                                            break;
                                        }
                                        int pieza = buscarPiezaPorIdentificador(producto, identificadoresUsados[producto], idBuscar, MAX_PIEZAS);
                                        if (pieza < 0 || pieza >= MAX_PIEZAS || strlen(piezasProductos[producto][pieza]) == 0) {
                                            printf("Debe ingresar un identificador valido de pieza existente.\n");
                                            continue;
                                        }
                                        printf("Pieza seleccionada: %s (Cantidad actual: %d)\n", piezasProductos[producto][pieza], piezasNecesarias[producto][pieza]);
                                        leerEnteroPositivo("Nueva cantidad necesaria por unidad: ", &piezasNecesarias[producto][pieza]);
                                        char respuesta;
                                        leerCaracter("Desea editar otra pieza? (S/N): ", &respuesta);
                                        if (respuesta != 'S' && respuesta != 's') {
                                            seguirEditando = 0;
                                        }
                                        break;
                                    } while (1);
                                } while (seguirEditando);

                            } else if (ed == 4) {
                                // Cambiar stock del producto
                                printf("Stock actual: %d\n", stockFProductos[producto]);
                                leerEnteroNoNegativo("Nuevo stock para el producto: ", &stockFProductos[producto]);

                            } else if (ed == 5) {
                                // Eliminar una pieza del producto
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
                                char idBuscar[MAX_NOMBRE];
                                int pieza = -1;
                                do {
                                    leerCadenaConEspacios("Ingrese identificador de la pieza a eliminar (vacio para cancelar): ", idBuscar, MAX_NOMBRE);
                                    if (strlen(idBuscar) == 0) {
                                        printf("Eliminacion cancelada.\n");
                                        break;
                                    }
                                    pieza = buscarPiezaPorIdentificador(producto, identificadoresUsados[producto], idBuscar, MAX_PIEZAS);
                                    if (pieza < 0 || pieza >= MAX_PIEZAS || strlen(piezasProductos[producto][pieza]) == 0) {
                                        printf("Debe ingresar un identificador valido de pieza existente.\n");
                                    } else {
                                        break;
                                    }
                                } while (1 && strlen(idBuscar) != 0);
                                if (strlen(idBuscar) == 0) {
                                    break;
                                }

                                printf("Confirmar eliminacion de %s? (S/N): ", piezasProductos[producto][pieza]);
                                char confirmacion;
                                leerCaracter("Confirmar: ", &confirmacion);
                                if (confirmacion == 'S' || confirmacion == 's') {
                                    for (int j = pieza; j < MAX_PIEZAS - 1; j++) {
                                        strcpy(piezasProductos[producto][j], piezasProductos[producto][j + 1]);
                                        piezasNecesarias[producto][j] = piezasNecesarias[producto][j + 1];
                                        tiemposPiezas[producto][j] = tiemposPiezas[producto][j + 1];
                                        stockPiezas[producto][j] = stockPiezas[producto][j + 1];
                                        strcpy(identificadoresUsados[producto][j], identificadoresUsados[producto][j + 1]);
                                    }
                                    strcpy(piezasProductos[producto][MAX_PIEZAS - 1], "");
                                    piezasNecesarias[producto][MAX_PIEZAS - 1] = 0;
                                    tiemposPiezas[producto][MAX_PIEZAS - 1] = 0;
                                    stockPiezas[producto][MAX_PIEZAS - 1] = 0;
                                    strcpy(identificadoresUsados[producto][MAX_PIEZAS - 1], "");

                                    printf("Pieza eliminada.\n");
                                    recalcularTiemposProductos(productosFTiempo, tiemposPiezas, totalProductos, MAX_PIEZAS);
                                } else {
                                    printf("Eliminacion cancelada.\n");
                                }

                            } else {
                                printf("Opcion invalida.\n");
                            }

                            char otraOpcion;
                            leerCaracter("Desea realizar otra edicion sobre este producto? (S/N): ", &otraOpcion);
                            if (otraOpcion != 'S' && otraOpcion != 's') {
                                seguirEditandoProducto = 0;
                            }
                        } while (seguirEditandoProducto);

                        char otroProducto;
                        leerCaracter("Desea editar otro producto? (S/N): ", &otroProducto);
                        if (otroProducto != 'S' && otroProducto != 's') {
                            salirEdicion = 1;
                        }
                    } while (!salirEdicion);
                    break;
                }

                case 3: {
                    // Eliminación de productos
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

                    // Elimina el producto y reorganiza los arreglos
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
                    // Información y detalles de productos
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
                    // Análisis y petición de producción
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

                    // Selección de producto para fabricar
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
                        // Si no hay stock suficiente, permite reponer piezas
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
                    
                    // Fabricación según stock y tiempo
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
                        // Ingreso de cantidad a fabricar
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
                        // Ingreso de tiempo disponible con selección de unidad
                        printf("Seleccione la unidad de tiempo:\n");
                        printf("1. Minutos\n");
                        printf("2. Horas\n");
                        printf("3. Dias\n");
                        printf("4. Semanas\n");
                        printf("5. Meses (30 dias)\n");
                        printf("6. Anios (365 dias)\n");
                        printf("0. Cancelar\n");
                        int unidadTiempo = 0;
                        do {
                            leerEnteroNoNegativo("Seleccione una opcion: ", &unidadTiempo);
                        } while (unidadTiempo < 0 || unidadTiempo > 6);

                        if (unidadTiempo == 0) {
                            printf("-> Pedido cancelado.\n");
                            break;
                        }

                        int tiempoIngresado = 0;
                        leerEnteroPositivo("Ingrese el tiempo disponible: ", &tiempoIngresado);

                        // Conversión a minutos
                        int minutosTotales = tiempoIngresado;
                        switch (unidadTiempo) {
                            case 1: // minutos
                                break;
                            case 2: // horas
                                minutosTotales *= 60;
                                break;
                            case 3: // dias
                                minutosTotales *= 60 * 24;
                                break;
                            case 4: // semanas
                                minutosTotales *= 60 * 24 * 7;
                                break;
                            case 5: // meses (30 dias)
                                minutosTotales *= 60 * 24 * 30;
                                break;
                            case 6: // años (365 dias)
                                minutosTotales *= 60 * 24 * 365;
                                break;
                        }

                        // Límite de cantidad maxima (2147483647)
                        int LIMITE_MINUTOS = 2147483647;
                        if (minutosTotales > LIMITE_MINUTOS) {
                            printf("El tiempo ingresado excede el limite maximo soportado (%d minutos).\n", LIMITE_MINUTOS);
                            minutosTotales = LIMITE_MINUTOS;
                            printf("Se usara el limite maximo permitido de 2147483647 minutos.\n");
                        }

                        int porTiempo = minutosTotales / tiempoUnidad;
                        int fabricablesFinal;
                        if (porTiempo < posiblesPorStock) { // se puede fabricar menos de lo que hay en stock
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
                                        int faltan = (porTiempo * piezasNecesarias[producto][i]) - stockPiezas[producto][i]; // calculo de faltantes
                                        if (faltan > 0) {
                                            stockPiezas[producto][i] += faltan;
                                        }
                                    }
                                    printf("-> Piezas repuestas automaticamente.\n");
                                } else if (modo == 'I' || modo == 'i') {
                                    for (int i = 0; i < MAX_PIEZAS; i++) {
                                        int faltan = (porTiempo * piezasNecesarias[producto][i]) - stockPiezas[producto][i]; // calculo de faltantes
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

                    // Confirmación y ejecución del pedido de fabricación
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
                    // Agregar stock a piezas de productos
                    if (totalProductos == 0) {
                        printf("No hay productos registrados. Registre al menos uno primero.\n");
                        break;
                    }

                    printf("===== AGREGAR STOCK A PIEZAS =====\n");
                    printf("+-----+-------------------------------+--------------------+\n");
                    printf("| No. | Nombre del producto           | Stock Actual       |\n");
                    printf("+-----+-------------------------------+--------------------+\n");
                    for (int i = 0; i < totalProductos; i++) {
                        printf("| %-3d | %-29s | %-18d |\n", i + 1, productos[i], stockFProductos[i]);
                    }
                    printf("+-----+-------------------------------+--------------------+\n");

                    int producto;
                    leerEnteroNoNegativo("Seleccione el numero del producto (0 para salir): ", &producto);
                    if (producto == 0 || producto > totalProductos) {
                        printf("Operacion cancelada.\n");
                        break;
                    }
                    producto--;

                    printf("\nPiezas del producto [%s]:\n", productos[producto]);
                    printf("+---------------+-------------------------+-------------------+\n");
                    printf("| Identificador | Nombre de la pieza      | Stock Actual      |\n");
                    printf("+---------------+-------------------------+-------------------+\n");
                    for (int i = 0; i < MAX_PIEZAS; i++) {
                        if (strlen(piezasProductos[producto][i]) > 0) {
                            printf("| %-13s | %-23s | %-17d |\n",
                                identificadoresUsados[producto][i],
                                piezasProductos[producto][i],
                                stockPiezas[producto][i]
                            );
                        }
                    }
                    printf("+---------------+-------------------------+-------------------+\n");

                    char identificador[MAX_NOMBRE];

                    
                    int pieza = -1;
                    do {
                        leerCadenaConEspacios("Ingrese el identificador de la pieza (vacio para salir): ", identificador, MAX_NOMBRE);

                        if (strlen(identificador) == 0) {
                            printf("Seleccion cancelada.\n");
                            break;
                        }

                        pieza = buscarPiezaPorIdentificador(producto, identificadoresUsados[producto], identificador, MAX_PIEZAS);
                        if (pieza == -1) {
                            printf("Pieza no encontrada. Intente de nuevo.\n");
                        }
                    } while (pieza == -1 && strlen(identificador) != 0);

                    if (pieza == -1 || strlen(identificador) == 0) {
                        break;
                    }

                    printf("Pieza seleccionada: %s (ID: %s)\n", piezasProductos[producto][pieza], identificadoresUsados[producto][pieza]);
                    printf("Stock actual: %d\n", stockPiezas[producto][pieza]);

                    int cantidad;
                    leerEnteroPositivo("Ingrese la cantidad a agregar: ", &cantidad);
                    stockPiezas[producto][pieza] += cantidad;

                    printf("Stock actualizado exitosamente. Nuevo stock: %d\n", stockPiezas[producto][pieza]);
                    break;
                }

                case 7: {
                    // Visualización del stock de productos terminados
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
                    // Configuración de credenciales y límites máximos
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
                        // Cambiar límites máximos de productos y piezas
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

        // Confirmación para cerrar el programa
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