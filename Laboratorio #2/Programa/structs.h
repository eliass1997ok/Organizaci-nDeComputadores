#pragma once

//################################### IMPORTACIONES ###################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//################################### DEFINICIONES DE ESTRUCTURAS ###################################

/**
 * @struct RestrictionsNode
 * @brief RestrictionsNode corresponde a un nodo de una lista enlazada. Permite almacenar los siguientes datos:
 *                         instruction: Corresponde a un string, que representa una línea de control.
 *                         state: Corresponde a un caracter, el cual indica si la línea de control presenta problemas.
 *                         next: Puntero hacia el siguiente nodo, del mismo tipo, con tal de crear una lista enlazada.
 *
 */

typedef struct restrictionsNode{
	char* instruction;
	char state;
	struct restrictionsNode* next;
}RestrictionsNode;

/**
 * @struct RestrictionsList
 * @brief RestrictionsList corresponde a una estructura que permite acceder al primer o al último elemento de una lista enlazada de restricciones.
 *                         También permite obtener la cantidad de nodos que la componen. Esta estructura está compuesta por los siguientes datos:
 *                         first: Corresponde a un puntero hacia el primer elemento de la lista enlazada.
 *                         last: Corresponde a un puntero hacia el último elemento de la lista enlazada.
 *                         length: Corresponde al largo de la lista enlazada.
 *
 */

typedef struct restrictionsList{
	RestrictionsNode* first;
	RestrictionsNode* last;
	int length;
}RestrictionsList;

/**
 * @struct LinesNode
 * @brief LinesNode corresponde a un nodo de una lista enlazada. Permite almacenar los siguientes datos:
 *                  line: Corresponde a un string, que representa una línea de un archivo.
 *                  next: Puntero hacia el siguiente nodo, del mismo tipo, con tal de crear una lista enlazada.
 *
 */

typedef struct linesNode{
	char* line;
	struct linesNode* next;
}LinesNode;

/**
 * @struct ListOfLines
 * @brief ListOfLines corresponde a una estructura que permite acceder al primer o al último elemento de una lista enlazada de líneas.
 *                    También permite obtener la cantidad de nodos que la componen. Esta estructura está compuesta por los siguientes datos:
 *                    first: Corresponde a un puntero hacia el primer elemento de la lista enlazada.
 *                    last: Corresponde a un puntero hacia el último elemento de la lista enlazada.
 *                    length: Corresponde al largo de la lista enlazada.
 *
 */

typedef struct listOfLines{
	LinesNode* first;
	LinesNode* last;
	int length;
}ListOfLines;

typedef struct instructionNode{
	char* instruction;
	char* firstOperand;
	char* secondOperand;
	char* thirdOperand;
	char* label;
	int offset;
	int type;

	struct instructionNode* next;
}InstructionNode;

typedef struct instructionLinkedList{
	InstructionNode* first;
	InstructionNode* last;
	int length;
}InstructionLinkedList;




