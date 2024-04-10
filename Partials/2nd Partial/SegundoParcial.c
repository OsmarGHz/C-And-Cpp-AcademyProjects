#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include <malloc.h>
#define N 2

/*
Integrantes del equipo:
++ Hernandez Prado Osmar Javier
++ Lopez Momox Limhi Gerson
*/

typedef struct{
    int hora, minuto;
} TIMESTAMP;

typedef struct alumno{
    char nombreComp [60];
    char matricula [10];
    int minutosTardados;
} ALUMNO;

typedef struct nodo{
    int nLista;
    TIMESTAMP marcaDeTiempo;
    struct nodo *siguiente;
} NODO;

NODO *crearNodo(){
    NODO *nuevo;
    nuevo = (NODO *) malloc(sizeof(NODO));
    if(nuevo != NULL){
        nuevo->siguiente=NULL;
    }
    return nuevo;
}

void limpiarBuffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarNombre(const char nombre[]) {
    int i, palabraValida = 0, letrasPalabra = 0;

    for (i = 0; nombre[i] != '\0'; i++) {
        // Si encontramos un espacio, reiniciamos el contador de letras de la palabra
        if (isspace(nombre[i])) {
            palabraValida = 0;
            letrasPalabra = 0;
            continue;
        }

        // Comprobamos que el primer caracter de una palabra sea ser mayúscula
        if (!palabraValida) {
            if (!isupper(nombre[i])) {
                printf("\n\t\t * El nombre debe comenzar con mayuscula *\n");
                return 1; // Codigo de error
            }
            palabraValida = 1;
        } else {
            // Si es una letra, debe ser minúscula
            if (!islower(nombre[i])) {
                printf("\n\t\t * Las letras del nombre deben estar en minuscula *\n");
                return 1; // Codigo de error
            }
        }

        letrasPalabra++;

        // Comprobamos si la palabra tiene al menos dos caracteres
        if (isspace(nombre[i + 1]) && letrasPalabra < 2) {
            printf("\n\t\t * Cada palabra del nombre debe tener al menos dos caracteres *\n");
            return 1; // Codigo de error
        }
    }
    return 0; // Sin errores
}

int validarMatricula(const char matricula[]) {
    int i, errors = 0;

    // Comprobamos si la longitud de la matricula es exactamente 10 caracteres
    if (strlen(matricula) != 10) {
        printf("\n\t\t * La matricula debe tener exactamente 10 digitos *\n");
        errors++;
    }else{
        // Comprobamos que todos los caracteres sean digitos
        for (i = 0; i < 10; i++) {
            if (!isdigit(matricula[i])) {
                printf("\n\t\t * La matricula debe contener solo digitos *\n");
                errors++;
                break;
            }
        }
    }
    return errors;
}

int validarMatriculaRepetida(const char matricula[], const struct alumno alu[], int index) {
    int i;

    for (i = 0; i < index; i++) {
        if (strcmp(alu[i].matricula, matricula) == 0) {
            printf("\n\t\t * La matricula ingresada ya existe para otro alumno *\n");
            return 1; // Matrícula repetida encontrada
        }
    }
    return 0; // No se encontraron matrículas repetidas
}

int validarCalificacion(double calificacion) {
    int parteDecimal;
    // Comprobamos si la calificacion esta dentro del rango permitido
    if (calificacion < 0.0 || calificacion > 10.0) {
        printf("\n\t\t * La calificacion debe estar en el rango de 0.0 a 10.0 *\n");
        return 1; // Indica que hay error
    }
    return 0; // Sin errores
}

int validarNumeroLista(int numeroLista) {
    // Comprobamos si el numero de lista está en el rango permitido
    if (numeroLista < 1 || numeroLista > N) {
        printf("\n\t\t * El numero de lista debe estar en el rango de 1 a %d *\n", N);
        return 1; // Indica que hubo un error
    }
    return 0; // Sin errores
}

void leerAlumnos(int i, struct alumno alu[]){
    int errores=0;
    do{
        printf("Ingrese el nombre completo del alumno %d (Max. 50 caracteres): ", i+1);
        scanf(" %50[^\n]s", alu[i].nombreComp);
        errores=validarNombre(alu[i].nombreComp);
        limpiarBuffer();
    } while (errores>0);

    do{
        printf("Ingrese la matricula del alumno %d (10 caracteres): ", i+1);
        scanf(" %10[^\n]s", alu[i].matricula);
        errores = validarMatricula(alu[i].matricula); // Llamamos a la función validarMatricula
        if (errores == 0) {
            errores = validarMatriculaRepetida(alu[i].matricula, alu, i); // Llamamos a la función validarMatriculaRepetida
            if (errores == 1) {
                continue; // Volver a solicitar la matrícula
            }
        }
        limpiarBuffer();
    } while (errores>0);

    alu[i].minutosTardados=0;
}

