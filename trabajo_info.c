#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#define filas 6
#define columnas 7
#define N 20
#define L 100

typedef struct{
	char usuario[N], contras[N];
	int partidas, victorias, record, derrotas, empates;
}ficha;

int recuperar_tablero (int [filas][columnas], int *, char[N], char[N]);
int guardar_tablero(int [filas][columnas], int , char[N], char[N]);
void jugar(int [filas][columnas], int, char [N], char [N] , ficha[L]) ;
void seguir_partida( ficha[L]);
void empezar_partida(char jug1[N], char jug2[N], ficha[L]);
int comprobar_victoria(int , int [filas][columnas], int , int );
void colocar_ficha(int , int [filas][columnas], int *, int *);
int pedir_fila(int , int [filas][columnas]);
int pedir_columna(int , int [filas][columnas]);
void mostrar_tablero(int [filas][columnas]);
void inicializar_tablero (int [filas][columnas]);
void jugar_con_lui(int [filas][columnas], int, char[N], ficha[L]);
void empezar_con_lui(char[N], ficha[L]);	
int elegir_columna(int , int [filas][columnas]);
void colocar_ficha_2(int , int [filas][columnas], int *, int *);
void registrar_usuario(char [N], char [N], ficha[L], int*);
int comprobar_usuario(char [N], ficha [L], int);
int comprobar_contrasena(char [N], char [N], ficha [L]);
void dos_jugadores(char [N], char [N], int*, ficha[L]);
int datos_jugador(char [N], char [N], int*, ficha[L]);
void un_jugador(char [N], int*, ficha[L]);
void imprimir_ranking(ficha [L], int);
int leer_ranking(ficha [L]);
void sumar_partida(char [N], ficha [L]);
void sumar_victoria(char [N], ficha [L]);
void sumar_derrota(char [N], ficha [L]);
void sumar_empate(char [N], ficha [L]);
void cambiar_record(char [N], ficha [L], int );
void guardar_todo(ficha [L], int);
int comprobar_datos2(char [N], ficha [L]);
int comprobar_datos1(char [N], char [N], ficha [L]);
void ordenar_ranking(ficha [L],int);

void ordenar_ranking(ficha lista[L],int l)
{	ficha aux;
 	 int i,j,k;
 	 for(i=0;i<l;i++)
	  {for(j=(i+1);j<l;j++)
	    {if((lista[j].record)<(lista[i].record)){
			for(k=0;lista[i].usuario[k]!='\0';k++){
			aux.usuario[k]=lista[i].usuario[k];
			aux.contras[k]=lista[i].contras[k];
			}
			aux.partidas=lista[i].partidas;
			aux.victorias=lista[i].victorias;
			aux.record=lista[i].record;
			aux.derrotas=lista[i].derrotas;
			aux.empates=lista[i].empates;
			for(k=0;lista[j].usuario[k]!='\0';k++){
			lista[i].usuario[k]=lista[j].usuario[k];
			lista[i].contras[k]=lista[j].contras[k];
			}
			lista[i].partidas=lista[j].partidas;
			lista[i].victorias=lista[j].victorias;
			lista[i].record=lista[j].record;
			lista[i].derrotas=lista[j].derrotas;
			lista[i].empates=lista[j].empates;
			for(k=0;aux.usuario[k]!='\0';k++){
			lista[j].usuario[k]=aux.usuario[k];
			lista[j].contras[k]=aux.contras[k];
			}
			lista[j].partidas=aux.partidas;
			lista[j].victorias=aux.victorias;
			lista[j].record=aux.record;
			lista[j].derrotas=aux.derrotas;
			lista[j].empates=aux.empates;
			}
    	}
	}
}						


void inicializar_tablero (int tablero[filas][columnas]) //pone el tablero a 0 si se inicia una partida, o lo empieza como estaba si se continúa una guardada
{int i, j;
for(i=0;i<filas;i++)
	for(j=0;j<columnas;j++)
		tablero[i][j]=0;
}

void mostrar_tablero(int tablero[filas][columnas])		//Muestra en pantalla la situación del tablero
{
int i, j;
system("cls");
printf("|");
for(i=1;i<=columnas;i++)
{printf("%d",i);
printf("|");
};
printf("\n");
for(i=0;i<filas;i++)
	{printf("|");
	for(j=0;j<columnas;j++)
		{switch(tablero[i][j])
			{case 1:
				printf("*");
				break;
			case 2:
				printf("O");
				break;
			default:
				printf(" ");
			};
		
		printf("|");
		};
	printf("\n");
	};
}


