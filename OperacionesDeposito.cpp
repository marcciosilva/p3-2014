/* 4547599 4012543 4466345 */

/*
Operaciones sobre Deposito.

Laboratorio de Programación 3.
InCo-FI-UDELAR
*/

#include "Cola.h"
#include "Deposito.h"
#include "ListaOrd.h"
#include <limits.h> // Proporciona INT_MAX.
#include <stdlib.h>
#include <string.h>

struct AuxListaColecciones {
	ListaOrd sublista;
	AuxListaColecciones* sig;
};

typedef AuxListaColecciones * listaColecciones;


struct AuxTupla {
	int* colecciones;
	int valor;
};

typedef AuxTupla * Tupla;

/*******************************************
		PROCEDIMIENTOS AUXILIARES
********************************************/
bool esVaciaListaColecciones (listaColecciones lc)
{
	return lc == NULL;
}

void insertarSublista (ListaOrd lst, listaColecciones &l)
{
	if (esVaciaListaColecciones(l) || (not esVaciaListaColecciones(l) && (primeroLista(l->sublista) > primeroLista(lst)))) {
		listaColecciones aux = new AuxListaColecciones;
		aux->sublista = lst;
		aux->sig = l;
		l = aux;
	} else if (primeroLista(l->sublista) < primeroLista(lst)) {
		insertarSublista(lst, l->sig);
	};
}

void dfsColecciones (Deposito d, int a, int* &marcados, ListaOrd &l)
{
	marcados[a] = 1;
	//inserto en l
	insLista(a, l);

	ListaOrd adyacentes = referencias(d, a);

	while (not esVaciaLista(adyacentes)) {
		if (marcados[primeroLista(adyacentes)] == 0)
			dfsColecciones(d, primeroLista(adyacentes), marcados, l);
		restoLista(adyacentes);
	};
}

int BFS (Deposito d, int a)
{
	Cola Q;
	ListaOrd listaAux;
	int v, nodoAux;
	int cantArticulosDeposito = cantidadArticulos(d);
	int* dist = new int[cantArticulosDeposito];
	bool* marcas = new bool[cantArticulosDeposito];

	//Inicializo los vectores distancia y marcas
	for (int i = 0 ; i < cantArticulosDeposito ; i++){
		dist[i] = 0;
		marcas[i] = 0;
	};

	// Creo estructuras auxiliares
	crearCola(Q);
	encolar(a, Q);

	marcas[a] = 1;

	while (not esVaciaCola(Q)) {
		v = frente(Q);
		desencolar(Q);
		// Procesar v
		listaAux = referencias(d, v);
		while (not esVaciaLista(listaAux)) {
			nodoAux = primeroLista(listaAux);
			if (!marcas[nodoAux] ) {
				encolar(nodoAux, Q);
				marcas[nodoAux] = 1;
				dist[nodoAux] = dist[v] + 1;
			};
			restoLista(listaAux);
		};
	};

	//Busca la distancia máxima
	int separacionActual = 0;
	for (int i = 0; i < cantidadArticulos(d); ++i) {
		if (dist[i] > separacionActual)
			separacionActual = dist[i];
	};

	destruirCola(Q);
	delete [] dist;
	delete [] marcas;

	return separacionActual;
}

void destruirListaColecciones (listaColecciones &lc)
{
	if (not esVaciaListaColecciones(lc)) {
		destruirListaColecciones(lc->sig);
		destruirLista(lc->sublista);
		delete lc;
	};
}
/*******************************************
					FIN
********************************************/
int * colecciones (Deposito d);

