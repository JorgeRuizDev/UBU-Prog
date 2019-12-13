/**
 * Title: Práctica Final Ficheros para examen
 * @authors: Ángel Arroyo
 * @organization: University of Burgos
 * @date: 2018-05-20
 * @version: 4.0
 *------------------------------------------
 * @version: 5.0
 * Fecha: 28/05/2019
 * Autor modificaciones: Jorge Ruiz Gómez (203)
 * Modificaciones:
 *  Añadida un printf para introducir datos en la función limpiar buffer
 *  
 *  Modificadas las opciones del selector para añadir una 6ta
 *
 *  Añadidas 2 funciones
 *  NodecapsFrecuentes  Que devuelve el valor más frecuente de nodcaps en forma de número
 *  tratValoresPerdidos  permite reemplazar el valor ? por uno a escoger por el usuario
 */

#include <stdio.h>
#include<stdbool.h>
#include<string.h>

/*Fichero de entrada (1) y de salida (2)*/
#define FICH "cancer.txt"
#define FICH2 "salidabin.bin"
#define FICH3 "cancerclean.txt"

/* Tamaño de cada uno de los campos*/
#define AGE 6
#define SIZE 6
#define CLASS 25
#define MENOPAUSE 8
#define INVNODE 15
#define NODECAPS 15
#define BREAST 6
#define BREASTQUAD 10
#define IRRADIANT 4

#define RANGOS 13
#define TAM_SALIDA 25

#define MAX_REGS 300

/*Vectores de cadenas con todos los posibles valores para ada campo*/
const char class[][CLASS] =
    { "no-recurrence-events", "recurrence-events" };
const char age[][AGE] =
    { "10-19", "20-29", "30-39", "40-49", "50-59", "60-69", "70-79",
  "80-89", "90-99"
};
const char menopause[][MENOPAUSE] = { "lt40", "ge40", "premeno" };

const char size[][SIZE] =
    { "0-4", "5-9", "10-14", "15-19", "20-24", "25-29", "30-34", "35-39",
  "40-44", "45-49", "50-54", "55-59"
};

const char invnode[][INVNODE] =
    { "0-2", "3-5", "6-8", "9-11", "12-14", "15-17", "18-20", "21-23",
  "24-26", "27-29", "30-32", "33-35", "36-39"
};
const char nodecaps[][NODECAPS] = { "yes", "no", "?" };
const char breast[][BREAST] = { "left", "right" };
const char breastquad[][BREASTQUAD] =
    { "left-up", "left-low", "right-up", "right-low", "central", "?" };
const char irradiant[][IRRADIANT] = { "yes", "no" };

struct cancer {
  char    class[CLASS], age[AGE], menopause[MENOPAUSE], size[SIZE],
      invnode[INVNODE], nodecaps[NODECAPS], breast[BREAST],
      breastquad[BREASTQUAD], irradiant[IRRADIANT];
  int     degmali;
};

typedef struct cancer CANCER;

bool    validarEntero(int, int, int, char);
int     solicitarOpcionMenu();
void    seleccionarOpcion(int);
int     contarCaracteres(FILE *);
void    distribuirTamanos(FILE *);
int     insertarFila(FILE *);
int     actualizarRiesgo(CANCER[], int);
int     calcularTamanomedio(CANCER[], int);
void    escribirBinario(CANCER, FILE *);
int     cargarRegistros(CANCER[], FILE *);
int     eliminarFilas(CANCER[], int, FILE *);
void    escribeFicheroLimpio(CANCER, FILE *);
bool    comparar(CANCER, CANCER);
int     contarFilas(FILE *);
int     limpiarBuffer();

//Prototipos examen
int nodecapsFrecuente(CANCER [],int);
void tratValoresPerdidos(CANCER [],int);


int limpiarBuffer() {
  while(getchar() != '\n') ;
  return 1;
}

/*El programa principal se ejecuta hasta que introduzcamos un 0 en el menú*/
int main() {
  int     opcion;
  do {
    opcion = solicitarOpcionMenu();
    seleccionarOpcion(opcion);
  } while(opcion != 0);
  return 0;
}

