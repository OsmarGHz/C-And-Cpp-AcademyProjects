#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <malloc.h>

typedef struct nodo{
    int nLista,dato;
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

NODO *insertarOrdenadamente (int info, NODO *nodoRaiz){
    NODO *nuevo = NULL, *aux = NULL, *anterior = NULL, *next;
    int ordenado = 0;
    nuevo = crearNodoConDato(info);
    if (nuevo==NULL) return NULL;

    if (nodoRaiz == NULL){
        nodoRaiz=nuevo;
    }else{
        aux=nodoRaiz;
        if (nuevo->dato > aux->dato){
            while (aux->siguiente != NULL && ordenado == 0){
                if (nuevo->dato > aux->siguiente->dato){
                    aux = aux->siguiente;
                    aux->siguiente=nuevo;
                }else{
                    anterior = aux;
                    next = aux->siguiente;
                    anterior->siguiente = nuevo;
                    nuevo->siguiente = next;
                    aux = aux->siguiente;
                    ordenado++;
                }
            }
        }else{
            nuevo->siguiente = aux;
            nodoRaiz = nuevo;
        }
    }
    return nodoRaiz;
}

NODO *eliminaNodo (int info, NODO *nodoRaiz){
    NODO *aux = NULL, *anterior = NULL;
    if (nodoRaiz != NULL){
        aux = nodoRaiz;
        if(nodoRaiz->dato == info){
            nodoRaiz = nodoRaiz->siguiente;
            free(aux); //Encontrado
        }else{
            aux = nodoRaiz;
            anterior = nodoRaiz;
            while (aux != NULL){
                if(aux->dato == info) break;
                anterior = aux;
                aux = aux->siguiente;
            }
            if(aux==NULL) return nodoRaiz; /* Dato no encontrado */
            anterior->siguiente = aux->siguiente;
            free(aux); //Encontrado
        }
    }
    return nodoRaiz;
}

void intermediario(NODO **nodoRaiz){
    *nodoRaiz = insertarOrdenadamente(20, *nodoRaiz);
    *nodoRaiz = insertarOrdenadamente(16, *nodoRaiz);
    *nodoRaiz = insertarOrdenadamente(18, *nodoRaiz);
    *nodoRaiz = insertarOrdenadamente(8, *nodoRaiz);
    *nodoRaiz = insertarOrdenadamente(14, *nodoRaiz);
}

int main(){
    NODO *nodoRaiz = NULL;
    intermediario(&nodoRaiz);
    /*
    nodoRaiz = insertarAlFinal(dato,nodoRaiz);
    nodoRaiz = insertarAlFinal(20,nodoRaiz);
    nodoRaiz = eliminaNodo(dato,nodoRaiz);
    */
}