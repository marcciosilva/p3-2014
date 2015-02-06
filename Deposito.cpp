/* 4547599 4012543 4466345 */

/*
Estructura de artículos y palabras clave.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

#include "ABB_T.h"
#include "ColaPrioridad.h"
#include "ListaOrd.h"
#include "Pila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AuxHash {
	ColaPrioridad 	colaPalabrasClave;
	ListaOrd 		listaAdy;
};

struct AuxDeposito {
	AuxHash* 	hash;
	ABB_T 		abbPalabrasClave;
	int 		total_articulos;
};

typedef AuxDeposito* Deposito;


/*******************************************
		PROCEDIMIENTOS AUXILIARES
********************************************/
ListaOrd referencias (Deposito d, int a);

void DFSDeposito(Deposito d, int vertice, int* &marcados, Pila &p)
/* Realiza DFS para todos los nodos pertenecientes a la misma CFC que 'vertice'.*/
{
	ListaOrd listaAux = referencias(d, vertice);

	//Marco 'vertice'
	marcados[vertice] = 1;

	while(not esVaciaLista(listaAux)) {
	    if (marcados[primeroLista(listaAux)] == -1) {
	    	DFSDeposito(d, primeroLista(listaAux), marcados, p);
	    };
	    restoLista(listaAux);
	};
	//Apilo en post-orden
	apilar(vertice, p);
}

bool estaPalabraClaveArbol(ABB_T &abb, char* p)
/*	Devuelve 'true' si la palabra clave 'p' se encuentra en el arbol binario
	de busqueda de palabras clave 'abb'. Devuelve 'false' en otro caso*/
{
	if (not esVacioABB(abb)) {
		if (strcmp(palabraClaveABB(abb), p) == 0)
			return true;
		else if (strcmp(p, palabraClaveABB(abb)) > 0) {
			ABB_T arbolDer = arbolDerecho(abb);
			return estaPalabraClaveArbol(arbolDer, p);
		} else {
			ABB_T arbolIzq = arbolIzquierdo(abb);
			return estaPalabraClaveArbol(arbolIzq, p);
		};
	} else {
		return false;
	};
}
/*******************************************
					FIN
********************************************/

Deposito crearDeposito (int cantidad_articulos)
/*	Devuelve un depósito con 'cantidad_articulos' artículos, sin referencias. */
{
	Deposito d = new AuxDeposito;
	d->hash = new AuxHash[cantidad_articulos];
	d->total_articulos = cantidad_articulos;

	for (int i = 0 ; i < cantidad_articulos ; i++) {
		crearLista(d->hash[i].listaAdy);
		crearColaPrioridad(d->hash[i].colaPalabrasClave, 10);
	};

	crearABB(d->abbPalabrasClave);

	return d;
}

void agregarReferencia (Deposito &d, int a1, int a2)
/*	Establece en 'd' una referencia desde 'a1' hacia 'a2'.
	La operación se debe realizar en promedio en O(r),
	siendo r la cantidad de referencias del artículo 'a1'.
	Precondición: 0 <= a1,a2 < cantidad de artículos de 'd'. */
{
	insLista(a2, d->hash[a1].listaAdy);
}

void insertarPalabraClave (Deposito &d, char * p)
/*	Inserta la palabra clave 'p' en 'd' si 'p' no existe en 'd'.
	En otro caso no hace nada.
	La operación se debe realizar en promedio en O(log C),
	siendo C la cantidad total de palabras clave. */
{
	agregarABB(d->abbPalabrasClave, p);
}

bool estaPalabraClave (Deposito d, char * p)
/*	Devuelve 'true' si la palabra clave 'p' existe en 'd',
	'false' en otro caso.
	La operación se debe realizar en promedio en O(log C),
	siendo C la cantidad total de palabras clave. */
{
	return estaPalabraClaveArbol(d->abbPalabrasClave, p);
}

