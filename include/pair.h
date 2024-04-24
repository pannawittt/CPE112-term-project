#ifndef _PAIR_H_
#define _PAIR_H_

#ifndef pair_t
#define pair_t int
#endif // pair_t

typedef struct{
    pair_t first;
    pair_t second;
}pair;

pair pair_make(pair_t first, pair_t second);

#endif // pair.h