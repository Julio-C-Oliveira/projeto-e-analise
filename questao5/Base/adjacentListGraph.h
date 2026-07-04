#ifndef ADJACENTLISTGRAPH
#define ADJACENTLISTGRAPH

#include "../general.h"

// Estrutura para o nó da lista de adjacência.
typedef struct Node_list {
    int destination; // Pra onde essa aresta leva.
    int weight; // Peso da aresta.
    struct Node_list* next; // Leva pra próxima aresta disponivel no vértice.
} Node_list;

// Estrutura do grafo por lista de adjacência.
typedef struct {
    int numberOfVertices;
    bool driven; // Se ele é direcionado ou não.
    Node_list** adjacentList; // Um array onde cada elemento é um nó.
} AdjacentGraph_list;

Node_list* createNode_list(int destination, int weight);
AdjacentGraph_list* createAdjacentGraph_list(int numberOfVertices, bool driven);

void addEdge_list(AdjacentGraph_list* graph, int origin, int destination, int weight);
void displayGraph_list(AdjacentGraph_list* graph);
void freeGraph_list(AdjacentGraph_list* graph);

int getNumberOfVertices_list(AdjacentGraph_list* graph);

AdjacentGraph_list* copyAdjacentGraph_list(AdjacentGraph_list* graph);

void removeEdge_list(AdjacentGraph_list* graph, int origin, int destination);

#endif 