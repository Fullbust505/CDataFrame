# DataFrameC

Our L1 C Project. The objective is to create a library similar to Panda (of Python) but in C

## Problems

Not all functions return NULL pointers in case of a failure in their execution.

## Last changes

### Linus

Moved the definitions of COLUMN, ENUM_TYPE and COL_TYPE to be able to access them in the main (otherwise, no test was possible).
Corrected the function "insert value"
Added the "destroy_col" function though I don't know if we should parkour the whole array to free each variable or not. To ask a teacher.
Added a test column, will be useful when we have the display function.
Corrected some docstring to make it more suitable and presentable.
Updated column.h
Adding "convert_to_str" function but not finished

### Raphaël
