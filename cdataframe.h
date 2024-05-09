#include "column.h"
#ifndef CDATAFRAME_H
#define CDATAFRAME_H
typedef struct lnode_ {
    void *data; // Pointer to a column
    struct lnode_ *prev;
    struct lnode_ *next;
} LNODE;

typedef struct list_ {
    LNODE *head;
    LNODE *tail;
} LIST;

typedef LIST CDATAFRAME;

CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);


#endif