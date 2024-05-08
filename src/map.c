#include "map.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define _red 1
#define _black 0

typedef struct map_node{
    void *key;
    void *value;
    struct map_node *child[2];
    int color;
}map_node;

struct map{
    map_node *root;
    int size;
    int (*cmpr)(const void*, const void*);
};

int mod(int value);
map_node* _map_create_node(void *_key, void *_value);
void** _map_insert_node(map _map, void *_key, void *_value);

map
map_create(int (*_cmprFunc)(const void*, const void*), size_t _sizeOfKey, size_t _sizeOfValue){
    map new_map = (map)malloc(sizeof(struct map));
    new_map->root = NULL;
    new_map->size = 0;
    new_map->cmpr = _cmprFunc;
    return new_map;
}

void**
map_get(map _map, void* _key){
    map_node *iter = _map->root;
    while(iter != NULL){
        if( _map->cmpr(iter->key, _key) == 0 ){
            return &(iter->value);
        }else if(_map->cmpr(iter->key, _key) > 0){
            iter = iter->child[1];
        }else{
            iter = iter->child[0];
        }
    }
    _map->size++;
    return _map_insert_node(_map, _key, NULL);
}

void*
map_at(map _map, void* _key){
    map_node *iter = _map->root;
    while(iter != NULL){
        if( _map->cmpr(iter->key, _key) == 0 ){
            return iter->value;
        }else if(_map->cmpr(iter->key, _key) > 0){
            iter = iter->child[1];
        }else{
            iter = iter->child[0];
        }
    }
    _map->size++;
    return *_map_insert_node(_map, _key, NULL);
}

void
map_set(map _map, void* _key, void* _value){
    map_node *iter = _map->root;
    while(iter != NULL){
        if( _map->cmpr(iter->key, _key) == 0 ){
            iter->value = _value;
            return;
        }else if(_map->cmpr(iter->key, _key) > 0){
            iter = iter->child[1];
        }else{
            iter = iter->child[0];
        }
    }
    _map->size++;
    _map_insert_node(_map, _key, _value);
}

