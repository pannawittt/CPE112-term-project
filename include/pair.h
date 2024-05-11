#ifndef _PAIR_H_
#define _PAIR_H_

#include "stddef.h"

typedef struct pair *pair;

pair pair_create(size_t _sizeOfFirst, size_t _sizeOfSecond);
void pair_set(pair _pair, void* _first, void* _second);
pair pair_make(void* _first, void* _second, size_t _sizeOfFirst, size_t _sizeOfSecond);
void* pair_first(pair _pair);
void* pair_second(pair _pair);

#endif // pair.h