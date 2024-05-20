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
    printf("6. Fill Dataframe with Input\n");
    printf("7. Display Dataframe\n");
    printf("8. Delete Dataframe\n");
    printf("9. Count Values Greater Than X\n");
    printf("10. Count Values Less Than X\n");
    printf("11. Count Values Equal To X\n");
    printf("12. Exit\n");
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
                printf("Where do you want to add it ? (Enter index of column) : ");
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
                    if ((i < 1) || (i > cdf->size)){
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
                    if ((j < 0)||(j > pointer->data->size)){
                        printf("Index of row incorrect\n");
                        break;
                    }
                    printf("Enter value to insert: ");
                    switch(pointer->data->column_type){
                        case UINT:
                            unsigned int ui_value;
                            printf("Enter a value to enter : ");
                            scanf("%u", ui_value);
                            insert_value(pointer->data, j, &ui_value);
                            break;
                        case INT:
                            int i_value;
                            scanf("%d", i_value);
                            insert_value(pointer->data, j, &i_value);                            break;
                        case CHAR:
                            char c_value;
                            scanf("%c", c_value);
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
                    print_col(mycol);
                }
                break;
            }
            case 4: {
                if (mycol != NULL) {
                    delete_column(&mycol);
                    printf("Column deleted successfully.\n");
                } else {
                    printf("No column to delete.\n");
                }
                break;
            }
            case 6: {
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
                if (mycol == NULL) {
                    printf("No column created yet.\n");
                } else {
                    int value;
                    printf("Enter value to compare: ");
                    scanf("%d", &value);
                    flush_input_buffer(); // Clear the input buffer

                    int count = count_values_greater_than_x(mycol, &value);
                    printf("Number of values greater than %d: %d\n", value, count);
                }
                break;
            }
            case 10: {
                if (mycol == NULL) {
                    printf("No column created yet.\n");
                } else {
                    int value;
                    printf("Enter value to compare: ");
                    scanf("%d", &value);
                    flush_input_buffer(); // Clear the input buffer

                    int count = count_values_less_than_x(mycol, &value);
                    printf("Number of values less than %d: %d\n", value, count);
                }
                break;
            }
            case 11: {
                if (mycol == NULL) {
                    printf("No column created yet.\n");
                } else {
                    int value;
                    printf("Enter value to compare: ");
                    scanf("%d", &value);
                    flush_input_buffer(); // Clear the input buffer

                    int count = count_values_equal_to_x(mycol, &value);
                    printf("Number of values equal to %d: %d\n", value, count);
                }
                break;
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
            case 14: { // Display Number of Cells Greater Than X
                if (cdf == NULL) {
                    printf("No dataframe created yet.\n");
                } else {
                    int value;
                    printf("Enter value to compare: ");
                    scanf("%d", &value);
                    flush_input_buffer(); // Clear the input buffer

                    display_num_cells_greater_than(cdf, &value);
                }
                break;
            }
            case 15: { // Display Number of Cells Less Than X
                if (cdf == NULL) {
                    printf("No dataframe created yet.\n");
                } else {
                    int value;
                    printf("Enter value to compare: ");
                    scanf("%d", &value);
                    flush_input_buffer(); // Clear the input buffer

                    display_num_cells_less_than(cdf, &value);
                }
                break;
            }
            case 16: { // Display Number of Cells Equal To X
                if (cdf == NULL) {
                    printf("No dataframe created yet.\n");
                } else {
                    int value;
                    printf("Enter value to compare: ");
                    scanf("%d", &value);
                    flush_input_buffer(); // Clear the input buffer

                    display_num_cells_equal_to(cdf, &value);
                }
                break;
            }

            case 17:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (choice != 17);
    // Clean up resources if not already done
    if (mycol != NULL) {
        delete_column(&mycol);
    }
    if (cdf != NULL) {
        delete_cdf(&cdf);
    }
    return 0;
}