void leerUnaCalificacion(int i, int currentPartial, double calif[][3]){
    int errores;
    do{
        printf("Ingrese la ");
        switch (currentPartial){
            case 0: printf("1ra"); break;
            case 1: printf("2da"); break;
            case 2: printf("3ra"); break;
            default: printf("rangoDesconocido"); break;
        }
        printf(" calificacion del alumno %d (del 0.0 al 10.0, se usara 1 solo decimal): ", i+1);
        scanf(" %lf", &calif[i][currentPartial]);
        errores = validarCalificacion(calif[i][currentPartial]); // Llamamos a la función validarCalificacion
        limpiarBuffer();
    } while (errores>0);
    
}

void leerCalifAlumnos(int i, double calif[][3]){
    leerUnaCalificacion(i,0,calif);
    leerUnaCalificacion(i,1,calif);
    calif[i][2]=-1; //Esta calificacion NO se valida, ya que luego se define si acabo o no el examen
}

void horaActual(int *hora, int *minuto) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    *hora = timeinfo->tm_hour;
    *minuto = timeinfo->tm_min;
}

void insertarInfoNodo(int nListaTemp, int horaTemp, int minutoTemp, NODO **nuevo){
    (*nuevo)->nLista = nListaTemp;
    (*(*nuevo)).marcaDeTiempo.hora = horaTemp;
    (*nuevo)->marcaDeTiempo.minuto = minutoTemp;
}

void agregadoDeAlumnoNodo(int nListaTemp, int horaTemp, int minutoTemp, NODO **nodoRaiz){
    int errores = 0;
    NODO *nuevo, *aux;
    errores=0;
    if (*nodoRaiz == NULL){
        nuevo = crearNodo();
        if (nuevo == NULL) printf("\n\t\t * Lo sentimos, algo paso.  *\n");
        insertarInfoNodo(nListaTemp, horaTemp, minutoTemp, &nuevo);
        *nodoRaiz=nuevo;
        printf("\n\t * ALUMNO AGREGADO AL EXAMEN  *\n");
    }else{
        aux=*nodoRaiz;
        if (aux->nLista==nListaTemp) errores++;
        while (aux->siguiente != NULL){
            aux = aux->siguiente;
            if (aux->nLista==nListaTemp) errores++;
        }
        if (errores==0){
            nuevo = crearNodo();
            if (nuevo == NULL) printf("\n\t\t * Lo sentimos, algo paso.  *\n");
            insertarInfoNodo(nListaTemp, horaTemp, minutoTemp, &nuevo);
            aux->siguiente=nuevo;
            printf("\n\t * ALUMNO AGREGADO AL EXAMEN  *\n");
        }else{
            printf("\n\t\t * Se encontro un alumno repetido. No se hara nada.  *\n");
        }
    }
}

void alumnoIniciaExamen(NODO **nodoRaiz){
    int horaTemp, minutoTemp, nListaTemp, errores=0;
    do{
        printf("Ingrese el numero de lista del alumno que inicio examen: ");
        scanf(" %d", &nListaTemp);
        errores = validarNumeroLista(nListaTemp); // Llamamos a la función validarNumeroLista
        limpiarBuffer();
    } while (errores>0);

    horaActual(&horaTemp, &minutoTemp); // Llamamos a la funcion horaActual para obtener la hora y minutos actuales
    agregadoDeAlumnoNodo(nListaTemp, horaTemp, minutoTemp, nodoRaiz);
}

void alumnoAEliminarEncontrado(int nListaTemp, struct alumno alu[], double calif[][3], NODO **aux){
    int horaTemp, minutoTemp, tiempoTardado = 0;
    printf("\n\t * Alumno encontrado  *\nSe tomara la hora del sistema para calcular los tiempos\n");
    horaActual(&horaTemp, &minutoTemp);

    // Calcular el tiempo tardado en minutos
    tiempoTardado = (horaTemp - (*aux)->marcaDeTiempo.hora) * 60 + (minutoTemp - (*aux)->marcaDeTiempo.minuto);
            
    // Asignar el tiempo tardado al alumno correspondiente
    alu[nListaTemp-1].minutosTardados = tiempoTardado;

    // Limpiar la estructura de nodo
    free(*aux);

    printf("Que calificacion obtuvo? ");
    leerUnaCalificacion(nListaTemp-1,2,calif);
}

