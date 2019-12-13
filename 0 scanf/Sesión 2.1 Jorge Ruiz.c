/**
* Title: Operaciones con fracciones
* Description: El programa muestra la suma, resta, multiplicación y división de 4 números (2 fracciones)
* hola mundo
* @author: Jorge Ruiz Gómez
* @organization: UBU
* @date: 2019-02-13
* @version: 1.0
*/

#include <stdio.h>


//Necesitamos 4 números, 2 numerador y 2 denominadores

int main (){
  
  int num1;
  int num2;
  int deno1;
  int deno2;
  int denoFinal;

  printf("Introduce la primera fracción:\n");
  printf("Separe los distintos dígitos con el tabulador (numerador TAB denominador)\n");
  scanf("%d\t%d", &num1 , &deno1);
  printf("Has introducido el número %d/%d \n ",num1, deno1);

  printf("Introduce la segunda fracción:\n");
  printf("Separe los distintos dígitos con el tabulador (numerador TAB denominador)\n");
  scanf("%d\t%d", &num2 , &deno2);
  printf("Has introducido el número %d/%d \n ",num2, deno2);

//Ahora hacemos las operaciones
  //Suma
  //calculamos el denominador común, para el resto de cálculos

  denoFinal = deno1 * deno2;
  //Suma
  printf("La suma de ambas fracciones %d/%d + %d/%d = %d/%d \n",num1,deno1,num2,deno2, num1 * deno2 + num2 * deno1, denoFinal );
  //resta
  printf("La resta de ambas fracciones %d/%d - %d/%d = %d/%d \n",num1,deno1,num2,deno2, num1 * deno2 - num2 * deno1, denoFinal );
  //Multiplicación
  printf("La multiplicación de ambas fracciones %d/%d * %d/%d = %d/%d \n",num1,deno1,num2,deno2, num1 * num2, denoFinal );
  //División
  printf("La división de ambas fracciones %d/%d / %d/%d = %d/%d \n",num1,deno1,num2,deno2, num1 * deno2 ,  num2 * deno1 );




  return 0;
 
}
