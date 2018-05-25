#pragma once
#include "structs.h"

/**
 * @brief searchLabel procedimiento que permite encontrar la ubicación de una etiqueta
 * 
 * @param list corresponde a una lista enlazada en la que se encuentran las instrucciones del programa MIPS
 * @param label corresponde a un string  que indica el nombre de la etiqueta a buscar
 *
 * @return LinesNode* se retorna un puntero hacia el nodo siguiente al que contiene la etiqueta.
 * 					  De no encontrar la etiqueta, se retorna un puntero hacia NULL.
 *
 */

LinesNode* searchLabel(ListOfLines* list, char* label);

/**
 * @brief createRestrictions procedimiento que permite crear una lista enlazada en la que se almacenan los valores de las líneas de control.
 *
 * @param lines corresponde a una lista enlazada que contiene las líneas de control y su estado, es decir, si se encuentra con 
 *              problemas de stuck at 0.
 *
 * @return RestrictionsList* se retorna a una lista enlazada de "restricciones", en la que se determina el valor de las líneas de control.
 *
 */

RestrictionsList* createRestrictions(ListOfLines* lines);

/**
 * @brief readFile procedimiento que permite la lectura de un archivo.
 *
 * @param nameOfFile corresponde al nombre del archivo a leer.
 *
 * @return ListOfLines* se retorna una lista enlazada en la que cada nodo corresponde a una línea del archivo.
 *
 */

ListOfLines* readFile(char* nameOfFile);

/**
 * @brief appendLine permite agregar un nodo que contiene una línea de un archivo, a una lista enlazada.
 *
 * @param lines corresponde a la lista enlazada a la cual se le agregará un elemento.
 * @param line corressponde a la línea del archivo que se le agregará a la lista enlazada.
 *
 */

void appendLine(ListOfLines* lines, char* line);

/**
 * @brief appendRestrictions procedimiento que permite añadir una línea de control a la lista enlazada de posibles restricciones.
 *
 * @param list corresponde a la lista enlazada a la que se le añadirá un elemento.
 * @param instruction corresponde a la línea de control que se añadirá.
 * @param state corresponde al valor que determina si la línea de control presenta problemas de stuck at zero.
 *
 */

void appendRestriction(RestrictionsList* list, char* instruction, char state);

/**
 * @brief freeList procedimiento que permite liberar la memoria de una lista enlazada de palabras (líneas del archivo).
 * 
 * @param node corresponde al nodo desde el cual se comenzará a liberar la memoria.
 * 
 */

void freeList(LinesNode* node);

/**
 * @brief freeRestrictions procedimiento que permite liberar la memoria de una lista enlazada de restricciones (líneas de control).
 * 
 * @param node corresponde al nodo desde el cual se comenzará a liberar la memoria.
 * 
 */

void freeRestrictions(RestrictionsNode* node);

/**
 * @brief searchRegister procedimiento que permite encontrar el valor númerico de un registro, a partir de un string con su nombre.
 *
 * @param registerString corresponde a un string con el nombre del registro a buscar.
 *
 * @return int correspondiente a la identificación numérica del registro.
 *
 */

int searchRegister(char* registerString);

/**
 * @brief searchError procedimimento que permite determinar si cierta línea de control posee error stuck at zero.
 * 
 * @param restrictions corresponde a la lista enlazada con el valor de todas las líneas de control.
 * @param instruction corresponde al nombre de la línea de control a buscar.
 *
 */

int searchError(RestrictionsList* restrictions, char* instruction);

/**
 * @brief showTrace procedimiento que permite llevar a cabo la escritura de la información en los archivos pertinentes.
 * 
 * @param program corresponde a la lista enlazada con las instrucciones del programa en MIPS.
 * @param restrictions corresponde a la lista enlazada que contiene la información de las líneas de control.
 * @param firstOutputFile corresponde al nombre del documento en el cual se debe escribir la traza del programa.
 * @param secondOutputFile corresponde al nombre del documento en el cual se debe escribir la traza del programa, incluyendo el valor
 *                         de cada registro.
 *
 */

void showTrace(ListOfLines* program, RestrictionsList* restrictions, char* firstOutputFile, char* secondOutputFile);

/**
 * @brief run procedimiento que permite inciar el programa.
 *
 */

void run();