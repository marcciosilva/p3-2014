/* 4547599 4012543 4466345 */

/*
Cola de prioridad acotada de árboles.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

#include "ABB_T.h"
#include <stdlib.h>

enum relacion {
   padre,
   hijoIzq,
   hijoDer
};

struct celda {
	ABB_T 	abb;
	int 	prio;
};

struct AuxColaPrioridad {
	celda* 	array;
	int 	size,
			tope;
};

typedef AuxColaPrioridad* ColaPrioridad;


/*******************************************
		PROCEDIMIENTOS AUXILIARES
********************************************/
void IntercambiarNodos (int pos, relacion familiar, ColaPrioridad &cp)
{
		celda temp;

		switch (familiar) {
				case padre   :
								temp = cp->array[(pos - 1) / 2];
								cp->array[(pos - 1) / 2] = cp->array[pos];
								cp->array[pos] = temp;
								break;

				case hijoIzq :
								temp = cp->array[pos * 2 + 1];
								cp->array[pos * 2 + 1] = cp->array[pos];
								cp->array[pos] = temp;
								break;

				case hijoDer :
								temp = cp->array[pos * 2 + 2];
								cp->array[pos * 2 + 2] = cp->array[pos];
								cp->array[pos] = temp;
								break;

				default : break;
		};
}
/*******************************************
					FIN
********************************************/

void crearColaPrioridad (ColaPrioridad &cp, int tamanio)
/*	Devuelve en 'cp' una cola de prioridad vacía,
	que podrá contener hasta 'tamanio' elementos.
	Precondición: tamanio > 0. */
{
	cp = new AuxColaPrioridad;
	cp->array = new celda[tamanio]; //arreglo de celdas de tamaño tamanio
	cp->size = tamanio;
	cp->tope = -1;
}

ABB_T encolarColaPrioridad (ColaPrioridad &cp, ABB_T abb, int prio)
/*	Agrega a 'cp' el árbol 'abb' con prioridad 'prio' si la prioridad de
	alguno de sus árboles es menor que 'prio' (en cuyo caso, lo agrega luego de
	remover alguno de los árboles con mínima prioridad) o si 'cp' no está llena.
	En otro caso no hace nada.
	En caso de remover un árbol, lo devuelve como resultado de la llamada. En
	caso de no poder insertar el árbol 'abb' por ser peor en prioridad, la función
	retorna 'abb'. En otro caso, se devuelve NULL. */
{
	//	Si la cola está llena
	if (cp->tope == cp->size - 1) {

		//	Busco la posición del árbol de menor prioridad
		//	para saber cuál quitar
		int posMinPrioridad = 0;
		for (int i = 1 ; i <= cp->tope ; i++) {
			if (cp->array[i].prio < cp->array[posMinPrioridad].prio)
				posMinPrioridad = i;
		};

		//	Inserto sólo si la prioridad del árbol de menor prioridad es menor que 'prio'
		if (cp->array[posMinPrioridad].prio < prio) {
			ABB_T abbARemover = cp->array[posMinPrioridad].abb;
			cp->array[posMinPrioridad].abb = abb;
			cp->array[posMinPrioridad].prio = prio;

			//	Reordeno el heap
			int pos = posMinPrioridad;
			while ((pos > 0) && (cp->array[pos].prio > cp->array[(pos - 1) / 2].prio)) {
				//intercambio nodos
				IntercambiarNodos(pos, padre, cp);
				pos = (pos - 1) / 2;
			};

			return abbARemover;
		//sino no hago nada y devuelvo el arbol que no pude insertar
		} else {
			return abb;
		};

	//Si no está llena simplemente lo agrego
	} else {
		(cp->tope)++;
		cp->array[cp->tope].prio = prio;
		cp->array[cp->tope].abb = abb;

		//	Reordeno el heap
		int pos = cp->tope;
		while ((pos > 0) && (cp->array[pos].prio > cp->array[(pos - 1) / 2].prio)) {
			//intercambio nodos
			IntercambiarNodos(pos, padre, cp);
			pos = (pos - 1) / 2;
		};

		return NULL;
	};
}

bool esVaciaColaPrioridad (ColaPrioridad cp)
/*	Devuelve 'true' si 'cp' es vacía, 'false' en otro caso. */
{
	return (cp->tope == -1);
}

bool esLlenaColaPrioridad (ColaPrioridad cp)
/*	Devuelve 'true' si 'cp' está llena, 'false' en otro caso. */
{
	return (cp->tope == cp->size - 1);
}

