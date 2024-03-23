#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>
#include <malloc.h>
#define N 2
#define NUMPARCIALES 3

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

int validarCalificacion(float calificacion) {
    int parteDecimal;
    // Comprobamos si la calificacion esta dentro del rango permitido
    if (calificacion < 0.0 || calificacion > 10.0) {
        printf("\n\t\t * La calificacion debe estar en el rango de 0.0 a 10.0 *\n");
        return 1; // Indica que hay error
    }

    // Comprobamos que la calificacion tenga como maximo un decimal
    parteDecimal = (int)(calificacion * 10) % 10;
    if (parteDecimal != 0 && parteDecimal != 5) {
        printf("\n\t\t * La calificacion debe tener como maximo un decimal *\n");
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
    char c;
    do{
            printf("Ingrese el nombre completo del alumno %d (Max. 50 caracteres): ", i+1);
            scanf(" %50[^\n]s", alu[i].nombreComp);
            errores=validarNombre(alu[i].nombreComp);
            while ((c = getchar()) != '\n' && c != EOF);
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
            while ((c = getchar()) != '\n' && c != EOF);
        } while (errores>0);
}

void leerCalifAlumnos(int i, float calif[][NUMPARCIALES]){
    int errores;
    char c;
    do{
        printf("Ingrese la 1ra calificacion del alumno %d (del 0.0 al 10.0): ", i+1);
        scanf(" %f", &calif[i][0]);
        errores = validarCalificacion(calif[i][0]); // Llamamos a la función validarCalificacion
        while ((c = getchar()) != '\n' && c != EOF);
    } while (errores>0);

    do{
        printf("Ingrese la 2da calificacion del alumno %d (del 0.0 al 10.0): ", i+1);
        scanf(" %f", &calif[i][1]);
        errores = validarCalificacion(calif[i][1]); // Llamamos a la misma función validarCalificacion
        while ((c = getchar()) != '\n' && c != EOF);
    } while (errores>0);
}

/*
int validarTiempo(int hora, int minuto) {
    // Comprobamos si la hora está en el rango correcto
    if (hora < 0 || hora > 23) {
        printf("\n\t\t * La hora debe estar en el rango de 0 a 23 *\n");
        return 1; // Indicamos que hay un error
    }

    // Comprobamos si los minutos están en el rango correcto
    if (minuto < 0 || minuto > 59) {
        printf("\n\t\t * Los minutos deben estar en el rango de 0 a 59 *\n");
        return 1; // Indica que tuvimos un error
    }
    return 0; // No hay errores
}
*/

void horaActual(int *hora, int *minuto) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    *hora = timeinfo->tm_hour;
    *minuto = timeinfo->tm_min;
}


void alumnoIniciaExamen(struct alumno alu[], float calif[][NUMPARCIALES], NODO **nodoRaiz){
    int horaTemp, minutoTemp, nListaTemp, errores=0;
    NODO *nuevo, *aux;
    char c;
    do{
        printf("Ingrese el numero de lista del alumno que inicio examen: ");
        scanf(" %d", &nListaTemp);
        errores = validarNumeroLista(nListaTemp); // Llamamos a la función validarNumeroLista
        while ((c = getchar()) != '\n' && c != EOF);
    } while (errores>0);

    horaActual(&horaTemp, &minutoTemp); // Llamamos a la funcion horaActual para obtener la hora y minutos actuales

    nuevo = crearNodo();
    if (nuevo == NULL) printf("\n\t\t * Lo sentimos, algo paso.  *\n");
    nuevo->nLista = nListaTemp;
    nuevo->marcaDeTiempo.hora = horaTemp;
    nuevo->marcaDeTiempo.minuto = minutoTemp;
    if (*nodoRaiz == NULL){
        *nodoRaiz=nuevo;
    }else{
        aux=*nodoRaiz;
        while (aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente=nuevo;
    }
}

void alumnoTerminaExamen(struct alumno alu[], float calif[][NUMPARCIALES], NODO **nodoRaiz){
    int horaTemp, minutoTemp, nListaTemp, errores=0;
    NODO *aux, *anterior;
    char c;
    if (*nodoRaiz == NULL){
        printf("\n\t\t * Lo sentimos, NO HAY ALUMNOS HACIENDO EXAMEN  *\n");
    }else{
        do{
            printf("Ingrese el numero de lista del alumno que acabo examen: ");
            scanf(" %d", &nListaTemp);
            errores = validarNumeroLista(nListaTemp); // Llamamos a la función validarNumeroLista
            while ((c = getchar()) != '\n' && c != EOF);
            if (errores==0){
                aux=*nodoRaiz;
                if ((*nodoRaiz)->nLista == nListaTemp){
                    *nodoRaiz = (*nodoRaiz)->siguiente;
                    free(aux);
                    printf("\n\t * Alumno encontrado  *\n");
                    do{
                        printf("Que calificacion obtuvo? (del 0.0 al 10.0): ");
                        scanf(" %f", &calif[nListaTemp-1][2]);
                        errores = validarCalificacion(calif[nListaTemp-1][2]); // Llamamos a la misma función validarCalificacion
                        while ((c = getchar()) != '\n' && c != EOF);
                    } while (errores>0);
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
                        free(aux);
                    }
                }
            }
        } while (errores>0);
    }
}

void resultadosFinales(){

}

void imprimirMenu() {
    printf("\n\t\t * MENU PRINCIPAL *\n");
    printf("\n\t 1. Agregar alumno que ingreso al examen");
    printf("\n\t 2. Un alumno acaba de terminar su examen");
    printf("\n\t 3. FINALIZAR PROGRAMA\n");
    printf("\n Ingrese la opcion deseada: ");
}

void menuCiclado(struct alumno alu[], float calif[][NUMPARCIALES], NODO **nodoRaiz){
    int input;
    printf("Lectura hecha. Pasando al menu... \n");
    do{
        imprimirMenu();
        scanf(" %d", &input);

        switch (input){
            case 1:
                alumnoIniciaExamen(alu, calif, nodoRaiz);
                break;
            case 2:
                alumnoTerminaExamen(alu, calif, nodoRaiz);
                break;
            case 3:
                resultadosFinales();
                break;
            default:
                printf("\n\t\t * Input NO valido. Ingrese un numero del 1 al 3 *\n");
                break;
        }
    } while (input != 3);
}

/*
void leerMat(float mat[][NUMPARCIALES]){
    int i;
    for (i = 0; i < N; i++){
        scanf(" %f",&mat[i][0]);
        scanf(" %f",&mat[i][1]);
        scanf(" %f",&mat[i][2]);
        printf(" %f %f %f", mat[i][0], mat[i][1], mat[i][2]);
    }
}

void escribirMat(float mat[][NUMPARCIALES]){
    int i;
    for (i = 0; i < N; i++){
        printf(" %f %f %f", mat[i][0], mat[i][1], mat[i][2]);
    }
}
*/

int main(){
    int i;
    float calificaciones[N][NUMPARCIALES];
    /*leerMat(calificaciones);
    escribirMat(calificaciones);*/
    ALUMNO alumnos[N];
    NODO *nodoRaiz = NULL;

    for (i = 0; i < N; i++){
        leerAlumnos(i, alumnos);
        leerCalifAlumnos(i, calificaciones);
    }
    menuCiclado(alumnos, calificaciones, &nodoRaiz);
}