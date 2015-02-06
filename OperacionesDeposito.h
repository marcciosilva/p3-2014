#ifndef _OPERACIONES_DEPOSITO_
#define _OPERACIONES_DEPOSITO_

/*
Operaciones sobre Deposito.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/


#include "Deposito.h"
#include "ListaOrd.h"

int gradosDeSeparacion (Deposito d, bool * articulos_considerados);
/*	Devuelve los grados de separación entre un conjunto de artículos
    considerados. El artículo número i es considerado si y sólo si
    articulos_considerados[i] == true.
    De no poder llegar mediante referencias desde un artículo a otro,
    transitando solo por artículos considerados,
    se debe retornar INT_MAX, incluido de limits.h
    De haber uno o menos artículos considerados retornar 0.
	La operación se debe realizar en peor caso en O(n . m ), sinedo 'm' la 
	cantidad de referencias entre los artículos de 'd' y 'n' la cantidad de
	artículos de 'd'.
	Precondición: el tamaño de 'articulos_considerados' es igual a
	la cantidad de artículos de 'd'. */

int * colecciones (Deposito d);
/*	Devuelve las colecciones de 'd', cada una en una lista diferente.
	La salida de esta operación debe ser un array en donde
	para la posición i se encuentra el número de colección a la que
	pertenece el artículo i.

# Formato de la salida

	Las colecciones se identifican con enteros de 0 a (k-1),
	siendo k la cantidad de colecciones. Una colección A tiene
	un identificador menor que otra colección B si y sólo si
	hay un artículo de A cuyo número es menor que todos los
	números de los artículos de B.

	Por ejemplo, dado el depósito que tiene los
	artículos 0, 1, 2 y 3, cuyas colecciones son:

	A = {1}
	B = {0, 2}
	C = {3}

	La salida debe ser: 0 1 0 2

	Observar que 0 2 0 1, 1 0 1 2, 1 2 1 0, 2 0 2 1, 2 1 2 0
	también agrupan correctamente las colecciones,
	pero no cumplen la forma de orden solicitada. 
	
	La operación se debe realizar en peor caso en O(m + n), sinedo 'm' la 
	cantidad de referencias entre los artículos de 'd' y 'n' la cantidad de
	artículos de 'd'. */

int cantidadArticulosConMismaPalabraClaveMasFrecuente (Deposito d, int a);
/*	Devuelve la cantidad de artículos de 'd' cuya palabra clave más
	frecuente es 'key', siendo 'key' la palabra clave más frecuente del 
	artículo 'a' (si más de una cumple esa condición se elije cualquiera de 
	ellas).
	La operación se debe realizar, en promedio, en O(c1), siendo 'c1' la
	cantidad de artículos asociados a 'key'.
    Precondición: 0 <= a < cantidad de artículos de 'd'.
    Precondición: el artículo 'a' tiene al menos una palabra clave. */

int referenciasConMismaPalabraMasFrecuente (Deposito d, int a);
/*	Devuelve la cantidad de artículos de 'd' hacia los que tiene referencia 
	directa el artículo 'a', y están asociados a la palabra clave más
	frecuente de 'a' (si más de una cumple esa condición se elije cualquiera de 
	ellas).
	La operación se debe realizar, en promedio, en O(r) siendo r la cantidad de
	referencias que hay en 'a'.
    Precondición: 0 <= a < cantidad de artículos de 'd'.
    Precondición: el artículo 'a' tiene al menos una palabra clave. */

/*  NUEVO  */
void identificarColecciones (Deposito d, char* * palabras_identificadoras,
		int cantidad_palabras_identificadoras, char* * &identificaciones,
		int &tamanio_arreglo);
/*	Asocia palabras identificadoras a las colecciones, buscando maximizar
	las suma de las apariciones de esas palabras en los artículos de las
	colecciones.
	Cada colección tiene hasta una palabra identificadora asignada y
	una palabra identificadora tiene hasta una colección asignada. Para que
	haya asignación entre una palabra identificadora 'p' y una colección 'c',
	'p' debe ser palabra identificadora de cada uno de los artículos de 'c'.
	La operación devuelve un array de palabras identificadoras, en donde en la
	posición 'i' se tiene la palabra identificadora asociada a la colección
	'i', según la numeración que se usa en la operación colecciones. Si una
	colección no tiene palabra identificadora, se le asocia NULL.
	La salida de esta función debe estar en el arreglo 'identificaciones', y
	en 'tamanio_arreglo' debe estar su tamaño.
	De haber más de una solución óptima, devolver cualquiera de ellas.
	Precondición: en 'palabras_identificadoras' hay
	'cantidad_palabras_identificadoras' elementos.
	Precondición: para todo 0 <= i < cantidad_palabras_identificadoras se
	cumple estaPalabraClave (d, palabras_clave [i]) */

#endif /* _OPERACIONES_DEPOSITO_ */
