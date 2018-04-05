#include "functions.h"

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

void appendRestriction(RestrictionsList* list, char* instruction, char state){
	RestrictionsNode* node;
	node = (RestrictionsNode*)calloc(1, sizeof(RestrictionsNode));

	node->instruction = (char*)calloc(32, sizeof(char));

	strcpy(node->instruction, instruction);
	node->state = state;

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

	while (node){
		aux = node;
		node = node->next;
		free(aux->line);
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

void showTrace(ListOfLines* program, RestrictionsList* restrictions, char* firstOutputFile, char* secondOutputFile){
	LinesNode* node;
	int** memory;
	int* registers;
	int jump;
	int validateInstruction;

	FILE* f1;
	FILE* f2;
	f1 = fopen(firstOutputFile, "w");
	if (! f1){
		printf("Error generando el archivo %s\nSaliendo...", firstOutputFile);
		freeList(program->first);
		freeRestrictions(restrictions->first);
		exit(1);
	}

	f2 = fopen(secondOutputFile, "w");
	if (! f2){
		printf("Error generando el archivo %s\nSaliendo...", secondOutputFile);
		freeList(program->first);
		freeRestrictions(restrictions->first);
		exit(1);
	}

	registers = (int*)calloc(32, sizeof(int));
	memory = (int**)calloc(32, sizeof(int*));

	for(int i=0; i<32; i++) memory[i] = (int*)calloc(100, sizeof(int));


	fprintf(f2, "\n   INSTRUCTIONS    |$0 |$at|$v0|$v1|$a0|$a1|$a2|$a3|$t0|$t1|$t2|$t3|$t4|$t5|$t6|$t7|$s0|$s1|$s2|$s3|$s4|$s5|$s6|$s7|$t8|$t9|$k0|$k1|$gp|$sp|$fp|$ra");

	node = program->first;

	while (node){
		char* token;
		char instruction[64];
		validateInstruction = 0;
		jump = 0;

		strcpy(instruction, strtok(node->line, "\n"));
		token = strtok(node->line, " ");

		if (strcmp(token, "addi") == 0){
			validateInstruction = 1;
			jump = 3;
			fprintf(f1, "%s\n", instruction);
			fprintf(f2, "\n%s ", instruction);

			//if (searchError(restrictions, "Regwrite") == 0){
				int saveTheSum, firstOperand, secondOperand;
				token = strtok(NULL, ", ");
				saveTheSum = searchRegister(token);

				token = strtok(NULL, ", ");
				firstOperand = registers[searchRegister(token)];
				
				token = strtok(NULL, " ");
				secondOperand = atoi(token);
				
				registers[saveTheSum] = firstOperand + secondOperand;
			//}
		}
		else if (strcmp(token, "subi") == 0){
			validateInstruction = 1;
			jump = 3;
			fprintf(f1, "%s\n", instruction);
			fprintf(f2, "\n%s ", instruction);

			//if (searchError(restrictions, "Regwrite") == 0){
				int saveTheSub, firstOperand, secondOperand;
				token = strtok(NULL, ", ");
				saveTheSub = searchRegister(token);	
				
				token = strtok(NULL, ", ");
				firstOperand = registers[searchRegister(token)];

				token = strtok(NULL, " ");
				secondOperand = atoi(token);

				registers[saveTheSub] = firstOperand - secondOperand;
			//}
		}
		else if (strcmp(token, "beq") == 0){
			validateInstruction = 1;
			jump = 1;
			fprintf(f1, "%s\n", instruction);
			fprintf(f2, "\n%s", instruction);

			if (searchError(restrictions, "Branch") == 0){
				int firstRegister, secondRegister;
				token = strtok(NULL, ", ");
				firstRegister = registers[searchRegister(token)];

				token = strtok(NULL, ", ");
				secondRegister = registers[searchRegister(token)];

				if (firstRegister == secondRegister){
					jump = 2;
					token = strtok(NULL, " ");
					node = searchLabel(program, token);
				}
			}

		}
		else if (strcmp(token, "jump") == 0 || strcmp(token, "j") == 0 || strcmp(token, "Jump") == 0){
			validateInstruction = 1;
			jump = 1;
			fprintf(f1, "%s          \n", instruction);
			fprintf(f2, "\n%s          ", instruction);

			if (searchError(restrictions, "Jump") == 0){
				jump = 2;
				token = strtok(NULL, " ");
				node = searchLabel(program, token);
			}
		}
		else if (strcmp(token, "add") == 0){
			validateInstruction = 1;
			jump = 3;
			fprintf(f1, "%s\n", instruction);
			fprintf(f2, "\n%s", instruction);
			
			if (searchError(restrictions, "Regwrite") == 0){
				int saveTheSum, firstOperand, secondOperand;
				token = strtok(NULL, ", ");
				saveTheSum = searchRegister(token);

				token = strtok(NULL, ", ");
				firstOperand = registers[searchRegister(token)];

				token = strtok(NULL, " ");
				secondOperand = registers[searchRegister(token)];

				registers[saveTheSum] = firstOperand + secondOperand;
			}
		}
		else if (strcmp(token, "sub") == 0){
			validateInstruction = 1;
			jump = 3;
			fprintf(f1, "%s\n", instruction);
			fprintf(f2, "\n%s ", instruction);
			
			if (searchError(restrictions, "Regwrite") == 0){
				int saveTheSub, firstOperand, secondOperand;
				token = strtok(NULL, ", ");
				saveTheSub = searchRegister(token);	
				
				token = strtok(NULL, ", ");
				firstOperand = registers[searchRegister(token)];

				token = strtok(NULL, " ");
				secondOperand = registers[searchRegister(token)];

				registers[saveTheSub] = firstOperand - secondOperand;
			}
		}
		else if (strcmp(token, "mul") == 0){
			validateInstruction = 1;
			jump = 3;
			fprintf(f1, "%s\n", instruction);
			fprintf(f2, "\n%s", instruction);
			
			if (searchError(restrictions, "Regwrite") == 0){
				int saveTheMul, firstOperand, secondOperand;
				token = strtok(NULL, ", ");
				saveTheMul = searchRegister(token);

				token = strtok(NULL, ", ");
				firstOperand = registers[searchRegister(token)];

				token = strtok(NULL, " ");
				secondOperand = registers[searchRegister(token)];

				registers[saveTheMul] = firstOperand * secondOperand;
			}
		}
		else if (strcmp(token, "div") == 0){
			validateInstruction = 1;
			jump = 3;
			fprintf(f1, "%s\n", instruction);
			fprintf(f2, "\n%s", instruction);

			if (searchError(restrictions, "Regwrite") == 0){
				int saveTheDiv, firstOperand, secondOperand;
				token = strtok(NULL, ", ");
				saveTheDiv = searchRegister(token);

				token = strtok(NULL, ", ");
				firstOperand = registers[searchRegister(token)];

				token = strtok(NULL, " ");
				secondOperand = registers[searchRegister(token)];

				registers[saveTheDiv] = firstOperand / secondOperand;
			}
		}
		else if (strcmp(token, "lw") == 0){
			validateInstruction = 1;
			jump = 3;
			fprintf(f1, "%s   \n", instruction);
			fprintf(f2, "\n%s   ", instruction);

			if (searchError(restrictions, "Regwrite") == 0 || searchError(restrictions, "Memread") == 0){
				int saveTheValue, position, value;
				token = strtok(NULL, ", ");
				saveTheValue = searchRegister(token);

				token = strtok(NULL, "(");
				position = atoi(token) / 4;

				token = strtok(NULL, ")");
				value = memory[searchRegister(token)][position];

				registers[saveTheValue] = value;
			}
		}
		else if (strcmp(token, "sw") == 0){
			validateInstruction = 1;
			jump = 3;
			fprintf(f1, "%s   \n", instruction);
			fprintf(f2, "\n%s   ", instruction);

			if (searchError(restrictions, "Memwrite") == 0){
				int valueToSet, position, registerToSet;
				token = strtok(NULL, ", ");
				valueToSet = registers[searchRegister(token)];

				token = strtok(NULL, "(");
				position = atoi(token) / 4;

				token = strtok(NULL, ")");
				registerToSet = searchRegister(token);

				memory[registerToSet][position] = valueToSet;
			}
		}

		if (jump == 3){
			fprintf(f1, " \n");
			fprintf(f2, " ");
			node = node->next;
		}
		else if (jump == 0 || jump == 1){
			node = node->next;
		}

		if (validateInstruction != 0) for(int i=0; i<32; i++) fprintf(f2, " | %d", registers[i]);

	}
	fprintf(f2, "\n");
	for(int i=0; i<32; i++) free(memory[i]);
	free(memory);
	free(registers);
	fclose(f1);
	fclose(f2);
}

void run(){
	char firstFile[100];
	char secondFile[100];
	char firstOutputFile[100];
	char secondOutputFile[100];


	printf("\nPARA EL INGRESO DE NOMBRES DE ARCHIVO, SE DEBE INCLUIR LA EXTENSIÓN. SE RECOMIENDA ARCHIVO DE TEXTO PLANO (.txt)\n\n");

	printf("Ingrese el nombre del archivo que contiene las instrucciones de un programa MIPS: ");
	scanf("%s", firstFile);

	printf("Ingrese el nombre del archivo que contiene la lista con las líneas de control: ");
	scanf("%s", secondFile);

	printf("Ingrese el nombre del archivo de salida que contendrá la traza del programa: ");
	scanf("%s", firstOutputFile);

	printf("Ingrese el nombre del archivo de salida que contendrá la traza de los registros: ");
	scanf("%s", secondOutputFile);

	ListOfLines* linesFirstFile;
	ListOfLines* linesSecondFile;
	linesFirstFile = readFile(firstFile);
	linesSecondFile = readFile(secondFile);

	RestrictionsList* restrictions;
	restrictions = createRestrictions(linesSecondFile);

	showTrace(linesFirstFile, restrictions, firstOutputFile, secondOutputFile);

	freeList(linesSecondFile->first);
	freeList(linesFirstFile->first);
	freeRestrictions(restrictions->first);

	printf("Archivos generados correctamente!\n");
}