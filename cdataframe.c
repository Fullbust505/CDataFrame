#include "cdataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CDATAFRAME *create_cdf(int size){
    /**
     * @brief: Creates a new CDataframe
     * @size: Size of the dataframe
     * @return: Pointer to the CDataframe
     */
    CDATAFRAME* cdf = (CDATAFRAME*) malloc(sizeof(CDATAFRAME)*size);
    cdf->head = NULL;
    cdf->tail = NULL;
    return cdf;
}

void delete_cdf(CDATAFRAME **cdf){
    /**
     * @brief: Deletes a CDataframe
     * @cdf: Double pointer to the CDataframe
     */
    lst_delete_list(*cdf);
    *cdf = NULL;
    printf("CDF succesfully freed !");
}

void delete_col_name_cdf(CDATAFRAME *cdf, char *col_name){
    /**
     * @brief: Deletes a column of the CDF 
     * @cdf: Pointer to a CDataframe
     * @col_name: Name of the column to delete
     */
    if (cdf == NULL){
        printf("Error : no elements in CDataFrame\n");
        return;
    }

    LNODE* pointer = cdf->tail;
    while (pointer != NULL){
        if (strcmp(pointer->data->title, col_name) == 0){
            delete_column(&(pointer->data));
            free(pointer);
            cdf->size--;
            return;
        }
        pointer = pointer->next;
    }
    printf("Error : column name given in parameter.\n");
    return;
}

