/* ptrStdTree.h
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

typedef struct __ptrStdTree_t {
    void* element;
    struct __ptrStdTree_t* parent;
    struct __ptrStdTree_t* child_l;
    struct __ptrStdTree_t* child_h;
    int8_t depth;
} ptrStdTreeNode_t;

// print usefull information about ptrStdTree on stdout
void ptrStdTreePrintInfo();

// print tree to stderr
void ptrStdTreePrintTree(ptrStdTreeNode_t* target, void (*printElement) (void*));

// create an empty node
ptrStdTreeNode_t* ptrStdTreeCreateNode(void* element);

// create and append a new node to an existing tree.
ptrStdTreeNode_t* ptrStdTreeAppend(ptrStdTreeNode_t* target, bool (*isGreater) (void*, void*), void* element);

// append a new node to child_l
ptrStdTreeNode_t* ptrStdTreeAppendLow(ptrStdTreeNode_t* target, void* element);

// append a new node to child_h
ptrStdTreeNode_t* ptrStdTreeAppendHigh(ptrStdTreeNode_t* target, void* element);

// free a tree and its elements
void ptrStdTreeFree(ptrStdTreeNode_t* target, void (*freeElement) (void*));

// search for a node in a tree
ptrStdTreeNode_t* ptrStdTreeSearch(ptrStdTreeNode_t* target, void* condition, bool (*compElem) (void*, void*), bool (*isGreater) (void*, void*));

// return element of node
void* ptrStdTreeGetContent(ptrStdTreeNode_t* target);

// return lowest valued node of the tree
ptrStdTreeNode_t* ptrStdTreeGetLowest(ptrStdTreeNode_t* target);

// return highest valued node of the tree
ptrStdTreeNode_t* ptrStdTreeGetHighest(ptrStdTreeNode_t* target);

// remove a node from a tree
ptrStdTreeNode_t* ptrStdTreeRemove(ptrStdTreeNode_t* target);

// search for an element in the tree, return its content and remove its node from the tree
void* ptrStdTreeExtract(ptrStdTreeNode_t* target, void* condition, bool (*compElem) (void*, void*), bool (*isGreater) (void*, void*));
