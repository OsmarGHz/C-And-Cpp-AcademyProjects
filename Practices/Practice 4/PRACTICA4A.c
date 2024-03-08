#include <stdio.h>

#define TOTALFUNCIONES 3 // Cuantas funciones habra?

void Ordenamiento(int position[], int hora_inicio[], int min_inicio[], int hora_fin[], int min_fin[]) {
	int i, j, temp;
	for (i = 0; i < TOTALFUNCIONES - 1; i++) {
		for (j = 0; j < TOTALFUNCIONES - i - 1; j++) {
			if (hora_inicio[j] > hora_inicio[j + 1] || (hora_inicio[j] == hora_inicio[j + 1] && min_inicio[j] > min_inicio[j + 1])) {
				temp = position[j];
				position[j] = position[j+1];
				position[j+1] = temp;
				
				// Intercambio de horas de inicio
				temp = hora_inicio[j];
				hora_inicio[j] = hora_inicio[j + 1];
				hora_inicio[j + 1] = temp;
				
				// Intercambio de minutos de inicio
				temp = min_inicio[j];
				min_inicio[j] = min_inicio[j + 1];
				min_inicio[j + 1] = temp;
				
				// Intercambio de horas de fin
				temp = hora_fin[j];
				hora_fin[j] = hora_fin[j + 1];
				hora_fin[j + 1] = temp;
				
				// Intercambio de minutos de fin
				temp = min_fin[j];
				min_fin[j] = min_fin[j + 1];
				min_fin[j + 1] = temp;
			}
		}
	}
}

int main() {
	int k,m;
	int horainicio[TOTALFUNCIONES];
	int minutosinicio[TOTALFUNCIONES];
	int horafinal[TOTALFUNCIONES];
	int minutosfinal[TOTALFUNCIONES];
	char nombrePelicula[TOTALFUNCIONES][30];
	int posiciones[TOTALFUNCIONES];
	
	printf("\n\nPor favor llene los siguientes datos a continuacion \n\n");
	
	for (k = 0; k < TOTALFUNCIONES; k++) {
		printf("ADVERTENCIA: Introduce el nombre junto o con guion bajo\n");
		printf("Nombre de la pelicula %d:\n",k+1);
		scanf("%29s", nombrePelicula[k]);
		
		printf("\nEscriba la hora de inicio de la funcion %d: (en hora militar 00 - 23)\n", k + 1);
		scanf("%d", &horainicio[k]);
		while (horainicio[k] >= 24) {
			printf("\n\nFuera de las 24 horas\nIntente nuevamente\n");
			scanf("%d", &horainicio[k]);
		}
		
		printf("\nEscriba los minutos de inicio de la funcion %d (00 - 59):\n", k + 1);
		scanf("%d", &minutosinicio[k]);
		while (minutosinicio[k] >= 60) {
			printf("\nFuera de los 59 minutos\nIntente nuevamente\n");
			scanf("%d", &minutosinicio[k]);
		}
		
		printf("\nEscriba la hora de fin de la funcion %d: (en hora militar 00 - 23)\n", k + 1);
		scanf("%d", &horafinal[k]);
		while (horafinal[k] >= 24) {
			printf("\n\nFuera de las 24 horas\nIntente nuevamente\n");
			scanf("%d", &horafinal[k]);
		}
		
		printf("\nEscriba los minutos de fin de la funcion %d (00 - 59):\n", k + 1);
		scanf("%d", &minutosfinal[k]);
		while (minutosfinal[k] >= 60) {
			printf("\nFuera de los 59 minutos\nIntente nuevamente\n");
			scanf("%d", &minutosfinal[k]);
		}
		posiciones[k]=k;
	}
	
	// Ordenar los horarios de inicio y fin
	Ordenamiento(posiciones, horainicio, minutosinicio, horafinal, minutosfinal);
	
	// Imprimir los horarios
	printf("\n       - CARTELERA -        \n");
	printf("\nPelicula: %s\n", nombrePelicula[m]);
	for (m = 0; m < TOTALFUNCIONES; m++) {
		printf("\nHorario %d - %02d:%02d a %02d:%02d", m + 1, horainicio[m], minutosinicio[m], horafinal[m], minutosfinal[m]);
	}
	
	return 0;
}
