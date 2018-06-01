#include "functions.h"

void appendLine(ListOfLines* lines, char* line){
	LinesNode* node;
	node = (LinesNode*)calloc(1, sizeof(LinesNode));

	node->line = (char*)calloc(1024, sizeof(char));

	strcpy(node->line, line);

	if (lines->length == 0){
		lines->first = node;
		lines->last = node;
	} else {
		lines->last->next = node;
		lines->last = node;
	}

	lines->length++;
}

void appendRestriction(RestrictionsList* list, char* instruction, char state){
	RestrictionsNode* node;
	node = (RestrictionsNode*)calloc(1, sizeof(RestrictionsNode));

	node->instruction = (char*)calloc(32, sizeof(char));

	strcpy(node->instruction, instruction);
	node->state = state;

	if (list->length == 0){
		list->first = node;
		list->last = node;
	} else {
		list->last->next = node;
		list->last = node;
	}

	list->length++;
}

void appendInstruction(InstructionLinkedList* list, char* instruction, char* firstOperand, char* secondOperand, char* thirdOperand, int offset, int type){
	InstructionNode* node;
	node = (InstructionNode*)calloc(1, sizeof(InstructionNode));

	node->instruction = (char*)calloc(32, sizeof(char));
	node->firstOperand = (char*)calloc(6, sizeof(char));
	node->secondOperand = (char*)calloc(10, sizeof(char));
	node->thirdOperand = (char*)calloc(10, sizeof(char));

	strcpy(node->instruction, instruction);
	strcpy(node->firstOperand, firstOperand);
	strcpy(node->secondOperand, secondOperand);
	strcpy(node->thirdOperand, thirdOperand);
	node->offset = offset;
	node->type = type;

	if (list->length == 0){
		list->first = node;
		list->last = node;
	} else {
		list->last->next = node;
		list->last = node;
	}

	list->length++;
}

void pushInstruction(InstructionLinkedList* list, InstructionNode* node){
	InstructionNode* newNode;
	newNode = (InstructionNode*)calloc(1, sizeof(InstructionNode));

	newNode->instruction = (char*)calloc(32, sizeof(char));
	newNode->firstOperand = (char*)calloc(6, sizeof(char));
	newNode->secondOperand = (char*)calloc(10, sizeof(char));
	newNode->thirdOperand = (char*)calloc(10, sizeof(char));

	strcpy(newNode->instruction, node->instruction);
	strcpy(newNode->firstOperand, node->firstOperand);
	strcpy(newNode->secondOperand, node->secondOperand);
	strcpy(newNode->thirdOperand, node->thirdOperand);

	newNode->type = node->type;

	if (list->length == 0){
		list->first = newNode;
		list->last = newNode;
	} else {
		newNode->next = list->first;
		list->first = newNode;
	}

	list->length++;
}

void popInstruction(InstructionLinkedList* list){
	if (list->length == 0){
		return;
	} else if (list->length == 1){
		list->first = NULL;
		list->last = NULL;
		list->length--;
	} else {
		list->first = list->first->next;
		list->length++;
	}
}

InstructionLinkedList* createInstructionLinkedList(){
	InstructionLinkedList* list;
	list = (InstructionLinkedList*)calloc(1, sizeof(InstructionLinkedList));

	list->first = NULL;
	list->last = NULL;
	list->length = 0;

	return list;
}

void freeList(LinesNode* node){
	LinesNode* aux;

	while (node){
		aux = node;
		node = node->next;
		free(aux->line);
		free(aux);
	}
}

void freeInstructionsList(InstructionNode* node){
	InstructionNode* aux;

	while(node){
		aux = node;
		node = node->next;
		free(aux->instruction);
		free(aux->firstOperand);
		free(aux->secondOperand);
		free(aux->thirdOperand);
		free(aux);
	}
}