/*
 * @Name: validarEntero
 * @Description: para cada vez que introduzcamos un entero desde teclado nos valida el dato en el rango adecuado y tipo
 * @Parámetros entrada: dato leido, número de parámetros leidos por scanf, límite superior, valor del char en el scanf
 * @return devuelve cierto cuando los datos introducidos para cada valor estén en el rango correcto y el tipo correcto
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
bool validarEntero(int opcion, int leidos, int sup, char enter) {
  bool    correcto;
  if(leidos != 2 || enter != '\n' || opcion < 0 || opcion > sup) {
    printf
	("Valor incorrecto, debe estar entre 0 y %d. (INTRO PARA CONTINUAR)\n",
	 sup);
    correcto = false;
    limpiarBuffer();
  } else
    correcto = true;
  return correcto;
}

/*
 * @Name: solicitarOpcionMenu
 * @Description: muestra menú y solicita una de las opciones
 * @return valor escogido por el usuario y validado
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
int solicitarOpcionMenu() {
  int     opcion, leidos, retorno;
  char    enter;
  bool    correcto;

  do {
    printf
	("\nBIENVENIDO AL SOFTWARE DE TRATAMIENTO DEL FICHERO DE CÁNCER DE MAMA\nElige una opción del menú\n");
    printf("+---------------------------------------------+\n");
    printf("| 1. Número de Caracteres totales.       |\n");
    printf("| 2. Relación Edad/Tamaño del tumor.             |\n");
    printf("| 3. Alta de filas.     	|\n");
    printf("| 4. Eliminar filas repetidas. |\n");
    printf("| 5. Pacientes de alto riesgo. |\n");
    printf("| 6. Tratamiento de valores perdidos.  |\n");
    printf("| 0. Salir del programa.                      |\n");
    printf("+---------------------------------------------+\n");

    leidos = scanf("%d%c", &opcion, &enter);
    correcto = validarEntero(opcion, leidos, 6, enter);

  } while(!correcto);

  return opcion;
}

 /*
  * @Name: seleccionarOpcion
  * @Description: llama a las funciones que ejecutan cada una de las opciones del menú
  * @Parámetros entrada: opción del menú seleccionada
  * @authors: Ángel Arroyo
  * @date: 2018-05-20
  * @version: 4.0
  */
void seleccionarOpcion(int opcion) {
  int     caracteres, filas, filasriesgo;
  FILE   *f, *g;
  CANCER  c[MAX_REGS];
  char    salida[TAM_SALIDA];

  switch (opcion) {
    case 1:
      f = fopen(FICH, "r");
      if(f != NULL) {
	caracteres = contarCaracteres(f);
	printf("\n Número de Caracteres: %d", caracteres);
	fclose(f);
      } else
	printf("\n Error en la apertura. ");
      printf("\n\n");

      break;
    case 2:
      f = fopen(FICH, "r");
      if(f != NULL) {
	distribuirTamanos(f);
	fclose(f);
      } else
	printf("\n Error en la apertura. ");
      printf("\n\n");

      break;

    case 3:
      f = fopen(FICH, "a");
      if(f != NULL) {
	printf("\n Se han añadido %d filas ", insertarFila(f));
	fclose(f);
      } else
	printf("\n Error en la apertura. ");
      f = fopen(FICH, "r");
      if(f != NULL) {
	printf(" y el fichero ya tiene %d filas.", contarFilas(f));
	fclose(f);
      } else
	printf("\n Error en la apertura. ");
      printf("\n\n");

      break;

    case 4:
      f = fopen(FICH, "r");
      g = fopen(FICH3, "w");

      if(f != NULL && g != NULL) {
	filas = cargarRegistros(c, f);
	printf("\n Se han cargado: %d en el vector de registros. ", filas);
	printf("\n Se ha generado el fichero sin filas repetidas: %s",
	       FICH3);
	fclose(f);
	printf("\n Se han eliminado %d filas del fichero de entrada %s",
	       eliminarFilas(c, filas, g), FICH);
	fclose(g);
      } else
	printf("\n Error en la apertura. ");

      printf("\n\n");
      break;
    case 5:			/*ejecuta el filtrado de filas sobre el fichero con filas no repetidas */
      f = fopen(FICH, "r");
      g = fopen(FICH3, "w");

      if(f != NULL && g != NULL) {
	filas = cargarRegistros(c, f);
	eliminarFilas(c, filas, g);
	fclose(g);
	fclose(f);
	g = fopen(FICH3, "r");
	if(g != NULL) {
	  filas = cargarRegistros(c, g);
	  filasriesgo = actualizarRiesgo(c, filas);
	  printf("\nHay %d pacientes en alto riesgo. ", filasriesgo);
	  printf("\nSe ha generado el fichero binario de salida: %s",
		 FICH2);
	  fclose(g);
	} else
	  printf("\n Error en la apertura. ");

      } else
	printf("\n Error en la apertura. ");

      printf("\n\n");
      break;
    case 6:
      f = fopen (FICH, "r");
      if (f != NULL ){
      filas = cargarRegistros(c,f);//Filas->número filas; c-> struct con filas
      tratValoresPerdidos(c,filas);//Pasamos los valores a la función
      fclose(f);//Cerramos el archivo
      break;
      
      }
  }
}

