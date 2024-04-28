#include "matrix.h"

mat mat_create(int row_size, int col_size){
    mat new_mat;
    new_mat.col = col_size;
    new_mat.row = row_size;
    new_mat.data = (char***)malloc(sizeof(char**)*row_size);
    for(int i=0;i<row_size;i++){
        new_mat.data[i] = (char**)malloc(sizeof(char*)*col_size);
        for(int j=0;j<col_size;j++){
            new_mat.data[i][j] = (char*)malloc(sizeof(char)*MAX_CHAR);
        }
    }
    return new_mat;
}

mat mat_readcsv(mat *Mat, char *file){
    FILE *f;
    char row[MAX_CHAR*100];
    char* token;
    int i = 0;
    f = fopen(file, "r");
    while(i < Mat->row && feof(f) != 1){
        fgets(row, MAX_CHAR*100, f);
        int rowlen = strlen(row);
        if(row[rowlen-1] == '\n'){
            row[rowlen-1] = '\0';
        }
        token = strtok(row, ",");
        int j = 0;
        while(j < Mat->col && token != NULL){
            if(strcmp(token,"") == 0){
                strcpy(token,"NULL");
            }
            strcpy(Mat->data[i][j], token);
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    fclose(f);
}

void mat_erase(mat *Mat){
    for(int i=0;i<Mat->row;i++){
        for(int j=0;j<Mat->col;j++){
            free(Mat->data[i][j]);
        }
        free(Mat->data[i]);
    }
    free(Mat->data);
}

mat mat_transpose(mat *Mat){
    mat new_mat = mat_create(Mat->col, Mat->row);
    for(int i=0;i<Mat->row;i++){
        for(int j=0;j<Mat->col;j++){
            strcpy(new_mat.data[j][i],Mat->data[i][j]);
        }
    }
    mat_erase(Mat);
    *Mat = new_mat;
    return new_mat;
}

char* mat_get(const mat *Mat, int row, int col){
    return Mat->data[row][col];
}

void mat_print(const mat *Mat){
    for(int i=0;i<Mat->row;i++){
        for(int j=0;j<Mat->col;j++){
            printf("%s\t",Mat->data[i][j]);
        }
        printf("\n");
    }
}

void _mat_merge(char ***arr, int l, int m, int r, int cmpind, int (*cmpfunc)(const char*, const char*)){
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

void _mat_mergesort(char ***arr, int l, int r, int cmpind, int (*cmpr)(const char*, const char*)){
    if(l < r){
        int m = l+(r-l)/2;
        _mat_mergesort(arr, l, m, cmpind, cmpr);
        _mat_mergesort(arr, m+1, r, cmpind, cmpr);
        _mat_merge(arr, l, m, r, cmpind, cmpr);
    }
}

void mat_sortrow(mat *Mat, int bycol, int (*cmpr)(const char*, const char*)){
    assert(bycol < Mat->col);
    _mat_mergesort(Mat->data, 0, Mat->row-1, bycol, cmpr);
}

mat mat_getrow(const mat *Mat, int start, int end){
    assert(end >= start);
    assert(end < Mat->row);
    mat new_mat = mat_create(end-start, Mat->col);
    for(int i=0;i<new_mat.row;i++){
        for(int j=0;j<new_mat.col;j++){
            strcpy(new_mat.data[i][j], Mat->data[i+start][j]);
        }
    }
    return new_mat;
}

void mat_delrow(mat *Mat, int row){
    for(int i=row;i<Mat->row-1;i++){
        for(int j=0;j<Mat->col;j++){
            strcpy(Mat->data[i][j], Mat->data[i+1][j]);
        }
    }
    for(int j=0;j<Mat->col;j++){
        free(Mat->data[Mat->row-1][j]);
    }
    free(Mat->data[Mat->row-1]);
}