/**
 * @file sala.h
 * @brief Cabecera para las funciones relacionadas con salas
*/

#ifndef SALAS
#define SALAS

/**
 * @brief Estructura que representa una sala
*/

typedef int lista; // REEMPLAZAR POR ESTRUCTURA DE LISTA ENLAZADA!!

typedef struct _sala
{
	int id; // Identificador de la sala
	char* nombre; // Nombre de la sala
	char* descripcion; // Descripcion de la sala
	char* tipo; // Tipo de la sala
	char* tesoro; // Tesoro (nombre de objeto a ser encontrado) de la sala
	char* enemigo; // Nombre de enemigo a encontrar en la sala
	char oculta; // Bandera que determina si una sala esta oculta o no
	lista vecinas; // Lista que contiene las IDs de salas adyacentes a la sala
} sala;

sala Crear_Sala(int id, char* nombre, char* descripcion, char* tipo,
				char* tesoro, char* enemigo, char oculta, lista vecinas);
void Imprimir_Sala(sala S);
void Liberar_Sala(sala S);

#endif
