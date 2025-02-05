/* ptrStdQueue.h
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
#endif

#include "ptrStdList.h"

//typedef struct __ptrStdList_t ptrStdQueue_t;

// print out usefull information about ptrStdList on stdout
void ptrStdQueuePrintInfo(void);

// print out a ptrStdList on stderr
void ptrStdQueuePrint(ptrStdQueue_t* list, void (*printElem) (void*));

// create an empty ptrStdList element
ptrStdQueue_t* ptrStdQueueCreateEmpty();

// create new ptrStdList
ptrStdQueue_t* ptrStdQueueCreateNew();

// add a new element to a list
ptrStdQueue_t* ptrStdQueueAdd(ptrStdQueue_t* target, void* buffer);

// poll the first element from the queue
void* ptrStdQueuePoll(ptrStdQueue_t* target);

// free a ptrStdList
void ptrStdQueueFree(ptrStdQueue_t* target, void (*freeElem) (void*));

// convert a ptrStdList to a ptrStdQueue
ptrStdQueue_t* ptrStdQueueFromList(ptrStdList_t target);