int pedir_columna(int movimientos, int tablero[filas][columnas]) //Pide al jugador al que toque la columna, la lee y comprueba que sea correcta
{int c;
do
	{if((movimientos%2)==0)
		printf("\nJugador 1, elija la columna en la que desea introducir la ficha o '0' para guardar\n");
	else
		printf("\nJugador 2, elija la columna en la que desea introducir la fichao '0' para guardar\n");
	scanf("%d",&c);
	fflush(stdin);
	c--;
	if(c>(columnas-1)||c<0)
		{if(c!=-1)
			printf("\nEsa columna no existe, pruebe con otra\n");}
	else
	if(tablero[0][c]!=0)
		printf("\nEsa columna está completa, pruebe con otra\n");
	}
while (((tablero[0][c]!=0)||c>(columnas-1)||c<0)&&c!=-1);

return c;
}


int pedir_fila(int c, int tablero[filas][columnas]) //Comprueba en qué fila de la columna dada se ha de colocar la ficha; la última que esté vacía
{int f=(filas-1), ficha_colocada=0;
	do
	{if (tablero[f][c]==0)
		ficha_colocada=1;
	else
		f--;
	}while (ficha_colocada==0);
return f;
}

void colocar_ficha(int movimientos, int tablero[filas][columnas], int *col, int *fil) //Pide al jugador la columna y coloca su ficha en la columna dada
{
*col=pedir_columna(movimientos, tablero);
if((*col)!=-1)							//siempre que no se haya pedido guardar la partida
	{*fil=pedir_fila(*col, tablero);
	tablero[*fil][*col]=(movimientos%2+1); //coloca un uno o un dos en la casilla de la matriz en la que se haya puesto la ficha, según el jugador que esté jugando
	}
	
}


int comprobar_victoria(int movimientos, int tablero[filas][columnas], int c, int f) //comprueba si el jugador que acaba de poner ficha ha hecho 4 en raya
{int jugador=(movimientos%2+1), i,j=0,k, victoria=0;
//comprobar columna
if(f<(filas-3))
	{victoria=jugador;
	for(i=(f+1);i<=(f+3);i++)
		if (tablero[i][c]!=jugador)
			victoria=0;
	};
//comprobar fila
for(i=(c+1);(tablero[f][i]==jugador)&&(i<columnas)&&(j<3);i++)
	j++;
for(i=(c-1);(tablero[f][i]==jugador)&&(i>=0)&&(j<3);i--)
	j++;
if(j==3)
	victoria=jugador;
//comprobar diagonal ascendente
j=0;
i=(c+1);
k=(f+1);
while((tablero[k][i]==jugador)&&(i<columnas)&&(k<filas)&&(j<3))
	{i++;
	k++;
	j++;
	};
i=(c-1);
k=(f-1);
while((tablero[k][i]==jugador)&&(i>=0)&&(k>=0)&&(j<3))
	{i--;
	k--;
	j++;
	};
if(j==3)
	victoria=jugador;
//comprobar diagonal descendente 
j=0;
i=(c+1);
k=(f-1);
while((tablero[k][i]==jugador)&&(i<columnas)&&(k>=0)&&(j<3))
	{i++;
	k--;
	j++;
	};
i=(c-1);
k=(f+1);
while((tablero[k][i]==jugador)&&(i>=0)&&(k<filas)&&(j<3))
	{i--;
	k++;
	j++;
	};
if(j==3)
	victoria=jugador;
return victoria;
}

void empezar_partida(char jug1[N], char jug2[N], ficha lista[L])			//Inicia el juego con el tablero y el número de movimientos a 0
{	int tablero[filas][columnas];
	inicializar_tablero(tablero);
	jugar(tablero, 0, jug1, jug2, lista);

}

int comprobar_datos2(char jug[N], ficha lista[L]){		//pide la contraseña de quien jugaba
	char contr[N];
	int exito;
	printf("Usuario: ");
	puts(jug);
	printf("Contraseña:");
	fflush(stdin);
	gets(contr);
	exito=comprobar_contrasena(jug, contr, lista);
	return exito;
}

int comprobar_datos1(char jug1[N], char jug2[N], ficha lista[L]){		//pide las contraseñas de los usuarios que jugaban 
	char contr[N];
	int exito=1;
	printf("Usuario: ");
	puts(jug1);
	printf("Contraseña:");
	fflush(stdin);
	gets(contr);
	fflush(stdin);
	if(comprobar_contrasena(jug1, contr, lista)==0)
		exito=0;
	printf("Usuario: ");
	puts(jug2);
	printf("Contraseña:");
	fflush(stdin);
	gets(contr);
	fflush(stdin);
	if(comprobar_contrasena(jug2, contr, lista)==0)
		exito=0;
	return exito;
}

