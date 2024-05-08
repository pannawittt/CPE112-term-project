#ifndef _MAP_H_
#define _MAP_H_

typedef struct map *map;

#include<stddef.h>

map map_create(int (*_cmprFunc)(const void*, const void*), size_t _sizeOfKey, size_t _sizeOfValue);
void** map_get(map _map, void* _key);
void map_erase(map _map, void* _key);
void map_set(map _map, void* _key, void* _value);
void* map_at(map _map, void* _key);
size_t map_size(map _map);
void** map_find(map _map, void* _key);

#endif // map.h