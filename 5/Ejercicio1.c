/*
Nombre: Calculadora de Ecuaciones de segundo grado
Descripción: Permite calcular cualquier tipo de ecuaciones de 2do grado, incluyendo aquellas con resultados imaginarios
Autor: Jorge Ruiz Gómez
Fecha: 13/03/2019
Organización: Ubu
Fecha: 13/03/2019
*/

#include <stdio.h>//Librerías
#include <math.h>

//Llamada y definición de las distintas funciones utilizadas para hacer el programa modular.
float f_radicando(float p_a, float p_b, float p_c);
void f_leerCoeficientes (float *p_a, float *p_b, float *p_c);
int f_tipo(float a,float b,float c, float d);
void calcularSol(float p_a, float p_b, float p_c,float tipo, float radicando, float *p_sol1, float *p_sol2 );
void muestraResultados(int tipo, float sol1,float sol2);

int main () { //Función principal
	
	float a,b,c,radicando; //las variables en las que almacenaremos los números de entrada
	float sol1,sol2;//variable que almacena la solución
	
	int tipo; //tipo=1, degradada; =2, primer grado, =3 x=(-b+-sqrt(radicando))/2*a Tipo 4 normal, Tipo 5 con nº imaginario
	
	f_leerCoeficientes (&a,&b,&c); //lamadas a las funciones
	printf("Los valores son: %f,%f,%f\n",a,b,c);
	radicando = f_radicando (a,b,c); //Aplica a la variable radicando el valor que devuelve la función.

	tipo = f_tipo(a,b,c,radicando);
	printf("El tipo es: %d\n",tipo);//muestra el tipo
	calcularSol (a,b,c,tipo,radicando, &sol1,&sol2);
	
	muestraResultados(tipo, sol1,sol2);
	return 0;//devuelve un entero para el INT de main
}

void f_leerCoeficientes (float *p_a, float *p_b, float *p_c) {//función de entrada de datos
	printf("Introduzca los coeficientes ax^2+bx+c=0\n\nSeparados mediante [enter]\n"); //imprime las instrucciones de entrada
	
	scanf("%f\n%f\n%f",p_a,p_b,p_c);//introucción de datos mediante teclado
	
}

float f_radicando(float p_a, float p_b, float p_c) {//función de calculo del radicando
	//El radicando se expresa como b*b-4*a*c
	
	return (p_b*p_b-4*p_a*p_c); //devuelve el valor calculado por la fórmula a la función

}

int f_tipo (float a, float b, float c,float d) {//analizador de tipos
	// == compara si es igual, != compara si es diferente y >< si son mayores/menores que. Con esto podemos identificar lso tipos
	if (a==0 && b==0) { //Por ejemplo esta compara si a es igual a  y b es igual a , si es así ejecuta el código entre {}
		return (1); //devuelve un valor a la función que la identifica como el tipo.
		
	}
	else if (a==0 && b!=0){
		return 2;
	}

	else if (d==0 && a!=0) {
		
		return 3;
	}
	else if (d>0) {
		return 4;
	}
	
	else if (d<0){
		return 5;
	}
}

void calcularSol(float p_a, float p_b, float p_c,float tipo,float radicando, float *p_sol1, float *p_sol2 ) {
	
	
	float a,b,c,d; //aplicamos nuevos valores a las variables de entrada para facilitar la legibilidad y facilidad del código
						//No es lo más óptimo
	a = p_a;
	b= p_b;
	c= p_c;
	d=radicando;
	
	if (tipo==1) {
		*p_sol1 = 0;
		*p_sol2 = 0; 
		
	}
	else if (tipo==2){
		*p_sol1=(-c)/b;
		*p_sol2 = 0;
	}
	else if (tipo==3) {
		*p_sol1= ((-b)/(2*a));	
	}
	else if (tipo==4) {
		*p_sol1 = (-b+sqrt(d))/(a*2);
		*p_sol2 = (-b-sqrt(d))/(a*2);
	}
	else if (tipo ==5) {
		//*p_sol1 = (-b+sqrt(-d))/a*2;
		//*p_sol2 = (-b-sqrt(-d))/a*2;
		*p_sol1=-b/2*a;
		*p_sol2=(sqrt(-radicando)/a*2);
	}
}

void muestraResultados(int tipo, float sol1,float sol2) { //Imprime el resultado y un texto especial dependiendo del tipo de ecuación
	if (tipo==1) {
		printf("La ecuación no tiene solución\n");
		
	}
	else if (tipo==2){
		printf("La solución es: %f\n",sol1);
	}
	else if (tipo==3) {
		printf("La solución es: %f\n",sol1);
	}
	else if (tipo==4) {
		printf("La soluciones son: %f y %f\n",sol1, sol2);
	}
	else if (tipo ==5) {
	 printf("La solución es: %f+%f(i) y %f-%f(i)	\n",sol1,sol2,sol1,sol2);
	}
	
} 