void seguir_partida(ficha lista[L])						//Reanuda el juego con el tablero y número de movimientos como se haya guardado
{	int tablero[filas][columnas], movimientos,p;
	char jug1[N], jug2[N];
	do{
		printf("¿Que partida desea reanudar?:\n");
		printf("1-Partida 1\n");
		printf("2-Partida 2\n");
		printf("3-Partida 3\n");
		scanf("%d",&p);
	}while(p<1||p>3);
	switch(p){
		case 1:{
			if(recuperar_tablero1(tablero, &movimientos, jug1, jug2)==0){
				printf("No se ha podido recuperar partida\n");
				system("pause");}
			else{
				if(jug2[0]=='L'&&jug2[1]=='u'&&jug2[2]=='i'&&jug2[3]=='\0'){		//comprueba si se estaba jugando con ia
					if(comprobar_datos2(jug1, lista)==1)		//pide las contraseñas del jugador que ha guardado la partida
						jugar_con_lui(tablero, movimientos, jug1, lista);
					else{
						printf("Los datos introducidos no son correctos");
						system("pause");}
				}
				else{
					if(comprobar_datos1(jug1, jug2, lista)==1)		//pide las contraseñas de los jugadores 
						jugar(tablero, movimientos, jug1, jug2, lista);
					else{
						printf("Los datos introducidos no son correctos");
						system("pause");
					}}
			}
			break;
		}
		case 2:{
			if(recuperar_tablero2(tablero, &movimientos, jug1, jug2)==0){
				printf("No se ha podido recuperar partida\n");
				system("pause");}
			else{
				if(jug2[0]=='L'&&jug2[1]=='u'&&jug2[2]=='i'&&jug2[3]=='\0'){
					if(comprobar_datos2(jug1, lista)==1)
						jugar_con_lui(tablero, movimientos, jug1, lista);
					else{
						printf("Los datos introducidos no son correctos");
						system("pause");}
				}
				else{
					if(comprobar_datos1(jug1, jug2, lista)==1)
						jugar(tablero, movimientos, jug1, jug2, lista);
					else{
						printf("Los datos introducidos no son correctos");
						system("pause");
					}}
			}
			break;
		}
			case 3:{
				if(recuperar_tablero3(tablero, &movimientos, jug1, jug2)==0){
				printf("No se ha podido recuperar partida\n");
				system("pause");}
			else{
				if(jug2[0]=='L'&&jug2[1]=='u'&&jug2[2]=='i'&&jug2[3]=='\0'){
					if(comprobar_datos2(jug1, lista)==1)
						jugar_con_lui(tablero, movimientos, jug1, lista);
					else{
						printf("Los datos introducidos no son correctos");
						system("pause");}
				}
				else{
					if(comprobar_datos1(jug1, jug2, lista)==1)
						jugar(tablero, movimientos, jug1, jug2, lista);
					else{
						printf("Los datos introducidos no son correctos");
						system("pause");
					}}
			}
			break;
			}
		}
}



void jugar(int tablero[filas][columnas], int movimientos, char jug1[N], char jug2[N],ficha lista[L]) 
{	int col, fil,p;
	int end=0;
	
	do{											//se sigue jugando siempre que la partida no haya finalizado
		mostrar_tablero(tablero);
		colocar_ficha(movimientos, tablero, &col, &fil);
		if(col!=-1)
			{end=(comprobar_victoria(movimientos, tablero, col, fil));
			movimientos ++;
			}
		if(end==0)
		if(movimientos==(filas*columnas))
			end=3;							//si se han llenado todas las casillas, marca empate siempre que no se acabe de hacer 4 en raya
	}while(end==0&&col!=-1);
	if(end!=0)
	{	mostrar_tablero(tablero);	//al final de la partida se muestra el tablero, el ganador y el número de movimientos
		switch(end)
		{	case 1:{
				printf("\nGana el jugador 1\n");
				system("pause");
				sumar_partida(jug1, lista);
				sumar_partida(jug2, lista);
				sumar_victoria(jug1, lista);
				sumar_derrota(jug2, lista);
				cambiar_record(jug1, lista, movimientos);
			}
			break;
			case 2:{
				printf("\nGana el jugador 2\n");
				system("pause");
				sumar_partida(jug1, lista);
				sumar_partida(jug2, lista);
				sumar_victoria(jug2, lista);
				sumar_derrota(jug1, lista);
				cambiar_record(jug2, lista, movimientos);
			}
			break;
			default:{
				printf("\nEmpate\n");
				system("pause");
				sumar_partida(jug1, lista);
				sumar_partida(jug2, lista);
				sumar_empate(jug1, lista);
				sumar_empate(jug2, lista);
			}
		};
		printf("\nMovimientos: %d\n", movimientos);
	}
	if(col==-1){
		do{
			printf("¿En que partida lo quieres guardar?:\n");
			printf("1-Partida 1\n");
			printf("2-Partida 2\n");
			printf("3-Partida 3\n");
			scanf("%d",&p);
		}while(p<1||p>3);
		switch(p){
			case 1:{
				if(guardar_tablero1(tablero, movimientos, jug1, jug2)==0){
					printf("Lo sentimos, no se ha podido guardar la partida");
					system("pause");}
				break;
			}
			case 2:{
				if(guardar_tablero2(tablero, movimientos, jug1, jug2)==0){
					printf("Lo sentimos, no se ha podido guardar la partida");
					system("pause");}
				break;
			}
			case 3:{
				if(guardar_tablero3(tablero, movimientos, jug1, jug2)==0){
					printf("Lo sentimos, no se ha podido guardar la partida");
					system("pause");}
				break;
			}
		}
		
	}
}

