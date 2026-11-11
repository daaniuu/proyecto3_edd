#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

void Menu_Principal(void)
{
    int opcion = 0;
    int lectura;

    while (opcion != 4)
    {
        printf("\n=== RPG: Explorador de Mazmorras ===\n");
        printf("1. Explorar\n");
        printf("2. Consultar una habitacion\n");
        printf("3. Mostrar habitaciones\n");
        printf("4. Salir\n");
        printf("Elige una opcion: ");

        lectura = scanf("%d", &opcion);

        if (lectura == 1)
        {
            switch (opcion)
            {
                case 1:
                    printf("Pendiente.\n");
                    break;
                case 2:
                    printf("Pendiente.\n");
                    break;
                case 3:
                    printf("Pendiente.\n");
                    break;
                case 4:
                    printf("Saliendo del juego.\n");
                    break;
                default:
                    printf("Opcion invalida.\n");
                    break;
            }
        }
        else
        {
            printf("No se ingresó un numero.\n");
            return;
        }
    }
}