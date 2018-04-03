#pragma once
#include "structs.h"

void appendLine(ListOfLines* lines, char* line);
void appendRestriction(RestrictionsList* list, char* instruction, char state, int arguments);
void freeList(LinesNode* node);
void freeRestrictions(RestrictionsNode* node);
ListOfLines* readFile(char* nameOfFile);
void showList(ListOfLines* list);
void showRestrictions(RestrictionsList* list);
RestrictionsList* createRestrictions(ListOfLines* lines);
LinesNode* searchLabel(ListOfLines* list, char* label);
int searchRegister(char* registerString);
int searchError(RestrictionsList* restrictions, char* instruction);
void showTrace(ListOfLines* program, RestrictionsList* restrictions, char* firstOutputFile, char* secondOutputFile);
void run();