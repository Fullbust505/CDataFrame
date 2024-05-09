# DataFrameC

Our L1 C Project. The objective is to create a library similar to Panda (of Python) but in C.
Here's a [link to our Github](https://github.com/Fullbust505/CDataFrame).

## Problems

Dataframe not finished.

## Last changes

### Linus

Added the list files. They are not a part of our job, they are given in the appendix of the project document.
Added functions to create, free and fill CDataFrame. Forgot the docstring.
Little optimization problem here : unfortunately, the "fill_input_cdf" has a big switch case. The reason is because a user cannot enter an ENUM_TYPE and we can't convert a string in an ENUM_TYPE except with a switch case, so... I had to do it. If you have something else, I'll gladly take it cuz now it's not very clean.

### Raphaël

Tried to fix title issue for a new column.
Added type STRING in the insert and convert value function.
