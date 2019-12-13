/* 
Título: Calculadora de Perimetro y Área de una circunferencia
Descripción: No da el Per y Area a partir del radio, usando funciones
Autor: Jorge Ruiz Gómez
Organización: UBU
Fecha: 20/02/19
Versión 1
*/

#include <stdio.h>
#define PI 3.1416


	//La fómula del lado L=2*PI*r ----- Area: A=PI*R^2
//Definimos las funciones void
void perCircunf (double radio, double *perCircunf);
void areaCircunf (double radio, double *areaCircunf);

int main () {
	//Declaramos las variables
	double radio;
	double perimetro;
	double area;
	
	perimetro = 1;
	//introducimos los datos
	printf("Introduzca el radio de la circunferencia (En m)\n");
	scanf("%lf", &radio);
	
	//llamamos a la funcion y asignamos los distintos valores a las variables
	perCircunf (radio, &perimetro);
	areaCircunf (radio, &area);
	
	
	//imprimimos el resultado
	printf ("\nEl perímetro es %f\nEl radio es %f\n", perimetro, area);
	
	return 0;
}

//Creamos las funciones
void perCircunf (double radio, double *perCircunf){
	*perCircunf = radio*2*PI;
	
}

void areaCircunf(double radio, double *areaCircunf){
	*areaCircunf = radio*radio*PI;
	
}