int guardar_tablero1(int tablero[filas][columnas], int movimientos, char jug1[N], char jug2[N])		//guarda en un fichero cada casilla del tablero
{int exito=1, i, j;																					//también guarda el numero de movimientos y usuario de los jugadores
FILE *tab;
tab=fopen("tablero1.txt","wt");
if(tab==NULL)
	exito=0;
else
	{for(i=0;i<filas;i++)
		for(j=0;j<columnas;j++)
			fprintf(tab,"%d ",tablero[i][j]);
	fprintf(tab,"%d ",movimientos);
	fputs(jug1,tab);
	fprintf(tab," ");
	fputs(jug2,tab);
	fprintf(tab," ");
	}
fclose(tab);
return exito;			
}

int guardar_tablero2(int tablero[filas][columnas], int movimientos, char jug1[N], char jug2[N])		//guarda en un fichero cada casilla del tablero
{int exito=1, i, j;																					//también guarda el numero de movimientos y usuario de los jugadores
FILE *tab;
tab=fopen("tablero2.txt","wt");
if(tab==NULL)
	exito=0;
else
	{for(i=0;i<filas;i++)
		for(j=0;j<columnas;j++)
			fprintf(tab,"%d ",tablero[i][j]);
	fprintf(tab,"%d ",movimientos);
	fputs(jug1,tab);
	fprintf(tab," ");
	fputs(jug2,tab);
	fprintf(tab," ");
	}
fclose(tab);
return exito;			
}

int guardar_tablero3(int tablero[filas][columnas], int movimientos, char jug1[N], char jug2[N])		//guarda en un fichero cada casilla del tablero
{int exito=1, i, j;																					//también guarda el numero de movimientos y usuario de los jugadores
FILE *tab;
tab=fopen("tablero3.txt","wt");
if(tab==NULL)
	exito=0;
else
	{for(i=0;i<filas;i++)
		for(j=0;j<columnas;j++)
			fprintf(tab,"%d ",tablero[i][j]);
	fprintf(tab,"%d ",movimientos);
	fputs(jug1,tab);
	fprintf(tab," ");
	fputs(jug2,tab);
	fprintf(tab," ");
	}
fclose(tab);
return exito;			
}

int recuperar_tablero1 (int tablero[filas][columnas], int *movimientos, char jug1[N], char jug2[N])		//crea un nuevo tablero con cada casilla del tablero guardado, también recupera el número de movimientos
{int exito=1, i, j;
char a='a';
FILE *tab;
tab=fopen("tablero1.txt","rt");
if(tab==NULL)
	exito=0;
else
	{for(i=0;i<filas;i++)
		for(j=0;j<columnas;j++)
			fscanf(tab,"%d ",&tablero[i][j]);
	
	fscanf(tab,"%d ",movimientos);
	for(i=0;a!=' ';i++){			//Recoge el nomnbre del primer jugador hasta que se encuentra con el espacio
		fscanf(tab,"%c",&a);
		if(a!=' ')
			jug1[i]=a;
	}
	a='a';
	for(i=0;a!=' ';i++){
		fscanf(tab,"%c",&a);
		if(a!=' ')
			jug2[i]=a;
	}
	}
fclose(tab);
return exito;			
}

