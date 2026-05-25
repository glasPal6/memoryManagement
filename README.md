# Basic Memory Linked List

Simple C memory tracker for debugging, plug-and-play alternative to Valgrind for small projects or quick checks.
Tracks all allocations/frees using singly linked list, logs unfreed (leaked) pointers at exit, and frees them automatically.

## What This Is For
- Plug-in tool to find memory leaks in small C projects
- Wraps malloc/free to track allocations
- Dumps log of all unfreed allocations on exit (filename, line, function, pointer)
- Also frees any missed memory
## Usage

1. **Add the header:**
   ```c
   #include "memLinkedList.h"
   ```
   Place this in your `.c` file.

2. **Enable the memory tracker:**
   Before including the header, set:
   ```c
   #define MEMMANAGEMENT_LL
   #include "memLinkedList.h"
   ```

3. **[Optional] Enable diagnostic prints:**
   To show every alloc/free in the terminal, also define:
   ```c
   #define MEMMANAGEMENT_PRINT
   ```
   before including the header.

4. **Redirect malloc/free:**
   Define these macros *after* the header include (or in just your tests):
   ```c
   #define malloc(X) linkedListMalloc(X, __FILE__, __LINE__, __FUNCTION__)
   #define free(X) linkedListFree(X, __FILE__, __LINE__, __FUNCTION__)
   ```
   All malloc/free calls will be tracked (no code rewrite).

5. **Hook memory log at exit:**
   At start of `main()`:
   ```c
   atexit(memoryLog); // dumps leak info and cleans up
   ```

6. **Example:**
   ```c
   // enable tracker and [optional] prints
   #define MEMMANAGEMENT_LL
   // #define MEMMANAGEMENT_PRINT
   #include "memLinkedList.h"
   #define malloc(X) linkedListMalloc(X, __FILE__, __LINE__, __FUNCTION__)
   #define free(X) linkedListFree(X, __FILE__, __LINE__, __FUNCTION__)

   int main() {
       atexit(memoryLog);
       int* x = malloc(sizeof(int));
       int* y = malloc(sizeof(int));
       free(x);
       // y intentionally not freed
       return 0;
   }
   ```

7. **Run your program.**
   On exit, if anything not freed, tracker writes `memory_not_freed.txt`:
   ```
   File, Line, Function, Pointer
   main.c, 10, main, 0x12345678
   ```
   and frees remaining memory automatically.

> [!NOTE]
> Calling `memoryLog` will free all memory that has not been freed and write log file.

## Future Work
- Add calloc/realloc tracking
- Binary tree for faster lookup
- Smarter diagnostics (double free, buffer overruns)
- Wider API (stats, live inspection)
