#include <stdio.h>
#include <string.h>

/* Integrantes
Cortes Arenas Nadia 

Hernandez Romero Maite 

Hernandez Prado Osmar Javier

Lopez Momox Limhi Gerson
*/

typedef struct{
    short dia, mes, anio;
}Fecha;

void lecturaFecha(Fecha *fechaAProcesar){
    printf("Ingrese fecha (Formato dia mes anio, ejemplo: 14 12 2005). Anios desde 1960: ");
    scanf("%hd %hd %hd", &(*fechaAProcesar).dia, &(*fechaAProcesar).mes, &(*fechaAProcesar).anio);
}

short comprobarAnioYBisiesto(Fecha *fechaAProcesar){
    short informe;
    if ( ((*fechaAProcesar).anio) < 1960 || ((*fechaAProcesar).anio) > 2024) informe = -1;
    else{
        switch ( ((*fechaAProcesar).anio) % 4 ){ //Aqui checamos si es bisiesto
            case 0: informe = 1;
                break;
            default: informe = 0;
                break;
        }
    }
    return informe;
}

short comprobarMesYDia(Fecha *fechaAProcesar, short bis){
    short informe;
    switch ( (*fechaAProcesar).mes ){

        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if ( ((*fechaAProcesar).dia) < 1 || ((*fechaAProcesar).dia) > 31 ) informe = 1;
            else informe = 0;
            break;

        case 4: case 6: case 9: case 11:
            if ( ((*fechaAProcesar).dia) < 1 || ((*fechaAProcesar).dia) > 30 ) informe = 1;
            else informe = 0;
            break;

        case 2:
            switch (bis){
                case 1:
                    if ( ((*fechaAProcesar).dia) < 1 || ((*fechaAProcesar).dia) > 29 ) informe = 1;
                    else informe = 0;
                    break;
                case 0:
                    if ( ((*fechaAProcesar).dia) < 1 || ((*fechaAProcesar).dia) > 28 ) informe = 1;
                    else informe = 0;
                    break;
                default: informe = -1;
                    break;
            }
            break;

        default: informe = 1;
            break;
    }
    return informe;
}

short comprobarFecha(Fecha *fechaAProcesar){
    short bisiesto,error;

    bisiesto=comprobarAnioYBisiesto(fechaAProcesar); // 1 = Bisiesto, 0 = NO bisiesto, -1 = error de anio
    if (bisiesto==-1) error = 1;
    else error=comprobarMesYDia(fechaAProcesar,bisiesto); // 1 = Errores, 0 = Todo Bien, -1 = Algo paso
    return error;
}

void imprimirFechaFormateada(Fecha *fechaAProcesar){
    printf("\n%hd de ", (*fechaAProcesar).dia);
    switch ( (*fechaAProcesar).mes){
        case 1: printf("Enero"); break;
        case 2: printf("Febrero"); break;
        case 3: printf("Marzo"); break;
        case 4: printf("Abril"); break;
        case 5: printf("Mayo"); break;
        case 6: printf("Junio"); break;
        case 7: printf("Julio"); break;
        case 8: printf("Agosto"); break;
        case 9: printf("Septiembre"); break;
        case 10: printf("Octubre"); break;
        case 11: printf("Noviembre"); break;
        case 12: printf("Diciembre"); break;
        default: break;
    }
    printf(" de %hd\n", (*fechaAProcesar).anio);
}

void imprimirFechaGenerica(){
    printf("\n1 de Enero de 1960\n");
}

int main(){
    Fecha unica;
    short errores=0;

    lecturaFecha(&unica);
    errores=comprobarFecha(&unica);
    if (errores==0) imprimirFechaFormateada(&unica);
    else imprimirFechaGenerica();
    
    return 0;
}
