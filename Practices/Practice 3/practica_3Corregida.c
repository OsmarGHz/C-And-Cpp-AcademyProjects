#include <stdio.h>
#define Cupo 20
/* Integrantes
Cortes Arenas Nadia 

Hernandez Romero Maite 

Hernandez Prado Osmar Javier

Lopez Momox Limhi Gerson
*/
void Funcion_impresion(int arrayinscritos[],int paselista[], int inscritos, int aTemprana, int aTarde, int noFueron){
    int i;
	printf("__________Reporte___________\n");
    printf("\nAlumnos Inscritos: %d", inscritos);
    printf("\nAlumnos que llegaron a tiempo: \n");
	printf("No. Butaca\tNo. Lista\tMatricula\n");
	for (i=0; i<aTemprana; i++){
		int n=paselista[i];
		printf("    %d    \t\t%d\t\t%d\n",(i+1), (paselista[i]),arrayinscritos[n-1]);
	}
    printf("\nAlumnos que llegaron tarde: \n");
	printf("No. Butaca\tNo. Lista\tMatricula\n");
	for (; i<(aTemprana+aTarde); i++){
		int n=paselista[i];
		printf("    %d    \t\t%d\t\t%d\n",(i+1), (paselista[i]),arrayinscritos[n-1]);
	}
    printf("\nAlumnos que no llegaron: \n");
	printf("No. Lista\tMatricula\n");
	for (; i<inscritos; i++){
		int n=paselista[i];
		printf("    %d\t\t%d\n", (paselista[i]),arrayinscritos[n-1]);
	}
}

void funcionvalidacion(int paselista[], int i, int inscritos){
	int s,nolista, cont=0;
	do {
		printf("Indique el numero de lista del alumno (del 1 al %d)\n", inscritos);
		scanf("%d",&nolista);
		while (nolista<=0 || nolista>inscritos){  //nolista se maneja de 1 a no.inscritos por eso debe ser menor igual para validar
			printf("Error, el numero de lista esta fuera del rango\n");
			scanf("%d",&nolista);
		}
		cont=0;
		for (s=0;s<inscritos; s++){ 
			if (paselista[s]==nolista){
				cont++;
				if (cont==1){
					printf("Error, ya existe ese numero de lista en paselista indice: %d\n ",paselista[s]); 
					s--;
				}
			    break;
			}
		}
	}while (cont!=0);
	paselista[i]=nolista;
	
}	
	
void funcion_principal(int paselista[Cupo], int arrayinscritos[]) {
		int n,asistenciaTemprana=0;
		int asistenciaTarde=0, c;
		int NoFueron=0, d;
		int p;
		//
		int inscritos=0;
		printf("Ingrese el numero de alumnos a inscribir\n");
		scanf("%d",&inscritos);
		while (inscritos<1 || inscritos>20){
			printf("Error, cupo maximo o cupo invalido: %d\nIngrese nuevamente a continuacion",Cupo);
			scanf("%d",&inscritos);
		}
		for (int i=0; i<inscritos; i++){
			int t;
			printf("Escriba la matricula %d a continuacion (desde 1010 a 1200)\n", i+1);
			scanf("%d",&t);
			while (t<1010 || t>1200){
				printf("Error, rebaso el rango permitido (matriculas validas desde 1010 a 1200)\nIngrese de nuevo a continuacion\n");
				scanf("%d",&t);
				printf("Guardado correctamente\n");
			}
			for (int k=0;k<inscritos;k++){
				if (t==arrayinscritos[k]){
					i--;
					printf("Error, la matricula ya habia sido ingresada\n");
				}
				break;
			}
			arrayinscritos[i]=t;
		}
		///////
		
		printf("\nIndique el numero de alumnos que asistieron a tiempo\n");
		scanf("%d",&n);
		asistenciaTemprana=n;
		p=asistenciaTemprana + asistenciaTarde + NoFueron;
		while (p>0 && p>inscritos){  //checa que los ninos metidos en el programa no sean mayor a 10 en total
			printf("Error, el numero de ninos por cada seccion rebasa el numero de ninos totales inscritos\n");
			scanf("%d",&n);
			asistenciaTemprana=n;
			p=asistenciaTemprana + asistenciaTarde + NoFueron;
		}
		
		for (int i=0; i<n; i++){ //validar el numero de lista y colocarlo en la matriz 
			funcionvalidacion(paselista, i,inscritos); 
	    }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		printf("Ahora escribe el numero de alumnos que asistieron tarde \n");
		scanf("%d",&n);
		asistenciaTarde=n;
		p=asistenciaTemprana + asistenciaTarde + NoFueron;
		while (p>0 && p>inscritos){  //checa que los ninos metidos en el programa no sean mayor en total
			printf("Error, el numero de ninos por cada seccion rebasa el numero de ninos totales inscritos\n");
			scanf("%d",&n);
			asistenciaTarde=n;
			p=asistenciaTemprana + asistenciaTarde + NoFueron;
		}
		c=asistenciaTemprana;//para que la matriz no inicie desde 0, sino desde el valor de la seccion anterior
		
		
		for (int s=0; s<=n-1; s++){
			funcionvalidacion(paselista, c,inscritos);
			c++;
		}
		
		d=c;
		NoFueron = inscritos - asistenciaTemprana - asistenciaTarde;
		printf("\n\t\tPasando a leer los que no llegaron: \n\n");
		n=NoFueron;
		/*
		printf("Ahora escribe el numero de alumnos que no aistieron \n");
		scanf("%d",&n);
		NoFueron=n;
		p=asistenciaTemprana + asistenciaTarde + NoFueron;
		while (p>0 && p>inscritos){  //checa que los ninos metidos en el programa no sean mayor a 10 en total
			printf("Error, el numero de ninos por cada seccion rebasa el numero de ninos totales inscritos\n");
			scanf("%d",&n);
			NoFueron=n;
			p=asistenciaTemprana + asistenciaTarde + NoFueron;
		}
		*/
		for (int s=0; s<=n-1; s++){
			funcionvalidacion(paselista, d, inscritos);
			d++;
			//printf("d es igual a : %d\n",d);
		}
		Funcion_impresion(arrayinscritos, paselista, inscritos, asistenciaTemprana, asistenciaTarde, NoFueron);
}
	
	void funcion_inicializar(int paselista[]){
		for (int i=0; i<Cupo; i++){
			paselista[i]= -1;
		}
	}

int main(int argc, char *argv[]) {
	int arrayinscritos[Cupo];
	int paselista[Cupo];
	funcion_inicializar(paselista);
	funcion_principal(paselista, arrayinscritos);
	
	return 0;
}

