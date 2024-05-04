#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COLUMN *create_column(ENUM_TYPE type, char *title){
    /**
     * @brief: Creates a new column for a dataframe that will store the titles, types, sizes and indexes.
     * @type: Column type
     * @title: Column title
     * @return: Pointer to the created array
     */
    COLUMN* new_col = (COLUMN*) malloc(sizeof(COLUMN));
    new_col->title = (char*) malloc(strlen(title) + 1);
    strcpy(new_col->title, title);
    new_col->size = 0;
    new_col->max_size = 256;
    new_col->column_type = type;
    new_col->data = (COL_TYPE**) malloc(new_col->max_size*sizeof(COL_TYPE));
    new_col->index = NULL; // For now, it's NULL, it's specified in the document

    if (new_col->title == NULL){
        printf("Memory not allocated .");
        return NULL;
    }
    strcpy(new_col->title, title);
    return new_col;

}

int insert_value(COLUMN *col, void *value){
    /**
     * @brief: A value of void type in a column.
     * @col: Pointer to the column
     * @value:  Pointer to the value to insert
     * @return: 1 if the value is correctly inserted, 0 otherwise
     */
    // Reallocation of the memory, in case there's not enough
    if (col->size == col->max_size){
        col->max_size += 256;
        col->data = (COL_TYPE**) realloc(col->data, col->max_size*sizeof(col->column_type));
    }

    // In case the NULL value has been entered, insert it anyways
    if (value == NULL){
        col->data[col->size] = NULL;
    } else{
        // Chose the correct field to assign to the value inserted in COL_TYPE struct
        switch(col->column_type) {
        case UINT:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(unsigned int));
            *((unsigned int*)col->data[col->size]) = *((unsigned int*)value);
            break;
        case INT:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(int));
            *((int*)col->data[col->size]) = *((int*)value);
            break;
        case CHAR:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(char));
            *((char*)col->data[col->size]) = *((char*)value);
            break;
        case FLOAT:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(float));
            *((float*)col->data[col->size]) = *((float*)value);
            break;
        case DOUBLE:
            col->data[col->size] = (COL_TYPE*) malloc (sizeof(double));
            *((double*)col->data[col->size]) = *((double*)value);
            break;
        case STRING:
            col->data[col->size] = (COL_TYPE*) malloc (strlen((char*)value) + 1);
            strcpy((char*)col->data[col->size], (char*)value);
            break;
        }
    }

    col->size++;
    
    if (col->data[col->size-1] == NULL){
        printf("Memory not allocated.");
        return 0;
    } 
    else return 1;
}

void delete_column(COLUMN **col){
    /**
     * @brief: Free the space allocated by a column
     * @col: Pointer to the column
     */

    free((*col)->title);

    free((*col)->index);
    free((*col)->data);     // Perhaps do we have to free all the data one by one and parkour the whole array ? idk
    
    free(*col);

    *col = NULL;
}

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size){
    /**
     * @brief Convert a value into a string
     * @col: Pointer to the column
     * @i: Position of the value in the data array
     * @str: The string in which the value will be written
     * @size:  Maximum size of the string
     */
    
    switch(col->column_type){       
        case UINT:
            snprintf(str, size, "%u", *((int*)col->data[i]));
            break;
        case INT:  
            snprintf(str, size, "%d", *((unsigned int*)col->data[i]));
            break;
        case CHAR:
            snprintf(str, size, "%s", *((char*)col->data[i]));
            break;
        case FLOAT:     
            snprintf(str, size, "%lf", *((float*)col->data[i]));
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", *((double*)col->data[i]));
            break;
        case STRING:
            strncpy(str, (char*)col->data[i], size - 1);
            str[size - 1] = '\0'; // Ensure null termination for the string to avoid errors
            break;
        default :
            str = NULL;
            printf("convert_value encountered a type error.");
    }

}

void display_value(COLUMN **data_frame, int num_columns, int num_rows) {
    /**
     * @brief: Displays the value of the data frame
     * @data_frame: The data frame 
     * @num_columns: The number of columns of the data frame
     * @num_rows: The number of rows in the data_frame
     */
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
            char str[256];
            convert_value(data_frame[j], i, str, 256);
            printf("%s\t", str);
        }
        printf("\n");
    }
}

void print_col(COLUMN *col) {
    /**
     * @brief: Prints a desired column
     * @col: The column of the data frame
     */
    printf("Column Title: %s\n", col->title);
    printf("Index\tValue\n");
    fflush(stdout);
    for (unsigned long long int i = 0; i < (col->size); i++) {
        printf("[%llu]\t", i);      // temp but works
        if (col->data[i] == NULL) {
            printf("NULL\n");
        } else {
            char str[256];
            convert_value(col, i, str, 256);
            printf("%s\n", str);
        }
    }
    fflush(stdout);
}

int n_occ(COLUMN *col, void *x){
    int nb_occ = 0;
    switch (col->column_type){
        case UINT:
            for (int i=0; i<col->size; i++){
                if (*((unsigned int*)col->data[i]) == *((unsigned int*)x)){
                    nb_occ += 1;
                }
            }
            break;

        case INT:
            for (int i=0; i<col->size; i++){
                if (*((int*)col->data[i]) == *((int*)x)){
                    nb_occ += 1;
                }
            }
            break;

        case CHAR:
            for (int i=0; i<col->size; i++){
                if (*((char*)col->data[i]) == *((char*)x)){
                    nb_occ += 1;
                }
            }
            break;
        
        case FLOAT:
            for (int i=0; i<col->size; i++){
                if (*((float*)col->data[i]) == *((float*)x)){
                    nb_occ += 1;
                }
            }
            break;
        
        case DOUBLE:
            for (int i=0; i<col->size; i++){
                if (*((double*)col->data[i]) == *((double*)x)){
                    nb_occ += 1;
                }
            }
            break;

        default:
            break;
    }
    
    return nb_occ;
}
/*
void* n_pos(COLUMN *col, int x){
    switch (col->column_type){
    case UINT:
        unsigned int *value = (*(unsigned int*)col->data[x]);
        break;
    case INT:
        int *value = (*(int*)col->data[x]);
    case CHAR:
        char *value = (*(char*)col->data[x]);
    case FLOAT:
        float *value = (*(float**)col->data[x]);    // Not really sure of why we need a double pointer, there's an error otherwise
    case DOUBLE:
        double *value = (*(double**)col->data[x]);

    default:
        break;
    }
}
*/