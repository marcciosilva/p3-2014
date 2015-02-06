/* 4547599 4012543 4466345 */

/*
Arbol binario de búsqueda.
A cada elemento se le asocia una palabra clave y una lista.
El árbol se ordena lexicográficamente según cada palabra clave.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

#include "ListaOrd.h"
#include <string.h>
#define MAX_STR 80

struct AuxABB_T {
	char* 		palabraClave;
	ListaOrd 	listaArticulos;
	AuxABB_T 	*izq, *der;
};

typedef AuxABB_T* ABB_T;


void crearABB (ABB_T & abb)
/*	Devuelve en 'abb' el arbol vacío. */
{
	abb = NULL;
}

bool esVacioABB (ABB_T abb)
/*	Devuelve 'true' si 'abb' es vacío, 'false' en otro caso. */
{
	return abb == NULL;
}

void agregarABB (ABB_T &abb, char* p)
/*	Agrega la palabra clave 'p' en 'abb'.
	En otro caso no hace nada. */
{
	if (esVacioABB(abb)) {
		abb = new AuxABB_T;
		abb->palabraClave = new char[MAX_STR];
		strcpy(abb->palabraClave, p);
		crearLista(abb->listaArticulos);
		abb->izq = NULL;
		abb->der = NULL;
	} else {
		if (strcmp(p, abb->palabraClave) > 0)
			agregarABB(abb->der, p);
		else if (strcmp(p, abb->palabraClave) < 0)
			agregarABB(abb->izq, p);
	};//si la palabra p es igual a la raiz, no se hace nada
}

char * palabraClaveABB (ABB_T abb)
/*	Devuelve la palabra clave de la raíz de 'abb'.
	Precondición: ! esVacioABB(abb). */
{
	return abb->palabraClave;
}

ListaOrd listaArticulosABB (ABB_T abb)
/*  Devuelve la lista de artículos asociada a la palabra clave
	de la raíz de 'abb'.
	Precondición: ! esVacioABB(abb) */
{
	return abb->listaArticulos;
}

void asociarArticuloABB (ABB_T abb, char* p, int a)
/*  Asocia en 'abb' el artículo 'a' con la palabra clave 'p',
	si ésta es una palabra del árbol. En otro caso no hace nada. */
{
	if (not esVacioABB(abb)) {
		if (strcmp(p, abb->palabraClave) == 0) {
			//asocio el articulo a la palabra clave
			insLista(a, abb->listaArticulos);
		} else {
			if (strcmp(p, abb->palabraClave) < 0) {
				asociarArticuloABB(abb->izq, p, a);
			} else {
				asociarArticuloABB(abb->der, p, a);
			};
		};
	};
}

void desasociarArticuloABB(ABB_T abb, char* p, int a)
/*  Desasocia en 'abb' el artículo 'a' de la palabra clave 'p',
	si ésta es una palabra del árbol y si contiene al artículo.
	En otro caso no hace nada. */
{
	if (not esVacioABB(abb)) {
		if (strcmp(p, abb->palabraClave) == 0){
			//desasocio el articulo de la palabra clave
			removerLista(a, abb->listaArticulos);
		} else {
			if (strcmp(p, abb->palabraClave) < 0)
				desasociarArticuloABB(abb->izq, p, a);
			else desasociarArticuloABB(abb->der, p, a);
		};
	};
}

ABB_T arbolIzquierdo (ABB_T abb)
/*	Devuelve el subárbol izquierdo de 'abb'.
	Precondicion: ! esVacioABB(abb). */
{
	return abb->izq;
}

ABB_T arbolDerecho (ABB_T abb)
/*	Devuelve el subárbol derecho de 'abb'.
	Precondicion: ! esVacioABB(abb).*/
{
	return abb->der;
}

void destruirABB (ABB_T &abb)
/*	Libera toda la memoria ocupada por 'abb'. */
{
	if (not esVacioABB(abb)) {
		destruirABB(abb->izq);
		destruirABB(abb->der);
		destruirLista(abb->listaArticulos);
		delete [] abb->palabraClave;
		delete abb;
	};
}
