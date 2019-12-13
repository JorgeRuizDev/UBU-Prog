/*
Nombre: Binomio de Newton por bucles o recursividad
Descripción: Introduciendo 3 enteros, calcula su función binomial
Autor: Jorge Ruiz Gómez
Organización:UBU
Versión:1.1
	Añadido:
		Un selector
		El cálculo mediante FOR
Fecha: 27/03/19

		Versión 1.1 (29/03/19)
			Arreglado error que no permitial el correcto funcionamiento del selector		
							El return del bucle se encontraba en el do y no fuera del bucle
							

Compilar con gcc -lm o usando un archivo makelist personalizado
*/
//definimos las directivas de preprocesador
#include <stdio.h>
#include <math.h>


//Declaración de prototipos

unsigned enteroPositivo ();
int leerEntero ();
int f_selector();
int f_ejecutarSuma(int,int,int,int);
int f_Factorial (int);
int f_sumatorio (int, int, int, int);
int f_sumatorioFor (int, int, int, int);
int f_binomial (int, int);
void imprime (int);
/*****************************************************************************/
//Función Main
int main () {
	//Declaración de variables
	int m,a,b,sumatorio;
	
	//Selector de modo	
	int selector;
	selector = f_selector ();
	

	//Asiganación y llamada a los valores de entrada
	m = enteroPositivo ();
	a = leerEntero ();
	b = leerEntero ();

	//Llamada a las funciones + Selector de modo
	sumatorio = f_ejecutarSuma (selector,a,b,m);
		

	imprime (sumatorio);
	return 0;
}
//*******************************************************************************
//SELECTOR
int f_selector (){
	int selector;
		do {
		printf("Seleccione un modo\n1)Cálculo mediante bucles\n2)Cálculo mediante recursividad\n");
		scanf("%d",&selector); 	

		}while (selector <1 | selector >2);
		
	return selector;
}
//***************************************************************************************

int f_ejecutarSuma (int selector,int a,int b,int m){
	int sumatorio;
	if (selector == 1)
		sumatorio = f_sumatorioFor (a,b,m,0);
		
	else 
		sumatorio = f_sumatorio (a,b,m,0);
	
	return sumatorio;
}
/*****************************************************************************/

unsigned enteroPositivo (){	//Entrada de un valor tipo unsigned de 2 Bytes (sin símbolo, siempre positivo)
	int a;
	printf("Introduzca el exponente del binomio, evite los signos\n");
	scanf("%d",&a);
	return a;
}

//*****************************************************************************
int leerEntero () {//Entrada de un valor entero
	int a;
	printf("Introduzca el número entero del interior del binomio\n");
	scanf("%d",&a);
	return a;
}
//*****************************************************************************

int f_Factorial (int n) {//Calculadora de factorial por recursividad
	int resultado;
	
	if (n==0) 
		resultado =  1;
	
	else if (n>0) {
		//El factorial de un número es ese número multiplicado por el factorial del anterior
		resultado = n*f_Factorial(n-1) ;
		
	}

	return resultado;
}
//***************************************************************************
int f_binomial (int m,int n){//Calculadora del binomial
	//Fórmula del binomial
	int binomial = (f_Factorial(m))/(f_Factorial(n)*f_Factorial(m-n));
	return binomial;
}

//***********************************************************************************

int f_sumatorio (int a, int b, int m, int n) { //Sea n el factorial
	int s;
	
	if (m==n){
		s=f_binomial (m,m)*pow(b,n);
		printf("\n(m) (%d)\n\t*%d^%d * %d^%d \t=%d+\n(n) (%d)",m,a,m-n,b,n,s,n);}
	else{
		
		s=f_binomial (m,n)*pow(a,m-n)*pow(b,n)+f_sumatorio(a,b,m,n+1);
		
		printf("\n(m) (%d)\n\t*%d^%d * %d^%d \t=%d+\n(n) (%d)",m,a,m-n,b,n,s,n);
	}
	
	return s;
}

//***************************************************************************************/
int f_sumatorioFor (int a, int b, int m, int n) { //Función que calcula el resultado del binomio con un bucle FOR
	int suma=0;
	printf("Suamtorio mediante bucles\n");
	for (n=0; n<=m; n++) {
		
		suma += (f_binomial(m,n)*pow(a,m-n)*pow(b,n));
		printf("\n(m) (%d)\n\t*%d^%d * %d^%d \t=%d+\n(n) (%d)",m,a,m-n,b,n,suma,n);//Imprime los pasos del bucle
		}
		return suma;
		
}

//********************************************************************************

void imprime (int sumatorio) {
	printf("\t\t\t\t Total=%d\n",sumatorio);	
}