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

void appendInstruction(InstructionLinkedList* list, char* instruction, char* firstOperand, char* secondOperand, char* thirdOperand, int offset, int type, char* label){
	InstructionNode* node;
	node = (InstructionNode*)calloc(1, sizeof(InstructionNode));

	node->instruction = (char*)calloc(32, sizeof(char));
	node->firstOperand = (char*)calloc(6, sizeof(char));
	node->secondOperand = (char*)calloc(10, sizeof(char));
	node->thirdOperand = (char*)calloc(10, sizeof(char));
	node->label = (char*)calloc(10, sizeof(char));

	strcpy(node->instruction, instruction);
	strcpy(node->firstOperand, firstOperand);
	strcpy(node->secondOperand, secondOperand);
	strcpy(node->thirdOperand, thirdOperand);
	strcpy(node->label, label);
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
		appendLine(lines, buffer);
	}

	return lines;
}

int searchRegister(char* registerString){
	if (strcmp(registerString, "$zero") == 0 || strcmp(registerString, "$zero)") == 0) return 0;
	if (strcmp(registerString, "$at") == 0 || strcmp(registerString, "$at)") == 0) return 1;
	if (strcmp(registerString, "$v0") == 0 || strcmp(registerString, "$v0)") == 0) return 2;
	if (strcmp(registerString, "$v1") == 0 || strcmp(registerString, "$v1)") == 0) return 3;
	if (strcmp(registerString, "$a0") == 0 || strcmp(registerString, "$a0)") == 0) return 4;
	if (strcmp(registerString, "$a1") == 0 || strcmp(registerString, "$a1)") == 0) return 5;
	if (strcmp(registerString, "$a2") == 0 || strcmp(registerString, "$a2)") == 0) return 6;
	if (strcmp(registerString, "$a3") == 0 || strcmp(registerString, "$a3)") == 0) return 7;
	if (strcmp(registerString, "$t0") == 0 || strcmp(registerString, "$t0)") == 0) return 8;
	if (strcmp(registerString, "$t1") == 0 || strcmp(registerString, "$t1)") == 0) return 9;
	if (strcmp(registerString, "$t2") == 0 || strcmp(registerString, "$t2)") == 0) return 10;
	if (strcmp(registerString, "$t3") == 0 || strcmp(registerString, "$t3)") == 0) return 11;
	if (strcmp(registerString, "$t4") == 0 || strcmp(registerString, "$t4)") == 0) return 12;
	if (strcmp(registerString, "$t5") == 0 || strcmp(registerString, "$t5)") == 0) return 13;
	if (strcmp(registerString, "$t6") == 0 || strcmp(registerString, "$t6)") == 0) return 14;
	if (strcmp(registerString, "$t7") == 0 || strcmp(registerString, "$t7)") == 0) return 15;
	if (strcmp(registerString, "$s0") == 0 || strcmp(registerString, "$s0)") == 0) return 16;
	if (strcmp(registerString, "$s1") == 0 || strcmp(registerString, "$s1)") == 0) return 17;
	if (strcmp(registerString, "$s2") == 0 || strcmp(registerString, "$s2)") == 0) return 18;
	if (strcmp(registerString, "$s3") == 0 || strcmp(registerString, "$s3)") == 0) return 19;
	if (strcmp(registerString, "$s4") == 0 || strcmp(registerString, "$s4)") == 0) return 20;
	if (strcmp(registerString, "$s5") == 0 || strcmp(registerString, "$s5)") == 0) return 21;
	if (strcmp(registerString, "$s6") == 0 || strcmp(registerString, "$s6)") == 0) return 22;
	if (strcmp(registerString, "$s7") == 0 || strcmp(registerString, "$s7)") == 0) return 23;
	if (strcmp(registerString, "$t8") == 0 || strcmp(registerString, "$t8)") == 0) return 24;
	if (strcmp(registerString, "$t9") == 0 || strcmp(registerString, "$t9)") == 0) return 25;
	if (strcmp(registerString, "$k0") == 0 || strcmp(registerString, "$k0)") == 0) return 26;
	if (strcmp(registerString, "$k1") == 0 || strcmp(registerString, "$k1)") == 0) return 27;
	if (strcmp(registerString, "$gp") == 0 || strcmp(registerString, "$gp)") == 0) return 28;
	if (strcmp(registerString, "$sp") == 0 || strcmp(registerString, "$sp)") == 0) return 29;
	if (strcmp(registerString, "$fp") == 0 || strcmp(registerString, "$fp)") == 0) return 30;
	if (strcmp(registerString, "$ra") == 0 || strcmp(registerString, "$ra)") == 0) return 31;
	return -1;
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
	if (strcmp(firstLine->instruction, "lw") == 0  && nextLine && (nextLine->type == 1 || nextLine->type == 2) && strcmp(nextLine->instruction, "beq") != 0 && 
		(strcmp(firstLine->firstOperand, nextLine->thirdOperand) == 0 || strcmp(firstLine->firstOperand, nextLine->secondOperand) == 0) )

		return firstLine->firstOperand;

	return NULL;
}