/*
 * @Name: contarFilas
 * @Description: cuenta las filas del fichero que le llega por parámetro
 * @Parámetros entrada: fichero a contar las filas
 * @return número de filas
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
int contarFilas(FILE * f) {
  int     total = 0;
  char    c;
  c = fgetc(f);
  while(!feof(f)) {		/*Bucle hasta fin de fich. */
    ++total;
    while(!feof(f) && c != '\n')	/*hasta fin de línea */
      c = fgetc(f);
    if(!feof(f))
      c = fgetc(f);
  }
  return total;
}

/*
 * @Name: contarCaracteres
 * @Description: cuenta los caracteres del fichero que le llega por parámetro. Omite los saltos de linea
 * @Parámetros entrada: fichero a contar los caracteres
 * @return número de caracteres
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
int contarCaracteres(FILE * f) {
  int     total = 0;
  char    c;
  c = fgetc(f);
  while(!feof(f)) {		/*Bucle hasta fin de fich. */
    if(c == '\n')		/*hasta fin de línea */
      c = fgetc(f);
    else {
      ++total;
      c = fgetc(f);
    }
  }
  return total;
}

/*
 * @Name: distribuirTamanos
 * @Description: Se nos pedirá por teclado el rango de edad de una paciente y se nos mostrará el porcentaje de pacientes que existen en cada grupo de tamaños de tumor
 * @Parámetros entrada: fichero de entrada
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
void distribuirTamanos(FILE * f) {
  int     opcion, leidos, rango[RANGOS], i;
  float   k = 0.0;
  char    enter, ageFile[AGE], sizeFile[SIZE];
  bool    correcto;

  for(i = 0; i < RANGOS; i++)
    rango[i] = 0;

  do {
    printf
	("\n     Distribución de tamaño de tumores por rangos de edad\n");
    printf
	("+---------------------------------------------------------------+\n");
    printf
	("1. 10-19\n2. 20-29\n3. 30-39\n4. 40-49\n5. 50-59\n6. 60-69\n7. 70-79\n8. 80-89\n9. 90-99       |\n");
    printf("Número (1-9): ");

    leidos = scanf("%d%c", &opcion, &enter);
    correcto = validarEntero(opcion, leidos, 9, enter);
  } while(!correcto);

  /*leemos el fichero de entrada pero solo almacenamos la edad y el tamaño del tumor */
  fscanf(f,
	 "%*[^,],%[^,],%*[^,],%[^,],%*[^,],%*[^,],%*c,%*[^,],%*[^,],%*s\n",
	 ageFile, sizeFile);

  while(!feof(f)) {

    if(strcmp(ageFile, age[opcion - 1]) == 0) {
      k++;
      for (i=0;i<RANGOS;i++)
        if(strcmp(sizeFile, size[i]) == 0)
          rango[i]++;
    }
    fscanf(f,
	   "%*[^,],%[^,],%*[^,],%[^,],%*[^,],%*[^,],%*c,%*[^,],%*[^,],%*s\n",
	   ageFile, sizeFile);
  }

  printf("\nResultados: %.0f  filas en el rango %s", k, age[opcion - 1]);
  printf("\nRango de edad seleccionado: %s", age[opcion - 1]);

  for(int j = 0; j < RANGOS; j++)
    printf("\n Tamaño: %d a %d Porcentaje: %5.2f%%", j * 5, j * 5 + 4,
	   (rango[j] / k) * 100);
}

