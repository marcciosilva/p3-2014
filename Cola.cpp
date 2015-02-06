/* 4547599 4012543 4466345 */

/*
Cola de enteros.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

#include <stdlib.h>

struct AuxNodo {
	int 	elem;
	AuxNodo* sig;
};

typedef AuxNodo* Nodo;

struct AuxCola {
	AuxNodo* pri;
	AuxNodo* ult;
};

typedef AuxCola* Cola;

/*
Cola --> AuxCola
	 _____________
	| Nodo : *pri |_____
	| ------------|		|
	| Nodo : *ult |		|
	|_____________|		|
				|		|
				|		|	 _____________
				|		|-->| int : elem  |
				|			| ------------|
				|			| Nodo : *sig |___
				|			|_____________|	  |
				|			 _____________	  |
				|			| int : elem  |	<-|
				|---------->| ------------|
							| Nodo : *sig |___
							|_____________|	  |
											 NULL
*/


/*******************************************
		PROCEDIMIENTOS AUXILIARES
********************************************/
AuxNodo* crearNodoCola (int i)
/* Devuelve un nodo limpio con el elemento i.*/
{
	Nodo nuevo_nodo = new AuxNodo;
	nuevo_nodo->elem = i;
	nuevo_nodo->sig = NULL;

	return nuevo_nodo;
}
/*******************************************
					FIN
********************************************/

void crearCola (Cola &c)
/*	Devuelve en 'c' la cola vacía. */
{
	c = new AuxCola;

	c->pri = NULL;
	c->ult = NULL;
}

bool esVaciaCola (Cola c)
/*	Devuelve 'true' si 'c' es vacía, 'false' en otro caso. */
{
	return c->pri == NULL;
}

void encolar (int i, Cola &c)
/*	Agrega el elemento 'i' al final de 'c'. */
{
	Nodo nuevo_nodo = crearNodoCola(i);

	if (c->pri == NULL) {
		c->pri = nuevo_nodo;
		c->ult = nuevo_nodo;
	} else {
		c->ult->sig = nuevo_nodo;
		c->ult = nuevo_nodo;
	};
}

int frente (Cola c)
/*	Devuelve el primer elemento de 'c'
	Precondición: ! esVaciaCola(c). */
{
	return c->pri->elem;
}

void desencolar (Cola &c)
/*	Remueve el primer elemento de 'c'.
	Precondición: ! esVaciaCola(c). */
{
	//Apunto al primer nodo con 'aux' y muevo 'c' al siguiente
	Nodo aux = c->pri;
	c->pri = c->pri->sig;
	aux->sig = NULL;

	//Si desencolé el último nodo
	if (c->pri == NULL) {
		c->ult = NULL;
	};

	//Elimino el nodo
	delete aux;
}

void destruirCola (Cola &c)
/*	Libera toda la memoria ocupada por 'c'. */
{
	while (c->pri != NULL) {
		desencolar(c);
	};

	delete c;
}
