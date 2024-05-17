#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructura para representar un cliente en la cola de prioridades
typedef struct Cliente {
    char identificador[7]; // Identificador único alfanumérico
    int operaciones;       // Número de operaciones que necesita realizar
    int urgencia;          // Nivel de urgencia (1-10)
    int turno;             // Turno del cliente
    struct Cliente *siguiente; // Puntero al siguiente cliente en la cola
} Cliente;

// Definición de la estructura Nodo
typedef struct Nodo {
    Cliente cliente;
    struct Nodo* siguiente;
} Nodo;

// Función para inicializar la lista ligada (cola de prioridades)
void inicializarLista(Nodo** cola) {
    *cola = NULL;
    printf("Lista ligada inicializada.\n");
}

// Función para generar un identificador único para cada cliente
void generarIdentificador(Cliente *cliente) {
    static int contador = 1; // Iniciar el contador en 1
    static char letra = 'A'; // Iniciar la letra en 'A'
    
    // Asignar el primer carácter según la urgencia del cliente
    cliente->identificador[0] = cliente->urgencia + '0';
    
    // Asignar los siguientes dos caracteres como letras mayúsculas
    cliente->identificador[1] = letra;
    cliente->identificador[2] = letra;
    
    // Asignar los siguientes cuatro caracteres como números
    sprintf(cliente->identificador + 3, "%04d", contador);
    
    // Incrementar el contador y, si llega a 9999, cambiar la letra y reiniciar el contador
    contador++;
    if (contador > 9999) {
        contador = 1;
        letra++;
        if (letra > 'Z') {
            letra = 'A';
        }
    }
    
    // Agregar el terminador de cadena al final del identificador
    cliente->identificador[7] = '\0';
}

// Función para agregar un nuevo cliente a la cola de prioridades
void agregarCliente(Nodo** cola) {
    Cliente nuevoCliente;
    printf("Ingrese el número de operaciones del cliente: ");
    scanf("%d", &nuevoCliente.operaciones);
    printf("Ingrese el nivel de urgencia del cliente (1-10): ");
    scanf("%d", &nuevoCliente.urgencia);

    // Generar identificador único para el cliente
    generarIdentificador(nuevoCliente.identificador);

    // Asignar turno al cliente
    nuevoCliente.turno = 0;

    // Crear un nuevo nodo para el cliente
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo cliente.\n");
        return;
    }
    nuevoNodo->cliente = nuevoCliente;
    nuevoNodo->siguiente = NULL;

    // Caso 1: La cola está vacía o el nuevo cliente tiene mayor urgencia que el primero
    if (*cola == NULL || nuevoCliente.urgencia < (*cola)->cliente.urgencia) {
        nuevoNodo->siguiente = *cola;
        *cola = nuevoNodo;
    }
    else {
        // Caso 2: El nuevo cliente debe insertarse en medio de la cola
        Nodo* temp = *cola;
        while (temp->siguiente != NULL && temp->siguiente->cliente.urgencia <= nuevoCliente.urgencia) {
            temp = temp->siguiente;
        }
        nuevoNodo->siguiente = temp->siguiente;
        temp->siguiente = nuevoNodo;
    }

    printf("Cliente agregado a la cola de prioridades.\n");
}

// Función para atender a un cliente de la cola de prioridades
void atenderCliente(Nodo** cola) {
    // Verificar si la cola está vacía
    if (*cola == NULL) {
        printf("No hay clientes en la cola.\n");
        return;
    }

    // Atender al cliente en la cabeza de la cola
    Nodo* clienteAtendido = *cola;
    printf("Atendiendo al cliente: %s\n", clienteAtendido->cliente.identificador);

    // Reducir el número de operaciones del cliente (máximo 3)
    if (clienteAtendido->cliente.operaciones > 3) {
        printf("Este cliente tiene más de 3 operaciones.\n");
        clienteAtendido->cliente.operaciones -= 3;
        // Mover al cliente al final de la cola
        *cola = clienteAtendido->siguiente;
        clienteAtendido->siguiente = NULL;
        Nodo* temp = *cola;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = clienteAtendido;
    } else {
        clienteAtendido->cliente.operaciones = 0;
        // Eliminar al cliente de la cola
        *cola = clienteAtendido->siguiente;
        free(clienteAtendido);
    }

    printf("Cliente atendido.\n");
}

// Función para liberar la memoria de la lista ligada (cola de prioridades)
void liberarLista(Nodo* cola) {
    Nodo* temp;
    while (cola != NULL) {
        temp = cola;
        cola = cola->siguiente;
        free(temp);
    }
}

