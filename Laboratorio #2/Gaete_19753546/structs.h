#pragma once

//################################### IMPORTACIONES ###################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//################################### DEFINICIONES DE ESTRUCTURAS ###################################

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

/**
 * @struct instructionNode
 * @brief instructionNode corresponde a una estructura que permite almacenar las instrucciones MIPS de manera ordenada.
 *                   	  Esta estructura está compuesta por los siguientes datos:
 *                   	  firstOperand: Corresponde a la primera parte de la instrucción.
 *                    	  secondOperand: Corresponde a la segunda parte de la instrucción. En caso de no existir, se reemplaza por un string vacío.
 *                   	  thirdOperand: Corresponde a la tercera parte de la instrucción. En caso de no existir, se reemplaza por un string vacío.
 *                   	  label: Corresponde a la etiqueta a la que está asociada una instrucción.
 *                   	  offset: Corresponde a cualquier posible constante presente en la instrucción.
 *                   	  type: Corresponde a un 'identificador' del tipo de instrucción, con el fin de determinar la cantidad de operandos útiles que posee.
 *                   	  
 *                   	  
 */

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

/**
 * @struct instructionLinkedList
 * @brief instructionLinkedList corresponde a una estructura que permite acceder al primer o al último elemento de una lista enlazada de instrucciones.
 *               		        También permite obtener la cantidad de nodos que la componen. Esta estructura está compuesta por los siguientes datos:
 *               		        first: Corresponde a un puntero hacia el primer elemento de la lista enlazada.
 *               		        last: Corresponde a un puntero hacia el último elemento de la lista enlazada.
 *               		        length: Corresponde al largo de la lista enlazada.
 *
 */
typedef struct instructionLinkedList{
	InstructionNode* first;
	InstructionNode* last;
	int length;
}InstructionLinkedList;