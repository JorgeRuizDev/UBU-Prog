#include <stdio.h>

/**
* Title: Valores juntos con comas
* Description: El programa separa tres valores introducidos previamente separados por comas
* @author: Jorge Ruiz Gómez
* @organization: UBU
* @date: 2019-02-13
* @version: 1.0
*/

//
int main () {
//Variables
  int a;
  int b;
  int c;
  int varia;

printf("Introduzca 3 valores separados por comas\n");
varia=scanf("%d,%d,%d", &a, &b, &c);//Pide los valores


//printf("El número de datos introducidos es\n");//Muestra los valores
printf("El número de datos introducidos es %d de 3\n",varia);


//printf("%d\n",b);
//printf("%d\n",c);

return 0;
}
