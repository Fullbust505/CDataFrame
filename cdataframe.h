#include "column.h"
#ifndef CDATAFRAME_H
#define CDATAFRAME_H
typedef struct lnode_ {
    COLUMN *data; // Pointer to a column, yes we changed its type
    struct lnode_ *prev;
    struct lnode_ *next;
} LNODE;

typedef struct list_ {
    LNODE *head;
    LNODE *tail;
} LIST;

typedef LIST CDATAFRAME;

CDATAFRAME *create_cdf(ENUM_TYPE *cdftype, int size);
void delete_cdf(CDATAFRAME **cdf);
void delete_column_cdf(CDATAFRAME *cdf, char *col_name);    // Name changed beacause of incompatibility with column.h function
int get_cdf_cols_size(CDATAFRAME *cdf);
void fill_input_cdf(CDATAFRAME *cdf, int nb_input);
void fill_hard_cdf(CDATAFRAME *cdf, int nb_input);

#endif