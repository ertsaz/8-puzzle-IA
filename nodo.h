extern unsigned int nodosGen; //declarado desde main.c

/**
 * DESCRIPCIÓN: define la estructura de nodo utilizada para crear un árbol de búsqueda
**/
typedef struct Nodo Nodo;
struct Nodo {
	Estado* estado;      //estado designado para un nodo
	Nodo* padre;       //nodo principal
	NodoList* hijo; //lista de nodos secundarios
};

/**
 * DESCRIPCIÓN:
 *   Esta función crea un nodo, lo inicializa con el
 *    siguientes parámetros y establece sus elementos secundarios en NULL.
 * Parámetros
 *    d -profundidad del nodo
 *    h -valor heurístico del nodo
 *    s -estado asignado al nodo
 *    p -nodo padre
 * RETURN:
 *    Devuelve un puntero `Nodo` al nodo asignado dinámicamente,
 *    o NULL en caso de falla.
**/
Nodo* crearNodo(Estado* s, Nodo* p) {
	Nodo* newNodo = malloc(sizeof(Nodo));
	if (newNodo) {
		newNodo->estado = s;
		newNodo->padre = p;
		newNodo->hijo = NULL;
		++nodosGen; //contador de actualizaciones
	}
	return newNodo;
}

/**
 * DESCRIPCIÓN:
 *    Esta función se utiliza para desasignar todos los nodos en un árbol, incluidos
 *    El nodo raíz.
 * PARÁMETRO:
 *    nodo -el nodo raíz del árbol para desasignar
**/
void destroyTree(Nodo* nodo) {
	if (nodo->hijo == NULL) {
		free(nodo->estado);
		free(nodo);
		return;
	}

	ListNodo* listNodo = nodo->hijo->head;
	ListNodo* sigNodo;

	while (listNodo) {
		sigNodo = listNodo->sigNodo;
		destroyTree(listNodo->actualNodo);
		listNodo = sigNodo;
	}

	//free (nodo-> estado);
	free(nodo->hijo);
	free(nodo);
}

/**
 * DESCRIPCIÓN:
 *    Esta función 'expande' el nodo, lo vincula a sus hijos y actualiza el
 *    Contador de expansión.
 * PARÁMETRO:
 *    padre -el nodo para expandir y buscar hijos
 *    estadoMeta: puntero al estado objetivo donde los valores heurísticos de cada niño
 *                estar basado en
 * RETURN:
 *    Devuelve un puntero a `NodoList` en caso de éxito, NULL en caso de error.
**/
NodoList* getChildren(Nodo* padre, Estado* estadoMeta) {
	NodoList* hijoPtr = NULL;
	Estado* estadoPrueba = NULL;
	Nodo* child = NULL;

	//intenta crear estados para cada movimiento y agrega a la lista de hijos si es verdadero
	if (padre->estado->accion != ABAJO && (estadoPrueba = crearEstado(padre->estado, ARRIBA))) {
		child = crearNodo(estadoPrueba, padre);
		pushNodo(child, &padre->hijo);
		pushNodo(child, &hijoPtr);
	}
	if (padre->estado->accion != ARRIBA && (estadoPrueba = crearEstado(padre->estado, ABAJO))) {
		child = crearNodo(estadoPrueba, padre);
		pushNodo(child, &padre->hijo);
		pushNodo(child, &hijoPtr);
	}
	if (padre->estado->accion != DERECHA && (estadoPrueba = crearEstado(padre->estado, IZQ))) {
		child = crearNodo(estadoPrueba, padre);
		pushNodo(child, &padre->hijo);
		pushNodo(child, &hijoPtr);
	}
	if (padre->estado->accion != IZQ && (estadoPrueba = crearEstado(padre->estado, DERECHA))) {
		child = crearNodo(estadoPrueba, padre);
		pushNodo(child, &padre->hijo);
		pushNodo(child, &hijoPtr);
	}

	return hijoPtr;
}

