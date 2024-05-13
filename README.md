# DataFrameC

Our L1 C Project. The objective is to create a library similar to Panda (of Python) but in C.
Here's a [link to our Github](https://github.com/Fullbust505/CDataFrame).

## Problems

WHY THE FUCK DOES THE PROGRAM DOESN T DISPLAY ANY COLUMNS AND FUCKING DOESN T GO THROUGH ALL THE FUNCTIONS.
Basically, when I want to create a Dataframe, it cries a bit (not really) and doesn't proceed through all the functions (like fill_input).

## Last changes

### Linus

Added the list files. They are not a part of our job, they are given in the appendix of the project document.
Added functions to create, free and fill CDataframe. Forgot the docstring. Added display functions for the CDataframe.
Added function protoypes for certain functions and started them (add row, add col).
Little optimization problem here : unfortunately, the "fill_input_cdf" has a big switch case. The reason is because a user cannot enter an ENUM_TYPE and we can't convert a string in an ENUM_TYPE except with a switch case, so... I had to do it. If you have something else, I'll gladly take it cuz now it's not very clean.
Be aware that I didn't test any function, I am exhausted and don't have the faith to confront my errors. However, when building the project, I didn't encounter any major error.

### Raphaël

Tried to fix title issue for a new column.
Added type STRING in the insert and convert value function.