void asociarArticuloPalabraClave (Deposito &d, int a, char * p, int c)
/*	Incluye a 'p' en las palabras claves del artículo 'a' y a 'a' entre los
	artículos de 'p'. El parámetro 'c' corresponde a la cantidad de veces
	que aparece 'p' en 'a'. Si ya hay 10 palabras clave asociadas a 'a' y
	alguna de las palabras asociadas a 'a' ocurre menos de 'c' veces,
	entonces 'p' sustituye a la que tiene menos en la asociación con 'a'
	(si más de una cumple esa condición sustituye a cualquiera de ellas).
	La operación se debe realizar en promedio en O(log C + art_prom),
	siendo C la cantidad total de palabras clave y art_prom la cantidad
	promedio de artículos de las palabras clave.
    Precondición: c > 0.
    Precondición: 0 <= a < cantidad de artículos de 'd'.
    Precondición: existe la palabra clave 'p' en 'd'.
    Precondición: no hay asociación entre el artículo 'a' y la palabra
    clave 'p'. */
{
	//busco el arbol de la palabra p en mi arbol de palabras clave
	ABB_T ptrPalabraClave = d->abbPalabrasClave;

	while (strcmp(palabraClaveABB(ptrPalabraClave), p) != 0) {
		if (strcmp(p, palabraClaveABB(ptrPalabraClave)) > 0)
			ptrPalabraClave = arbolDerecho(ptrPalabraClave);
		else ptrPalabraClave = arbolIzquierdo(ptrPalabraClave);
	};

	//Incluyo 'p' en las palabras claves del artículo 'a'
	ABB_T arbolRemovido = encolarColaPrioridad(d->hash[a].colaPalabrasClave, ptrPalabraClave, c);

	if (not esVacioABB(arbolRemovido)) {
		if (arbolRemovido != ptrPalabraClave) { //si son iguales, no hago nada porque no se agrego
			desasociarArticuloABB(d->abbPalabrasClave, palabraClaveABB(arbolRemovido), a);
			asociarArticuloABB(d->abbPalabrasClave, p, a);
		};
	} else {
		//Incluyo 'a' entre los artículos de 'p'
		asociarArticuloABB(d->abbPalabrasClave, p, a);
	};
}

bool estaAsociadoArticuloPalabraClave (Deposito d, int a, char * p)
/*	Devuelve 'true' si hay asociación entre el artículo 'a' y la palabra
	clave 'p', 'false' en otro caso.
	La operación se debe realizar en promedio en O(1).
    Precondición: 0 <= a < cantidad de artículos de 'd'.
    Precondición: existe la palabra clave 'p' en 'd'. */
{
	bool asociado = false;
	ColaPrioridad cp = copiarColaPrioridad(d->hash[a].colaPalabrasClave);

	while (not esVaciaColaPrioridad(cp) && not asociado) {
		if (strcmp(p, palabraClaveABB(maximoColaPrioridad(cp))) == 0) {
			asociado = true;
		} else {
			removerMaximoColaPrioridad(cp);
		};
	};
	destruirColaPrioridad(cp);

	return asociado;
}

ABB_T claveMasFrecuente (Deposito d, int a)
/*	Devuelve el árbol cuya raíz es la palabra clave que aparece
    más veces en 'a'.
	La operación se debe realizar en promedio en O(1).
    Precondición: 0 <= a < cantidad de artículos de 'd'.
    Precondición: el artículo 'a' tiene palabras clave asociadas. */
{
	return maximoColaPrioridad(d->hash[a].colaPalabrasClave);
}

ListaOrd articulosConPalabraClave (Deposito d, char * p)
/*  Devuelve una lista con los artículos que tienen a 'p' como palabra clave.
	La operación se debe realizar en promedio en O(log C), siendo C la
	cantidad total de palabras clave.
    Precondición: existe la palabra clave 'p'. */
{
	ABB_T abb = d->abbPalabrasClave;
	while (strcmp(palabraClaveABB(abb), p) != 0) {
		if (strcmp(p, palabraClaveABB(abb)) > 0)
			abb = arbolDerecho(abb);
		else abb = arbolIzquierdo(abb);
	};

	return listaArticulosABB(abb);
}

void imprimirPalabrasClaveEnArticulo (Deposito d, int a)
/*  Imprime las palabras clave de 'a' y su cantidad de ocurrencias
    (separados por un espacio) en orden descendente según su frecuencia,
    una por línea (entre las que tengan igual frecuencia se imprimen en
    cualquier orden).
    Por ejemplo, si se tiene la	palabra clave "hola" con cantidad 3 y la
    palabra clave "chau" con cantidad 5, se debe imprimir:

		chau 5
		hola 3

	La operación se debe realizar en promedio en O(1).
    Precondición: 0 <= a < cantidad de artículos de 'd'. */
{
	ColaPrioridad cp = copiarColaPrioridad(d->hash[a].colaPalabrasClave);

	while (not esVaciaColaPrioridad(cp)) {
		ABB_T abbAImprimir = maximoColaPrioridad(cp);
		int prio = prioridadMaximoColaPrioridad(cp);
		printf("%s %d\n", palabraClaveABB(abbAImprimir), prio);
		removerMaximoColaPrioridad(cp);
	};

	destruirColaPrioridad(cp);
}

