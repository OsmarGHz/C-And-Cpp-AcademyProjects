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
    printf("\nIngrese fecha (Formato dia mes anio, ejemplo: 14 12 2005). \nAnios desde 1960:\n");
    scanf("%hd %hd %hd", &(*fechaAProcesar).dia, &(*fechaAProcesar).mes, &(*fechaAProcesar).anio);

}

short comprobarAnioYBisiesto(Fecha *fechaAProcesar){
    short informe;
    if ( ((*fechaAProcesar).anio) < 1960 || ((*fechaAProcesar).anio) > 2024) ((*fechaAProcesar).anio) = 1960;
    
    if (((*fechaAProcesar).anio % 4 == 0))
    /*((*fechaAProcesar).anio) % 4 devuelve el residuo de la división del año por 4.  */
        informe = 1;// Es bisiesto
    else
        informe = 0; // No es bisiesto

    return informe;
}

short comprobarMesYDia(Fecha *fechaAProcesar, short bis){
    short informe = 0;

    // Si el mes resultante es mayor que 12
        if ((*fechaAProcesar).mes > 12 || (*fechaAProcesar).mes < 0) {
            (*fechaAProcesar).mes = 1;
        }
        
    
    switch ( (*fechaAProcesar).mes ){

        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (((*fechaAProcesar).dia) > 31 || ((*fechaAProcesar).dia) < 1){
                (*fechaAProcesar).dia = 1;
            }
            
            break;

        case 4: case 6: case 9: case 11:
            if (((*fechaAProcesar).dia) > 30 || ((*fechaAProcesar).dia) < 1){
                (*fechaAProcesar).dia = 1;
            }
            break;

        case 2:
            if (bis == 1){
                if (((*fechaAProcesar).dia) > 29 || ((*fechaAProcesar).dia) < 1){
                (*fechaAProcesar).dia = 1;
            }
            }
            else{
                if (((*fechaAProcesar).dia) > 28 || ((*fechaAProcesar).dia) < 1){
                (*fechaAProcesar).dia = 1;
            }
            }
            break;
        }

    return informe;
}

short comprobarFecha(Fecha *fechaAProcesar){
    short bisiesto,error;

    bisiesto=comprobarAnioYBisiesto(fechaAProcesar); // 1 = Bisiesto, 0 = NO bisiesto
    error=comprobarMesYDia(fechaAProcesar,bisiesto); // 1 = Errores, 0 = Todo Bien, -1 = Algo paso
    return error;
}

void imprimirFechaFormateada(Fecha *fechaAProcesar){
    char fechaFinal[50], temp[10];
    sprintf(temp, "%hd", (*fechaAProcesar).dia);
    strcpy(fechaFinal, temp);
    strcat(fechaFinal, " de ");
    switch ( (*fechaAProcesar).mes){
        case 1: strcat(fechaFinal, "Enero"); break;
        case 2: strcat(fechaFinal, "Febrero"); break;
        case 3: strcat(fechaFinal, "Marzo"); break;
        case 4: strcat(fechaFinal, "Abril"); break;
        case 5: strcat(fechaFinal, "Mayo"); break;
        case 6: strcat(fechaFinal, "Junio"); break;
        case 7: strcat(fechaFinal, "Julio"); break;
        case 8: strcat(fechaFinal, "Agosto"); break;
        case 9: strcat(fechaFinal, "Septiembre"); break;
        case 10: strcat(fechaFinal, "Octubre"); break;
        case 11: strcat(fechaFinal, "Noviembre"); break;
        case 12: strcat(fechaFinal, "Diciembre"); break;
        default: break;
    }
    strcat(fechaFinal, " de ");
    sprintf(temp, "%hd", (*fechaAProcesar).anio);
    strcat(fechaFinal, temp);
    printf("%s\n", fechaFinal);
}


int main(){
    Fecha unica;
    short errores=0;

    lecturaFecha(&unica);
    errores=comprobarFecha(&unica);
    if (errores == 0) {
        imprimirFechaFormateada(&unica);
    } else {
        printf("Error en la fecha ingresada.\n");
    }
   
    
    return 0;
}
