/**
 * @file product.c
 * @brief Funciones relacionadas con habitaciones
*/

#include "salas.h"

#include <stdio.h>	
#include <stdlib.h>
#include <string.h>

/**
 * @brief Crea la instancia de una sala.
 *
 * Si no hay memoria suficiente se imprime "Error" y se retorna una sala
 * invalida, es decir, con sus cadenas de caracteres en NULL.
 *
 * @param id Identificador de la sala
 * @param nombre Nombre de la sala
 * @param descripcion Descripcion de la sala
 * @param tipo Tipo de la sala
 * @param tesoro Nombre del tesoro (objeto a ser encontrado) de la sala
 * @param enemigo Nombre de enemigo a encontrar en la sala
 * @param oculta Bandera que determina si una sala esta oculta o no
 * @param vecinas Lista que contiene las IDs de salas adyacentes a la sala
 *
 * @return S Instancia de sala.
*/
sala Crear_Sala(int id, char* nombre, char* descripcion, char* tipo,
				char* tesoro, char* enemigo, char oculta, lista vecinas)
{
	sala S = {id, NULL, NULL, NULL, NULL, NULL, oculta, NULL};

	S.nombre = malloc(strlen(nombre) + 1);
	if(S.nombre == NULL)
	{
		printf("Error: no hay memoria disponible\n");
		return S;
	}
	strcpy(S.nombre, nombre);

	S.descripcion = malloc(strlen(descripcion) + 1);
	if(S.descripcion == NULL)
	{
		printf("Error: no hay memoria disponible\n");
		free(S.nombre);
		S.nombre = NULL;
		return S;
	}
	strcpy(S.descripcion, descripcion);

	S.tipo = malloc(strlen(tipo) + 1);
	if(S.tipo == NULL)
	{
		printf("Error: no hay memoria disponible\n");
		free(S.nombre);
		S.nombre = NULL;
		free(S.descripcion);
		S.descripcion = NULL;
		return S;
	}
	strcpy(S.tipo, tipo);

	S.tesoro = malloc(strlen(tesoro) + 1);
	if(S.tesoro == NULL)
	{
		printf("Error: no hay memoria disponible\n");
		free(S.nombre);
		S.nombre = NULL;
		free(S.descripcion);
		S.descripcion = NULL;
		free(S.tipo);
		S.tipo = NULL;
		return S;
	}
	strcpy(S.tesoro, tesoro);

	S.enemigo = malloc(strlen(enemigo) + 1);
	if(S.enemigo == NULL)
	{
		printf("Error: no hay memoria disponible\n");
		free(S.nombre);
		S.nombre = NULL;
		free(S.descripcion);
		S.descripcion = NULL;
		free(S.tipo);
		S.tipo = NULL;
		free(S.tesoro);
		S.tesoro = NULL;
		return S;
	}
	strcpy(S.enemigo, enemigo);

	// INICIALIZAR VECINAS ACA
	vecinas = 0;
	printf("%d\n(inicializar vecinas!!!!)\n", vecinas);

	return S;
}


/**
 * @brief Imprime por consola una sala.
 *
 * @param S Instancia de sala.
*/
void Imprimir_Sala(sala S)
{
	printf("	- ID: %d\n", S.id);
	printf("	- Nombre: %s\n", S.nombre);
	printf("	- Descripcion: %s\n", S.descripcion);
	printf("	- Tipo: %s\n", S.tipo);
	printf("	- Tesoro: %s\n", S.tesoro);
	printf("	- Enemigo: %s\n", S.enemigo);
	printf("	- Oculta: %c\n", S.oculta);
	printf(" - Vecinas: %d\n", S.vecinas);
}

/**
 * @brief Elimina una sala.
 *
 * @param S Instancia de sala.
*/
void Liberar_Sala(sala S)
{
	free(S.nombre);
	free(S.descripcion);
	free(S.tipo);
	free(S.tesoro);
	free(S.enemigo);
}
