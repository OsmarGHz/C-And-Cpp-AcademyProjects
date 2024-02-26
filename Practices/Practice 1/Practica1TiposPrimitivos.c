#include <stdio.h>
#include <limits.h>
#include <string.h>

/* Integrantes
Cortes Arenas Nadia 

Hernández Romero Maite 

Hernández Prado Osmar Javier

Lopez Momox Limhi Gerson
*/

int main() {
    //unsigned char charsing = 9879879896;
    //printf("\n -------    %ld     ", charsing); Esta fue usada para ver el rango de un unsigned char
    // Imprime información sobre los tamaños de los tipos de datos primitivos
    printf("\n\tPractica 1 Rangos Primitivos\n");

    printf("\nNumero de bytes en int : %d\n", sizeof(int));
    printf("\nNumero de bytes en short : %d\n", sizeof(short));
    printf("\nNumero de bytes en long : %d\n", sizeof(long));
    printf("\nNumero de bytes en long long : %d\n", sizeof(long long));
    printf("\nNumero de bytes en float : %d\n", sizeof(float));
    printf("\nNumero de bytes en double : %d\n", sizeof(double));
    printf("\nNumero de bytes en long double : %d\n", sizeof(long double));
    printf("\nNumero de bytes en char : %d\n", sizeof(char));
    printf("\nNumero de bytes en char sin signo : %d\n", sizeof(unsigned char));

    // Imprime información sobre los rangos de los tipos de datos primitivos
    printf("\nEl rango operativo de int va desde %d hasta %d\n", INT_MIN, INT_MAX);
    printf("\nEl rango operativo de short va desde %d hasta %d\n", SHRT_MIN, SHRT_MAX);
    printf("\nEl rango operativo de long va desde %ld hasta %ld\n", LONG_MIN, LONG_MAX);
    printf("\nEl rango operativo de float va desde %e hasta %e\n", -__FLT_MAX__, __FLT_MAX__);
    printf("\nEl rango operativo de double va desde %e hasta %e\n", -__DBL_MAX__, __DBL_MAX__);
    printf("\nEl rango operativo de char va desde %d hasta %d\n", SCHAR_MIN, SCHAR_MAX);

    // Imprime información sobre los rangos de los tipos de datos primitivos sin signo
    printf("\nEl rango operativo sin signo de int va desde 0 hasta %u\n", UINT_MAX);
    printf("\nEl rango operativo sin signo de short va desde 0 hasta %u\n", USHRT_MAX);
    printf("\nEl rango operativo sin signo de long va desde 0 hasta %lu\n", ULONG_MAX);
    printf("\nEl rango operativo sin signo de char va desde 0 hasta %d\n", UCHAR_MAX);

    return 0;
}