void freeRestrictions(RestrictionsNode* node){
	RestrictionsNode* aux;

	while (node){
		aux = node;
		node = node->next;
		free(aux->instruction);
		free(aux);
	}
}

ListOfLines* readFile(char* nameOfFile){
	FILE* f = fopen(nameOfFile, "r");

	if (! f){
		printf("El archivo %s no existe.\nSaliendo...", nameOfFile);
		exit(1);	
	} 

	ListOfLines* lines;
	lines = (ListOfLines*)calloc(1, sizeof(ListOfLines));

	char buffer[255];

	while (fgets(buffer, 255, (FILE*)f)){
		LinesNode* node;
		node = (LinesNode*)calloc(1, sizeof(LinesNode));

		appendLine(lines, buffer);
	}

	return lines;
}

RestrictionsList* createRestrictions(ListOfLines* lines){
	LinesNode* aux;
	aux = lines->first;

	RestrictionsList* restrictions;
	restrictions = (RestrictionsList*)calloc(1, sizeof(RestrictionsList));

	while (aux){
		RestrictionsNode* nodeOfRestrictions;
		nodeOfRestrictions = (RestrictionsNode*)calloc(1, sizeof(RestrictionsNode));

		char* token;
		char instruction[32];

		token = strtok(aux->line, " ");
		strcpy(instruction, token);

		token = strtok(NULL, " ");

		appendRestriction(restrictions, instruction, token[0]);

		aux = aux->next;
	}

	return restrictions;
}

LinesNode* searchLabel(ListOfLines* list, char* label){
	LinesNode* node;
	char* token;

	node = list->first;

	while (node){
		token = strtok(node->line, ":");
		if (strcmp(token, label) == 0) return node->next;
		node = node->next;
	}

	return NULL;
}

int searchRegister(char* registerString){
	if (strcmp(registerString, "$zero") == 0) return 0;
	if (strcmp(registerString, "$at") == 0) return 1;
	if (strcmp(registerString, "$v0") == 0) return 2;
	if (strcmp(registerString, "$v1") == 0) return 3;
	if (strcmp(registerString, "$a0") == 0) return 4;
	if (strcmp(registerString, "$a1") == 0) return 5;
	if (strcmp(registerString, "$a2") == 0) return 6;
	if (strcmp(registerString, "$a3") == 0) return 7;
	if (strcmp(registerString, "$t0") == 0) return 8;
	if (strcmp(registerString, "$t1") == 0) return 9;
	if (strcmp(registerString, "$t2") == 0) return 10;
	if (strcmp(registerString, "$t3") == 0) return 11;
	if (strcmp(registerString, "$t4") == 0) return 12;
	if (strcmp(registerString, "$t5") == 0) return 13;
	if (strcmp(registerString, "$t6") == 0) return 14;
	if (strcmp(registerString, "$t7") == 0) return 15;
	if (strcmp(registerString, "$s0") == 0) return 16;
	if (strcmp(registerString, "$s1") == 0) return 17;
	if (strcmp(registerString, "$s2") == 0) return 18;
	if (strcmp(registerString, "$s3") == 0) return 19;
	if (strcmp(registerString, "$s4") == 0) return 20;
	if (strcmp(registerString, "$s5") == 0) return 21;
	if (strcmp(registerString, "$s6") == 0) return 22;
	if (strcmp(registerString, "$s7") == 0) return 23;
	if (strcmp(registerString, "$t8") == 0) return 24;
	if (strcmp(registerString, "$t9") == 0) return 25;
	if (strcmp(registerString, "$k0") == 0) return 26;
	if (strcmp(registerString, "$k1") == 0) return 27;
	if (strcmp(registerString, "$gp") == 0) return 28;
	if (strcmp(registerString, "$sp") == 0) return 29;
	if (strcmp(registerString, "$fp") == 0) return 30;
	if (strcmp(registerString, "$ra") == 0) return 31;
	return -1;
}

