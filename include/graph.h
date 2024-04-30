#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "util.h"

typedef struct{
   int weight;
   int bus;
}path;

typedef struct{
    int nodeSize;
    path** adjMatrix;
}graph;

graph* graph_create(const int _nodeSize);
void graph_addedge(graph* _graph, const int _sourceVertex, const int _destinaionVertex, const int _weight, const int _busNo);

#endif //graph.h