#include "adjacentMatrizGraph.h"

AdjacentGraph_matriz* createAdjacentGraph_matriz(int numberOfVertices, bool driven) {
    AdjacentGraph_matriz* graph = (AdjacentGraph_matriz*)malloc(sizeof(AdjacentGraph_matriz));
    graph->numberOfVertices = numberOfVertices;
    graph->driven = driven;

    graph->adjacentMatriz = (int**)malloc(numberOfVertices*sizeof(int*));

    for (int i = 0; i < numberOfVertices; i++)
        graph->adjacentMatriz[i] = (int*)calloc(numberOfVertices, sizeof(int));

    return graph;
}

void addEdge_matriz(AdjacentGraph_matriz* graph, int origin, int destination, int weight) {
    graph->adjacentMatriz[origin][destination] = weight;

    if (!graph->driven)
        graph->adjacentMatriz[destination][origin] = weight;
}

void displayGraph_matriz(AdjacentGraph_matriz* graph) {
    for (int i = 0; i < graph->numberOfVertices; i++) {
        for (int j = 0; j < graph->numberOfVertices; j++)
            printf("%2d ", graph->adjacentMatriz[i][j]);
        printf("\n");
    }
}

void freeGraph_matriz(AdjacentGraph_matriz* graph) {
    for (int i = 0; i < graph->numberOfVertices; i++)
        free(graph->adjacentMatriz[i]);
    free(graph->adjacentMatriz);
    free(graph);
}

int getNumberOfVertices_matriz(AdjacentGraph_matriz* graph) {
    return graph->numberOfVertices;
}