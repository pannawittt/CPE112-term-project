#include "heap.h"

#define _heapv _heap->vect

heap heap_create(int (*cmpr_func)(const heap_t, const heap_t)){
    heap new_heap;
    new_heap.vect.size = 0;
    new_heap.vect.capacity = 8;
    new_heap.vect.array = (heap_t*)malloc(sizeof(heap_t)*new_heap.vect.capacity);
    new_heap.cmpr = cmpr_func;
    return new_heap;
}

void heap_push (heap *_heap, heap_t _val){
    if(_heapv.size >= _heapv.capacity){
        _heapv.capacity <<= 1;
        _heapv.array = (heap_t*)realloc(_heapv.array, _heapv.capacity*sizeof(heap_t));
    }
    _heapv.array[_heapv.size] = _val;
    int idx = _heapv.size;
    while(idx > 0 && _heap->cmpr(_heapv.array[(idx-1)/2], _heapv.array[idx]) ){
        swap(_heapv.array[(idx-1)/2], _heapv.array[idx]);
        idx = (idx-1)/2;
    }
    _heapv.size++;
}

int heap_empty (const heap *_heap){
    return _heapv.size <= 0;
}

void heapify (heap *_heap, int _idx){
    int left = _idx*2 + 1;
    int right = _idx*2 + 2;
    int largest = _idx;
    if(left < _heapv.size && _heap->cmpr(_heapv.array[largest], _heapv.array[left]) ){
        largest = left;
    }
    if(right < _heapv.size && _heap->cmpr(_heapv.array[largest], _heapv.array[right]) ){
        largest = right;
    }
    if(largest != _idx){
        swap(_heapv.array[_idx], _heapv.array[largest]);
        heapify(_heap, largest);
    }
}

void heap_pop (heap *_heap){
    if(heap_empty(_heap)){
        _heapv.array[0] = _heapv.array[--_heapv.size];
        heapify(_heap, 0);
    }
    fprintf(stderr, "heap : is empty. can't pop.\n" );
}

heap_t heap_top (const heap *_heap){
    if(!heap_empty(_heap)){
        return _heapv.array[0];
    }
    fprintf(stderr, "heap : is empty. can't get top element.\n" );
}

#undef _heapv