int recuperar_tablero2 (int tablero[filas][columnas], int *movimientos, char jug1[N], char jug2[N])		//crea un nuevo tablero con cada casilla del tablero guardado, también recupera el número de movimientos
{int exito=1, i, j;
char a='a';
FILE *tab;
tab=fopen("tablero2.txt","rt");
if(tab==NULL)
	exito=0;
else
	{for(i=0;i<filas;i++)
		for(j=0;j<columnas;j++)
			fscanf(tab,"%d ",&tablero[i][j]);
	
	fscanf(tab,"%d ",movimientos);
	for(i=0;a!=' ';i++){			//Recoge el nomnbre del primer jugador hasta que se encuentra con el espacio
		fscanf(tab,"%c",&a);
		if(a!=' ')
			jug1[i]=a;
	}
	a='a';
	for(i=0;a!=' ';i++){
		fscanf(tab,"%c",&a);
		if(a!=' ')
			jug2[i]=a;
	}
	}
fclose(tab);
return exito;			
}

int recuperar_tablero3 (int tablero[filas][columnas], int *movimientos, char jug1[N], char jug2[N])		//crea un nuevo tablero con cada casilla del tablero guardado, también recupera el número de movimientos
{int exito=1, i, j;
char a='a';
FILE *tab;
tab=fopen("tablero3.txt","rt");
if(tab==NULL)
	exito=0;
else
	{for(i=0;i<filas;i++)
		for(j=0;j<columnas;j++)
			fscanf(tab,"%d ",&tablero[i][j]);
	
	fscanf(tab,"%d ",movimientos);
	for(i=0;a!=' ';i++){			//Recoge el nomnbre del primer jugador hasta que se encuentra con el espacio
		fscanf(tab,"%c",&a);
		if(a!=' ')
			jug1[i]=a;
	}
	a='a';
	for(i=0;a!=' ';i++){
		fscanf(tab,"%c",&a);
		if(a!=' ')
			jug2[i]=a;
	}
	}
fclose(tab);
return exito;			
}

void jugar_con_lui(int tablero[filas][columnas], int movimientos, char jug[N],ficha lista[L])
{	int col, fil, p;
	char lui[N]="Lui";		//Se guarda "Lui" en el segundo jugador para cuando se guarde la partida, poder saber que se estaba jugando con ia
	int end=0;
	do{											//se sigue jugando siempre que la partida no haya finalizado
		mostrar_tablero(tablero);
		colocar_ficha_2(movimientos, tablero, &col, &fil);
		if(col!=-1)
			{
			end=(comprobar_victoria(movimientos, tablero, col, fil));
			movimientos ++;
			}
		if(end==0)
		if(movimientos==(filas*columnas))
			end=3;							//si se han llenado todas las casillas, marca empate siempre que no se acabe de hacer 4 en raya
	}while(end==0&&col!=-1);	
	if(end!=0)
	{
	mostrar_tablero(tablero);	
	switch(end)							//una vez acaba la partida, se muestra el tablero, el ganador y el número de movimientos
	{	case 1:{
			printf("\nEnhorabuena, has ganado\n");
			system("pause");
			sumar_partida(jug, lista);
			sumar_partida(lui, lista);
			sumar_victoria(jug, lista);
			sumar_derrota(lui, lista);
			cambiar_record(jug, lista, movimientos);
		}	
		break;
		case 2:{
			printf("\nLo sentimos, has perdido\n");
			system("pause");
			sumar_partida(jug, lista);
			sumar_partida(lui, lista);
			sumar_victoria(lui, lista);
			sumar_derrota(jug, lista);
			cambiar_record(lui, lista, movimientos);
		}
		break;
		default:{
			printf("\nEmpate\n");
			system("pause");
			sumar_partida(jug, lista);
			sumar_partida(lui, lista);
			sumar_empate(jug, lista);
			sumar_empate(lui, lista);
		}
	};
	printf("\nMovimientos: %d\n",movimientos);
	}
	if(col==-1){
		do{
			printf("¿En que partida lo quieres guardar?:\n");
			printf("1-Partida 1\n");
			printf("2-Partida 2\n");
			printf("3-Partida 3\n");
			scanf("%d",&p);
		}while(p<1||p>3);
		switch(p){
			case 1:{
				if(guardar_tablero1(tablero, movimientos, jug, lui)==0){
					printf("Lo sentimos, no se ha podido guardar la partida");
					system("pause");}
				break;
			}
			case 2:{
				if(guardar_tablero2(tablero, movimientos, jug, lui)==0){
					printf("Lo sentimos, no se ha podido guardar la partida");
					system("pause");}
				break;
			}
			case 3:{
				if(guardar_tablero3(tablero, movimientos, jug, lui)==0){
					printf("Lo sentimos, no se ha podido guardar la partida");
					system("pause");}
				break;
			}
		}
		
	}
}


