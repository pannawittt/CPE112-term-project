#include "pair.h"

pair pair_make(pair_t _first, pair_t _second){
    pair new_pair;
    new_pair.first = _first;
    new_pair.second = _second;
    return new_pair;
}