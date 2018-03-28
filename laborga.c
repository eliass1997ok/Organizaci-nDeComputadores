#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct restrictionsNode{
	char* instruction;
	char state;
	int arguments;
	struct restrictionsNode* next;
}RestrictionsNode;

typedef struct restrictionsList{
	RestrictionsNode* first;
	RestrictionsNode* last;
	int length;
}RestrictionsList;

typedef struct linesNode{
	char* line;
	struct linesNode* next;
}LinesNode;

typedef struct listOfLines{
	LinesNode* first;
	LinesNode* last;
	int length;
}ListOfLines;

void appendLine(ListOfLines* lines, char* line){
	LinesNode* node;
	node = (LinesNode*)calloc(1, sizeof(LinesNode));

	node->line = (char*)calloc(1024, sizeof(char));

	strcpy(node->line, line);

	if (lines->length == 0){
		lines->first = node;
		lines->last = node;
	}
	else{
		lines->last->next = node;
		lines->last = node;
	}

	lines->length++;

}

void appendRestriction(RestrictionsList* list, char* instruction, char state, int arguments){
	RestrictionsNode* node;
	node = (RestrictionsNode*)calloc(1, sizeof(RestrictionsNode));

	node->instruction = (char*)calloc(32, sizeof(char));

	strcpy(node->instruction, instruction);
	node->state = state;
	node->arguments = arguments;

	if (list->length == 0){
		list->first = node;
		list->last = node;
	}
	else{
		list->last->next = node;
		list->last = node;
	}

	list->length++;
}

void freeList(LinesNode* node){
	LinesNode* aux;

	while (aux){
		aux = node;
		node = node->next;
		free(aux->line);
		free(aux);
	}
}

void freeRestrictions(RestrictionsNode* node){
	RestrictionsNode* aux;

	while (aux){
		aux = node;
		node = node->next;
		free(aux->instruction);
		free(aux);
	}
}

ListOfLines* readFile(char* nameOfFile){
	FILE* f = fopen(nameOfFile, "r");

	if (! f){
		printf("The file %s doesn't exists.\n", nameOfFile);
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

void showList(ListOfLines* list){
	LinesNode* aux;

	aux = list->first;

	while (aux){
		printf("%s\n", aux->line);
		aux = aux->next;
	}
	printf("\n");
}

void showRestrictions(RestrictionsList* list){
	RestrictionsNode* aux;
	aux = list->first;

	while (aux){
		printf("Instruction: %s\nState: %c\nArguments: %d\n", aux->instruction, aux->state, aux->arguments);
		aux = aux->next;
	}
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
		int arguments;

		token = strtok(aux->line, " ");
		strcpy(instruction, token);

		if (strcmp(token, "addi") == 0 || strcmp(token, "subi") == 0 || strcmp(token, "beq") == 0 || 
			strcmp(token, "add") == 0 || strcmp(token, "sub") == 0 || strcmp(token, "mul") == 0 ||
			strcmp(token, "div") == 0) 
			arguments = 3;
		
		if (strcmp(token, "lw") == 0 || strcmp(token, "sw") == 0)
			arguments = 2;

		if (strcmp(token, "jump") == 0 || strcmp(token, "j") == 0 || strcmp(token, "Jump") == 0)
			arguments = 1;

		token = strtok(NULL, " ");

		appendRestriction(restrictions, instruction, token[0], arguments);

		aux = aux->next;
	}

	return restrictions;
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

void showTrace(ListOfLines* program, RestrictionsList* restrictions){
	LinesNode* node;
	LinesNode* aux;
	int* registers;
	registers = (int*)calloc(32, sizeof(int));

	printf("   INSTRUCTIONS   |$0 |$at|$v0|$v1|$a0|$a1|$a2|$a3|$t0|$t1|$t2|$t3|$t4|$t5|$t6|$t7|$s0|$s1|$s2|$s3|$s4|$s5|$s6|$s7|$t8|$t9|$k0|$k1|$gp|$sp|$fp|$ra|\n");

	node = program->first;

	while (node){
		char* token;
		char instruction[64];

		strcpy(instruction, node->line);
		token = strtok(node->line, " ");

		if (strcmp(token, "addi") == 0){
			printf("%s ", instruction);

			//if (verificar si no hay error para la suma)
				int saveTheSum, firstOperand, secondOperand;
				token = strtok(NULL, ", ");
				saveTheSum = searchRegister(token);

				token = strtok(NULL, ", ");
				firstOperand = registers[searchRegister(token)];
				
				token = strtok(NULL, " ");
				secondOperand = atoi(token);
				

				registers[saveTheSum] = firstOperand + secondOperand;
			//end if
		}
		for(int i=0; i<32; i++) printf(" | %d", registers[i]);
		printf("\n");
		node = node->next;
	}

	free(registers);

}

int main(){
	char firstFile[100];
	char secondFile[100];

	printf("Ingrese el nombre del archivo que contiene las instrucciones de un programa MIPS: ");
	scanf("%s", firstFile);

	printf("Ingrese el nombre del archivo que contiene la lista con las líneas de control: ");
	scanf("%s", secondFile);

	ListOfLines* linesFirstFile;
	ListOfLines* linesSecondFile;
	linesFirstFile = readFile(firstFile);
	linesSecondFile = readFile(secondFile);

	 showList(linesFirstFile);
	// showList(linesSecondFile);

	RestrictionsList* restrictions;
	restrictions = createRestrictions(linesSecondFile);

	//showRestrictions(restrictions);

	showTrace(linesFirstFile, restrictions);

	free(linesSecondFile->first);
	free(linesFirstFile->first);

	return 0;
}