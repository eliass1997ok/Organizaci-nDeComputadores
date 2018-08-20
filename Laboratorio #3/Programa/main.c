#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

typedef struct results{
    int hit;
    int miss;
    int associativity;
    int policy;
    int** finalState;
    struct results* next;
}Results;

typedef struct resultsList{
    Results* first;
    Results* last;
    int length;
}ResultsList;

typedef struct numberNode{
    int number;
    struct numberNode* next;
}NumberNode;

typedef struct numberLinkedList{
    NumberNode* first;
    NumberNode* last;
    int length;
}NumberLinkedList;

ResultsList* createResults(){
    ResultsList* list;
    list = (ResultsList*)calloc(1, sizeof(ResultsList));

    list->first = NULL;
    list->last = NULL;
    list->length = 0;

    return list;
}

NumberLinkedList* createNumberList(){
    NumberLinkedList* list;
    list = (NumberLinkedList*)calloc(1, sizeof(NumberLinkedList));

    list->first = NULL;
    list->last = NULL;
    list->length = 0;

    return list;
}

void appendResult(ResultsList* list, int hit, int miss, int associativity, int policy, int** finalState){

}

void appendNumberList(NumberLinkedList* list, int number){
    NumberNode* node;
    node = (NumberNode*)calloc(1, sizeof(NumberNode));

    node->number = number;

    if (list->length == 0){
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }

    list->length++;
}

void freeNumberList(NumberNode* node){
    NumberNode* aux;

    while (node){
        aux = node;
        node = node->next;
        free(aux);
    }
}

void printGroups(int blocks){
    for (int i=1; i<=blocks; i=i*2) if (blocks % i == 0) printf("blocks per group: %d number of groups: %d\n", i, blocks/i);
}

void print_usage() {
    printf("Usage: ./executable -n filename -m num -p num\n");
}

int searchSpace(int* memory, int large){
    for (int i=0; i<large; i++) if (! memory[i]) return i;

    return -1;
}


int* listToArray(NumberLinkedList* list){
    int* numbers;
    numbers = (int*)calloc(list->length, sizeof(int));

    NumberNode* aux;
    aux = list->first;
    int counter;
    counter = 0;

    while (aux){
        numbers[counter] = aux->number;
        counter++;
        aux = aux->next;
    }

    return numbers;
}

NumberLinkedList* readFile(char* filename){
    FILE* f;
    f = fopen(filename, "r");

    if (!f){
        perror(filename);
        exit(EXIT_FAILURE);
    }

    NumberLinkedList* list;
    list = createNumberList();

    while (! feof(f)){
        int number;
        fscanf(f, "%d\n", &number);
        appendNumberList(list, number);
    }

    fclose(f);

    return list;
}

int searchInList(NumberLinkedList* list, int number){
    NumberNode* node;
    node = list->first;
    int counter;
    counter = 0;

    while (node){
        if (node->number == number) return counter;

        counter++;
        node = node->next;
    }

    return -1;
}

int replaceFIFO(NumberLinkedList* list, int* array, int large){
    int min;
    min = 99999;

    for (int i=0; i<large; i++){
        int aux;
        aux = searchInList(list, array[i]);

        if (aux < min) min = aux;
    }

    return min;

}

int validateHit(int* numbers, int number, int large){
    for (int i=0; i<large; i++) if (numbers[i] == number) return 1;

    return 0;
}

void fifo(int blocks, NumberLinkedList* list){
    int* numbers;
    numbers = listToArray(list);

    for (int i=1; i<=blocks; i=i*2){
        int** cacheOrganization;
        int misses, hits, groups;
        hits = 0;
        misses = 0;
        groups = blocks/i;
        cacheOrganization = (int**)calloc(groups, sizeof(int*));

        for(int j=0; j<groups; j++) cacheOrganization[j] = (int*)calloc(i, sizeof(int));

        for (int counter = 0; counter < list->length; counter++){
            int data = numbers[counter];
            int position = data % groups;

            int wordPosition;
            wordPosition = searchSpace(cacheOrganization[position], i);

            if (validateHit(cacheOrganization[position], data, i)){
                hits++;
            } else if (wordPosition == -1){
                misses++;
                wordPosition = replaceFIFO(list, cacheOrganization[position], i);
                cacheOrganization[position][wordPosition] = data;
            } else {
                misses++;
                cacheOrganization[position][wordPosition] = data;
            }
        }

        for (int iaux = 0; iaux<groups; iaux++){
            for (int jaux = 0; jaux<i; jaux++){
                printf(" %d ", cacheOrganization[iaux][jaux]);
            }
            printf("\n");
        }

        printf("hit: %d\nmiss: %d", hits, misses);

        printf("\n");
    }
}

int main(int argc, char *argv[]){
    char* filename;
    NumberLinkedList* numbers;
    int dataSize, words, option, wordsInCache, blocksInCache, amountOfNumbers;
    
    filename = (char*)calloc(30, sizeof(char));

	option = 0;

	while ((option = getopt(argc, argv, "n:m:p:")) != -1) {
		switch (option) {
			 case 'n' : strcpy(filename, optarg);
			 	 break;
             case 'm' : dataSize = atoi(optarg); 
                 break;
             case 'p' : words = atoi(optarg);
                 break;
             default: print_usage(); 
                 exit(EXIT_FAILURE);
        }
    }

    printf("filename: %s \nmemory: %d \nwords: %d\n", filename, dataSize, words);
    wordsInCache = dataSize / 32;
    blocksInCache = wordsInCache / words;
    printf("Words in cache: %d\nBlocks in cache: %d\n", wordsInCache, blocksInCache);

    printGroups(blocksInCache);
    numbers = readFile(filename);

    fifo(blocksInCache, numbers);

    freeNumberList(numbers->first);
    free(filename);

	return 0;
}