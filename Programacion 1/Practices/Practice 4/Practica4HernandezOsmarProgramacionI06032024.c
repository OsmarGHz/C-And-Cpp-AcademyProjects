#include <stdio.h>
#include <string.h>
#define TOTALFUNCIONES 3 // Cuantas funciones habran?

/* Integrantes
Cortes Arenas Nadia 

Hernandez Romero Maite 

Hernandez Prado Osmar Javier

Lopez Momox Limhi Gerson
*/

struct Funcion {
	int horainicio;
	int minutosinicio;
	int horafinal;
	int minutosfinal;
	char nombrePelicula[30];
};

void ordenarFuncionesBurbuja(struct Funcion funciones[], int positions[]) {
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

void ordenarFuncionesSeleccion(struct Funcion funciones[], int positions[]){
	int i, j, temp, masChico;
	for (i = 0; i < TOTALFUNCIONES - 1; i++){
		masChico = i;
		for (j = i+1; j < TOTALFUNCIONES; j++){
			if (funciones[positions[masChico]].horainicio > funciones[positions[j]].horainicio || (funciones[positions[masChico]].horainicio == funciones[positions[j]].horainicio && funciones[positions[masChico]].minutosinicio > funciones[positions[j]].minutosinicio)){
				masChico = j;
			}
		}
		if (masChico != i){
			temp = positions[i];
			positions[i] = positions[masChico];
			positions[masChico] = temp;
		}
	}
}

void ordenarFuncionesInsercion(struct Funcion funciones[], int positions[]){
	int i, j, temp;
	for (i = 1; i < TOTALFUNCIONES; i++){
		temp = positions[i];
		for (j = i; j > 0 && (funciones[positions[j - 1]].horainicio > funciones[temp].horainicio || (funciones[positions[j - 1]].horainicio == funciones[temp].horainicio && funciones[positions[j - 1]].minutosinicio > funciones[temp].minutosinicio)); j--){
			positions[j] = positions[j - 1];
		}
		positions[j] = temp;
	}
}

void busquedaBinaria(struct Funcion funciones[], int positions[], int peticion){
	int infLim = 0, supLim = TOTALFUNCIONES-1, mid = (infLim + supLim)/2, encontrado = 0;
	while (!encontrado && supLim>=infLim){
		if (peticion == funciones[positions[mid]].horainicio){
			printf("Funcion %d - Pelicula: %s, Hora de Inicio: %02d:%02d, Hora de Fin: %02d:%02d\n",mid + 1, funciones[positions[mid]].nombrePelicula, funciones[positions[mid]].horainicio, funciones[positions[mid]].minutosinicio, funciones[positions[mid]].horafinal, funciones[positions[mid]].minutosfinal);
			encontrado++;
		}else if (peticion > funciones[positions[mid]].horainicio){
			infLim = mid+1;
		}else if (peticion < funciones[positions[mid]].horainicio){
			supLim = mid-1;
		}
		mid = (infLim + supLim)/2;
	}
	if (!encontrado) printf("\nNo se encontro el elemento");
}

void busquedaDeNombre(struct Funcion funciones[], int positions[], char peticionTexto[]){
	int i, contador=0;
	for (i = 0; i < TOTALFUNCIONES; i++){
		if (strstr(funciones[positions[i]].nombrePelicula, peticionTexto) != NULL){
			printf("Funcion %d - Pelicula: %s, Hora de Inicio: %02d:%02d, Hora de Fin: %02d:%02d\n",i + 1, funciones[positions[i]].nombrePelicula, funciones[positions[i]].horainicio, funciones[positions[i]].minutosinicio, funciones[positions[i]].horafinal, funciones[positions[i]].minutosfinal);
			contador++;
		}
	}
	if (contador==0){
		printf("\nLo sentimos. No se encontraron resultados");
	}
}

int main() {
	struct Funcion funciones[TOTALFUNCIONES];
	int k, posiciones[TOTALFUNCIONES], decision, peticion;
	char peticionTexto[30];
	
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
	
	printf("\nMenu: ");
	printf("\nElija alguna de las siguientes opciones de ordenamiento: ");
	printf("\n1. Ordenado Burbuja\n2. Ordenado por seleccion\n3. Ordenado por Insercion");
	do{	printf("\nIngrese la opcion deseada: ");
		scanf("%d", &decision);
		switch (decision){
			case 1:
				ordenarFuncionesBurbuja(funciones,posiciones);
				break;
			case 2:
				ordenarFuncionesSeleccion(funciones,posiciones);
				break;
			case 3:
				ordenarFuncionesInsercion(funciones,posiciones);
				break;
			default:
				printf("Opcion incorrecta");
				break;
		}
	} while (decision != 1 && decision != 2 && decision != 3);	
	
	printf("\n\n---Cartelera---\n");
	for (k = 0; k < TOTALFUNCIONES; k++) {
		printf("Funcion %d - Pelicula: %s, Hora de Inicio: %02d:%02d, Hora de Fin: %02d:%02d\n",k + 1, funciones[posiciones[k]].nombrePelicula, funciones[posiciones[k]].horainicio, funciones[posiciones[k]].minutosinicio, funciones[posiciones[k]].horafinal, funciones[posiciones[k]].minutosfinal);
	}

	do{ printf("\nDesea iniciar una busqueda? (1 = Si, de horario, 2 = Si, de Nombre, Cualquier otro numero = No)");
		scanf("%d", &decision);
		if (decision==1){
			printf("\nEn que hora esta buscando su pelicula? ");
			scanf("%d", &peticion);
			busquedaBinaria(funciones,posiciones,peticion);
		}else if (decision==2){
			printf("\nIngrese el nombre de la pelicula que busca: ");
			scanf("%s", &peticionTexto);
			busquedaDeNombre(funciones,posiciones,peticionTexto);
		}
		
	} while (decision == 1 || decision == 2);
	
	return 0;
}