void empezar_con_lui(char jug1[N],ficha lista[L])			//Inicia el juego con el tablero y el número de movimientos a 0
{	int tablero[filas][columnas];
	inicializar_tablero(tablero);
	jugar_con_lui(tablero, 0, jug1, lista);

}

int elegir_columna(int movimientos, int tablero[filas][columnas]) //Elige la columna en la que Lui va a colocar la ficha
{int c=0, f, colocado=0,i=0;
srand(time(NULL));
sleep(1);
if(movimientos==1){						//Esto es para evitar que, nada más empezar, puedas poner 3 seguidas por el centro, dejando hueco a cada lado y ganar
	if(tablero[filas-1][3]==0)
		c=3;
	else
		c=4;
	colocado=1;
}
while((c<columnas)&&(colocado==0))				//Si hay alguna columna con la que haga cuatro en raya, elige esa columna
	{f=pedir_fila(c,tablero);
	if(comprobar_victoria(movimientos, tablero, c, f)!=0)
		colocado=1;
	if(colocado==0)
		c++;
	};
if(colocado==0)								//Si no, si hay alguna columna con la que el otro jugador vaya a hacer cuatro en raya, elige colocarla en esa para evitarlo
	{c=0;
	while((c<columnas)&&(colocado==0))
		{f=pedir_fila(c,tablero);
		if(comprobar_victoria(movimientos+1, tablero, c, f)!=0)
			colocado=1;
		if(colocado==0)
			c++;
		}
	}
while(colocado==0&&i<1000)						//Si no ha elegido ya, elige una columna aleatoria siempre que no permita al otro jugador ganar por colocarla en ella
	{c=rand()%columnas;
	f=pedir_fila(c,tablero);
	if(comprobar_victoria((movimientos+1),tablero,c,(f+1))==0)
	colocado=1;
	i++;							//Se le pone un contador para evitar que se quede encerrado en el bucle si no tiene más opciones
	}
;
return c;
}


void colocar_ficha_2(int movimientos, int tablero[filas][columnas], int *col, int *fil) //Coloca una ficha que elige el jugador o el programa, según a quien le toque
{if(movimientos%2==0)
	*col=pedir_columna(movimientos, tablero);
else
	*col=elegir_columna(movimientos, tablero);
if((*col)!=-1)									//Siempre que no se haya pedido guardar partida
	{
	*fil=pedir_fila(*col, tablero);	
	tablero[*fil][*col]=(movimientos%2+1);		//En la casilla que le dan, pone la ficha del jugador que toca
	}
}

void registrar_usuario(char usuario[N], char contras[N], ficha lista[L], int*n){	
	int i;
	for(i=0;i<N;i++){
		lista[*n].usuario[i]=usuario[i];		//*n es el primer sitio vacío en el vector de la estructura
		lista[*n].contras[i]=contras[i];		//guarda en la estructura los datos
	}								
	lista[*n].partidas=0;						//se inicializan las partidas, victorias, derrotas y empates a 0
	lista[*n].victorias=0;						//y el record de movimientos al máximo posible
	lista[*n].record=filas*columnas;
	lista[*n].derrotas=0;						
	lista[*n].empates=0;
}

int comprobar_usuario(char usuario[N], ficha lista[L], int n){		//comprueba si existe el usuario
	int i, j, existe=0;
	for(j=0;j<n&&existe==0;j++){
		existe=1;
		for(i=0;usuario[i]!='\0'&&lista[j].usuario[i]!='\0';i++)
			if(lista[j].usuario[i]!=usuario[i])
				existe=0;
	}
	return existe;
}


int comprobar_contrasena(char usuario[N], char contr[N], ficha lista[L]){		//comprueba que la contraseña coincida con la del usuario
	int correcta=1,usu=0 ,i, j;
	for(j=0;usu==0&&j<L;j++){		 				//coge la estructura del vector que tiene ese usuario
		usu=1;										//La condición j<L es por si se ha guardado el tablero con un jugador nuevo y se ha cerrado el programa sin guardar la nueva estructura en el fichero
		for(i=0;lista[j].usuario[i]!='\0'||usuario[i]!='\0';i++)
			if(lista[j].usuario[i]!=usuario[i])
				usu=0;
	}
	j--;
	for(i=0;lista[j].contras[i]!='\0'||contr[i]!='\0';i++)		//comprueba que coincida la contraseña con la de la estructura
			if(lista[j].contras[i]!=contr[i])
				correcta=0;
	return correcta;
}


