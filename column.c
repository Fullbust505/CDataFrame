#include "column.h"

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
    /*Structure of the columns*/
    char *title;
    unsigned int size; //logical size
    unsigned int max_size; //physical size
    ENUM_TYPE column_type;
    COL_TYPE **data; // array of pointers to stored data
    unsigned long long int *index; // array of integers
};
typedef struct column COLUMN;

COLUMN *create_column(ENUM_TYPE type, char *title){
    COLUMN* new_col = (COLUMN*) malloc(sizeof(COLUMN));
    *new_col->title = *title;
    new_col->size = 0;
    new_col->max_size = 256;
    new_col->column_type = type;
    //**new_col->data = ;


    return new_col;
}

