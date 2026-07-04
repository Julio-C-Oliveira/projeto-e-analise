#ifndef DFS
#define DFS

#include "../Base/adjacentListGraph.h"
#include "../Base/adjacentMatrizGraph.h"

#include "defines.h"

typedef struct {
    char color;
    int startTime;
    int endTime;
    int predecessor;
} DFS_AuxiliaryAttributes;

void dfsVisit_list(AdjacentGraph_list* graph, int vertex, DFS_AuxiliaryAttributes* auxiliaryAttibutes, int* timestamp);
void dfs_list(AdjacentGraph_list* graph, int startVertex);

void dfsVisit_matriz(AdjacentGraph_matriz* graph, int vertex, DFS_AuxiliaryAttributes* auxiliaryAttibutes, int* timestamp);
void dfs_matriz(AdjacentGraph_matriz* graph, int startVertex);

bool dfsVisitCycleSearch_list(AdjacentGraph_list* graph, int vertex, DFS_AuxiliaryAttributes* auxiliaryAttibutes, int* timestamp, int* cycleStart, int* cycleEnd);
void dfsCycleSearch_list(AdjacentGraph_list* graph, int startVertex);

void dfsVisitCycleSearch_matriz(AdjacentGraph_matriz* graph, int vertex, DFS_AuxiliaryAttributes* auxiliaryAttibutes, int* timestamp, int* cycleStart, int* cycleEnd, bool* hasCycle);
void dfsCycleSearch_matriz(AdjacentGraph_matriz* graph, int startVertex);

int dfsGetNumberOfConnectedComponents_list(AdjacentGraph_list* graph, int startVertex);

#endif