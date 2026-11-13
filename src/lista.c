/**
 * @file lista.c
 * @brief Funciones relacionadas con listas de salas
*/

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "salas.h"

//==============================================================================
//        FUNCIONES DE INICIALIZACION
//==============================================================================

/**
 * @brief Crea una lista a una variable de tipo lista.
 * 
 * @param L Variable de tipo lista en donde crearla.
 *
 * @return La lista si se creo correctamente, NULL en caso contrario.
 */
lista Crear_Lista_Vacia(lista L)
{
	if(Lista_Vacia(L) == false)
	{
		Eliminar_Lista(L);
	}

	L = malloc(sizeof(struct nodo_lista));
	if(L == NULL)
	{
		printf("Out of memory!\n");
		return L;
	}
	L->siguiente = NULL;

	return L;
}

/**
 * @brief Carga en la lista las habitaciones ocultas de "mazmorra.txt".
 *
 * @param S Sala a insertar
 * @param L Lista en donde se debe insertar la sala
 * @return arbol_de_busqueda Referencia a la lista con la salas insertadas
 */
lista Cargar_Habitaciones_Ocultas(lista L)
{
	FILE* archivo;
	int leer;
	int cont_salas = 0;
	char caracter;

	// Variables para grabar los valores leidos de mazmorras.txt, y luego copiar en una sala individual.
	int id_sala;
	char nombre_sala[21];
	char descripcion_sala[50];
	char tipo_sala[11];
	char tesoro_sala[50];
	char enemigo_sala[50];
	char oculta_sala;

	L = Crear_Lista_Vacia(L);

	archivo = fopen("mazmorra.txt", "r");
	if(archivo == NULL)
	{
		printf("Error de Cargar_Habitaciones_Ocultas: No se pudo abrir mazmorra.txt\n");
		return L;
	}

	// Saltar hasta la seccion de habitaciones ocultas en el .txt
	for(int i = 0; i < 4; i++)
	{
		do
		{
			caracter = fgetc(archivo);
		}
		while(caracter != '#');
	}
	do
	{
		caracter = fgetc(archivo);
	}
	while(caracter != '\n');

	while(!feof(archivo))
	{
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
			printf("Error de Cargar_Habitaciones_Ocultas: Formato de archivo incorrecto\n");
			return L;
		}
		if(leer == -1) // Retorna -1 cuando llega al final del archivo
		{
			break;
		}
		if(ferror(archivo))
		{
			printf("Error de Cargar_Habitaciones_Ocultas: Error al leer el archivo\n");
			return L;
		}

		L = Insertar_Sala(L, Crear_Sala(id_sala, nombre_sala, descripcion_sala, tipo_sala, 
			tesoro_sala, enemigo_sala, oculta_sala, 0));

		// Mover el cursor hasta la siguiente linea
		do
		{
			caracter = fgetc(archivo);
		}
		while(caracter != '\n');
	}

	printf("%d salas cargadas.\n", cont_salas);

	printf("Debug:\n");
	Imprimir_Lista(L);

	fclose(archivo);

	return L;
}

//==============================================================================
//        FUNCIONES DE INSERCION
//==============================================================================

/**
 * @brief Inserta la sala en la lista dada al final de esta.
 * 
 * @param L Lista a insertar la sala.
 * @param S Sala a insertar.
 *
 * @return La sala en todos los casos.
 */
lista Insertar_Sala(lista L, sala S)
{
	// Restricciones: El inventario debe existir y el inventario no puede estar lleno.
	// Revisa si el inventario existe.
	if(L == NULL)
	{
		printf("Error de Insertar_Sala: Inventario nulo\n");
		return L;
	}

	// Posiciona un puntero posicion al ultimo elemento del inventario.
	posicion_lista p = L;
	while(p->siguiente != NULL)
	{
		p = p->siguiente;
	}

	// Crea el nodo auxilar a sostener el objeto a insertar.
	posicion_lista aux = malloc(sizeof(struct nodo_lista));
    if(aux == NULL)
    {
        printf("Out of memory!\n");
        return aux;
    }

	// Inserta el nodo auxiliar al final de la lista.
    aux->sala = S;
    aux->siguiente = NULL;
    p->siguiente = aux;

    return L;
}

//==============================================================================
//        FUNCIONES DE BUSQUEDA
//==============================================================================