InstructionNode* searchJump(InstructionLinkedList* instructions, char* label){
	InstructionNode* aux;
	aux = instructions->first;

	while (aux){
		if (! strcmp(aux->label, label)) return aux;

		aux = aux->next;
	}

	return NULL;
}

void doTheOperation(InstructionNode* instruction, int* registers, int** memory){
	if (strcmp(instruction->instruction, "addi") == 0)
		registers[searchRegister(instruction->firstOperand)] = registers[searchRegister(instruction->secondOperand)] + instruction->offset;
	else if (strcmp(instruction->instruction, "subi") == 0)
		registers[searchRegister(instruction->firstOperand)] = registers[searchRegister(instruction->secondOperand)] - instruction->offset;
	else if (strcmp(instruction->instruction, "add") == 0)
		registers[searchRegister(instruction->firstOperand)] = registers[searchRegister(instruction->secondOperand)] + registers[searchRegister(instruction->thirdOperand)];
	else if (strcmp(instruction->instruction, "sub") == 0)
		registers[searchRegister(instruction->firstOperand)] = registers[searchRegister(instruction->secondOperand)] - registers[searchRegister(instruction->thirdOperand)];
	else if (strcmp(instruction->instruction, "mul") == 0)
		registers[searchRegister(instruction->firstOperand)] = registers[searchRegister(instruction->secondOperand)] * registers[searchRegister(instruction->thirdOperand)];
	else if (strcmp(instruction->instruction, "div") == 0)
		registers[searchRegister(instruction->firstOperand)] = registers[searchRegister(instruction->secondOperand)] / registers[searchRegister(instruction->thirdOperand)];
	else if (strcmp(instruction->instruction, "sw") == 0)
		memory[searchRegister(instruction->secondOperand)][instruction->offset/4] = registers[searchRegister(instruction->firstOperand)];
	else if (strcmp(instruction->instruction, "lw") == 0)
		registers[searchRegister(instruction->firstOperand)] = memory[searchRegister(instruction->secondOperand)][instruction->offset/4];
}

void writeHazardsFile(InstructionLinkedList* instructions, char* outputFile, int* registers, int** memory){
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

	int jump;
	jump = 0;

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
		jump = 0;
		doTheOperation(node, registers, memory);
		if (node->next && searchHazardNonSeparatedLines(node, node->next) && marked == 0 && lw != 2){

			fprintf(f, "%d;%s;\n", cicleCounter, searchHazardNonSeparatedLines(node, node->next));
			cicleCounter++;
			boolean = 1;
			ant = 0;
		}

		lw = 0;
		marked = 0;

		if (node->next && determineLwHazard(node, node->next)){
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

		if (strcmp(node->instruction, "beq") == 0){
			fprintf(f, "%d;;X\n", cicleCounter);
			cicleCounter++;
			if (registers[searchRegister(node->firstOperand)] == registers[searchRegister(node->secondOperand)]){
				jump = 1;
				node = searchJump(instructions, node->thirdOperand);
			} else {
				fprintf(f, "%d;;X\n", cicleCounter);
				cicleCounter++;
				fprintf(f, "%d;;X\n", cicleCounter);
				cicleCounter++;
			}
		}

		if (node && strcmp(node->instruction, "j") == 0){
			fprintf(f, "%d;;X\n", cicleCounter);
			cicleCounter++;
			jump = 1;
			node = searchJump(instructions, node->firstOperand);			
		}

		if (! boolean){
			fprintf(f, "%d;;\n", cicleCounter);
			cicleCounter++;
		} 
		if (! jump){
			node = node->next;	
		}
		
	}

	fclose(f);
}

