#include <stdio.h>
#include <stdlib.h>
#define N 2

typedef struct{
    int hora, minuto;
} TIMESTAMP;

typedef struct{
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
    return nuevo;
}

int main(){
    int calificaciones[N][3];
    ALUMNO alumnos[N];
    NODO *nodoUnico;
    //struct nodo *nodoUnico = (struct nodo *) malloc(sizeof(struct nodo));
    //NODO *nodoUnico = (NODO *) malloc(sizeof(NODO));
    
    nodoUnico = crearNodo();

}