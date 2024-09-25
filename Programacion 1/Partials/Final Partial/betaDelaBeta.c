#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo.\n");
        return nuevoNodo;
    }
    strcpy(nuevoNodo->cliente.turno, cliente.turno);
    nuevoNodo->cliente.operacionesPendientes = cliente.operacionesPendientes;
    nuevoNodo->cliente.urgencia = cliente.urgencia;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->cliente.operacionesHechas = cliente.operacionesHechas;
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

void guardarClienteEnArchivoTexto(Cliente cliente) {
    FILE *archivo = fopen("clientes.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de texto.\n");
        return;
    }
    fprintf(archivo, "-------------------\n");
    fprintf(archivo, "Turno: %s\n", cliente.turno);
    fprintf(archivo, "Operaciones totales: %d\n", cliente.operacionesPendientes);
    fprintf(archivo, "Urgencia: %d\n", cliente.urgencia);
    fprintf(archivo, "-------------------\n");

    fclose(archivo);
}

void datosCliente(Cliente cliente){

    printf("-------------------\n");
    printf("Datos del nuevo cliente:\n");
    printf("Turno: %s\n", cliente.turno);
    printf("Pendiente: %d\n", cliente.operacionesPendientes);
    printf("Urgencia: %d\n", cliente.urgencia);
    printf("-------------------\n");
    
}

void pasarAPreHistorial(Nodo** clienteAtendido, Nodo** listaNextReporte){
    
}

void atenderCliente(Nodo** cola, Nodo** listaNextReporte) {
    Nodo* clienteAtendido;
    // Verificar si la cola esta vacia
    if (*cola == NULL) {
        printf("No hay clientes en la cola.\n");
        return;
    }

    // Atender al cliente en la cabeza de la cola
    clienteAtendido = *cola;
    printf("Atendiendo al cliente: %s\n", clienteAtendido->cliente.turno);

    // Reducir el numero de operaciones del cliente (maximo 3)
    if (clienteAtendido->cliente.operacionesPendientes > 3) {
        printf("Este cliente tiene mas de 3 operaciones pendientes.\n");
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
        pasarAPreHistorial(&clienteAtendido, listaNextReporte);
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

// Funcion para guardar los datos de la lista en un archivo binario
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
        fwrite(&(actual->cliente), sizeof(Cliente), 1, archivo);
        actual = actual->siguiente;
    }

    // Cerrar el archivo
    fclose(archivo);
    printf("Datos de la lista guardados en el archivo binario: %s\n", nombreArchivo);
}

// Funcion para cargar la lista desde un archivo binario
Nodo* cargarListaDesdeArchivoBinario(int *contadorTurnos) {
    // Obtener la fecha y hora actual para buscar el archivo correcto
    time_t tiempo = time(NULL);
    struct tm* tiempoLocal = localtime(&tiempo);
    char nombreArchivo[50];
    FILE* archivo, *updater = NULL;
    Nodo* inicio = NULL, *nuevoNodo = NULL, *ultimo = NULL;
    Cliente cliente;

    if((updater=fopen("updater.txt","r")) != NULL) fscanf(updater, "%s", nombreArchivo);
    else nombreArchivo[0] = 0;

    archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("No se encontro un archivo de clientes para cargar.\n");
        printf("Cargando programa desde Cero\n");
        return NULL;
    }

    while (fread(&cliente, sizeof(Cliente), 1, archivo)) {
        nuevoNodo = crearNodo(cliente);
        if (inicio == NULL){
            inicio = nuevoNodo;
            ultimo = nuevoNodo;
        }else{
            ultimo->siguiente = nuevoNodo;
            ultimo = nuevoNodo;
        }
        (*contadorTurnos)++;
    }

    fclose(archivo);
    printf("Datos cargados desde el archivo binario: %s\n", nombreArchivo);
    return inicio;
}

void operacionNuevoCliente(int *contadorTurnos, Nodo** listaClientes){
    Cliente nuevoCliente;
    generarTurno(nuevoCliente.turno, contadorTurnos);
    do{
        printf("\nIngrese el numero de operaciones del cliente:\n");
        scanf("%d", &nuevoCliente.operacionesPendientes);
        if (nuevoCliente.operacionesPendientes < 1){
            printf("\nNumero de operaciones erroneo. Intente de nuevo\n");
        }
    }while (nuevoCliente.operacionesPendientes < 1);

    do{
        printf("\nIngrese el grado de urgencia (mayor que cero):\n");
        scanf("%d", &nuevoCliente.urgencia);
        if (nuevoCliente.urgencia < 1){
            printf("\nNumero de urgencia inexistente. Intente de nuevo");
        }
    }while (nuevoCliente.urgencia < 1);
    nuevoCliente.operacionesHechas = 0;
    insertarPorUrgencia(listaClientes, crearNodo(nuevoCliente));
    datosCliente(nuevoCliente);
}


void menuCiclado(int *contadorTurnos, Nodo **listaClientes, Nodo **listaNextReporte){
    int opcion;

    do {
        printf("\n\tMENU\nOpciones disponibles:\n");
        printf("1. Nuevo cliente\n2. Atender cliente\n3. Salir\n");
        
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                //Crear Nuevo Cliente
                operacionNuevoCliente(contadorTurnos, listaClientes);
                break;
            case 2:
                // Atender cliente
                atenderCliente(listaClientes, listaNextReporte);
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
        // Mostrar el contenido de la cola de prioridades despues de cada operacion
        if (opcion != 3) mostrarFila(*listaClientes);
    } while (opcion != 3);
}


int main() {
    Nodo* listaClientes = NULL, *listaNextReporte = NULL;
    int contadorTurnos=0;

    listaClientes = cargarListaDesdeArchivoBinario(&contadorTurnos);
    menuCiclado(&contadorTurnos, &listaClientes, &listaNextReporte);

    return 0;
}