// Función para mostrar el contenido de la cola de prioridades, incluyendo el número de operaciones restantes
void mostrarFila(Nodo* cola) {
    printf("Clientes en la cola de prioridades:\n");
    Nodo* temp = cola;
    while (temp != NULL) {
        printf("Identificador: %s - Urgencia: %d - Operaciones restantes: %d\n",
               temp->cliente.identificador, temp->cliente.urgencia, temp->cliente.operaciones);
        temp = temp->siguiente;
    }
}


// Función para mostrar el menú de operaciones disponibles
void mostrarMenu() {
    printf("\nMENU\n");
    printf("1. Nuevo cliente\n");
    printf("2. Atender cliente\n");
    printf("3. Salir\n");
}

// Función para guardar los datos de la lista en un archivo binario
void guardarListaEnArchivoBinario(Nodo* cola) {
    // Obtener la fecha y hora actual para formar el nombre del archivo
    time_t tiempo = time(NULL);
    struct tm* tiempoLocal = localtime(&tiempo);
    char nombreArchivo[50];
    sprintf(nombreArchivo, "clientes%02d%02d%02d%02d%02d.bin", tiempoLocal->tm_mday, tiempoLocal->tm_mon + 1,
            tiempoLocal->tm_year + 1900, tiempoLocal->tm_hour, tiempoLocal->tm_min);

    // Abrir el archivo binario en modo escritura
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    // Recorrer la lista y escribir cada nodo en el archivo binario
    Nodo* actual = cola;
    while (actual != NULL) {
        fwrite(&(actual->cliente), sizeof(Cliente) - sizeof(struct Cliente *), 1, archivo);
        actual = actual->siguiente;
    }

    // Cerrar el archivo
    fclose(archivo);
    printf("Datos de la lista guardados en el archivo binario: %s\n", nombreArchivo);
}

// Función para cargar la lista desde un archivo binario
Nodo* cargarListaDesdeArchivoBinario() {
    // Obtener la fecha y hora actual para buscar el archivo correcto
    time_t tiempo = time(NULL);
    struct tm* tiempoLocal = localtime(&tiempo);
    char nombreArchivo[50];
    sprintf(nombreArchivo, "clientes%02d%02d%02d%02d%02d.bin", tiempoLocal->tm_mday, tiempoLocal->tm_mon + 1,
            tiempoLocal->tm_year + 1900, tiempoLocal->tm_hour, tiempoLocal->tm_min);

    FILE* archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("No se encontró un archivo de clientes para cargar.\n");
        return NULL;
    }

    Nodo* inicio = NULL;
    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente) - sizeof(struct Cliente *), 1, archivo)) {
        Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
        if (nuevoNodo == NULL) {
            printf("Error: No se pudo asignar memoria para el nuevo nodo.\n");
            return inicio;
        }
        nuevoNodo->cliente = cliente;
        nuevoNodo->siguiente = inicio;
        inicio = nuevoNodo;
    }

    fclose(archivo);
    printf("Datos cargados desde el archivo binario: %s\n", nombreArchivo);
    return inicio;
}

// Función principal
int main() {
    // Declarar la cola de prioridades
    Nodo* colaPrioridades;

    // Cargar automáticamente la última lista creada al iniciar el programa
    colaPrioridades = cargarListaDesdeArchivoBinario();

    // Inicializar la cola de prioridades si no se cargó ninguna lista
    if (colaPrioridades == NULL) {
        inicializarLista(&colaPrioridades);
    }

    int opcion;
    do {
        // Mostrar el menú de operaciones
        mostrarMenu();

        // Leer la opción del usuario
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        // Realizar la operación correspondiente
        switch(opcion) {
            case 1:
                // Agregar un nuevo cliente a la cola de prioridades
                agregarCliente(&colaPrioridades);
                break;
            case 2:
                // Atender a un cliente de la cola de prioridades
                atenderCliente(&colaPrioridades);
                break;
            case 3:
                // Guardar los datos de la lista en un archivo binario
                guardarListaEnArchivoBinario(colaPrioridades);
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida. Por favor seleccione una opción válida.\n");
        }

        // Mostrar el contenido de la cola de prioridades después de cada operación
        mostrarFila(colaPrioridades);
    } while (opcion != 3);

    // Liberar la memoria de la lista antes de salir del programa
    liberarLista(colaPrioridades);

    return 0;
}
