#define ESPACIO '0'

//esto enumera los movimientos disponibles en el juego en relación con el personaje en blanco
typedef enum mov {
	ARRIBA, ABAJO, IZQ, DERECHA, //valores para subir, bajar, izquierda, derecha, respectivamente
	NO_APLICA         //valor asignado para los estados de entrada inicial y objetivo
} mov;

typedef struct Estado {
	mov accion;           //acción que resultó en `este` estado del tablero
	char tablero[3][3];      //configuración del tablero resultante después de aplicar la acción
} Estado;

/**
 * DESCRIPCIÓN:
 *    Esto crea un estado si `mov` es un movimiento válido del estado del tablero` estado`.
 * Parámetros
 *    estado: puntero al estado inicial
 *    movr: acción que se aplicará al estado dado
 * RETURN:
 *    Devuelve un puntero a un nuevo `Estado` después de aplicar el movimiento. Devuelve NULL
 *    Al fracaso.
**/
Estado* crearEstado(Estado* estado, mov mov) {
	Estado* newEstado = malloc(sizeof(Estado));

	//copia la configuración de la placa de `estado` a` newEstado`
	//mientras busca la fila y la columna del carácter en blanco
	char i, j;       
	char fil, col;   

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (estado->tablero[i][j] == ESPACIO) {
				fil = i;
				col = j;
			}

			newEstado->tablero[i][j] = estado->tablero[i][j];
		}
	}

	//prueba si las coordenadas son válidas después de la traducción en función del movimiento
	//si es así, intercambie los valores del tablero en cuestión para reflejar el movimiento
	if (mov == ARRIBA && fil - 1 >= 0) {
		char temp = newEstado->tablero[fil - 1][col];
		newEstado->tablero[fil - 1][col] = ESPACIO;
		newEstado->tablero[fil][col] = temp;
		newEstado->accion = ARRIBA;
		return newEstado;
	}
	else if (mov == ABAJO && fil + 1 < 3) {
		char temp = newEstado->tablero[fil + 1][col];
		newEstado->tablero[fil + 1][col] = ESPACIO;
		newEstado->tablero[fil][col] = temp;
		newEstado->accion = ABAJO;
		return newEstado;
	}
	else if (mov == IZQ && col - 1 >= 0) {
		char temp = newEstado->tablero[fil][col - 1];
		newEstado->tablero[fil][col - 1] = ESPACIO;
		newEstado->tablero[fil][col] = temp;
		newEstado->accion = IZQ;
		return newEstado;
	}
	else if (mov == DERECHA && col + 1 < 3) {
		char temp = newEstado->tablero[fil][col + 1];
		newEstado->tablero[fil][col + 1] = ESPACIO;
		newEstado->tablero[fil][col] = temp;
		newEstado->accion = DERECHA;
		return newEstado;
	}

	free(newEstado);
	return NULL;
}

/**
 * DESCRIPCIÓN: Esto libera memoria de `s` y se reasigna a NULL
**/
void deleteEstado(Estado** estado) {
	free(*estado);
	estado = NULL;
}

/**
 * DESCRIPCIÓN:
 *    Esto verifica si los dos estados dados coinciden entre sí. Una alternativa
 *    la forma es verificar si la distancia de Manhattan entre estos dos estados es cero, pero
 *    tomaría una cantidad de tiempo y recursos computacionales más significativos
 * Parámetros
 *    estado1 -estado para hacer coincidir contra `estado2`
 *    estado2 -estado para coincidir con `estado1`
 * RETURN:
 *    Devuelve 1 si los estados coinciden, 0 de lo contrario.
**/
char estadoHallado(Estado const* estadoPrueba, Estado const* estadoMeta) {
	char fil = 3, col;

	while (fil--) {
		col = 3;
		while (col--) {
			if (estadoPrueba->tablero[fil][col] != estadoMeta->tablero[fil][col])
				return 0;
		}
	}

	return 1;
}
