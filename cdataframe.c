#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>

CDATAFRAME *create_cdf(ENUM_TYPE *cdftype, int size){
    CDATAFRAME* cdf = (CDATAFRAME*) malloc(sizeof(CDATAFRAME)*size);
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
            return;
        }
        pointer = pointer->next;
    }
    if (pointer->data->title == col_name){
        delete_column(&(pointer->data));
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

    LNODE* pointer = cdf->head;
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
                pointer->data = create_column(UINT, &title);
            case 2 :
                pointer->data = create_column(INT, &title);
            case 3 :
                pointer->data = create_column(CHAR, &title);
            case 4 :
                pointer->data = create_column(FLOAT, &title);
            case 5 :
                pointer->data = create_column(DOUBLE, &title);
            case 6 :
                pointer->data = create_column(STRING, &title);
        }
        pointer = pointer->next;
    }
    return;
}

void fill_hard_cdf(CDATAFRAME *cdf, int nb_input){
    LNODE* pointer = cdf->head;
    char title[50] = "Random fill";
    int type_choice;
    for (int i=0; i<nb_input; i++){
        type_choice = rand()%6 +1;
        switch (type_choice){
            case 1 :
                pointer->data = create_column(UINT, &title);
            case 2 :
                pointer->data = create_column(INT, &title);
            case 3 :
                pointer->data = create_column(CHAR, &title);
            case 4 :
                pointer->data = create_column(FLOAT, &title);
            case 5 :
                pointer->data = create_column(DOUBLE, &title);
            case 6 :
                pointer->data = create_column(STRING, &title);
        }
        pointer = pointer->next;
    }
    return;
}