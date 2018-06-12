#pragma once
#include "structs.h"

/**
 * @brief readFile función que permite la lectura de un archivo.
 *
 * @param nameOfFile corresponde al nombre del archivo a leer.
 *
 * @return ListOfLines* se retorna una lista enlazada en la que cada nodo corresponde a una línea del archivo.
 *
 */

ListOfLines* readFile(char* nameOfFile);

/**
 * @brief appendLine procedimiento que permite agregar un nodo que contiene una línea de un archivo, a una lista enlazada.
 *
 * @param lines corresponde a la lista enlazada a la cual se le agregará un elemento.
 * @param line corressponde a la línea del archivo que se le agregará a la lista enlazada.
 *
 */

void appendLine(ListOfLines* lines, char* line);

/**
 * @brief appendInstruction procedimiento que permite agregar un nodo que contiene una instrucción, a una lista enlazada.
 *
 * @param list corresponde a la lista enlazada a la cual se le agregará un elemento.
 * @param instruction corressponde a la línea del archivo que se le agregará a la lista enlazada.
 * @param firstOperand corresponde a la primera parte de la instrucción.
 * @param secondOperand corresponde a la segunda parte de la instrucción.
 * @param thirdOperand corresponde a la tercera parte de la instrucción.
 * @param offset corresponde a cualquier constante que pueda presentar la instrucción.
 * @param type corresponde a un identificador del tipo de instrucción.
 * @param label corresponde a la etiqueta que podría estar asociada a la instrucción.
 */

void appendInstruction(InstructionLinkedList* list, char* instruction, char* firstOperand, char* secondOperand, char* thirdOperand, int offset, int type, char* label);

/**
 * @brief pushInstruction procedimimento que permite insertar un nodo como la cabeza de una lista de instrucciones.
 * 
 * @param list corresponde a la lista enlazada con las instrucciones del programa.
 * @param node corresponde al nodo que se insertará como primer elemento.
 *
 */

void pushInstruction(InstructionLinkedList* list, InstructionNode* node);

/**
 * @brief pushInstruction procedimimento que permite eliminar el primer elemento de una lista enlazada.
 * 
 * @param list corresponde a la lista enlazada con las instrucciones del programa, a la cual se le eliminará su primer elemento.
 *
 */

void popInstruction(InstructionLinkedList* list);

/**
 * @brief createInstructionLinkedList función que permite crear una lista enlazada de instrucciones inicial.
 * 
 * @return esta función retorna una lista enlazada inicial, la cual está vacía.
 *
 */

InstructionLinkedList* createInstructionLinkedList();

/**
 * @brief freeList procedimiento que permite liberar la memoria de una lista enlazada de palabras (líneas del archivo).
 * 
 * @param node corresponde al nodo desde el cual se comenzará a liberar la memoria.
 * 
 */

void freeList(LinesNode* node);

/**
 * @brief freeInstructionsList procedimiento que permite liberar la memoria de una lista enlazada de instrucciones.
 * 
 * @param node corresponde al nodo desde el cual se comenzará a liberar la memoria.
 * 
 */

void freeInstructionsList(InstructionNode* node);


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
 * @brief fillRegisters función que permite establecer los valores iniciales de los registros.
 *
 * @param lines corresponde a una lista enlazada en la que se tiene cada línea del texto con los valores de los registros.
 *
 * @return int* correspondiente al arreglo que representa a cada registro.
 *
 */

int* fillRegisters(ListOfLines* lines);

/**
 * @brief searchHazardNonSeparatedLines función que permite determinar si cierta línea de control posee error stuck at zero.
 * 
 * @param firstLine corresponde a la primera instrucción.
 * @param nextLine corresponde a la segunda instrucción. Se busca un posible hazard de datos con la primera instrucción.
 *
 * @return char* corresponde al string que indica el registro en donde se produce un hazard.
 *
 */

char* searchHazardNonSeparatedLines(InstructionNode* firstLine, InstructionNode* nextLine);

/**
 * @brief determineLwHazard función que permite determinar si cierta línea de control posee error stuck at zero.
 * 
 * @param firstLine corresponde a la primera instrucción.
 * @param nextLine corresponde a la segunda instrucción. Se busca un posible hazard de datos producido por un lw con la primera instrucción.
 *
 * @return char* corresponde al string que indica el registro en donde se produce un hazard.
 *
 */

char* determineLwHazard(InstructionNode* firstLine, InstructionNode* nextLine);

/**
 * @brief searchJump función que permite determinar el nodo que posee cierta etiqueta.
 * 
 * @param instructions corresponde a la lista de instrucciones que componen el programa.
 * @param label corresponde a la etiqueta a buscar dentro del código MIPS.
 *
 * @return InstructionNode* corresponde al nodo que posee la etiqueta buscada. En caso de no ser encontrado, retorna un puntero a NULL.
 *
 */

InstructionNode* searchJump(InstructionLinkedList* instructions, char* label);

/**
 * @brief doTheOperation procedimimento que permite realizar cierta instrucción.
 * 
 * @param instruction corresponde a la instrucción a llevar a cabo.
 * @param registers corresponde a los valores de los registos que puede ocupar la instrucción.
 * @param memory corresponde a los valores de memoria que puede ocupar la instrucción.
 * 
 */

