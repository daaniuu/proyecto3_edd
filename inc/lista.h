#ifndef LISTA
#define LISTA

#include <stdbool.h>
#include "salas.h"

typedef struct nodo_lista* puntero_a_nodo_lista;
typedef puntero_a_nodo_lista lista;
typedef puntero_a_nodo_lista posicion_lista;

/**
 * @brief Estructura de lista
 * 
 * Cada campo indica las caracteristicas de un nodo de la lista.
 */
struct nodo_lista
{
    sala sala;
    puntero_a_nodo_lista siguiente;
};

//==============================================================================
//        FUNCIONES DE INICIALIZACION
//==============================================================================
lista Crear_Lista_Vacia(lista L);
lista Cargar_Habitaciones_Ocultas(lista L);

//==============================================================================
//        FUNCIONES DE INSERCION
//==============================================================================
lista Insertar_Sala(lista L, sala S);

//==============================================================================
//        FUNCIONES DE BUSQUEDA
//==============================================================================
posicion_lista Encontrar_Sala_Por_ID(lista L, int id);
posicion_lista Encontrar_Sala_Anterior_Por_ID(lista L, int id);

//==============================================================================
//        FUNCIONES DE BUSQUEDA
//==============================================================================
void Imprimir_Lista(lista L);

//==============================================================================
//        FUNCIONES DE ELIMINACION
//==============================================================================
void Eliminar_Sala_Por_ID(lista L, int id);
void Eliminar_Lista(lista L);

//==============================================================================
//        FUNCIONES AUXILIARES
//==============================================================================
bool Lista_Vacia(lista L);

#endif