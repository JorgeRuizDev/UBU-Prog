/*
	Nombre: Práctica Final programación 1 UBU 2019
	
	Descripción:Analizador de fichero de cáncer de mama https://archive.ics.uci.edu/ml/datasets/Breast+Cancer
		Permite mediante un selector de teclado, ver, modificar, y analizar los distintos aspectos del fichero en cuestión
	Autor: Jorge Ruiz Gómez
	Fecha inicio 10/04/2019
	Fecha final 19/05/2019
	
	Compilado mediante GCC estándar, no es necesario enlazar otras librerias
	o incluir más archivos en la carpeta de compilado
	
	Programado mediante Notepad++ Windows y la utilidad WSL1 
	WSL1(Windows Subsystem for Linux Versión 1 // V. W10 LSTC 2019, utilizado el compilador GCC)
*/

//------------------------------------------------------------------------------
//Definición de directivas de preprocesador
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
//Constantes
//Edad
#define EDAD1 "10-19"
#define EDAD2 "20-29"
#define EDAD3 "30-39"
#define EDAD4 "40-49"
#define EDAD5 "50-59"
#define EDAD6 "60-69"
#define EDAD7 "70-79"

//Tamaño tumor (string extraido del archivo)
#define TAM1 "0-4"
#define TAM2 "5-9"
#define TAM3 "10-14"
#define TAM4 "15-19"
#define TAM5 "20-24"
#define TAM6 "25-29"
#define TAM7 "30-34"
#define TAM8 "35-39"
#define TAM9 "40-44"
#define TAM10 "45-49"
#define TAM11 "50-54"
#define TAM12 "55-59"

//Definimos un tamaño máximo para el vector
//Otra forma sería calculando el número de líenas del archivo, y usar ese número como el tamaño del vector
//es más dinámico, pero a la vez necesita de más tiempo de ejecución
#define MAX 500

//estructuras-----------------------


struct cancer{
		char clase[23];
		char edad[6];
		char menopausia[10];
		char tamanoTumor[6];
		char nodos[6];
		char nodeCaps[4];
		int grado;
		char seno[6];
		char zona[10];
		char irradiado[4];	
};

typedef struct cancer CANCER;
//----------------------------------




//Definición de prototipos
//Funciones primarias

	//Selector Inicial
int solicitarOpcionMenu ();
void seleccionarOpcion (int);
	//Contador
int contarCaracteres (FILE *) ;
	//Mostrar relación tamaño/edad
void distribuirTamanos (FILE *);
	//Insertar Fila
void insertarFila (FILE *);
	//Struct
int cargarRegistros(CANCER [],FILE *);
	//Eliminar Filas
void eliminarFilas(FILE *);
	//Archivo binario
void actualizarTamanoMedio(FILE *);
int calcularTamanoMedio(CANCER [],FILE *,int);
void escribirBinario (CANCER [],int , FILE *);

//Funciones secundarias
void cleanStdin ();
int selectorNumerico(int min, int max);
int fedad ();
int numeroFilas (FILE *);


//------------------------------------------------------------------------------

