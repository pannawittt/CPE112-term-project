#include "pair.h"

pair pair_make(pair_t1 _first, pair_t2 _second){
    pair new_pair;
    new_pair.first = _first;
    new_pair.second = _second;
    return new_pair;
}