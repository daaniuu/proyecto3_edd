/**
 * @file abb.h
 * @brief Cabecera para las funciones de árboles binarios de búsqueda (ABB) de
 * salas
*/

#ifndef ABB_H
#define ABB_H

#include "salas.h"

typedef struct nodo* puntero_a_nodo;
typedef puntero_a_nodo arbol_de_busqueda;
typedef puntero_a_nodo posicion;

/**
 * @brief Representa un nodo de un ABB
 *
 * El orden del arbol lo da el ID del sala: las salas de ID menor al
 * nodo padre estan en el subarbol izquierdo y las de ID mayor en el
 * derecho.
 */
struct nodo
{
	sala sala;
	puntero_a_nodo izquierdo;
	puntero_a_nodo derecho;
};

//==============================================================================
//        FUNCIONES DE INSERCIÓN
//==============================================================================
arbol_de_busqueda ABB_Insertar_Nodo(sala S, arbol_de_busqueda T);
arbol_de_busqueda ABB_Cargar_Habitaciones_Visibles(arbol_de_busqueda T);

//==============================================================================
//        FUNCIONES DE BÚSQUEDA
//==============================================================================
posicion ABB_Buscar(int id, arbol_de_busqueda T);
posicion ABB_Buscar_Minimo(arbol_de_busqueda T);
posicion ABB_Buscar_Maximo(arbol_de_busqueda T);

//==============================================================================
//        FUNCIONES DE RECORRIDO
//==============================================================================
void ABB_Imprimir_Preorder(arbol_de_busqueda T);
void ABB_Imprimir_Inorder(arbol_de_busqueda T);
void ABB_Imprimir_Postorder(arbol_de_busqueda T);

//==============================================================================
//        FUNCIONES DE ELIMINACIÓN
//==============================================================================
arbol_de_busqueda ABB_Borrar_Por_ID(int id, arbol_de_busqueda T);
arbol_de_busqueda ABB_Borrar_Arbol(arbol_de_busqueda T);

//==============================================================================
//        FUNCIONES AUXILIARES
//==============================================================================
int ABB_Obtener_ID_Por_Posicion(posicion P);

#endif
