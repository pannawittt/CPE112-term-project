#include "pair.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct pair{
    void* first;
    void* second;
    size_t firstSize;
    size_t secondSize;
};

pair
pair_create(size_t _sizeOfFirst, size_t _sizeOfSecond){
    pair new_pair = (pair)malloc(sizeof(struct pair));
    new_pair->first = NULL;
    new_pair->second = NULL;
    new_pair->firstSize = _sizeOfFirst;
    new_pair->secondSize = _sizeOfSecond;
    return new_pair;
}

pair
pair_make(void* _first, void* _second, size_t _sizeOfFirst, size_t _sizeOfSecond){
    pair new_pair = (pair)malloc(sizeof(struct pair));
    new_pair->first = (void*)malloc(sizeof(_sizeOfFirst));
    new_pair->second = (void*)malloc(sizeof(_sizeOfSecond));
    memcpy(new_pair->first, _first, _sizeOfFirst);
    memcpy(new_pair->second, _second, _sizeOfSecond);
    new_pair->firstSize = _sizeOfFirst;
    new_pair->secondSize = _sizeOfSecond;
    return new_pair;
}

void
pair_set(pair _pair, void* _first, void* _second){
    if(_first){
        memcpy(_pair->first, _first, _pair->firstSize);
    }
    if(_second){
        memcpy(_pair->second, _second, _pair->secondSize);
    }
}

void*
pair_first(pair _pair){
    return _pair->first;
}

void*
pair_second(pair _pair){
    return _pair->second;
}