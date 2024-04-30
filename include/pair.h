#ifndef _PAIR_H_
#define _PAIR_H_

typedef struct pair{
    void* first;
    void* second;
}*pair;

pair pair_create();
pair pair_make(void* _first, void* _second);

#endif // pair.h