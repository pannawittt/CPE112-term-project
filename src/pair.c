#include "pair.h"

#include <stdlib.h>
#include <stddef.h>

pair
pair_create(){
    pair new_pair = (pair)malloc(sizeof(struct pair));
    new_pair->first = NULL;
    new_pair->second = NULL;
    return new_pair;
}

pair
pair_make(void* _first, void* _second){
    pair new_pair = (pair)malloc(sizeof(struct pair));
    new_pair->first = _first;
    new_pair->second = _second;
    return new_pair;
}