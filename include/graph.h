#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "vector.h"

typedef struct graph *graph;
typedef struct path *path;

graph graph_create(const int _nodeSize);
void graph_addedge(graph _graph, const int _sourceVertex, const int _destinaionVertex, int _weight, char *_busNo);
vector graph_get(const graph _graph, const int _vertex);

#endif //graph.h