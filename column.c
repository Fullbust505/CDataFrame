#include "column.h"
#include <stdio.h>
#include <stdlib.h>

enum enum_type{   
    /*Types for the columns*/
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;

union column_type{  
    /*Types for the arrays of datas*/
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union column_type COL_TYPE ;


struct column {
    /**
     * Structure of the columns
     * 
     */
    char *title;
    unsigned int size; //logical size
    unsigned int max_size; //physical size
    ENUM_TYPE column_type;
    COL_TYPE **data; // array of pointers to stored data
    unsigned long long int *index; // array of integers
};
typedef struct column COLUMN;

COLUMN *create_column(ENUM_TYPE type, char *title){
    /**
     * Creates a new column for a dataframe that will store the titles, types, sizes and indexes.
     * 
     */
    COLUMN* new_col = (COLUMN*) malloc(sizeof(COLUMN));
    *new_col->title = *title;
    new_col->size = 0;
    new_col->max_size = 256;
    new_col->column_type = type;
    new_col->data = (COL_TYPE**) malloc(new_col->max_size*sizeof(COL_TYPE));
    new_col->index = (unsigned long long int*) malloc(new_col->size*sizeof(unsigned long long int));

    if (new_col == NULL){
        printf("Memory not allocated .");
        return NULL;
    }

    /*
    if (new_col->data == NULL || new_col->index == NULL) {
        printf("Memory not allocated for data or index arrays.");
        return NULL;
    }
    */

    return new_col;

}

int insert_value(COLUMN *col, void *value){
    /**
     * Inserts a value of void type in a column.
     * 
     */
    // Reallocation of the memory, in case there's not enough
    if (col->size == col->max_size){
        col->max_size += 256;
        col = (COLUMN*) realloc(col, col->max_size*sizeof(col->column_type));
    }

    /*
    To allocate memory for the new date inserted
    col->data[col->size] = (COL_TYPE*)malloc(sizeof(COL_TYPE));
    if (col->data[col->size] == NULL) {
        printf("Memory not allocated for data element.");
        return 0;
    }

    Chose the correct field to assign to the value inserted in COL_TYPE struct
    switch(col->column_type) {
        case UINT:
            col->data[col->size]->uint_value = *((unsigned int*)value);
            break;
        case INT:
            col->data[col->size]->int_value = *((int*)value);
            break;
        case CHAR:
            col->data[col->size]->char_value = *((char*)value);
            break;
        case FLOAT:
            col->data[col->size]->float_value = *((float*)value);
            break;
        case DOUBLE:
            col->data[col->size]->double_value = *((double*)value);
            break;
            */

    //COL_TYPE temp = *value;
    col->data[col->size] = *value;
    col->size += 1;
    
    if (col->data[col->size-1] == NULL) return 0;
    else return 1;
}