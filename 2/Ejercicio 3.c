/*
Nombre: Ultimate megapower mostrador de cifras
Descripción: Muestra las cifras individuales que forman un número de 4 cifras
Autor: Jorge Ruiz Gómez
Organización: UBU
Fecha: 20/02/19
Versión: 1.0
*/

#include <stdio.h>

//Nombra la función que se encarga de dividir
void divcifras ( int cifra,int *cifra1, int *cifra2, int *cifra3, int *cifra4);

//Función principal
int main () {
	
	int cifra, cifraf1, cifraf2, cifraf3, cifraf4; //variables de la cifra
	
	//pide la cifra
	printf("\nIntroduzca un número de 4 cifras (1000-9999)\n");//El programa funciona con números menores de 1000, devolviendo un 0 en las cifras vacías
	scanf("%d",&cifra);
	
	divcifras(cifra, &cifraf1, &cifraf2, &cifraf3, &cifraf4);//llama a la función
	
	printf("Las cifras que forman %d son:\n\n%d\n%d\n%d\n%d\n\n",cifra, cifraf1, cifraf2, cifraf3, cifraf4); //Imprime el resultado
	


	
	return 0;
}




void divcifras (int cifra, int *cifra1, int *cifra2, int *cifra3, int *cifra4) {
	
	int c1, c2, c3, c4; //las variables que vamos a usar
	int b2, b3, b4;
	
	
	//divide la cifra y muestra el resultado
	
	c1 = cifra/1000;
	
	b2 = (cifra-c1*1000);
	
	c2 = b2/100;
	
	b3 = b2-c2*100;
	
	c3 = b3/10;
	
	c4 = b3-c3*10;
	/*
	Explicación de como separar la cifra.
	La cifra (4879), si la dividimos entre 1000, se guarda sólo el entero, por lo que así podemos obtener la cifra inicial (4)-C1
	
	Para hallar la siguiente cifra, Restamos a la cifra completa (4879) 4000, para dejar el 879, para restar el número exacto, multiplicamos c1*1000=4000
	
	Ahora que tenemos el 879 suelto, podemos dividir entre 100 para hallar la segunda cifra (C2) y repetir el proceso para la 3ra y 4ta. Se podría automatizar 
	para cualquier dígito con bucles y condiciones, pero no es posible para nuestro nivel
	*/
	
	//Envía el resultado a la función para que termine
	*cifra1 = c1;
	*cifra2 = c2;
	*cifra3 = c3;
	*cifra4 = c4;
}