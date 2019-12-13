/*
Nombre: Cuántos días tiene el mes?
Descripción: Muestra los dias que tiene un mes en los años positivos, incluyendo bisiestos
Autor: Jorge Ruiz Gómez
Organización: Ubu
Fecha: 15/03/2019
Versión: 1.1



CAMBIOS:En la versión 1.1, en la función fDatos se trabaja directamente sobre los punteros y no sobre un integer temporal.
		Solventado un error en la función fCalcularDias, en el statement if en el que se igualaba a 2 en vez de comparar.
*/

#include <stdio.h>

/*************************************************************************************************************************************/
void fDatos (int *pMes, int *pyear) ; //Establecemos las funciones
int fCalcularDias (int pMes, int pYear);
void fMuestraMes (int dias);
/*************************************************************************************************************************************/

/*************************************************************************************************************************************/
int main () {//Función principal
	int mes, year, dias; //Variables donde almacenamos los datos
	
	//Entrada
	fDatos(&mes,&year);
	//Operaciones
	dias =  fCalcularDias (mes, year);
	//Salida
	fMuestraMes (dias); 
	
	return 0;
}

/*************************************************************************************************************************************/

void fDatos (int *pMes, int *pyear) { //Función de entrada de datos

	//Entrada de datos
	printf("Introduzca el year con el siguiente formato\nmm/aaaa\n\n");
	scanf("%d/%d",pMes, pyear);
	
	
	//Condicional que permite saber si una fecha es incorrecta
	if(*pMes>12 | *pMes<1 | *pyear <1 ) {//Aquí habría que añadir un bucle para que el programa funcionase sólo con un mes y año aceptables o algo para que se cerrase
	
		printf("La fecha no es válida\nVuelva a ejecutar el programa\nLos resultados mostrados a continuación son erróneos\n");
		pMes = 0;
		pyear =0;
		//Aquí habría que añadir un exit ya que el programa no funciona adecuadamente.
	}	
}

/*************************************************************************************************************************************/

int fCalcularDias (int pMes, int pYear) {//Función que calcula los días
	
	if (pMes == 2 && ((pYear%4 ==0 && pYear%100 !=0) | (pYear%400==0 && pMes ==2) )) { //Calcula si es bisiesto
		
		printf("Ese año fue bisiesto\n");
		return 29;
	}
	
	else {//asigna los días del mes introducido en el valor de la función
		switch (pMes){
			case 1 :
				return 31;  break;
			case 2 :
				return 28;
				break;
			case 3 :
				return 31;
				break;
			case 4 :
				return 30;
				break;
			case 5
				:return 31;
				break;
			case 6 :
				return 30;
				break;
			case 7 :
				return 31;
				break;
			case 8:
				return 31;
				break;
			case 9 :
				return 30;
				break;
			case 10 :
				return 31;
				break;
			case 11 :
				return 30;
				break;
			case 12 :
				return 31;
				break;
			default:printf("Error en la sentencia switch\n"); return 0; break;
		}
	}
			
}

/*************************************************************************************************************************************/

void fMuestraMes (int dias) { //imprime los días que tiene el mes
	
	printf ("El mes de la fecha introducida tiene %d días\n",dias);
}

