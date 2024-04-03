#ifndef COLUMN_H
#define COLUMN_H

COLUMN *create_column(ENUM_TYPE type, char *title);
int insert_value(COLUMN *col, void *value);

#endif