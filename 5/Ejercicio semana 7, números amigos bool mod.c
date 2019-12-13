/*
Nombre: Números amigos
Descripción: nos indica si dos números positivos son amigos entre sí
Fecha 03/04/19
Organización: Ubu
Versión: 1.1 (06/04/19)
	Añadido en la función capturaNumero un contador para saber que dato se va a introducir, es decir, las veces que se ha ejecutado la función correctamente.
	
	reemplazados los _Bool por bool para un código más uniforme
Compilar mediante GCC para un correcto funcionamiento

*/

//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

//Llamada a las directivas de preprocesador
#include <stdio.h>
#include <stdbool.h>	//Librería que nos permite usar booleanos

//Declaración de prototipos
int clean_stdin();
int capturaNumero (int *);
int sumaDivisores (int);
bool compara (int, int, int, int);
void escribeResultado (bool, int, int);

//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

int main () {
	int n1, n2, sdiv1, sdiv2,contador=1;	//Define las variables enteras en las que se almacenan las sumas de los divisores y los números introducidos
	bool amigos;		
	//Lamadas a las funciones
	printf("---------------------------------------------------------------\n");
	n1=  capturaNumero (&contador);
	n2 = capturaNumero (&contador);
	
	printf ("Los valores introducidos son: %d y %d\n",n1,n2);
	
	sdiv1 = sumaDivisores (n1);
	sdiv2 = sumaDivisores (n2);
	
	amigos = compara (n1,sdiv1,n2,sdiv2);
	escribeResultado (amigos, n1,n2);
	
	return 0;
}

//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

int clean_stdin () {	//Función que nos permite introducir una entrada limpia
	printf("Valor Incorrecto\n");
	while(getchar () != '\n');
	return 1;
}

//-----------------------------------------------------------------------------------------------------------------------

int capturaNumero (int *contador) {
	
	int numero, leidos;	//Definimos las variables a utilizar durante la entrada y su verificación
	char enter;
	bool correcto;
	
	do {
		
		printf("%d:Introduzca el número para comprobar si es amigo: ",*contador);
		leidos = scanf("%d%c",&numero,&enter);
	
	if 	(leidos != 2 || enter != '\n' || numero <=0) {	//Si la entrada no es correcta (no es un número positivo ni un enter tras introducido)

			correcto = false;
			clean_stdin ();
	
	}
	else {		//Devuelve que el valor es correcto
		printf("¡Valor correcto!\n\n");
		correcto=true;
		*contador = *contador +1;
		}
		
	}while (correcto != true);	//Si el valor no es correcto ejecuta el do {} hasta que lo sea
	
		return numero; 
}

//-----------------------------------------------------------------------------------------------------------------------

int sumaDivisores (int d) {
	int n = d, suma = 0;	//Damos el valor n el mismo de d, y la suma = 0 para evitar errores
	
	while (n>0) {	
			
		if (d%n == 0){		//Si es divisor (el resto es 0, suma el número a 0)
			suma += n;
			n--;}		//Repetimos el bucle con un número menos 
		
		else
			n--;
	}
	
	return (suma - d);		//Restamos el valor d, ya que es divisor de n al inicio (n=d), es decir, nos suma el valor de d en el total, pero la suma de divisores no incluye a este.
	
}

//-----------------------------------------------------------------------------------------------------------------------

bool compara (int n1, int div1, int n2, int div2) {
	
	if (n1 == div2 && n2 == div1 )		//Compara si dos números son amigos, y devuelve un true
		return true;
	else
		return false;
	
}

//-----------------------------------------------------------------------------------------------------------------------

void escribeResultado (bool rbool, int n1, int n2){	//Si los numeros eran enteros o no, imprime un mensaje distinto
	
	if (rbool == true)
		printf("Los números %d y %d son amigos entre sí\n",n1,n2);
	
	else
		printf("Los números %d y %d no son amigos entre sí\n",n1,n2);
	
	printf("---------------------------------------------------------------\n");
}
