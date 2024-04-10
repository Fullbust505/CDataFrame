# DataFrameC

Our L1 C Project. The objective is to create a library similar to Panda (of Python) but in C

## Problems

Not all functions return NULL pointers in case of a failure in their execution.

## Last changes

### Linus

FINALLY finished the "convert_value" function THOUGH not sure if it works yet, we'll need the display function to test it.
Other option to avoid time consuming methods : If we start from the end of str, it will be quicker (O(n) instead of higher) but dunno what happens if we have empty first cases for str. After some tests, it seems to not work, not 100% sure, check with teacher perhaps.

### Raphaël

Added a "display_value" and "print_column" function using the "convert_value" to print the value int the needed type