void
map_erase(map _map, void *key){
    map_node *stk[5], *ptr, *x, *y;
    map_node *p, *q, *r;
    int dir[5], ht = 0, diff, i;
    int color;
    
    if (_map->size <= 0) {
        return;
    }
    _map->size--;
    
    ptr = _map->root;
    while (ptr != NULL) {
        if (_map->cmpr(key, ptr->key) == 0){
            break;
        }
        diff = _map->cmpr(key, ptr->key) > 0 ? 1 : 0;
        stk[mod(ht)] = ptr;
        dir[mod(ht++)] = diff;
        ptr = ptr->child[diff];
    }

    if (ptr->child[1] == NULL) {
        if ((ptr == _map->root) && (ptr->child[0] == NULL)) {
            free(ptr);
            _map->root = NULL;
        } else if (ptr == _map->root) {
            _map->root = ptr->child[0];
            free(ptr);
        } else {
            stk[mod(ht - 1)]->child[dir[mod(ht - 1)]] = ptr->child[0];
        }
    }else {
        x = ptr->child[1];
        if (x->child[0] == NULL) {
        x->child[0] = ptr->child[0];
        color = x->color;
        x->color = ptr->color;
        ptr->color = color;
        if (ptr == _map->root) {
            _map->root = x;
        } else {
            stk[mod(ht - 1)]->child[dir[mod(ht - 1)]] = x;
        }
        dir[mod(ht)] = 1;
        stk[mod(ht++)] = x;
        }else {
            i = ht++;
            while (1) {
                dir[mod(ht)] = 0;
                stk[mod(ht++)] = x;
                y = x->child[0];
                if (!y->child[0])
                break;
                x = y;
            }

            dir[mod(i)] = 1;
            stk[mod(i)] = y;
            if (i > 0){
                stk[mod(i - 1)]->child[dir[mod(i - 1)]] = y;
            }
            y->child[0] = ptr->child[0];
            x->child[0] = y->child[1];
            y->child[1] = ptr->child[1];

            if (ptr == _map->root) {
                _map->root = y;
            }
            color = y->color;
            y->color = ptr->color;
            ptr->color = color;
        }
    }
    if (ht < 1){
        return;
    }
    if (ptr->color == _black) {
        while(1) {
            p = stk[mod(ht - 1)]->child[dir[mod(ht - 1)]];
            if (p && p->color == _red) {
                p->color = _black;
                break;
            }
            if (ht < 2){
                break;
            }
            if(dir[mod(ht - 2)] == 0) {
                r = stk[mod(ht - 1)]->child[1];
                if(!r){
                    break;
                } 
                if (r->color == _red) {
                    stk[mod(ht - 1)]->color = _red;
                    r->color = _black;
                    stk[mod(ht - 1)]->child[1] = r->child[0];
                    r->child[0] = stk[mod(ht - 1)];
                    if(stk[mod(ht - 1)] == _map->root) {
                        _map->root = r;
                    }else {
                        stk[mod(ht - 2)]->child[dir[mod(ht - 2)]] = r;
                    }
                    dir[mod(ht)] = 0;
                    stk[mod(ht)] = stk[mod(ht - 1)];
                    stk[mod(ht - 1)] = r;
                    ht++;
                    r = stk[mod(ht - 1)]->child[1];
                }

                if ((!r->child[0] || r->child[0]->color == _black) && (!r->child[1] || r->child[1]->color == _black)) {
                    r->color = _red;
                }else {
                    if (!r->child[1] || r->child[1]->color == _black) {
                        q = r->child[0];
                        r->color = _red;
                        q->color = _black;
                        r->child[0] = q->child[1];
                        q->child[1] = r;
                        r = stk[mod(ht - 1)]->child[1] = q;
                    }
                    r->color = stk[mod(ht - 1)]->color;
                    stk[mod(ht - 1)]->color = _black;
                    r->child[1]->color = _black;
                    stk[mod(ht - 1)]->child[1] = r->child[0];
                    r->child[0] = stk[mod(ht - 1)];
                    if (stk[mod(ht - 1)] == _map->root) {
                        _map->root = r;
                    } else {
                        stk[mod(ht - 2)]->child[dir[mod(ht - 2)]] = r;
                    }
                    break;
                }
            } else {
                r = stk[mod(ht - 1)]->child[0];
                if(!r) {
                    break;
                }
                if (r->color == _red) {
                    stk[mod(ht - 1)]->color = _red;
                    r->color = _black;
                    stk[mod(ht - 1)]->child[0] = r->child[1];
                    r->child[1] = stk[mod(ht - 1)];
                    if (stk[mod(ht - 1)] == _map->root) {
                        _map->root = r;
                    } else {
                        stk[mod(ht - 2)]->child[dir[mod(ht - 2)]] = r;
                    }
                    dir[mod(ht)] = 1;
                    stk[mod(ht)] = stk[mod(ht - 1)];
                    stk[mod(ht - 1)] = r;
                    ht++;

                    r = stk[mod(ht - 1)]->child[0];
                }
                if ((!r->child[0] || r->child[0]->color == _black) && (!r->child[1] || r->child[1]->color == _black)) {
                    r->color = _red;
                } else {
                    if (!r->child[0] || r->child[0]->color == _black) {
                        q = r->child[1];
                        r->color = _red;
                        q->color = _black;
                        r->child[1] = q->child[0];
                        q->child[0] = r;
                        r = stk[mod(ht - 1)]->child[0] = q;
                    }
                    r->color = stk[mod(ht - 1)]->color;
                    stk[mod(ht - 1)]->color = _black;
                    r->child[0]->color = _black;
                    stk[mod(ht - 1)]->child[0] = r->child[1];
                    r->child[1] = stk[mod(ht - 1)];
                    if(stk[mod(ht - 1)] == _map->root) {
                        _map->root = r;
                    }else {
                        stk[mod(ht - 2)]->child[dir[mod(ht - 2)]] = r;
                    }
                    break;
                }
            }
            ht--;
        }
    }
}

