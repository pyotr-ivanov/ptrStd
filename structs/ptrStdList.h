/* ptrStdList.h
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

typedef struct __ptrStdList_t {
    void* element;
    struct __ptrStdList_t* previous;
    struct __ptrStdList_t* next;
}ptrStdList_t;

// print out usefull information about ptrStdList on stdout
void ptrStdListPrintInfo(void);

// print out content of a ptrStdList element on stderr
void ptrStdListPrintElement(ptrStdList_t* list, void (*printElem) (void*));

// print out a ptrStdList on stderr
void ptrStdListPrint(ptrStdList_t* list, void (*printElem) (void*));

// create an empty ptrStdList element
ptrStdList_t* ptrStdListCreateEmpty();

// create new ptrStdList
ptrStdList_t* ptrStdListCreateNew();

// add a new element to a list
ptrStdList_t* ptrStdListAdd(ptrStdList_t* target, void* buffer);

// free a ptrStdList
void ptrStdListFree(ptrStdList_t* target, void (*freeElem) (void*));

// search for an element in the ptrStdList 
ptrStdList_t* ptrStdListSearch(ptrStdList_t* target, void* condition, bool(*compElem) (void*, void*));

// return the content of the given ptrStdList element
void* ptrStdListGetContent(ptrStdList_t* target);

// remove a ptrStdList element from a ptrStdList
void ptrStdListRemove(ptrStdList_t* target);

// search for an element in a ptrStdList, return its content and remove it from the list
void* ptrStdListExtract(ptrStdList_t* target, void* condition, bool(*compElem) (void*, void*));
