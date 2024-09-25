#include <stdio.h>
#include <string.h>

typedef struct{
    int h,m;
}Time;

typedef struct{
    char mes[20];
    int d;
}Date;

typedef struct{
    char perm[3];
}Permisos;

typedef struct{
    char nomArchivo[20];
    char usua[20];
    int tam;
    char tipoArchivo;
    Time tiempo;
    Date fecha;
    Permisos pro[3];
}Archivo;

int main(){
    char decision;
    short lecturaSeparada[3],temp;
    int i,j,lectura;
    Archivo files[20]={0};

    files[0].pro[0].perm[0] = 1; // Lectura
    files[0].pro[0].perm[1] = 1; // Escritura
    files[0].pro[0].perm[2] = 0; // Ejecucion
    files[0].pro[1].perm[0] = 1; // Lectura
    files[0].pro[1].perm[1] = 0; // Escritura
    files[0].pro[1].perm[2] = 0; // Ejecucion
    files[0].pro[2].perm[0] = 1; // Lectura
    files[0].pro[2].perm[1] = 0; // Escritura
    files[0].pro[2].perm[2] = 0; // Ejecucion
    strcpy(files[0].usua,"Rider");
    files[0].tam = 50;
    strcpy(files[0].fecha.mes,"Feb");
    files[0].fecha.d = 7;
    files[0].tiempo.h = 17;
    files[0].tiempo.m = 01;
    strcpy(files[0].nomArchivo,"archivo1");
    files[0].tipoArchivo='c';
    
    printf("\n-");
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if(files[0].pro[i].perm[j]==1){
                switch (j){
                case 0: printf("r"); break;
                case 1: printf("w"); break;
                case 2: printf("x"); break;
                default: printf("ALGO PASÓ");
                }
            }else printf("-");
        }
    }
    printf(" %s %d %s %d %02d:%02d %s.%c ",files[0].usua, files[0].tam, files[0].fecha.mes, files[0].fecha.d, files[0].tiempo.h, files[0].tiempo.m, files[0].nomArchivo, files[0].tipoArchivo);

    printf("\nIngrese 'c' para modificar permisos de un archivo, o cualquier otra cosa para terminar el programa: ");
    scanf("%c",&decision);
    switch (decision){
        case 'c':
            printf("Ingrese los 3 digitos de permisos: ");
            scanf("%i",&lectura);
            for (i = 2; i >= 0; i--){
                lecturaSeparada[i]=lectura%10;
                lectura /= 10;
                temp=lecturaSeparada[i];
                for (j = 2; j >= 0; j--){
                    if ((temp & 1) == 1){
                        files[0].pro[i].perm[j]=1;
                    }else{
                        files[0].pro[i].perm[j]=0;
                    }
                    temp = temp >> 1;
                }
            }
            printf("\n-");
            for (i = 0; i < 3; i++){
                for (j = 0; j < 3; j++){
                    if(files[0].pro[i].perm[j]==1){
                        switch (j){
                        case 0: printf("r"); break;
                        case 1: printf("w"); break;
                        case 2: printf("x"); break;
                        default: printf("ALGO PASÓ");
                        }
                    }else printf("-");
                }
            }
            printf(" %s %d %s %d %02d:%02d %s.%c ",files[0].usua, files[0].tam, files[0].fecha.mes, files[0].fecha.d, files[0].tiempo.h, files[0].tiempo.m, files[0].nomArchivo, files[0].tipoArchivo);
            break;
        default:
            break;
    }
}