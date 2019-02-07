#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void main() {
int v[5],i;
for(i=0;i<5;i++){
	printf("introduzca valor\n");
	scanf("%d",&v[i]);
};
printf("La cadena es:");
for(i=0;i<5;i++){
	printf("%d ",v[i]);
};
}
