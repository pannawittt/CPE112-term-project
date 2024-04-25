#ifndef _MAP_H_
#define _MAP_H_

#ifdef MOD
#undef MOD
#endif // MOD

#define MOD 5
#include "util.h"
#include "pair.h"

#define _red 1
#define _black 0

typedef struct map_node{
    pair value;
    struct map_node *child[2];
    int color;
}map_node;

typedef struct{
    map_node *root;
    int size;
    int (*cmpr)(const pair_t1, const pair_t1);
}map;

map map_create(int (*cmpr_func)(const pair_t1, const pair_t1));
pair_t2 *map_get(map *_map, pair_t1 key);
map_node *_map_create_node(pair _value);
pair_t2 *_map_insert_node(map *_map, pair _value);

#endif // map.h