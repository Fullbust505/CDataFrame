# DataFrameC

Our L1 C Project. The objective is to create a library similar to Panda (of Python) but in C.
Here's a [link to our Github](https://github.com/Fullbust505/CDataFrame).

## Problems

Not all functions return NULL pointers in case of a failure in their execution.

## Last changes

### Linus

Got my answer for the index issue, it will be used later apprently.
Added the "n_occ" function (NOT TESTED YET !!)
Added the "n_pos" function (NOT TESTED YET !!)
Btw, I noticed that we did apply cases for columns of type CHAR but not of type STRING. So... we'll have to add it. Don't have the strength tonight.

### Raphaël

Tried to fix title issue for a new column.
Added type STRING in the insert and convert value function.