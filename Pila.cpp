/* 4547599 4012543 4466345 */

/*
Pila acotada de enteros.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

#include <stdlib.h>

struct AuxPila {
    int* pila;
    int tamanio;
    int tope;
};

typedef AuxPila* Pila;


void crearPila (int cota, Pila &p)
/*  Devuelve en 'p' la pila vacía, que podrá contener hasta 'cota' elementos. */
{
    p = new AuxPila;
    p->pila = new int[cota];
    p->tamanio = cota;
    p->tope = -1;
}

bool esVaciaPila (Pila p)
/* Devuelve 'true' si p es vacia, 'false' en otro caso.*/
{
    return (p->tope) == -1;
}

bool esLlenaPila (Pila p)
/*  Devuelve 'true' si 'p' tiene 'cota' elementos, (siendo 'cota' el valor del
    parámetro pasado en crearPila), 'false' en otro caso. */
{
    return p->tope == (p->tamanio - 1);
}

void apilar (int i, Pila &p)
/*  Si ! esLlenaPila (p) inserta 'i' en la cima de 'p'.
    En otro caso no hace nada. */
{
    if (not esLlenaPila(p)) {
        (p->tope)++;
        (p->pila)[p->tope] = i;
    };
}

int cima (Pila p)
/*  Devuelve la cima de 'p'.
    Precondición: ! esVaciaPila(p). */
{
    return (p->pila)[(p->tope)];
}

void desapilar (Pila &p)
/*  Remueve la cima de 'p'.
    Precondición: ! esVaciaPila(p). */
{
    (p->tope)--;
}

void destruirPila (Pila &p)
/*  Libera toda la memoria ocupada por 'p'. */
{
    delete[] p->pila;
    delete p;
}