/*
 * @Name: insertarFila
 * @Description: Añade nuevas filas al fichero breast-cancer.txt con los datos que introduzcamos por teclado para cada una de las 10 columnas. 
 * @Parámetros entrada: fichero de entrada (con filas repetidas)
 * @return Devuelve el número de filas nuevas añadidas. 
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
int insertarFila(FILE * f) {
  int     cont = 0, degmali, leidos, x, opcion[10];
  bool    salir = false, correcto;
  char    enter, otra;

  do {

    do {
      printf
	  ("\nIntroduce la CLASE: 1.no-recurrence-events 2.recurrence-events (1-2): ");
      leidos = scanf("%d%c", &opcion[0], &enter);
      correcto = validarEntero(opcion[0], leidos, 2, enter);
    } while(!correcto);

    do {
      printf
	  ("\nIntroduce la EDAD: 1.10-19 2.20-29 3.30-39 4.40-49 5.50-59 6.60-69 7.70-79 8.80-89 9.90-99 (1-9): ");
      leidos = scanf("%d%c", &opcion[1], &enter);
      correcto = validarEntero(opcion[1], leidos, 9, enter);
    } while(!correcto);

    do {
      printf("\nIntroduce MENOPAUSIA: 1.lt40 2.ge40 3.premeno (1-3): ");
      leidos = scanf("%d%c", &opcion[2], &enter);
      correcto = validarEntero(opcion[2], leidos, 3, enter);
    } while(!correcto);

    do {
      printf
	  ("\nIntroduce el TAMAÑO del tumor: 1.0-4 2.5-9 3.10-14 4.15-19 5.20-24 6.25-29 7.30-34 8.35-39 9.40-44 10.45-49 11.50-54 12.55-59: (1-12): ");
      leidos = scanf("%d%c", &opcion[3], &enter);
      correcto = validarEntero(opcion[3], leidos, 12, enter);
    } while(!correcto);

    do {
      printf
	  ("\nIntroduce el INV-NODES: 1.0-2 2.3-5 3.6-8 4.9-11 5.12-14 6.15-17 7.18-20 8.21-23 9.24-26 10.27-29 11.30-32 12.33-35 13.36-39 (1-13): ");
      leidos = scanf("%d%c", &opcion[4], &enter);
      correcto = validarEntero(opcion[4], leidos, 13, enter);
    } while(!correcto);

    do {
      printf("\nIntroduce el NODE-CAPS: 1.YES 2.NO 3.? (1-3): ");
      leidos = scanf("%d%c", &opcion[5], &enter);
      correcto = validarEntero(opcion[5], leidos, 3, enter);
    } while(!correcto);

    do {
      printf("\nIntroduce el DEGMALI:(1-3): ");
      leidos = scanf("%d%c", &opcion[6], &enter);
      correcto = validarEntero(opcion[6], leidos, 3, enter);
    } while(!correcto);

    degmali = opcion[6];

    do {
      printf("\nIntroduce el BREAST: 1.left 2.right(1-2): ");
      leidos = scanf("%d%c", &opcion[7], &enter);
      correcto = validarEntero(opcion[7], leidos, 2, enter);
    } while(!correcto);

    do {
      printf
	  ("\nIntroduce el BREAST-QUAD: 1.left-up 2.left-low 3.right-up 4.right-low 5.central 6.? (1-6): ");
      leidos = scanf("%d%c", &opcion[8], &enter);
      correcto = validarEntero(opcion[8], leidos, 6, enter);
    } while(!correcto);

    do {
      printf("\nIntroduce RADIACION: 1.yes 2.no (1-2): ");
      leidos = scanf("%d%c", &opcion[9], &enter);
      correcto = validarEntero(opcion[9], leidos, 2, enter);
    } while(!correcto);

    for(x = 0; x < 10; x++)
      opcion[x] = opcion[x] - 1;

/*escribimos en el fichero de salida una cadena con todos los campos seleccionados*/
    fprintf(f, "%s,%s,%s,%s,%s,%s,%d,%s,%s,%s\n", class[opcion[0]],
	    age[opcion[1]], menopause[opcion[2]], size[opcion[3]],
	    invnode[opcion[4]], nodecaps[opcion[5]], degmali,
	    breast[opcion[7]], breastquad[opcion[8]],
	    irradiant[opcion[9]]);
    cont++;

    printf("\n Otra?? ('n' para finalizar) ");
    scanf("%c", &otra);
  } while(otra != 'n');

  return cont;
}

