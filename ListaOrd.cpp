/* 4547599 4012543 4466345 */

/*
Lista de enteros ordenada de manera creciente, sin elementos repetidos.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

#include <stdlib.h>

struct AuxListaOrd {
	int elem;
	AuxListaOrd *sig;
};

typedef AuxListaOrd* ListaOrd;


/*******************************************
		PROCEDIMIENTOS AUXILIARES
********************************************/
AuxListaOrd* crearNodoListaOrd (int i)
/* Devuelve un nodo limpio con el elemento i.*/
{
	ListaOrd nuevo_nodo = new AuxListaOrd;
	nuevo_nodo->elem = i;
	nuevo_nodo->sig = NULL;

	return nuevo_nodo;
}
/*******************************************
					FIN
********************************************/

void crearLista (ListaOrd &l)
/*	Devuelve en 'l' la lista vacía. */
{
	l = NULL;
}

bool esVaciaLista (ListaOrd l)
/*	Devuelve 'true' si 'l' es vacía, 'false' en otro caso. */
{
	return l == NULL;
}

void insLista (int i, ListaOrd &l)
/*	Inserta 'i', manteniendo el orden, en la lista 'l', si 'i' no está en 'l'.
	En otro caso no hace nada. */
{
	ListaOrd prev, actual;
	bool termine;

	// Caso lista vacía
	if (esVaciaLista(l)) {
		l = crearNodoListaOrd(i);
	}
	// Caso insertar al comienzo
	else if (i < l->elem) {
			actual = crearNodoListaOrd(i);
			actual->sig = l;
			l = actual;
	}
	// Caso iterativo
	else {
		termine = false;
		prev = l;
		actual = l->sig;
		while ((actual != NULL) && not termine) {
			if (i < actual->elem) {
				termine = true;
				prev->sig = crearNodoListaOrd(i);
				prev->sig->sig = actual;
			 } else {
			 	if (i == actual->elem) {
					termine = true;
			 	} else {
					actual = actual->sig;
					prev = prev->sig;
			 	};
			 };
		};

		// Caso insertar al final
		if (not termine) {
			prev->sig = crearNodoListaOrd(i);
		};
	};
}

/*	Versión recursiva de insLista()
	-------------------------------
{
	// Caso lista vacía o insertar al comienzo
	if (esVaciaLista(l) || ((not esVaciaLista(l)) && ((l->elem) > i))) {
		ListaOrd aux = new AuxListaOrd;
		aux->elem = i;
		aux->sig = l;
		l = aux;
	} else if ((l->elem) < i) {
		insLista(i, l->sig);
	};
}
*/

int primeroLista (ListaOrd l)
/*	Devuelve el valor del primer elemento de 'l'.
	Precondición: ! esVaciaLista (l). */
{
	return l->elem;
}

void restoLista (ListaOrd &l)
/*	Cambia 'l' a su resto.
	Precondición: ! esVaciaLista (l). */
{
	l = l->sig;
}

void removerLista (int i, ListaOrd &l)
/*	Remueve el elemento 'i' de la lista 'l'.
	Si no estaba, no hace nada. */
{
	if (not esVaciaLista(l)) {
		if (primeroLista(l) == i) {
			ListaOrd tmp = l;
			restoLista(l);
			delete tmp;

		} else {
			ListaOrd tmp = l;
			ListaOrd anterior = tmp;
			while (not esVaciaLista(tmp) && (primeroLista(tmp) != i)) {
				anterior = tmp;
				tmp = tmp->sig;
			};
			if (not esVaciaLista(tmp)) { //es decir que lo encontré
				anterior->sig = tmp->sig;
				tmp->sig = NULL;
				delete tmp;
			};
		};
	};
}

void destruirLista (ListaOrd &l)
/*	Libera toda la memoria ocupada por 'l'. */
{
	if (not esVaciaLista(l)) {
		destruirLista(l->sig);
		delete l;
	};
}
