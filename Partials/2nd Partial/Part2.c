#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int validarNombre(char name[]){
    int j,errors=0;
    if(strlen(name)<4){
        printf("\n\t\t * Lo sentimos, es necesario al menos 4 caracteres  *\n");
        errors++;
    }else{
        if (name[0]<65 || name[0]>90){
            printf("\n\t\t * Lo sentimos, 1er caracter NO es Mayuscula *\n");
            errors++;
        }
        j=1;
        while (j < strlen(name)){
            if (name[j]<97 || name[j]>122){
                if (name[j]==27){
                    if (j+1>strlen(name) && (name[j+1]>=65 && name[j+1]<=90)){
                        j+=2;
                        continue;
                    }else{
                        printf("\n\t\t * Lo sentimos, caracter NO valido luego de un espacio *\n");
                        errors++;
                        break;
                    }
                }else{
                    printf("\n\t\t * Lo sentimos, caracter correspondiente NO es minuscula ni espacio *\n");
                    errors++;
                    break;
                }
            }else{
                j++;
                continue;
            }
        }
    }
    return errors;
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
            //errores=validarMatricula(alu[i].matricula);
            //Falta crear funcion. Preferentemente hacer validacion de caracteres con codigo ascii, parecido a la funcion validarNombre(), para evitar lidiar con int y los ceros a la izq.
            while ((c = getchar()) != '\n' && c != EOF);
        } while (errores>0);

        do{
            printf("Ingrese la 1ra calificacion del alumno %d (del 0.0 al 10.0): ", i+1);
            scanf(" %.1f", &calif[i][0]);
            //errores=validarCalificacion(calif[i][0]);
            //Falta crear funcion. Validar que vaya del 0.0 al 10.0. Recordar que es un flotante
            while ((c = getchar()) != '\n' && c != EOF);
        } while (errores>0);

        do{
            printf("Ingrese la 2da calificacion del alumno %d (del 0.0 al 10.0): ", i+1);
            scanf(" %.1f", &calif[i][1]);
            //errores=validarCalificacion(calif[i][1]);
            //Se usa la misma funcion que en calif[i][0]. Validar que vaya del 0.0 al 10.0. Recordar que es un flotante
            while ((c = getchar()) != '\n' && c != EOF);
        } while (errores>0);
    }
    printf("Lectura hecha. Pasando al menu... \n");
}

void alumnoIniciaExamen(struct alumno alu[], float calif[][NUMPARCIALES], NODO *nodoRaiz){
    int horaTemp, minutoTemp, nListaTemp, errores=0;
    char c;
    do{
        printf("Ingrese el numero de lista del alumno que inicio examen: ");
        scanf(" %d", &nListaTemp);
        //errores=validarNumeroLista(nListaTemp);
        //Crear funcion que valide si el numero de lista esta entre 1 y N, y restarle 1 para coincidir con el indice
        while ((c = getchar()) != '\n' && c != EOF);
    } while (errores>0);

    do{
        printf("Ingrese la hora y minuto en que inicio examen el alumno %d (formato 24 horas, ejemplo: 11 27): ", nListaTemp);
        scanf(" %d %d", &horaTemp, &minutoTemp);
        //errores=validarTiempo(horaTemp,minutoTemp);
        //Crear funcion que valide las horas estan entre 0 y 23, y los minutos entre 0 y 59
        while ((c = getchar()) != '\n' && c != EOF);
    } while (errores>0);
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