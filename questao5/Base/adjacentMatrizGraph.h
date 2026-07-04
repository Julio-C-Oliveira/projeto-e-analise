#ifndef ADJACENTMATRIZGRAPH
#define ADJACENTMATRIZGRAPH

#include "../general.h"

// Estrutura do grafo por matriz de adjacência.
typedef struct {
    int numberOfVertices;
    bool driven;
    int** adjacentMatriz;
} AdjacentGraph_matriz;

AdjacentGraph_matriz* createAdjacentGraph_matriz(int numberOfVertices, bool driven);
void addEdge_matriz(AdjacentGraph_matriz* graph, int origin, int destination, int weight);
void displayGraph_matriz(AdjacentGraph_matriz* graph);
void freeGraph_matriz(AdjacentGraph_matriz* graph);

int getNumberOfVertices_matriz(AdjacentGraph_matriz* graph);

#endif 