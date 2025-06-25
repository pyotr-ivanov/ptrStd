/* ptrStdTree.c
 * part of the ptrStd libary
 *
 */

#include "ptrStdTree.h"

// print usefull information about ptrStdTree on stdout
void ptrStdTreePrintInfo() {
    return;
}

// create an empty node
ptrStdTreeNode_t* ptrStdTreeCreateNode(void * element) {
    if (element == NULL) {
        fprintf(stderr, "ptrStdTreeCreateNode(): called exit(). element is NULL\n");
        exit(EINVAL);
    }

    ptrStdTreeNode_t* new = calloc(1, sizeof(ptrStdTreeNode_t));
    if (new == NULL) exit(ENOMEM);
    else {
        new->element = element;
        return new;
    }
}

// create and append a new node to an existing tree.
ptrStdTreeNode_t* ptrStdTreeAppend(ptrStdTreeNode_t* target, bool (*isGreater) (void*, void*), void* element) {
    if (target == NULL || element == NULL || isGreater == NULL) {
        fprintf(stderr, "ptrStdTreeAppend(): exit due to invalid pointer\n");
        exit(EINVAL);
    }

    if (isGreater(target->element, element)) {      // isGreater() == true
        if (target->child_h == NULL) return ptrStdTreeAppendHigh(target, element);
        else return ptrStdTreeAppend(target->child_h, isGreater, element);
    } else {                                        // isGreater() == false
        if (target->child_l == NULL) return ptrStdTreeAppendLow(target, element);
        else return ptrStdTreeAppend(target->child_l, isGreater, element);
    }
}

// append a new node to child_l
ptrStdTreeNode_t* ptrStdTreeAppendLow(ptrStdTreeNode_t* target, void* element) {
    if (target == NULL || element == NULL) {
        fprintf(stderr, "ptrStdTreeAppend(): exit due to invalid pointer\n");
        exit(EINVAL);
    }
    ptrStdTreeNode_t* new = ptrStdTreeCreateNode(element);
    target->child_l = new;
    new->parent = target;
    new->depth = target->depth + 1
    return new;
}

// append a new node to child_h
ptrStdTreeNode_t* ptrStdTreeAppendHigh(ptrStdTreeNode_t* target, void* element) {
    if (target == NULL || element == NULL) {
        fprintf(stderr, "ptrStdTreeAppend(): exit due to invalid pointer\n");
        exit(EINVAL);
    }
    ptrStdTreeNode_t* new = ptrStdTreeCreateNode(element);
    target->child_h = new;
    new->parent = target;
    new->depth = target->depth + 1
    return new;
}

// free a tree and its elements
void ptrStdTreeFree(ptrStdTreeNode_t* target, void (*freeElement) (void)) {
    if (target == NULL) return;
    if (freeElement == NULL) {
        fprintf(stderr, "ptrStdTreeFree(): exit due to invalid pointer\n");
        exit(EINVAL);
    }

    if (target->child_l != NULL) {
        ptrStdTreeFree(target->child_l, freeElement);
    }

    if (target->child_h != NULL) {
        ptrStdTreeFree(target->child_h, freeElement);
    }

    freeElement(target->element);
    free(target);
    return;
}

// search for a node in a tree
ptrStdTreeNode_t* ptrStdTreeSearch(ptrStdTreeNode_t* target, void* condition, bool (*compElem) (void*, void*), bool (*isGreater) (void*, void*)) {
    if (target == NULL || condition == NULL || compElem == NULL || isGreater == NULL) {
        fprintf(stderr, "ptrStdTreeSearch(): exit due to invalid pointer\n");
        exit(EINVAL);
    }

    if (compElem(condition, target->element)) {         // condition matches
        return target;
    } else if (isGreater(target->element, condition)) { // condition is on h side of tree
        if (target->child_h == NULL) return NULL;
        else return ptrStdTreeSearch(target->child_h, condition, compElem, isGreater);  
    } else {                                            // condition is on l side of tree
        if (target->child_l == NULL) return NULL;
        else return ptrStdTreeSearch(target->child_l, condition, compElem, isGreater);
    }
}

// return element of node
void* ptrStdTreeGetContent(ptrStdTreeNode_t* target) {
    if (target == NULL) {
        fprintf(stderr, "ptrStdTreeGetContent(): exit due to invalid pointer\n");
        exit(EINVAL);
    }
    return target->element;
}

// return lowest valued node of the tree
ptrStdTreeNode_t* ptrStdTreeGetLowest(ptrStdTreeNode_t* target) {
    if (target == NULL) {
        fprintf(stderr, "ptrStdTreeGetLowest(): exit due to invalid pointer\n");
        exit(EINVAL);
    }

    if (target->child_l == NULL) {
        return target;
    } else return ptrStdTreeGetLowest(target->child_l);
}

// return highest valued node of the tree
ptrStdTreeNode_t* ptrStdTreeGetHighest(ptrStdTreeNode_t* target) {
    if (target == NULL) {
        fprintf(stderr, "ptrStdTreeGetHighest(): exit due to invalid pointer\n");
        exit(EINVAL);
    }

    if (target->child_h == NULL) {
        return target;
    } else return ptrStdTreeGetLowest(target->child_h);
}

// remove a node from a tree
ptrStdTreeNode_t* ptrStdTreeRemove(ptrStdTreeNode_t* target) {
    if (target == NULL) {
        fprintf(stderr, "ptrStdTreeRemove(): exit due to invalid pointer\n");
        exit(EINVAL);
    }

    if (target->parent == NULL) {
        if (target->child_l != NULL) {
            ptrStdTreeNode_t* newroot = target->child_l;

            if (target->child_h != NULL) {
                ptrStdTreeNode_t* branch = target->child_h;
                ptrStdTreeNode_t* insert = ptrStdTreeGetHighest(target->child_l);
                branch->parent = insert;
                insert->child_h = branch;
            }
            newroot->parent = NULL;
            free(target);
            return newroot;

        } else if (target->child_h != NULL){
            ptrStdTreeNode_t* newroot = target->child_h;
            newroot->parent = NULL;
            free(target);
            return newroot;
        } else {
            free(target);
            return NULL;
        }
    }
}

// search for an element in the tree, return its content and remove its node from the tree
void* ptrStdTreeExtract(ptrStdTreeNode_t* target, void* condition, bool (*compElem) (void*, void*), bool (*isGreater) (void*, void*)) {
    if (target == NULL || condition == NULL || compElem == NULL || isGreater == NULL) {
        fprintf(stderr, "ptrStdTreeExtract(): exit due to invalid pointer\n");
        exit(EINVAL);
    }

    ptrStdTreeNode_t* object = ptrStdTreeSearch(target, condition, compElem, isGreater);
    void * content = ptrStdTreeGetContent(object);
    ptrStdTreeRemove(object);
    return content;
}
