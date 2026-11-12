/**
 * @file abb.c
 * @brief Funciones de árboles binarios de búsqueda (ABB) de salas
 *
 * Cada nodo del árbol guarda una sala y sus dos hijos. El orden lo da el
 * ID: en el subárbol izquierdo de un nodo están las salas de menor ID
 * y en el derecho las de mayor ID, por lo que no puede haber dos salas con
 * el mismo ID.
 *
 * Un árbol vacío es un puntero nulo. Por eso las funciones que pueden cambiar
 * la raíz (abb_insert y abb_delete_tree) retornan el árbol resultante y se
 * usan siempre de la forma ABB = abb_insert(P, ABB).
*/

#include "abb.h"
#include "salas.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

//==============================================================================
//        FUNCIONES DE INICIALIZACION
//==============================================================================

/**
 * @brief Inserta una sala en el ABB, segun su ID
 *
 * Una sala de menor ID que el del nodo actual se inserta a la izquierda y
 * una de mayor ID a la derecha. El árbol pasa a ser el dueño de los strings de
 * la sala, por lo que quien llama nunca debe liberarla después de insertarla.
 *
 * No se permiten IDs repetidas: si ya existe una sala con la misma ID se
 * imprime "Error" y se libera la sala entregada. Lo mismo ocurre si no hay
 * memoria para el nodo. Si la sala es inválida (al menos un miembro string en
 * NULL, es decir, un Crear_Sala fallido) se imprime "Error" y el árbol queda
 * intacto.
 *
 * @param S Sala a insertar
 * @param T ABB donde se debe insertar la sala
 * @return arbol_de_busqueda Referencia al ABB con la sala insertada
 */
arbol_de_busqueda ABB_Insertar_Nodo(sala S, arbol_de_busqueda T)
{
	if(S.nombre == NULL || S.descripcion == NULL || S.tipo == NULL || S.tesoro == NULL || S.enemigo == NULL)
	{
		printf("Error: Al menos un miembro string de la sala nulo\n");
		return T;
	}

	if(T == NULL) // Inserta el elemento en la posicion disponible si es NULL.
	{
		T = malloc(sizeof(struct nodo));
		if(T == NULL)
		{
			printf("Out of memory!\n");
			Liberar_Sala(S);
			return T;
		}
		T->sala = S;
		T->izquierdo = NULL;
		T->derecho = NULL;
		return T;
	}

	if(S.id == ABB_Obtener_ID_Por_Posicion(T))
	{
		printf("Error: El ID comparado es igual al de la sala al ingresar\n");
		Liberar_Sala(S);
		return T;
	}

	if(S.id > ABB_Obtener_ID_Por_Posicion(T))
	{
		T->derecho = ABB_Insertar_Nodo(S, T->derecho);
		return T;
	}
	else
	{
		T->izquierdo = ABB_Insertar_Nodo(S, T->izquierdo);
		return T;
	}
}

/**
 * @brief Carga en el ABB los datos de "mazmorra.txt"
 *
 * Si no se encuentra exactamente una sala de tipo INICIO, se indica error y
 * termina el programa.
 * Si se encuentran salas con IDs repetidos, se conserva unicamente la
 * primera sala cargada.
 * Si no hay memoria para un nodo, se libera la memoria asignada y termina el
 * programa.
 * Si la sala es inválida (al menos un miembro string en
 * NULL, es decir, un Crear_Sala fallido) se imprime "Error" y el árbol queda
 * intacto.
 *
 * @param S Sala a insertar
 * @param T ABB donde se debe insertar la sala
 * @return arbol_de_busqueda Referencia al ABB con la sala insertada
 */
arbol_de_busqueda ABB_Cargar_Habitaciones_Visibles(arbol_de_busqueda T)
{
	FILE* archivo;
	int leer;
	int cont_salas = 0;
	char caracter;
	//char string[10];

	// Variables para grabar los valores leidos de mazmorras.txt, y luego copiar en una sala individual.
	int id_sala;
	char nombre_sala[21];
	char descripcion_sala[50];
	char tipo_sala[11];
	char tesoro_sala[50];
	char enemigo_sala[50];
	char oculta_sala;

	archivo = fopen("mazmorra.txt", "r");
	if(archivo == NULL)
	{
		printf("Error de ABB_Cargar_Arbol: No se pudo abrir mazmorra.txt\n");
		return T;
	}

	// Saltar las lineas de formato
	for(int i = 0; i < 3; i++)
	{
		do 
		{
			caracter = fgetc(archivo);
		}
		while(caracter != '\n');
	}

	/*caracter = fgetc(archivo);
	fseek(archivo, -1, SEEK_CUR);
	fgets(string, 10, archivo);
	printf("%s", string);*/

	while((caracter = fgetc(archivo)) != '#')
	{
		fseek(archivo, -1, SEEK_CUR);
		printf("oliwi\n");
		leer = fscanf(archivo, "%d|%20[^|]|%49[^|]|%10[^|]|%49[^|]|%49[^|]|%c", &id_sala, nombre_sala, descripcion_sala, 
								tipo_sala, tesoro_sala, enemigo_sala, &oculta_sala);
		printf("%d\n", leer);
		if(leer == 7)
		{
			cont_salas++;
		}
		if(leer != 7 && !feof(archivo))
		{
			printf("Error de arbol_de_busqueda: Formato de archivo incorrecto\n");
			return T;
		}
		if(ferror(archivo))
		{
			printf("Error de arbol_de_busqueda: Error al leer el archivo\n");
			return T;
		}

		T = ABB_Insertar_Nodo(Crear_Sala(id_sala, nombre_sala, descripcion_sala, tipo_sala, 
			tesoro_sala, enemigo_sala, oculta_sala, 0), T);

		// Mover el cursor hasta la siguiente linea
		do 
		{
			caracter = fgetc(archivo);
		}
		while(caracter != '\n');
	}

	printf("%d salas cargadas.\n", cont_salas);

	printf("Debug:\n");
	ABB_Imprimir_Inorder(T);

	fclose(archivo);

	return T;
}

