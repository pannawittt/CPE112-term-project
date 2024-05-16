#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stddef.h>

/**
 * Vector ( dynamic array )
 * data structure ที่คล้ายกับ array
 * แต่ใช้พื้นที่แบบประหยัดเพราะว่า
 * ความจุใน array ปรับเองตามขนาดของ array
*/
typedef struct vector *vector;

/**
 * macro ขนาดของ struct vector
 * C23 standard
*/
#define _VECTOR_SIZE_ 32

vector vector_create(size_t _sizeOfElement);
void vector_push(vector _vector, void* _element);
void vector_pop(vector _vector);
void vector_swap(vector _vector, size_t _first, size_t _second);
void vector_reverse(vector _vector);
size_t vector_size(const vector _vector);
int vector_empty(const vector _vector);
void* vector_at(const vector _vector, const int _index);
void** vector_get(const vector _vector, const int _index);
void** vector_begin(const vector _vector);
void** vector_end(const vector _vector);
void** vector_find(const vector _vector, void* _value, int (*cmpr)(const void*, const void*));
void* vector_trav(const vector _vector);

#endif // vector.h