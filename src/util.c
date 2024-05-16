#include "util.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

void**
find(void** _begin, void** _end, const void* _value, size_t _sizeOfElement){
    void** _start = _begin;
    for(;_start != _end; _start++){
        if(!memcmp(*_start, _value, _sizeOfElement)){
            return _start;
        }
    }
    return _end;
}

int 
minute(const char* _string){
    return ((_string[0]-'0')*10 + (_string[1]-'0'))*60 + (_string[2]-'0')*10 + (_string[3]-'0');
}

int
cmp(const void *_p1, const void *_p2, size_t _sizeOfElement){
    const unsigned char *c1 = (const unsigned char*)_p1;
    const unsigned char *c2 = (const unsigned char*)_p2;
    while(*c1 == *c2++){
        if(*c1++ == '\0'){
            return 0;
        }
    }
    return *c1 - *c2;
}

char*
str(char* _string){
    char* new_string = (char*)calloc(250, sizeof(char));
    strcpy(new_string, _string);
    return new_string;
}

char*
toLower(char* s){
    for(char *p=s; *p; p++){
        *p=tolower(*p);
    }
    return s;
}

void*
pint(const int _value){
    int *new_int = (int*)malloc(sizeof(int));
    *new_int = _value;
    return (void*)new_int;
}

void*
pchar(const char _value){
    char *new_char = (char*)malloc(sizeof(char));
    *new_char = _value;
    return (void*)new_char;
}

void*
pfloat(const float _value){
    float *new_float = (float*)malloc(sizeof(float));
    *new_float = _value;
    return (void*)new_float;
}

void*
pstr(const char* _value){
    if(!_value){
        return NULL;
    }
    size_t len = strlen(_value);
    char *new_str = (char*)malloc(sizeof(char)*(len+1));
    strcpy(new_str, _value);
    return (void*)new_str;
}