int main (){
	int menu;
	
	for(int a=0;a<10;a--){//Bucle infinito para que siempre retorne este menú
	menu = solicitarOpcionMenu ();
	seleccionarOpcion (menu);
	}
	return 0;
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

void cleanStdin (){
	/*Clean stdin (standar Input) nos permite limpiar la entrada 
	en caso de que introduzcamos dos valores en un mismo scnaf(integer+char)*/
	
	printf("Entrada de datos no válida\n");
	while (getchar () != '\n');	
}

//-------------------------------------------------------------------------------------

int solicitarOpcionMenu () {
	
	int seleccion;
	char enter;
	bool verificarEntrada;
	
	do {
		printf("\n\n--------------------------------------------------\n");
		printf ("1) Mostrar el total de caracteres del fichero\n");
		printf ("2) Mostrar la relacón edad/tamaño del tumor\n");
		printf ("3) Introducir nuevos datos al archivo\n");
		printf ("4) Eliminar Filas repetidas\n");
		printf ("5) Imprimir los pacientes de riesgo\n");
		printf ("6) Salir\n");
		printf("--------------------------------------------------\n");
		int leidos = scanf ("%d%c",&seleccion, &enter);
		
		if ((leidos !=2) | (seleccion>6) | (seleccion <1) | (enter != '\n')){
			verificarEntrada = false;
			cleanStdin ();
			}

		else
			verificarEntrada = true;

	}while (verificarEntrada == false);
	return seleccion;
}

//-------------------------------------------------------------------------------------

void seleccionarOpcion (int opcion) {

	FILE *pArchivo;

	//Abrimos y cerramos el archivo en cada SWITCH
	switch (opcion){
		
		case 1:
		pArchivo = fopen ("./breast-cancer.txt","a+");			
		if (pArchivo == NULL){
			
			printf("No se han leer crear el archivo\n");
			printf("Compruebe que la carpeta sobre la que está trabajando tiene los permisos adecuados\n");
			printf("Deteniendo la ejecución...\n");
			
		exit (0);
		}
		
		contarCaracteres(pArchivo);
		fclose(pArchivo);
		break;
		
		case 2:
		pArchivo = fopen ("./breast-cancer.txt","a+");			
		if (pArchivo == NULL){
			
			printf("No se han leer crear el archivo\n");
			printf("Compruebe que la carpeta sobre la que está trabajando tiene los permisos adecuados\n");
			printf("Deteniendo la ejecución...\n");
			
		exit (0);
		}		
		distribuirTamanos(pArchivo);
		fclose(pArchivo);
		break;
		
		case 3:
		pArchivo = fopen ("./breast-cancer.txt","a+");			
		if (pArchivo == NULL){
			
			printf("No se han leer crear el archivo\n");
			printf("Compruebe que la carpeta sobre la que está trabajando tiene los permisos adecuados\n");
			printf("Deteniendo la ejecución...\n");
			
		exit (0);
		}		
		insertarFila (pArchivo);
		fclose(pArchivo);
		break;
		
		case 4:
		pArchivo = fopen ("./breast-cancer.txt","a+");			
		if (pArchivo == NULL){
			
			printf("No se han leer crear el archivo\n");
			printf("Compruebe que la carpeta sobre la que está trabajando tiene los permisos adecuados\n");
			printf("Deteniendo la ejecución...\n");
			
		exit (0);
		}
		eliminarFilas(pArchivo);
		fclose(pArchivo);
		break;
		
		case 5:
		pArchivo = fopen ("./breast-cancer.txt","a+");			
		if (pArchivo == NULL){
			
			printf("No se han leer crear el archivo\n");
			printf("Compruebe que la carpeta sobre la que está trabajando tiene los permisos adecuados\n");
			printf("Deteniendo la ejecución...\n");
			
		exit (0);
		}
		//Realiza un nuevo fichero binario según el riesgo
		actualizarTamanoMedio(pArchivo);
		fclose(pArchivo);
		break;
		
		case 6:
		printf("Saliendo...\n");
		exit (0);
		break;
		
		default:
		printf("Error catastrófico a la hora de seleccionar opción\n");
		exit(0);
		break;
	}
	
	printf("\n\nPulse [ENTER] para continuar...");
	getchar();
	
	
	
} 

//-------------------------------------------------------------------------------------

int contarCaracteres (FILE *fp ) {
	
	int nCaracteres=0;

		char c = fgetc(fp); 
		
		//!feof--Ejecutar el bucle hasta que se llegue al final del archivo
		while (!feof (fp)) {
			c = fgetc(fp); 
			nCaracteres++;
		}
		fclose(fp);
		
	printf("El número de caracteres que contiene el fichero es %d\n",nCaracteres);

	return nCaracteres;
} 
//-------------------------------------------------------------------------------------
void distribuirTamanos (FILE *fp){
		
		char edad[6];
		char tamano[6];
		int nPacientes = 0, nPacientesAfectados = 0;//pacientes= Número de pacientes; PacientesAfectados = número de pacientes de la edad escogida
		int nTam1=0, nTam2=0, nTam3=0, nTam4=0, nTam5=0, nTam6=0, nTam7=0, nTam8=0, nTam9=0, nTam10=0, nTam11=0, nTam12=0;
		
		//Selector de edad
		//Hemos creado una función dedicada a escoger una edad
		int edadComparar = fedad();
		char edadEntrada[6];

		
		switch(edadComparar){//Este switch añade a una variable la edad en forma de STRING para poder compararla
			//EDAD1 "10-19"
			case 1:
			strcpy(edadEntrada,EDAD1);

			break;
			
			//EDAD2 "20-29"
			case 2:
			strcpy(edadEntrada,EDAD2);
						
			break;
			
			//EDAD3 "30-39"
			case 3:
			strcpy(edadEntrada,EDAD3);
					
			break;
			
			//EDAD4 "40-49"
			case 4:
			strcpy(edadEntrada,EDAD4);
						
			break;
						
			//EDAD5 "50-59"
			case 5:
			strcpy(edadEntrada,EDAD5);			
						
			break;
			
			//EDAD6 "60-69"
			case 6:
			strcpy(edadEntrada,EDAD6);
						
			break;
			
			//EDAD7 "70-79"
			case 7:
			strcpy(edadEntrada,EDAD7);
						
			break;
			
			default:
			printf("Error catastrófico en el switch edadComparar\n");
		}



	
		while(fscanf(fp, "%*[^,],%[^,],%*[^,],%[^,],%*[^\n]",edad,tamano)!=EOF){	
		
		//Debug que muestra/imprime el tamaño y la edad
		//printf("Edad: %s\ntamano: %s\n",edad,tamano); 
		
		nPacientes++; //Contador del número de pacientes


		
//If que se encargar de contar el tamaño del tumor si la edad introducida coincide.
	if(strcmp(edad,edadEntrada)==0){
		//árbol para contar el tamaño de cada tumor
		
		nPacientesAfectados++;
		
		if(strcmp (tamano, TAM1)==0)
			nTam1++;
		else if(strcmp (tamano, TAM2)==0)
			nTam2++;
		else if(strcmp (tamano, TAM3)==0)
			nTam3++;
		else if(strcmp (tamano, TAM4)==0)
			nTam4++;
		else if(strcmp (tamano, TAM5)==0)
			nTam5++;		
		else if(strcmp (tamano, TAM6)==0)
			nTam6++;
		else if(strcmp (tamano, TAM7)==0)
			nTam7++;
		else if(strcmp (tamano, TAM8)==0)
			nTam8++;
		else if(strcmp (tamano, TAM9)==0)
			nTam9++;		
		else if(strcmp (tamano, TAM10)==0)
			nTam10++;
		else if(strcmp (tamano, TAM11)==0)
			nTam11++;
		else if(strcmp (tamano, TAM12)==0)
			nTam12++;
		else
			printf("No coincide el tamaño %s con ninguno de la lista\n",tamano);
		//Fin arbol TamañoTumor	
		}
		
	}	//fin while
	
	
	
	//Salida de datos
		printf("\n--------Grupo %s-------\n",edadEntrada);
		printf("Distribución del tamaño de los tumores en las edades comprendidas entre %s\n",edadEntrada);
		printf("Número total de muestras: %d\n",nPacientes);
		printf("Número de pacientes cuya edad está comprendida ente %s: %d\n",edadEntrada, nPacientesAfectados);
		printf("\n-----------------------------------------------\n");
		printf("   Tamaño     Casos     -%%-\n");
		
		printf("\n    %-11s%2d      %.3f%%\n",TAM1,nTam1,((float)nTam1/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM2,nTam2,((float)nTam2/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM3,nTam3,((float)nTam3/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM4,nTam4,((float)nTam4/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM5,nTam5,((float)nTam5/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM6,nTam6,((float)nTam6/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM7,nTam7,((float)nTam7/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM7,nTam7,((float)nTam7/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM8,nTam8,((float)nTam8/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM9,nTam9,((float)nTam9/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM10,nTam10,((float)nTam10/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM11,nTam11,((float)nTam11/nPacientesAfectados*100));
		printf("\n    %-11s%2d      %.3f%%\n",TAM12,nTam12,((float)nTam12/nPacientesAfectados*100));
		
		/*Se ha verificado que la salida de datos es correcta con el comando $ grep*/
	}

//-------------------------------------------------------------------------------------

int fedad (){
	/*Función para introducir la edad, y convertirla en una posición del 1-10*/
	int edad;
	bool validacionBool;
	
	
	printf("Introduzca un rango de edades\n");
	printf("1) %s\n2) %s \n3) %s \n4) %s\n5) %s\n6) %s\n7) %s\n",EDAD1,EDAD2,EDAD3,EDAD4,EDAD5,EDAD6,EDAD7);
	
	do{
		printf("---> ");
	scanf("%d",&edad);
	if(edad<1 || edad >7){
		cleanStdin();
		validacionBool = false;
	}
	else
		validacionBool = true;
	}while (validacionBool==false);
	
	return edad;
}


void insertarFila (FILE *pArchivo){

	//arrays de caracteres a imprimir
	char clase[23],edad[6], menopausia[10],tamanoTumor[6],nodos[6],nodeCaps[4],seno[6],zona[10],irradiado[4];
	int numeroFilas = 0, numeroFilasTotales =0 ;
	bool bucleAnadirFila = true;
	
	
	    for (char c = getc(pArchivo); c != EOF; c = getc(pArchivo)) {
		if (c == '\n') 
			numeroFilasTotales++;
		}

	/*
	El funcionamiento de esta funcion es el de:
	1º- Un selector que permita escoger en un switch/case una sentencia
	2º- Las variables en blanco sobre las que vamos a introducir los datos a copiar
	3º- Un strcpy en cada switch/case que copie el valor mostrado en los printf, a la variable en blaco
	4º. Un fprintf que imprima las variables con los datos ya introducidos
	
	Otra manera:
		Este código se puede hacer más compacto pero menos legible
		usando un array que contenga en cada posición el string a copiar
		Luego con un selector (1-x), podemos escoger esa posición (restando una unidad, de 0-(x-1))
		Y luego haciendo un strcpy del array en la posición escogida, a la variable en blaco.
	
		Este método se utilizará más adelante, en la función de actualizar registros.
	*/
	
do{	
	//clase
	printf("Clase:\n1) no-recurrence-events \n2) recurrence-events\n");
	int sClase = selectorNumerico(1,2);
	
	switch (sClase){
		case 1:
		strcpy (clase,"no-recurrence-events");
		break;
		case 2:
		strcpy (clase,"recurrence-events");
		break;
		default:
		printf("Error catastrófico, deteniendo la ejecución...\n");
		exit(0);
		break;
	}
	
	//edad
	//reutlizamos los selectores y switches de edad
	int sEdad=fedad();
	
	switch(sEdad){//Este switch añade a una variable la edad en forma de STRING para poder añadirla
			//EDAD1 "10-19"
			case 1:
			strcpy(edad,EDAD1);

			break;
			
			//EDAD2 "20-29"
			case 2:
			strcpy(edad,EDAD2);
						
			break;
			
			//EDAD3 "30-39"
			case 3:
			strcpy(edad,EDAD3);
					
			break;
			
			//EDAD4 "40-49"
			case 4:
			strcpy(edad,EDAD4);
						
			break;
			
						
			//EDAD5 "50-59"
			case 5:
			strcpy(edad,EDAD5);			
						
			break;
			
			//EDAD6 "60-69"
			case 6:
			strcpy(edad,EDAD6);
						
			break;
			
			//EDAD7 "70-79"
			case 7:
			strcpy(edad,EDAD7);
						
			break;
			
			default:
			printf("Error catastrófico, deteniendo la ejecución...\n");
			exit (0);
			break;
		}
		
			
	//Tipo de menopausia
		printf("Tipo de menopausia\n");
		printf("1) lt40\n2) ge40 \n3) premeno\n");
		int sMenopausia = selectorNumerico (1,3);
		
		switch (sMenopausia){
		case 1:
		strcpy (menopausia,"lt40");
		break;
		case 2:
		strcpy (menopausia,"ge40");
		break;
		case 3:
		strcpy (menopausia,"premeno");
		break;
		default:
		printf("Error catastrófico, deteniendo la ejecución...\n");
		exit(0);
		break;
	}
	
	//tamaño
		printf("1)0-4 \n2) 5-9\n3) 10-14\n4) 15-19\n5) 20-24\n6) 25-29\n7) 30-34\n8) 35-39\n9) 40-44\n10) 45-49\n11) 50-54\n12) 55-59\n");
		int sTamanio = selectorNumerico(1,12);
		
		switch (sTamanio){
			case 1:
			strcpy (tamanoTumor,"0-4");
			break;
			case 2:
			strcpy (tamanoTumor,"5-9");
			break;
			case 3:
			strcpy (tamanoTumor,"10-14");
			break;
			case 4:
			strcpy (tamanoTumor,"15-19");
			break;
			case 5:
			strcpy (tamanoTumor,"20-24");
			break;
			case 6:
			strcpy (tamanoTumor,"25-29");
			break;
			case 7:
			strcpy (tamanoTumor,"30-34");
			break;
			case 8:
			strcpy (tamanoTumor,"35-39");
			break;
			case 9:
			strcpy (tamanoTumor,"40-44");
			break;
			case 10:
			strcpy (tamanoTumor,"45-49");
			break;
			case 11:
			strcpy (tamanoTumor,"50-54");
			break;
			case 12:
			strcpy (tamanoTumor,"55-59");
			break;
			default:
			printf("Error catastrófico, deteniendo la ejecución...\n");
			exit(0);				
		}
		
		//Nodes
		printf("Introduzca en número de inv-nodes\n");
		printf("1)0-2\n2) 3-5\n3) 6-8\n4) 9-11\n5) 12-14\n6) 15-17\n7) 18-20\n8) 21-23\n9) 24-26\n10) 27-29\n11) 30-32\n12) 33-35\n13) 36-39\n");
		
		int sNodos = selectorNumerico (1,13);
		
		switch (sNodos){
			case 1:
			strcpy (nodos,"0-2");
			break;
			case 2:
			strcpy (nodos,"3-5");
			break;
			case 3:
			strcpy (nodos,"6-8");
			break;
			case 4:
			strcpy (nodos,"9-11");
			break;
			case 5:
			strcpy (nodos,"12-14");
			break;
			case 6:
			strcpy (nodos,"15-17");
			break;
			case 7:
			strcpy (nodos,"18-20");
			break;
			case 8:
			strcpy (nodos,"21-23");
			break;
			case 9:
			strcpy (nodos,"24-26");
			break;
			case 10:
			strcpy (nodos,"27-29");
			break;
			case 11:
			strcpy (nodos,"30-32");
			break;
			case 12:
			strcpy (nodos,"33-35");
			break;
			case 13:
			strcpy (nodos,"36-39");
			break;
			default:
			printf("Error catastrófico, deteniendo la ejecución...\n");
			exit(0);
			break;			
		}
		
		//node caps	
		printf("Node Caps\n1) yes\n2) no \n3) desconocido (?)\n");
		int sCaps = selectorNumerico(1,3);
		
		switch(sCaps){
			case 1:
			strcpy (nodeCaps,"yes");
			break;
			case 2:
			strcpy (nodeCaps,"no");
			break;
			case 3:
			strcpy (nodeCaps,"?");
			break;
			default:
			printf("Error catastrófico, deteniendo la ejecución...\n");
			exit(0);
			break;					
		}
		
		//Grado Maligno
		printf("Grado maligno\n1) Grado 1\n2) Grado 2 \n3) Grado 3");
		int sGrado = selectorNumerico(1,3);
		
		//seno
		printf("Seno:\n1) left\n2) right\n");
		int sSeno = selectorNumerico (1,2);
		
		switch(sSeno){
			case 1:
			strcpy (seno,"left");
			break;
			case 2:
			strcpy (seno,"right");
			break;
			default:
			printf("Error catastrófico, deteniendo la ejecución...\n");
			exit(0);
			break;					
		}
		
		//zona
		printf("Zona: \n1) left-up\n2) left-low\n3) right-up\n4) right-low\n5) central\n");
		int sZona = selectorNumerico(1,5);
		
		switch (sZona){
			case 1:
			strcpy (zona,"left-up");
			break;
			case 2:
			strcpy (zona,"left-low");
			break;
			case 3:
			strcpy (zona,"right-up");
			break;
			case 4:
			strcpy (zona,"right-low");
			break;
			case 5:
			strcpy (zona,"central");
			break;
			default:
			printf("Error catastrófico, deteniendo la ejecución...\n");
			exit(0);
			break;
		}
		
		//Irradiado
		printf("Irradiat\n1) yes\n2) no\n3) Desconocido (?)\n");
		int sIrradiado = selectorNumerico (1,3);
		
		switch (sIrradiado){
			case 1:
			strcpy (irradiado,"yes");
			break;
			case 2:
			strcpy (irradiado,"no");
			break;
			case 3:
			strcpy (irradiado,"?");
			break;
			default:
			printf("Error catastrófico, deteniendo la ejecución...\n");
			exit(0);
			break;
		}
		//continuar
		printf("¿Desea introducir otro caso?\n introduzca n para parar\n");
		int continuarentrada;
		scanf("%lc",&continuarentrada);
		
		if(continuarentrada == 'n')
			bucleAnadirFila =false;
		
		
		numeroFilas++;
		
		//escribir en el archivo:
		fprintf(pArchivo,"%s,%s,%s,%s,%s,%s,%d,%s,%s,%s\n",clase,edad, menopausia,tamanoTumor,nodos,nodeCaps,sGrado,seno,zona,irradiado);
		//clase[23],edad[6], menopausia[10],tamanoTumor[6],nodos[6],nodeCaps[4],seno[6],zona[10],irradiado[4]
	}while (bucleAnadirFila == true);	
	
	
	printf("Fin de la ejecución\nNúmero de líneas añadidas %d\nNúmero de líneas totales %d\n",numeroFilas,numeroFilas+numeroFilasTotales);
}
int selectorNumerico(int min, int max){

	//El selector devuelve un valor validado para ser usado en un SWITCH (u otros)
	//Se introduce el intervalo de valores aceptados, y permite devolver un valor
	int num;
	char enter;
	bool validacionBool;
	do{
		printf("---> ");
		int numDatosIntro = scanf("%d%c",&num,&enter);
		
		if(numDatosIntro != 2 || enter != '\n' || num>max || num<min){
			validacionBool=false;
			cleanStdin();
		}
		else
			validacionBool = true;
			
	}while (validacionBool==false);
		
	return num;	 
}


int cargarRegistros(CANCER vector[],FILE *pArchivo){
	

	int fmax=0;	//Variable sobre la que vamos a añadir al array todo el archivo, además de contar las líneas.
	
	printf("Cargando registros...\n");
	
	while(fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]",vector[fmax].clase,vector[fmax].edad,vector[fmax].menopausia,vector[fmax].tamanoTumor,vector[fmax].nodos,vector[fmax].nodeCaps,&vector[fmax].grado,vector[fmax].seno,vector[fmax].zona,vector[fmax].irradiado)==10){
	
		//Debug para imprimir todo lo leido:	
	/*
	printf("%s,",vector[fmax].clase);		
	printf("%s,",vector[fmax].edad);	
	printf("%s,",vector[fmax].menopausia);
	printf("%s,",vector[fmax].tamanoTumor);
	printf("%s,",vector[fmax].nodos);
	printf("%s,",vector[fmax].nodeCaps);
	printf("%d,",vector[fmax].grado);
	printf("%s,",vector[fmax].seno);
	printf("%s,",vector[fmax].zona);
	printf("%s",vector[fmax].irradiado);
	*/
	fmax++;	
	}

	return fmax;
}

//-----------------------------------------------------------------------------

void eliminarFilas(FILE *pArchivo){
	
	//Abrimos un archivo en blanco (lectura + escritura)
	FILE *pImprimir;
	pImprimir = fopen("./breast-cancer-no-duplicates.txt","w+");
	if (pImprimir==NULL){
		
		printf("No se han podido crear el archivo\n");
		printf("Compruebe que la carpeta sobre la que está trabajando tiene los permisos adecuados\n");
		printf("Deteniendo la ejecución...\n");
		
		fclose (pImprimir);
		exit(0);
	}
	//--------------------

	//Cargamos el vector de registros
	CANCER vector[MAX];			//Reservamos un espacio en memoria para el vector de registros.
	
	//Cargamos el vector de registros al vector
	int nLineas = cargarRegistros(vector,pArchivo);
	printf("Se han leído %d líneas\n",nLineas);
	
	//Definimos un contador para el número de veces que se encuentra una línea igual
	int nIguales=0;

	
	//Definimos una variable de tipo booleana para ejecutar o no  el segundo FOR
	//También lo usamos para comprobar si escribimos esa posición del array o no en el archivo
	bool repetidas = false;

	//Realizamos dos FOR, y nos encargamos de comparar los distintos valores del vector, si no coinciden escribimos la línea A	
	for(int a=0;a<=nLineas; a++){
		
		//b=a+1 para evitar que coincida la misma línea
		for (int b=a+1; b<nLineas && repetidas==false; b++){
			int contador=0;		//Realizamos, si el valor del contador es ig
			if(contador==0 && strcmp(vector[a].clase,vector[b].clase)==0){
				contador++;
			}
			if(contador==1 && strcmp(vector[a].edad,vector[b].edad)==0){
				contador++;
			}			
			if(contador==2 && strcmp(vector[a].menopausia,vector[b].menopausia)==0){
				contador++;
			}			
			if(contador==3 && strcmp(vector[a].tamanoTumor,vector[b].tamanoTumor)==0){
				contador++;
			}
			if(contador==4 && strcmp(vector[a].nodos,vector[b].nodos)==0){
				contador++;
			}
			if(contador==5 && strcmp(vector[a].nodeCaps,vector[b].nodeCaps)==0){
				contador++;
			}
			if(contador==6 && vector[a].grado==vector[b].grado){
				contador++;
			}
			if(contador==7 && strcmp(vector[a].seno,vector[b].seno)==0){
				contador++;
			}
			if(contador==8 && strcmp(vector[a].zona,vector[b].zona)==0){
				contador++;
			}	
			if(contador==9 && strcmp(vector[a].irradiado,vector[b].irradiado)==0){
				contador++;
			}

			if	(contador == 10){//Se ha repetido todo el struct, por lo que el apartado del vector a, coincide con el b
				nIguales++;
				repetidas=true;
	
			}				
			else
				repetidas=false;	

		}//fin For Anidado b	
		
		if(repetidas==false)
			fprintf(pImprimir,"%s,%s,%s,%s,%s,%s,%d,%s,%s,%s",vector[a].clase,vector[a].edad,vector[a].menopausia,vector[a].tamanoTumor,vector[a].nodos,vector[a].nodeCaps,vector[a].grado,vector[a].seno,vector[a].zona,vector[a].irradiado);		
		repetidas=false;
	}//fin For a

		//----------------
	printf("El número de líneas repetidas en breast-cancer.txt es %d\n",nIguales);
	printf("Nuevo archivo generado breast-cancer-no-duplicates.txt\n");
}

//----------------------------------------------------

void actualizarTamanoMedio(FILE *pArchivo){
	CANCER vector[500];		//Variable en la que almacenamos el vector de registros.
	
	//Array en el que vamos a almacenar a los pacientes en peligro
	//Por algún motivo, si ponemos MAX, se genera un core dump a la hora de salir de la función escribir Binario
	CANCER peligro[100];	

	//Llamada a las funciones necesarias
	int nLineas = cargarRegistros(vector,pArchivo);
	int tMedio = calcularTamanoMedio(vector,pArchivo,nLineas);

	/*
	Creamos un array con los distintos tamaños.
	La idea es la de porder comparar los strings de VECTOR, con los elementes de un vector comprendidos entre:
	El siguiente a la media y el último
	*/
	char *aTam[] = {TAM1,TAM2,TAM3,TAM4,TAM5,TAM6,TAM7,TAM8,TAM9,TAM10,TAM11,TAM12};

	printf("El tamaño medio de los tumores es %s\n",aTam[tMedio]);
	printf("Todos aquellos pacientes cuyo tamaño sea mayor,sean recurrentes e irradiados\n  están considerados como pacientes en estado crítico\n");

	int nLineasPeligro=0; //Variable que guarda el número de líenas que tendrá el nuevo array PELIGRO
	bool bucle=false;	 //Permite reducir el coste de cómputo al ejecutar o no un strcmp
	
	
	
	//Comparamos los valores, y si la el TAM medio conincide con el array

	for (int a=0; a<=nLineas; a++ ){
		bucle=false;
		
		/*
		Si el array es de tipo Eventos Recurrentes, irradiado, se ejecuta un segundo bucle
		*/
		if((strcmp(vector[a].clase,"\nrecurrence-events")==0)&&(strcmp(vector[a].irradiado,"yes")==0)){
			
				for (int b=(tMedio+1); b<=11;b++){
					/*
					Este segundo for(b) permite comparar las posiciones del array de tamaños+1, con el string que es
					irradiado y recurrente, si coincide alguna de las posiciones de memoria, se dev
					*/
					if((bucle==false) && (strcmp(vector[a].tamanoTumor,aTam[b])==0)){
						
						//printf("Tamaño %s\n",aTam[b]);
						//Copiamos todo el vector
						memcpy(&peligro[nLineasPeligro],&vector[a],sizeof(CANCER));
						//Cambiamos la variable booleana para que no continúe la ejecución
						bucle=true;
						nLineasPeligro++;
					}
				}//Fin for B
		}
	}//Fin for A

	//Llamamos a la función que imprimirá el archivo binario
	//pasamos el nuevo array, nlineas de dicho array y el archivo
	escribirBinario(peligro,nLineasPeligro,pArchivo);
}

//-----------------------------------------------------------------

int calcularTamanoMedio(CANCER vector[],FILE *pArchivo,int nLineas){
	
	//Reutilizamos el código de la función de distribuir tamaños
	int nTam1=0, nTam2=0, nTam3=0, nTam4=0, nTam5=0, nTam6=0, nTam7=0, nTam8=0, nTam9=0, nTam10=0, nTam11=0, nTam12=0;

	printf("Cargando tamaño medio...\n");

	printf("%d: %s tiene el tamaño 1\n",1,vector[nLineas-1].tamanoTumor);

	for(int a=0; a<nLineas; a++){

		if	   (strcmp (vector[a].tamanoTumor, TAM1)==0)
			nTam1++;
		else if(strcmp (vector[a].tamanoTumor, TAM2)==0)
			nTam2++;
		else if(strcmp (vector[a].tamanoTumor, TAM3)==0)
			nTam3++;
		else if(strcmp (vector[a].tamanoTumor, TAM4)==0)
			nTam4++;
		else if(strcmp (vector[a].tamanoTumor, TAM5)==0)
			nTam5++;		
		else if(strcmp (vector[a].tamanoTumor, TAM6)==0)
			nTam6++;
		else if(strcmp (vector[a].tamanoTumor, TAM7)==0)
			nTam7++;
		else if(strcmp (vector[a].tamanoTumor, TAM8)==0)
			nTam8++;
		else if(strcmp (vector[a].tamanoTumor, TAM9)==0)
			nTam9++;		
		else if(strcmp (vector[a].tamanoTumor, TAM10)==0)
			nTam10++;
		else if(strcmp (vector[a].tamanoTumor, TAM11)==0)
			nTam11++;
		else if(strcmp (vector[a].tamanoTumor, TAM12)==0)
			nTam12++;
		}
		
		//CALCULAR LA MEDIA:
/*		
		Punto intermedio del intevalo * frecuencia = f(x)
		Sumatorio de F(x)/nº de muestras=Tmedio
*/		
	int media = (2*nTam1+7*nTam2+12*nTam3+17*nTam4+22*nTam5+27*nTam6+32*nTam7+37*nTam8+42*nTam9+47*nTam10+52*nTam11+57*nTam12)/nLineas;
	
	printf("Tamaño medio: %d\n",media);
	
	//Arbol para devolver una posición del vector dependiendo del intervalo de la media:
	if(media<5)
		return 0;
	else if(media >=5 && media <10)
		return 1;
	else if(media >=10 && media <15)
		return 2;
	else if(media >=15 && media <20)
		return 3;
	else if(media >=20 && media <25)
		return 4;
	else if(media >=25 && media <30)
		return 5;
	else if(media >=30 && media <35)
		return 6;
	else if(media >=35 && media <40)
		return 7;
	else if(media >=40 && media <45)
		return 8;
	else if(media >=45 && media <50)
		return 9;
	else if(media >=50 && media <55)
		return 10;
	else if(media >=55 && media <60)
		return 11;
	else{
		printf("Error calculando el tamaño medio\nSaliendo...\n");
		exit (0);
	}
	//Una manera más compacta, hubiese sido dar un número entre 0 y 11 a cada valor, calcular la media, y devolver ese número
	//así se devuelve una posición del array, no es necesario el árbol de returns.
}

void escribirBinario (CANCER peligro [],int nLineasPeligro, FILE *pArchivo){
	
	//Debug que nos permite imprimir el nuevo vector
	/*
	for (int i=0; i<nLineasPeligro;i++){
	printf("%s,",peligro[i].clase);		
	printf("%s,",peligro[i].edad);	
	printf("%s,",peligro[i].menopausia);
	printf("%s,",peligro[i].tamanoTumor);
	printf("%s,",peligro[i].nodos);
	printf("%s,",peligro[i].nodeCaps);
	printf("%d,",peligro[i].grado);
	printf("%s,",peligro[i].seno);
	printf("%s,",peligro[i].zona);
	printf("%s",peligro[i].irradiado);
	}
	*/
	
	//Abrimos un nuevo archivo, esta vez binario

	FILE *pBinario;
	pBinario = fopen ("Pacientes_riesgo","w+b");
	if (fopen == NULL){
		printf("Problema al abrir el archivo binario\nSaliendo...\n");
		exit (0);
	}
	//---------------
	
	
	printf("\nNúmero de líneas en el vector peligro %d\n",nLineasPeligro);	
	
	//Escribimos todo el nuevo vector al archivo
	//La primera como recurrence eventes tiene el salto de líena al principio, hay una líena vacía
	fwrite (peligro,sizeof(CANCER),nLineasPeligro,pBinario);

	printf("Nuevo archivo binario generado con el contenido del vector peligro: \"Pacientes_riesgo\"\n");

	fclose(pBinario);
}

//-----------------------------------------------------------------

int numeroFilas (FILE *pArchivo){
	
	int numeroFilasTotales;
	
	for (char c = getc(pArchivo); c != EOF; c = getc(pArchivo)) {
		if (c == '\n') 
			numeroFilasTotales++;
		}
		return numeroFilasTotales;
}

//fin