size_t
map_size(map _map){
    return _map->size;
}

void**
map_find(map _map, void* _key){
    map_node *iter = _map->root;
    while(iter != NULL){
        if( _map->cmpr(iter->key, _key) == 0 ){
            return &(iter->value);
        }else if(_map->cmpr(iter->key, _key) > 0){
            iter = iter->child[1];
        }else{
            iter = iter->child[0];
        }
    }
    return NULL;
}

/**
 * ฟังก์ชั่นใช้ในไฟล์นี้เท่านั้น
*/
int 
mod(int a){
    int r = a % 5;
    return r < 0 ? r + 5 : r;
}

map_node*
_map_create_node(void *_key, void *_value){
    map_node *new_node = (map_node *)malloc(sizeof(map_node));
    new_node->color = _red;
    new_node->child[0] = new_node->child[1] = NULL;
    new_node->key = _key;
    new_node->value = _value;
    return new_node;
}

void**
_map_insert_node(map _map, void *_key, void *_value){
    map_node *stk[5], *ptr, *new_node, *x, *y;
    int dir[5], ht = 0, index;
    ptr = _map->root;

    if(!_map->root){
        _map->root = _map_create_node(_key, _value);
        return &(_map->root->value);
    }

    stk[mod(ht)] = _map->root;
    dir[mod(ht++)] = 0;
    while (ptr != NULL){
        // 0: left, 1: right
        index = _map->cmpr(ptr->key, _key) > 0 ? 1 : 0;
        stk[mod(ht)] = ptr;
        ptr = ptr->child[index];
        dir[mod(ht++)] = index;
    }
    stk[mod(ht-1)]->child[index] = new_node = _map_create_node(_key, _value);
    while((ht >= 3) && (stk[mod(ht-1)]->color == _red)){
        if(dir[mod(ht-2)] == 0){
            y = stk[mod(ht-2)]->child[1];
            if(y != NULL && y->color == _red){
                stk[mod(ht-2)]->color = _red;
                stk[mod(ht-1)]->color = y->color = _black;
                ht -= 2;
            }else{
                if(dir[mod(ht-1)] == 0) {
                    y = stk[mod(ht-1)];
                }else {
                    x = stk[mod(ht-1)];
                    y = x->child[1];
                    x->child[1] = y->child[0];
                    y->child[0] = x;
                    stk[mod(ht-2)]->child[0] = y;
                }
                x = stk[mod(ht-2)];
                x->color = _red;
                y->color = _black;
                x->child[0] = y->child[1];
                y->child[1] = x;
                if(x == _map->root){
                    _map->root = y;
                }else {
                    stk[mod(ht-3)]->child[dir[mod(ht-3)]] = y;
                }
                break;
            }
        }else {
            y = stk[mod(ht-2)]->child[0];
            if ((y != NULL) && (y->color == _red)) {
                stk[mod(ht-2)]->color = _red;
                stk[mod(ht-1)]->color = y->color = _black;
                ht -= 2;
            }else {
                if (dir[mod(ht-1)] == 1){
                    y = stk[mod(ht-1)];
                }else {
                    x = stk[mod(ht-1)];
                    y = x->child[0];
                    x->child[0] = y->child[1];
                    y->child[1] = x;
                    stk[mod(ht-2)]->child[1] = y;
                }
                x = stk[mod(ht-2)];
                y->color = _black;
                x->color = _red;
                x->child[1] = y->child[0];
                y->child[0] = x;
                if(x == _map->root){
                    _map->root = y; 
                }else {
                    stk[mod(ht-3)]->child[dir[mod(ht-3)]] = y;
                }
                break;
            }
        }
    }
    _map->root->color = _black;
    return &(new_node->value);
}

#undef _red
#undef _black