int searchError(RestrictionsList* restrictions, char* instruction){
	RestrictionsNode* node;
	node = restrictions->first;

	while (node){
		if (strcmp(node->instruction, instruction) == 0) 
			if (node->state == 'x' || node->state == 'X') return 0;
		node = node->next;
	}

	return 1;
}

int* fillRegisters(ListOfLines* lines){
	int* registers;

	registers = (int*)calloc(32, sizeof(int));

	LinesNode* node;
	node = lines->first;

	while (node){
		char* token;
		int positionOfRegister;
		int valueAtRegister;

		token = strtok(node->line, " ");
		positionOfRegister = searchRegister(token);

		valueAtRegister = atoi(strtok(NULL, " "));

		registers[positionOfRegister] = valueAtRegister;

		node = node->next;		
	}

	return registers;
}

char* searchHazardNonSeparatedLines(InstructionNode* firstLine, InstructionNode* nextLine){
	if ((firstLine->type == 1 || firstLine->type == 2 || firstLine->type == 4) && strcmp(firstLine->instruction, "beq") != 0 && 
		(nextLine->type == 1 || nextLine->type == 2 || nextLine->type == 4)  && strcmp(nextLine->instruction, "beq") != 0 &&
		strcmp(firstLine->instruction, "lw") != 0 && strcmp(nextLine->instruction, "lw") != 0 &&
		(strcmp(firstLine->firstOperand, nextLine->secondOperand) == 0 || strcmp(firstLine->firstOperand, nextLine->thirdOperand) == 0) )

		return firstLine->firstOperand;

	else if ((firstLine->type == 1 || firstLine->type == 2) && strcmp(firstLine->instruction, "beq") != 0 && 
			strcmp(nextLine->instruction, "beq") == 0 &&
			(strcmp(firstLine->firstOperand, nextLine->firstOperand) == 0 || strcmp(firstLine->firstOperand, nextLine->secondOperand) == 0))

		return firstLine->firstOperand;

	return NULL;
}

char* determineLwHazard(InstructionNode* firstLine, InstructionNode* nextLine){
	// printf("first line instruction: %s\n", firstLine->instruction);
	// printf("instrucción segunda linea: %s\n",nextLine->instruction);
	// printf("tipo segunda linea: %d\n", nextLine->type);
	// printf("primer operando primera línea: %s\n",firstLine->firstOperand);
	// printf("segundo operando segunda línea: %s\n",nextLine->secondOperand);
	// printf("tercer operando segunda línea: %s\n",nextLine->thirdOperand);
	if (strcmp(firstLine->instruction, "lw") == 0  && nextLine && (nextLine->type == 1 || nextLine->type == 2) && strcmp(nextLine->instruction, "beq") != 0 && 
		(strcmp(firstLine->firstOperand, nextLine->thirdOperand) == 0 || strcmp(firstLine->firstOperand, nextLine->secondOperand) == 0) )

		return firstLine->firstOperand;

	// printf("no entré\n");
	return NULL;
}

