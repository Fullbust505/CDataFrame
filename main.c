#include <stdio.h>
#include <stdlib.h>
#include "column.h"
#include "cdataframe.h"
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
    print_col(mycol);
    delete_column(&mycol);

    ENUM_TYPE cdftype [] = {INT,CHAR,INT};
    CDATAFRAME *cdf = create_cdf(cdftype, 3);


    return 0;
}