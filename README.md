# Proyecto 3 - Estructura de Datos

**RPG: Explorador de Mazmorras**

Proyecto 3 de la asignatura **Estructura de Datos**, desarrollado en lenguaje **C (C99/C11)**. Consiste en un juego por consola en el que el personaje explora habitaciones conectadas, consulta rutas y descubre o elimina habitaciones del mapa.

## Integrantes

- Daniel Uribe
- Felipe Desmaras
- Gustavo Navarro

## Comandos Makefile

```bash
make
```

Compila el proyecto.

```bash
make run
```

Compila y ejecuta el programa.

```bash
make clean
```

Elimina las carpetas `obj/` y `build/`, junto con los archivos generados durante la compilación.

> Estos comandos corresponden a la organización prevista para el Makefile y deben verificarse al incorporarlo al repositorio.

## Estructura del proyecto

El proyecto se separará en distintos archivos `.c` y `.h` con el objetivo de mantener una estructura ordenada y modular.

Además, contará con un **Makefile** para facilitar la compilación y ejecución en Linux.

La estructura general contempla módulos asociados al mapa de la mazmorra, las estructuras de datos, la carga de habitaciones y las opciones del juego.

### Carpetas

- `src/` → Contiene los archivos `.c` del proyecto.
- `inc/` → Contiene los archivos `.h` del proyecto.
- `obj/` → Contiene los archivos objeto generados durante la compilación.
- `build/` → Contiene el ejecutable generado.
- `data/` → Contiene los archivos de texto utilizados para cargar el mapa, como `mazmorra.txt`.

## Convenciones de código

Para mantener un código uniforme entre todos los integrantes del grupo se utilizarán las siguientes convenciones:

### Funciones

Las funciones utilizarán nombres descriptivos con palabras iniciadas en mayúscula y separadas por guion bajo, siguiendo el estilo del README de referencia.

Ejemplos:

```c
Agregar_Habitacion();
Eliminar_Habitacion();
Buscar_Ruta();
Mostrar_Vecinas();
```

### Variables

Las variables utilizarán `snake_case`.

Ejemplos:

```c
int habitacion_actual;
int cantidad_habitaciones;
int id_destino;
char nombre_habitacion[50];
```

### Constantes y #define

Las constantes y definiciones realizadas mediante `#define` se escribirán completamente en **MAYÚSCULAS**.

Ejemplos:

```c
#define MAX_NOMBRE 50
#define MAX_DESCRIPCION 200
#define MAX_LINEA 512
```

### Buenas prácticas

- Mantener una indentación y espaciado consistentes.
- Dividir el código en funciones pequeñas, con una responsabilidad clara.
- Documentar cada función indicando propósito, parámetros, retorno y posibles errores.
- Identificar la autoría de las secciones desarrolladas por cada integrante.
- Comprobar punteros y asignaciones de memoria dinámica; liberar la memoria al terminar.
- Validar las entradas del usuario y los datos del archivo de mapa.
- Implementar desde cero las estructuras solicitadas, sin utilizar bibliotecas que ya las resuelvan.
- Evitar variables globales innecesarias y código duplicado.

## Organización del proyecto

La siguiente distribución es **propuesta** y podrá ajustarse según los acuerdos del equipo. Todos los integrantes participarán en la implementación, pruebas y redacción del informe.

### Daniel Uribe

**Módulo de Grafo y Algoritmos de Recorrido**

- Implementación de la representación del mapa mediante un grafo no dirigido.
- Desarrollo de las operaciones para agregar y eliminar habitaciones y pasillos.
- Implementación de la consulta de habitaciones vecinas.
- Implementación de **BFS** para encontrar rutas con la menor cantidad de pasillos.
- Implementación de **DFS** para recorrer habitaciones alcanzables.
- Desarrollo de la búsqueda de habitaciones a `k` pasillos.
- Pruebas de rutas inexistentes y mapas desconectados.
- Redacción de la sección de grafos, BFS y DFS del informe.

### Felipe Desmaras

**Módulo de Árbol Binario de Búsqueda (ABB/AVL) e Información de Habitaciones**

- Implementación desde cero del **ABB o AVL**, ordenado por ID de habitación.
- Desarrollo de inserción, búsqueda y eliminación de nodos.
- Manejo de los casos de eliminación: hoja, un hijo y dos hijos.
- Implementación de los recorridos **inorden, preorden y postorden**.
- Desarrollo de la consulta de información de habitaciones por ID.
- Implementación del listado de habitaciones mediante recorrido inorden.
- Pruebas de IDs repetidos, búsquedas inexistentes y eliminación de nodos.
- Redacción de la sección de árboles del informe.

### Gustavo Navarro

**Módulo de Carga de Datos, Exploración e Integración del Juego**

- Desarrollo de la lectura del archivo `mazmorra.txt` con sus ocho campos.
- Validación de errores de carga y construcción del mapa en dos pasadas.
- Implementación de la posición actual del personaje y registro de habitaciones visitadas.
- Desarrollo de la búsqueda y descubrimiento de habitaciones secretas pendientes.
- Integración de la operación **quemar habitación**, sincronizando el grafo y el árbol.
- Desarrollo del menú principal y la interacción por consola.
- Integración de los módulos y verificación del comportamiento del juego.
- Redacción de las secciones de carga de datos, exploración e integración del informe.

## Organización del trabajo con Git y GitHub

- Cada integrante trabajará en sus archivos o ramas acordadas, evitando modificar simultáneamente el mismo módulo sin coordinación.
- Antes de comenzar una sesión de trabajo, se revisarán y descargarán los cambios del repositorio.
- Los commits deberán ser frecuentes y tener mensajes descriptivos de los cambios realizados.
- Los cambios se revisarán y probarán antes de integrarse a la rama principal.
- Se evitará subir archivos objeto, ejecutables y otros archivos temporales; se utilizará `.gitignore`.
- Los tres integrantes revisarán el funcionamiento final del proyecto y colaborarán en el informe.

## Pruebas previstas

Se verificará, como mínimo, la carga de un mapa válido y de archivos con errores; la consulta de habitaciones; los recorridos BFS y DFS; la búsqueda a `k` pasillos; el descubrimiento de habitaciones secretas; la eliminación de habitaciones con sus conexiones; y los casos en los que no existe una ruta hacia el destino.

---

**Nota:** Este documento describe la organización prevista del equipo. Los módulos y responsabilidades deben actualizarse si la distribución real cambia durante el desarrollo.
