//declaraciones a futuro
typedef struct Nodo Nodo;
typedef struct NodoList NodoList;

/**
 * DESCRIPCIÓN:
 *    El nodo en la lista vinculada. Tenga en cuenta que, como convención, lo anterior
 *    el nodo del encabezado de la lista es NULL y también el siguiente nodo de la lista
 *    cola.
**/
typedef struct ListNodo {
	Nodo* actualNodo;
	struct ListNodo* prevNodo; //el nodo antes de la instancia `this`
	struct ListNodo* sigNodo; //el siguiente nodo en la lista vinculada
} ListNodo;

/**
 * DESCRIPCIÓN:
 *    Contiene la lista vinculada de nodos, así como otra información de la lista.
**/
struct NodoList {
	unsigned int nodoCount;    //el número de nodos en la lista
	ListNodo* head;            //puntero al primer nodo de la lista
	ListNodo* tail;            //puntero al último nodo de la lista
};

/**
 *DESCRIPCIÓN:
 *    Una estructura para mantener la solución.
**/
typedef struct RutaSolucion {
	mov accion;
	struct RutaSolucion* sig;
} RutaSolucion;

/**
 * DESCRIPCIÓN:
 *    Esta función se utiliza para desasignar una lista de tipo `RutaSolucion`.
**/
void deleteSolucion(RutaSolucion** list) {
	RutaSolucion* sig;
	while (*list) {
		sig = (*list)->sig;
		free(*list);
		*list = sig;
	}
	*list = NULL;
}

/**
 * DESCRIPCIÓN:
 *    Su función empuja un nodo a la lista de nodos.
 * PARÁMETRO:
 *    nodo -el nodo para agregar a la lista
 *    lista: un puntero al puntero de lista para agregar el nodo
 * RETURN:
 *   Devuelve 1 en caso de éxito, 0 en caso de error.
**/
char pushNodo(Nodo* nodo, NodoList** const list) {
	if (!nodo)
		return 0;

	ListNodo* dNodo = malloc(sizeof(ListNodo));
	if (!dNodo)
		return 0;

	dNodo->actualNodo = nodo;

	if (*list && !(*list)->nodoCount) {
		(*list)->head = dNodo;
		(*list)->tail = dNodo;
		dNodo->sigNodo = NULL;
		dNodo->prevNodo = NULL;
		++(*list)->nodoCount;
		return 1;
	}

	if (*list == NULL) {
		*list = malloc(sizeof(NodoList));
		if (*list == NULL)
			return 0;

		(*list)->nodoCount = 0;
		(*list)->head = NULL;
		(*list)->tail = dNodo;
	}
	else {
		(*list)->head->prevNodo = dNodo;
	}

	dNodo->sigNodo = (*list)->head;
	dNodo->prevNodo = NULL;
	(*list)->head = dNodo;

	++(*list)->nodoCount;

	return 1;
}

/**
 * DESCRIPCIÓN:
 *    Esto separa el nodo al final de la lista. El anterior
 *    El nodo del siguiente nodo para separar se establecerá en NULL.
 * PARÁMETRO:
 *    lista -la lista para hacer estallar
 * RETURN:
 *    Devuelve la dirección del nodo despegado; NULL si la lista
 *    esta vacio.
**/
Nodo* popNodo(NodoList** const list) {
	if (!*list || (*list)->nodoCount == 0)
		return NULL;

	Nodo* sacado = (*list)->tail->actualNodo;
	ListNodo* prevNodo = (*list)->tail->prevNodo;

	//libera el nodo de la lista que apunta al nodo que se abrirá
	free((*list)->tail);

	if ((*list)->nodoCount == 1) {
		(*list)->head = NULL;
	}
	else {
		prevNodo->sigNodo = NULL;
	}

	(*list)->tail = prevNodo;
	--(*list)->nodoCount;
	return sacado;
}

/**
 * DESCRIPCIÓN:
 *    Esta función agrega una lista de nodos a `list`. Se conecta
 *    el nodo principal de la lista que se agregará, al final de la lista
 *    anexar a. Conectar una lista a sí mismo será ignorado. Después
 *    la conexión, `toAppend` se asignará a NULL. Desasignación de
 *    los nodos de `toAppend` se manejarán desde` list`. Esto es principalmente
 *    para evitar el puntero colgante o llamar gratis varias veces al
 *    misma dirección
 * Parámetros
 *    toAppend: la lista que se agregará
 *    list: la lista para agregar `a Append` en
**/
void pushList(NodoList** toAppend, NodoList* list) {
	//si alguna de las listas es NULL, el encabezado de la lista que se agregará es NULL,
	//o la lista apunta al mismo nodo inicial
	if (!*toAppend || !list || !(*toAppend)->head || (*toAppend)->head == list->head) {
		return;
	}

	//si la lista para agregar no tiene actualmente ningún elemento
	if (!list->nodoCount) {
		list->head = (*toAppend)->head;
		list->tail = (*toAppend)->tail;
	}
	else {
		//conecta las listas
		(*toAppend)->tail->sigNodo = list->head;
		list->head->prevNodo = (*toAppend)->tail;
		list->head = (*toAppend)->head;
	}

	//actualizar la información de la lista
	list->nodoCount += (*toAppend)->nodoCount;

	free(*toAppend);
	*toAppend = NULL;
}