int gradosDeSeparacion (Deposito d, bool* articulos_considerados)
/*	Devuelve los grados de separación entre un conjunto de artículos
    considerados. El artículo número i es considerado si y sólo si
    articulos_considerados[i] == true.
    De no poder llegar mediante referencias desde un artículo a otro,
    transitando solo por artículos considerados,
    se debe retornar INT_MAX, incluido de limits.h
    De haber uno o menos artículos considerados retornar 0.
	La operación se debe realizar en peor caso en O(n . m ), sinedo 'm' la
	cantidad de referencias entre los artículos de 'd' y 'n' la cantidad de
	artículos de 'd'.
	Precondición: el tamaño de 'articulos_considerados' es igual a
	la cantidad de artículos de 'd'. */
{
	int cantArticulosDeposito = cantidadArticulos(d);
	int cantArticulosConsiderados = 0;

	// Calculo la cantidad de artículos considerados
	for (int i = 0; i < cantArticulosDeposito; ++i)	{
		if(articulos_considerados[i])
		 	cantArticulosConsiderados++;
	};

	// Caso borde 0 o 1 solo artículo.
	if(cantArticulosConsiderados < 2) {
		return 0;
	} else {
		// Calculo mismaCFC
		bool mismaCFC = true;
		int* vector_colecciones = colecciones(d);
		int j = 0;

		while(not articulos_considerados[j])
		    j++;

		int cfc_nro = vector_colecciones[j];

		for (j++; j < cantArticulosDeposito; j++) {
			if (articulos_considerados[j] && not (cfc_nro == vector_colecciones[j]))
				mismaCFC = false;
		};

		if (mismaCFC == false) {
			return INT_MAX;
		} else {
			// Construimos un grafo de cubrimiento con los articulos_considerados
			Deposito dCubrimiento = crearDeposito(cantArticulosDeposito);
			ListaOrd listaAux;
			// Agrego a dCubrimiento las referencias existentes entre los articulos considerados.
			for (int i = 0 ; i < cantArticulosDeposito ; i++) {
				listaAux = referencias(d, i);
				while(not esVaciaLista(listaAux)) {
					if (articulos_considerados[i] && articulos_considerados[primeroLista(listaAux)]) {
						agregarReferencia(dCubrimiento, primeroLista(listaAux), i);
					};
					restoLista(listaAux);
				};
			};

			// Algoritmo separación máxima
			int separacionMaxima = 0;

			for (int i = 0, separacionActual = 0; i < cantArticulosDeposito; ++i) {
				if(articulos_considerados[i]) {
					separacionActual = BFS(dCubrimiento, i);
					if (separacionActual > separacionMaxima) {
						separacionMaxima = separacionActual;
					};
				};
			};

			return separacionMaxima;
		};
	};
}

int * colecciones (Deposito d)
/*	Devuelve las colecciones de 'd', cada una en una lista diferente.
	La salida de esta operación debe ser un array en donde
	para la posición i se encuentra el número de colección a la que
	pertenece el artículo i.

# Formato de la salida

	Las colecciones se identifican con enteros de 0 a (k-1),
	siendo k la cantidad de colecciones. Una colección A tiene
	un identificador menor que otra colección B si y sólo si
	hay un artículo de A cuyo número es menor que todos los
	números de los artículos de B.

	Por ejemplo, dado el depósito que tiene los
	artículos 0, 1, 2 y 3, cuyas colecciones son:

	A = {1}
	B = {0, 2}
	C = {3}

	La salida debe ser: 0 1 0 2

	Observar que 0 2 0 1, 1 0 1 2, 1 2 1 0, 2 0 2 1, 2 1 2 0
	también agrupan correctamente las colecciones,
	pero no cumplen la forma de orden solicitada.

	La operación se debe realizar en peor caso en O(m + n), sinedo 'm' la
	cantidad de referencias entre los artículos de 'd' y 'n' la cantidad de
	artículos de 'd'. */
{
	Pila verticesPost = dfsPostOrden(d);
	Deposito dTrans = transpuesto(d);

	//armar DFS en dTrans, siguiendo el orden de la pila desde el tope
	int* marcados = new int[cantidadArticulos(d)];
	for (int i = 0 ; i < cantidadArticulos(d) ; i++) {
		marcados[i] = 0;
	};

	//creo listaColecciones para almacenar colecciones
	listaColecciones l = NULL;
	while (not esVaciaPila(verticesPost)) {
		if (marcados[cima(verticesPost)] == 0) {
			ListaOrd listaColeccion;
			crearLista(listaColeccion);
			dfsColecciones(dTrans, cima(verticesPost), marcados, listaColeccion);
			insertarSublista(listaColeccion, l);
		};
		desapilar(verticesPost);
	};

	//	Al salir del while, voy a tener una listaColecciones de listas tipo
	//	ListaOrd, donde cada una corresponde a una colección
	//	ahora basta con irme fijando cuál es el primer elemento de cada sublista
	//	y voy asignando identificadores para cada colección
	int* vector_salida = new int[cantidadArticulos(d)];

	listaColecciones aux_l = l;
	ListaOrd aux_sublista;

	for (int i = 0 ; not esVaciaListaColecciones(aux_l) ; i++) {
		aux_sublista = aux_l->sublista;
		while (not esVaciaLista(aux_sublista)) {
			vector_salida[primeroLista(aux_sublista)] = i;
			restoLista(aux_sublista);
		};
		aux_l = aux_l->sig;
	};

	//destruyo la estructura de listaColecciones
	destruirListaColecciones(l);

	return vector_salida;
}

