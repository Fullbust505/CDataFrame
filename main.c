#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"
#include "cdataframe.h"
#define N 5

void display_menu(){
    printf("\nMenu:\n");
    printf("1. Create Column\n");
    printf("2. Insert Value in Column\n");
    printf("3. Print Column\n");
    printf("4. Delete Column\n");
    printf("5. Fill Dataframe with Input\n");
    printf("6. Hard fill Dataframe\n");
    printf("7. Display Dataframe\n");
    printf("8. Delete Dataframe\n");
    printf("9. Count Values Greater Than X\n");
    printf("10. Count Values Less Than X\n");
    printf("11. Count Values Equal To X\n");
    printf("12. Display the Dataframe's number of rows\n");
    printf("13. Display the Dataframe's number of columns\n");
    printf("14. Exit\n");
    printf("Choose an option: ");
}

int main(){

    int choice;
    COLUMN *mycol = create_column(INT, "test");
    CDATAFRAME *cdf = create_cdf(50);

    do {
        display_menu();
        scanf("%d", &choice);
        flush_input_buffer(); // Clear the input buffer

        switch (choice) {
            case 1: {
                char title[50];
                int type_choice;
                printf("Enter column title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; // Remove newline character
                
                printf("Enter column type (1: UINT, 2: INT, 3: CHAR, 4: FLOAT, 5: DOUBLE, 6: STRING): ");
                scanf("%d", &type_choice);
                flush_input_buffer(); // Clear the input buffer
                ENUM_TYPE type = (ENUM_TYPE)type_choice;

                int i = 0;
                printf("Where do you want to add it ? (Enter index of row) : ");
                scanf("%d", &i);
                add_col_cdf(cdf, type, title, i);
                break;
            }
            case 2: {
                if (cdf == NULL) {
                    printf("No column created yet.\n");
                } else {
                    int i = 0;
                    printf("Where do you want to add your value ? (Enter column index) : ");
                    scanf("%d", &i);
                    if ((i < 1) || (i > cdf->size+1)){
                        printf("Index of column incorrect\n");
                        break;
                    }
                    LNODE * pointer = cdf->tail;
                    while (i-1 != 0){
                        pointer = pointer->next;
                    }
                    
                    unsigned long long int j = 0;
                    printf("At which line do you want to add it ? (Enter row index) : ");
                    scanf("%llu", &j);
                    if ((j < 0)||(j > pointer->data->size +1)){
                        printf("Index of row incorrect\n");
                        break;
                    }
                    printf("Enter value to insert: ");
                    switch(pointer->data->column_type){
                        case UINT:
                            unsigned int ui_value;
                            scanf("%u", &ui_value);
                            insert_value(pointer->data, j, &ui_value);
                            break;
                        case INT:
                            int i_value;
                            scanf("%d", &i_value);
                            insert_value(pointer->data, j, &i_value);                            break;
                        case CHAR:
                            char c_value;
                            scanf("%c", &c_value);
                            insert_value(pointer->data, j, &c_value);
                            break;
                        case FLOAT:
                            float f_value;
                            scanf("%f", &f_value);
                            insert_value(pointer->data, j, &f_value);
                            break;
                        case DOUBLE:
                            double d_value;
                            scanf("%ld", &d_value);
                            insert_value(pointer->data, j, &d_value);
                            break;
                        case STRING:
                            char *s_value[50];
                            scanf("%s", s_value);
                            insert_value(pointer->data, j, s_value);
                            break;
                        default:
                            printf("An Error occured\n");
                            break;
                    }
                    
                    flush_input_buffer(); // Clear the input buffer


                    printf("Value inserted successfully.\n");
                }
                break;
            }
            case 3: {
                if (mycol == NULL) {
                    printf("No column created yet.\n");
                } else {
                    printf("Which column do you want to print ? (Enter index of column) : ");
                    int col_choice;
                    scanf("%d", &col_choice);
                    
                    LNODE *pointer = cdf->tail;
                    while (col_choice-1 != 0){
                        pointer = pointer->next;
                    }
                    print_col(pointer->data);
                }
                break;
            }
            case 4: {
                if (mycol != NULL) {
                    delete_column(&mycol);
                    printf("Column deleted successfully.\n");
                } else {
                    printf("Which column do you want to delete ? (Enter index of column) : ");
                    int col_choice;
                    scanf("%d", &col_choice);
                    
                    LNODE *pointer = cdf->tail;
                    while (col_choice-1 != 0){
                        pointer = pointer->next;
                    }
                    delete_column(&pointer->data);
                }
                break;
            }
            case 5: {
                if (cdf == NULL) {
                    printf("No dataframe created yet.\n");
                } else {
                    int num_inputs;
                    printf("Enter number of inputs: ");
                    scanf("%d", &num_inputs);
                    flush_input_buffer(); // Clear the input buffer

                    fill_input_cdf(cdf, num_inputs);

                    printf("Dataframe filled successfully.\n");
                }
                break;
            }
            case 6 :
                if (cdf == NULL){
                    printf("No dataframe created yet.\n");
                } else{
                    int num_inputs;
                    printf("Enter number of columns: ");
                    scanf("%d", &num_inputs);
                    flush_input_buffer(); // Clear the input buffer

                    fill_hard_cdf(cdf, num_inputs);

                    printf("Dataframe filled successfully.\n");
                }
            case 7: {
                if (cdf == NULL) {
                    printf("No dataframe created yet.\n");
                } else {
                    display_cdf(*cdf);
                }
                break;
            }
            case 8: {
                if (cdf != NULL) {
                    delete_cdf(&cdf);
                    printf("Dataframe deleted successfully.\n");
                } else {
                    printf("No dataframe to delete.\n");
                }
                break;
            }
            case 9: {
                if (cdf == NULL) {
                    printf("No column created yet.\n");
                } else {
                    int type;
                    printf("Please choose the value's type by entering their corresponding number (from 1 to 6)\n");
                    printf("Usigned Int - Int - Char - Float - Double - String\n");
                    scanf("%d", &type);
                    printf("Enter value to compare: ");
                    switch(type){
                        case 1:
                            unsigned int ui_value;
                            printf("Enter a value to enter : ");
                            scanf("%u", &ui_value);
                            display_num_cells_greater_than(cdf,&ui_value);
                            break;
                        case INT:
                            int i_value;
                            scanf("%d", &i_value);
                            display_num_cells_greater_than(cdf,&i_value);                            break;
                        case CHAR:
                            char c_value;
                            scanf("%c", &c_value);
                            display_num_cells_greater_than(cdf,&c_value);
                            break;
                        case FLOAT:
                            float f_value;
                            scanf("%f", &f_value);
                            display_num_cells_greater_than(cdf,&f_value);
                            break;
                        case DOUBLE:
                            double d_value;
                            scanf("%ld", &d_value);
                            display_num_cells_greater_than(cdf,&d_value);
                            break;
                        case STRING:
                            char *s_value[50];
                            scanf("%s", s_value);
                            display_num_cells_greater_than(cdf, s_value);
                            break;
                    }
                    flush_input_buffer(); // Clear the input buffer
                }
            }
            case 10: {
                if (cdf == NULL) {
                    printf("No column created yet.\n");
                } else {
                    int type;
                    printf("Please choose the value's type by entering their corresponding number (from 1 to 6)\n");
                    printf("Usigned Int - Int - Char - Float - Double - String\n");
                    scanf("%d", &type);
                    printf("Enter value to compare: ");
                    switch(type){
                        case 1:
                            unsigned int ui_value;
                            printf("Enter a value to enter : ");
                            scanf("%u", &ui_value);
                            display_num_cells_less_than(cdf,&ui_value);
                            break;
                        case INT:
                            int i_value;
                            scanf("%d", &i_value);
                            display_num_cells_less_than(cdf,&i_value);                            break;
                        case CHAR:
                            char c_value;
                            scanf("%c", &c_value);
                            display_num_cells_less_than(cdf,&c_value);
                            break;
                        case FLOAT:
                            float f_value;
                            scanf("%f", &f_value);
                            display_num_cells_less_than(cdf,&f_value);
                            break;
                        case DOUBLE:
                            double d_value;
                            scanf("%ld", &d_value);
                            display_num_cells_less_than(cdf,&d_value);
                            break;
                        case STRING:
                            char *s_value[50];
                            scanf("%s", s_value);
                            display_num_cells_less_than(cdf, s_value);
                            break;
                    }
                    flush_input_buffer(); // Clear the input buffer
                }
            }
            case 11: {
                if (cdf == NULL) {
                    printf("No column created yet.\n");
                } else {
                    int type;
                    printf("Please choose the value's type by entering their corresponding number (from 1 to 6)\n");
                    printf("Usigned Int - Int - Char - Float - Double - String\n");
                    scanf("%d", &type);
                    printf("Enter value to compare: ");
                    switch(type){
                        case 1:
                            unsigned int ui_value;
                            printf("Enter a value to enter : ");
                            scanf("%u", &ui_value);
                            display_num_cells_equal_to(cdf,&ui_value);
                            break;
                        case INT:
                            int i_value;
                            scanf("%d", &i_value);
                            display_num_cells_equal_to(cdf,&i_value);                            break;
                        case CHAR:
                            char c_value;
                            scanf("%c", &c_value);
                            display_num_cells_equal_to(cdf,&c_value);
                            break;
                        case FLOAT:
                            float f_value;
                            scanf("%f", &f_value);
                            display_num_cells_equal_to(cdf,&f_value);
                            break;
                        case DOUBLE:
                            double d_value;
                            scanf("%ld", &d_value);
                            display_num_cells_equal_to(cdf,&d_value);
                            break;
                        case STRING:
                            char *s_value[50];
                            scanf("%s", s_value);
                            display_num_cells_equal_to(cdf, s_value);
                            break;
                    }
                    flush_input_buffer(); // Clear the input buffer
                }
            }
            case 12: { // Display Number of Rows
                if (cdf == NULL) {
                    printf("No dataframe created yet.\n");
                } else {
                    display_num_rows(cdf);
                }
                break;
            }
            case 13: { // Display Number of Columns
                if (cdf == NULL) {
                    printf("No dataframe created yet.\n");
                } else {
                    display_num_columns(cdf);
                }
                break;
            }
            case 14: {
                printf("Exiting program.\n");
                break;
            }
            default:
                printf("Invalid option. Please try again.\n");
                break;
            
        }
    } while (choice != 14);
    // Clean up resources if not already done
    if (mycol != NULL) {
        delete_column(&mycol);
    }
    if (cdf != NULL) {
        delete_cdf(&cdf);
    }
    return 0;
}