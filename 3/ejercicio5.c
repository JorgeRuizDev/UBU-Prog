/*
Nombre: Calculadora de propiedades de figuras geométricas.
Descripción: calcula el área, perímetro y apotema a partir del radio y lados de una figura
Autor: Jorge Ruiz Gómez
Versión: 1.0
Fecha: 27/02/19
Organización: UBU
*/

#include <stdio.h> //Directivas del procesador para las liberías
#include <math.h>
#define PI 3.1415926535 //Asigna un valor a la palabra PI, y se sustituye en todo el programa la palabra PI por el valor



int lados(); //Nombra las funciones que vamos a usar
void fradio (float *p_radio);
void longlado (int n_lados,float radio, float *p_long_lado);
void area(float d_lado, float *areaAdelvolver);
void perimetro (float d_lado, float n_lado, float *perimetroAdevolver);
void apotema (float p_perimetro, float p_area);


int main () { //Función principal
	int n_lados;//llamada a todas las funciones
	float radio, distancialado;
	float f_perimetro, f_area; //Guardan el valor final de la función
	
	n_lados = lados (); //asignamos el a la varible el valor resultante de la función (Los números de lados)
	
	fradio (&radio); //Asgina el radio a una variable, el resultado obtenido de la función radio.
	
	
	longlado (n_lados, radio, &distancialado); //Estas funciones calculan los valores necesarios para resolver el problema (lado,area,etc...)
	area (distancialado, &f_area);
	perimetro (distancialado, n_lados, &f_perimetro);
	
	apotema (f_perimetro, f_area);
	
	return 0; //Devuelve 0 para cerrar main.
	}
	
	
	int lados (int nlados) { //Introducimos el número de lados.
	
	int numerolados;
	
	printf ("Introduce el número de lados de la figura:\n");
	scanf ("%d",&numerolados);
	
	return numerolados;
	}
	
	void fradio (float *p_radio) { //intorducimos el radio
		printf ("Introduce la longitud del radio en metros:\n");
		scanf("%f",p_radio);
		
	}
	
	
	void longlado (int n_lados, float radio,float *p_long_lado) { //calcula la distancia de cada lado.
		float r,n,l,lcuadrado;
		
		//lcuadrado=2*r^2*(1-cos(360º/n))
		//l=lcuadrado^(1/2)
		
		n=n_lados; //asignamos a L el número de lados
		r=radio;//asignamos a r el radio
		
		lcuadrado=(2*r*r*(1-cos((2*PI)/n)));
		
		l =sqrt(lcuadrado);
		*p_long_lado = l;
	}
	
	void area(float d_lado, float *areaAdelvolver) { // calcula el área y lo devuelve a main y lo imprime
		float areaCalculada = d_lado* d_lado +pow((0.5*d_lado),2);
		printf("El área de la figura es %f m\n", areaCalculada );
		*areaAdelvolver = areaCalculada;
	}
	
	void perimetro (float d_lado,float n_lado, float *perimetroAdevolver) { //calcula el perímetro y lo devuelve a main y lo imprime
		
		float perimetroCalculado = d_lado*n_lado; 
		printf("El perímetro de la figura es %f m\n", perimetroCalculado);
		*perimetroAdevolver = perimetroCalculado;
	}
	
	void apotema (float p_perimetro, float p_area) { //calcula e imprime el apotema
		
		float apotema = (0.5 * p_perimetro) * p_area;
		printf("EL apotema de la figura es %f m\n", apotema);
	}