# Basic Memory Linked list

Valgrind is cool, but I wanted something simpilar to use which could be used as a plug and play of malloc and free.
The idea is to store the addresses and locations of the blocks in a linked list, then you can see if memory blocks are freed or not.
If the memory is not freed, then it is freed when written out to a log file.

## Use

Included `memLinkedList.h` in your project. It is a stb format so you need to define MEMMANAGEMENT_LL in your project before including it.
Use the definitions at the top of the file to change malloc and free to the impleneted functions. 
At the start of the program call `atexit(memoryLog);` to print the memory log when the program exits.
> [!NOTE]
> Calling `memoryLog` will free all memory that has not been freed.

To print allocations and frees set MEMMANAGEMENT_PRINT like MEMMANAGEMENT_LL.

## Future Work
- Add the rest of the memory allocation functions.
- Change the storage from a linked list to a binary tree.
- It would be cool to add more functionality to the program.
