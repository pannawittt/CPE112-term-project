#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct graph *graph;

graph graph_create(const int _nodeSize);
void graph_addedge(graph _graph, const int _sourceVertex, const int _destinaionVertex, int _weight, char *_busNo);

#endif //graph.h