/*
 * @Name: cargarRegistros
 * @Description: Carga el fichero de entrada en el vector de registros
 * @Parámetros entrada: fichero de entrada (con filas repetidas o sin ellas) y vector de registros vacío
 * @return Devuelve el número de filas cargadas 
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
int cargarRegistros(CANCER c[MAX_REGS], FILE * f) {
  int     filas, i = 0;
  fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%s\n",
	 c[i].class, c[i].age, c[i].menopause, c[i].size, c[i].invnode,
	 c[i].nodecaps, &c[i].degmali, c[i].breast, c[i].breastquad,
	 c[i].irradiant);
  while(!feof(f) && i < MAX_REGS) {
    i++;
    fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%s\n",
	   c[i].class, c[i].age, c[i].menopause, c[i].size, c[i].invnode,
	   c[i].nodecaps, &c[i].degmali, c[i].breast, c[i].breastquad,
	   c[i].irradiant);
  }
  return i;
}

/*
 * @Name: eliminarFilas
 * @Description: Cargaremos el fichero .txt en un vector de registros y eliminaremos las filas repetidas, aquellas con todos los campos iguales. 
   Crearemos un nuevo fichero con las filas sin repetir y nos devolverá el número de filas de este nuevo fichero.
 * @Parámetros entrada: fichero de salida vacío, vector de registros cargado y número de filas del mismo 
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
int eliminarFilas(CANCER c[MAX_REGS], int filas, FILE * g) {
  int     i, j = 0, k;
  bool    iguales = false;
  for(i = 0; i < filas; i++) {	/*comparamos todas con todas mediante un doble bucle */
    iguales = false;
    for(k = i + 1; k < filas && !iguales; k++)
      if(comparar(c[i], c[k])) {
	j++;
	iguales = true;
      } else if(k == filas - 1 && iguales == false)	/*escribe al fichero de salida cada fila no repetida */
	escribeFicheroLimpio(c[i], g);
  }
  return j;
}

