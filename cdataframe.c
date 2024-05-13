#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>

CDATAFRAME *create_cdf(ENUM_TYPE *cdftype, int size){
    CDATAFRAME* cdf = (CDATAFRAME*) malloc(sizeof(cdftype)*size);
    cdf->size = size;
    cdf->head = NULL;
    cdf->tail = NULL;
    return cdf;
}

void delete_cdf(CDATAFRAME **cdf){
    free((*cdf)->head);
    free((*cdf)->tail);
    free(*cdf);
    *cdf = NULL;
}

void delete_column_cdf(CDATAFRAME *cdf, char *col_name){
    if (cdf == NULL){
        printf("Error : no elements in CDataFrame\n");
        return;
    }

    LNODE* pointer = cdf->tail;
    while (pointer->next != NULL){
        if (pointer->data->title == col_name){
            delete_column(&(pointer->data));
            free(pointer);
            cdf->size--;
            return;
        }
        pointer = pointer->next;
    }
    if (pointer->data->title == col_name){
        delete_column(&(pointer->data));
        free(pointer);
        cdf->size--;
        return;
    }
    printf("Error : column name given in parameter.\n");
    return;
}

int get_cdf_cols_size(CDATAFRAME *cdf){
    if (cdf == NULL){
        return 0;
    }
    LNODE* pointer = cdf->tail;
    int count = 0;
    while (pointer->next != NULL){
        count ++;
        pointer = pointer->next;
    }
    count++;
    return count;
}

void fill_input_cdf(CDATAFRAME *cdf, int nb_input){
    if (nb_input < 1){
        printf("Error : nb_input must be strictly greater than 0 and below the size of the CDataFrame.\n");
        return;
    }

    LNODE* pointer = cdf->tail;
    cdf->tail = pointer;
    LNODE* prev = NULL;
    char title[50];
    int type_choice;
    for (int i=0; i<nb_input; i++){
        printf("Filling column number %d\n", i);
        printf("Enter the column's title : \n");
        gets(title);
        printf("Please choose the column's type by entering their corresponding number (from 1 to 6)\n");
        printf("Usigned Int - Int - Char - Float - Double - String\n");
        scanf("%d", &type_choice);
        
        switch (type_choice){
            case 1 :
                pointer->data = create_column(UINT, title);
            case 2 :
                pointer->data = create_column(INT, title);
            case 3 :
                pointer->data = create_column(CHAR, title);
            case 4 :
                pointer->data = create_column(FLOAT, title);
            case 5 :
                pointer->data = create_column(DOUBLE, title);
            case 6 :
                pointer->data = create_column(STRING, title);
        }
        if (i != 0){
            pointer->prev = prev;
            prev->next = pointer;
        } else{
            pointer->prev = NULL;
        }
        prev = pointer;
        pointer = pointer->next;
    }
    pointer->next = NULL;
    cdf->head = pointer;
    return;
}

void fill_hard_cdf(CDATAFRAME *cdf, int nb_input){
    LNODE* pointer = cdf->tail;
    cdf->tail = pointer;
    LNODE* prev;
    char title[50] = "Random fill";
    int type_choice;
    for (int i=0; i<nb_input; i++){
        type_choice = rand()%6 +1;
        switch (type_choice){
            case 1 :
                pointer->data = create_column(UINT, title);
            case 2 :
                pointer->data = create_column(INT, title);
            case 3 :
                pointer->data = create_column(CHAR, title);
            case 4 :
                pointer->data = create_column(FLOAT, title);
            case 5 :
                pointer->data = create_column(DOUBLE, title);
            case 6 :
                pointer->data = create_column(STRING, title);
        }
        if (i != 0){
            pointer->prev = prev;
            prev->next = pointer;
        } else{
            pointer->prev = NULL;
        }
        prev = pointer;
        pointer = pointer->next;
    }
    pointer->next = NULL;
    cdf->head = pointer;
    return;
}

void display_cdf(CDATAFRAME cdf){
    LNODE* pointer = cdf.tail;
    while (pointer != cdf.head){
        print_col(pointer->data);
        pointer = pointer->next;
    }
    print_col(pointer->data);
    return;
}

void display_rows_cdf(CDATAFRAME cdf, unsigned long long int limit){
    LNODE* pointer = cdf.tail;
    while (pointer != cdf.head){    // Yes, I just copied the print_col function and changed the for loop
        printf("Column Title: %s\n", pointer->data->title);
        printf("Index\tValue\n");
        fflush(stdout);
        for (unsigned long long int i = 0; i < limit; i++) {
            printf("[%llu]\t", i);      // temp but works
            if (pointer->data->data[i] == NULL) {
                printf("NULL\n");
            } else {
                char str[256];
                convert_value(pointer->data, i, str, 256);
                printf("%s\n", str);
            }
        }
        pointer = pointer->next;
    }
    return;
}

void display_col_cdf(CDATAFRAME cdf, int limit){
    LNODE* pointer = cdf.tail;
    while ((pointer != cdf.head) || (limit != 0)){
        print_col(pointer->data);
        pointer = pointer->next;
        limit--;
    }
    if ((pointer == cdf.head) && (limit != 0)){
        print_col(pointer->data);
    }
    return;
}  

void add_row_cdf(CDATAFRAME *cdf, int i){
    LNODE* pointer = cdf->tail;

    while (pointer != cdf->tail){
        if (pointer->data->size == pointer->data->max_size){
            pointer->data->max_size += 256;
            pointer->data->data = (COL_TYPE**) realloc(pointer->data->data, pointer->data->max_size*sizeof(pointer->data->column_type));
        }
        for (int j=i; j<pointer->data->size; j++){
            switch (pointer->data->column_type){
            case UINT:
                // TODO: create a temporary variable according to the type ? Had an error when I tried
                break;
            
            default:
                break;
            }
        }
    }
}

void add_col_cdf(CDATAFRAME *cdf, ENUM_TYPE type,char *col_name){
    // TODO : fix it ??? why tf is it not working ??
    cdf->size++;
    cdf = (CDATAFRAME*) realloc(cdf, cdf->size*sizeof(CDATAFRAME)); // We've put double pointers before for realloc, don't know if it's correct
    LNODE *pointer = cdf->head;
    //pointer->next = create_column(type, col_name);
    cdf->head = pointer->next;
    return;
}