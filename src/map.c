#include "map.h"

map map_create(int (*cmpr_func)(const pair_t1, const pair_t1)){
    map new_map;
    new_map.root = NULL;
    new_map.size = 0;
    new_map.cmpr = cmpr_func;
    return new_map;
}

map_node *_map_create_node(pair _value){
    map_node *new_node = (map_node *)malloc(sizeof(map_node));
    new_node->color = _red;
    new_node->child[0] = new_node->child[1] = NULL;
    new_node->value.second = _value.second;
    new_node->value.first = _value.first;
    return new_node;
}

pair_t2 *map_get(map *_map, pair_t1 _key){
    map_node *_iter = _map->root;
    if( _map->cmpr(_iter->value.first, _key) == 0 ){
        return &(_iter->value.second);
    }
    while(_iter != NULL){
        if( _map->cmpr(_iter->value.first, _key) ){
            _iter = _iter->child[0];
        }else{
            _iter = _iter->child[1];
        }
    }
    return _map_insert_node(_map, pair_make(_key, 0));
}

pair_t2 *_map_insert_node(map *_map, pair _value){
    map_node *stk[5], *ptr, *new_node, *x, *y;
    int dir[5], ht = 0, index;

    ptr = _map->root;

    if(!_map->root){
        _map->root = _map_create_node(_value);
        return &(_map->root->value.second);
    }

    stk[mod(ht)] = _map->root;
    dir[mod(ht++)] = 0;
    while (ptr != NULL){
        // 0: left, 1: right
        index = _map->cmpr(ptr->value.first, _value.first) > 0 ? 1 : 0;
        stk[mod(ht)] = ptr;
        ptr = ptr->child[index];
        dir[mod(ht++)] = index;
    }
    stk[mod(ht-1)]->child[index] = new_node = _map_create_node(_value);
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
    return &(new_node->value.second);
}

#undef MOD