#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

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