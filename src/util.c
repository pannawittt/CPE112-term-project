#include "util.h"

int greater(const util_t _first, const util_t _second){
    return _first > _second;
}

int greater_equal(const util_t _first, const util_t _second){
    return _first >= _second;
}

int less(const util_t _first, const util_t _second){
    return _first < _second;
}

int less_equal(const util_t _first, const util_t _second){
    return _first <= _second;
}

int mmod(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}

int mod(int a){
    int r = a % MOD;
    return r < 0 ? r + MOD : r;
}

int minute(const char* string){
    return ((string[0]-'0')*10 + (string[1]-'0'))*60 + (string[2]-'0')*10 + (string[3]-'0');
}