int get_cdf_cols_size(CDATAFRAME *cdf){
    /**
     * @brief: Get the number of columns of the CDataframe
     * @cdf: Pointer to a CDataframe
     * @return: Number of columns in the CDataframe
     */
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

void flush_input_buffer(){
    /**
     * @brief Flushes the input buffer
     */
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void fill_input_cdf(CDATAFRAME *cdf, int nb_input){
    /**
     * @brief: Fills a CDataframe according to the inputs of the user
     * @cdf: Pointer to a CDataframe
     * @nb_input: Number of columns that will be created
     */
    if (nb_input < 1){
        printf("Error : nb_input must be strictly greater than 0 and below the size of the CDataFrame.\n");
        return;
    }

    LNODE* pointer = (LNODE*) malloc(sizeof(LNODE));
    LNODE* prev = (LNODE*) malloc(sizeof(LNODE));
    char title[20];
    int type_choice;

    for (int i=0; i<nb_input; i++){
        printf("Filling column number %d\n", i);
        printf("Enter the column's title : \n");
        scanf("%s", &title);
        printf("Please choose the column's type by entering their corresponding number (from 1 to 6)\n");
        printf("Usigned Int - Int - Char - Float - Double - String\n");
        scanf("%d", &type_choice);
        
        switch (type_choice){
            case 1 :
                pointer = lst_create_lnode(create_column(UINT, title));
                break;
            case 2 :
                pointer = lst_create_lnode(create_column(INT, title));
                break;
            case 3 :
                pointer = lst_create_lnode(create_column(CHAR, title));
                break;
            case 4 :
                pointer = lst_create_lnode(create_column(FLOAT, title));
                break;
            case 5 :
                pointer = lst_create_lnode(create_column(DOUBLE, title));
                break;
            case 6 :
                pointer = lst_create_lnode(create_column(STRING, title));
                break;
            default :
                printf("Incorrect type input.");
                break;
        }
        print_col(pointer->data);
        if (i != 0){
            prev->next = pointer;
            pointer->prev = prev;
        } else{
            pointer->prev = NULL;
            cdf->tail = pointer;
        }
        prev = pointer;
        pointer = pointer->next;
        
    }
    cdf->head = pointer;
    printf("\n///////Finish///////////\n");
    return;
}

void fill_hard_cdf(CDATAFRAME *cdf, int nb_input){
    /**
     * @brief Fills a CDataframe with random data
     * @param cdf Pointer to the CDataframe
     * @param nb_input Number of columns to be created
     */
    LNODE* pointer = cdf->tail;
    cdf->tail = pointer;
    LNODE* prev;
    char title[50] = "Random fill";

    int type_choice;
    for (int i=0; i<nb_input; i++){
        type_choice = rand()%6 +1;
        switch (type_choice){
            case 1 :
                pointer = lst_create_lnode(create_column(UINT, title));
                break;
            case 2 :
                pointer = lst_create_lnode(create_column(INT, title));
                break;
            case 3 :
                pointer = lst_create_lnode(create_column(CHAR, title));
                break;
            case 4 :
                pointer = lst_create_lnode(create_column(FLOAT, title));
                break;
            case 5 :
                pointer = lst_create_lnode(create_column(DOUBLE, title));
                break;
            case 6 :
                pointer = lst_create_lnode(create_column(STRING, title));
                break;
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
    /**
     * @brief Displays the CDataframe
     * @param cdf CDataframe to be displayed
     */
    LNODE* pointer = cdf.tail;
    while (pointer != cdf.head){
        print_col(pointer->data);
        pointer = pointer->next;
    }
    print_col(pointer->data);
    return;
}

void display_rows_cdf(CDATAFRAME cdf, unsigned long long int limit){
    /**
     * @brief Displays the rows of the CDataframe
     * @param cdf CDataframe to be displayed
     * @param limit Maximum number of rows to display
    */
    LNODE* pointer = cdf.tail;
    while (pointer != NULL){    // Yes, I just copied the print_col function and changed the for loop
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
    /**
     * @brief Displays the columns of the CDataframe
     * @param cdf CDataframe to be displayed
     * @param limit Maximum number of columns to display
     */
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
    if (cdf->tail == NULL){
        printf("Adding row failed\n");
    }
    while (pointer != NULL){
        if (i > pointer->data->max_size){   
            pointer->data->max_size += 256;
            pointer->data->data = (COL_TYPE**) realloc(pointer->data->data, pointer->data->max_size*sizeof(pointer->data->column_type));
            for (int j=pointer->data->size; j<i; j++){
                pointer->data->data[j] = NULL;
                pointer->data->size++;
            }
        } else {
            memmove(&pointer->data->data[i+1] , &pointer->data->data[i], sizeof(pointer->data->column_type));
            pointer->data->data[i] = NULL;
            pointer->data->size++;
        }
        pointer = pointer->next;
    }
    return;
}

void add_col_cdf(CDATAFRAME *cdf, ENUM_TYPE type, char *col_name, int i){
    if (i < 1){
        printf("Adding col failed\n");
        return;
    }
    cdf->size++;
    cdf = (CDATAFRAME*) realloc(cdf, cdf->size*sizeof(CDATAFRAME)); // We've put double pointers before for realloc, don't know if it's correct
    LNODE *pointer = (LNODE*) malloc(sizeof(LNODE));
    switch (type){
        case UINT :
            pointer = lst_create_lnode(create_column(UINT, col_name));
            break;
        case INT :
            pointer = lst_create_lnode(create_column(INT, col_name));
            break;
        case CHAR :
            pointer = lst_create_lnode(create_column(CHAR, col_name));
            break;
        case FLOAT :
            pointer = lst_create_lnode(create_column(FLOAT, col_name));
            break;
        case DOUBLE :
            pointer = lst_create_lnode(create_column(DOUBLE, col_name));
            break;
        case STRING :
            pointer = lst_create_lnode(create_column(STRING, col_name));
            break;
    }
    if (i == 1){
        lst_insert_tail(cdf, pointer);
        return;
    } if (cdf->size == i){
        lst_insert_head(cdf, pointer);
        return;
    } if (0 < i < cdf->size + 1) {
        LNODE* tmp = cdf->tail;
        while (i-1 != 0){
            tmp = tmp->next;
            i--;
        }
        lst_insert_after(cdf, pointer, tmp);
    }
    return;
}

void delete_row_cdf(CDATAFRAME *cdf, int i){
    LNODE* pointer = cdf->tail;
    if (cdf->tail == NULL){
        printf("Adding row failed\n");
    }
    while (pointer != NULL){    
        memmove(&pointer->data->data[i] , &pointer->data->data[i+1], sizeof(pointer->data->column_type));
        pointer->data->size++;
        pointer = pointer->next;
    }
    return;
}

void delete_col_i_cdf(CDATAFRAME *cdf, int i){
    LNODE *pointer = cdf->tail;
    if (cdf->tail == NULL){
        printf("Deleting col failed.\n");
        return;
    } if (i == 1){
        lst_delete_tail(cdf);
        return;
    } if (cdf->size == i){
        lst_delete_head(cdf);
        return;
    } if (0 < i < cdf->size + 1) {
        LNODE* tmp = cdf->tail;
        while (i-1 != 0){
            tmp = tmp->next;
            i--;
        }
        lst_delete_lnode(cdf, tmp);
    }
    return;
}

void rename_col_cdf(CDATAFRAME *cdf, char *og_name, char *new_col_name){
    if (cdf == NULL){
        printf("Error : no elements in CDataFrame\n");
        return;
    }

    LNODE* pointer = cdf->tail;
    while (pointer != NULL){
        if (strcmp(pointer->data->title, og_name) == 0){
            strcpy(pointer->data->title, new_col_name);
            free(pointer);
            return;
        }
        pointer = pointer->next;
    }
    printf("Error : column name given in parameter.\n");
    return;
}

void search_value_cdf(CDATAFRAME cdf, ENUM_TYPE type, COL_TYPE *value){
    if (cdf.tail == NULL){
        printf("Error : no elements in CDataframe\n");
        return;
    }
    LNODE *pointer = cdf.tail;
    int i=1; int exist = 1;
    while (pointer != NULL){
        if (pointer->data->column_type == type){
            for (int j=0; j<pointer->data->size; j++){
                if (pointer->data->data[j] == value){
                    printf("Value found at position in column %d in row %d", i, j);
                }
            }
        }
        i++;
        pointer = pointer->next;
    }
    if (exist == 1){
        printf("Value not found in CDataframe : please verify the type and the value entered\n");
        return;
    }
}

COL_TYPE* get_value_cdf(CDATAFRAME cdf, int col, unsigned long long int row){
    if (cdf.tail == NULL){
        printf("Error : no elements in CDataframe\n");
        return NULL;
    } if (col > cdf.size){
        printf("Error : col number too big\n");
        return NULL;
    }
    LNODE* pointer = cdf.tail;
    for (int i=1; i<col; i++){
        pointer = pointer->next;
    }
    if (row > pointer->data->size){
        printf("Error : row number too big\n");
        return NULL;
    }
    return pointer->data->data[row];
}

void change_value_cdf(CDATAFRAME *cdf, int col, unsigned long long int row, COL_TYPE *value){
    if (cdf->tail == NULL){
        printf("Error : no elements in CDataframe\n");
        return;
    } if (col > cdf->size){
        printf("Error : col number too big\n");
        return;
    }
    LNODE* pointer = cdf->tail;
    for (int i=1; i<col; i++){
        pointer = pointer->next;
    }
    if (row > pointer->data->size){
        printf("Error : row number too big\n");
        return;
    }
    pointer->data->data[row] = value;
    return;
}

void display_col_names(CDATAFRAME cdf){
    if (cdf.tail == NULL){
        printf("Error : no elements in CDataframe\n");
        return;
    }
    LNODE *pointer = cdf.tail;
    while (pointer != NULL){
        printf("Column 1 : %s\n", pointer->data->title);
        pointer = pointer->next;
    }
    return;
}

<<<<<<< HEAD
void display_num_rows(CDATAFRAME *cdf){
    /**
     * Get the number of rows in the dataframe.
     * @param cdf Pointer to the dataframe struct.
     * @return Number of rows in the dataframe.
     */
    printf("Number of rows: %d\n", cdf->num_rows);
}

void display_num_columns(CDATAFRAME *cdf){
    /**
     * Get the number of columns in the dataframe.
     * @param cdf Pointer to the dataframe struct.
     * @return Number of columns in the dataframe.
     */
    printf("Number of columns: %d\n", cdf->num_columns);
}

void display_num_cells_equal_to(CDATAFRAME *cdf, int x){
    /**
     * Get the count of cells equal to a given value in the dataframe.
     * @param cdf Pointer to the dataframe struct.
     * @param x Value to compare with.
     * @return Number of cells equal to the given value.
     */
    int count = 0;
    for (int i = 0; i < cdf->num_rows; i++) {
        for (int j = 0; j < cdf->num_columns; j++) {
            if (cdf->data[i][j] == x) {
                count++;
=======
void display_num_rows(list *lst){
    if (lst == NULL || lst->head == NULL) {
        printf("Number of rows: 0\n");
        return;
    }
    int num_rows = 0;
    lnode *current_node = lst->head;
    while (current_node != NULL) {
        if (current_node->data != NULL) {
            if (current_node->data->size > num_rows) {
                num_rows = current_node->data->size;
>>>>>>> 46228f4325eb1aff1be4c5a34ccace630c3e7db8
            }
        }
        current_node = current_node->next;
    }
    printf("Number of rows: %d\n", num_rows);
}

<<<<<<< HEAD
void display_num_cells_greater_than(CDATAFRAME *cdf, int x){
    /**
     * Get the count of cells containing a value greater than a given value in the dataframe.
     * @param cdf Pointer to the dataframe struct.
     * @param x Value to compare with.
     * @return Number of cells containing a value greater than the given value.
     */
    int count = 0;
    for (int i = 0; i < cdf->num_rows; i++) {
        for (int j = 0; j < cdf->num_columns; j++) {
            if (cdf->data[i][j] > x) {
                count++;
            }
        }
=======
void display_num_columns(list *lst){
    if (lst == NULL || lst->head == NULL) {
        printf("Number of columns: 0\n");
        return;
>>>>>>> 46228f4325eb1aff1be4c5a34ccace630c3e7db8
    }
    int num_columns = 0;
    lnode *current_node = lst->head;
    while (current_node != NULL) {
        num_columns++;
        current_node = current_node->next;
    }
    printf("Number of columns: %d\n", num_columns);
}

<<<<<<< HEAD
void display_num_cells_less_than(CDATAFRAME *cdf, int x){
    /**
     * Get the count of cells containing a value less than a given value in the dataframe.
     * @param df Pointer to the dataframe struct.
     * @param x Value to compare with.
     * @return Number of cells containing a value less than the given value.
     */
    int count = 0;
    for (int i = 0; i < cdf->num_rows; i++) {
        for (int j = 0; j < cdf->num_columns; j++) {
            if (cdf->data[i][j] < x) {
                count++;
            }
        }
=======
void display_num_cells_equal_to(list *lst, void *x){
    if (lst == NULL || lst->head == NULL) {
        printf("Number of cells equal to %p: 0\n", x);
        return;
>>>>>>> 46228f4325eb1aff1be4c5a34ccace630c3e7db8
    }
    int count = 0;
    lnode *current_node = lst->head;
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        if (col != NULL) {
            count += count_values_equal_to_x(col, x);
        }
        current_node = current_node->next;
    }
    printf("Number of cells equal to %p: %d\n", x, count);
}

void display_num_cells_greater_than(list *lst, void *x){
    if (lst == NULL || lst->head == NULL) {
        printf("Number of cells greater than %p: 0\n", x);
        return;
    }
    int count = 0;
    lnode *current_node = lst->head;
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        if (col != NULL) {
            count += count_values_greater_than_x(col, x);
        }
        current_node = current_node->next;
    }
    printf("Number of cells greater than %p: %d\n", x, count);
}

void display_num_cells_less_than(list *lst, void *x){
    if (lst == NULL || lst->head == NULL) {
        printf("Number of cells less than %p: 0\n", x);
        return;
    }
    int count = 0;
    lnode *current_node = lst->head;
    while (current_node != NULL) {
        COLUMN *col = current_node->data;
        if (col != NULL) {
            count += count_values_less_than_x(col, x);
        }
        current_node = current_node->next;
    }
    printf("Number of cells less than %p: %d\n", x, count);
}