/*
 * @Name: escribeFicheroLimpio
 * @Description: escribe en el fichero de salida una sola fila (no repetida en el fichero original)   
 * @Parámetros entrada: fichero de salida y registro a escribie
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
void escribeFicheroLimpio(CANCER c, FILE * g) {
  fprintf(g, "%s,%s,%s,%s,%s,%s,%d,%s,%s,%s\n", c.class, c.age,
	  c.menopause, c.size, c.invnode, c.nodecaps, c.degmali, c.breast,
	  c.breastquad, c.irradiant);
}

/*
 * @Name: comparar
 * @Description: compara dos registros si tienen todos sus campos iguales   
 * @Parámetros entrada: registro c y registro d
 * @return: cierto o falso
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
bool comparar(CANCER c, CANCER d) {
  bool    r;
  if(strcmp(c.class, d.class) == 0 && strcmp(c.age, d.age) == 0
     && strcmp(c.menopause, d.menopause) == 0
     && strcmp(c.size, d.size) == 0 && strcmp(c.invnode, d.invnode) == 0
     && strcmp(c.nodecaps, d.nodecaps) == 0 && c.degmali == d.degmali
     && strcmp(c.breast, d.breast) == 0
     && strcmp(c.breastquad, d.breastquad) == 0
     && strcmp(c.irradiant, d.irradiant) == 0)
    r = true;
  else
    r = false;
  return r;
}

/*
 * @Name: actualizarRiesgo
 * @Description: Suponemos en alto riesgo a aquellos pacientes con tratamiento recurrente, que se hayan sometido a radioterapia y con un tamaño de tumor mayor a la media de los tamaños de los tumores de todas las filas. 
   Escribiremos en un fichero binario esos pacientes en alto riesgo, todos sus campos.   
 * @Parámetros entrada: vector de registros (sin filas repetidas) y número de filas
 * @return: fils escritas al fichero binario
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
int actualizarRiesgo(CANCER c[MAX_REGS], int filas) {
  FILE   *s;
  int     medio, i, j, h = 0, riesgo = 0;
  s = fopen(FICH2, "wb");
  if(s != NULL) {
    medio = calcularTamanomedio(c, filas);
    printf("\nEl tamaño medio del tumor es: %s ", size[medio - 1]);
    for(i = 0; i < filas; i++)
      if(strcmp(c[i].irradiant, irradiant[0]) == 0
	 && strcmp(c[i].class, class[1]) == 0
	 && strcmp(c[i].size, size[medio - 1]) > 0) {
	riesgo++;
	escribirBinario(c[i], s);	/*cada fila en alto riesgo se escribe al fichero binario de salida */
      }
  } else
    printf("\n Error en la apertura de binario. ");
  return riesgo;
}

/*
 * @Name: calcularTamanomedio
 * @Description: Calcula el tamaño medio del tumor entre todas las filas del fichero  
 * @Parámetros entrada: vector de registros (sin filas repetidas) y número de filas
 * @return: número entero entre 1 y 12 que se corresponde al tamaño medio del tumor
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
int calcularTamanomedio(CANCER c[MAX_REGS], int filas) {
  int     i, j, h = 0, contar[12], suma = 0, media;
  for(i = 0; i < 12; i++)
    contar[i] = 0;

  for(i = 0; i < filas; i++)
    for(j = 0, h = 0; j < 12 && h == 0; j++)
      if(strcmp(c[i].size, size[j]) == 0) {
	h = 1;
	contar[j]++;		/*aumentamos en 1 el contador para cada uno de los 12 tamaños */
      }

  for(i = 0, j = 1; i < 12; i++, j++)
    suma += j * contar[i];	/*media de los tamaños de los tumores */
  return suma / filas;
}

/*
 * @Name: escribirBinario
 * @Description: escribe en el fichero de salida binario una sola fila de paciente en alto riesgo   
 * @Parámetros entrada: fichero de salida binario y registro a escribir
 * @authors: Ángel Arroyo
 * @date: 2018-05-20
 * @version: 4.0
 */
void escribirBinario(CANCER c, FILE * b) {
  fwrite(&c, sizeof(c), 1, b);
}

//------------------------------------

//Contenido del examen: Debajo