int cantidadArticulosConMismaPalabraClaveMasFrecuente (Deposito d, int a)
/*	Devuelve la cantidad de artículos de 'd' cuya palabra clave más
	frecuente es 'key', siendo 'key' la palabra clave más frecuente del
	artículo 'a' (si más de una cumple esa condición se elije cualquiera de
	ellas).
	La operación se debe realizar, en promedio, en O(c1), siendo 'c1' la
	cantidad de artículos asociados a 'key'.
    Precondición: 0 <= a < cantidad de artículos de 'd'.
    Precondición: el artículo 'a' tiene al menos una palabra clave. */
{
	int cantidad = 0;
	ABB_T abbKey = claveMasFrecuente(d, a);
	char* key = palabraClaveABB(abbKey);
	ListaOrd articulosAsociados = listaArticulosABB(abbKey);
	while (not esVaciaLista(articulosAsociados)) {
		char* key_comp = palabraClaveABB(claveMasFrecuente(d, primeroLista(articulosAsociados)));
		if (strcmp(key_comp, key) == 0)
			cantidad++;
		restoLista(articulosAsociados);
	};

	return cantidad;
}

int referenciasConMismaPalabraMasFrecuente (Deposito d, int a)
/*	Devuelve la cantidad de artículos de 'd' hacia los que tiene referencia
	directa el artículo 'a', y están asociados a la palabra clave más
	frecuente de 'a' (si más de una cumple esa condición se elije cualquiera de
	ellas).
	La operación se debe realizar, en promedio, en O(r) siendo r la cantidad de
	referencias que hay en 'a'.
    Precondición: 0 <= a < cantidad de artículos de 'd'.
    Precondición: el artículo 'a' tiene al menos una palabra clave. */
{
	int cantidad = 0;
	char* palabraMasFrecuenteA = new char[MAX_STR];
	strcpy(palabraMasFrecuenteA, palabraClaveABB(claveMasFrecuente(d, a)));
	ListaOrd referenciasDeA = referencias(d, a);

	while (not esVaciaLista(referenciasDeA)) {
		if (estaAsociadoArticuloPalabraClave(d, primeroLista(referenciasDeA), palabraMasFrecuenteA))
			cantidad++;
		restoLista(referenciasDeA);
	};

	delete [] palabraMasFrecuenteA;
	return cantidad;
}

void BTColecciones (Tupla t, Tupla sol, bool * &marcados, int pos,
					int cantidad_palabras_identificadoras, int cantArticulos,
					int cantColecciones, int* * costos, int * poda, int * poda2);

void identificarColecciones (Deposito d, char* * palabras_identificadoras,
		int cantidad_palabras_identificadoras, char* * &identificaciones,
		int &tamanio_arreglo)
