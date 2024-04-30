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

vector vector_create();
void vector_push(vector _vector, void* _element);
void vector_pop(vector _vector);
size_t vector_size(const vector _vector);
int vector_empty(const vector _vector);
void* vector_at(const vector _vector, const int _index);
void** vector_get(const vector _vector, const int _index);
void** vector_begin(const vector _vector);
void** vector_end(const vector _vector);

#endif // vector.h