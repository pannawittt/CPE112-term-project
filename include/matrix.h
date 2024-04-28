#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "util.h"

#ifndef MAX_CHAR
#define MAX_CHAR 250
#endif // MAX_CHAR

typedef struct{
    int row;
    int col;
    char*** data;
}mat;

void _mat_mergesort(char* **arr, int l, int r, int cmpind, int (*cmpfunc)(const char*, const char*));
void _mat_merge(char* **arr, int l, int m, int r, int cmpind, int (*cmpfunc)(const char*, const char*));

mat mat_create(int _rowSize, int _colSize);
mat mat_readcsv(mat *_mat, char *_file);
mat mat_transpose(mat *_mat);
void mat_erase(mat *_mat);
char* mat_get(const mat *_mat, int _row, int _col);
void mat_print(const mat *_mat);
void mat_sortrow(mat *_mat, int _sortColumn, int (*_cmprFunc)(const char*, const char*));
mat mat_getrow(const mat *_mat, int _start, int _end);
void mat_delrow(mat *_mat, int _row);

#endif // matrix.h