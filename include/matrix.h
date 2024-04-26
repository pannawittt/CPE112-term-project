#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "util.h"

#ifndef MAX_CHAR
#define MAX_CHAR 250
#endif // MAX_CHAR

typedef struct{
    int _row;
    int _col;
    char*** data;
}mat;

mat mat_create(int row_size, int col_size);
mat mat_readcsv(mat *_mat, char *_file);
mat mat_transpose(mat *_mat);
void mat_erase(mat *_mat);
char* mat_get(const mat *_mat, int row, int col);

#endif // matrix.h