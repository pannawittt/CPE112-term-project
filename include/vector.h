#ifndef _VECTOR_H_
#define _VECTOR_H_

#ifndef vector_t
#define vector_t int
#endif

#include "util.h"

typedef struct{
    vector_t *array;
    int size;
    int capacity;
}vector;

vector vector_create(void);

void vector_push(vector *_vector, vector_t val);
void vector_pop(vector *_vector);
int vector_empty(vector *_vector);
vector_t vector_get(vector *_vector, int index);
vector_t* vector_begin(vector *_vector);

#endif
