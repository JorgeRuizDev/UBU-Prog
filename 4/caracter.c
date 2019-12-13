/*
Nombre: Conversor de Minúsuculas a mayúsculas
Definición: Convierte utilizando las equivalencias en ASCII
Autor: Jorge Ruiz Gómez
Fecha: 06/03/19
Versión: 1.0
Organización: UBU
*/




#include <stdio.h>
//Nombramos las funciones y las definimos
void leercaracter (char *p_caracterMinus);
void pasarMayus (char *p_caracterMinus,char *p_caracterMayus);
void imprimirCar(char *p_caracterMayus);



int main () { //Variable  principal
	char caracterMinus, caracterMayus;
	
	leercaracter(&caracterMinus);
	pasarMayus(&caracterMinus, &caracterMayus); //Usamos dos variables para no perder la letra minúscula
	imprimirCar(&caracterMayus);
	
	return 0;
}


void leercaracter(char *p_caracterMinus) { //Lee el caracter desde el teclado
	printf("Introduce el carácter en minúscula (a-z)\n");
	*p_caracterMinus = getchar (); //Devuelve el caracter asignado mediante getchar

}

void pasarMayus (char *p_caracterMinus, char *p_caracterMayus) { //función que pasa a mayúsculas
	//Vamos a pasar el carcater mediante un sumatorio en ASCI
	//Hay una diferencia de -32 en ascii entre las minúsculas y las mayúsculas
	
	int carAscii; //variable que guarda el caracter en valor ascii
	carAscii = *p_caracterMinus; //guardamos el valor en ascii
	
	printf("La letra en Ascii es: %d\n",carAscii); //comprobamos que la letra está en ascii
	
	*p_caracterMayus = carAscii-32; //pasamos la letra a mayúsculas restando 32
}

void imprimirCar(char *p_caracterMayus) { //función que imprime le caracter
	
	printf("El caracter en mayúsculas es: ");
	putchar(*p_caracterMayus);//imprime la variable pasada de main
	printf("\n");//salto de línea
	
}
