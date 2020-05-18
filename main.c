#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "estado.h"
#include "lista.h"
#include "nodo.h"
#include "io.h"

unsigned int nodosExpandidos;  //número de nodos expandidos
unsigned int nodosGen; //número de nodos generados
unsigned int solucionTam; //número de movimientos en solución
double runtime;              //tiempo transactualido (en milisegundos)

RutaSolucion* BFS_search(Estado*, Estado*);

int main(void) {
	bienvenida();           

	Estado inicial;           //estado inicial de la placa
	Estado estadoMeta;         //configuración de la portería

	//ruta de solución de cada método de búsqueda
	RutaSolucion* bfs;

	//ingresa el estado inicial de la placa
	printf("ESTADO inicial:\n");
	llenarEstado(&inicial);

	//input the meta estado
	printf("\nESTADO meta:\n");
	llenarEstado(&estadoMeta);

	printf("Estado del Tablero inicial:\n");
	imprimirTablero(inicial.tablero);

	printf("Estado del Tablero Meta::\n");
	imprimirTablero(estadoMeta.tablero);

	bfs = BFS_search(&inicial, &estadoMeta);
	printf("\n------------------------- USING BFS ALGORITHM --------------------------\n");
	imprimirSolucion(bfs);

	//free resources
	deleteSolucion(&bfs);
	system("pause");
	return 0;
}

/**
 * DESCRIPCIÓN:
 *    Nuestra implementación de búsqueda de primer orden.
 * Parámetros
 *    inicial -dirección al estado inicial
 *    objetivo -dirección al estado objetivo
 * RETURN:
 *    Devuelve la solución en una lista vinculada; NULL si no se encuentra la solución.
**/
RutaSolucion* BFS_search(Estado* inicial, Estado* meta) {
	NodoList* cola = NULL;
	NodoList* listahijo = NULL;
	Nodo* nodo = NULL;

	//iniciar temporizador
	clock_t inicio = clock();

	//inicializar la cola con el nodo raíz del árbol de búsqueda
	insertarNodo(crearNodo(inicial, NULL), &cola);
	Nodo* raiz = cola->head->actualNodo; //for deallocating the generated tree

	//mientras haya un nodo en la cola para expandir
	while (cola->nodoCount > 0) {
		//abre el último nodo (cola) de la cola
		nodo = sacarNodo(&cola);

		//si el estado del nodo es el estado objetivo
		if (estadoHallado(nodo->estado, meta))
			break;

		//de lo contrario, expande el nodo y actualiza el contador de nodos expandidos
		listahijo = optenerlistahijo(nodo, meta);
		++nodosExpandidos;

		//agrega los listahijos del nodo a la cola
		pushList(&listahijo, cola);
	}

	//determina el tiempo transactualido
	runtime = (double)(clock() - inicio) / CLOCKS_PER_SEC;

	//obtener la ruta de la solución en orden desde la raíz, si existe
	RutaSolucion* pathHead = NULL;
	RutaSolucion* newPathNodo = NULL;

	while (nodo) {
		newPathNodo = malloc(sizeof(RutaSolucion));
		newPathNodo->accion = nodo->estado->accion;
		newPathNodo->sig = pathHead;
		pathHead = newPathNodo;

		//actualizar la longitud de la solución y pasar al siguiente nodo
		++solucionTam;
		nodo = nodo->padre;
	}

	--solucionTam; //descontar el nodo raíz

	//desasignar el árbol generado
	destroyTree(raiz);

	return pathHead;
}