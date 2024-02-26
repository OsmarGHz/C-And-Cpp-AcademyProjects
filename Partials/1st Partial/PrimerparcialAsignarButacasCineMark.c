#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define NUMMAXFUN 48
#define FILAS 16
#define COLUMNAS 13

/* Integrantes
Aguila de Ita Angel Manuel

Hernandez Prado Osmar Javier

Lopez Momox Limhi Gerson
*/

void ocuparButaca(unsigned char butacas[][2], int fila, int columna) // Función para ocupar una butaca
{
    butacas[columna][fila / 8] |= (1 << (fila % 8));
}

void liberarButaca(unsigned char butacas[][2], int fila, int columna) // Función para liberar una butaca
{
    butacas[columna][fila / 8] &= ~(1 << (fila % 8));
}

int estadoButaca(unsigned char butacas[][2], int fila, int columna) // Función para imprimir el estado de las butacas
{
    return (butacas[columna][fila / 8] >> (fila % 8)) & 1;
}

void mostrarButacas(unsigned char butacas[][2])
{   
    int filaActual,j,fila,columna;

    printf("Estado de las butacas:\n        ");

    for (j = 0; j < COLUMNAS; j++) printf("  Col%2d|", j);

    printf("\n------------------------------------------------------------------------------------------------------------------\n");

    for (fila = 0; fila < FILAS; fila++)
    {
        printf("Fila%2d  |", filaActual++);
        for (columna = 0; columna < COLUMNAS; columna++)
        {
            printf("\t%c", estadoButaca(butacas, fila, columna) ? 'O' : 'L');
        }
        printf("\n");
    }
}

typedef struct
{
    char nombrePelicula[50];
    char clasificacion[3];
    char genero[20];
    short int horaInicio, minutoInicio, horaFin, minutoFin;
    unsigned char butacas[COLUMNAS][2];
} FUNCION;

