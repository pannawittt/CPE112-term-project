#ifndef _MAP_H_
#define _MAP_H_

#ifdef MOD
#undef MOD
#endif // MOD

#define MOD 5
#include "util.h"

#define _red 1
#define _black 0

#ifndef map_t1
#define map_t1 char*
#endif // map_t1

#ifndef map_t2
#define map_t2 int
#endif // map_t2

#ifndef MAX_CHAR
#define MAX_CHAR 250
#endif // MAX_CHAR

typedef struct map_node{
    map_t1 key;
    map_t2 value;
    struct map_node *child[2];
    int color;
}map_node;

typedef struct{
    map_node *root;
    int size;
    int (*cmpr)(const map_t1, const map_t1);
}map;

map map_create(int (*cmpr_func)(const map_t1, const map_t1));
map_t2 *map_get(map *_map, map_t1 key);
void map_erase(map *_map, map_t1 key);
map_node *_map_create_node(map_t1 _key, map_t2 _value);
map_t2 *_map_insert_node(map *_map, map_t1 _key, map_t2 _value);

#endif // map.h