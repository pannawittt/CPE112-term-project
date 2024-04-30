#include "graph.h"

graph* graph_create(const int node){
    graph *new_graph = (graph*)malloc(sizeof(graph));
    new_graph->nodeSize = node;
    new_graph->adjMatrix = (path**)malloc(sizeof(path*)*node);
    for(int i=0;i<node;i++){
        new_graph->adjMatrix[i] = (path*)malloc(sizeof(path)*node);
    }
    return new_graph;
}

void graph_addedge(graph* Graph, const int u, const int v, const int w, const int bus){
    Graph->adjMatrix[u][v].bus = bus;
    Graph->adjMatrix[u][v].weight = w;
}