void dos_jugadores(char jug1[N], char jug2[N], int *n, ficha lista[L]){		//prepara para iniciar una partida con dos jugadores
	char contr[N];
	int i, iguales;
	do{
		printf("Jugador 1:\nNombre de usuario:\n");			//pide el usuario y contraseña del jugador
		gets(jug1);
		fflush(stdin);
		printf("Contraseña:\n");
		gets(contr);
		fflush(stdin);
	}while(datos_jugador(jug1,contr, n, lista)==0);			//mientras los datos sean incorrectos(no coincidan usuario y contraseña
	do{
		do{
			printf("Jugador 2:\nNombre de usuario:\n");		
			gets(jug2);
			fflush(stdin);
			iguales=1;
			for(i=0;jug2[i]!='\0'&&jug1!='\0';i++)		//comprueba si ambos jugadores son iguales
				if(jug1[i]!=jug2[i])
					iguales=0;
			if(iguales==1)
				printf("Los usuarios no pueden ser iguales\n");
		}while(iguales==1);
		printf("Contraseña:\n");
		gets(contr);
		fflush(stdin);
	}while(datos_jugador(jug2,contr, n, lista)==0);
}

int datos_jugador(char usuario[N], char contr[N], int *n, ficha lista[L]){		
	int hecho=0;
	if(comprobar_usuario(usuario, lista, *n)==0){						///comprueba si existe el usuario, en caso contrario lo registra
		printf("Usuario nuevo, lo registraremos con la contraseña utilizada\n");
		system("pause");
		registrar_usuario(usuario, contr, lista, n);
		(*n)++;
		hecho=1;
	}
	else
		if(comprobar_contrasena(usuario,contr, lista)==0)			//en caso afirmativo, comprueba que coincida la contraseña
			printf("Datos incorrectos\n");
		else
			hecho=1;
	return hecho;
}

void un_jugador(char jug[N], int *n, ficha lista[L]){		//prepara lo necesario para jugar contra Lui
	char contr[N];
	char lui[N]="Lui";
	int i;
	if(comprobar_usuario(lui, lista, *n)==0){						//Registra también a Lui si no existe, para que los jugadores puedan competir con él en el ránking
		registrar_usuario(lui, "T_D_Lemon", lista, n);
		(*n)++;
	}
	do{
		printf("Nombre de usuario:\n");				//pide los datos
		gets(jug);
		fflush(stdin);
		printf("Contraseña:\n");
		gets(contr);
		fflush(stdin);
	}while(datos_jugador(jug,contr, n, lista)==0);		//mientras sean incorrectos(la contraseña no coincida)
}

int leer_ranking(ficha lista[L]){		//descarga los datos guardados en un fichero en el vector de estructuras 
	FILE *pf;
	pf=fopen("Usuarios.txt","ab");		//por si no existe
	fclose(pf);
	int  i=0;
	pf=fopen("Usuarios.txt","rb");	
	if(pf==NULL)
		printf("Ha habido un error\n");
	else{
		for(i=0;(!feof(pf));i++){
			fread(&lista[i].usuario,sizeof(char),N,pf);
			fread(&lista[i].contras,sizeof(char),N,pf);
			fread(&lista[i].partidas,sizeof(int),1,pf);
			fread(&lista[i].victorias,sizeof(int),1,pf);
			fread(&lista[i].record,sizeof(int),1,pf);
			fread(&lista[i].derrotas,sizeof(int),1,pf);
			fread(&lista[i].empates,sizeof(int),1,pf);
		}	
	}
	fclose(pf);
	return i-1;
}

void imprimir_ranking(ficha lista[L], int l){		//imprime en pantalla los resultados de cada jugador, sacados del vector de estructuras
int i;												//l es la longitud que se ha llenado del vector de estructuras
for(i=0;i<l;i++){
		puts(lista[i].usuario);
		printf("Partidas: %d\n",lista[i].partidas);
		printf("Victorias: %d\n",lista[i].victorias);
		printf("Derrotas: %d\n",lista[i].derrotas);
		printf("Empates: %d\n",lista[i].empates);
		printf("Record de movimientos en una victoria: %d\n\n",lista[i].record);
}}