InstructionLinkedList* instructionLine(char* filename){
	FILE* f;
	f = fopen(filename, "r");

	if (! f){
		perror(filename);
		exit(1);
	}

	InstructionLinkedList* list;
	list = createInstructionLinkedList();

	int label;
	label = 0;

	char labelName[10];

	while(! feof(f)){
		char instruction[20];

		fscanf(f, "%s", instruction);

		if (strcmp(instruction, "add") == 0 || strcmp(instruction, "sub") == 0 || 
			strcmp(instruction, "div") == 0 || strcmp(instruction, "mul") == 0 || 
			strcmp(instruction, "beq") == 0){

			char firstOperand[20];
			char secondOperand[20];
			char thirdOperand[20];
			fscanf(f, "%s %s %s", firstOperand, secondOperand, thirdOperand);

			if (! label){
				appendInstruction(list, instruction, firstOperand, secondOperand, thirdOperand, 0, 1, "");
			} else {
				appendInstruction(list, instruction, firstOperand, secondOperand, thirdOperand, 0, 1, labelName);
				label = 0;
			}
		} else if (strcmp(instruction, "addi") == 0 || strcmp(instruction, "subi") == 0){
			char firstOperand[20];
			char secondOperand[20];
			int thirdOperand = 0;

			fscanf(f, "%s %s %d", firstOperand, secondOperand, &thirdOperand);

			if (! label){
				appendInstruction(list, instruction, firstOperand, secondOperand, "", thirdOperand, 2, "");

			} else {
				appendInstruction(list, instruction, firstOperand, secondOperand, "", thirdOperand, 2, labelName);
				label = 0;	
			}
		} else if (strcmp(instruction, "j") == 0) {
			char firstOperand[20];

			fscanf(f, "%s", firstOperand);

			if (! label){
				appendInstruction(list, instruction, firstOperand, "", "", 0, 3, "");

			} else {
				appendInstruction(list, instruction, firstOperand, "", "", 0, 3, labelName);
				label = 0;	
			}
		} else if (strcmp(instruction, "sw") == 0 || strcmp(instruction, "lw") == 0){
			char firstOperand[20];
			char secondOperand[20];
			int offset = 0;

			fscanf(f, "%s %d(%s)", firstOperand, &offset, secondOperand);

			if (! label){
				appendInstruction(list, instruction, firstOperand, secondOperand, "", offset, 4, "");

			} else {
				appendInstruction(list, instruction, firstOperand, secondOperand, "", offset, 4, labelName);
				label = 0;
			}
		} else {
			char* token;
			label = 1;
			token = strtok(instruction, ":\n");
			strcpy(labelName, token);
		}
	}

	fclose(f);

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

void printInstructions(InstructionLinkedList* stack, FILE* f, int cycle){
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

	printInstructions(stack, f, newCounter);
	pushInstruction(stack, createNull());
	newCounter++;

	printInstructions(stack, f, newCounter);
	pushInstruction(stack, createNull());
	newCounter++;

	printInstructions(stack, f, newCounter);
	pushInstruction(stack, createNull());
	newCounter++;

	printInstructions(stack, f, newCounter);
	pushInstruction(stack, createNull());
	newCounter++;
}

int beq(InstructionNode* node, int* registers){
	if (registers[searchRegister(node->firstOperand)] == registers[searchRegister(node->secondOperand)])
		return 1;

	return 0;
}

void writePipelinedFile(InstructionLinkedList* instructions, char* filename, int* registers, int** memory){
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
	int lw = 0;

	while (node){
		pushInstruction(stack, node);
		printInstructions(stack, f, cycle);

		InstructionNode* ID;
		ID = getID(stack);

		if (! lw)	doTheOperation(node, registers, memory);
		
		lw = 0;

		if (ID && getIF(stack) && determineLwHazard(ID, getIF(stack))){
			lw = 1;
			popInstruction(stack);
			pushInstruction(stack, createStall());
		}


		if (strcmp(node->instruction, "beq") == 0 || strcmp(node->instruction, "j") == 0){
			int mark = 0;
			if (node->next){
				pushInstruction(stack, node->next);
				cycle++;
				printInstructions(stack, f, cycle);
				popInstruction(stack);
				pushInstruction(stack, createStall());
			}


			if (strcmp(node->instruction, "j") != 0 && beq(node, registers)){
				mark = 1;
				lw = 1;
				node = searchJump(instructions, node->thirdOperand);
			}

			if (node && strcmp(node->instruction, "j") == 0){
				mark = 1;
				lw = 1;
				node = searchJump(instructions, node->firstOperand);
			} 
			if (! mark){
				InstructionNode* jumpedNode;
				jumpedNode = searchJump(instructions, node->thirdOperand);
				if (jumpedNode){
					pushInstruction(stack, jumpedNode);
					cycle++;
					printInstructions(stack, f, cycle);
					if(jumpedNode->next){
						pushInstruction(stack, jumpedNode->next);
						cycle++;
						printInstructions(stack, f, cycle);
						popInstruction(stack);
						popInstruction(stack);
						cycle++;
						pushInstruction(stack, createStall());
						pushInstruction(stack, createStall());

					} else {
						popInstruction(stack);
						cycle++;
						pushInstruction(stack, createStall());
					}
				}
			}	
		}

		cycle++;
		
		if (lw == 0) node = node->next;
	}

	finishPipeline(stack, f, cycle);

	fclose(f);
}

void run(){
	char firstFile[100];
	char secondFile[100];
	char firstOutputFile[100];
	char secondOutputFile[100];
	char thirdOutputFile[100];

	printf("\nPARA EL INGRESO DE NOMBRES DE ARCHIVO, SE DEBE INCLUIR LA EXTENSIÓN. SE RECOMIENDA ARCHIVO DE TEXTO PLANO PARA LAS ENTRADAS (.txt) MIENTRAS QUE PARA LA SALIDA, DEBE SER UN ARCHIVO .csv\n\n");

	printf("Ingrese el nombre del archivo que contiene las instrucciones de un programa MIPS: ");
	scanf("%s", firstFile);

	printf("Ingrese el nombre del archivo que contiene la lista con los valores de los registros: ");
	scanf("%s", secondFile);

	printf("Ingrese el nombre del archivo de salida que contendrá la traza del programa (pipelined): ");
	scanf("%s", firstOutputFile);

	printf("Ingrese el nombre del archivo de salida que contendrá la detección de hazards: ");
	scanf("%s", secondOutputFile);

	printf("Ingrese el nombre del archivo de salida que contendrá la traza multiple-issue: ");
	scanf("%s", thirdOutputFile);

	ListOfLines* linesFirstFile;
	linesFirstFile = readFile(secondFile);

	InstructionLinkedList* list;
	list = instructionLine(firstFile);

	int* registers1;
	registers1 = fillRegisters(linesFirstFile);

	int* registers2;
	registers2 = (int*)calloc(32, sizeof(int));

	for (int i=0; i<32; i++) registers2[i] = registers1[i];

	int** memory1;
	memory1 = (int**)calloc(32, sizeof(int*));

	for (int i=0; i<32; i++) memory1[i] = (int*)calloc(100, sizeof(int));

	int** memory2;
	memory2 = (int**)calloc(32, sizeof(int*));

	for (int i=0; i<32; i++) memory2[i] = (int*)calloc(100, sizeof(int));

	writeHazardsFile(list, secondOutputFile, registers1, memory1);
	writePipelinedFile(list, firstOutputFile, registers2, memory2);
	
	freeInstructionsList(list->first);

	printf("Archivos generados correctamente!\n");
}