void writeHazardsFile(InstructionLinkedList* instructions, int* registersFromFile, char* outputFile){
	FILE* f;
	f = fopen(outputFile, "w");
	
	if (! f) exit(1);

	InstructionNode* instructionLine;
	instructionLine = instructions->first;

	fprintf(f, "CICLOS;DATOS;CONTROL\n");

	int marked;
	marked = 0;

	int lw;
	lw = 0;

	int ant;
	ant = 0;

	int auxiliarCounter;
	auxiliarCounter = 0;

	int cicleCounter;
	cicleCounter = 1;
	
	fprintf(f, "%d;;\n", cicleCounter);
	cicleCounter++;
	fprintf(f, "%d;;\n", cicleCounter);
	cicleCounter++;
	
	InstructionNode* node;
	node = instructions->first;

	while (node){
		int boolean = 0;

		if (node->next && searchHazardNonSeparatedLines(node, node->next) && marked == 0 && lw != 2){

			fprintf(f, "%d;%s;\n", cicleCounter, searchHazardNonSeparatedLines(node, node->next));
			cicleCounter++;
			boolean = 1;
			ant = 0;
		}

		lw = 0;
		marked = 0;

		if (node->next && determineLwHazard(node, node->next)){
			// fprintf(f, "%d;;\n", cicleCounter);
			// cicleCounter++;
			auxiliarCounter++;
			boolean = 1;
			lw = 1;
			fprintf(f, "%d;;%s\n", cicleCounter, determineLwHazard(node, node->next));
			cicleCounter++;
			fprintf(f, "%d;%s;\n", cicleCounter, determineLwHazard(node, node->next));
			cicleCounter++;
			ant = 1;

		}


		if (node->next && node->next->next && searchHazardNonSeparatedLines(node, node->next->next) &&
		 ! searchHazardNonSeparatedLines(node->next, node->next->next) && marked == 0){
			// fprintf(f, "%d;;\n",cicleCounter);
			// cicleCounter++;
			if (ant == 1){
				fprintf(f, "%d;;\n", cicleCounter);
				cicleCounter++;
			}

			ant = 0;
			marked = 1;
			boolean = 1;

			fprintf(f, "%d;%s;\n", cicleCounter, searchHazardNonSeparatedLines(node, node->next->next));
			cicleCounter++;
			ant = 0;
		}


		if (node->next && node->next->next && lw == 0 && determineLwHazard(node, node->next->next) && 
			searchHazardNonSeparatedLines(node->next, node->next->next)){
			fprintf(f, "%d;;\n", cicleCounter);
			cicleCounter++;
			boolean = 1;
			lw = 2;
			fprintf(f, "%d;%s|%s;\n", cicleCounter, determineLwHazard(node, node->next->next), searchHazardNonSeparatedLines(node->next, node->next->next));
			cicleCounter++;
		}
		if (node->next && node->next->next && lw == 0 && determineLwHazard(node, node->next->next) && 
			! searchHazardNonSeparatedLines(node->next, node->next->next)){
			fprintf(f, "%d;;\n", cicleCounter);
			cicleCounter++;
			boolean = 1;
			fprintf(f, "%d;%s;\n", cicleCounter, determineLwHazard(node, node->next->next));
			cicleCounter++;
		}

		if (node->next && node->next->next && searchHazardNonSeparatedLines(node, node->next->next) &&
			searchHazardNonSeparatedLines(node->next, node->next->next) && marked != 1){

			if (ant == 1){
				fprintf(f, "%d;;\n", cicleCounter);
				cicleCounter++;
			}

			ant = 0;
			marked = 1;
			boolean = 1;
			fprintf(f, "%d;%s|%s;\n", cicleCounter, searchHazardNonSeparatedLines(node, node->next->next), searchHazardNonSeparatedLines(node->next, node->next->next));
			cicleCounter++;
		}

		if (! boolean){
			fprintf(f, "%d;;\n", cicleCounter);
			cicleCounter++;
		} 

		node = node->next;
	}
	// auxiliarCounter+=3;
	// printf("%d\n", auxiliarCounter);
	// printf("%d\n", cicleCounter);
	// for (int i=0; i<auxiliarCounter; i++){
	// 	fprintf(f, "%d;;\n", cicleCounter-1);
	// 	cicleCounter++;
	// }
	fclose(f);
}

