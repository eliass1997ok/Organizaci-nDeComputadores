#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	if(lines->length == 0){
		lines->first = node;
		lines->last = node;
	}
	else{
		lines->last->next = node;
		lines->last = node;
	}

	lines->length++;

}

void freeList(LinesNode* node){
	LinesNode* aux;

	while(aux){
		aux = node;
		node = node->next;
		free(aux->line);
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

	while(aux){
		printf("%s\n", aux->line);
		aux = aux->next;
	}
	printf("\n");
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
	showList(linesSecondFile);

	free(linesSecondFile->first);
	free(linesFirstFile->first);

	return 0;
}