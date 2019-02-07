#include <stdio.h>
#include <stdlib.h>
#define N 4

 typedef struct { 
    char nombre[50]; 
    char telefono[10]; 
} Tcontacto; 
        
void main(){
	Tcontacto lista[N];
	char tel[10];
	int i,j, encontrado=0,distinto;
	for(i=0;i<N;i++){
		printf("Nombre:");
		fflush(stdin);
		gets(lista[i].nombre);
		printf("Telefono:");
		gets(lista[i].telefono);
		fflush(stdin);
	}
	printf("introduzca un nombre:");
	gets(tel);
	fflush(stdin);
	for(i=0;i<N&&encontrado==0;i++){
		distinto=0;
		for(j=0;tel[j]!='\0'&&lista[i].nombre[j]!='\0'&&distinto==0;j++){
			if(tel[j]!=lista[i].nombre[j])
			distinto=1;
		}
		if(distinto==0){
			printf("El telefono es: ");
			puts (lista[i].telefono);
			encontrado=1;
		}
	}
	if(encontrado==0)
		printf("No existe nadie con ese numero");
		
}
