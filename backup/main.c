#include <stdio.h>
#include "column.h"
#define N 5

int main(){
    
    // Tests
    char str[5];
    COLUMN *mycol = create_column(INT, "My column");
    int a = 52, b = 44, c = 15, d = 18;
    insert_value(mycol, &a);
    insert_value(mycol, &b);
    insert_value(mycol, &c);
    insert_value(mycol, &d);
    convert_value(mycol, 2, str, N);
    printf("%s \n", str);
    delete_column(&mycol);

    return 0;
}