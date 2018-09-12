#pragma once
#include "structs.h"

/**
 * @brief createResults función que permite la creación de una lista vacía de resultados.
 *
 * @return esta función retorna una lista enlazada inicial, la cual está vacía.
 *
 */
ResultsList* createResults();

/**
 * @brief getMaxResult función que permite obtener los resultados de la caché con la mayor cantidad de hits.
 *
 * @param results corresponde a una lista con todos los resultados generados de la caché.
 * 
 * @return esta función retorna una lista enlazada con los mejores resultados.
 *
 */
ResultsList* getMaxResult(ResultsList* results);

/**
 * @brief createNumberList función que permite la creación de una lista vacía de números.
 *
 * @return esta función retorna una lista enlazada inicial, la cual está vacía.
 *
 */
NumberLinkedList* createNumberList();

/**
 * @brief readFile función que permite la creación de una lista de números, en base a un archivo de texto.
 *
 * @param filename corresponde al nombre del archivo de texto con números.
 * 
 * @return esta función retorna una lista enlazada con los números contenidos dentro del archivo.
 *
 */
NumberLinkedList* readFile(char* filename);

/**
 * @brief listToArray función que permite la transformación de una lista enlazada de números a un arreglo de números.
 *
 * @param list corresponde la lista a transformar.
 * 
 * @return esta función retorna un arreglo de números en base a la transformación de una lista enlazada de números.
 *
 */
int* listToArray(NumberLinkedList* list);

/**
 * @brief getIndex función que permite obtener la posición de un elemento dentro de una lista enlazada.
 *
 * @param list corresponde la lista objetivo.
 * @param element corresponde al elemento a buscar el índice.
 * 
 * @return esta función retorna un número que representa la posición del elemento dentro de la lista enlazada.
 *
 */
int getIndex(NumberLinkedList* list, int element);

/**
 * @brief isIn función que permite determinar si un elemento se encuentra o no dentro de una lista enlazada de números.
 *
 * @param list corresponde la lista objetivo.
 * @param element corresponde al elemento a buscar.
 * 
 * @return esta función retorna un número que indica si el elemento está o no.
 *
 */
int isIn(NumberLinkedList* list, int element);

/**
 * @brief searchSpace función que permite buscar un espacio vacío dentro un conjunto de la memoria caché para almacenar un nuevo bloque.
 *
 * @param memory corresponde a la representación de un conjunto de la memoria caché.
 * @param large corresponde a la cantidad de bloques en el conjunto.
 * 
 * @return esta función retorna un número que indica la posición de un espacio vacío. En su defecto, retorna un -1, indicando que no hay espacio disponible.
 *
 */
int searchSpace(int* memory, int large);

/**
 * @brief returnPositionArray función que permite obtener el índice de un número en un arreglo a partir de su índice dado en una lista.
 *
 * @param list corresponde a la lista en la que se encuentra el número.
 * @param positionInList corresponde a la posición del número dentro de la lista.
 * @param array corresponde al arreglo que posiblemente contiene el número de la lista.
 * @param large corresponde al largo del arreglo.
 * 
 * @return esta función retorna un número que indica la posición del número en el arreglo dado por el índice de la lista.
 *
 */
int returnPositionArray(NumberLinkedList* list, int positionInList, int* array, int large);

/**
 * @brief replaceFIFO función que permite obtener el índice de un número en un arreglo a partir de su índice dado en una lista.
 *
 * @param list corresponde a la lista en la que se encuentran los números ingresados.
 * @param array corresponde al arreglo que contiene los números (conjunto de bloques).
 * @param large corresponde al largo del arreglo (conjunto).
 * 
 * @return esta función retorna un el índice del número que se debe reemplazar.
 *
 */
int replaceFIFO(NumberLinkedList* list, int* array, int large);

/**
 * @brief validateHit función que permite determinar si un bloque hace o no hit dentro de un conjunto de la memoria caché.
 *
 * @param numbers corresponde al arreglo que representa un conjunto de la memoria caché.
 * @param number corresponde al bloque que se desea verificar si hace o no un hit.
 * @param large corresponde al largo del arreglo (conjunto).
 * 
 * @return esta función retorna un número a modo de booleano, que determina si se hace hit o no.
 *
 */
int validateHit(int* numbers, int number, int large);

/**
 * @brief searchMax función que permite obtener el número máximo dentro de un arreglo de números.
 *
 * @param numbers corresponde al arreglo donde se buscará el máximo.
 * @param large corresponde al largo del arreglo.
 * 
 * @return esta función retorna el número mayor del arreglo.
 *
 */
int searchMax(int* array, int large);

/**
 * @brief appendResult procedimiento que permite añadir un resultado a la lista enlazada de resultados.
 *
 * @param list corresponde a la lista enlazada donde se agregará el resultado.
 * @param hit corresponde a la cantidad de hits dentro de ese caché.
 * @param miss corresponde a la cantidad de miss dentro de ese caché.
 * @param associativity corresponde al nivel de asociatividad del caché.
 * @param policy corresponde al identificador de la política de reemplazo utilizada.
 * @param finalState corresponde a los valores finales almacenados en la caché.
 *
 */
