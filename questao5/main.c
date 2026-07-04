#include "general.h"
#include "libraries.h"

#include <stdio.h>
#include <time.h>

void runTest_list(AdjacentGraph_list* graph, int startVertex, int endVertex) {
    displayGraph_list(graph);
    printf("\nNúmero de vértices: %d\n\n", getNumberOfVertices_list(graph));
    dfs_list(graph, startVertex);
    printf("\n");
    bfs_list(graph, startVertex);
    printf("\n");
    printf("De %d para %d são necessários %d passos.\n", startVertex, endVertex, bfsCalculateStepSize_list(graph, startVertex, endVertex));
    printf("\n");
    dfsCycleSearch_list(graph, startVertex);
}

void runTest_matriz(AdjacentGraph_matriz* graph, int startVertex, int endVertex) {
    displayGraph_matriz(graph);
    printf("Número de vértices: %d\n\n", getNumberOfVertices_matriz(graph));
    dfs_matriz(graph, 0);
    printf("\n");
    bfs_matriz(graph, 0);
    printf("\n");
    printf("De %d para %d são necessários %d passos.\n", startVertex, endVertex, bfsCalculateStepSize_matriz(graph, startVertex, endVertex));
    printf("\n");
    dfsCycleSearch_matriz(graph, startVertex);
}

void test_for_samarone(int startVertex, int endVertex) {
    printf("Não Euleriano ====================================================================================== ||||\n");
    printf("Grafo com lista de adjacência: ====================================== ||\n");
    AdjacentGraph_list* adjacentListGraphNaoEuleriano = createAdjacentGraph_list(5, false);

    addEdge_list(adjacentListGraphNaoEuleriano, 2, 1, 1);
    addEdge_list(adjacentListGraphNaoEuleriano, 2, 0, 1);
    addEdge_list(adjacentListGraphNaoEuleriano, 1, 0, 1);
    addEdge_list(adjacentListGraphNaoEuleriano, 1, 3, 1);
    addEdge_list(adjacentListGraphNaoEuleriano, 0, 3, 1);
    addEdge_list(adjacentListGraphNaoEuleriano, 3, 4, 1);

    runTest_list(adjacentListGraphNaoEuleriano, startVertex, endVertex);
    freeGraph_list(adjacentListGraphNaoEuleriano);

    printf("\nGrafo com matriz de adjacência: ====================================== ||\n");
    AdjacentGraph_matriz* adjacentMatrizGraphNaoEuleriano = createAdjacentGraph_matriz(5, false);

    addEdge_matriz(adjacentMatrizGraphNaoEuleriano, 2, 1, 1);
    addEdge_matriz(adjacentMatrizGraphNaoEuleriano, 2, 0, 1);
    addEdge_matriz(adjacentMatrizGraphNaoEuleriano, 1, 0, 1);
    addEdge_matriz(adjacentMatrizGraphNaoEuleriano, 1, 3, 1);
    addEdge_matriz(adjacentMatrizGraphNaoEuleriano, 0, 3, 1);
    addEdge_matriz(adjacentMatrizGraphNaoEuleriano, 3, 4, 1);

    runTest_matriz(adjacentMatrizGraphNaoEuleriano, startVertex, endVertex);
    freeGraph_matriz(adjacentMatrizGraphNaoEuleriano);

    printf("\n\nCiclo Euleriano ====================================================================================== ||||\n");
    printf("Grafo com lista de adjacência: ====================================== ||\n");
    AdjacentGraph_list* adjacentListGraphComCicloEuleriano = createAdjacentGraph_list(5, false);
    
    addEdge_list(adjacentListGraphComCicloEuleriano, 2, 1, 1);
    addEdge_list(adjacentListGraphComCicloEuleriano, 2, 0, 1);
    addEdge_list(adjacentListGraphComCicloEuleriano, 1, 0, 1);
    addEdge_list(adjacentListGraphComCicloEuleriano, 0, 3, 1);
    addEdge_list(adjacentListGraphComCicloEuleriano, 0, 4, 1);
    addEdge_list(adjacentListGraphComCicloEuleriano, 3, 4, 1);

    runTest_list(adjacentListGraphComCicloEuleriano, startVertex, endVertex);
    freeGraph_list(adjacentListGraphComCicloEuleriano);

    printf("\nGrafo com matriz de adjacência: ====================================== ||\n");
    AdjacentGraph_matriz* adjacentMatrizGraphComCicloEuleriano = createAdjacentGraph_matriz(5, false);
    
    addEdge_matriz(adjacentMatrizGraphComCicloEuleriano, 2, 1, 1);
    addEdge_matriz(adjacentMatrizGraphComCicloEuleriano, 2, 0, 1);
    addEdge_matriz(adjacentMatrizGraphComCicloEuleriano, 1, 0, 1);
    addEdge_matriz(adjacentMatrizGraphComCicloEuleriano, 0, 3, 1);
    addEdge_matriz(adjacentMatrizGraphComCicloEuleriano, 0, 4, 1);
    addEdge_matriz(adjacentMatrizGraphComCicloEuleriano, 3, 4, 1);

    runTest_matriz(adjacentMatrizGraphComCicloEuleriano, startVertex, endVertex);
    freeGraph_matriz(adjacentMatrizGraphComCicloEuleriano);


    printf("\n\nCaminho Euleriano ====================================================================================== ||||\n");
    printf("Grafo com lista de adjacência: ====================================== ||\n");
    AdjacentGraph_list* adjacentListGraphComCaminhoEuleriano = createAdjacentGraph_list(5, false);

    addEdge_list(adjacentListGraphComCaminhoEuleriano, 2, 1, 1);
    addEdge_list(adjacentListGraphComCaminhoEuleriano, 2, 0, 1);
    addEdge_list(adjacentListGraphComCaminhoEuleriano, 0, 3, 1);
    addEdge_list(adjacentListGraphComCaminhoEuleriano, 3, 4, 1);

    runTest_list(adjacentListGraphComCaminhoEuleriano, startVertex, endVertex);
    freeGraph_list(adjacentListGraphComCaminhoEuleriano);

    printf("\nGrafo com matriz de adjacência: ====================================== ||\n");
    AdjacentGraph_matriz* adjacentMatrizGraphComCaminhoEuleriano = createAdjacentGraph_matriz(5, false);
    
    addEdge_matriz(adjacentMatrizGraphComCaminhoEuleriano, 2, 1, 1);
    addEdge_matriz(adjacentMatrizGraphComCaminhoEuleriano, 2, 0, 1);
    addEdge_matriz(adjacentMatrizGraphComCaminhoEuleriano, 0, 3, 1);
    addEdge_matriz(adjacentMatrizGraphComCaminhoEuleriano, 3, 4, 1);

    runTest_matriz(adjacentMatrizGraphComCaminhoEuleriano, startVertex, endVertex);
    freeGraph_matriz(adjacentMatrizGraphComCaminhoEuleriano);
}

