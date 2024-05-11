#include "graph.h"

/**
 * นำเข้า library
*/
#include "vector.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/**
 * private macro:
 *  size of struct path
*/
#define _PATH_SIZE_ 16

/**
 * private struct & function
*/
static path path_create(int _weight, char *_bus, int _destination);

/**
 * struct graph & path
*/
struct graph{
    int nodeSize;
    vector* adjList;
};

struct path{
    int weight;
    int destination;
    char *bus;
};

graph
graph_create(const int _nodeSize){
    graph new_graph = (graph)malloc(sizeof(struct graph));
    new_graph->nodeSize = _nodeSize;
    new_graph->adjList = (vector*)malloc(sizeof(vector) * _nodeSize);
    for(int i=0;i<new_graph->nodeSize;i++){
        new_graph->adjList[i] = vector_create(sizeof(struct path));
    }
    return new_graph;
}

void
graph_addedge(graph _graph, const int _sourceVertex, const int _destinaionVertex, int _weight, char *_busNo){
    path new_path = path_create(_weight, _busNo, _destinaionVertex);
    vector_push(_graph->adjList[_sourceVertex], new_path);
}

vector
graph_get(const graph _graph, const int _vertex){
    return _graph->adjList[_vertex];
}

/**
 * private definition
*/
static path
path_create(int _weight, char *_bus, const int _destination){
    path new_path = (path)malloc(sizeof(struct path));
    new_path->weight = _weight;
    new_path->destination = _destination;
    new_path->bus = (char)malloc(sizeof(char)*250);
    memcpy(new_path->bus, _bus, sizeof(char)*250);
    return new_path;
}
