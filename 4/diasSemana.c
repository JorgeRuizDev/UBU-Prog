/*
Nombre: Test de enumeración mediante 
Descripción: Muestra una lista con los días de la semana usando un ENUM global
Autor: Jorge Ruiz Gómez
Fecha: 07/03/2019 
Organización: UBU
Versión: 1.1
Cambios: (06/03/19) Códgio primitivo
		(07/03/2019) uso de una variable asignada desde el código y no Entrada
*/

#include <stdio.h>
void diaSiguiente (int p_dia);//Funciones
void todosDias ();

enum diasDeLaSemana {lunes=1, martes=2, miercoles=3, jueves=4, viernes=5, sabado=6, domingo=7};	//Enum Global donde se asigna a cada día su número correspondiente

int main (){
	
	//enum diasDeLaSemana {lunes=1, martes=2, miercoles=3, jueves=4, viernes=5, sabado=6, domingo=7};	
	
	enum diasDeLaSemana dia; //Asignamos la llamada a ENUM con dia
	
	
	printf("El día por defecto es: ");
	dia = martes; //asignamos que valor de enum es dia (Por defecto ponemos martes/02)
	printf("%d\n",dia); //imprime el día asignado en la línea anterior
	
	diaSiguiente(dia);//llamadas a las funciones
	todosDias ();
	
	return 0;
}

void diaSiguiente (int p_dia) {
	
	printf("El día siguiente es: ");

	printf("%d\n",p_dia+1);//imprime el día siguiente en la lista (03 por defecto)
	
}

void todosDias () {
	
	printf("La equivalencia de los días es:\n lunes=1,\n martes=2,\n miercoles=3,\n jueves=4,\n viernes=5,\n sabado=6,\n domingo=7\n");
	printf("%d,%d,%d,%d,%d,%d,%d\n",lunes, martes,miercoles,jueves,viernes,sabado,domingo); //imprime la lista desde el enum global
	
}