ListaOrd referencias (Deposito d, int a)
/*	Devuelve la lista ordenada de las referencias de 'a'.
	La operación se debe realizar en promedio en O(1).
	Precondición: 0 <= a < cantidad de artículos de 'd'. */
{
	return d->hash[a].listaAdy;
}

int cantidadArticulos (Deposito d)
/*	Devuelve la cantidad de artículos de 'd'.
	La operación se debe realizar en promedio en O(1). */
{
	return d->total_articulos;
}

Pila dfsPostOrden (Deposito d)
/*	Devuelve una pila con todos los artículos de 'd' tras una recorrida dfs.
	Los apila en postorden. Cuando haya que decidir entre más de un artículo
	a visitar, se debe elegir el de menor número.
	La operación se debe realizar en peor caso en O(m + n), sinedo 'm' la
	cantidad de referencias entre los artículos de 'd' y 'n' la cantidad de
	artículos de 'd'. */
{
	int cantVertices = d->total_articulos;
	Pila p;
	crearPila(cantVertices, p);
	int* marcas = new int[cantVertices];

	//Inicializo todos como NO marcados
	for (int i = 0 ; i < cantVertices ; i++) {
		marcas[i] = -1;
	};

	for (int i = 0 ; i < cantVertices ; i++) {
		if (marcas[i] == -1)
			DFSDeposito(d, i, marcas, p);
	};

	return p;
}

Deposito transpuesto (Deposito d)
/*	Devuelve un depósito igual a 'd' pero con las referencias en sentido inverso.
	La operación se debe realizar en peor caso en O(m + n), siendo 'm' la
	cantidad de referencias entre los artículos de 'd' y 'n' la cantidad de
	artículos de 'd'. */
{
	Deposito transpuesto = crearDeposito(d->total_articulos);
	transpuesto->abbPalabrasClave = d->abbPalabrasClave;

	// Creo un puntero a d->ListaAdy para poder recorrerla sin perder referencia a la original
	ListaOrd listaAux;

	for (int i = 0 ; i < d->total_articulos; i++) {
		transpuesto->hash[i].colaPalabrasClave = d->hash[i].colaPalabrasClave;
		listaAux = d->hash[i].listaAdy;
		while (not esVaciaLista(listaAux)) {
			agregarReferencia(transpuesto, primeroLista(listaAux), i);
			restoLista(listaAux);
		};
	};

	return transpuesto;
}

void nuevosAccesibles (Deposito d, int a, int id, int * &colecciones)
/*	Modifica 'colecciones' asignando 'id' a los artículos cuyo actual valor es
	-1 y son accesibles desde 'a' siguiendo referencias por artículos cuyo
	actual valor también es -1.
	La operación se debe realizar en peor caso en O(m + n), sinedo 'm' la
	cantidad de referencias entre los artículos de 'd' y 'n' la cantidad de
	artículos de 'd'.
	Precondición: el tamaño de colecciones es igual a la cantidad de artículos
	de 'd'.
    Precondición: 0 <= a < cantidad de artículos de 'd'.
	Precondición: colecciones[a] == id. */
{
	ListaOrd listaAux = referencias(d, a);

	while (not esVaciaLista(listaAux)) {
	    if (colecciones[primeroLista(listaAux)] == -1) {
	    	colecciones[primeroLista(listaAux)] = id;
	    	nuevosAccesibles(d, primeroLista(listaAux), id, colecciones);
	    };
		restoLista(listaAux);
	};
}

int cantidadPalabraClaveEnArticulo (Deposito d, int a, char * p)
/*	Devuelve la cantidad asociada a la palabra clave 'p' en el artículo 'a'.
    Precondición: estaAsociadoArticuloPalabraClave (d, a, p). */
{
	ABB_T abb = d->abbPalabrasClave;
	while (strcmp(palabraClaveABB(abb), p) != 0) {
		if (strcmp(p, palabraClaveABB(abb)) > 0)
			abb = arbolDerecho(abb);
		else abb = arbolIzquierdo(abb);
	};

	return prioridadColaPrioridad(d->hash[a].colaPalabrasClave, abb);
}

void destruirDeposito (Deposito &d)
/*	Libera la memoria asignada a 'd'. */
{
	for (int i = 0 ; i < d->total_articulos ; i++) {
		destruirColaPrioridad(d->hash[i].colaPalabrasClave);
		destruirLista(d->hash[i].listaAdy);
	};

	delete [] d->hash;
	destruirABB(d->abbPalabrasClave);

	delete d;
}