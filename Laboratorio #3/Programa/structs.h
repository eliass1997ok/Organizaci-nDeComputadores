#pragma once

//################################### IMPORTACIONES ###################################

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "functions.h"

//################################### DEFINICIONES DE ESTRUCTURAS ###################################

/**
 * @struct Results
 * @brief Results corresponde a un nodo de una lista enlazada. Permite almacenar los siguientes datos:
 *                  hit: Corresponde a la cantidad de hits que se producen en una caché.
 *                  miss: Corresponde a la cantidad de miss que se producen en una caché.
 *                  associativity: Corresponde a la asociatividad de la caché.
 *                  policy: Corresponde a la política de reemplazo que fue utilizada en la caché.
 *                  finalState: Corresponde al estado final de la caché, tras ingresar todos los bloques.
 *                  next: Corresponde a un puntero hacia un siguiente resultado.
 *                            
 */
typedef struct results{
    float hit;
    float miss;
    int associativity;
    int policy;
    int** finalState;
    struct results* next;
}Results;

/**
 * @struct ResultsList
 * @brief ResultsList corresponde a una estructura que permite acceder al primer o al último elemento de una lista enlazada de resultados.
 *                    first: Corresponde a un puntero hacia el primer nodo de la lista enlazada.
 *                    last: Corresponde a un puntero hacia el último nodo de la lista enlazada.
 *                    length: Corresponde al largo de la lista.
 *                            
 */
typedef struct resultsList{
    Results* first;
    Results* last;
    int length;
}ResultsList;

/**
 * @struct NumberNode
 * @brief NumberNode corresponde a un nodo de una lista enlazada. Permite almacenar los siguientes datos:
 *                   number: Corresponde a un número dentro de la lista enlazada.
 *                   next: Corresponde a un puntero hacia un siguiente número.
 *                            
 */
typedef struct numberNode{
    int number;
    struct numberNode* next;
}NumberNode;

/**
 * @struct NumberLinkedList
 * @brief NumberLinkedList corresponde a una estructura que permite acceder al primer o al último elemento de una lista enlazada de números.
 *                         first: Corresponde a un puntero hacia el primer nodo de la lista enlazada.
 *                         last: Corresponde a un puntero hacia el último nodo de la lista enlazada.
 *                         length: Corresponde al largo de la lista.
 *                                 
 */
typedef struct numberLinkedList{
    NumberNode* first;
    NumberNode* last;
    int length;
}NumberLinkedList;