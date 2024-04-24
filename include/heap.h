#ifndef _HEAP_H_
#define _HEAP_H_

#include "vector.h"
#include "util.h"

#ifndef heap_t
#define heap_t int
#endif

typedef struct{
    heap_t *array;
    int size;
    int capacity;
}heap_container;

typedef struct{
    heap_container vect;
    int (*cmpr)(const heap_t, const heap_t);
}heap;

heap heap_create(int (*cmpr_func)(const heap_t, const heap_t));

void heap_push (heap *_heap, heap_t val);
int heap_empty (const heap *_heap);
void heapify (heap *_heap, int idx);
void heap_pop (heap *_heap);
heap_t heap_top (const heap *_heap);

#endif
