#include "exploracion.h"
#include <stdlib.h>

int Exploracion_Fue_Visitada(const exploracion *E, int id_sala)
{
    int i;

    if (E == NULL)
    {
        return 0;
    }

    for (i = 0; i < E->cantidad_visitadas; i++)
    {
        if (E->ids_visitadas[i] == id_sala)
        {
            return 1;
        }
    }

    return 0;
}

int Exploracion_Entrar_Sala(exploracion *E, int id_sala)
{
    int nueva_capacidad;
    int *nuevos_ids;

    if (E == NULL)
    {
        return 0;
    }

    if (!Exploracion_Fue_Visitada(E, id_sala))
    {
        if (E->cantidad_visitadas == E->capacidad_visitadas)
        {
            if (E->capacidad_visitadas == 0)
            {
                nueva_capacidad = 4;
            }
            else
            {
                nueva_capacidad = E->capacidad_visitadas * 2;
            }

            nuevos_ids = realloc(
                E->ids_visitadas,
                nueva_capacidad * sizeof(int)
            );

            if (nuevos_ids == NULL)
            {
                return 0;
            }

            E->ids_visitadas = nuevos_ids;
            E->capacidad_visitadas = nueva_capacidad;
        }

        E->ids_visitadas[E->cantidad_visitadas] = id_sala;
        E->cantidad_visitadas++;
    }

    E->id_actual = id_sala;
    return 1;
}

int Exploracion_Inicializar(exploracion *E, int id_inicial)
{
    if (E == NULL)
    {
        return 0;
    }

    E->id_actual = -1;
    E->ids_visitadas = NULL;
    E->cantidad_visitadas = 0;
    E->capacidad_visitadas = 0;

    if (Exploracion_Entrar_Sala(E, id_inicial) == 0)
    {
        Exploracion_Liberar(E);
        return 0;
    }

    return 1;
}

void Exploracion_Liberar(exploracion *E)
{
    if (E == NULL)
    {
        return;
    }

    free(E->ids_visitadas);

    E->id_actual = -1;
    E->ids_visitadas = NULL;
    E->cantidad_visitadas = 0;
    E->capacidad_visitadas = 0;
}