#include <stdio.h>
#include <stdlib.h>

// ----------------------------------------------------------------------------
// Place these to change the functioning of malloc at the head of the program
// ----------------------------------------------------------------------------
// #define malloc(X) linkedListMalloc(X, __FILE__, __LINE__, __FUNCTION__)
// #define free(X) linkedListFree(X, __FILE__, __LINE__, __FUNCTION__)
// ----------------------------------------------------------------------------

void *linkedListMalloc(size_t size, const char *src_file, int line,
                       const char *func);
void *linkedListFree(void *ptr, const char *src_file, int line,
                     const char *func);

void printMemoryLog(FILE *file);

#ifdef MEMMANAGEMENT_LL

typedef struct Node {
    struct Node *next;
    const char *file;
    int line;
    const char *func;
    void *ptr;
} Node;
Node *head = NULL;

void *linkedListMalloc(size_t size, const char *src_file, int line,
                       const char *func) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("Error: malloc failed in %s:%d:%s\n", src_file, line, func);
    }
#ifdef MEMMANAGEMENT_PRINT
    printf("Allocated: %s, %i, %s, %p[%li]\n", src_file, line, func, ptr, size);
#endif

    if (head == NULL) {
        head = malloc(sizeof(Node));
        head->next = NULL;
        head->file = src_file;
        head->line = line;
        head->func = func;
        head->ptr = ptr;
    } else {
        Node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = malloc(sizeof(Node));
        current->next->next = NULL;
        current->next->file = src_file;
        current->next->line = line;
        current->next->func = func;
        current->next->ptr = ptr;
    }

    return ptr;
}

void *linkedListFree(void *ptr, const char *src_file, int line,
                     const char *func) {
    if (head == NULL) {
        printf("Error: linkedListFree failed in %s:%d:%s\n", src_file, line,
               func);
    } else if (head->next == NULL) {
        if (head->ptr == ptr) {
            free(head);
            head = NULL;
        }
    } else {
        Node *current = head;
        while (current->next != NULL) {
            if (current->next->ptr == ptr) {
                Node *temp = current->next;
                current->next = current->next->next;
                free(temp);
                break;
            } else {
                current = current->next;
            }
        }
    }

    free(ptr);
#ifdef MEMMANAGEMENT_PRINT
    printf("Freed: %s, %i, %s, %p\n", src_file, line, func, ptr);
#endif

    return NULL;
}

void printMemoryLog(FILE *file) {
    if (head != NULL)
        fprintf(file, "File, Line, Function, Pointer\n");
    Node *current = head;
    while (current != NULL) {
        fprintf(file, "%s, %i, %s, %p\n", current->file, current->line,
                current->func, current->ptr);
        Node *temp = current;
        current = current->next;
        free(temp->ptr);
        free(temp);
    }
}

#endif // MEMMANAGEMENT_LL
