#ifndef _PAIR_H_
#define _PAIR_H_

#ifndef pair_t1
#define pair_t1 char*
#endif // pair_t1

#ifndef pair_t2
#define pair_t2 int
#endif // pair_t2

#include "util.h"

typedef struct{
    pair_t1 first;
    pair_t2 second;
}pair;

pair pair_create(pair_t1 first, pair_t2 second);

#endif // pair.h