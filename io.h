//variables externas declaradas desde main.c
extern unsigned int nodosExpandidos;
extern unsigned int nodosGen;
extern unsigned int solucionTam;
extern double runtime;

/*
 
  print("  ___    ____  _   _ ___________     _____ \n");
  print(" ( _ )  |  _ \\| | | |__  /__  / |   | ____|\n");
  print(" / _ \\  | |_) | | | | / /  / /| |   |  _|  \n");
  print("| (_) | |  __/| |_| |/ /_ / /_| |___| |___ \n");
  print(" \\___/  |_|    \\___//____/____|_____|_____|\n");
                                             
 
*/

/**
 * DESCRIPCIÓN: Esto muestra el arte ASCII '8-Puzzle Solver' en la pantalla
**/
void bienvenida(void) {
	printf("  ___    ____  _   _ ___________     _____ \n");
	printf(" ( _ )  |  _ \\| | | |__  /__  / |   | ____|\n");
	printf(" / _ \\  | |_) | | | | / /  / /| |   |  _|  \n");
	printf("| (_) | |  __/| |_| |/ /_ / /_| |___| |___ \n");
	printf(" \\___/  |_|    \\___//____/____|_____|_____|\n");
}

/**
 * DESCRIPCIÓN:
 *    Esta función llena el "estado" con números no repetidos del 0 al 9
**/
void llenarEstado(Estado* const estado) {
	estado->accion = NO_APLICA;
	char fil, col;
	int caracter;

	//flags para validación de entrada
	char esNumUsad[9] = { 0 };

	for (fil = 0; fil < 3; ++fil) {
		for (col = 0; col < 3; ++col) {
			printf("    tablero[%i][%i]: ", fil, col);

			//para evitar escanear nueva línea desde la secuencia de entrada
			scanf_s("%i", &caracter);

			//comprueba si la entrada es un carácter en blanco o es un número mayor que 0 y menor que 9
			if (caracter >= 0 && caracter < 9) {
				//verifica si la entrada se repite
				if (!esNumUsad[caracter]) {
					estado->tablero[fil][col] = caracter + '0';
					esNumUsad[caracter] = 1;
				}
				else {
					printf("   ERROR: el número% c ya está en uso. Intente nuevamente con diferentes entradas.\n", caracter);
					--col;
				}
			}
			else {
				printf("    ERROR: entrada inválida. Ingrese un número del 0 al 8.\n");
				--col;
			}
		}
	}
	printf("\n");
}

/**
 * DESCRIPCIÓN: Muestra el contenido de `placa` a la salida estándar
**/
void imprimirTablero(char const tablero[][3]) {
	char fil, col;

	for (fil = 0; fil < 3; ++fil) {
		printf("+---+---+---+\n");
		for (col = 0; col < 3; ++col) {
			printf("| %c ", tablero[fil][col]);
		}
		printf("|\n");
	}
	printf("+---+---+---+\n");
}

/**
 * DESCRIPCIÓN:
 *    Esta función interpreta instrucciones numéricas del movimiento a realizar,
 *    es su contraparte verbal que se mostrará en la pantalla.
 * PARÁMETRO:
 *    solución: la ruta de la solución que consiste en una lista de nodos desde la raíz
 *               a la meta
**/
void imprimirSolucion(struct RutaSolucion* path) {
	//comprobar si existe solución
	if (!path) {
		printf("No se encontró solución.\n");
		return;
	}

	//si el estado inicial ya es el estado objetivo
	if (!path->sig) {
		printf("No se necesitan movimientos. El estado inicial ya es el estado objetivo.\n");
		return;
	}

	printf("SOLUCIÓN: (Relativa al carácter espacial)\n");

	//usará hashmap para acelerar un poco el proceso
	char* mov[4] = { "ARRIBA", "ABAJO", "IZQ", "DERECHA" };
	int cont = 1;

	//se saltará el primer nodo ya que representa el estado inicial sin acción
	for (path = path->sig; path; path = path->sig, ++cont) {
		printf("%i. mov %s\n", cont, mov[path->accion]);
	}

	printf(
		"DETALLES\n"
		" - Longitud de la solución : %i\n"
		" - Nodos expandidos        : %i\n"
		" - Nodos generados         : %i\n"
		" - Tiempo de ejecución     : %g milliseconds\n"
		" - Memoria usada           : %i bytes\n", //solo contando los `Nodos asignados
		solucionTam, nodosExpandidos, nodosGen, runtime, nodosGen * sizeof(Nodo));
}
