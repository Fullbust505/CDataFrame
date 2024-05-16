# DataFrameC

Our L1 C Project. The objective is to create a library similar to Panda (of Python) but in C.
Here's a [link to our Github](https://github.com/Fullbust505/CDataFrame).

## Problems

WHY THE FUCK DOES THE PROGRAM DOESN T DISPLAY ANY COLUMNS AND FUCKING DOESN T GO THROUGH ALL THE FUNCTIONS.
Basically, when I want to create a Dataframe, it cries a bit (not really) and doesn't proceed through all the functions (like fill_input).

## Last changes

### Linus

Destroyed the previous CDATAFRAME structure. Why ? So that now I'll link it to the list.h struct to take advantage of the pre-made functions. HOWEVER, there's a conflict, thanks to the void type of data. We might be able to correct it someday, I'm currently asking a friend of mine how to.

### Raphaël

Tried to fix title issue for a new column.
Added type STRING in the insert and convert value function.
