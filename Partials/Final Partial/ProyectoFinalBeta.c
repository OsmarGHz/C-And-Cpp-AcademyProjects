#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
Integrantes del equipo:
++ Hernandez Prado Osmar Javier
++ Lopez Momox Limhi Gerson
++ Arenas Cortes Nadia
*/

typedef struct Cliente {
    char turno[10];
    int operacionesPendientes, operacionesHechas, urgencia;
} Cliente;

typedef struct Nodo {
    Cliente cliente;
    struct Nodo* siguiente;
} Nodo;


Nodo* crearNodo(Cliente cliente) {
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevoNodo->cliente.turno, cliente.turno);
    nuevoNodo->cliente.operacionesPendientes = cliente.operacionesPendientes;
    nuevoNodo->cliente.urgencia = cliente.urgencia;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->cliente.operacionesHechas = 0;
    return nuevoNodo;
}

void insertarPorUrgencia (Nodo** lista, Nodo* nuevoNodo){
    Nodo *aux = NULL, *anterior = NULL, *next = NULL;
    int ordenado = 0;

    if (*lista == NULL) {
        *lista = nuevoNodo;
    }else{
        aux = *lista;
        if (nuevoNodo->cliente.urgencia >= aux->cliente.urgencia){
            while (aux->siguiente != NULL && ordenado == 0){
                if (nuevoNodo->cliente.urgencia >= aux->siguiente->cliente.urgencia){
                    aux = aux->siguiente;
                }else{
                    anterior = aux;
                    next = aux->siguiente;
                    anterior->siguiente = nuevoNodo;
                    nuevoNodo->siguiente = next;
                    aux = aux->siguiente;
                    ordenado++;
                }
            }
            if (ordenado==0){
                aux->siguiente=nuevoNodo;
                ordenado++;
            }
        }else{
            nuevoNodo->siguiente = aux;
            *lista = nuevoNodo;
            ordenado++;
        }
    }
}

void generarTurno(char turno[], int *contadorTurnos) {
    int primeraL, segundaL, terceraL, primerDigito, segundoDigito;
    char primerChar, segundoChar, tercerChar;

    terceraL = (*contadorTurnos) % 26;
    segundoDigito = ((*contadorTurnos) / 26) % 10;
    segundaL = ((*contadorTurnos) / 260) % 26;
    primerDigito = ((*contadorTurnos) / 6760) % 10;
    primeraL = ((*contadorTurnos) / 67600) % 26;

    primerChar = 65 + primeraL;
    segundoChar = 65 + segundaL;
    tercerChar = 65 + terceraL;

    sprintf(turno, "%c%d%c%d%c", primerChar, primerDigito, segundoChar, segundoDigito, tercerChar);
    (*contadorTurnos)++;
}


void datosCliente(Cliente cliente){
    printf("Datos del nuevo cliente:\n");
    printf("Turno: %s\n", cliente.turno);
    printf("Operaciones pendientes: %d\n", cliente.operacionesPendientes);
    printf("Grado de urgencia: %d\n", cliente.urgencia);
}

void atenderCliente(Nodo** cola) {
    Nodo* clienteAtendido;
    // Verificar si la cola está vacía
    if (*cola == NULL) {
        printf("No hay clientes en la cola.\n");
        return;
    }

    // Atender al cliente en la cabeza de la cola
    clienteAtendido = *cola;
    printf("Atendiendo al cliente: %s\n", clienteAtendido->cliente.turno);

    // Reducir el número de operaciones del cliente (máximo 3)
    if (clienteAtendido->cliente.operacionesPendientes > 3) {
        printf("Este cliente tiene más de 3 operaciones pendientes.\n");
        clienteAtendido->cliente.operacionesPendientes -= 3;
        clienteAtendido->cliente.operacionesHechas += 3;
        // Mover al cliente al final de la cola
        *cola = clienteAtendido->siguiente;
        clienteAtendido->siguiente = NULL;
        insertarPorUrgencia(cola, clienteAtendido);
    } else {
        clienteAtendido->cliente.operacionesHechas += clienteAtendido->cliente.operacionesPendientes;
        clienteAtendido->cliente.operacionesPendientes = 0;
        // Eliminar al cliente de la cola
        *cola = clienteAtendido->siguiente;
        free(clienteAtendido);
    }

    printf("Cliente atendido.\n");
}