/*arbol_de_busqueda ABB_Cargar_Pasillos(arbol_de_busqueda T)
{

}*/

//==============================================================================
//        FUNCIONES DE BÚSQUEDA
//==============================================================================

/**
 * @brief Busca en el ABB la sala que tenga un ID determinado
 *
 * En cada nodo se compara el ID buscado con el del nodo y se sigue por el
 * subárbol izquierdo (si es menor) o por el derecho (si es mayor), descartando
 * el otro. Se retorna el nodo que contiene la sala, no una copia.
 *
 * Si no existe una sala con ese ID, o el árbol está vacío, se imprime
 * un aviso con el ID buscado y se retorna un puntero nulo.
 *
 * @param id ID de la sala a buscar
 * @param T ABB donde se busca
 * @return posicion Nodo que contiene la sala, o NULL si no se encuentra
 */
posicion ABB_Buscar(int id, arbol_de_busqueda T)
{
	if(T == NULL)
	{
		printf("Error de abb_find: Arbol vacio\n");
		return T;
	}

	// Caso de no haber encontrado el nodo
	// (haber llegado hasta el final y no coincide el ID)
	if(!T->izquierdo && !T->derecho && ABB_Obtener_ID_Por_Posicion(T) != id)
	{
		printf("Error de abb_find: Sala de ID %d no encontrada\n", id);
		return NULL;
	}
	if(ABB_Obtener_ID_Por_Posicion(T) == id)
	{
		return T;
	}
	else if(id < ABB_Obtener_ID_Por_Posicion(T))
	{
		return ABB_Buscar(id, T->izquierdo);
	}
	else
	{
		return ABB_Buscar(id, T->derecho);
	}
}

/**
 * @brief Busca la sala de menor ID del ABB
 *
 * La de menor ID es siempre el nodo que queda más a la izquierda. Si el árbol
 * está vacío se imprime "Error" y se retorna un puntero nulo.
 *
 * @param T ABB donde se busca
 * @return posicion Nodo con la sala de menor ID, o NULL si el árbol está vacío
 */
posicion ABB_Buscar_Minimo(arbol_de_busqueda T)
{
	if(T == NULL)
	{
		printf("Error de ABB_Buscar_Minimo: Arbol vacio\n");
		return T;
	}

	// Caso de haber llegado hasta el final izquierdo
	if(!T->izquierdo)
	{
		return T;
	}
	else
	{
		return ABB_Buscar_Minimo(T->izquierdo);
	}
}

/**
 * @brief Busca la sala de mayor ID del ABB
 *
 * La de mayor ID es siempre el nodo que queda más a la derecha. Si el árbol está
 * vacío se imprime "Error" y se retorna un puntero nulo.
 *
 * @param T ABB donde se busca
 * @return posicion Nodo con la sala de mayor ID, o NULL si el árbol está vacío
 */
posicion ABB_Buscar_Maximo(arbol_de_busqueda T)
{
	if(T == NULL)
	{
		printf("Error de ABB_Buscar_Maximo: Arbol vacio\n");
		return T;
	}

	// Caso de haber llegado hasta el final derecho
	if(!T->derecho)
	{
		return T;
	}
	else
	{
		return ABB_Buscar_Maximo(T->derecho);
	}
}

//==============================================================================
//        FUNCIONES DE RECORRIDO
//==============================================================================

/**
 * @brief Imprime el ABB en preorder (raíz, izquierda, derecha)
 *
 * Se imprime la raiz del arbol, luego el subarbol izquierdo, y finalmente el
 * subarbol derecho. Se imprime una línea por sala, con el formato
 * "nombre [ID]". Si el árbol está vacío no se imprime nada.
 *
 * @param T ABB a imprimir
 */
void ABB_Imprimir_Preorder(arbol_de_busqueda T)
{
	if(T == NULL)
	{
		return;
	}
	printf("%s, [%d]\n", T->sala.nombre, T->sala.id);
	ABB_Imprimir_Preorder(T->izquierdo);
	ABB_Imprimir_Preorder(T->derecho);
}

