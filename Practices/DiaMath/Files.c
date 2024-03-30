#include <stdio.h>
#include <string.h>
#define MAXSIZE 10

typedef struct{
    short mes,dia,hora,minuto;
}TimeDate;

typedef struct{
    char nombre[35],user[35],tipo[5];
    long long int tamano;
    short int perm;
    TimeDate momento;
}File;

int main(){
    char opcion,opcion2,temporal[100]={0};
    short int temp,mascara,i,j,k,l,error,longMinima,igualdad,tamanoReal=0,decision,decision2,lectura,lecturaTemporal[3];
    File files[MAXSIZE]={0};

    printf("\n\t\tBienvenido! \n\n Cual es su nombre de Usuario? (Se tomaran los 1ros 35 caracteres): ");
    scanf(" %s",files[0].user);
    if (MAXSIZE >= 2) { for (i = 1; i < MAXSIZE; i++) strcpy(files[i].user,files[0].user); printf("\n Anotado!");}
    
    //Parte del menu
    do{ printf("\n Ingrese una letra de opcion, o la letra m para ver el menu: ");
        scanf("%s",&temporal);
        if (strlen(temporal)==1) opcion=temporal[0];
        else printf("\n\t\t * Error. La longitud debe de ser de Solo 1 letra. *\n\n");
        switch (opcion){
        case 'm': case 'M':
            printf("\n\t a\tAgrega un archivo nuevo");
            printf("\n\t c\tCambiar caracteristicas de archivo");
            printf("\n\t e\tEliminar archivo");
            printf("\n\t l\tLista de archivos");
            printf("\n\t 0\tSalir del programa");
            printf("\n\t m\tMuestra este menu\n");
            break;
        case 'a': case 'A':
            if (tamanoReal>=MAXSIZE){
                printf("\n\t\t * No se pueden agregar mas archivos  *\n");
                break;
            }
	        fflush(stdin);
	        printf("\n Ingrese: ");
            i=tamanoReal;
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
                printf(" Tipo del archivo %d ( ingrese maximo 4 letras ): ",i+1);
                scanf("%s",&temporal);
                if (strlen(temporal)>0 && strlen(temporal)<5) strcpy(files[i].tipo,temporal);
                else printf("\n\t\t * Error. La longitud debe de ser de entre 1 y 4 letras. *\n\n");
            } while (strlen(temporal)<1 || strlen(temporal)>4);

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
	        		scanf(" %c",&opcion2);
                    switch (opcion2){
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
            printf(" Archivo creado!");
            tamanoReal++;
            break;
        case 'c': case 'C':
            if (tamanoReal==0){
                printf("\n\t\t * No hay archivos modificables  *\n");
                break;
            }
            printf("Ingrese el numero del archivo que desee modificar (del 1 al %hd): ", tamanoReal);
            fflush(stdin);
            scanf(" %hd", &lectura);
            i=lectura-1;
            printf("Warning: No se puede modificar la fecha ni el usuario por cuestiones de seguridad.\n");
            printf("Siendo:\n\t1. Permisos\t 2. Tamano\t 3. Nombre de archivo\t 4. Tipo del archivo\n");
            printf("Que desea modificar del archivo %hd? (Ingrese el numero de la opcion correspondiente): ", i);
            fflush(stdin);
            scanf(" %hd", &decision);
            switch (decision){
                case 1:
                    printf(" Siendo:\n\t1\tModo normal\n\t2\tModo CHMOD\n Como deseas cambiar los permisos? (Ingrese el numero correspondiente) ");
                    scanf(" %hd", &decision2);
                    switch (decision2){
                        case 1:
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
	                        		scanf(" %c",&opcion2);
                                    switch (opcion2){
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
                            break;
                        case 2:
                            do{
                                printf(" Ingrese los 3 digitos de permisos, juntos (del 0 al 7 cada uno): ");
                                scanf(" %hd",&lectura);
                                temp=0;
                                for (j = 2; j >= 0; j--){
                                    lecturaTemporal[j]=lectura%10;
                                    lectura /= 10;
                                    if (lecturaTemporal[j]>7) break;
                                    switch (j){
                                        case 2:
                                            temp+=lecturaTemporal[j];
                                            break;
                                        case 1:
                                            lecturaTemporal[j] = lecturaTemporal[j] << 3;
                                            temp+=lecturaTemporal[j];
                                            break;
                                        case 0:
                                            lecturaTemporal[j] = lecturaTemporal[j] << 6;
                                            temp+=lecturaTemporal[j];
                                            break;
                                        default:
                                            break;
                                    }
                                }
                                files[i].perm=temp;
                            } while (lecturaTemporal[j]>7);

                            break;
                        default:
                            break;
                        }
                    break;
                case 2:
                    do{ fflush(stdin);
                        printf(" Tamano del archivo %d (en bytes, solo puede ser numerico): ",i+1);
                        scanf(" %lld",&files[i].tamano);
                        if (files[i].tamano==0) printf("\n\t\t * Error. El tamano del archivo debe de ser mayor a cero *\n\n");
                    } while (files[i].tamano==0);
                    printf("Cambio hecho!\n");
                    break;
                case 3:
                    do{ error=0;
                        printf("\n Nombre del archivo %d (Se tomaran los 1ros 35 caracteres): ",i+1);
                        scanf(" %s",files[i].nombre);
                        for (j = 0; j < tamanoReal; j++){
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
                    printf("Cambio hecho!\n");
                    break;
                case 4:
                    do{ fflush(stdin);
                        printf(" Tipo del archivo %d ( ingrese maximo 4 letras ): ",i+1);
                        scanf("%s",&temporal);
                        if (strlen(temporal)>0 && strlen(temporal)<5) strcpy(files[i].tipo,temporal);
                        else printf("\n\t\t * Error. La longitud debe de ser de entre 1 y 4 letras. *\n\n");
                    } while (strlen(temporal)<1 || strlen(temporal)>4);
                    printf("Cambio hecho!\n");
                    break;
                default:
                    printf("\n\t\t * Lo sentimos, opcion invalida.  *\n");
                    break;
            }
            break;
        case 'e': case 'E':
            if (tamanoReal==0){
                printf("\n\t\t * No hay archivos a eliminar  *\n");
                break;
            }
            printf(" Ingrese el numero del archivo que desea eliminar (del 1 al %hd): ", tamanoReal);
            scanf("%hd", &i);
            if (i > 0 && i <= tamanoReal){
                for (int j = i - 1; j < tamanoReal - 1; j++) // Al eliminar el archivo recorre las demas una posicion atras
                {   
                    files[j].perm = files[j+1].perm;
                    strcpy(files[j].user, files[j+1].user);
                    files[j].tamano = files[j+1].tamano;
                    files[j].momento.mes = files[j+1].momento.mes;
                    files[j].momento.dia = files[j+1].momento.dia;
                    files[j].momento.hora = files[j+1].momento.hora;
                    files[j].momento.minuto = files[j+1].momento.minuto;
                    strcpy(files[j].nombre, files[j+1].nombre);
                    strcpy(files[j].tipo, files[j+1].tipo);
                }

                tamanoReal--;
                printf(" Warning: Archivo eliminado!\n");
            }
            else printf("\n\t\t * Error. Numero de archivo no valido *\n\n");
            break;
        case 'l': case 'L':
            //Escritura de directorio tipo ls -l            
            for (i = 0; i < tamanoReal; i++){
	        	printf("\n -");
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
                printf(" %d %02d:%02d %s.%s",files[i].momento.dia, files[i].momento.hora, files[i].momento.minuto, files[i].nombre, files[i].tipo);
            }
            break;
        case '0':
            printf("\n Saliendo...");
            break;
        default:
            printf("\n\t\t * Error. Opcion No Valida *\n\n");
            break;
        }
    } while (opcion!='0');

    return 0;
}