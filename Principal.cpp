/*
Programa principal de la tarea 2.

Laboratorio de Programacion 3.
InCo-FI-UDELAR
-------------------------------------------------------------------------------

Al comenzar la ejecución se pide la cantidad de artículos. Luego, para cada uno de ellos
se pide ingresar los id de los artículos referenciados, terminando en -1.
Luego se pide las palabras claves y sus cantidades para cada uno, terminando en -1.

Comandos disponibles:

	- salir
	Termina la ejecución

	- recrear
	Vuelve a crear el depósito, como al inicio de la ejecución

	- identificarColecciones [n] [palabra clave 1] [palabra clave 2] ... [palabra clave n]
	Llama a la operación identificarColecciones de OperacionesDeposito,
	con las palabras clave pasadas como parámetro.

*/

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "OperacionesDeposito.h"


// mensajes de salida
const char msg_bienvenida []	= "Tarea 2 - 2014 - Programacion 3.";
const char msg_final []			= "FIN.";

// nombres de comandos
const char cmnd_salir []								= "salir";
const char cmnd_pedirDeposito []						= "recrear";
const char cmnd_identificarColecciones []				= "identificarColecciones";

int cantidad_articulos;
Deposito d;

void pedirDeposito ()
{
	scanf ("%d", &cantidad_articulos);
	assert (cantidad_articulos >= 0);
	d = crearDeposito (cantidad_articulos);

	// leer aristas
	for (int u = 0; u < cantidad_articulos; u++)
	{
		int v;
		bool fin = false;
		while (! fin)
		{
			scanf ("%d", &v);
			assert ((v == -1) || ((v != u) && (0 <= v) && (v < cantidad_articulos)) );
			if (v == -1)
			{
				fin = true;
			}
			else
			{
				agregarReferencia (d, u, v);
			}
		}
	}

	for (int u = 0; u < cantidad_articulos; u++)
	{
		char palabra_clave[MAX_STR];
		int cantidad;
		bool fin = false;
		while (! fin)
		{
			scanf ("%s %d", palabra_clave, &cantidad);
			if (strcmp (palabra_clave, "-1") == 0)
			{
				fin = true;
			}
			else
			{
				insertarPalabraClave (d, palabra_clave);
				asociarArticuloPalabraClave (d, u, palabra_clave, cantidad);
			}
		}
	}
}

void imprimirReferenciasDeposito (Deposito d)
{
	for (int a = 0; a < cantidadArticulos (d); a++)
	{
		for (ListaOrd refs = referencias (d, a); ! esVaciaLista (refs); restoLista(refs))
		{
			printf ("%d ", primeroLista (refs));
		}
		printf ("\n");
	}
}

int main()
{
	printf ("%s\n\n", msg_bienvenida);     

	char buffer [MAX_STR];

	pedirDeposito ();

	bool fin = false;
	while (! fin)
	{
		printf (">");
		scanf ("%s", buffer);
		if (strcmp (buffer, cmnd_identificarColecciones) == 0)
		{
			int cantidad_palabras_identificadoras;
			scanf (" %d", &cantidad_palabras_identificadoras);

			char* * palabras_identificadoras = new char* [cantidad_palabras_identificadoras];

			for (int i = 0; i < cantidad_palabras_identificadoras; i++)
			{
				palabras_identificadoras [i] = new char [MAX_STR];
				scanf (" %s", palabras_identificadoras [i]);
			}

			char* * identificaciones;
			int tamanio_arreglo;

			identificarColecciones (d, palabras_identificadoras, cantidad_palabras_identificadoras,
					identificaciones, tamanio_arreglo);

			assert (identificaciones != NULL);

			for (int i = 0; i < tamanio_arreglo; i++)
			{
				if (identificaciones [i] == NULL)
				{
					printf ("%d -> \n", i);
				}
				else
				{
					printf ("%d -> %s\n", i, identificaciones [i]);
				}
			}

			delete [] identificaciones;

			for (int i = 0; i < cantidad_palabras_identificadoras; i++)
			{
				delete [] palabras_identificadoras [i];
			}

			delete [] palabras_identificadoras;
		}
		else if (strcmp (buffer, cmnd_pedirDeposito) == 0)
		{
			destruirDeposito (d);
			pedirDeposito ();
		}
		// FIN
		else if (strcmp (buffer, cmnd_salir) == 0)
		{
			fin = true;
			printf ("%s\n", msg_final);
		}
		// ERROR
		else 
		{
			printf ("%s: Comando no reconocido \n", buffer);
			exit (1);
		}
	}
	destruirDeposito (d);
	return 0;
}
