#include <stdio.h>
/**
* Title: Valor ASCII correspondiente a un entero [48,122]
* Description: El programa muestra el valor ASCII correspondiente a un entero comprendido entre 48 y 122
* @author: Jorge Ruiz Gómez
* @organization: UBU
* @date: 2019-02-13
* @version: 1.0
*/
int main()
{
  int a; //Variable para introducir el valor
  printf("Introduzca un valor comprendido entre 48 y 122 para ver su ASCII\n");
  scanf("%d",&a); //introduce el valor
  printf("El valor correspondiente de %d en ASCII es - %c - \n",a,a); //muestra el valor en entero y ascii

  return 0;
}
