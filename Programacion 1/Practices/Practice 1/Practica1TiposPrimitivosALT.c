#include <stdio.h>

int main(){
	int entero,enteroSinSigno,flotante,doble,largo,corto,caracter;
	int bitsEntero,bitsEnteroSinSigno,bitsFlotante,bitsDoble,bitsLargo,bitsCorto,bitsCaracter;
	long rangoEntero=1,rangoDoble=1,rangoLargo=1,rangoCorto=1,rangoCaracter=1;
	long long rangoEnteroSinSigno=1;
	long minimoEntero=-1,minimoDoble=-1,minimoLargo=-1,minimoCorto=-1,minimoCaracter=-1;
	double minimoFlotante=-1,rangoFlotante=1;
	entero=sizeof(int);
	enteroSinSigno=sizeof(unsigned int);
	flotante=sizeof(float);
	doble=sizeof(double);
	largo=sizeof(long);
	corto=sizeof(short);
	caracter=sizeof(char);
	
	bitsEntero=entero*8;
	bitsEnteroSinSigno=enteroSinSigno*8;
	bitsFlotante=flotante*8;
	bitsDoble=doble*8;
	bitsLargo=largo*8;
	bitsCorto=corto*8;
	bitsCaracter=caracter*8;
	
	for(int i=1;i<bitsEntero;i++){
		rangoEntero*=2;
	}
	rangoEntero-=1;
	for(int i=1;i<bitsEntero;i++){
		minimoEntero*=(-2);
	}
	
	for(int i=1;i<=bitsEnteroSinSigno;i++){
		rangoEnteroSinSigno*=2;
	}
	rangoEnteroSinSigno-=1;
	
	for(int i=1;i<bitsFlotante;i++){
		rangoFlotante*=2;
	}
	rangoFlotante-=1;
	for(int i=1;i<bitsFlotante;i++){
		minimoFlotante*=(-2);
	}
	
	printf("Tamano de int en bytes: %d, rango: %ld a %ld \n",entero,minimoEntero,rangoEntero);
	printf("Tamano de unsigned int en bytes: %d, rango: 0 a %lld \n",enteroSinSigno,rangoEnteroSinSigno);
	printf("Tamano de float en bytes: %d, rango: %.5lf a %.5lf \n",flotante,minimoFlotante,rangoFlotante);
	printf("Tamano de double en bytes: %d, rango: \n",doble);
	printf("Tamano de long en bytes: %d, rango: \n",largo);
	printf("Tamano de short en bytes: %d, rango: \n",corto);
	printf("Tamano de char en bytes: %d, rango: \n",caracter);
	
	return 0;
}