void test_for_nelson(int numVertices, bool isDense) {
    printf("\n\n==================================================================================\n");
    printf("GERANDO 3 GRAFOS ALEATORIOS E EXPORTANDO PARA JSON\n");
    printf("==================================================================================\n\n");

    // Array que vai guardar os 3 experimentos
    GraphExperiment experiments[3];

    for (int i = 0; i < 3; i++) {
        int currentV = (numVertices >= 5 && numVertices <= 10) ? numVertices : (rand() % 6) + 5;
        
        AdjacentGraph_list* randomGraph = generateRandomConnectedGraph_list(currentV, isDense);
        
        // 1. Preenche dados base na struct
        experiments[i].numVertices = currentV;
        
        // Zera a matriz estática
        for(int u = 0; u < 10; u++) {
            for(int v = 0; v < 10; v++) {
                experiments[i].matrix[u][v] = 0;
            }
        }
        
        // Converte a Lista de Adjacência para a Matriz Estática (Para o Python desenhar)
        for(int v = 0; v < currentV; v++) {
            Node_list* curr = randomGraph->adjacentList[v];
            while(curr != NULL) {
                experiments[i].matrix[v][curr->destination] = curr->weight;
                curr = curr->next;
            }
        }
        
        printf("----------------------------------------\n");
        printf("Processando Grafo Aleatório %d | Vértices: %d\n", i + 1, currentV);
        printf("----------------------------------------\n");
        
        // 2. Executa os algoritmos passando os ponteiros das estruturas de resultado
        checkPlanarity(randomGraph, &experiments[i].planar);
        findArticulationPoints_list(randomGraph, &experiments[i].articulation);
        fleury_list(randomGraph, &experiments[i].euler);

        freeGraph_list(randomGraph);
    }

    // 3. Salva o pacote completo no disco
    saveResultsToJSON(experiments, "resultados_q5.json");
}

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));

    int numVertices = 0; 
    bool isDense = false; 
    
    if (argc >= 3) {
        numVertices = atoi(argv[1]);
        isDense = atoi(argv[2]) != 0;
        if (argc == 4) srand((unsigned int)atoi(argv[3]));
    } else {
        printf("Rodando de modo aleatório...\n");
    }

    test_for_nelson(numVertices, isDense);
    
    return 0;
}