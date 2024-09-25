/*
    Alumno: Osmar Javier Hernandez Prado
    Matematicas discretas
*/

#include <stdio.h>

int sucesor(int n){
    return n-(-1);
}

int sumaPeano(int a,int b){
    if(b==0) return a;
    else return sumaPeano(sucesor(a),b-1);
}

int multiplicacionPeano(int a,int b){
    if(b==0) return 0;
    else return sumaPeano(multiplicacionPeano(a,b-1),a);
}

int sumaPeanoTrazaSum(int a,int b){
    if(b==0) {
        printf("\n%d + %d = %d", a, b, a);
        return a;
    }
    else {
        printf("\n%d + %d = %d + S(%d) = S(%d + %d)", a, b, a, b-1, a, b-1);
        return sumaPeanoTrazaSum(a,b-1);
    }
}

int sumaPeanoTrazaSuc(int a,int b, int originalA, int originalB){
    int res;
    if(b==0){
        printf("%d",originalA);
        if (originalB==0) printf(" = %d", a);
        return a;
    }
    else{
        printf("S(");
        res = sumaPeanoTrazaSuc(sucesor(a),b-1, originalA, originalB);
        printf(")");
        if (originalB==b) printf(" = %d", res);
        return res;
    }
}

int prodPeanoTrazaProd(int a,int b){
    if(b==0) {
        printf("\n%d * %d = 0", a, b);
        return a;
    }
    else {
        printf("\n%d * %d = %d * S(%d) = %d + (%d * %d)", a, b, a, b-1, a, a, b-1);
        return prodPeanoTrazaProd(a,b-1);
    }
}

int prodPeanoTrazaSum(int a,int b, int originalA, int originalB){
    int res;
    if(b==0){
        printf("0");
        if (originalB==0) printf(" = 0");
        return 0;
    }
    else{
        printf("%d + (", originalA);
        res = sumaPeano(prodPeanoTrazaSum(a,b-1, originalA, originalB),a) ;
        printf(")");
        if (originalB==b) printf(" = %d", res);
        return res;
    }
}

int main(){
    int a,b,resSuma,resMulti;
    printf("Ingrese a: ");
    scanf("%d",&a);
    printf("Ingrese b: ");
    scanf("%d",&b);
    resSuma = sumaPeano(a,b);
    printf("\nResultados: ");
    printf("\n%d + %d = %d",a,b,resSuma);
    resMulti = multiplicacionPeano(a,b);
    printf("\n%d * %d = %d",a,b,resMulti);

    printf("\n\nSuma de Peano con Traza de sumas: ");
    sumaPeanoTrazaSum(a,b);
    printf("\n\nSuma de Peano con Traza de sucesores: \n");
    sumaPeanoTrazaSuc(a,b,a,b); //Esta funcion requiere 4 parametros para el respaldo de valores
    printf("\n\nProducto de Peano con Traza de los productos: ");
    prodPeanoTrazaProd(a,b);
    printf("\n\nProducto de Peano con Traza de las sumas: \n");
    prodPeanoTrazaSum(a,b,a,b);
}