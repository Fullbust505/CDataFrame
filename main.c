#include <stdio.h>
#include <stdlib.h>
#include "column.h"
#include "cdataframe.h"
#define N 5

void display_menu(){
    printf("\nMenu:\n");
    printf("1. Create Column\n");
    printf("2. Insert Value in Column\n");
    printf("3. Print Column\n");
    printf("4. Delete Column\n");
    printf("5. Create Dataframe\n");
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
    // Tests

    /* COLUMN TEST 
    char str[5];
    COLUMN *mycol = create_column(INT, "My column");
    int a = 52, b = 44, c = 15, d = 18;
    insert_value(mycol, &a);
    insert_value(mycol, &b);
    insert_value(mycol, &c);
    insert_value(mycol, &d);
    print_col(mycol);
    delete_column(&mycol);
    */

    int choice;
    COLUMN *mycol = NULL;
    CDATAFRAME *cdf = NULL;

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
                mycol = create_column(type, title);
                printf("Column created successfully.\n");
                break;
            }
            case 2: {
                if (mycol == NULL) {
                    printf("No column created yet.\n");
                } else {
                    int value;
                    printf("Enter value to insert: ");
                    scanf("%d", &value);
                    flush_input_buffer(); // Clear the input buffer

                    insert_value(mycol, &value);

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
            case 5: {
                int num_columns;
                printf("Enter number of columns in the dataframe: ");
                scanf("%d", &num_columns);
                flush_input_buffer(); // Clear the input buffer

                ENUM_TYPE cdftype[num_columns];
                for (int i = 0; i < num_columns; i++) {
                    printf("Enter type for column %d (1: UINT, 2: INT, 3: CHAR, 4: FLOAT, 5: DOUBLE, 6: STRING): ", i + 1);
                    scanf("%d", &cdftype[i]);
                    flush_input_buffer(); // Clear the input buffer
                }

                cdf = create_cdf(cdftype, num_columns);

                printf("Dataframe created successfully.\n");
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

                    int count = count_values_greater_than_x(mycol, value);
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

                    int count = count_values_less_than_x(mycol, value);
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

                    int count = count_values_equal_to_x(mycol, value);
                    printf("Number of values equal to %d: %d\n", value, count);
                }
                break;
            }
            case 12:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (choice != 12);
    // Clean up resources if not already done
    if (mycol != NULL) {
        delete_column(&mycol);
    }
    if (cdf != NULL) {
        delete_cdf(&cdf);
    }
    return 0;
}