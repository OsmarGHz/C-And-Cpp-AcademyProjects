#include <stdio.h>
#define TotalFunciones 3 // Cuantas funciones habran?
#define filas 13
#define columnas 2
#define butacas_por_fila 8


void ordenarFunciones(int horainicio[], int minutosinicio[], int horafinal[], int minutosfinal[]) {
	int x, y, temp;
	for (x = 1; x <= TotalFunciones; x++) {
		for (y = 1; y <= TotalFunciones - x; y++) {
			if  (horainicio[y] > horainicio[y + 1] || (horainicio[y] == horainicio[y + 1] && minutosinicio[y] > minutosinicio[y + 1]) ||
				(horainicio[y] == horainicio[y + 1] && minutosinicio[y] == minutosinicio[y + 1] && horafinal[y] > horafinal[y + 1]) ||
				(horainicio[y] == horainicio[y + 1] && minutosinicio[y] == minutosinicio[y + 1] && horafinal[y] == horafinal[y + 1] && minutosfinal[y] > minutosfinal[y + 1])) {
				// Intercambiar horas iniciales
				temp = horainicio[y];
				horainicio[y] = horainicio[y + 1];
				horainicio[y + 1] = temp;
				// Intercambiar minutos iniciales
				temp = minutosinicio[y];
				minutosinicio[y] = minutosinicio[y + 1];
				minutosinicio[y + 1] = temp;
				// Intercambiar horas finales
				temp = horafinal[y];
				horafinal[y] = horafinal[y + 1];
				horafinal[y + 1] = temp;
				// Intercambiar minutos finales
				temp = minutosfinal[y];
				minutosfinal[y] = minutosfinal[y + 1];
				minutosfinal[y + 1] = temp;
			}
		}
	}
}

