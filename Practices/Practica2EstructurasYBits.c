#include <stdio.h>
#include <string.h>
#define TAMDIR 1

/* Integrantes
Cortes Arenas Nadia 

Hernandez Romero Maite 

Hernandez Prado Osmar Javier

Lopez Momox Limhi Gerson
*/

typedef struct{
    short mes,dia,hora,minuto;
}TimeDate;

typedef struct{
    char nombre[35],user[35];
    long long int tamano;
    short int perm;
    char tipo;
    TimeDate momento;
}File;

int main(){
    char decision,temporal[100]={0};
    short int temp,mascara,i,j,k,l,error,longMinima,igualdad;
    File files[TAMDIR]={0};

    printf("\n Cual es su nombre de Usuario? (Se tomaran los 1ros 35 caracteres): ");
    scanf(" %s",files[0].user);
    if (TAMDIR >= 2) { for (i = 1; i < TAMDIR; i++) strcpy(files[i].user,files[0].user); }
    
    for (i = 0; i < TAMDIR; i++){
		fflush(stdin);
		printf("\n Ingrese: ");

        do{ error=0;
            printf("\n Nombre del archivo %d (Se tomaran los 1ros 35 caracteres): ",i+1);
            scanf(" %s",files[i].nombre);
            for (j = 0; j < i; j++){
                if (strlen(files[i].nombre)>=strlen(files[j].nombre)) longMinima=strlen(files[i].nombre);
                else longMinima=strlen(files[j].nombre);
                igualdad=1;
                for (k = 0; k < longMinima; k++){
                    if (files[i].nombre[k]==files[j].nombre[k]){
                        continue;
                    }else{
                        igualdad=0;
                        break;
                    }
                }
                if (igualdad==1){
                    printf("\n\t\t * Error. Nombre repetido, favor de ingresar otro *\n");
                    error++;
                    break;
                }
            }
        } while (error>0 || igualdad>0);

        do{ fflush(stdin);
            printf(" Tipo del archivo %d ( ingrese una sola letra, ejemplo, c ): ",i+1);
            scanf("%s",&temporal);
            if (strlen(temporal)==1) files[i].tipo=temporal[0];
            else printf("\n\t\t * Error. La longitud debe de ser de Solo 1 letra. *\n\n");
        } while (strlen(temporal)!=1);
        
        
        

        do{ fflush(stdin);
            printf(" Tamano del archivo %d (en bytes, solo puede ser numerico): ",i+1);
            scanf(" %lld",&files[i].tamano);
            if (files[i].tamano==0) printf("\n\t\t * Error. El tamano del archivo debe de ser mayor a cero *\n\n");
        } while (files[i].tamano==0);

        do{ fflush(stdin);
            printf(" Siendo:");
            printf("\n\t 1=Enero\t 2=Febrero\t 3=Marzo\t 4=Abril \n\t 5=Mayo \t 6=Junio\t 7=Julio\t 8=Agosto \n\t 9=Septiembre\t 10=Octubre\t 11=Noviembre\t 12=Diciembre\n");
            printf(" Numero del mes de creacion del archivo %d ( ejemplo, 12 ): ",i+1);
            scanf(" %hd",&files[i].momento.mes);
            if (files[i].momento.mes<=0 || files[i].momento.mes>12) printf("\n\t\t * Error. Numero de mes fuera del rango del anio, o entrada incorrecta. *\n\n");
        } while (files[i].momento.mes<=0 || files[i].momento.mes>12);

        //Dias maximos por mes del anio: 31 29 31 30 31 30 31 31 30 31 30 31
        do{ error=0;
            fflush(stdin);
            printf(" Dia de creacion del archivo %d (ejemplo, 27): ",i+1);
            scanf(" %hd",&files[i].momento.dia);
            switch (files[i].momento.mes){
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    if (files[i].momento.dia>31 || files[i].momento.dia <= 0){
                        error++;
                        printf("\n\t\t * Error. Numero de dia fuera del rango del mes. *\n\n");
                    }
                    break;
                case 4: case 6: case 9: case 11:
                    if (files[i].momento.dia>30 || files[i].momento.dia <= 0){
                        error++;
                        printf("\n\t\t * Error. Numero de dia fuera del rango del mes. *\n\n");
                    }
                    break;
                case 2:
                    if (files[i].momento.dia>29 || files[i].momento.dia <= 0){
                        error++;
                        printf("\n\t\t * Error. Numero de dia fuera del rango del mes. *\n\n");
                    }
                    break;
                default: printf("\n\t\t * Error. Probablemente la entrada de mes o dia fue incorrecta. *\n\n");
                    break;
            }
        } while (error>0);
        
		do{ error=0;
            fflush(stdin);
            printf(" Hora y minuto de creacion del archivo %d (Formato de 24 horas. Ejemplo: 23 59): ",i+1);
            scanf(" %hd %hd",&files[i].momento.hora,&files[i].momento.minuto);
            if (files[i].momento.hora>23 || files[i].momento.hora<0){
                error++;
                printf("\n\t\t * Error. Numero de hora invalido. Ingrese una hora del 0 al 23*\n\n");
            }else if (files[i].momento.minuto<0 || files[i].momento.minuto>59){
                error++;
                printf("\n\t\t * Error. Numero de minuto invalido. Ingrese un numero de minuto del 0 al 59*\n\n");
            }
        } while (error>0);

        files[i].perm=0;
        j=0,l=256;
        while (j<3){
            k=0;
            while (k<3){
                fflush(stdin);
                printf(" Desea que el ");
                switch (j){
                    case 0: printf("Propietario "); break;
                    case 1: printf("Grupo "); break;
                    case 2: printf("resto de usuarios "); break;
                }
                printf("tenga el permiso de ");
                switch (k){
                    case 0: printf("lectura? "); break;
                    case 1: printf("escritura? "); break;
                    case 2: printf("ejecucion? "); break;
                }
                printf("( s = Si, n = No ) ");
				scanf(" %c",&decision);
                switch (decision){
                    case 's': case 'S':
                        files[i].perm+=l;
                        k++;
                        l/=2;
                        break;
                    case 'n': case 'N': k++; l/=2; break;
                    fflush(stdin);
                    default: printf("\n\t\t * Error. Ingrese solamente 's' o 'n' *\n\n");
                }
            }
            j++;
        }
    }

    //Escritura de directorio tipo ls -l
    for (i = 0; i < TAMDIR; i++){
		printf("\n-");
		mascara=256, temp=files[i].perm;
        for (j = 0; j < 9; j++){
            if ((temp&mascara)==mascara){
                switch (j%3){
                    case 0: printf("r"); break;
                    case 1: printf("w"); break;
                    case 2: printf("x"); break;
                    default: printf("ALGO PASO");
                }
            }else{
                printf("-");
            }
            mascara/=2;
        }
		printf(" %s %d ",files[i].user, files[i].tamano);
        switch (files[i].momento.mes){
            case 1: printf("Jan"); break;
            case 2: printf("Feb"); break;
            case 3: printf("Mar"); break;
            case 4: printf("Apr"); break;
            case 5: printf("May"); break;
            case 6: printf("Jun"); break;
            case 7: printf("Jul"); break;
            case 8: printf("Aug"); break;
            case 9: printf("Sep"); break;
            case 10: printf("Oct"); break;
            case 11: printf("Nov"); break;
            case 12: printf("Dec"); break;
            default: printf("ALGO PASO"); break;
        }
        printf(" %d %02d:%02d %s.%c",files[i].momento.dia, files[i].momento.hora, files[i].momento.minuto, files[i].nombre, files[i].tipo);
    }
    return 0;
}
