#include "column.h"
#include "list.h"
#ifndef CDATAFRAME_H
#define CDATAFRAME_H

typedef list CDATAFRAME;
typedef lnode LNODE;

CDATAFRAME *create_cdf(ENUM_TYPE *cdftype, int size);
void fill_input_cdf(CDATAFRAME *cdf, int nb_input);
void fill_hard_cdf(CDATAFRAME *cdf, int nb_input);
void delete_cdf(CDATAFRAME **cdf);

void display_cdf(CDATAFRAME cdf);
void display_rows_cdf(CDATAFRAME cdf, unsigned long long int limit);
void display_cols_cdf(CDATAFRAME cdf, int limit);
void display_col_names(CDATAFRAME cdf);

void add_col_cdf(CDATAFRAME *cdf,ENUM_TYPE type, char *col_name, int i);  
void delete_col_name_cdf(CDATAFRAME *cdf, char *col_name);    // Name changed beacause of incompatibility with column.h function
void delete_col_i_cdf(CDATAFRAME *cdf, int i);
void add_row_cdf(CDATAFRAME *cdf, int i);   
void delete_row_cdf(CDATAFRAME *cdf, int i); 
void rename_col_cdf(CDATAFRAME *cdf, char *og_name, char *new_col_name);
void search_value_cdf(CDATAFRAME cdf, ENUM_TYPE type, COL_TYPE *value);
COL_TYPE* get_value_cdf(CDATAFRAME cdf, int col, unsigned long long int row);
void change_value_cdf(CDATAFRAME *cdf, int col, unsigned long long int row, COL_TYPE *value);

int get_cdf_cols_size(CDATAFRAME *cdf);




#endif