InstructionLinkedList* lineToInstruction(ListOfLines* lines){
	InstructionLinkedList* list;
	list = createInstructionLinkedList();

	LinesNode* node;
	node = lines->first;

	while (node){
		char* token;
		token = strtok(node->line, " ");

		if (strcmp(token, "add") == 0 || strcmp(token, "sub") == 0 || 
			strcmp(token, "div") == 0 || strcmp(token, "mul") == 0 || 
			strcmp(token, "beq") == 0){

			char firstOperand[20];
			char secondOperand[20];
			char thirdOperand[20];

			strcpy(firstOperand, strtok(NULL, ", "));
			strcpy(secondOperand, strtok(NULL, ", "));

			char* last = strtok(NULL, "\n");
			strcpy(thirdOperand, strndup(last+1, strlen(last)));

			appendInstruction(list, token, firstOperand, secondOperand, thirdOperand, 0, 1);

		} else if (strcmp(token, "addi") == 0 || strcmp(token, "subi") == 0){
			char firstOperand[20];
			char secondOperand[20];
			int thirdOperand;

			strcpy(firstOperand, strtok(NULL, ", "));
			strcpy(secondOperand, strtok(NULL, ", "));
			thirdOperand = atoi(strtok(NULL, "\n"));

			appendInstruction(list, token, firstOperand, secondOperand, "", thirdOperand, 2);

		} else if (strcmp(token, "j") == 0) {
			char firstOperand[20];

			strcpy(firstOperand, strtok(NULL, "\n"));

			appendInstruction(list, token, firstOperand, "", "", 0, 3);

		} else if (strcmp(token, "sw") == 0 || strcmp(token, "lw") == 0){
			char firstOperand[20];
			char secondOperand[20];
			int offset;

			strcpy(firstOperand, strtok(NULL, ", "));
			offset = atoi(strtok(NULL, "("));
			strcpy(secondOperand, strtok(NULL, ")"));

			appendInstruction(list, token, firstOperand, secondOperand, "", offset, 4);
		}

		node = node->next;
	}

	return list;
}

InstructionNode* createStall(){
	InstructionNode* node;
	node = (InstructionNode*)calloc(1, sizeof(InstructionNode));
	node->instruction = (char*)calloc(4, sizeof(char));
	node->firstOperand = "";
	node->secondOperand = "";
	node->thirdOperand = "";
	node->offset = 0;
	node->type = 0;

	strcpy(node->instruction, "NOP");

	return node;
}

InstructionNode* getIF(InstructionLinkedList* stack){
	return stack->first;
}
InstructionNode* getID(InstructionLinkedList* stack){
	// printf("hola\n");
	// printf("valor del puntero: %p\n", stack->first->next);
	if (stack->first && stack->first->next) return stack->first->next;
	return NULL;
}
InstructionNode* getEX(InstructionLinkedList* stack){
	if(stack->first && stack->first->next) return stack->first->next->next;
	return NULL;
}
InstructionNode* getMEM(InstructionLinkedList* stack){
	if(stack->first && stack->first->next && stack->first->next->next) return stack->first->next->next->next;
	return NULL;
}
InstructionNode* getWB(InstructionLinkedList* stack){
	if(stack->first && stack->first->next && 
		stack->first->next->next && stack->first->next->next->next) return stack->first->next->next->next->next;
	return NULL;
}

void printInstrutions(InstructionLinkedList* stack, FILE* f, int cycle){
		InstructionNode* nodeIF = getIF(stack);
		char* IF;
		if (nodeIF) IF = nodeIF->instruction;
		else IF = " - ";

		InstructionNode* nodeID = getID(stack);
		char* ID;
		if (nodeID) ID = nodeID->instruction;
		else ID = " - ";

		InstructionNode* nodeEX = getEX(stack);
		char* EX;
		if (nodeEX) EX = nodeEX->instruction;
		else EX = " - ";

		InstructionNode* nodeMEM = getMEM(stack);
		char* MEM;
		if (nodeMEM) MEM = nodeMEM->instruction;
		else MEM = " - ";

		InstructionNode* nodeWB = getWB(stack);
		char* WB;
		if (nodeWB) WB = nodeWB->instruction;
		else WB = " - ";

		fprintf(f, "%d;%s;%s;%s;%s;%s\n", cycle, IF, ID, EX, MEM, WB);
}