bool perteneceColaPrioridad (ColaPrioridad cp, ABB_T abb)
/*	Devuelve 'true' si 'abb' se encuentra en 'cp', 'false' en otro caso. */
{
	if (not esVaciaColaPrioridad(cp)) {
		bool pertenece = false;
		for (int i = 0 ; i <= cp->tope ; i++) {
			//si apuntan a la misma dir de memoria los punteros
			if (cp->array[i].abb == abb) {
				pertenece = true;
			};
		};

		return pertenece;
	} else {
		return false;
	};
}

ABB_T maximoColaPrioridad (ColaPrioridad cp)
/*	Devuelve el árbol de 'cp' que tiene asignada mayor prioridad
	(si más de uno cumple esa condición devuelve cualquiera de ellos).
	Precondición: 'cp' no es vacía. */
{
	return cp->array[0].abb;
}

int prioridadMaximoColaPrioridad (ColaPrioridad cp)
/*	Devuelve la mayor prioridad de los árboles de 'cp'.
	Precondición: 'cp' no es vacía. */
{
	return cp->array[0].prio;
}

void destruirColaPrioridad (ColaPrioridad &cp);

void removerMaximoColaPrioridad (ColaPrioridad &cp)
/*	Remueve de 'cp' el árbol de mayor prioridad
	(si más de uno cumple esa condición remueve cualquiera de ellos).
	Precondición: 'cp' no es vacía. */
/*{
	ColaPrioridad colaNueva;
	crearColaPrioridad(colaNueva, cp->size);
	for (int i = 1 ; i <= cp->tope ; i++) {
		encolarColaPrioridad(colaNueva, cp->array[i].abb, cp->array[i].prio);
	};

	destruirColaPrioridad(cp);
	cp = colaNueva;
}*/

/*	Versión alternativa de removerMaximoColaPrioridad()
	-------------------------------------------------
  //pseudo-codigo:
	//sustituyo el primer elemento del array por el ultimo
	//comparo con sus dos hijos
			//si el de la izquierda es el menor o si ambos hijos son menores pero
					//tienen igual prioridad, lo cambio con el de la izquierda
			//si es el de la derecha, lo cambio con el de la izquierda
			//si no son menores, termina*/
{
	//sustituyo el primer elemento del array por el ultimo
	cp->array[0].abb = cp->array[cp->tope].abb;
	cp->array[0].prio = cp->array[cp->tope].prio;
	--(cp->tope);

	int pos = 0;
	bool done = false;

	//reordeno la cola
	//mientras tenga un hijo y no haya terminado
	while (((pos*2 + 1) <= cp->tope) && (not done)) {

			//si existe el hijo derecho
			if ((pos*2 + 2) <= cp->tope) {

					//elijo el hijo de mayor prioridad para intercambiar
					if (cp->array[pos*2 + 2].prio > cp->array[pos*2 + 1].prio) {
							if (cp->array[pos].prio < cp->array[pos*2 + 2].prio) {
									IntercambiarNodos(pos, hijoDer, cp);
									pos = pos*2 + 2;
							} else {
									done = true;
							};

					} else if (cp->array[pos].prio < cp->array[pos*2 + 1].prio) {
							IntercambiarNodos(pos, hijoIzq, cp);
							pos = pos*2 + 1;
					} else {
							done = true;
					};

			//caso solo hay hijo izquierdo
			} else if (cp->array[pos].prio < cp->array[pos*2 + 1].prio) {
					IntercambiarNodos(pos, hijoIzq, cp);
					pos = pos*2 + 1;
			} else {
					done = true;
			};
	};
}


ColaPrioridad copiarColaPrioridad (ColaPrioridad cp)
/*	Devuelve una cola de prioridad con los mismos elementos de 'cp'	(comparte
	memoria). */
{
	ColaPrioridad colaNueva; crearColaPrioridad(colaNueva, cp->size);
	colaNueva->tope = cp->tope;
	for (int i = 0 ; i <= cp->tope ; i++) {
		colaNueva->array[i].abb = cp->array[i].abb;
		colaNueva->array[i].prio = cp->array[i].prio;
	};

	return colaNueva;
}

int prioridadColaPrioridad (ColaPrioridad cp, ABB_T abb)
/*	Devuelve la prioridad asociada a 'abb' en 'cp'.
	Precondición: perteneceColaPrioridad (cp, abb) */
{
	int i = 0;
	bool found = false;

	//no debe chequearse que i < cp->tope, es precondicion
	while (not found) {
		if (cp->array[i].abb == abb) {
			found = true;
		};
		i++;
	};

	//asumiendo que el arbol esta en la cp no tengo que chequear si found == true
	return cp->array[i - 1].prio;
}

void destruirColaPrioridad (ColaPrioridad &cp)
/*	Libera toda la memoria ocupada por 'cp'. */
{
	delete [] cp->array;
	delete cp;
}