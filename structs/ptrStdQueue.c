/* ptrStdQueue.c
 * part of the ptrStd libary
 *
 */
#include "ptrStdList.h"
// print out usefull information about ptrStdList on stdout
void ptrStdQueuePrintInfo() {
    return;
}


// print out a ptrStdList on stderr
void ptrStdQueuePrint(ptrStdQueue_t* list, void (*printElem) (void*)) {
    if (list == NULL) {
        return;
    }
    ptrStdList_t* temp = (ptrStdList_t*) list->next;
    ptrStdListPrint(temp, printElem);
    return;
}

// create an empty ptrStdQueue element
ptrStdQueue_t* ptrStdQueueCreateEmpty() {
    ptrStdQueue_t* new = calloc(1, sizeof(ptrStdQueue_t));
    if (new == NULL) {
        exit(ENOMEM);
    } else return new;
}

// create new ptrStdQueue
ptrStdQueue_t* ptrStdQueueCreateNew() {
    ptrStdQueue_t* new = ptrStdQueueCreateEmpty();
    return new;
}

// add a new element to a Queue
ptrStdQueue_t* ptrStdQueueAdd(ptrStdQueue_t* target, void* buffer) {
    if (target == NULL) {
        fprintf(stderr, "ptrStdListAdd: list does not exist.\n");
        exit(EINVAL);
    }

    ptrStdQueue_t* new;
    if (target->element == NULL) {
        new = (ptrStdQueue_t*) ptrStdListAdd((ptrStdList_t*) target, buffer);
    } else {
        new = (ptrStdQueue_t*) ptrStdListAdd((ptrStdList_t*) target->element, buffer);
    }
    
    target->element = new;
    return new;
}

// get the first element of the Queue
void* ptrStdQueuePoll(ptrStdQueue_t* target) {
    if (target == NULL) {
        exit(EINVAL);
    }

    if (target->next == NULL) {                     // queue is empty
        return NULL;
    } else {
        if (target->next == target->element) {      // reset end pointer if queue will be empty after poll
            target->element = NULL;
        }
        void* ret = ptrStdListGetContent((ptrStdList_t*) target->next);
        ptrStdListRemove((ptrStdList_t*) target->next);
        return ret;
    }
}
// free a ptrStdQueue
void ptrStdQueueFree(ptrStdQueue_t* target, void (*freeElem) (void*)) {
    if (target == NULL) {
        return;
    }

    if (target->next != NULL) {
        ptrStdListFree((ptrStdList_t*) target->next, freeElem);
    }

    free(target);
    return;
}

// convert a ptrStdList to a ptrStdQueue
ptrStdQueue_t* ptrStdQueueFromList(ptrStdList_t target) {
    if (target == NULL) {
        return NULL;
    }

    // get last element of the list
    ptrStdList_t* temp = target;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (temp != target) {
        target->element = temp;
    }
    return (ptrStdQueue_t*) target;
}
