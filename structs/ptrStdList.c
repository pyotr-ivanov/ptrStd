/* ptrStdList.c
 * part of the ptrStd libary
 *
 */
#include "ptrStdList.h"


// print out usefull information about ptrStdList on stdout
void ptrStdListPrintInfo() {
    return;
}

// print out content of a ptrStdList element on stderr
void ptrStdListPrintElement(ptrStdList_t* list, void (*printElem) (void*)) {
//    void* element = ptrStdListGetContent(list);
    fprintf(stderr, "elemaddr: %p\n", list->element);
    printElem(list->element);
    return;
}

// print out a ptrStdList on stderr
void ptrStdListPrint(ptrStdList_t* list, void (*printElem) (void*)) {
    fprintf(stderr, "List contents:\n");
    if (list == NULL) {
        fprintf(stderr, "    list is empty.\n");
        return;
    }
    ptrStdList_t* temp = list;
    size_t index = 0;
    while (temp != NULL) {
        fprintf(stderr, "    [%lu]:", index);
        printElem(temp->element);
        index++;
        temp = temp->next;
    }

    return;
}

// create an empty ptrStdList element
ptrStdList_t* ptrStdListCreateEmpty() {
    ptrStdList_t* new = calloc(1, sizeof(ptrStdList_t));
    if (new == NULL) {
        exit(ENOMEM);
    } else return new;
}

// create new ptrStdList
ptrStdList_t* ptrStdListCreateNew() {
    ptrStdList_t* new = ptrStdListCreateEmpty();
    return new;
}

// add a new element to a list
ptrStdList_t* ptrStdListAdd(ptrStdList_t* target, void* buffer) {
    if (target == NULL) {
        fprintf(stderr, "ptrStdListAdd: list does not exist.\n");
        exit(EINVAL);
    }

    ptrStdList_t* new = ptrStdListCreateEmpty();

    ptrStdList_t* temp = target;    // append new element to list
    if (temp != NULL) {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new;
        new->previous = temp;
    }

    new->element = buffer;

    return new;
}

// free a ptrStdList
void ptrStdListFree(ptrStdList_t* target, void (*freeElem) (void*)) {
    ptrStdList_t* temp = target;
    ptrStdList_t* te_next;

    while (temp != NULL) {  
        if (freeElem != NULL) {         // free element
            freeElem(temp->element);
        }
        te_next = temp->next;
        free(temp);
        temp = te_next;
    }

    return;
}

// search for an element in the ptrStdList 
ptrStdList_t* ptrStdListSearch(ptrStdList_t* target, void* condition, bool(*compElem) (void*, void*)) {
    if (compElem == NULL) {
        fprintf(stderr, "ptrStdListSearch(): exit due to invalid function pointer\n");
        exit(EINVAL);
    }
    ptrStdList_t* temp = target;

    while (temp != NULL) {
        if (compElem(temp->element, condition)) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

// return the content of the given ptrStdList element
void* ptrStdListGetContent(ptrStdList_t* target) {
    if (target == NULL) {
        fprintf(stderr, "ptrStdListGetContent(): exit due to invalid element pointer\n");
        exit(EINVAL);
    }

    return target->element;
}

// remove a ptrStdList element from a ptrStdList
void ptrStdListRemove(ptrStdList_t* target) { 
    if (target == NULL) {
        fprintf(stderr, "ptrStdListRemove(): exit due to invalid element pointer\n");
        exit(EINVAL);
    }


    if (target->previous != NULL) {
        target->previous->next = target->next;
    }


    if (target->next != NULL) {
        target->next->previous = target->previous;
    }

    free(target);
    return;
}

// search for an element in a ptrStdList, return its content and remove it from the list
void* ptrStdListExtract(ptrStdList_t* target, void* condition, bool(*compElem) (void*, void*)) {
    if (compElem == NULL) {
        fprintf(stderr, "ptrStdListSearch(): exit due to invalid function pointer\n");
        exit(EINVAL);
    }

    ptrStdList_t* temp = ptrStdListSearch(target, condition, compElem);

    if (temp == NULL) return NULL;
    void* content = ptrStdListGetContent(temp);
    ptrStdListRemove(temp);

    return content;
}
