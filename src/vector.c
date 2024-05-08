#include "vector.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

/**
 * struct vector
 * ใช้ void** ( array ของ void* ) เพื่อที่จะให้ vector ลองรับ dynamic type
 * แต่ต้อง cast type เองเวลาใช้
 * เก็บขนาดและความจุของ vector เป็น int
 * SOE คือขนาดของ element ของ vector
*/
struct vector{
    void **array;
    size_t size;
    size_t capacity;
    size_t SOE;
};

/**
 * private function
 * update_capacity() ใช้อัพเดตขนาดของ array
 * ลายละเอียดอยู่ข้างล่างไฟล์นี้
*/
static void update_capacity(vector _vector, size_t _newCapacity);

vector 
vector_create(size_t _sizeOfElement){
    vector new_vector = (vector)malloc(sizeof(struct vector));
    new_vector->size = 0;
    new_vector->array = NULL;
    new_vector->capacity = 0;
    new_vector->SOE = _sizeOfElement;
    update_capacity(new_vector, 8);
    return new_vector;
}

void 
vector_push(vector _vector, void* _element){
    if(_vector->size >= _vector->capacity){
        update_capacity(_vector, _vector->capacity<<1);
    }
    memcpy(_vector->array[_vector->size++], _element, _vector->SOE);
}

void 
vector_pop(vector _vector){
    if(_vector->size > 0){
        _vector->size--;
    }
}

size_t
vector_size(const vector _vector){
    return _vector->size;
}

int 
vector_empty(const vector _vector){
    return _vector->size <= 0;
}

void*
vector_at(const vector _vector, int _index){
    if(_index < _vector->size){
        return _vector->array[_index];
    }
    return *vector_end(_vector);
}

void**
vector_get(const vector _vector, int _index){
    if(_index < _vector->size){
        return &_vector->array[_index];
    }
    return vector_end(_vector);
}

void**
vector_begin(const vector _vector){
    return &_vector->array[0];
}

void** 
vector_end(const vector _vector){
    return &_vector->array[_vector->size];
}

void**
vector_find(const vector _vector, void* _value){
    for(int i=0;i<_vector->size;i++){
        if(!memcmp(_vector->array[i], _value, _vector->SOE)){
            return vector_get(_vector, i);
        }
    }
    return vector_end(_vector);
}

/**
 * ฟังก์ชั่นสำหรับใช้ในไฟล์นี้เท่านั้น
*/
static void
update_capacity(vector _vector, size_t _newCapacity){
    size_t old = _vector->capacity;
    _vector->capacity = _newCapacity;
    _vector->array = (void**)realloc(_vector->array, sizeof(void*)*(_vector->capacity));
    for(;old<_newCapacity;old++){
        _vector->array[old] = (void*)malloc(_vector->SOE);
    }
}