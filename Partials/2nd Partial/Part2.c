#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2

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

short validarNombre(char name[]){
    int i;
    short errors=0;
    if(strlen(name)<4){
        printf("\n\t\t * Lo sentimos, es necesario al menos 4 caracteres  *\n");
        errors++;
    }else{
        if (name[0]<65 || name[0]>90){
            printf("\n\t\t * Lo sentimos, 1er caracter NO es Mayuscula *\n");
            errors++;
        }
        i=1;
        while (i < strlen(name)){
            if (name[i]<97 || name[i]>122){
                if (name[i]==27){
                    if (i+1>strlen(name) && (name[i+1]>=65 && name[i+1]<=90)){
                        i+=2;
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
                i++;
                continue;
            }
        }
    }
    return errors;
}

void leerAlumnos(struct alumno alu[]){
    int i;
    char c;
    short errores;
    for (i = 0; i < N; i++){
        do{
            printf("Ingrese el nombre completo del alumno %d (Max. 50 caracteres): ", i+1);
            scanf(" %50[^\n]s", alu[i].nombreComp);
            errores=validarNombre(alu[i].nombreComp);
            while ((c = getchar()) != '\n' && c != EOF); // ALternativa fflush stdin
        } while (errores>0);
    }
    
}

NODO *crearNodo(){
    NODO *nuevo;
    nuevo = (NODO *) malloc(sizeof(NODO));
    return nuevo;
}

int main(){
    int calificaciones[N][3];
    ALUMNO alumnos[N];
    NODO *nodoUnico;
    //struct nodo *nodoUnico = (struct nodo *) malloc(sizeof(struct nodo));
    //NODO *nodoUnico = (NODO *) malloc(sizeof(NODO));

    leerAlumnos(alumnos);
    nodoUnico = crearNodo();

}