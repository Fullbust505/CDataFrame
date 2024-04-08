#include <stdio.h>
#include "column.h"

int main(){
    
    // Tests
    ENUM_TYPE type;
    type = INT;
    char title[10] = "TEST";
    COLUMN *mycol = create_column(type, &title);
    

    return 0;
}