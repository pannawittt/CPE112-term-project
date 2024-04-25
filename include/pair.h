#ifndef _PAIR_H_
#define _PAIR_H_

#ifndef pair_t1
#define pair_t1 int
#endif // pair_t

#ifndef pair_t2
#define pair_t2 int
#endif // pair_t

typedef struct{
    pair_t1 first;
    pair_t2 second;
}pair;

pair pair_make(pair_t1 first, pair_t2 second);

#endif // pair.h