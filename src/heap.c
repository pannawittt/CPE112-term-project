#include "heap.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

/** library เพิ่มเติม
 * vector.h ใช้เป็น data structure ในการเก็บค่าใน heap
*/
#include "vector.h"

/** struct heap ( priority queue )
 * data structure สำหรับใช้เก็บค่าโดยค่าใน index แรกจะมีค่าสุดตามฟังก์ชั่น cmpr()
 * container : vector สำหรับใช้เก็บค่า
 * cmpr : function สำหรับเปลียบเทียบค่าของ heap
 * elementSize : ขนาดของตัวแปรใน heap
*/
struct heap{
    vector container;
    int (*cmpr)(const void*, const void*);
    size_t elementSize;
};

/** private function
 * swap() ใช้สลับค่าสองค่า
 * ลายละเอียดอยู่ข้างล่างไฟล์นี้
*/
void swap(void* _first, void* _second, size_t _sizeOfElement);

heap
heap_create(size_t _sizeOfElement, int (*_cmprFunc)(const void*, const void*)){
    heap new_heap = (heap)malloc(sizeof(struct heap));
    new_heap->container = vector_create(_sizeOfElement);
    new_heap->cmpr = _cmprFunc;
    new_heap->elementSize = _sizeOfElement;
    return new_heap;
}

void
heap_push (heap _heap, void* _value){
    vector_push(_heap->container, _value);
    size_t idx = vector_size(_heap->container)-1;
    while(idx > 0 && _heap->cmpr(vector_at(_heap->container, (idx-1)/2), vector_at(_heap->container, idx))){
        vector_swap(_heap->container, (idx-1)/2, idx);
        idx = (idx-1)/2;
    }
}

size_t
heap_size(const heap _heap){
    return vector_size(_heap->container);
}

int 
heap_empty (const heap _heap){
    return vector_empty(_heap->container);
}

void
heapify (heap _heap, int _idx){
    int left = _idx*2 + 1;
    int right = _idx*2 + 2;
    int largest = _idx;
    if(left < vector_size(_heap->container) && _heap->cmpr(vector_at(_heap->container, largest), vector_at(_heap->container, left)) ){
        largest = left;
    }
    if(right < vector_size(_heap->container) && _heap->cmpr(vector_at(_heap->container, largest), vector_at(_heap->container, right)) ){
        largest = right;
    }
    if(largest != _idx){
        swap(vector_at(_heap->container, _idx), vector_at(_heap->container, largest), _heap->elementSize);
        heapify(_heap, largest);
    }
}

void
heap_pop (heap _heap){
    if(!heap_empty(_heap)){
        vector_swap(_heap->container, 0, vector_size(_heap->container)-1);
        vector_pop(_heap->container);
        heapify(_heap, 0);
    }
}

void*
heap_top (const heap _heap){
    if(!heap_empty(_heap)){
        return vector_at(_heap->container, 0);
    }
}

/**
 * ฟังก์ชั่นสำหรับใช้ในไฟล์นี้เท่านั้น
*/
void 
swap(void* _first, void* _second, size_t _sizeOfElement){
    void *temp = malloc(_sizeOfElement);
    memcpy(temp, _first, _sizeOfElement);
    memcpy(_second, _first, _sizeOfElement);
    memcpy(_first, temp, _sizeOfElement);
    free(temp);
}