void sumar_partida(char jugador[N], ficha lista[L]){	//le suma uno al número de partidas del usuario dado
	int i, j, encontrado=0;
	for(i=0;encontrado==0;i++){			//busca qué estructura hay que modificar
		encontrado=1;
		for(j=0;jugador[j]!='\0'&&lista[i].usuario[j]!='\0';j++)
				if(jugador[j]!=(lista[i].usuario[j]))
					encontrado=0;
	}
	lista[i-1].partidas++;
}

void sumar_victoria(char jugador[N], ficha lista[L]){		//le suma uno al número de victorias del usuario dado
	int i, j, encontrado=0;
	for(i=0;encontrado==0;i++){						//busca qué estructura hay que modificar
		encontrado=1;
		for(j=0;jugador[j]!='\0'&&lista[i].usuario[j]!='\0';j++)
				if(jugador[j]!=(lista[i].usuario[j]))
					encontrado=0;
	}
	lista[i-1].victorias++;
}

void sumar_derrota(char jugador[N], ficha lista[L]){		//le suma uno al número de derrotas del usuario dado
	int i, j, encontrado=0;
	for(i=0;encontrado==0;i++){						//busca qué estructura hay que modificar
		encontrado=1;
		for(j=0;jugador[j]!='\0'&&lista[i].usuario[j]!='\0';j++)
				if(jugador[j]!=(lista[i].usuario[j]))
					encontrado=0;
	}
	lista[i-1].derrotas++;
}

void sumar_empate(char jugador[N], ficha lista[L]){		//le suma uno al número de empates del usuario dado
	int i, j, encontrado=0;
	for(i=0;encontrado==0;i++){						//busca qué estructura hay que modificar
		encontrado=1;
		for(j=0;jugador[j]!='\0'&&lista[i].usuario[j]!='\0';j++)
				if(jugador[j]!=(lista[i].usuario[j]))
					encontrado=0;
	}
	lista[i-1].empates++;
}

void cambiar_record(char jugador[N], ficha lista[L], int mov){		//si el numero de movimientos de la partida es menor al récord, lo sustituye
	int i, j, encontrado=0;
	for(i=0;encontrado==0;i++){		//busca qué estructura hay que modificar
		encontrado=1;
		for(j=0;jugador[j]!='\0'&&lista[i].usuario[j]!='\0';j++)
				if(jugador[j]!=(lista[i].usuario[j]))
					encontrado=0;
	}
	if(mov<lista[i-1].record)
		lista[i-1].record=mov;	
}

void guardar_todo(ficha lista[L], int n){		//guarda los datos del vector de estructuras en un fichero
	FILE *pf;									//n es el numero de usuarios registradas
	int  i;
	pf=fopen("Usuarios.txt","wb");	
	if(pf==NULL)
		printf("No se han podido guardar los nuevos datos\n");
	else{
		for(i=0;i<n;i++){
			
			fwrite(lista[i].usuario,sizeof(char),N,pf);
			fwrite(&lista[i].contras,sizeof(char),N,pf);
			fwrite(&lista[i].partidas,sizeof(int),1,pf);
			fwrite(&lista[i].victorias,sizeof(int),1,pf);
			fwrite(&lista[i].record,sizeof(int),1,pf);
			fwrite(&lista[i].derrotas,sizeof(int),1,pf);
			fwrite(&lista[i].empates,sizeof(int),1,pf);
			
		}	
	}
	fclose(pf);
		
	}


void main()
{
	int opcion;
	char a, jug1[N], jug2[N];
	ficha lista[L];
	int  n;
	n=leer_ranking(lista);
	do{
		system("cls");
		printf("Elija la opción que desee:\n\n1-Iniciar nueva partida\n2-Reanudar partida\n3-Ver la clasificación\n4-Guardar y salir\n");
		scanf("%d",&opcion);
		fflush(stdin);
		switch(opcion){
			case 1:{
				do{
					printf("¿Desea jugar contra Lui?(s/n)");
					scanf("%c",&a);
					fflush(stdin);
				}while(a!='s'&&a!='n'&&a!='S'&&a!='N');
				if(a=='s'||a=='S'){
					un_jugador(jug1, &n, lista);
					empezar_con_lui(jug1, lista);
				}
				else{
					dos_jugadores(jug1, jug2, &n, lista);
					empezar_partida(jug1,jug2, lista);
				}
				break;
			}
			case 2:{
				seguir_partida(lista);
				break;
			}
			case 3:{
				ordenar_ranking(lista,n);
				imprimir_ranking(lista, n);
				system("pause");
				break;
			}
		}
		
	}while(opcion!=4);
	guardar_todo(lista, n);
}
