#ifndef _ABBT_H
#define _ABBT_H

#define MAX_STR 80 /* Largo máximo de una palabra clave. */

/*
Arbol binario de búsqueda.
A cada elemento se le asocia una palabra clave y una lista.
El árbol se ordena lexicográficamente según cada palabra clave.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

#include "ListaOrd.h"

struct AuxABB_T;
typedef AuxABB_T* ABB_T;

void crearABB (ABB_T & abb);
/*	Devuelve en 'abb' el arbol vacío. */

void agregarABB (ABB_T &abb, char* p);
/*	Agrega la palabra clave 'p' en 'abb'.
	En otro caso no hace nada. */

bool esVacioABB (ABB_T abb);
/*	Devuelve 'true' si 'abb' es vacío, 'false' en otro caso. */

char * palabraClaveABB (ABB_T abb);
/*	Devuelve la palabra clave de la raíz de 'abb'.
	Precondición: ! esVacioABB(abb). */

ListaOrd listaArticulosABB (ABB_T abb);
/*  Devuelve la lista de artículos asociada a la palabra clave
	de la raíz de 'abb'.
	Precondición: ! esVacioABB(abb) */

void asociarArticuloABB (ABB_T abb, char* p, int a);
/*  Asocia en 'abb' el artículo 'a' con la palabra clave 'p',
	si ésta es una palabra del árbol. En otro caso no hace nada. */

void desasociarArticuloABB(ABB_T abb, char* p, int a);
/*  Desasocia en 'abb' el artículo 'a' de la palabra clave 'p',
	si ésta es una palabra del árbol y si contiene al artículo.
	En otro caso no hace nada. */

ABB_T arbolIzquierdo (ABB_T abb);
/*	Devuelve el subárbol izquierdo de 'abb'.
	Precondicion: ! esVacioABB(abb). */

ABB_T arbolDerecho (ABB_T abb);
/*	Devuelve el subárbol derecho de 'abb'.
	Precondicion: ! esVacioABB(abb).*/

void destruirABB (ABB_T &abb);
/*	Libera toda la memoria ocupada por 'abb'. */

#endif /* _ABBT_H */
