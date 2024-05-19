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
        default :
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
            snprintf(str, size, "%u", *((unsigned int*)col->data[i]));
            break;
        case INT:  
            snprintf(str, size, "%d", *((int*)col->data[i]));
            break;
        case CHAR:
            snprintf(str, size, "%c", *((char*)col->data[i]));
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
            if (i < data_frame[j]->size) { // Ensure index i is valid
                char str[256];
                convert_value(data_frame[j], i, str, sizeof(str));
                printf("%s\t", str);
            } else {
                printf("\t"); // Print empty cell if index is out of bounds
            }
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

int n_occ(COLUMN *col, void *x) {
    int nb_occ = 0;
    char x_str[256]; // Assuming the maximum size for the string representation
    
    // Convert the value to a string for comparison
    convert_value(col, 0, x_str, sizeof(x_str));

    for (int i = 0; i < col->size; i++) {
        char str[256];
        convert_value(col, i, str, sizeof(str));

        // Compare the string representations
        if (strcmp(str, x_str) == 0) {
            nb_occ++;
        }
    }
    return nb_occ;
}


COL_TYPE* get_value_at_position(COLUMN *col, unsigned long long int x) {
    if (x >= col->size) {
        printf("Error: Index out of bounds.\n");
        return NULL;
    }
    return col->data[x];
}

int count_values_greater_than_x(COLUMN *col, void *x) {
    int count = 0;
    char x_str[256]; // Assuming the maximum size for the string representation
    
    // Convert the value to a string for comparison
    convert_value(col, 0, x_str, sizeof(x_str));

    for (int i = 0; i < col->size; i++) {
        char str[256];
        convert_value(col, i, str, sizeof(str));

        // Compare the string representations
        if (strcmp(str, x_str) > 0) {
            count++;
        }
    }
    return count;
}

int count_values_less_than_x(COLUMN *col, void *x) {
    int count = 0;
    char x_str[256]; // Assuming the maximum size for the string representation
    
    // Convert the value to a string for comparison
    convert_value(col, 0, x_str, sizeof(x_str));

    for (int i = 0; i < col->size; i++) {
        char str[256];
        convert_value(col, i, str, sizeof(str));

        // Compare the string representations
        if (strcmp(str, x_str) < 0) {
            count++;
        }
    }
    return count;
}

int count_values_equal_to_x(COLUMN *col, void *x) {
    int count = 0;
    char x_str[256]; // Assuming the maximum size for the string representation
    
    // Convert the value to a string for comparison
    convert_value(col, 0, x_str, sizeof(x_str));

    for (int i = 0; i < col->size; i++) {
        char str[256];
        convert_value(col, i, str, sizeof(str));

        // Compare the string representations
        if (strcmp(str, x_str) == 0) {
            count++;
        }
    }
    return count;
}

void fill_col(COLUMN *col, int value){
      /**
     * @brief: Fills the entire column with the specified value.
     * @col: Pointer to the column
     * @value: The value to fill the column with
     */
    for(int i = 0; i < col->max_size; i++) {
        switch (col->column_type) {
            case UINT:
                col->data[i] = (COL_TYPE*) malloc(sizeof(unsigned int));
                if (col->data[i] == NULL) {
                    printf("Memory not allocated.");
                    return;
                }
                *((unsigned int*)col->data[i]) = (unsigned int)value;
                break;
            case INT:
                col->data[i] = (COL_TYPE*) malloc(sizeof(int));
                if (col->data[i] == NULL) {
                    printf("Memory not allocated.");
                    return;
                }
                *((int*)col->data[i]) = (int)value;
                break;
            case CHAR:
                col->data[i] = (COL_TYPE*) malloc(sizeof(char));
                if (col->data[i] == NULL) {
                    printf("Memory not allocated.");
                    return;
                }
                *((char*)col->data[i]) = (char)value;
                break;
            case FLOAT:
                col->data[i] = (COL_TYPE*) malloc(sizeof(float));
                if (col->data[i] == NULL) {
                    printf("Memory not allocated.");
                    return;
                }
                *((float*)col->data[i]) = (float)value;
                break;
            case DOUBLE:
                col->data[i] = (COL_TYPE*) malloc(sizeof(double));
                if (col->data[i] == NULL) {
                    printf("Memory not allocated.");
                    return;
                }
                *((double*)col->data[i]) = (double)value;
                break;
            case STRING:
                col->data[i] = (COL_TYPE*) malloc(strlen((char*)&value)+1);
                if (col->data[i] == NULL) {
                    printf("Memory not allocated.");
                    return;
                }
                strcpy((char*)col->data[i], (char*)&value);
                break;
            default:
                printf("Unsupported column type.");
                return;
        }
    }
}