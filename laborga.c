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

// void showTrace(ListOfLines* program, RestrictionsList* restrictions){
// 	int* registers;
// 	registers = (int*)calloc(32, sizeof(int));

	

// }

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

	// showList(linesFirstFile);
	// showList(linesSecondFile);

	RestrictionsList* restrictions;
	restrictions = createRestrictions(linesSecondFile);

	showRestrictions(restrictions);

	free(linesSecondFile->first);
	free(linesFirstFile->first);

	return 0;
}