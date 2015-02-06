#ifndef _PILA_H
#define _PILA_H

/*
Pila acotada de enteros.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

struct AuxPila;
typedef AuxPila* Pila;

void crearPila (int cota, Pila &p);
/*	Devuelve en 'p' la pila vacía, que podrá contener hasta 'cota' elementos. */

bool esVaciaPila (Pila p);
/*	Devuelve 'true' si 'p' es vacía, 'false' en otro caso. */

bool esLlenaPila (Pila p);
/*	Devuelve 'true' si 'p' tiene 'cota' elementos, (siendo 'cota' el valor del
	parámetro pasado en crearPila), 'false' en otro caso. */

void apilar (int i, Pila &p);
/*	Si ! esLlenaPila (p) inserta 'i' en la cima de 'p'.
	En otro caso no hace nada. */

int cima (Pila p);
/*	Devuelve la cima de 'p'.
	Precondición: ! esVaciaPila(p). */

void desapilar (Pila &p);
/*	Remueve la cima de 'p'.
	Precondición: ! esVaciaPila(p). */

void destruirPila (Pila &p);
/*	Libera toda la memoria ocupada por 'p'. */

#endif /* _PILA_H */
