#ifndef _COLAPRIORIDAD_H
#define _COLAPRIORIDAD_H

/*
Cola de prioridad acotada de árboles.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

#include "ABB_T.h"

struct AuxColaPrioridad;
typedef AuxColaPrioridad * ColaPrioridad;

void crearColaPrioridad (ColaPrioridad &cp, int tamanio);
/*	Devuelve en 'cp' una cola de prioridad vacía, 
	que podrá contener hasta 'tamanio' elementos.
	Precondición: tamanio > 0. */

ABB_T encolarColaPrioridad (ColaPrioridad &cp, ABB_T abb, int prio);
/*	Agrega a 'cp' el árbol 'abb' con prioridad 'prio' si la prioridad de 
	alguno de sus árboles es menor que 'prio' (en cuyo caso, lo agrega luego de
	remover alguno de los árboles con mínima prioridad) o si 'cp' no está llena.
	En otro caso no hace nada.
	En caso de remover un árbol, lo devuelve como resultado de la llamada. En
	caso de no poder insertar el árbol 'abb' por ser peor en prioridad, la función
	retorna 'abb'. En otro caso, se devuelve NULL. */

bool esVaciaColaPrioridad (ColaPrioridad cp);
/*	Devuelve 'true' si 'cp' es vacía, 'false' en otro caso. */

bool esLlenaColaPrioridad (ColaPrioridad cp);
/*	Devuelve 'true' si 'cp' está llena, 'false' en otro caso. */

bool perteneceColaPrioridad (ColaPrioridad cp, ABB_T abb);
/*	Devuelve 'true' si 'abb' se encuentra en 'cp', 'false' en otro caso. */

ABB_T maximoColaPrioridad (ColaPrioridad cp);
/*	Devuelve el árbol de 'cp' que tiene asignada mayor prioridad
	(si más de uno cumple esa condición devuelve cualquiera de ellos).
	Precondición: 'cp' no es vacía. */

int prioridadMaximoColaPrioridad (ColaPrioridad cp);
/*	Devuelve la mayor prioridad de los árboles de 'cp'.
	Precondición: 'cp' no es vacía. */

void removerMaximoColaPrioridad (ColaPrioridad &cp);
/*	Remueve de 'cp' el árbol de mayor prioridad
	(si más de uno cumple esa condición remueve cualquiera de ellos).
	Precondición: 'cp' no es vacía. */

ColaPrioridad copiarColaPrioridad (ColaPrioridad cp);
/*	Devuelve una cola de prioridad con los mismos elementos de 'cp'	(comparte 
	memoria). */

/*  NUEVO  */	
int prioridadColaPrioridad (ColaPrioridad cp, ABB_T abb);
/*	Devuelve la prioridad asociada a 'abb' en 'cp'.
	Precondición: perteneceColaPrioridad (cp, abb) */

void destruirColaPrioridad (ColaPrioridad &cp);
/*	Libera toda la memoria ocupada por 'cp'. */

#endif /* _COLAPRIORIDAD_H */
