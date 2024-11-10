# Tarea 2 - Diseño y Análisis de Algoritmos

Integrantes: Dante Cárcamo A, Francisco Gutiérrez A

## Descripción

Este proyecto implementa algoritmos de inserción y búsqueda para ABB y Splay Trees. El objetivo es evaluar el costo que se tiene en estas estructuras al momento de realizar búsquedas en ellas considerando una inserción previa aleatoria de valores y otra con elementos ordenados, además se consideran búsquedas según una función de probabilidad para así comparar la entropía con el costo obtenido en los splay trees. Se estudia este comportamiento para distintas cantidades de elementos insertados.

## Dependencias

- La implementación del código fue realizada en C++ y compilada en GNU C++.
- Biblioteca estándar C++

El código hace uso de las siguientes bibliotecas:

    <iostream>, <fstream>,<string>,<filesystem>: Para manejo de datos, tanto para, salida y almacenamiento.
    <set>,<unordered_set>: Para acceso optimizado a los datos.
    <ctime>,<chrono>: Para manejo del tiempo tanto para mensajes de debbuging como para mediciones de los experimentos.
    <vector>, <algorithm>, <random>, <algorithm>, <cstdlib> :Para implementación de estructuras.
    <iomanip>, <queue>: Para visualización en etapa de debbuging.


## Compilación

Puedes compilar el código utilizando un compilador como g++ de la siguiente forma:

```
g++ t2.cpp -o t2
```

## Ejecución

Una vez compilado, ejecuta el programa:

```
./t2
```

Esto generará archivos CSV con los resultados de los experimentos. 

Se insertan N elementos a un vector, donde el N varía desde 100000 a 1000000. Para cada valor de N se calcula el tiempo de búsqueda para ABB y el tiempo de Búsqueda para Splay. Estos datos componen un archivo .CSV que representa los resultados del experimento.

## Descripción del código:

### Node
La clase `Node` representa a la entidad principal de un árbol binario en la cual se definen los métodos de construcción básicos de un nodo y limpieza de punteros.

*Atributos*

- `info`: Valore almacenado en el nodo.
- `Parent`: Punteros al nodo padre, se utiliza en particular para el Splay Tree. Inicialmente es un puntero nulo.
- `left`: Puntero al nodo izquierdo (inicialmente es un puntero nulo).
- `right`: Puntero al nodo derecho (inicialmente es un puntero nulo).

*Métodos*

- `clean`: Limpia los punteros de manera recursiva bajando por los hijos.

### ABB

La clase `ABB` representa la entidad de un Árbol Binario de Búsqueda. Se inicializa con un valor que se almacena en la raíz del árbol.

*Atributos:*

- `root`: Puntero a la raíz del árbol, perteneciente a la clase `Node`.

*Métodos de Node:*
- `insertABB(int x)`: Inserta un valor x en el ABB, cuya raíz es apuntado por `root`, de manera iterativa.

- `searchABB(int x)`: Realiza la búsqueda de un valor x en el árbol apuntado por `root` de manera iterativa, si lo encuentra devuelve un uno indicando que se encontró con éxito, devuelve cero en caso contrario.

- `cleanBB()`: Limpia los punteros del árbol apuntado por `root`, dejando finalmente `root` vacío.

### Splay Tree

La clase `SplayTree` representa la entidad de un Splay Tree. Al igual que para el `ABB`, se inicializa con un valor almacenado en un Nodo apuntado por `root`.

*Atributos*

-`root`: Puntero a la raíz del árbol.

*Métodos de SplayTree*

- `zig(Node* x)`: Realiza una rotación en sentido horario, `x` es un puntero al nodo que se busca dejar en la raíz del árbol.

- `zag(Node* x)`: Realiza una rotación en sentido antihorario, `x` es un puntero al nodo que se busca dejar en la raíz del árbol.

- `zigZig(Node* x)`: Realiza dos rotaciones horario.

- `zagZag(Node* x)`: Realiza dos rotaciones antihorario.

- `zigZag(Node* x)`: Realiza una rotación horario y luego otra antihorario.

- `zagZig(Node* x)`: Realiza una rotación antihorario y luego otra horario.

- `splay(Node* x)`: Lleva al nodo x hasta la raíz realizando rotaciones. 

- `insertSplay(int x)`: Inserta el valor x, para ello avanza en el árbol de manera iterativa y realiza un Splay al nuevo `Nodo` con el elemento x.

- `searchSplay(int x)`: Busca el elemento en el árbol de manera iterativa y realiza un Splay al nodo respectivo.

*Funciones*

- `print()` y `prettyPrintfile()`: Métodos utilizados para visualizar los ABB en la fase de implementación y chequear la correcta funcionalidad de los métodos anteriores.

- `contieneElementos()`: verifica si el vector A contiene el elemento random elegido.

- `permutarVector(vec v)`: Realiza la permutación aleatoria del vector v (utilizado usando el arreglo B definido en el enunciado de la tarea).

- `f(int N,int i)`: Calcula el valor de la función de probabilidad para A[i] considerando una cantidad de datos totales igual a N.

- `calculaC(int N)`: Calcula la constante C utilizada en la función de probabilidad definida en el enunciado de la tarea.

- `hora()`: utiliza funciones de la librería ctime para medir el tiempo actual.
- `calculaH(int N, int C)`: Calcula la entropía utilizando la función de probabilidad definida en el enunciado de la tarea.

## ¿Cómo funciona?

### Experimento 1
Para cada valor de N, se crea un arreglo A en el cual se insertan N valores aleatorios distintos entre 1 y 2N mediante un ciclo `while` usando la función `rand()` (se utiliza el rango [1, 2N] para que no se tengan tantos ciclos sin insertar debido a que el valor ya se encuentra en A). Luego se crea el arreglo B, se permutan los valores de B usando `permutarVector()` y se insertan los valores de A en un nodo usando `insertABB()` y en otro nodo usando `insertSplay()`. Finalmente se realizan las búsquedas usando `searchABB()` y `searchSplay()` según corresponda. Tanto A como B son vectores de C++.

### Experimento 2
A diferencia del experimento anterior al crear el arreglo B, se utiliza la función `f()` para calcular la cantidad de copias de A[i] a insertar en B. Lo demás sigue la secuencia ya descrita en el Experimento 1.

### Experimento 3
Para ordenar el arreglo A antes de insertar se utiliza `sort()`. Lo demás sigue la secuencia ya descrita en el Experimento 1.

### Experimento 4
Se crea una copia del vector A y se almacena en un vector C el cual se ordena utilizando `sort()` y se insertan los valores de C en los árboles. Lo demás sigue la secuencia ya descrita en el experimento 2.