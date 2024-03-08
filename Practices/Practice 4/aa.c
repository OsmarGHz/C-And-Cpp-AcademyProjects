#include <stdio.h>
#define TOTALFUNCIONES 3 // Cuantas funciones habran?

struct Funcion {
	int horainicio;
	int minutosinicio;
	int horafinal;
	int minutosfinal;
	char nombrePelicula[30];
};

void ordenarFunciones(struct Funcion funciones[], int positions[]) {
	int i, j, temp;
	for (i = 0; i < TOTALFUNCIONES - 1; i++) {
		for (j = 0; j < TOTALFUNCIONES - i - 1; j++) {
			if (funciones[positions[j]].horainicio > funciones[positions[j + 1]].horainicio || (funciones[positions[j]].horainicio == funciones[positions[j + 1]].horainicio && funciones[positions[j]].minutosinicio > funciones[positions[j + 1]].minutosinicio)) {
				temp = positions[j];
				positions[j] = positions[j + 1];
				positions[j + 1] = temp;
			}
		}
	}
}

void buscarBinariadamente(struct Funcion funciones[], int positions[]){
	char decision;
	short izq, der, mit, target;
	do{
		printf("Desea buscar una hora en especifico? ");
		scanf("%c",&decision);
		if (decision=="s"||decision=="S"){
			printf("Ingrese SOLO la hora en la que quiere ver una peli (ejemplo: 15): ");
			scanf("%hd",&target);
			while (target < 0 || target >= 24) { 
				printf("\nFuera de las 24 horas\nIntente nuevamente\n");
				scanf("%hd", &target);
			}
			izq=0;
			der=TOTALFUNCIONES;
			
		}
	} while (decision=="s" || decision=="S");
	
}

int main() {
	struct Funcion funciones[TOTALFUNCIONES];
	int k, posiciones[TOTALFUNCIONES];
	
	printf("\n\nPor favor llene los siguientes datos a continuacion \n\n");
	
	for (k = 0; k < TOTALFUNCIONES; k++) {
		printf("\nNombre de la pelicula para la funcion %d:\n", k + 1);
		scanf("%29s", funciones[k].nombrePelicula); 
		
		printf("\nEscriba la hora de inicio de la funcion %d (en hora militar 00 - 23):\n", k + 1);
		scanf("%d", &funciones[k].horainicio);
		while (funciones[k].horainicio < 0 || funciones[k].horainicio >= 24) { 
			printf("\nFuera de las 24 horas\nIntente nuevamente\n");
			scanf("%d", &funciones[k].horainicio);
		}
		
		printf("\nEscriba los minutos de inicio de la funcion %d (00 - 59):\n", k + 1);
		scanf("%d", &funciones[k].minutosinicio);
		while (funciones[k].minutosinicio < 0 || funciones[k].minutosinicio >= 60) { 
			printf("\nFuera de los 59 minutos\nIntente nuevamente\n");
			scanf("%d", &funciones[k].minutosinicio);
		}
		
		printf("\nEscriba la hora de fin de la funcion %d: (en hora militar 00 - 23)\n", k + 1);
		scanf("%d", &funciones[k].horafinal);
		while (funciones[k].horafinal < 0 || funciones[k].horafinal >= 24) {
			printf("\nFuera de las 24 horas\nIntente nuevamente\n");
			scanf("%d", &funciones[k].horafinal);
		}
		
		printf("\nEscriba los minutos de fin de la funcion %d (00 - 59):\n", k + 1);
		scanf("%d", &funciones[k].minutosfinal);
		while (funciones[k].minutosfinal < 0 || funciones[k].minutosfinal >= 60) { 
			printf("\nFuera de los 59 minutos\nIntente nuevamente\n");
			scanf("%d", &funciones[k].minutosfinal);
		}
		posiciones[k] = k;
	}
	
	ordenarFunciones(funciones,posiciones);
	
	printf("\n\n---Cartelera---\n");
	for (k = 0; k < TOTALFUNCIONES; k++) {
		printf("Funcion %d - Pelicula: %s, Hora de Inicio: %02d:%02d, Hora de Fin: %02d:%02d\n",k + 1, funciones[posiciones[k]].nombrePelicula, funciones[posiciones[k]].horainicio, funciones[posiciones[k]].minutosinicio, funciones[posiciones[k]].horafinal, funciones[posiciones[k]].minutosfinal);
	}
	
	buscarBinariadamente(funciones,posiciones);
	
	return 0;
}
