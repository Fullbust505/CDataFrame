# DataFrameC

Our L1 C Project. The objective is to create a library similar to Panda (of Python) but in C

## Problems

Not all functions return NULL pointers in case of a failure in their execution.

## Last changes

### Linus

FINALLY finished the "convert_value" function THOUGH not sure if it works yet, we'll need the display function to test it.
Other option to avoid time consuming methods : If we start from the end of str, it will be quicker (O(n) instead of higher) but dunno what happens if we have empty first cases for str. After some tests, it seems to not work, not 100% sure, check with teacher perhaps.

### Raphaël

Added switch case in the "insert_value" function to sort the value's location according to it's type
Added an if statement in "create_column" to verify if the value has an index or a memory allocated
