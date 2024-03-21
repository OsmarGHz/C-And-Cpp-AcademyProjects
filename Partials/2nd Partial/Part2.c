#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#define N 1
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
    int i, palabra_valida = 0, letras_palabra = 0;

    for (i = 0; nombre[i] != '\0'; i++) {
        // Si encontramos un espacio, reiniciamos el contador de letras de la palabra
        if (isspace(nombre[i])) {
            palabra_valida = 0;
            letras_palabra = 0;
            continue;
        }

        // Comprobamos que el primer caracter de una palabra sea ser mayúscula
        if (!palabra_valida) {
            if (!isupper(nombre[i])) {
                printf("\n\t\t * El nombre debe comenzar con mayuscula *\n");
                return 1; // Codigo de error
            }
            palabra_valida = 1;
        } else {
            // Si es una letra, debe ser minúscula
            if (!islower(nombre[i])) {
                printf("\n\t\t * Las letras del nombre deben estar en minuscula *\n");
                return 1; // Codigo de error
            }
        }

        letras_palabra++;

        // Comprobamos si la palabra tiene al menos dos caracteres
        if (isspace(nombre[i + 1]) && letras_palabra < 2) {
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

int validarCalificacion(float calificacion) {
    // Comprobamos si la calificacion esta dentro del rango permitido
    if (calificacion < 0.0 || calificacion > 10.0) {
        printf("\n\t\t * La calificacion debe estar en el rango de 0.0 a 10.0 *\n");
        return 1; // Indica que hay error
    }

    // Comprobamos que la calificacion tenga como maximo un decimal
    int parte_decimal = (int)(calificacion * 10) % 10;
    if (parte_decimal != 0 && parte_decimal != 5) {
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

void leerAlumnos(struct alumno alu[], float calif[][NUMPARCIALES]){
    int i,errores;
    char c;
    for (i = 0; i < N; i++){
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
            while ((c = getchar()) != '\n' && c != EOF);
        } while (errores>0);

        do{
            printf("Ingrese la 1ra calificacion del alumno %d (del 0.0 al 10.0): ", i+1);
            scanf(" %.1f", &calif[i][0]);
            errores = validarCalificacion(calif[i][0]); // Llamamos a la función validarCalificacion
            while ((c = getchar()) != '\n' && c != EOF);
        } while (errores>0);

        do{
            printf("Ingrese la 2da calificacion del alumno %d (del 0.0 al 10.0): ", i+1);
            scanf(" %.1f", &calif[i][1]);
            errores = validarCalificacion(calif[i][1]); // Llamamos a la misma función validarCalificacion
            while ((c = getchar()) != '\n' && c != EOF);
        } while (errores>0);
    }
    printf("Lectura hecha. Pasando al menu... \n");
}

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


void alumnoIniciaExamen(struct alumno alu[], float calif[][NUMPARCIALES], NODO *nodoRaiz){
    int horaTemp, minutoTemp, nListaTemp, errores=0;
    NODO *nuevo, *aux;
    char c;
    do{
        printf("Ingrese el numero de lista del alumno que inicio examen: ");
        scanf(" %d", &nListaTemp);
        errores = validarNumeroLista(nListaTemp); // Llamamos a la función validarNumeroLista
        while ((c = getchar()) != '\n' && c != EOF);
    } while (errores>0);

    do{
        printf("Ingrese la hora y minuto en que inicio examen el alumno %d (formato 24 horas, ejemplo: 11 27): ", nListaTemp);
        scanf(" %d %d", &horaTemp, &minutoTemp);
        errores = validarTiempo(horaTemp, minutoTemp); // Llamamos a la función validarTiempo
        while ((c = getchar()) != '\n' && c != EOF);
    } while (errores>0);

    nuevo = crearNodo();
    if (nuevo == NULL) printf("\n\t\t * Lo sentimos, algo paso.  *\n");
    if (nodoRaiz == NULL){
        nodoRaiz=nuevo;
    }else{
        aux=nodoRaiz;
        while (aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente=nuevo;        
    }
    
    
}

void alumnoTerminaExamen(){

}

void resultadosFinales(){

}

void menuCiclado(struct alumno alu[], float calif[][NUMPARCIALES], NODO *nodoRaiz){
    int input;
    do{
        printf("\n\t\t * MENU PRINCIPAL *\n");
        printf("\n\t 1. Agregar alumno que ingreso al examen");
        printf("\n\t 2. Un alumno acaba de terminar su examen");
        printf("\n\t 3. FINALIZAR PROGRAMA\n");
        printf("\n Ingrese la letra de la opcion deseada: ");
        scanf(" %d", &input);
        switch (input){
            case 1:
                alumnoIniciaExamen(alu, calif, nodoRaiz);
                break;
            case 2:
                alumnoTerminaExamen();
                break;
            case 3:
                resultadosFinales();
                break;
            default:
                printf("\n\t\t * Lo sentimos, input NO valido. Ingrese un numero del 1 al 3 *\n");
                break;
        }
    } while (input != 3);
    
}

int main(){
    float calificaciones[N][NUMPARCIALES];
    ALUMNO alumnos[N];
    NODO *nodoRaiz = NULL;

    leerAlumnos(alumnos, calificaciones);
    menuCiclado(alumnos, calificaciones, nodoRaiz);
}