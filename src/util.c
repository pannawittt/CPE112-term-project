#include "util.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void**
find(void** _begin, void** _end, const void* _value, size_t _sizeOfElement){
    void** _start = _begin;
    for(;_start != _end; _start++){
        if (memcmp(*_start, _value, _sizeOfElement) == 0){
            return _start;
        }
    }
    return _end;
}

int 
minute(const char* _string){
    return ((_string[0]-'0')*10 + (_string[1]-'0'))*60 + (_string[2]-'0')*10 + (_string[3]-'0');
}

void*
make_int(const int _value){
    int *new_int = (int*)malloc(sizeof(int));
    *new_int = _value;
    return (void*)new_int;
}

void*
make_char(const char _value){
    char *new_char = (char*)malloc(sizeof(char));
    *new_char = _value;
    return (void*)new_char;
}

void*
make_float(const float _value){
    float *new_float = (float*)malloc(sizeof(float));
    *new_float = _value;
    return (void*)new_float;
}