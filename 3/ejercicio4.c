
/*
Título: Calculadora de área y perímetro de un rombo
Descripción: Calcula el área y el perímetro de un rombo mediante funciones
Autor: Jorge Ruiz Gómez
Fecha: 27/02/2019
Versión: 1.0
Organización: UBU

*/


//Importante: Para compilar añadir -lm tras gcc nombrearchibo.c 

// gcc nombre.c -lm

#include <stdio.h> //Llama las liberías
#include <math.h>

void diagonalesRombo (float *p_diagonal); //Define las funciones del programa
void areaRombo (float p_diagonal1, float p_diagonal2);
void perimetroRombo (float p_diagonal1, float p_diagonal2);

int main () { //función principal
	float diagonal1, diagonal2; //Define las variables en las que vamos a almacenar las diagonales
	
	printf("\nDiagonal 1: "); // Llama a la funcion para almacenar la diagonal
	diagonalesRombo (&diagonal1);
	
	printf("Diagonal 2: ");
	diagonalesRombo (&diagonal2);	
	
	
	printf("\n");//imprime un espacio
	
	areaRombo (diagonal1, diagonal2); //Llama a la funcion que calcula el área
	
	perimetroRombo (diagonal1, diagonal2); //llama a la función que calcula el perímetro
	
	return 0;
}


void diagonalesRombo (float *p_diagonal) {
	//pide la entrada de datos y la asigna a las variables de MAIN
	printf("Introduce el tamaño de la diagonal en metros:\n");
	scanf("%f",p_diagonal);	
}

void areaRombo (float p_diagonal1, float p_diagonal2) { //calcula el área y lo imprime
	//el a´rea = 0.5*D*d
	float area;
	
	area = p_diagonal1 * p_diagonal2 * 0.5;
	
	printf("El área del rombo es %f m\n", area);	
}

void perimetroRombo (float p_diagonal1, float p_diagonal2){ //calcula el área y lo imprime
	
	float perimetro;
	//perímetro: 2*sqr(d^2+D^2)
	
	perimetro = 2*sqrt(pow(p_diagonal1,2)+pow(p_diagonal2,2)); //utiliza las funciones de la librería math.h para calcular
	
	printf("El perímetro del rombo es %f m\n",perimetro);
	
}