/*	Asocia palabras identificadoras a las colecciones, buscando maximizar
	las suma de las apariciones de esas palabras en los artículos de las
	colecciones.
	Cada colección tiene hasta una palabra identificadora asignada y
	una palabra identificadora tiene hasta una colección asignada. Para que
	haya asignación entre una palabra identificadora 'p' y una colección 'c',
	'p' debe ser palabra identificadora de cada uno de los artículos de 'c'.
	La operación devuelve un array de palabras identificadoras, en donde en la
	posición 'i' se tiene la palabra identificadora asociada a la colección
	'i', según la numeración que se usa en la operación colecciones. Si una
	colección no tiene palabra identificadora, se le asocia NULL.
	La salida de esta función debe estar en el arreglo 'identificaciones', y
	en 'tamanio_arreglo' debe estar su tamaño.
	De haber más de una solución óptima, devolver cualquiera de ellas.
	Precondición: en 'palabras_identificadoras' hay
	'cantidad_palabras_identificadoras' elementos.
	Precondición: para todo 0 <= i < cantidad_palabras_identificadoras se
	cumple estaPalabraClave (d, palabras_clave [i]) */
{
	int* articulosPorColeccion = colecciones(d);
	int cantColecciones = 0;
	int cantArticulos = cantidadArticulos(d);

	// Quiero saber cuántas colecciones hay
	for (int i = 0; i < cantArticulos; ++i) {
		if (articulosPorColeccion[i] > cantColecciones)
			cantColecciones = articulosPorColeccion[i];
	};

	// Para que refleje correctamente la cantidad de colecciones existentes
	++cantColecciones;

	// Inicializo las estructuras para su primer llamado
	Tupla t = new AuxTupla;
	Tupla sol = new AuxTupla;

	t->valor = 0;
	sol->valor = 0;
	t->colecciones = new int[cantColecciones];
	sol->colecciones = new int[cantColecciones];

	for (int i = 0; i < cantColecciones; ++i) {
		t->colecciones[i] = cantidad_palabras_identificadoras;
		sol->colecciones[i] = cantidad_palabras_identificadoras;
	};
	// Si colecciones[i] = cantidad_palabras_identificadoras significa que la
	// colección 'i' tendrá asociado NULL.

	bool* marcados = new bool[cantidad_palabras_identificadoras + 1];
	for (int i = 0; i < cantidad_palabras_identificadoras + 1; ++i) {
	 	marcados[i] = false;
	} // marcados[] indica las palabras clave que ya utilicé

	// Matriz de costos
	int** costos = new int*[cantidad_palabras_identificadoras + 1];
	for (int i = 0; i < cantidad_palabras_identificadoras + 1; ++i)
	   	costos[i] = new int[cantColecciones];

	for (int i = 0; i < cantidad_palabras_identificadoras + 1; ++i) {
		for (int j = 0; j < cantColecciones; ++j) {
			costos[i][j] = 0;
		};
	};

	// Calculo la matriz de costos
	int k;
	bool asig_valida;
	for (int i = 0; i < cantidad_palabras_identificadoras; ++i) {
		for (int j = 0; j < cantColecciones; ++j) {
			k = 0;
			asig_valida = true;
			while(asig_valida && (k < cantArticulos)) {
			    if (articulosPorColeccion[k] == j) {
					if (not estaAsociadoArticuloPalabraClave(d, k, palabras_identificadoras[i])) {
						asig_valida = false;
					} else {
						costos[i][j] += cantidadPalabraClaveEnArticulo(d, k, palabras_identificadoras[i]);
					};
				};
			++k;
			};
			if (not asig_valida) {
				costos[i][j] = -1;
			};
		};
	};

	//---------------PREDICADO DE PODA------------------------
	//armo arreglo para el predicado de poda
	//cada celda indica la maxima cantidad de palabras que se le puede asignar
	//a una tupla armada desde esa coleccion en adelante
	int * poda;
	poda = new int[cantColecciones];
	for (int i = 0 ; i < cantColecciones ; i++){
		poda[i] = 0;
	}
	for (int i = cantColecciones - 1 ; i >= 0 ; i--){
		int cantidadMaxima = 0;
		for (int j = 0 ; j < cantidad_palabras_identificadoras ; j++){
			if (costos[j][i] > cantidadMaxima) cantidadMaxima = costos[j][i];
		}
		poda[i] = cantidadMaxima;
		//hasta aca tengo la cantidad maxima de palabras asignadas a cada coleccion
		//tengo que ajustar el arreglo para que cada celda involucre a las
		//decisiones posteriores
		if (i < cantColecciones - 1) poda[i] += poda[i+1];
	}
	//---------------FIN PREDICADO DE PODA------------------------

	//---------------PREDICADO DE PODA 2------------------------
	// Arreglo de tamaño 'cantidad_palabras_clave'
	// Cada celda guarda el máximo valor que cada palabra clave puede
	// aportar si fuera asignada a la 'mejor' colección para esa palabra clave
	int * poda2;
	poda2 = new int[cantidad_palabras_identificadoras];
	for (int i = 0 ; i < cantidad_palabras_identificadoras ; i++) {
		poda2[i] = 0;
	};
	for (int i = 0 ; i < cantidad_palabras_identificadoras ; i++) {
		for (int j = 0 ; j < cantColecciones ; j++) {
			if (costos[i][j] > poda2[i])
				poda2[i] = costos[i][j];
		};
	};
	//---------------FIN PREDICADO DE PODA------------------------



	BTColecciones (t, sol, marcados, 0, cantidad_palabras_identificadoras,
					cantArticulos, cantColecciones, costos, poda, poda2);

	// Procesar solución
	tamanio_arreglo = cantColecciones;
	identificaciones = new char*[cantColecciones];

	for (int i = 0; i < cantColecciones; ++i) {
		identificaciones[i] = NULL;
	};

	for (int i = 0; i < cantColecciones; ++i) {
		if (sol->colecciones[i] != cantidad_palabras_identificadoras) {
			identificaciones[i] = palabras_identificadoras[sol->colecciones[i]];
		};
	};

	// Libero memoria de las estructuras auxiliares
	for (int i = 0; i < cantidad_palabras_identificadoras + 1; ++i)
		delete [] costos [i];
	delete [] costos;

	delete [] poda;
	delete [] poda2;
	delete [] marcados;
	delete [] t-> colecciones;
	delete [] sol->colecciones;
	delete t;
	delete sol;

}