int main() {
	
	int inicio, bienvenida, editar;
	int k, HorarioSeleccionado;
	int seccion, butaca, asientos_fil, eleccionAsiento;
	int horainicio[TotalFunciones];
	int minutosinicio[TotalFunciones];
	int horafinal[TotalFunciones];
	int minutosfinal[TotalFunciones];
	char NombrePelicula[30];
	unsigned char mtz[TotalFunciones][filas][columnas] = {0}; // Matriz para cada sala
	
	do {
		printf("\nComo desea entrar: \n 1. Vendedor \n 2. Comprador \n 0. Salir \n");
		scanf("%d", &inicio);
		
		switch (inicio) {
		case 1: {
			do {
				printf("\n\nQue desea hacer? \n 1. Editar la cartelera \n 2. Pre-Visualizar la cartelera \n 0. Volver al menu \n");
				scanf("%d", &editar);
				switch (editar) {
				case 1: {
					printf("\n\nPor favor llene los siguientes datos a continuacion \n\n");
					
					printf("ADVERTENCIA: Introduce el nombre junto o con guion bajo");
					printf("\nNombre de la pelicula\n");
					scanf("%s", NombrePelicula);
					
					for (k = 1; k <= TotalFunciones; k++) {
						
						printf("\nEscriba la hora de inicio de la funcion %d: (en hora militar 00 - 23)\n", k);
						scanf("%d", &horainicio[k]);
						while (horainicio[k] >= 24) {
							printf("\n\nFuera de las 24 horas\nIntente nuevamente\n");
							scanf("%d", &horainicio[k]);
						}
						
						
						printf("\nEscriba los minutos de inicio de la funcion %d (00 - 59):\n", k);
						scanf("%d", &minutosinicio[k]);
						while (minutosinicio[k] >= 60) {
							printf("\nFuera de los 59 minutos\nIntente nuevamente\n");
							scanf("%d", &minutosinicio[k]);
						}
						
						printf("\nEscriba la hora de fin de la funcion %d: (en hora militar 00 - 23)\n", k);
						scanf("%d", &horafinal[k]);
						while (horafinal[k] >= 24) {
							printf("\n\nFuera de las 24 horas\nIntente nuevamente\n");
							scanf("%d", &horafinal[k]);
						}
						
						printf("\nEscriba los minutos de fin de la funcion %d (00 - 59):\n", k);
						scanf("%d", &minutosfinal[k]);
						while (minutosfinal[k] >= 60) {
							printf("\nFuera de los 59 minutos\nIntente nuevamente\n");
							scanf("%d", &minutosfinal[k]);
						}
						
						for (int i = 1; i < k; i++) {
							if ((horainicio[k] < horafinal[i] || (horainicio[k] == horafinal[i] && minutosinicio[k] < minutosfinal[i])) &&
								(horafinal[k] > horainicio[i] || (horafinal[k] == horainicio[i] && minutosfinal[k] > minutosinicio[i]))) {
								printf("\nError: El horario de la funcion %d se superpone con el horario de la funcion %d.\n", k, i);
								printf("Intente nuevamente.\n");
								k--; 
								break;
							}
						}
						
					}
					
				}
				break;
				
				case 2: {
					
					ordenarFunciones(horainicio, minutosinicio, horafinal, minutosfinal);
					
					// Imprimir los horarios ordenados
					printf("\n       - CARTELERA -        \n");
					printf("\nPelicula: %s\n", NombrePelicula);
					for (int m = 1; m <=TotalFunciones; m++) {
						printf("\nHorario %d - %02d:%02d a %02d:%02d", m , horainicio[m], minutosinicio[m], horafinal[m], minutosfinal[m]);
					}
					printf("\n");
					
				}
				break;
				
				case 0: {
					break;
				}
				default: {
					printf("Opcion invalida. Intente nuevamente.\n");
				}
				}
			} while (editar != 0);
			break;
		}
		case 2: {
			do {
				printf("\n Bienvenido a nuestro cine - CINE and POLIS, En que podemos ayudarlo?");
				printf("\n\n 1. Comprar boletos\n 2. Pre-Visualizar nuestra cartelera \n 0. Volver al menu \n");
				scanf("%d", &bienvenida);
				switch (bienvenida) {
				case 1: {
					
					ordenarFunciones(horainicio, minutosinicio, horafinal, minutosfinal);
					// Imprimir los horarios ordenados
					printf("\n       - CARTELERA -        \n");
					printf("\nPelicula: %s\n", NombrePelicula);
					for (int m = 1; m <=TotalFunciones; m++) {
						printf("\nHorario %d - %02d:%02d a %02d:%02d", m , horainicio[m], minutosinicio[m], horafinal[m], minutosfinal[m]);
					}
					printf("\n");
					
					
					printf("\n\nEn que horario le gustaria entrar?\n");
					scanf("%d", &HorarioSeleccionado);
					while (HorarioSeleccionado>TotalFunciones ) {
						printf("\n\nFuncion invalida, introduzca una funcion que se le muestra en pantalla\n");
						scanf("%d", &HorarioSeleccionado);
					}
					
					
					printf("Los asientos ocupados estan marcados con 'X', los asientos libres estan marcados por 'O'.\n");
					printf("\n\t\t\t\tPANTALLA \n\n\n");
					for (int i = 0; i < filas; i++) {
						printf("(Fila: %d) \t", i);
						for (int j = 0; j < columnas; j++) {
							for (int bit = 0; bit < butacas_por_fila; bit++) {
								printf("%c ", ((mtz[HorarioSeleccionado - 1][i][j] & (1 << bit)) != 0) ? 'X' : 'O');
							}
							printf("\t "); // Separacion entre columnas
						}
						printf("\n"); // Nueva linea para cada fila
					}
					
					//DESDE AQUI EMPIEZA BUTACAS
					
					do {
						printf("\nColoca el numero de la fila en que se encuentra el asiento: ");
						scanf("%d", &asientos_fil);
						while (asientos_fil < 0 || asientos_fil >= filas) {
							printf("Numero de fila fuera del rango permitido.\nIngrese de nuevo: ");
							scanf("%d", &asientos_fil);
						}
						
						printf("Ingresa el numero de seccion (1 para la izquierda, 2 para la derecha): ");
						scanf("%d", &seccion);
						while (seccion != 1 && seccion != 2) {
							printf("La seccion esta fuera del rango permitido.\nIngrese de nuevo: ");
							scanf("%d", &seccion);
						}
						
						printf("Ingresa el numero de butaca: ");
						scanf("%d", &butaca);
						while (butaca <= 0 || butaca > butacas_por_fila) {
							printf("El numero de butaca esta fuera del rango permitido.\nIngrese de nuevo: ");
							scanf("%d", &butaca);
						}
						
						
						unsigned char temporal = 1 << (butaca - 1);
						
						if ((mtz[HorarioSeleccionado - 1][asientos_fil][seccion - 1] & temporal) == 0) {
							mtz[HorarioSeleccionado - 1][asientos_fil][seccion - 1] |= temporal; 
							printf("Asiento marcado correctamente.\n");
							
							if (butaca > 1) {
								unsigned char asientoIzquierdo = 1 << (butaca - 2); // izquierda
								mtz[HorarioSeleccionado - 1][asientos_fil][seccion - 1] |= asientoIzquierdo;
							}
							if (butaca < butacas_por_fila) { 
								unsigned char asientoDerecho = 1 << butaca; // derecha
								mtz[HorarioSeleccionado - 1][asientos_fil][seccion - 1] |= asientoDerecho;
							}
						} else {
							printf("El asiento ya esta ocupado. Por favor, elige otro.\n");
						}
						
						printf("Los asientos ocupados estan marcados con 'X', los asientos libres estan marcados por 'O'.\n");
						printf("\n\t\t\t\tPANTALLA \n\n\n");
						for (int i = 0; i < filas; i++) {
							printf("(Fila: %d) \t", i);
							for (int j = 0; j < columnas; j++) {
								for (int bit = 0; bit < butacas_por_fila; bit++) {
									printf("%c ", ((mtz[HorarioSeleccionado - 1][i][j] & (1 << bit)) != 0) ? 'X' : 'O');
								}
								printf("\t "); // Separacion entre columnas
							}
							printf("\n"); // Nueva linea para cada fila
						}
						
						printf("Estas seguro de tu eleccion? (1: Si, 2: No): ");
						scanf(" %d", &eleccionAsiento);
						
						if (eleccionAsiento != 1) {
							
							printf("Desea liberarlo? (1: Si, 2: No): ");
							char liberar;
							scanf(" %c", &liberar);
							if (liberar == '1') {
								mtz[HorarioSeleccionado - 1][asientos_fil][seccion - 1] &= ~temporal; // Liberar el asiento
								printf("Asiento liberado correctamente.\n");
							}
						}
					} while (eleccionAsiento != 1);
					
					
					//AQUI ACABA
					
					//BOLETO
					printf("\n\nImprimiendo su boleto\n\n");
					printf("\n----------------------");
					printf("\n|                    |");
					printf("\n|    CINE and POLI   |");
					printf("\n|                    |");
					printf("\n| - - -- - - - - - - |");
					printf("\n| Pelicula: %s |", NombrePelicula);
					printf("\n| Horario: %02d:%02d - %02d:%02d |", horainicio[HorarioSeleccionado], minutosinicio[HorarioSeleccionado], horafinal[HorarioSeleccionado], minutosfinal[HorarioSeleccionado]);
					printf("\n|                    |");
					printf("\n| Fila: %d            |", asientos_fil);
					printf("\n| Seccion: %d         |", seccion);
					printf("\n| Butaca: %d          |", butaca);
					printf("\n|                    |");
					printf("\n| - - -- - - - - - - |");
					printf("\n| GRACIAS POR VENIR  |");
					printf("\n|                    |");
					printf("\n----------------------");
					//acaba boleto
					
					break;
				};
				case 2: {
					
					ordenarFunciones(horainicio, minutosinicio, horafinal, minutosfinal);
					
					// Imprimir los horarios ordenados
					printf("\n       - CARTELERA -        \n");
					printf("\nPelicula: %s\n", NombrePelicula);
					for (int m = 1; m <=TotalFunciones; m++) {
						printf("\nHorario %d - %02d:%02d a %02d:%02d", m , horainicio[m], minutosinicio[m], horafinal[m], minutosfinal[m]);
					}
					printf("\n");
				}
				case 0: {
					break;
				}
				default: {
					printf("Opcion invalida. Intente nuevamente.\n");
				}
				}
			} while (bienvenida != 0);
		}
		
		}
	} while (inicio != 0);
	return 0;
}
