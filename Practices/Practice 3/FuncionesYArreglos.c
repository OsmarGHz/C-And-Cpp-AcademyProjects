#include <stdio.h>
#include <string.h>
#define TAMAL 20

short numeroInscripciones(){
    short temp;
    printf("Cuantos alumnos hay inscritos? ");
    scanf("%hd",&temp);
    return temp;
}

void inscribirAlumnos(int insc[]){
    short realmenteInscritos,i,j,temp,error;
    realmenteInscritos=numeroInscripciones();
    i=0;
    while (i<realmenteInscritos){
        printf("Ingrese la matricula del alumno %d (entre 1010 y 1200)", i+1);
        scanf("%hd",&temp);
        if (temp<1010 || temp>1200){
            printf("\n\t\t * Matricula incorrecta. Favor de ingresar otra.  *\n");
        }else{
            error=0;
            for (j = 0; j < i; j++){
                if (insc[j]==temp){
                    printf("\n\t\t * Matricula repetida. Favor de ingresar otra.  *\n");
                    error++;
                }
            }
            if (error==0){
                insc[i]=temp;
                i++;
            }
        }
    }
}

short calculoAlumnosTiempo(){
    short temp;
    do{
        printf("Cuantos alumnos llegaron a tiempo? ");
        scanf("%d",&temp);
        if (temp<0 || temp>realmenteInscritos){
            printf("Numero de alumnos incorrecto. Ingrese otra cantidad.");
        }else{
            return temp;
        }
    } while (temp<0 || temp>realmenteInscritos);
}

void alumnosTiempo(){
    short aTiempo;
    aTiempo=calculoAlumnosTiempo();
    i=0;
    while (i<aTiempo){
        printf("Ingrese la matricula del alumno %d (entre 1010 y 1200)", i+1);
        scanf("%d",&temp);
        if (temp<1010 || temp>1200){
            printf("\n\t\t * Matricula incorrecta. Favor de ingresar otra.  *\n");
        }else{
            coincidencia=0;
            for (j = 0; j < realmenteInscritos; j++){
                if (temp==inscritos[j]){
                    printf("\n\t\t * Alumno encontrado... *\n");
                    for (k = 0; k < i; k++){
                        if (butacas[k]==j){
                            coincidencia++;
                        }
                    }
                    tempIt=j;
                    coincidencia++;
                }
            }
            if (coincidencia==1){
                printf("Registrado\n");
                butacas[i]=tempIt;
                i++;
            }else if(coincidencia>1){
                printf("\n\t\t * Esta matricula ya tiene lugar. Favor de ingresar otra.  *\n");
            }else{
                printf("\n\t\t * No se encontro el alumno. *\n");
            }
        }
    }
}

int main(){
    int inscritos[TAMAL], butacas[TAMAL];
    short rInscritos;
    //int realmenteInscritos,aTiempo,tarde,i,j,k,temp,tempIt;
    //short error=0,coincidencia=0;
    inscribirAlumnos(inscritos);
    alumnosTiempo();

    do{
        printf("Cuantos alumnos llegaron TARDE? ");
        scanf("%d",&tarde);
        if (tarde<0 || tarde>(realmenteInscritos-aTiempo)){
            printf("Numero de alumnos incorrecto. Ingrese otra cantidad.");
        }
    } while (tarde<0 || tarde>(realmenteInscritos-aTiempo));
    
    printf("Cuantos alumnos llegaron TARDE? ");
    scanf("%d",&tarde);
    while (i<(aTiempo+tarde)){
        printf("Ingrese la matricula del alumno %d (entre 1010 y 1200)", i+1);
        scanf("%d",&temp);
        if (temp<1010 || temp>1200){
            printf("\n\t\t * Matricula incorrecta. Favor de ingresar otra.  *\n");
        }else{
            coincidencia=0;
            for (j = 0; j < realmenteInscritos; j++){
                if (temp==inscritos[j]){
                    printf("\n\t\t * Alumno encontrado... *\n");
                    for (k = 0; k < i; k++){
                        if (butacas[k]==j){
                            coincidencia++;
                        }
                    }
                    tempIt=j;
                    coincidencia++;
                }
            }
            if (coincidencia==1){
                printf("Registrado\n");
                butacas[i]=tempIt;
                i++;
            }else if(coincidencia>1){
                printf("\n\t\t * Esta matricula ya tiene lugar. Favor de ingresar otra.  *\n");
            }else{
                printf("\n\t\t * No se encontro el alumno. *\n");
            }
        }
    }

    printf("\n********************* REPORTE DE ASISTENCIA *************************\n");
    printf("\nAlumnos inscritos: %d", realmenteInscritos);
    printf("\nAlumnos que llegaron a tiempo\n");
    printf("\nNo. de butaca\tNo. de lista\tMatricula");
    for (i = 0; i < aTiempo; i++){
        printf("\n\t%d\t %d\t %d",i,butacas[i],inscritos[butacas[i]]);
    }
    printf("\nAlumnos que llegaron tarde\n");
    printf("\nNo. de butaca\tNo. de lista\tMatricula");
    for (; i < (aTiempo+tarde); i++){
        printf("\n\t%d\t %d\t %d",i,butacas[i],inscritos[butacas[i]]);
    }

    printf("\nAlumnos que llegaron tarde\n");
    printf("\nNo. de lista\tMatricula");
    for (i = 0; i < realmenteInscritos; i++){
        coincidencia=0;
        for (j = 0; j < (aTiempo+tarde); j++){
            if (i==butacas[j]){
                coincidencia++;
            }
        }
        if (coincidencia==0){
            printf("\n\t%d\t %d",i,inscritos[i]);
        }
        
    }
}