void doTheOperation(InstructionNode* instruction, int* registers, int** memory);

/**
 * @brief writeHazardsFile procedimimento que permite escribir en un archivo los hazards encontrados.
 * 
 * @param instructions corresponde a la lista de instrucciones del programa.
 * @param outputFile corresponde al nombre del archivo de salida.
 * @param registers corresponde a los valores de los registos que puede ocupar la instrucción.
 * @param memory corresponde a los valores de memoria que puede ocupar la instrucción.
 * 
 */

void writeHazardsFile(InstructionLinkedList* instructions, char* outputFile, int* registers, int** memory);

/**
 * @brief lineToInstruction función que permite transformar una lista de strings en una lista de instrucciones.
 *
 * @param lines corresponde a una lista enlazada en la que se tiene cada línea del texto con instrucciones.
 *
 * @return InstructionLinkedList* correspondiente a la lista enlazada de instrucciones.
 *
 */

InstructionLinkedList* lineToInstruction(ListOfLines* lines);

/**
 * @brief createStall función que permite crear una instrucción especial que sirve de espera.
 * 
 * @return InstructionNode* corresponde a una instrucción de espera.
 *
 */

InstructionNode* createStall();

/**
 * @brief getIF función que permite retornar el primer elemento de la lista. El primer elemento
 *              representa la instrucción dentro de la etapa Instruction Fetch del pipeline.
 *
 * @param stack corresponde a una lista enlazada de palabras, la cual se utilizará simulando una pila de instrucciones.
 * 
 * @return InstructionNode* corresponde a la instrucción dentro de IF.
 *
 */

InstructionNode* getIF(InstructionLinkedList* stack);

/**
 * @brief getID función que permite retornar el segundo elemento de la lista. El segundo elemento
 *              representa la instrucción dentro de la etapa Instruction Decode del pipeline.
 *
 * @param stack corresponde a una lista enlazada de palabras, la cual se utilizará simulando una pila de instrucciones.
 * 
 * @return InstructionNode* corresponde a la instrucción dentro de ID.
 *
 */

InstructionNode* getID(InstructionLinkedList* stack);

/**
 * @brief getEX función que permite retornar el tercer elemento de la lista. El tercer elemento
 *              representa la instrucción dentro de la etapa Execution del pipeline.
 *
 * @param stack corresponde a una lista enlazada de palabras, la cual se utilizará simulando una pila de instrucciones.
 * 
 * @return InstructionNode* corresponde a la instrucción dentro de EX.
 *
 */

InstructionNode* getEX(InstructionLinkedList* stack);

/**
 * @brief getMEM función que permite retornar el cuarto elemento de la lista. El cuarto elemento
 *              representa la instrucción dentro de la etapa Memory del pipeline.
 *
 * @param stack corresponde a una lista enlazada de palabras, la cual se utilizará simulando una pila de instrucciones.
 * 
 * @return InstructionNode* corresponde a la instrucción dentro de MEM.
 *
 */

 InstructionNode* getMEM(InstructionLinkedList* stack);

 /**
 * @brief getWB función que permite retornar el quinto elemento de la lista. El quinto elemento
 *              representa la instrucción dentro de la etapa Write Back del pipeline.
 *
 * @param stack corresponde a una lista enlazada de palabras, la cual se utilizará simulando una pila de instrucciones.
 * 
 * @return InstructionNode* corresponde a la instrucción dentro de WB.
 *
 */

 InstructionNode* getWB(InstructionLinkedList* stack);

/**
 * @brief printInstructions procedimimento que permite escribir en un archivo los hazards encontrados.
 * 
 * @param stack corresponde a la lista de instrucciones del programa, la cual simula ser una pila.
 * @param f corresponde al nombre del archivo de salida.
 * @param cycle corresponde al número de ciclo en el cual se encuentra la instrucción.
 * 
 */

 void printInstructions(InstructionLinkedList* stack, FILE* f, int cycle);

/**
 * @brief createNull procedimimento que permite escribir en un archivo los hazards encontrados.
 * 
 * @return InstructionNode* corresponde a una instrucción vacía. NO ES UNA ESPERA.
 * 
 */

 InstructionNode* createNull();

/**
 * @brief finishPipeline procedimimento que permite escribir en un archivo los últimos 4 ciclos del pipeline.
 * 
 * @param stack corresponde a la lista de instrucciones del programa, la cual simula ser una pila.
 * @param f corresponde al nombre del archivo de salida.
 * @param cycle corresponde al número de ciclo en el cual se encuentra la instrucción.
 * 
 */

 void finishPipeline(InstructionLinkedList* stack, FILE* f, int cycle);

/**
 * @brief writePipelinedFile procedimimento que permite escribir en un archivo el programa ejecutado en un pipeline de 5 etapas.
 * 
 * @param instructions corresponde a la lista de instrucciones del programa.
 * @param filename corresponde al nombre del archivo de salida.
 * 
 */

 void writePipelinedFile(InstructionLinkedList* instructions, char* filename, int* registers, int** memory);

/**
 * @brief run procedimiento que permite inciar el programa.
 *
 */

void run();