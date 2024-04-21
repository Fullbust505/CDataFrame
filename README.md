# DataFrameC

Our L1 C Project. The objective is to create a library similar to Panda (of Python) but in C.
Here's a [link to our Github](https://github.com/Fullbust505/CDataFrame).

## Problems

Not all functions return NULL pointers in case of a failure in their execution.

## Last changes

### Linus

Corrected the "insert_value" function
Corrected the "print_col" function BUT I do not see the purpose of the index array so we're not gonna use it for now. When I know more about it, I'll change everything cuz for now we add value without updating the index attribute of the column
Added files for the first deposit.

### Raphaël

Added a "display_value" and "print_column" function using the "convert_value" to print the value in the needed type
