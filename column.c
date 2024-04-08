#include "column.h"
#include <stdio.h>
#include <stdlib.h>

COLUMN *create_column(ENUM_TYPE type, char *title){
    /**
     * @brief: Creates a new column for a dataframe that will store the titles, types, sizes and indexes.
     * @type: Column type
     * @title: Column title
     * @return: Pointer to the created array
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

    /* /!\ Explain please /!\
    if (new_col->data == NULL || new_col->index == NULL) {
        printf("Memory not allocated for data or index arrays.");
        return NULL;
    }
    */

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
        col->data = (COLUMN*) realloc(col->data, col->max_size*sizeof(col->column_type));
    }

    // Chose the correct field to assign to the value inserted in COL_TYPE struct
    switch(col->column_type) {
        case UINT:
            *((unsigned int*)col->data[col->size]) = *((unsigned int*)value);
            break;
        case INT:
            *((int*)col->data[col->size]) = *((int*)value);
            break;
        case CHAR:
            *((char*)col->data[col->size]) = *((char*)value);
            break;
        case FLOAT:
            *((float*)col->data[col->size]) = *((float*)value);
            break;
        case DOUBLE:
            *((double*)col->data[col->size]) = *((double*)value);
            break;
    }
    // In case the NULL value has been entered, insert it anyways
    if (value == NULL){
        col->data[col->size] = NULL;
    }

    col->size += 1;
    
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
            unsigned int val = col->data[i];
            int count = 0;
            do{
                str[count] = (char)val%10;
                val /= 10;
                count++;
            } while(val > 10);
            
            char temp;  //We have to reverse it because it's in the wrong order. Didn't find better method
            for (int j=0; j<=count/2; j++){
                temp = str[0];
                str[0] = str[count-1-j];
                str[count-1-j] = temp;
            }
            str[count] = '\0';

            break;
        case INT:  
            int val = col->data[i]; 
            int count = 0;
            if (val < 0){   // We prevent any problem with the '-' sign
                str[count] = '-';
                count++;
                val = -val;
            }
            // Didn't find a better method for this

            break;
        case CHAR:
            //Well it's already done
            str = col->data[i];
            break;
        case FLOAT:
            //Perhaps same as UNIT but by multiplying by 10 to take the decimal numbers with the %

            break;
        case DOUBLE:

            break;
    }

}
