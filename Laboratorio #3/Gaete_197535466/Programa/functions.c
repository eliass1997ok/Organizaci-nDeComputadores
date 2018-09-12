#include "functions.h"

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

void appendResult(ResultsList* list, float hit, float miss, int associativity, int policy, int** finalState){
    Results* node;
    node = (Results*)calloc(1, sizeof(Results));

    node->hit = hit;
    node->miss = miss;
    node->associativity = associativity;
    node->policy = policy;
    node->finalState = finalState;

    if (list->length == 0){
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }

    list->length++;
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

void removeByIndex(NumberLinkedList* list, int index){
    if (list->first == NULL){
        return;
    }

    NumberNode* aux = list->first;

    if (index == 0){
        list->first = aux->next;
        list->length--;
        free(aux);
        return;
    }

    for (int i=0; aux != NULL && i < index-1; i++) aux = aux->next;

    if (aux == NULL || aux->next == NULL) return;

    NumberNode* next;
    next = aux->next->next;
    list->length--;
    aux->next = next;
}

int getIndex(NumberLinkedList* list, int element){
    NumberNode* node;
    int counter;
    
    node = list->first;
    counter = 0;

    while (node){
        if (node->number == element) return counter;

        counter++;
        node = node->next;
    }

    return -1;
}

void removeByElement(NumberLinkedList* list, int element){
    int index;
    index = getIndex(list, element);

    if (index != -1) removeByIndex(list, index);
}

int isIn(NumberLinkedList* list, int element){
    NumberNode* node;
    node = list->first;

    while (node){
        if (node->number == element) return 1;
        node = node->next;
    }

    return -1;
}

void print_usage(){
    printf("Usage: ./executable -n filename -m num -p num\n");
}

int searchSpace(int* memory, int large){
    for (int i=0; i<large; i++) if (memory[i] == -1) return i;

    return -1;
}

void reverseArray(int* array, int end){
    int temp;
    int start;
    start = 0;
    while (start < end)
    {
        temp = array[start];   
        array[start] = array[end];
        array[end] = temp;
        start++;
        end--;
    }   
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

void arrayToList(int* array, NumberLinkedList* list, int large){
    for (int i=0; i<large; i++) appendNumberList(list, array[i]);  
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

int returnPositionArray(NumberLinkedList* list, int positionInList, int* array, int large){
    NumberNode* node;
    node = list->first;

    int counter;
    counter = 0;

    while (counter != positionInList){
        counter++;
        node = node->next;
    }

    for (int i=0; i<large; i++) if (array[i] == node->number) return i;

    return -1;
}

int replaceFIFO(NumberLinkedList* list, int* array, int large){
    int min;
    min = 99999;

    for (int i=0; i<large; i++){
        int aux;
        aux = getIndex(list, array[i]);

        if (aux < min) min = aux;
    }

    return returnPositionArray(list, min, array, large);
}

int validateHit(int* numbers, int number, int large){
    for (int i=0; i<large; i++) if (numbers[i] == number) return 1;

    return 0;
}

void fifo(int blocks, NumberLinkedList* list, ResultsList* results){
    int* numbers;
    numbers = listToArray(list);

    for (int i=1; i<=blocks; i=i*2){
        int** cacheOrganization;
        float misses, hits; 
        int groups;
        hits = 0;
        misses = 0;
        groups = blocks/i;
        cacheOrganization = (int**)calloc(groups, sizeof(int*));

        for(int j=0; j<groups; j++) cacheOrganization[j] = (int*)calloc(i, sizeof(int));

        for (int iaux=0; iaux<groups; iaux++) for(int jaux=0; jaux<i; jaux++) cacheOrganization[iaux][jaux] = -1;        

        for (int counter = 0; counter < list->length; counter++){
            int data = numbers[counter];
            int positionAux = data % blocks;
            int position = positionAux / i;

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
        appendResult(results, hits, misses, i, 1, cacheOrganization);

    }
}

void lifo(int blocks, NumberLinkedList* list, ResultsList* results){
    int* numbers;
    numbers = listToArray(list);

    for (int i=1; i<=blocks; i=i*2){
        int** cacheOrganization;
        float misses, hits;
        int groups;
        hits = 0;
        misses = 0;
        groups = blocks/i;
        cacheOrganization = (int**)calloc(groups, sizeof(int*));

        for(int j=0; j<groups; j++) cacheOrganization[j] = (int*)calloc(i, sizeof(int));

        for (int iaux=0; iaux<groups; iaux++) for(int jaux=0; jaux<i; jaux++) cacheOrganization[iaux][jaux] = -1;

        for (int counter = 0; counter < list->length; counter++){
            int data = numbers[counter];
            int positionAux = data % blocks;
            int position = positionAux / i;

            int wordPosition;
            wordPosition = searchSpace(cacheOrganization[position], i);

            if (validateHit(cacheOrganization[position], data, i)){
                hits++;
            } else if (wordPosition == -1){
                misses++;
                wordPosition = i-1;
                cacheOrganization[position][wordPosition] = data;
            } else {
                misses++;
                cacheOrganization[position][wordPosition] = data;
            }
        }
        appendResult(results, hits, misses, i, 2, cacheOrganization);
    }
}

void lru(int blocks, NumberLinkedList* list, ResultsList* results){
    int* numbers;
    numbers = listToArray(list);

    for (int i=1; i<=blocks; i=i*2){
        NumberLinkedList* listUpdated;
        int** cacheOrganization;
        float misses, hits;
        int groups;
        listUpdated = createNumberList();
        hits = 0;
        misses = 0;
        groups = blocks/i;
        cacheOrganization = (int**)calloc(groups, sizeof(int*));

        for(int j=0; j<groups; j++) cacheOrganization[j] = (int*)calloc(i, sizeof(int));

        for (int iaux=0; iaux<groups; iaux++) for(int jaux=0; jaux<i; jaux++) cacheOrganization[iaux][jaux] = -1;

        for (int counter = 0; counter < list->length; counter++){
            int data = numbers[counter];
            int positionAux = data % blocks;
            int position = positionAux / i;

            int wordPosition;
            wordPosition = searchSpace(cacheOrganization[position], i);

            if (isIn(listUpdated, data) == -1){
                appendNumberList(listUpdated, data);
            } else {
                removeByElement(listUpdated, data);
                appendNumberList(listUpdated, data);
            }

            if (validateHit(cacheOrganization[position], data, i)){
                hits++;
            } else if (wordPosition == -1){
                misses++;
                wordPosition = replaceFIFO(listUpdated, cacheOrganization[position], i);
                cacheOrganization[position][wordPosition] = data;
            } else {
                misses++;
                cacheOrganization[position][wordPosition] = data;
            }
        }
        appendResult(results, hits, misses, i, 3, cacheOrganization);
    }
}

void mru(int blocks, NumberLinkedList* list, ResultsList* results){
    int* numbers;
    numbers = listToArray(list);

    for (int i=1; i<=blocks; i=i*2){
        NumberLinkedList* listUpdated;
        int** cacheOrganization;
        float misses, hits;
        int groups;
        listUpdated = createNumberList();
        hits = 0;
        misses = 0;
        groups = blocks/i;
        cacheOrganization = (int**)calloc(groups, sizeof(int*));

        for(int j=0; j<groups; j++) cacheOrganization[j] = (int*)calloc(i, sizeof(int));

        for (int iaux=0; iaux<groups; iaux++) for(int jaux=0; jaux<i; jaux++) cacheOrganization[iaux][jaux] = -1;

        for (int counter = 0; counter < list->length; counter++){
            int data = numbers[counter];
            int positionAux = data % blocks;
            int position = positionAux / i;

            int wordPosition;
            wordPosition = searchSpace(cacheOrganization[position], i);

            if (isIn(listUpdated, data) == -1){
                appendNumberList(listUpdated, data);
            } else {
                removeByElement(listUpdated, data);
                appendNumberList(listUpdated, data);
            }

            int* array;
            array = listToArray(listUpdated);
            reverseArray(array, listUpdated->length-1);
            NumberLinkedList* reverseUpdatedList;
            reverseUpdatedList = createNumberList();
            arrayToList(array, reverseUpdatedList, listUpdated->length);

            if (validateHit(cacheOrganization[position], data, i)){
                hits++;
            } else if (wordPosition == -1){
                misses++;
                wordPosition = replaceFIFO(reverseUpdatedList, cacheOrganization[position], i);
                cacheOrganization[position][wordPosition] = data;
            } else {
                misses++;
                cacheOrganization[position][wordPosition] = data;
            }
        }
        appendResult(results, hits, misses, i, 4, cacheOrganization);
    }
}

int searchMax(int* array, int large){
    int max;
    max = 0;

    for (int i=0; i<large; i++){
        if (array[i] > max){
            max = array[i];
        }
    }

    return max;
}

ResultsList* getMaxResult(ResultsList* results){
    Results* node;
    ResultsList* finalResults;
    NumberLinkedList* numberList;
    float max;
    finalResults = createResults();
    numberList = createNumberList();
    node = results->first;


    while (node){
        appendNumberList(numberList, node->hit);
        node = node->next;
    }

    max = searchMax(listToArray(numberList), numberList->length);
    node = results->first;

    while (node){
        if (node->hit == max){
            appendResult(finalResults, node->hit, node->miss, node->associativity, node->policy, node->finalState);
        }

        node = node->next; 
    }

    return finalResults;
}

void writeFileWithConfigurations(ResultsList* results, char* filename){
    FILE* f;
    f = fopen(filename, "w");

    if (! f){
        perror(filename);
        exit(1);
    }

    Results* node;
    int counter;
    counter = 0;
    node = results->first;

    while (node){
        fprintf(f, "%d.\n", counter);
        fprintf(f, "Asociatividad de la caché: %d-asociativo\n", node->associativity);

        if (node->policy == 1){
            fprintf(f, "Política de reemplazo: FIFO\n");
        } else if (node->policy == 2){
            fprintf(f, "Política de reemplazo: LIFO\n");
        } else if (node->policy == 3){
            fprintf(f, "Política de reemplazo: LRU\n");
        } else {
            fprintf(f, "Política de reemplazo: MRU\n");
        }

        fprintf(f, "Tasa de hits: %f\n", node->hit/(node->miss + node->hit));
        fprintf(f, "Tasa de miss: %f\n", node->miss/(node->miss + node->hit));
        fprintf(f, "\n");

        counter++;
        node = node->next;
    }

    fclose(f);
    printf("Archivo %s escrito satisfactoriamente.\n", filename);
}

void writeValuesOfCache(ResultsList* results, char* filename, int blocksInCache){
    FILE* f;
    f = fopen(filename, "w");

    if (! f){
        perror(filename);
        exit(1);
    }

    Results* node;
    int counter;
    counter = 0;
    node = results->first;

    while (node){  
        fprintf(f, "%d.\n", counter);
        fprintf(f, "Conjunto;Bloque;Dirección;\n");
        for (int i=0; i<blocksInCache/node->associativity; i++){
            for (int j=0; j<node->associativity; j++){
                fprintf(f, "%d;%d;%d\n", i, j, node->finalState[i][j]);
            }
        }
        fprintf(f, "\n");

        counter++;
        node = node->next; 
    }

    fclose(f);
    printf("Archivo %s escrito satisfactoriamente.\n", filename);   
}

void run(int argc, char *argv[]){
	char* filename;
    NumberLinkedList* numbers;
    int dataSize, words, option, wordsInCache, blocksInCache;
    
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

    wordsInCache = dataSize / 32;
    blocksInCache = wordsInCache / words;

    numbers = readFile(filename);

    ResultsList* results;
    results = createResults();

    fifo(blocksInCache, numbers, results);
    lifo(blocksInCache, numbers, results);
    lru(blocksInCache, numbers, results);
    mru(blocksInCache, numbers, results);

    ResultsList* finalResults;
    finalResults = getMaxResult(results);

    char filename1[50];
    printf("[>] Nombre de archivo para la(s) mejor(es) configuracion(es) de cache: ");
    scanf("%s", filename1);

    char filename2[50];
    printf("[>] Nombre de archivo ver el estado final de la cache: ");
    scanf("%s", filename2);

    writeFileWithConfigurations(finalResults, filename1);
    writeValuesOfCache(finalResults, filename2, blocksInCache);

    freeNumberList(numbers->first);
    free(filename);
}