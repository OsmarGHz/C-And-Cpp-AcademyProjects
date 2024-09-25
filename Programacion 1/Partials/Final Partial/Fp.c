#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

typedef struct nodo{
    int nivelUrgencia, operaPendientes, operaHechas;
    char turno[10];
    struct nodo *siguiente;
} NODO;

NODO *crearNodo(){
    NODO *nuevo = NULL;
    nuevo = (NODO *) malloc(sizeof(NODO));
    if(nuevo != NULL){
        nuevo->siguiente=NULL;
    }
    return nuevo;
}

NODO *crearNodoConDato(int info){
    NODO *nuevo = NULL;
    nuevo = (NODO *) malloc(sizeof(NODO));
    if(nuevo != NULL){
        nuevo->dato = info;
        nuevo->siguiente = NULL;
    }
    return nuevo;
}

NODO *insertarAlFinal (int info, NODO *nodoRaiz){
    NODO *nuevo = NULL, *aux = NULL;
    nuevo = crearNodoConDato(info);
    if (nuevo==NULL) return NULL;

    if (nodoRaiz == NULL){
        nodoRaiz=nuevo;
    }else{
        aux=nodoRaiz;
        while (aux->siguiente != NULL){ aux = aux->siguiente; }
        aux->siguiente=nuevo;
    }
    return nodoRaiz;
}

int main(){

}