int eliminadorDeAlumnoNodo(struct alumno alu[], double calif[][3], NODO **nodoRaiz){
    NODO *aux, *anterior;
    int errores = 0, nListaTemp;
    printf("Ingrese el numero de lista del alumno que acabo examen: ");
    scanf(" %d", &nListaTemp);
    errores = validarNumeroLista(nListaTemp); // Llamamos a la función validarNumeroLista
    limpiarBuffer();
    if (errores==0){
        aux=*nodoRaiz;
        if ((*nodoRaiz)->nLista == nListaTemp){
            *nodoRaiz = (*nodoRaiz)->siguiente;
            alumnoAEliminarEncontrado(nListaTemp, alu, calif, &aux);
        }else{
            aux=*nodoRaiz;
            anterior=*nodoRaiz;
            while (aux != NULL){
                if (aux->nLista == nListaTemp) break;
                anterior = aux;
                aux = aux->siguiente;
            }
            if (aux == NULL){
                printf("\n\t\t * Lo sentimos, no se encontro el dato.  *\n");
                errores++;
            }else{
                anterior->siguiente = aux->siguiente;
                alumnoAEliminarEncontrado(nListaTemp, alu, calif, &aux);
            }
        }
    }
    return errores;
}

void alumnoTerminaExamen(struct alumno alu[], double calif[][3], NODO **nodoRaiz){
    int errores=0;
    if (*nodoRaiz == NULL){
        printf("\n\t\t * Lo sentimos, NO HAY ALUMNOS HACIENDO EXAMEN  *\n");
    }else{
        do{
            errores = eliminadorDeAlumnoNodo(alu, calif, nodoRaiz);
        } while (errores>0);
    }
}

void resultadosFinales(NODO **nodoRaiz, struct alumno alu[], double calif[][3]) {
    NODO *aux;
    int i;
    printf("\n\t\t * RESULTADOS FINALES *\n");
    printf("\nN.L\tNombre del Alumno\tMatricula\tTiempo Tardado (minutos)\tCalific 1\tCalif 2\tCalif 3\n");

    while (*nodoRaiz != NULL){
        aux=*nodoRaiz;
        *nodoRaiz = (*nodoRaiz)->siguiente;
        free(aux);
    }
    for (i = 0; i < N; i++){
        if (calif[i][2]==-1) calif[i][2]=5;
        printf("%d\t%s\t%s\t%d\t%.1lf\t%.1lf\t%.1lf\n", i+1, alu[i].nombreComp, alu[i].matricula, alu[i].minutosTardados, calif[i][0], calif[i][1], calif[i][2]);
    }
}

void imprimirMenu() {
    printf("\n\t\t * MENU PRINCIPAL *\n");
    printf("\n\t 1. Agregar alumno que ingreso al examen");
    printf("\n\t 2. Un alumno acaba de terminar su examen");
    printf("\n\t 3. FINALIZAR PROGRAMA\n");
    printf("\n Ingrese la opcion deseada: ");
}

void menuCiclado(struct alumno alu[], double calif[][3], NODO **nodoRaiz) {
    int input;
    do {
        imprimirMenu();
        scanf(" %d", &input);

        switch (input) {
            case 1:
                alumnoIniciaExamen(nodoRaiz);
                break;
            case 2:
                alumnoTerminaExamen(alu, calif, nodoRaiz);
                break;
            case 3:
                resultadosFinales(nodoRaiz, alu, calif); // Llamar a resultadosFinales con los datos de los alumnos
                break;
            default:
                printf("\n\t\t * Input NO valido. Ingrese un numero del 1 al 3 *\n");
                break;
        }
    } while (input != 3);
}

int main(){
    int i;
    double calificaciones[N][3];
    ALUMNO alumnos[N];
    NODO *nodoRaiz = NULL;

    for (i = 0; i < N; i++){
        leerAlumnos(i, alumnos);
        leerCalifAlumnos(i, calificaciones);
    }
    menuCiclado(alumnos, calificaciones, &nodoRaiz);
}