void mostrarFila(Nodo* cola) {
    printf("Clientes en la cola de prioridades:\n");
    Nodo* temp = cola;
    while (temp != NULL) {
        printf("Identificador: %s - Urgencia: %d - Operaciones restantes: %d\n",
               temp->cliente.turno, temp->cliente.urgencia, temp->cliente.operacionesPendientes);
        temp = temp->siguiente;
    }
}

void liberarLista(Nodo* lista) {
    Nodo* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->siguiente;
        free(temp);
    }
}

// Función para guardar los datos de la lista en un archivo binario
void guardarListaEnArchivoBinario(Nodo* cola) {
    // Obtener la fecha y hora actual para formar el nombre del archivo
    time_t tiempo = time(NULL);
    struct tm* tiempoLocal = localtime(&tiempo);
    char nombreArchivo[50];
    FILE* archivo = NULL, *updater = NULL;
    Nodo* actual;

    sprintf(nombreArchivo, "clientes%02d%02d%02d%02d%02d.bin", tiempoLocal->tm_mday, tiempoLocal->tm_mon + 1,
            tiempoLocal->tm_year - 100, tiempoLocal->tm_hour, tiempoLocal->tm_min);

    if((updater=fopen("updater.txt","w")) != NULL){
        fprintf(updater, "%s", nombreArchivo);
    }

    // Abrir el archivo binario en modo escritura
    archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    // Recorrer la lista y escribir cada nodo en el archivo binario
    actual = cola;
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
    FILE* archivo, *updater = NULL;
    Nodo* inicio = NULL, *nuevoNodo = NULL;
    Cliente cliente;

    if((updater=fopen("updater.txt","r")) != NULL){
        fscanf(updater, "%s", nombreArchivo);
    }else{
        nombreArchivo[0] = 0;
    }

    archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("No se encontró un archivo de clientes para cargar.\n");
        printf("Cargando programa desde Cero\n");
        return NULL;
    }

    while (fread(&cliente, sizeof(Cliente) - sizeof(struct Cliente *), 1, archivo)) {
        nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
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


void menuCiclado(int *contadorTurnos, Nodo **listaClientes){
    int opcion;
    Cliente nuevoCliente;
    do {
        printf("\n\tMENU\nOpciones disponibles:\n");
        printf("1. Nuevo cliente\n2. Atender cliente\n3. Salir\n");
        
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                generarTurno(nuevoCliente.turno, contadorTurnos);
                do{
                    printf("Ingrese el numero de operaciones del cliente: ");
                    scanf("%d", &nuevoCliente.operacionesPendientes);
                    if (nuevoCliente.operacionesPendientes < 1){
                        printf("Numero de operaciones erroneo. Intente de nuevo\n");
                    }
                }while (nuevoCliente.operacionesPendientes < 1);

                do{
                    printf("Ingrese el grado de urgencia (mayor que cero): ");
                    scanf("%d", &nuevoCliente.urgencia);
                    if (nuevoCliente.urgencia < 1){
                        printf("Numero de urgencia inexistente. Intente de nuevo");
                    }
                }while (nuevoCliente.urgencia < 1);

                insertarPorUrgencia(listaClientes, crearNodo(nuevoCliente));
                datosCliente(nuevoCliente);
                break;
            case 2:
                // Atender cliente
                atenderCliente(listaClientes);
                break;
            case 3:
                // Guardar los datos de la lista en un archivo binario
                guardarListaEnArchivoBinario(*listaClientes);
                liberarLista(*listaClientes);
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Por favor, seleccione nuevamente.\n");
                break;
        }
        // Mostrar el contenido de la cola de prioridades después de cada operación
        if (opcion != 3) mostrarFila(*listaClientes);
    } while (opcion != 3);
}


int main() {
    Nodo* listaClientes = NULL;
    int contadorTurnos=0;

    listaClientes = cargarListaDesdeArchivoBinario();
    menuCiclado(&contadorTurnos, &listaClientes);

    return 0;
}
