#ifndef EXPLORACION_H
#define EXPLORACION_H

typedef struct
{
    int id_actual;
    int *ids_visitadas;
    int cantidad_visitadas;
    int capacidad_visitadas;
} exploracion;

int Exploracion_Inicializar(exploracion *E, int id_inicial);
int Exploracion_Entrar_Sala(exploracion *E, int id_sala);
int Exploracion_Fue_Visitada(const exploracion *E, int id_sala);
void Exploracion_Liberar(exploracion *E);

#endif