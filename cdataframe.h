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
    int size;   // Added size attribute to keep a track on memory allocation;
} LIST;

typedef LIST CDATAFRAME;

CDATAFRAME *create_cdf(ENUM_TYPE *cdftype, int size);
void delete_cdf(CDATAFRAME **cdf);
void add_col_cdf(CDATAFRAME *cdf,ENUM_TYPE type, char *col_name);  // TODO
void delete_column_cdf(CDATAFRAME *cdf, char *col_name);    // Name changed beacause of incompatibility with column.h function
void add_row_cdf(CDATAFRAME *cdf, int i);   // TODO
void delete_row_cdf(CDATAFRAME *cdf, int i); // TODO
void rename_col_cdf(CDATAFRAME *cdf, char *new_col_name); //TODO
int get_cdf_cols_size(CDATAFRAME *cdf);
void fill_input_cdf(CDATAFRAME *cdf, int nb_input);
void fill_hard_cdf(CDATAFRAME *cdf, int nb_input);
void display_cdf(CDATAFRAME cdf);
void display_rows_cdf(CDATAFRAME cdf, unsigned long long int limit);
void display_cols_cdf(CDATAFRAME cdf, int limit);


#endif