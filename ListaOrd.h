#ifndef _LISTAORD_H
#define _LISTAORD_H

/*
Lista de enteros ordenada de manera creciente, sin elementos repetidos.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

struct AuxListaOrd;
typedef AuxListaOrd* ListaOrd;

void crearLista (ListaOrd &l);
/*	Devuelve en 'l' la lista vacía. */

void insLista (int i, ListaOrd &l);
/*	Inserta 'i', manteniendo el orden, en la lista 'l', si 'i' no está en 'l'. 
	En otro caso no hace nada. */

bool esVaciaLista (ListaOrd l);
/*	Devuelve 'true' si 'l' es vacía, 'false' en otro caso. */

int primeroLista (ListaOrd l);
/*	Devuelve el valor del primer elemento de 'l'.
	Precondición: ! esVaciaLista (l). */

void restoLista (ListaOrd &l);
/*	Cambia 'l' a su resto.
	Precondición: ! esVaciaLista (l). */

void removerLista (int i, ListaOrd &l);
/*	Remueve el elemento 'i' de la lista 'l'.
	Si no estaba, no hace nada. */

void destruirLista (ListaOrd &l);
/*	Libera toda la memoria ocupada por 'l'. */

#endif /* _LISTAORD_H */
