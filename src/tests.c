#include <stdio.h>

#include "memLinkedList.h"
#define malloc(X) linkedListMalloc(X, __FILE__, __LINE__, __FUNCTION__)
#define free(X) linkedListFree(X, __FILE__, __LINE__, __FUNCTION__)

int main() {
    // Basic test
    printf("Basic allocation and free\n");
    int *ptr = malloc(sizeof(int));
    free(ptr);

    char *ptr2 = malloc(sizeof(char));
    free(ptr2);

    // Different order of frees
    printf("\nDifferend order of allocations and frees\n");
    int *ptr3 = malloc(sizeof(int));
    int *ptr4 = malloc(sizeof(int));
    int *ptr5 = malloc(sizeof(int));
    free(ptr5);
    free(ptr4);
    free(ptr3);

    // Basic non free
    printf("\nBasic non free\n");
    char *ptr6 = malloc(sizeof(char));
    /*free(ptr6);*/

    // One not freed
    printf("\nDifferent order of allocations and frees with one not freed\n");
    int *ptr7 = malloc(sizeof(int));
    int *ptr8 = malloc(sizeof(int));
    int *ptr9 = malloc(sizeof(int));
    free(ptr9);
    /*free(ptr8);*/
    free(ptr7);

    FILE *log_file = fopen("log_memory.txt", "w");
    printMemoryLog(log_file);
    /*printMemoryLog(stdout);*/
    fclose(log_file);
    return 0;
}
