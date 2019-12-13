/*
Nombre: Calculadora básica con fracciones
Descripción: Calculadora que nos muestra la suma y resta de fracciones
------- programada de forma modular
Autor: Jorge Ruiz Gómez
Versión: 1.0
Fecha: 27/02/19
Organización: UBU
*/

#include <stdio.h> //Llamada a las librerías a la hora de compilar


//Definimos los voids de las funciones que vamos a necesitar, cada una con una función distinta
void leer (int *num, int *deno);

void escribir (int numf, int denof);
void suma (int num1,int deno1,int num2,int deno2);
void resta (int num1, int deno1, int num2, int deno2);
void multiplicacion (int num1, int deno1, int num2, int deno2);
void division (int num1, int deno1, int num2, int deno2);

int main () {
	int a,b,c,d; //Damos un nombre a cada variable que vamos a usar
	
	
	//Llamamos a la función de entrada de datos (leer), y de salida (escribir,)
	
	
	printf("Fracción 1: "); //Diferencia como se presenta la entrada de datos
	leer (&a,&b);
	escribir (a,b);
	
	
	printf("Fracción 2: "); //Igual que la anterior para la segunda fracción
	leer (&c,&d); //Coge el valor de memoria de las variables para que se puedan imprimir
	escribir (c,d);
	
	
	
	//Llama a las funciones
	suma (a,b,c,d); 
	
	resta (a,b,c,d);
	
	multiplicacion(a,b,c,d);
	
    division(a,b,c,d);
	
	return 0;
}

void leer (int *num, int *deno){ //función leer

	printf("Esciba la fracción de la siguiente manera: n/d\n"); //imprime las instrucciones
	scanf("%d/%d",num,deno); //Entrada de datos
	
}

void escribir (int numf, int denof){ //Funcion escribir
	printf("La fracción es: %d/%d\n",numf, denof); //Imprime los resultados previamente escaneados
	
}
void suma (int num1,int deno1,int num2,int deno2){ //realiza la suma
int resultado_suma, denominadorComun;
denominadorComun = (deno1*deno2);
resultado_suma = (num1*deno2+ num2*deno1);
printf("La suma ambas fracciónes es: %d/%d\n",resultado_suma, denominadorComun);

}

void resta (int num1,int deno1,int num2,int deno2){ //realiza la resta
int resultado_resta, denominadorComun;
denominadorComun = (deno1*deno2);
resultado_resta = (num1 * deno2 - num2 * deno1);
printf("La resta ambas fracciónes es: %d/%d\n",resultado_resta, denominadorComun);

}


void multiplicacion (int num1,int deno1,int num2,int deno2){ //realiza la multiplicación
int resultado_multiplicacion, denominadorComun;
denominadorComun = (deno1*deno2);
resultado_multiplicacion = (num1 * num2);
printf("La multiplicación ambas fracciónes es: %d/%d\n",resultado_multiplicacion, denominadorComun);

}

void division (int num1,int deno1,int num2,int deno2){ //realiza la división

printf("La división ambas fracciónes es: %d/%d\n",num1*deno2, deno1*num2);

}

