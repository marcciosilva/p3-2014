#ifndef _DEPOSITO_H
#define _DEPOSITO_H

/*
Estructura de artículos y palabras clave.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/


#include "ABB_T.h"
#include "ListaOrd.h"
#include "Pila.h"

struct AuxDeposito;
typedef AuxDeposito * Deposito;

Deposito crearDeposito (int cantidad_articulos);
/*	Devuelve un depósito con 'cantidad_articulos' artículos, sin referencias. */

void agregarReferencia (Deposito &d, int a1, int a2);
/*	Establece en 'd' una referencia desde 'a1' hacia 'a2'. 
	La operación se debe realizar en promedio en O(r),
	siendo r la cantidad de referencias del artículo 'a1'.
	Precondición: 0 <= a1,a2 < cantidad de artículos de 'd'. */

void insertarPalabraClave (Deposito &d, char * p);
/*	Inserta la palabra clave 'p' en 'd' si 'p' no existe en 'd'.
	En otro caso no hace nada. 
	La operación se debe realizar en promedio en O(log C), 
	siendo C la cantidad total de palabras clave. */

bool estaPalabraClave (Deposito d, char * p);
/*	Devuelve 'true' si la palabra clave 'p' existe en 'd', 
	'false' en otro caso.
	La operación se debe realizar en promedio en O(log C), 
	siendo C la cantidad total de palabras clave. */

void asociarArticuloPalabraClave (Deposito &d, int a, char * p, int c);
/*	Incluye a 'p' en las palabras clave del artículo 'a' y a 'a' entre los
	artículos de 'p'. El parámetro 'c' corresponde a la cantidad de veces
	que aparece 'p' en 'a'. Si ya hay 10 palabras clave asociadas a 'a' y
	alguna de las palabras asociadas a 'a' ocurre menos de 'c' veces,
	entonces 'p' sustituye a la que tiene menos en la asociación con 'a' 
	(si más de una cumple esa condición sustituye a cualquiera de ellas).
	La operación se debe realizar en promedio en O(log C + art_prom),
	siendo C la cantidad total de palabras clave y art_prom la cantidad
	promedio de artículos de las palabras clave.
    Precondición: c > 0.
    Precondición: 0 <= a < cantidad de artículos de 'd'.
    Precondición: existe la palabra clave 'p' en 'd'.
    Precondición: no hay asociación entre el artículo 'a' y la palabra
    clave 'p'. */

bool estaAsociadoArticuloPalabraClave (Deposito d, int a, char * p);
/*	Devuelve 'true' si hay asociación entre el artículo 'a' y la palabra
	clave 'p', 'false' en otro caso.
	La operación se debe realizar en promedio en O(1).
    Precondición: 0 <= a < cantidad de artículos de 'd'.
    Precondición: existe la palabra clave 'p' en 'd'. */

ABB_T claveMasFrecuente (Deposito d, int a);
/*	Devuelve el árbol cuya raíz es la palabra clave que aparece
    más veces en 'a'.
	La operación se debe realizar en promedio en O(1).
    Precondición: 0 <= a < cantidad de artículos de 'd'.
    Precondición: el artículo 'a' tiene palabras clave asociadas. */

ListaOrd articulosConPalabraClave (Deposito d, char * p);
/*  Devuelve una lista con los artículos que tienen a 'p' como palabra clave.
	La operación se debe realizar en promedio en O(log C), siendo C la
	cantidad total de palabras clave.
    Precondición: existe la palabra clave 'p'. */

void imprimirPalabrasClaveEnArticulo (Deposito d, int a);
/*  Imprime las palabras clave de 'a' y su cantidad de ocurrencias 
    (separados por un espacio) en orden descendente según su frecuencia, 
    una por línea (entre las que tengan igual frecuencia se imprimen en 
    cualquier orden). 
    Por ejemplo, si se tiene la	palabra clave "hola" con cantidad 3 y la 
    palabra clave "chau" con cantidad 5, se debe imprimir:

chau 5
hola 3
	

	La operación se debe realizar en promedio en O(1).
    Precondición: 0 <= a < cantidad de artículos de 'd'. */

ListaOrd referencias (Deposito d, int a);
/*	Devuelve la lista ordenada de las referencias de 'a'.
	La operación se debe realizar en promedio en O(1).
	Precondición: 0 <= a < cantidad de artículos de 'd'. */

int cantidadArticulos (Deposito d);
/*	Devuelve la cantidad de artículos de 'd'. 
	La operación se debe realizar en promedio en O(1). */

Pila dfsPostOrden (Deposito d);
/*	Devuelve una pila con todos los artículos de 'd' tras una recorrida dfs.
	Los apila en postorden. Cuando haya que decidir entre más de un artículo
	a visitar, se debe elegir el de menor número. 
	La operación se debe realizar en peor caso en O(m + n), sinedo 'm' la 
	cantidad de referencias entre los artículos de 'd' y 'n' la cantidad de
	artículos de 'd'. */

Deposito transpuesto (Deposito d);
/*	Devuelve un depósito igual a 'd' pero con las referencias en sentido inverso. 
	La operación se debe realizar en peor caso en O(m + n), siendo 'm' la 
	cantidad de referencias entre los artículos de 'd' y 'n' la cantidad de
	artículos de 'd'. */

void nuevosAccesibles (Deposito d, int a, int id, int * &colecciones);
/*	Modifica 'colecciones' asignando 'id' a los artículos cuyo actual valor es 
	-1 y son accesibles desde 'a' siguiendo referencias por artículos cuyo 
	actual valor también es -1.
	La operación se debe realizar en peor caso en O(m + n), sinedo 'm' la 
	cantidad de referencias entre los artículos de 'd' y 'n' la cantidad de
	artículos de 'd'.
	Precondición: el tamaño de colecciones es igual a la cantidad de artículos 
	de 'd'.
    Precondición: 0 <= a < cantidad de artículos de 'd'.
	Precondición: colecciones [a] == id. */

/*  NUEVO  */	
int cantidadPalabraClaveEnArticulo (Deposito d, int a, char * p);
/*	Devuelve la cantidad asociada a la palabra clave 'p' en el artículo 'a'.
    Precondición: estaAsociadoArticuloPalabraClave (d, a, p). */

void destruirDeposito (Deposito &d);
/*	Libera la memoria asignada a 'd'. */

#endif /* _DEPOSITO_H */
