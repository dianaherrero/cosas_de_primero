#include <stdio.h>
#include <stdlib.h>


	void main() {
	int juan=0, chus=0, n, i;
	char j, c;
	printf("introduzca victorias maximas\n");
	scanf("%d",&n);
	do
	{
	do{
		printf("Juan, introduzca su arma (piedra(I), papel(P), tijera(T), lagarto(L) o spock(S))\n");
		fflush(stdin);
		scanf("%c",&j);
		fflush(stdin);
		if(j!='I'&&j!='P'&&j!='T'&&j!='L'&&j!='S')
			printf("Ese arma no existe, pruebe otra\n");
	}while(j!='I'&&j!='P'&&j!='T'&&j!='L'&&j!='S');
	system("cls");
	do{
		printf("Ch�s, introduzca su arma (piedra(I), papel(P), tijera(T), lagarto(L) o spock(S))\n");
		scanf("%c",&c);
		fflush(stdin);
		if(c!='I'&&c!='P'&&c!='T'&&c!='L'&&c!='S')
			printf("Ese arma no existe, pruebe otra\n");
	}while(c!='I'&&c!='P'&&c!='T'&&c!='L'&&c!='S');
	system("cls");
	
	if(j==c)
		printf("Empate, hab�is usado las mismas armas\n");
	if(j=='I')
		{if (c=='P')
			{printf("Papel envuelve a piedra, punto para Ch�s\n");
			chus++;};
		
		if (c=='T')
			{printf("Piedra aplasta a tijera, punto para Juan\n");
			juan++;};
		
		if (c=='L')
			{printf("Piedra aplasta a lagarto, punto para Juan\n");
			juan++;};
		
		if (c=='S')
			{printf("Spock vaporiza a piedra, punto para Ch�s\n");
			chus++;};
		};
	if(j=='P')
		{if (c=='I')
			{printf("Papel envuelve a piedra, punto para Juan\n");
			juan++;};

		if (c=='T')
			{printf("Tijera corta a papel, punto para Ch�s\n");
			chus++;};
		
		if (c=='L')
			{printf("Lagarto devora a papel, punto para Ch�s\n");
			chus++;};
		
		if (c=='S')
			{printf("Papel desautoriza a Spock, punto para Juan\n");
			juan++;};
		};
	if(j=='S')
		{if (c=='P')
			{printf("Papel desautoriza a Spock, punto para Ch�s\n");
			chus++;};
	
		if (c=='T')
			{printf("Spock rompe tijera, punto para Juan\n");
			juan++;};
		
		if (c=='L')
			{printf("Lagarto envenena a Spock, punto para Ch�s\n");
			chus++;};
		
		if (c=='I')
			{printf("Spock vaporiza a piedra, punto para Juan\n");
			juan++;};
		};
	if(j=='T')
		{if (c=='P')
			{printf("Tijera corta a papel, punto para Juan\n");
			juan++;};
		
		if (c=='I')
			{printf("Piedra aplasta a tijera, punto para Ch�s\n");
			chus++;};
		
		if (c=='L')
			{printf("Tijera decapita a lagarto, punto para Juan\n");
			juan++;};
		
		if (c=='S')
			{printf("Spock rompe a tijera, punto para Ch�s\n");
			chus++;};
		};
	if(j=='L')
		{if (c=='P')
			{printf("Lagarto devora a papel, punto para Juan\n");
			juan++;};
	
		if (c=='T')
			{printf("Tijera decapita a lagarto, punto para Ch�s\n");
			chus++;};
		
		if (c=='I')
			{printf("Piedra aplasta a lagarto, punto para Ch�s\n");
			chus++;};
		
		if (c=='S')
			{printf("Lagarto envenena a Spock, punto para Juan\n");
			juan++;};
		};
	
	}while ((chus<n)&&(juan<n));
	printf("%d-%d\n",juan, chus);
	if(juan>chus)
	printf("Gana Juan\n");
	else
	printf("Gana Ch�s\n");
	system ("PAUSE");
}
