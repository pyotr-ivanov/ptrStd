/* ptrStdBuffer.h
 * part of the ptrStd libary
 *
 */
#ifndef PTRSTD_COMMON
#define PTRSTD_COMMON 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#endif // !

typedef struct __ptrStdBuffer_t {
    size_t len;
    void* data;
}ptrStdBuffer_t;

// print out usefull information about ptrStdBuffer on stdout
void ptrStdBufferPrintInfo(void);

// print out buffer info on stderr
void ptrStdBufferPrint(void* target);
// create a empty buffer
ptrStdBuffer_t* ptrStdBufferCreateEmpty(size_t capacity);

// create a nonempty buffer
ptrStdBuffer_t* ptrStdBufferCreate(size_t capacity, void* content, size_t contentLength);

// free a buffer
void ptrStdBufferFree(void* target);

// return the content of a buffer
void* ptrStdBufferGetContent(ptrStdBuffer_t* target);

// compare two buffers
bool ptrStdBufferComp(void* a, void* b);
