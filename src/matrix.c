#include "matrix.h"

/**
 * นำเข้า library
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * struct mat
*/
struct mat{
    int row;
    int col;
    char*** data;
};

/**
 * macro
*/
#define MAX_CHAR 250

/**
 * private function
*/
int* _getLengthCSV(const char* _file);

void 
_mat_merge(char ***arr, int l, int m, int r, int cmpind, int (*cmpfunc)(const char*, const char*)){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    char ***L = malloc(sizeof(char**)*n1);
    char ***R = malloc(sizeof(char**)*n2);

    for(i=0; i<n1; i++){
        L[i] = arr[l+i];
    }
    for(j=0; j<n2; j++){
        R[j] = arr[m + 1 + j];
    }
    i = j = 0;k = l;
    while (i < n1 && j < n2) {
        if (cmpfunc(L[i][cmpind], R[j][cmpind])) {
            arr[k] = L[i];
            i++;
        }else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = L[i];
        i++;k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;k++;
    }
}

void 
_mat_mergesort(char ***arr, int l, int r, int cmpind, int (*cmpr)(const char*, const char*)){
    if(l < r){
        int m = l+(r-l)/2;
        _mat_mergesort(arr, l, m, cmpind, cmpr);
        _mat_mergesort(arr, m+1, r, cmpind, cmpr);
        _mat_merge(arr, l, m, r, cmpind, cmpr);
    }
}

mat
mat_create(const int row_size, const int col_size){
    mat new_mat = (mat)malloc(sizeof(struct mat));
    new_mat->col = col_size;
    new_mat->row = row_size;
    new_mat->data = (char***)malloc(sizeof(char**)*row_size);
    for(int i=0;i<row_size;i++){
        new_mat->data[i] = (char**)malloc(sizeof(char*)*col_size);
        for(int j=0;j<col_size;j++){
            new_mat->data[i][j] = (char*)calloc(MAX_CHAR,sizeof(char));
        }
    }
    return new_mat;
}

mat
mat_readcsv(const char *_file){
    int* length = _getLengthCSV(_file);                     // รับจำนวน row และ col ของไฟล์

    mat new_mat = mat_create(length[0], length[1]);

    FILE *f;
    char row[MAX_CHAR*100];
    char* token;
    int i = 0;
    f = fopen(_file, "r");
    if(f == NULL){
        printf("ไม่สามารถเปิดไฟล์ได้: %s\n", _file);
        return NULL;
    }
    while(fgets(row, MAX_CHAR*100, f)){
        int rowlen = strlen(row);
        if(row[rowlen-1] == '\n'){
            row[rowlen-1] = '\0';
        }
        token = strtok(row, ",");
        int j = 0;
        while(token != NULL){
            if(strcmp(token,"") == 0){
                strcpy(token,"NULL");
            }
            strcpy(new_mat->data[i][j], token);
            j++;
            token = strtok(NULL, ",");
        }
        i++;
    }
    fclose(f);
    return new_mat;
}

void
mat_erase(mat Mat){
    for(int i=0;i<Mat->row;i++){
        for(int j=0;j<Mat->col;j++){
            free(Mat->data[i][j]);
        }
        free(Mat->data[i]);
    }
    free(Mat->data);
    free(Mat);
}

mat
mat_transpose(mat Mat){
    mat new_mat = mat_create(Mat->col, Mat->row);
    for(int i=0;i<Mat->row;i++){
        for(int j=0;j<Mat->col;j++){
            strcpy(new_mat->data[j][i],Mat->data[i][j]);
        }
    }
    mat_erase(Mat);
    Mat = new_mat;
    return new_mat;
}

char*
mat_get(const mat Mat,const int row,const int col){
    return Mat->data[row][col];
}

void
mat_print(const mat Mat){
    for(int i=0;i<Mat->row;i++){
        for(int j=0;j<Mat->col;j++){
            printf("%s\t",Mat->data[i][j]);
        }
        printf("\n");
    }
    printf("[%d rows x %d columns]\n", Mat->row, Mat->col);
}

void 
mat_sortrow(mat Mat, const int bycol, int (*cmpr)(const char*, const char*)){
    assert(bycol < Mat->col);
    _mat_mergesort(Mat->data, 0, Mat->row-1, bycol, cmpr);
}

void
mat_cpyrow(mat Mat1, const int row1, const mat Mat2, const int row2){
    assert(Mat1->col == Mat2->col);
    for(int i=0;i<Mat1->col;i++){
        strcpy(Mat1->data[row1][i], Mat2->data[row2][i]); 
    }
}

mat
mat_getrows(const mat Mat, const int start, const int end){
    assert(end >= start);
    assert(end < Mat->row);
    mat new_mat = mat_create(end-start, Mat->col);
    for(int i=0;i<new_mat->row;i++){
        mat_cpyrow(new_mat, i, Mat, i+start);
    }
    return new_mat;
}

void
mat_delrow(mat Mat,const int row){
    for(int i=row;i<Mat->row-1;i++){
        for(int j=0;j<Mat->col;j++){
            strcpy(Mat->data[i][j], Mat->data[i+1][j]);
        }
    }
    for(int j=0;j<Mat->col;j++){
        free(Mat->data[Mat->row-1][j]);
    }
    free(Mat->data[Mat->row-1]);
    Mat->row -= 1;
}

void
mat_catrow(mat Mat1, const mat Mat2){
    assert(Mat1->col == Mat2->col);
    int save = Mat1->row;
    Mat1->row += Mat2->row;
    Mat1->data = (char***)realloc(Mat1->data, Mat1->row*sizeof(char**));
    for(int i=save,j=0;i<Mat1->row;i++,j++){
        Mat1->data[i] = (char**)malloc(Mat1->col*sizeof(char*));
        for(int j=0;j<Mat1->col;j++){
            Mat1->data[i][j] = (char*)malloc(MAX_CHAR*sizeof(char));
        }
        mat_cpyrow(Mat1,i,Mat2,j);
    }
}

mat
mat_siftrow(const mat Mat, int (*check)(char**)){
    mat new_mat = mat_create(0, Mat->col);
    for(int i=0;i<Mat->row;i++){
        if(check(Mat->data[i])){
            mat_catrow(new_mat, mat_getrow(Mat, i));
        }
    }
    return new_mat;
}

mat
mat_getrow(const mat Mat, const int row){
    mat new_mat = mat_create(1, Mat->col);
    mat_cpyrow(new_mat, 0, Mat, row);
    return new_mat;
}

size_t
mat_lenrow(const mat _mat){
    return _mat->row;
}

size_t
mat_lencol(const mat _mat){
    return _mat->col;
}

/**
 * defined function
*/
int* _getLengthCSV(const char* _file){
    FILE *f;
    char buffer[MAX_CHAR*100];
    char* token;
    f = fopen(_file, "r");
    if(f == NULL){
        printf("ไม่สามารถเปิดไฟล์ได้: %s\n", _file);
        return NULL;
    }
    size_t rows=0, columns=0;
    while(fgets(buffer, MAX_CHAR*100, f)){
        rows++;
        token = strtok(buffer, ",");
        size_t temp = 1;
        while(token != NULL){
            token = strtok(NULL, ",");
            temp++;
        }
        columns = (columns > temp ? columns : temp);
    }

    int *length = (int*)malloc(sizeof(int)*2);
    length[0] = rows;
    length[1] = columns;
    fclose(f);
    return length;
}