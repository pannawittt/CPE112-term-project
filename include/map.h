#ifndef _MAP_H_
#define _MAP_H_

#ifndef map_key_t
#define map_key_t int
#endif //map_key_t

#ifndef map_val_t
#define map_val_t int
#endif //map_val_t

#include "util.h"

#define _red 1
#define _balck 0

typedef struct map_node{
    map_key_t key;
    map_val_t val;
    struct map_node *left;
    struct map_node *right;
    int color;
}map_node;

#define stack_t map_node
#include "stack.h"

typedef struct{
    map_node *root;
    int size;
    int (*cmpr)(const map_key_t, const map_key_t);
}map;

map map_create(int (*cmpr_func)(const map_key_t, const map_key_t));
map_val_t *map_get(map *_map, map_key_t key);
map_node *map_create_node(map_key_t _key ,map_val_t _val);
map_val_t *map_insert_node(map_key_t _key ,map_val_t _val);

#endif // map.h