int main()
{
    short int i, numeroFunciones = 0, decision = 0, decision2 = 0, decision3 = 0;
    char c;
    FUNCION funciones[NUMMAXFUN]={0};
    int fila, columna;

    printf("\n\t * Bienvenido, admin! *");

    while (decision != 2 || numeroFunciones == 0)
    {
        decision = 0;
        printf("\nOpciones: ");
        printf("\n\t1. Control de las funciones");
        if (numeroFunciones > 0) printf("\n\t2. INICIAR VENTA DE BOLETOS");
        printf("\nIngrese el numero de la opcion deseada: ");
        fflush(stdin);
        scanf("%hd", &decision);

        if (decision == 1)
        {
            decision2 = 0;
            while (decision2 != 4)
            {
                if (numeroFunciones > 0)
                {
                    printf("\nID / \'Nombre\' / \'Genero\' / Clasificacion / Hora de inicio / Hora de fin.\n");
                    for (i = 0; i < numeroFunciones; i++)
                        printf("%hd. \'%s\' \'%s\' %s %02d:%02d %02d:%02d\n", i + 1, funciones[i].nombrePelicula, funciones[i].genero, funciones[i].clasificacion, funciones[i].horaInicio, funciones[i].minutoInicio, funciones[i].horaFin, funciones[i].minutoFin);
                }
                printf("Que desea hacer?");
                if (numeroFunciones < NUMMAXFUN)
                    printf("\n\t1. Agregar una funcion (%hd funcion(es) actualmente, 48 como maximo)", numeroFunciones);
                if (numeroFunciones > 0)
                {
                    printf("\n\t2. Modificar una funcion");
                    printf("\n\t3. Eliminar una funcion");
                }
                printf("\n\t4. SALIR del control de funciones \nIngrese el numero de la opcion deseada: ");
                scanf("%hd", &decision2);

                if (decision2 == 1)
                {
                    printf("Ingrese el nombre de la pelicula de la funcion %hd (Max. 50 caracteres): ", numeroFunciones + 1);
                    while ((c = getchar()) != '\n' && c != EOF)
                        ; // Otra forma de hacer flush stdin en situaciones como esta
                    scanf(" %50[^\n]s", funciones[numeroFunciones].nombrePelicula);
                    printf("Ingrese el genero de la pelicula (Max. 20 caracteres): ");
                    while ((c = getchar()) != '\n' && c != EOF)
                        ;
                    scanf(" %20[^\n]s", funciones[numeroFunciones].genero);
                    printf("Ingrese la clasificacion de la pelicula (Max. 2 letras. Ejemplo: AA): ");
                    while ((c = getchar()) != '\n' && c != EOF)
                        ;
                    scanf(" %2[^\n]s", funciones[numeroFunciones].clasificacion);
                    for (i = 0; i < strlen(funciones[numeroFunciones].clasificacion); i++)
                    {
                        funciones[numeroFunciones].clasificacion[i] = toupper(funciones[numeroFunciones].clasificacion[i]);
                    }
                    do{
                        printf("Ingrese la hora y minuto de inicio de la funcion %hd (en formato 24 horas, ejemplo: 11 27): ", numeroFunciones + 1);
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                        scanf(" %hd %hd", &funciones[numeroFunciones].horaInicio, &funciones[numeroFunciones].minutoInicio);
                        if (funciones[numeroFunciones].horaInicio<0 || funciones[numeroFunciones].minutoInicio<0 || funciones[numeroFunciones].horaInicio>=24 || funciones[numeroFunciones].minutoInicio>=60){
                            printf("\n\t\t * Lo sentimos, hora invalida.  *\n");
                        }
                    } while (funciones[numeroFunciones].horaInicio<0 || funciones[numeroFunciones].minutoInicio<0 || funciones[numeroFunciones].horaInicio>=24 || funciones[numeroFunciones].minutoInicio>=60);
                    do{
                        printf("Ingrese la hora y minuto de finalizacion de la funcion %hd (en formato 24 horas, ejemplo: 13 10): ", numeroFunciones + 1);
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                        scanf(" %hd %hd", &funciones[numeroFunciones].horaFin, &funciones[numeroFunciones].minutoFin);
                        if (funciones[numeroFunciones].horaFin<0 || funciones[numeroFunciones].minutoFin<0 || funciones[numeroFunciones].horaFin>=24 || funciones[numeroFunciones].minutoFin>=60){
                            printf("\n\t\t * Lo sentimos, hora invalida.  *\n");
                        }
                        
                    } while (funciones[numeroFunciones].horaFin<0 || funciones[numeroFunciones].minutoFin<0 || funciones[numeroFunciones].horaFin>=24 || funciones[numeroFunciones].minutoFin>=60);
                    numeroFunciones++;
                    printf("Funcion agregada!\n");
                }
                else if (decision2 == 2)
                {
                    printf("Ingrese el numero de la funcion que desee modificar: ");
                    fflush(stdin);
                    scanf(" %hd", &i);
                    printf("Siendo:\n\t1. Nombre de Pelicula\t 2. Genero\t 3. Clasificacion\t 4. Hora Inicio Funcion\t 5. Hora Fin Funcion\n");
                    printf("Que desea modificar de la funcion %hd? (Ingrese el numero de la opcion correspondiente): ", i);
                    fflush(stdin);
                    scanf(" %hd", &decision3);
                    switch (decision3)
                    {
                    case 1:
                        printf("Ingrese el nombre de la pelicula de la funcion %hd (Max. 50 caracteres): ", i);
                        while ((c = getchar()) != '\n' && c != EOF)
                            ; // Otra forma de hacer flush stdin en situaciones como esta
                        scanf(" %50[^\n]s", funciones[i - 1].nombrePelicula);
                        printf("Cambio hecho!\n");
                        break;
                    case 2:
                        printf("Ingrese el genero de la pelicula (Max. 20 caracteres): ");
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                        scanf(" %20[^\n]s", funciones[i - 1].genero);
                        printf("Cambio hecho!\n");
                        break;
                    case 3:
                        printf("Ingrese la clasificacion de la pelicula (Max. 2 letras. Ejemplo: AA): ");
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                        scanf(" %2[^\n]s", funciones[i - 1].clasificacion);
                        for (i = 0; i < strlen(funciones[i - 1].clasificacion); i++)
                        {
                            funciones[i - 1].clasificacion[i] = toupper(funciones[i - 1].clasificacion[i]);
                        }
                        printf("Cambio hecho!\n");
                        break;
                    case 4:
                        printf("Ingrese la hora y minuto de inicio de la funcion %hd (en formato 24 horas, ejemplo: 11 27): ", i);
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                        scanf(" %hd %hd", &funciones[i - 1].horaInicio, &funciones[i - 1].minutoInicio);
                        printf("Cambio hecho!\n");
                        break;
                    case 5:
                        printf("Ingrese la hora y minuto de finalizacion de la funcion %hd (en formato 24 horas, ejemplo: 13 10): ", i);
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                        scanf(" %hd %hd", &funciones[i - 1].horaFin, &funciones[i - 1].minutoFin);
                        printf("Cambio hecho!\n");
                        break;
                    default:
                        printf("\n\t\t * Lo sentimos, opcion invalida.  *\n");
                        break;
                    }
                }
                else if (decision2 == 3)
                {
                    printf("Ingrese el numero de la funcion que desea eliminar: ");
                    scanf("%hd", &i);

                    if (i > 0 && i <= numeroFunciones)
                    {
                        for (int j = i - 1; j < numeroFunciones - 1; j++) // Al eliminar la función recorre las demas una posicion atras
                        {
                            strcpy(funciones[j].nombrePelicula, funciones[j + 1].nombrePelicula);
                            strcpy(funciones[j].genero, funciones[j + 1].genero);
                            strcpy(funciones[j].clasificacion, funciones[j + 1].clasificacion);
                            funciones[j].horaInicio = funciones[j + 1].horaInicio;
                            funciones[j].minutoInicio = funciones[j + 1].minutoInicio;
                            funciones[j].horaFin = funciones[j + 1].horaFin;
                            funciones[j].minutoFin = funciones[j + 1].minutoFin;
                        }

                        numeroFunciones--;
                        printf("Funcion eliminada!\n");
                    }
                    else
                    {
                        printf("ID de funcion invalido.\n");
                    }
                }
                else if (decision2 == 4)
                {
                    printf("Saliendo...");
                }
                else
                {
                    printf("\n\t\t * Lo sentimos, opcion invalida.  *\n");
                }
            }
        }
        else if (decision == 2 && numeroFunciones > 0){
            printf("\n\t\t * Bienvenido a CINEMARK 1.0 *\n");
            do{
                printf("\nVENTA DE BOLETOS\n");
                printf("\n\t1. Seleccionar una funcion");
                printf("\n\t2. Salir\n");
                printf("\nIngrese el numero de la opcion deseada: ");
                scanf("%hd",&decision2);
                if (decision2==1){
                    printf("\nID / \'Nombre\' / \'Genero\' / Clasificacion / Hora de inicio / Hora de fin.\n");
                    for (i = 0; i < numeroFunciones; i++) printf("%hd. \'%s\' \'%s\' %s %02d:%02d %02d:%02d\n", i + 1, funciones[i].nombrePelicula, funciones[i].genero, funciones[i].clasificacion, funciones[i].horaInicio, funciones[i].minutoInicio, funciones[i].horaFin, funciones[i].minutoFin);
                    do{
                        printf("\nIngrese el numero de funcion de las disponibles en la lista: ");
                        scanf("%hd",&i);
                        if (i<=0 || i>numeroFunciones) printf("\n\t\t * Lo sentimos, opcion invalida.  *\n");
                    } while (i<=0 || i>numeroFunciones);
                    do{
                        printf("\nSeleccione una opcion para la pelicula \'%s\' a las %02d:%02d :\n", funciones[i-1].nombrePelicula, funciones[i-1].horaInicio, funciones[i-1].minutoInicio);
                        mostrarButacas(funciones[i-1].butacas);
                        printf("\n\t1. Asignar butaca");
                        printf("\n\t2. Liberar butaca");
                        printf("\n\t3. Salir\n");
                        printf("\nIngrese el numero de la opcion deseada: ");
                        scanf("%hd", &decision3);
                        switch (decision3){
                            case 1:
                                printf("Siendo L = Libre, O = Ocupada, Ingrese fila y columna de la butaca a asignar (0-%d, 0-%d): ", FILAS - 1, COLUMNAS - 1);
                                scanf("%d %d", &fila, &columna);
                                if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS){
                                    ocuparButaca(funciones[i-1].butacas, fila, columna);
                                    printf("Butaca asignada exitosamente.\nAqui esta su boleto:\n");
                                    printf("\n\t\t *            FUNCIONES DE CINE CINEMARK SA DE CV            *\n");
                                    printf("\n\t\t *                           BOLETO                          *\n");
                                    printf("\n\t\t * Pelicula: \'%s\'\n",funciones[i-1].nombrePelicula);
                                    printf("\n\t\t * Fila: %d\n",fila);
                                    printf("\n\t\t * Columna (o asiento): %d\n",columna);
                                    printf("\n\t\t * Hora de inicio: %02d:%02d\n",funciones[i-1].horaInicio,funciones[i-1].minutoInicio);
                                    printf("\n\t\t * Hora de finalizacion: %02d:%02d\n",funciones[i-1].horaFin,funciones[i-1].minutoFin);
                                    printf("\n\t\t * Genero de la Pelicula: %s\n",funciones[i-1].genero);
                                    printf("\n\t\t * Clasificacion: %s\n\n",funciones[i-1].clasificacion);
                                    printf("\n\t\t * FAVOR DE NO PERDER EL BOLETO HASTA ENTREGARLO EN         *\n");
                                    printf("\n\t\t * TAQUILLA O CANCELARLO, LO QUE OCURRA PRIMERO             *\n");
                                }
                                else{
                                    printf("Fila o columna invalida.\n");
                                }
                                break;
                            case 2:
                                printf("Siendo L = Libre, O = Ocupada, Ingrese fila y columna de la butaca a liberar (0-%d, 0-%d): ", FILAS - 1, COLUMNAS - 1);
                                scanf("%d %d", &fila, &columna);
                                if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS){
                                    liberarButaca(funciones[i-1].butacas, fila, columna);
                                    printf("Butaca liberada exitosamente.\n");
                                }
                                else{
                                    printf("Fila o columna invalida.\n");
                                }
                                break;
                            case 3:
                                printf("Saliendo del programa...\n");
                                break;
                            default:
                                printf("Opcion invalida. Por favor, seleccione una opcion valida.\n");
                        }
                    } while (decision3 != 3);
                }else if(decision2==2){
                    printf("Saliendo...");
                }else{
                    printf("\n\t\t * Lo sentimos, opcion invalida.  *\n");
                }
            } while (decision2!=2);
        }
    }
    return 0;
}

////funcion que devuelva el numero de sillas desocupadas en la sala