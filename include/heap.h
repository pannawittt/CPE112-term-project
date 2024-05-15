#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct heap *heap;

#include <stddef.h>

heap heap_create(size_t _sizeOfElement, int (*_cmprFunc)(const void*, const void*));
void heap_push(heap _heap, void* _value);
int heap_empty(const heap _heap);
size_t heap_size(const heap _heap);
void heapify(heap _heap, int _index);
void heap_pop(heap _heap);
void* heap_top(const heap _heap);
void* heap_trav(const heap _heap);

#endif
