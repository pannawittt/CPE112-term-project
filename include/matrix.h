#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stddef.h>

typedef struct mat *mat;

mat mat_create(const int _rowSize,const int _colSize);
mat mat_readcsv(const char *_file);
mat mat_transpose(mat _mat);
void mat_erase(mat _mat);
char* mat_get(const mat _mat, const int _row, const int _col);
void mat_print(const mat _mat);
void mat_sortrow(mat _mat, const int _sortByColumn, int (*_cmprFunc)(const char*, const char*));
mat mat_getrows(const mat _mat, const int _start, const int _end);
mat mat_getrow(const mat _mat, const int _row);
mat mat_siftrow(const mat _mat, int (*_checkFunc)(char**));
void mat_delrow(mat _mat, const int _row);
void mat_catrow(mat _matDestination, const mat _matSource);
void mat_cpyrow(mat _matDestination, const int _rowDestination, const mat _matSource, const int _rowSource);
size_t mat_lenrow(const mat _mat);
size_t mat_lencol(const mat _mat);

#endif // matrix.h