/* ptrStdBuffer.c
 * part of the ptrStd libary
 *
 */
#include "ptrStdBuffer.h"


// print out usefull information about ptrStdBuffer on stdout
void ptrStdBufferPrintInfo(void) {
    exit(ENOSYS);
}

// print out buffer info on stderr
void ptrStdBufferPrint(void* target) {
    ptrStdBuffer_t* buffer = (ptrStdBuffer_t*) target;
    if (buffer == NULL) {
        fprintf(stderr, "NULLPOINTER\n");
        return;
    }

    fprintf(stderr, "[capacity: %lu]", buffer->len);
    for (size_t index = 0; index < buffer->len; index++) {
        fprintf(stderr, "%hhu;", *((uint8_t*) buffer->data + index));
    }

    fprintf(stderr, "\n");
    return;
}

// create a empty buffer
ptrStdBuffer_t* ptrStdBufferCreateEmpty(size_t capacity) {
    ptrStdBuffer_t* new = calloc(1, sizeof(ptrStdBuffer_t));
    uint8_t* buffer = calloc(capacity, sizeof(uint8_t));

    if (new == NULL || buffer == NULL) {
        exit(ENOMEM);
    }

    new->len = capacity;
    new->data = buffer;

    return new;
}

// create a nonempty buffer
ptrStdBuffer_t* ptrStdBufferCreate(size_t capacity, void* content, size_t contentLength) {
    ptrStdBuffer_t* buffer = ptrStdBufferCreateEmpty(capacity);

    if (content == NULL || contentLength == 0) {
        return buffer;
    } else if (capacity < contentLength) {
        fprintf(stderr, "ptrStdBufferCreate(): content to long for buffer\n");
        exit(EXIT_FAILURE);
    }

    memcpy((uint8_t*) buffer->data, content, contentLength);
    fprintf(stderr, "%p;%p\n", buffer, buffer->data);
    return buffer;
}

// free a buffer
void ptrStdBufferFree(void* target) {
    if (target != NULL) {
        ptrStdBuffer_t* temp = (ptrStdBuffer_t*) target;
        free(temp->data);
        free(temp);
    }
    return;
}

// return the content of a buffer
void* ptrStdBufferGetContent(ptrStdBuffer_t* target) {
    return target->data;
}

// compare two buffers
bool ptrStdBufferComp(void* a, void* b) {
    if (a == NULL || b == NULL) return false;

    ptrStdBuffer_t *buf_a, *buf_b;
    buf_a = (ptrStdBuffer_t*) a;
    buf_b = (ptrStdBuffer_t*) b;

    if (buf_a->len != buf_b->len) return false;

    uint8_t val_a[buf_a->len], val_b[buf_a->len];

    memcpy(val_a, buf_a->data, buf_a->len);
    memcpy(val_b, buf_b->data, buf_b->len);

    for (size_t index = 0; index < buf_a->len; index++) {
        if (val_a[index] != val_b[index]) return false;
    }

    return true;
}