InstructionNode* createNull(){
	InstructionNode* node;
	node = (InstructionNode*)calloc(1, sizeof(InstructionNode));
	node->instruction = (char*)calloc(4, sizeof(char));
	node->firstOperand = "";
	node->secondOperand = "";
	node->thirdOperand = "";
	node->offset = 0;
	node->type = 0;

	strcpy(node->instruction, " - ");

	return node;
}

void finishPipeline(InstructionLinkedList* stack, FILE* f, int cycle){
	int newCounter = cycle;

	pushInstruction(stack, createNull());

	printInstrutions(stack, f, newCounter);
	pushInstruction(stack, createNull());
	newCounter++;

	printInstrutions(stack, f, newCounter);
	pushInstruction(stack, createNull());
	newCounter++;

	printInstrutions(stack, f, newCounter);
	pushInstruction(stack, createNull());
	newCounter++;

	printInstrutions(stack, f, newCounter);
	pushInstruction(stack, createNull());
	newCounter++;
}

void writePipelinedFile(InstructionLinkedList* instructions, char* filename){
	FILE* f;
	f = fopen(filename, "w");

	if (! f) exit(1);

	InstructionLinkedList* stack;
	stack = createInstructionLinkedList();

	fprintf(f, "CICLOS;IF;ID;EX;MEM;WB\n");

	InstructionNode* node;
	node = instructions->first;


	int cycle;
	cycle = 1;
	int lw;

	while (node){
		lw = 0;

		pushInstruction(stack, node);
		printInstrutions(stack, f, cycle);

		if (getID(stack) && getIF(stack) && determineLwHazard(getID(stack), getIF(stack))){
			lw = 1;
			popInstruction(stack);
			pushInstruction(stack, createStall());
		}

		cycle++;
		if (lw == 0) node = node->next;
	}

	finishPipeline(stack, f, cycle);

	fclose(f);
}

void run(){
	// char firstFile[100];
	// char secondFile[100];
	// char firstOutputFile[100];
	// char secondOutputFile[100];


	// printf("\nPARA EL INGRESO DE NOMBRES DE ARCHIVO, SE DEBE INCLUIR LA EXTENSIÓN. SE RECOMIENDA ARCHIVO DE TEXTO PLANO (.txt)\n\n");

	// printf("Ingrese el nombre del archivo que contiene las instrucciones de un programa MIPS: ");
	// scanf("%s", firstFile);

	// printf("Ingrese el nombre del archivo que contiene la lista con los valores de los registros: ");
	// scanf("%s", secondFile);

	// printf("Ingrese el nombre del archivo de salida que contendrá la traza del programa: ");
	// scanf("%s", firstOutputFile);

	// printf("Ingrese el nombre del archivo de salida que contendrá la traza de los registros: ");
	// scanf("%s", secondOutputFile);

	ListOfLines* linesFirstFile;
	ListOfLines* linesSecondFile;
	linesFirstFile = readFile("registers.txt");
	linesSecondFile = readFile("mips.txt");


	int* registers;
	registers = fillRegisters(linesFirstFile);

	// writePipelinedFile(linesFirstFile, registers, "prueba.csv");

	free(registers);

	InstructionLinkedList* list;
	list = lineToInstruction(linesSecondFile);

	writeHazardsFile(list, registers, "test.csv");
	writePipelinedFile(list, "pipeline.csv");

	// InstructionNode* node;
	// node = list->first;

	// while (node){
	// 	printf("Nombre instrucción: %s\nPrimer Operando: %s\nSegundo Operando: %s\nTercer Operando: %s\nOffset: %d\n\n", node->instruction, node->firstOperand, node->secondOperand, node->thirdOperand, node->offset);
	// 	node = node->next;
	// }
	
	// showTrace(linesFirstFile, restrictions, firstOutputFile, secondOutputFile);

	freeList(linesFirstFile->first);
	freeList(linesSecondFile->first);
	freeInstructionsList(list->first);

	// printf("Archivos generados correctamente!\n");
}