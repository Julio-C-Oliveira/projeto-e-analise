#ifndef BFS
#define BFS

#include "../Base/adjacentListGraph.h"
#include "../Base/adjacentMatrizGraph.h"

#include "defines.h"

typedef struct {
    char color;
    int distance;
    int predecessor;
} BFS_AuxiliaryAttributes;

void bfs_list(AdjacentGraph_list* graph, int startVertex);
void bfs_matriz(AdjacentGraph_matriz* graph, int startVertex);

int bfsCalculateStepSize_list(AdjacentGraph_list* graph, int startVertex, int endVertex);
int bfsCalculateStepSize_matriz(AdjacentGraph_matriz* graph, int startVertex, int endVertex);

#endif