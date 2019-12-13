#include <stdio.h>
/**
* Title: Números enteros positivos, negrativos y grandes
* Description: El programa permite introducir un número entero positivo, negativo y grande, y luego lo muestra
* @author: Jorge Ruiz Gómez
* @organization: UBU
* @date: 2019-02-13
* @version: 1.0
*/
int main () {
  
  int unsigned short entero; //Guarda un número entero
  int signed short signo;  //Guarda un número con signo (Negativo)
  int signed long long largo; // Guarda un número largo

  printf("Introduzca tres números enteros (Sin signo, con signo y largo) \n");
  
  printf("En el orden previo, utilice <space> o <enter> para diferenciarlos \n");
  
 
  scanf ("%hu\n%hd\n%lld", &entero, &signo, &largo);//vincula cada dato a una variable
  //scanf ("%hd", &signo);
  //scanf ("%D", &largo);
  
  printf ("Los números introducidos son: %hu, %hd, %lld \n",entero, signo, largo);//Saca los números

  
 




return 0;
}
