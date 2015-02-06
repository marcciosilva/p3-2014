#ifndef _COLA_H
#define _COLA_H

/*
Cola de enteros.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

struct AuxCola;
typedef AuxCola* Cola;

void crearCola (Cola & c);
/*	Devuelve en 'c' la cola vacía. */

bool esVaciaCola (Cola c);
/*	Devuelve 'true' si 'c' es vacía, 'false' en otro caso. */

void encolar (int i, Cola &c);
/*	Agrega el elemento 'i' al final de 'c'. */

int frente (Cola c);
/*	Devuelve el primer elemento de 'c'
	Precondición: ! esVaciaCola(c). */

void desencolar (Cola &c);
/*	Remueve el primer elemento de 'c'.
	Precondición: ! esVaciaCola(c). */

void destruirCola (Cola &c);
/*	Libera toda la memoria ocupada por 'c'. */

#endif /* _COLA_H */
