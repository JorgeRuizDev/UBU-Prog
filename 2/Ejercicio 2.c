/* 
Título: Conversor de segundos a horas 2000
Descripción: Nos muestra la equivalencia de una cantidad 
de segundos en horas, minutos y segundos
Autor: Jorge Ruiz Gómez
Organización: UBU
Fecha: 20/02/19
Versión 1
*/

#include <stdio.h>


//declaramos las funciones
void calculo(long segundos, int *horas, int *minutos, int *rsegundos);

int main (){
	long segundos; //indica las variables
	int hor,min,rseg;
	
	
	printf("Introduzca los segundos que desee convertir\n"); //pide los segundos
	scanf("%ld",&segundos);
	printf("%ld segundos equivalen a ",segundos);
	
	calculo (segundos, &hor, &min, &rseg); //llama a la función
	
	printf("--%d hora(s), %d minutos y %d segundos--\n",hor,min,rseg); //Imprime el resultado
	
	
	return 0;
}

void calculo(long segundos, int *horas, int *minutos, int *rsegundos) {
	

	
	int horaf, minf, segf; //indica las variables

	segf = (segundos%60); //calcula el resto de los minutos para sacar los segundos
	
	minf = (segundos/60)%60; //calcula el resto de las horas para calcular los minutos
	
	horaf = (segundos/60)/60; //calcula a cuantas horas equivalen

	
	//indica las variables que tienen que volver a main ()
	*minutos = minf;
	*horas = horaf;
	*rsegundos = segf;
	
	
	
	
	
}
