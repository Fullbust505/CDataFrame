# DataFrameC

Our L1 C Project. The objective is to create a library similar to Panda (of Python) but in C.
Here's a [link to our Github](https://github.com/Fullbust505/CDataFrame).

## Functionnalities (if it worked properly)

Create a column
Name the column
Choose the type of values in the column
Print the column
Delete the column
Add more columns
Rename a column
Delete the DataFrame to start over
Add rows
Delete rows
Fill Dataframe with Input
Hard fill Dataframe
Display Dataframe
Delete Dataframe
Count Values Greater Than X
Count Values Less Than X
Count Values Equal To X
Display the Dataframe's number of rows
Display the Dataframe's number of columns
Search a value in the dateframe
Change a value in the dataframe


## Problems we faced during the project

At first we just had a few issues because we made some mistake in the code written.
After a week we encountered a problem with naming our column when creating it, it printed a random name that looked like an address.
We took a day or two to find the error in the functions and merged the branch "title_issue" with the main branch to work easily.

After doing a overhaul of our CDATAFRAME structure to accomodate to our new functions that used simply linked lists, we had some issues when making our functions.
But now, we are facing a big issue (with memory allocation we think), and so the program doesn't work anymore, damn it, just at the end we mess up...

## Step by step progression of the project

We firstly created a CMakeLists and the required files for the start of the project, as well as a backup for any futur prolblems.
Then we created the first functions, like insert_value, create_column, destroy_col and convert_value.
After this we worked on the functions of display_value to display after using the previously added fuctions.
Linus fixed some issues on some functions and added n_occ and n_pos.
Then Raphael finished the remaining basic functions needed for the dataframe.

We planned to use simply linked list(SLL) when creating our dataframe, so Linus wrote the basic functions for nodes for the SLL.
Afterwards, we remade the CDATAFRAME structure to take advantage of the files with the SLL, But we were had a problem with this, the function create_cdf didn't go all the way through and stopped with no error printed.
A few days later, we fixed the issue and started adding more functions to fill the columns, add columns, add indexes for the value inserted, etc.
Then Raphael created a menu in the main file to test out the different functions and actual use the dataframe.
Linus worked on adding and deleting rows of columns created during that time and encountered some difficulties but made it.

For more clarity in the functions Linus had made docstrings on some the functions he made, and Raphael later finished addinf them to the rest of the functions.

Raphael then finished the menu with all the functions needed for the dataframe and Linus fixed some coding mistakes here and there for it to work.

And then we met big issues with memory allocation (at least we think it was that) and we don't know how to fix it at this very moment.

## Last changes

### Linus

All the differents commit since the start :

Moved the definitions of COLUMN, ENUM_TYPE and COL_TYPE to be able to access them in the main (otherwise, no test was possible).
Corrected the function "insert value"
Added the "destroy_col" function though I don't know if we should parkour the whole array to free each variable or not. To ask a teacher.
Added a test column, will be useful when we have the display function.

Corrected some docstring to make it more suitable and presentable.
Updated column.h
Adding "convert_to_str" function but not finished

FINALLY finished the "convert_value" function THOUGH not sure if it works yet, we'll need the display function to test it.
Other option to avoid time consuming methods : If we start from the end of str, it will be quicker (O(n) instead of higher) but dunno what happens if we have empty first cases for str. After some tests, it seems to not work, not 100% sure, check with teacher perhaps.

Corrected the "convert_value" function

Corrected the "insert_value" function
Corrected the "print_col" function BUT I do not see the purpose of the index array so we're not gonna use it for now. When I know more about it, I'll change everything cuz for now we add value without updating the index attribute of the column

Got my answer for the index issue, it will be used later apprently.
Added the "n_occ" function (NOT TESTED YET !!)
Added the "n_pos" function (NOT TESTED YET !!)
Btw, I noticed that we did apply cases for columns of type CHAR but not of type STRING. So... we'll have to add it. Don't have the strength tonight.

All our prior functions work !
We just have to correct the 2 or 3 last ones and then get to the dataframe.

Added the list files. They are not a part of our job, they are given in the appendix of the project document.
Added functions to create, free and fill CDataframe. Forgot the docstring. Added display functions for the CDataframe.
Little optimization problem here : unfortunately, the "fill_input_cdf" has a big switch case. The reason is because a user cannot enter an ENUM_TYPE and we can't convert a string in an ENUM_TYPE except with a switch case, so... I had to do it. If you have something else, I'll gladly take it cuz now it's not very clean.
Be aware that I didn't test any function, I am exhausted and don't have the faith to confront my errors. However, when building the project, I didn't encounter any major error

Destroyed the previous CDATAFRAME structure. Why ? So that now I'll link it to the list.h struct to take advantage of the pre-made functions. HOWEVER, there's a conflict, thanks to the void type of data. We might be able to correct it someday, I'm currently asking a friend of mine how to.

filling functions solved.

we can now add rows. Didn't test them though.
We can delete things now.

Corrected many issues but it still doesn't work...

### Raphaël

All the differents commit since the start :

Added switch case in the "insert_value" function to sort the value's location according to it's type
Added an if statement in "create_column" to verify if the value has an index or a memory allocated

Added a "display_value" and "print_column" function using the "convert_value" to print the value in the needed type

Tried to fix title issue for a new column.
Added type STRING in the insert and convert value function.

Made the followinf functions :
get_value_at_position
count_values_greater_than_x
count_values_less_than_x
count_values_equal_to_x

All the necessary functions that were asked to be added in the project are present.
We can now start the dataframe part of the project.

Added a fill_col function for a future fill_cdt function

Modified the main with a switch case to choose which funtion of the dataframe to run

Added doctrings to many functions that didn't have any

Added functions that displays many things from the dataframe :
-the number of rows in the dataframe.
-the number of columns in the dataframe.
-the number of cells in the dataframe that are equal to a given value x.
-the number of cells in the dataframe that contain a value greater than x.
-the number of cells in the dataframe that contain a value less than x.
