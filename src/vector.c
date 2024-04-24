#include "vector.h"

vector vector_create(void){
    vector new_vector;
    new_vector.size = 0;
    new_vector.capacity = 8;
    new_vector.array = (vector_t*)malloc(new_vector.capacity*sizeof(vector_t));
    return new_vector;
}

void vector_push(vector *_vector, vector_t val){
    if(_vector->size >= _vector->capacity){
        _vector->capacity<<=1;
        _vector->array = (vector_t*)realloc(_vector->array,_vector->capacity*sizeof(vector_t));
    }
    _vector->array[_vector->size++] = val;
}

void vector_pop(vector *_vector){
    if(_vector->size > 0){
        _vector->size--;
    }
    fprintf(stderr, "vector : is empty. can't pop.\n");
}

int vector_empty(vector *_vector){
    return _vector->size <= 0;
}

vector_t vector_get(vector *_vector, int index){
    if(index < _vector->size){
        return _vector->array[index];
    }
    fprintf(stderr, "vector : index out of bound.\n");
}
vector_t* vector_begin(vector *_vector){
    return &_vector->array[0];
}