/**
 * @brief Busca una sala por ID en la lista dada.
 * 
 * @param L Lista a buscar la sala.
 * @param id ID para buscar la sala.
 *
 * @return La variable posicion de la sala si es encontrada, NULL en caso contrario.
 */
posicion_lista Encontrar_Sala_Por_ID(lista L, int id)
{
	if(Lista_Vacia(L) == true)
	{
		printf("Error de Encontrar_Sala_Por_ID: Inventario vacio o nulo\n");
		return L;
	}

	posicion_lista p = L->siguiente;
	while(p != NULL)
	{
		if(p->sala.id == id)
		{
			//printf("Sala encontrada!\n");
			//analizar_objeto(p->sala);
			return p;
		}
		p = p->siguiente;
	}
	//printf("Sala no encontrada! :<\n");
	return NULL;
}

/**
 * @brief Busca la sala anterior a la sala indicada por ID en la lista dada.
 * 
 * @param L Lista a buscar la sala.
 * @param id ID para buscar la sala anterior.
 *
 * @return La variable posicion de la sala anterior si es encontrada, NULL en caso contrario.
 */
posicion_lista Encontrar_Sala_Anterior_Por_ID(lista L, int id)
{
	if(Lista_Vacia(L) == true)
	{
		printf("Error de Encontrar_Sala_Anterior_Por_ID: Inventario vacio o nulo\n");
		return L;
	}

	posicion_lista p = L;
	while(p->siguiente != NULL) // Gracias a la inicializacion de p, deberia ser imposible tratar de eliminar la cabecera.
	{
		if(p->siguiente->sala.id == id)
		{
			//printf("encontrar_objeto_anterior_por_id: Sala anterior encontrada!\n");
			//analizar_objeto(p->objeto);
			return p;
		}
		p = p->siguiente;
	}
	//printf("encontrar_objeto_anterior_por_id: Sala no encontrada! :<\n");
	return NULL;
}

//==============================================================================
//        FUNCIONES DE RECORRIDO
//==============================================================================

/**
 * @brief Imprime todas las salas de la lista en orden de insercion.
 */
void Imprimir_Lista(lista L)
{
	if(L == NULL)
	{
		printf("Error de Imprimir_Lista: Inventario nulo\n");
		return;
	}
	
	printf("  ==============\n");
	printf("  Salas ocultas:\n");
	printf("  ==============\n\n");
	if(L->siguiente == NULL)
	{
		printf("No hay salas ocultas!\n\n");
		return;
	}
	posicion_lista p = L->siguiente;
	while(p != NULL)
	{
		Imprimir_Sala(p->sala);
		printf("\n");
		p = p->siguiente;
	}
}

//==============================================================================
//        FUNCIONES DE ELIMINACION
//==============================================================================

/**
 * @brief Elimina la sala indicada de la lista.
 *
 * @param L Lista en donde se elimina una sala.
 * @param id ID de la sala a eliminar.
 */
void Eliminar_Sala_Por_ID(lista L, int id)
{
	if(Lista_Vacia(L) == true)
	{
		printf("Error de Eliminar_Sala_Por_ID: Inventario vacio o nulo\n");
		return;
	}
	
	posicion_lista p, aux;
	p = Encontrar_Sala_Anterior_Por_ID(L, id); 
	if(p == NULL)
	{
		printf("Error de Eliminar_Sala_Por_ID: No se encontro el objeto a eliminar\n");
		return;
	}

	aux = p->siguiente;
	// printf("Eliminando [%s]...\n", aux->sala.nombre);
	p->siguiente = aux->siguiente;
	free(aux);
}

/**
 * @brief Elimina la lista dada.
 *
 * Corre un bucle que libera la memoria asignada del ultimo nodo hasta alcanzar la cabecera,
 * acto seguido, libera su memoria.
 *
 * @param i Lista a eliminar.
 */
void Eliminar_Lista(lista L)
{
	posicion_lista aux = L;

	while(aux != NULL)
	{
		aux = aux->siguiente;
		free(L);
		L = aux;
	}
}

//==============================================================================
//        FUNCIONES AUXILIARES
//==============================================================================

/**
 * @brief Comprueba si la lista esta vacia. 
 * 
 * @param L Lista a consultar.
 *
 * @return 1 si esta vacia, 0 si no esta vacia o si es nula.
 */
bool Lista_Vacia(lista L)
{
	if(L == NULL || L->siguiente == NULL)
	{
		return true;
	}
	return false;
}
