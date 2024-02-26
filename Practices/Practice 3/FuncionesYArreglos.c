#include <stdio.h>
#include <string.h>
#define TAMBUT 20

int main(){
    int inscritos[TAMBUT], butacas[TAMBUT];
    int realmenteInscritos,aTiempo,aTarde,i,j;
    short error=0,coincidencia=0;
    printf("Cuantos alumnos hay inscritos? ");
    scanf("%d",&realmenteInscritos);
    i=0;
    while (i<realmenteInscritos){
        printf("Ingrese la matricula del alumno %d (entre 1010 y 1200)", i+1);
        scanf("%d",&inscritos[i]);
        if (inscritos[i]<1010 || inscritos[i]>1200){
            printf("\n\t\t * Matricula incorrecta. Favor de ingresar otra.  *\n");
        }else{
            error=0;
            for (j = 0; j < i; j++){
                if (inscritos[j]==inscritos[i]){
                    printf("\n\t\t * Matricula repetida. Favor de ingresar otra.  *\n");
                    error++;
                }
            }
            if (error==0){
                i++;
            }
        }
    }
    printf("Cuantos alumnos llegaron a tiempo? ");
    scanf("%d",&aTiempo);
    i=0;
    while (i<aTiempo){
        printf("Ingrese la matricula del alumno %d (entre 1010 y 1200)", i+1);
        scanf("%d",&butacas[i]);
        if (inscritos[i]<1010 || inscritos[i]>1200){
            printf("\n\t\t * Matricula incorrecta. Favor de ingresar otra.  *\n");
        }else{
            coincidencia=0;
            for (j = 0; j < i; j++){
                if (inscritos[j]==inscritos[i]){
                    printf("\n\t\t * Matricula repetida. Favor de ingresar otra.  *\n");
                    error++;
                }
            }
            if (error==0){
                i++;
            }
        }
    }
}