/**
 * @brief Imprime el ABB en inorder (izquierda, raíz, derecha)
 *
 * Las salas salen ordenados de menor a mayor ID. Se imprime una línea
 * por sala, con el formato "nombre [ID]". Si el árbol está vacío no se
 * imprime nada.
 *
 * @param T ABB a imprimir
 */
void ABB_Imprimir_Inorder(arbol_de_busqueda T)
{
	if(T == NULL)
	{
		return;
	}
	ABB_Imprimir_Inorder(T->izquierdo);
	//printf("%s, [%d]\n", T->sala.nombre, T->sala.id);
	Imprimir_Sala(T->sala);
	ABB_Imprimir_Inorder(T->derecho);
}

/**
 * @brief Imprime el ABB en postorder (izquierda, derecha, raíz)
 *
 * Se imprime el subarbol izquierdo, luego el subarbol derecho, y finalmente la
 * raiz del arbol. Se imprime una línea por sala, con el formato
 * "nombre [ID]". Si el árbol está vacío no se imprime nada.
 *
 * @param T ABB a imprimir
 */
void ABB_Imprimir_Postorder(arbol_de_busqueda T)
{
	if(T == NULL)
	{
		return;
	}
	ABB_Imprimir_Postorder(T->izquierdo);
	ABB_Imprimir_Postorder(T->derecho);
	printf("%s, [%d]\n", T->sala.nombre, T->sala.id);
}

//==============================================================================
//        FUNCIONES DE ELIMINACIÓN
//==============================================================================

/**
 * @brief Elimina el nodo del ABB con el ID indicado.
 *
 * Se libera la memoria del nodo y su sala con el ID dado.
 *
 * @param T ABB a eliminar un nodo
 * @return El ABB en donde se elimino la sala, NULL si es que no esta
 * inicializado
 */
arbol_de_busqueda ABB_Borrar_Por_ID(int id, arbol_de_busqueda T)
{
	if(T == NULL)
	{
		printf("Error de ABB_Borrar_Por_ID: Arbol nulo o sala de ID %d ausente\n", id);
		return T;
	}

	if(id < T->sala.id)
	{
		T->izquierdo = ABB_Borrar_Por_ID(id, T->izquierdo);
	}
	else if(id > T->sala.id)
	{
		T->derecho = ABB_Borrar_Por_ID(id, T->derecho);
	}
	else
    {
        if(T->izquierdo == NULL || T->derecho == NULL) // Caso de 0 o 1 hijo:
        {
            arbol_de_busqueda hijo = (T->izquierdo != NULL) ? T->izquierdo : T->derecho;
            Liberar_Sala(T->sala);
            free(T);
            return hijo;
        }

        // Caso de 2 hijos: Reemplazar por el sucesor
        posicion min = ABB_Buscar_Minimo(T->derecho);
        sala copia = Crear_Sala(min->sala.id, min->sala.nombre, min->sala.descripcion, min->sala.tipo,
								min->sala.tesoro, min->sala.enemigo, min->sala.oculta, min->sala.vecinas);
        if(copia.nombre == NULL)
		{
			return T; // sin memoria: no tocar el árbol
		}
        Liberar_Sala(T->sala);
        T->sala = copia;
        T->derecho = ABB_Borrar_Por_ID(copia.id, T->derecho);
    }

    return T;
}

/**
 * @brief Elimina todos los nodos del ABB
 *
 * Se libera la memoria de todas las salas y nodos. Los nodos se liberan
 * en postorder (primero los dos subárboles y al final la raíz), porque si se
 * liberara la raíz primero se perdería el acceso a sus hijos. Después de
 * llamarla, T deja de ser válido, por lo que se debe asignar el valor
 * retornado: ABB = abb_delete_tree(ABB).
 *
 * @param T ABB a eliminar
 * @return arbol_de_busqueda Siempre NULL (el árbol vacío)
 */
arbol_de_busqueda ABB_Borrar_Arbol(arbol_de_busqueda T)
{
	if(T == NULL)
	{
		return T;
	}
	T->izquierdo = ABB_Borrar_Arbol(T->izquierdo);
	T->derecho = ABB_Borrar_Arbol(T->derecho);
	Liberar_Sala(T->sala);
	free(T);
	T = NULL;
	return T;
}

//==============================================================================
//        FUNCIONES AUXILIARES
//==============================================================================

/**
 * @brief Devuelve el ID de la sala que está en una posición del ABB
 *
 * Si la posición es nula se imprime "Error" y se retorna -1.
 *
 * @param P Posición (nodo) del ABB
 * @return int ID de la sala, o -1 si la posición es nula
 */
int ABB_Obtener_ID_Por_Posicion(posicion P)
{
	if(P == NULL)
	{
		printf("Error al obtener el ID de la sala\n");
		return -1;
	}
	return P->sala.id;
}
