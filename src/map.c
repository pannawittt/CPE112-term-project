#include "map.h"

map map_create(int (*cmpr_func)(const map_key_t, const map_key_t)){
    map new_map;
    new_map.root = NULL;
    new_map.size = 0;
    new_map.cmpr = cmpr_func;
    return new_map;
}

map_node *map_create_node(map_key_t _key, map_val_t _val){
    map_node *new_node = (map_node *)malloc(sizeof(map_node));
    new_node->color = _red;
    new_node->left = new_node->right = NULL;
    new_node->val = _val;
    new_node->key = _key;
    return new_node;
}

map_val_t *map_get(map *_map, map_key_t key){
    map_node *_iter = _map->root;
    if( _map->cmpr(_iter->key, key) == 0 ){
        return _iter->val;
    }
    while(_iter != NULL){
        if( _map->cmpr(_iter->key, key) ){
            _iter = _iter->left;
        }else{
            _iter = _iter->right;
        }
    }
    return map_insert_node(key, 0);
}

map_val_t *map_insert_node(map_key_t _key ,map_val_t _val){
    stack node_stk = stack_create();
}

#undef stack_t