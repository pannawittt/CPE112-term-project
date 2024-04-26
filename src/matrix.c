#include "matrix.h"

mat mat_create(int row_size, int col_size){
    mat new_mat;
    new_mat._col = col_size;
    new_mat._row = row_size;
    new_mat.data = (char***)malloc(sizeof(char**)*row_size);
    for(int i=0;i<row_size;i++){
        new_mat.data[i] = (char**)malloc(sizeof(char*)*col_size);
        for(int j=0;j<col_size;j++){
            new_mat.data[i][j] = (char*)malloc(sizeof(char)*MAX_CHAR);
        }
    }
    return new_mat;
}

mat mat_readcsv(mat *_mat, char *_file){
    FILE *f;
    char row[MAX_CHAR*100];
    char* token;
    int i = 0;
    f = fopen(_file, "r");
    while(i < _mat->_row && feof(f) != 1){
        fgets(row, MAX_CHAR*100, f);
        if(row[strlen(row)-1] == '\n'){
            row[strlen(row)-1] = '\0';
        }
        token = strtok(row, ",");
        int j = 0;
        while(j < _mat->_col && token != NULL){
            strcpy(_mat->data[i][j], token);
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    fclose(f);
}

void mat_erase(mat *_mat){
    for(int i=0;i<_mat->_row;i++){
        free(_mat->data[i]);
    }
    free(_mat->data);
}

mat mat_transpose(mat *_mat){
    mat new_mat = mat_create(_mat->_col, _mat->_row);
    for(int i=0;i<_mat->_row;i++){
        for(int j=0;j<_mat->_col;j++){
            new_mat.data[j][i] = _mat->data[i][j];
        }
    }
    mat_erase(_mat);
    *_mat = new_mat;
    return new_mat;
}

char* mat_get(const mat *_mat, int row, int col){
    return _mat->data[row][col];
}