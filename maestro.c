#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void main() {
int n,i,r;
char a;
do{
	printf("Introduzca n\n");
	scanf("%d",&n);
	for(i=0;i<=10;i++){
		r=(n*i);
		printf("%dx%d=%d\n",n,i,r);
	}
	printf("¿repetir?(s/n)\n");
	scanf("%c",&a);
	fflush(stdin);
	printf("%c",a);
	system("pause");
	
}while(a=='s');
}