void tratValoresPerdidos(CANCER array[],int filas){

        //Imprimimos el número de filas
        printf("Se han leído %d filas\n",filas);

        //Variables del selector (para verificar la entrada)
        int opcion, nIntroducidos;
        char enter;
        bool correcto;


        //Calculamos el nodecap más frecuente (Devuelve 0 o 1)
        int nodeC=nodecapsFrecuente(array,filas);

        //definimos un string que guarde el nodecap común
        char nodeComparar[NODECAPS];
        //----

        //Asignamos al nuevo sting unos valores dependiento del valor de nodeC
        switch(nodeC){
          case 0:
            printf("La mayoría de los pacientes no tienen nodecaps\n");
            strcpy(nodeComparar,"no");
            break;
          case 1:
            printf("La mayoría de los pacientes tienen nodecaps\n");
            strcpy(nodeComparar,"yes");
            break;
          default:
            printf("Error en el switch nodeC en la función trarValoresPerdidos()\n");
            break;
        }
        

        printf("A continuación se mostrarán las líneas cuyo NODE-CAPS no está definido\n");
        printf("El número a la izquierda de la fila \"x)\", indica el número de la fila afectada\n ");
        //Bucle que analiza el componente NODECAPS del regristo
        //Va de 0 a número de filas-1

        for(int a=0; a<filas;a++){
        //El siguiente if imprime las filas cuyo nodecpas es "?"

          //Podríamos optimizar el código comparando sólo el primer valor del string, ya que sería
          // y, n ,?; Ahorraríamos tiempo de ejecución.
          //podemos hacerlo con la función strncmp

               if(strcmp(array[a].nodecaps,"?")==0){
                  
                        printf("\n--------------\n%d) ",a+1);
                        printf("%s,",array[a].class);
                        printf("%s,",array[a].age);
                        printf("%s,",array[a].menopause);
                        printf("%s,",array[a].size);
                        printf("%s,",array[a].invnode);
                        printf("%s,",array[a].nodecaps);
                        printf("%d",array[a].degmali);
                        printf("%s,",array[a].breast);
                        printf("%s,",array[a].breastquad);
                        printf("%s\n",array[a].irradiant);
                        
                        //Imprimimos un menú
                        printf("¿Qué desea hacer con la anterior fila anterior?\n");
                        printf("1) Sustituir el valor por -yes-\n");
                        printf("2) Sustituir el valor por -no-\n");
                        printf("3) Sustituir el valor por el más frecuente (%s)\n",nodeComparar);
                        
                        //Validamos la entrda entre (1 y 3)
                        do{
                          printf("--> ");
                                nIntroducidos=scanf("%d%c",&opcion,&enter);
                                correcto= validarEntero(opcion,nIntroducidos,3,enter);
                                if (opcion == 0){
                                  correcto=false;
                                  printf("Pulse [ENTER\n]\n");
                                  limpiarBuffer();
                                }
                        }while(!correcto);

                        //Dependiendo de la entrada escogida, el programa reemplazará el nodecaps
                        //indefinido por el escogido por el usuario

                        switch (opcion){                    
                          case 1:
                            strcpy(array[a].nodecaps,"yes");
                            break;
                          case 2:
                            strcpy(array[a].nodecaps,"no");
                            break;
                          case 3:
                            strcpy(array[a].nodecaps,nodeComparar);
                            break;
                        }
                        //Mostramos la nueva línea por pantalla.
                        printf("Nueva línea:\n");

                        printf("%s,",array[a].class);
                        printf("%s,",array[a].age);
                        printf("%s,",array[a].menopause);
                        printf("%s,",array[a].size);
                        printf("%s,",array[a].invnode);
                        printf("%s,",array[a].nodecaps);
                        printf("%d",array[a].degmali);
                        printf("%s,",array[a].breast);
                        printf("%s,",array[a].breastquad);
                        printf("%s\n",array[a].irradiant);
                       
                }

     }
        printf("Se ha actualizado el registro de entrada con los nuevos valores de los NODE-CAPS conflictivos\n");
}

//------------------------------

int nodecapsFrecuente(CANCER array[],int lineas){

        printf("Calculando en NODE-CAPS más frecuente\nEspere...\n");
        //Los valores que nos van a servir como contador los ponemos a 0
        int yes=0, no=0, desconocido=0;

        //Hacemos un bucle que compare los distintos valores del array, y cuente los valores de cada uno
for (int i=0;i<lineas;i++){
        if (strcmp(array[i].nodecaps,"yes")==0)
                yes++;
        else if (strcmp(array[i].nodecaps,"no")==0)
                no++;
        else
          desconocido++;
        }

        //Imprimimos la información
        printf("Hay %d pacientes con nodecaps\n",yes);
        printf("Hay %d pacientes sin nodecaps\n",no);
        printf("Hay %d pacientes con cuyo nodecaps es desconocido\n\n",desconocido);


        //Devolvemos los valores a la función
        //1 para yes, 0 para no
        if (yes>no)
          return 1;
        else
          return 0;
}
//FIN