void BTColecciones (Tupla t, Tupla sol, bool * &marcados, int pos,
					int cantidad_palabras_identificadoras, int cantArticulos,
					int cantColecciones, int* * costos, int * poda, int * poda2)
{
	for (int i = 0; i < cantidad_palabras_identificadoras + 1; ++i) {
		if (not marcados[i]) {
			if (costos[i][pos] != -1) {
				if (i < cantidad_palabras_identificadoras)
					marcados[i] =  true;
					t->colecciones[pos] = i;
					t->valor += costos[i][pos];
			};
			if (pos == cantColecciones - 1) {
				if (t->valor > sol->valor) {
					sol->valor = t->valor;
					for (int i = 0; i < cantColecciones; ++i) {
						sol->colecciones[i] = t->colecciones[i];
					};
				};
			} else {
				// Acá iría el predicado de poda
				if (t->valor + poda[pos+1] > sol->valor) {
					int suma_poda2 = 0;
					for (int i = 0; i < cantidad_palabras_identificadoras; ++i) {
						if (not marcados[i]) {
							suma_poda2 += poda2[i];
						};
					};
					if (t->valor + suma_poda2 > sol->valor) {
						BTColecciones (t, sol, marcados, pos + 1, cantidad_palabras_identificadoras,
								cantArticulos, cantColecciones, costos, poda, poda2);
					};
				};
			};
			marcados[i] =  false;
			if (costos[i][pos] != -1 && i < cantidad_palabras_identificadoras)
				t->valor -= costos[i][pos];
		};
	};
}