void appendResult(ResultsList* list, float hit, float miss, int associativity, int policy, int** finalState);

/**
 * @brief appendNumberList procedimiento que permite añadir un número a la lista enlazada de números.
 *
 * @param list corresponde a la lista enlazada donde se agregará el número.
 * @param number corresponde al número a ingresar a la lista enlazada.
 *
 */
void appendNumberList(NumberLinkedList* list, int number);

/**
 * @brief freeNumberList procedimiento que permite liberar la memoria para una lista enlazada de números.
 *
 * @param node corresponde al nodo desde el cual comenzará a liberarse la memoria.
 *
 */
void freeNumberList(NumberNode* node);

/**
 * @brief removeByIndex procedimiento que permite eliminar un nodo de una lista enlazada de números, en base al índice de ese nodo.
 *
 * @param list corresponde a la lista enlazada donde se removerá el nodo.
 * @param index corresponde al índice del nodo a borrar.
 *
 */
void removeByIndex(NumberLinkedList* list, int index);

/**
 * @brief removeByElement procedimiento que permite eliminar un nodo a partir de un elemento.
 *
 * @param list corresponde a la lista enlazada donde se removerá el nodo.
 * @param element corresponde al elemento que se quiere borrar.
 *
 */
void removeByElement(NumberLinkedList* list, int element);

/**
 * @brief print_usage procedimiento que muestra por pantalla el correcto uso de los flags.
 *
 */
void print_usage();

/**
 * @brief reverseArray procedimiento que permite invertir el orden de un arreglo de números.
 *
 * @param array corresponde al arreglo a invertir.
 * @param end corresponde al índice final del arreglo.
 *
 */
void reverseArray(int* array, int end);

/**
 * @brief arrayToList procedimiento que permite convertir un arreglo de números en una lista de números.
 *
 * @param array corresponde al arreglo a convertir en lista.
 * @param list corresponde a la lista vacía, ingresada por referencia.
 * @param large corresponde al largo del arreglo.
 *
 */
void arrayToList(int* array, NumberLinkedList* list, int large);

/**
 * @brief fifo procedimiento que permite simular el ingreso de bloques a la caché mediante un reemplazo FIFO (First In First Out).
 *
 * @param blocks corresponde a la cantidad de bloques totales en la caché.
 * @param list corresponde a la lista con las direcciones de los bloques a ingresar.
 * @param results corresponde a la lista en la que se almacenan los resultados.
 *
 */
void fifo(int blocks, NumberLinkedList* list, ResultsList* results);

/**
 * @brief lifo procedimiento que permite simular el ingreso de bloques a la caché mediante un reemplazo LIFO (Last In First Out).
 *
 * @param blocks corresponde a la cantidad de bloques totales en la caché.
 * @param list corresponde a la lista con las direcciones de los bloques a ingresar.
 * @param results corresponde a la lista en la que se almacenan los resultados.
 *
 */
void lifo(int blocks, NumberLinkedList* list, ResultsList* results);

/**
 * @brief lru procedimiento que permite simular el ingreso de bloques a la caché mediante un reemplazo LRU (Least Recently Used).
 *
 * @param blocks corresponde a la cantidad de bloques totales en la caché.
 * @param list corresponde a la lista con las direcciones de los bloques a ingresar.
 * @param results corresponde a la lista en la que se almacenan los resultados.
 *
 */
void lru(int blocks, NumberLinkedList* list, ResultsList* results);

/**
 * @brief mru procedimiento que permite simular el ingreso de bloques a la caché mediante un reemplazo MRU (Most Recently Used).
 *
 * @param blocks corresponde a la cantidad de bloques totales en la caché.
 * @param list corresponde a la lista con las direcciones de los bloques a ingresar.
 * @param results corresponde a la lista en la que se almacenan los resultados.
 *
 */
void mru(int blocks, NumberLinkedList* list, ResultsList* results);

/**
 * @brief writeFileWithConfigurations procedimiento que permite escribir en un archivo las configuraciones de la caché que permiten optimizar los hits.
 *
 * @param results corresponde a la lista con los mejores resultados posibles.
 * @param filename corresponde al nombre del archivo en que se escribirán las configuraciones.
 *
 */
void writeFileWithConfigurations(ResultsList* results, char* filename);

/**
 * @brief writeValuesOfCache procedimiento que permite escribir en un archivo los valores finales almacenados en la(s) caché(s) óptimas.
 *
 * @param results corresponde a la lista con los mejores resultados posibles.
 * @param filename corresponde al nombre del archivo en que se escribirán los valores.
 *
 */
void writeValuesOfCache(ResultsList* results, char* filename, int blocksInCache);

/**
 * @brief run procedimiento que permite comenzar la ejecución del programa.
 *
 * @param argc corresponde a la cantidad de "flags" dadas al momento de ejecutar el programa
 * @param argv corresponde a los "flags" dados al momento de ejecutar el programa.
 *
 */
void run(int argc, char* argv[]);