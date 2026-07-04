#ifndef GENERATEGRAPH_H
#define GENERATEGRAPH_H

#include "general.h"

#include "Base/adjacentListGraph.h"

// Questão A: Planaridade
typedef struct {
    bool isPlanar;
    char reason[256]; // Ex: "Subgrafo K5 encontrado..." ou "Passou nos testes"
} ResultPlanarity;

// Questão B: Pontos de Articulação
typedef struct {
    bool hasArticulation;
    int count;
    int points[10]; // Como V max é 10, no máximo teremos 10 pontos
} ResultArticulation;

// Questão C: Euleriano
typedef struct {
    int type; // 0 = Nenhum, 1 = Caminho Euleriano, 2 = Ciclo Euleriano
    int pathLength;
    int path[100]; // Uma caminhada terá no máximo V + E passos
} ResultEuler;

// O pacote completo de 1 Grafo
typedef struct {
    int numVertices;
    int matrix[10][10]; // Representação para o Python desenhar
    ResultPlanarity planar;
    ResultArticulation articulation;
    ResultEuler euler;
} GraphExperiment;

AdjacentGraph_list* generateRandomConnectedGraph_list(int numVertices, bool isDense);
void saveResultsToJSON(GraphExperiment experiments[3], const char* filename);

#endif