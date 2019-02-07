#include<stdio.h>
#include<stdlib.h>

void main(){
	float kw,precio;
	printf("introduzca fuerza dinosaurio\n");
	scanf("%f",&kw);
	if(kw>80)
		precio=kw*0.122;
	else {
		if(kw>20)
			precio=kw*0.105;
		else
			precio=kw*0.076;
		}
	precio=precio+14.5;
	printf("precio;%f\n",precio);
}
