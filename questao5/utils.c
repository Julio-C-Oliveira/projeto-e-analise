#include "utils.h"

#include <time.h>

AdjacentGraph_list* generateRandomConnectedGraph_list(int numVertices, bool isDense) {
    // Validação da regra: mínimo 5, máximo 10 vértices
    if (numVertices < 5) numVertices = 5;
    if (numVertices > 10) numVertices = 10;

    // Cria o grafo (false = não-orientado)
    AdjacentGraph_list* graph = createAdjacentGraph_list(numVertices, false);

    // Configuração das Probabilidades baseada no código de referência
    double probDense = 0.5; 
    double probSparse = 9.0 / (numVertices * numVertices); 
    double edgeProbability = isDense ? probDense : probSparse;

    // --- PASSO 1: Garantir Conectividade (Caminho Simples) ---
    for (int i = 0; i < numVertices - 1; i++) {
        int weight = (rand() % 30) + 1; // Peso aleatório entre 1 e 30
        addEdge_list(graph, i, i + 1, weight); 
    }

    // --- PASSO 2: Preencher o resto das arestas com base na densidade ---
    for (int i = 0; i < numVertices; i++) {
        // j = i + 2 garante duas coisas:
        // 1. Não cria laços nele mesmo (j != i)
        // 2. Pula a aresta i -> i+1, que já foi criada no PASSO 1.
        for (int j = i + 2; j < numVertices; j++) {
            
            // Sorteia um número entre 0.0 e 1.0
            double chance = (double)rand() / RAND_MAX;
            
            if (chance < edgeProbability) { 
                int weight = (rand() % 30) + 1;
                addEdge_list(graph, i, j, weight);          
            }
        }
    }

    return graph;
}

void saveResultsToJSON(GraphExperiment experiments[3], const char* filename) {
    FILE *out = fopen(filename, "w");
    if (!out) {
        printf("Erro ao criar o arquivo JSON.\n");
        return;
    }

    fprintf(out, "[\n"); // Início do array de 3 grafos

    for (int i = 0; i < 3; i++) {
        fprintf(out, "  {\n");
        
        // 1. Matriz de Adjacência
        fprintf(out, "    \"num_vertices\": %d,\n", experiments[i].numVertices);
        fprintf(out, "    \"matrix\": [\n");
        for (int v = 0; v < experiments[i].numVertices; v++) {
            fprintf(out, "      [");
            for (int u = 0; u < experiments[i].numVertices; u++) {
                fprintf(out, "%d%s", experiments[i].matrix[v][u], (u < experiments[i].numVertices - 1) ? "," : "");
            }
            fprintf(out, "]%s\n", (v < experiments[i].numVertices - 1) ? "," : "");
        }
        fprintf(out, "    ],\n");

        // 2. Resultados Questão A
        fprintf(out, "    \"planar\": {\n");
        fprintf(out, "      \"is_planar\": %s,\n", experiments[i].planar.isPlanar ? "true" : "false");
        fprintf(out, "      \"reason\": \"%s\"\n", experiments[i].planar.reason);
        fprintf(out, "    },\n");

        // 3. Resultados Questão B
        fprintf(out, "    \"articulation\": {\n");
        fprintf(out, "      \"has_points\": %s,\n", experiments[i].articulation.hasArticulation ? "true" : "false");
        fprintf(out, "      \"points\": [");
        for(int p = 0; p < experiments[i].articulation.count; p++) {
            fprintf(out, "%d%s", experiments[i].articulation.points[p], (p < experiments[i].articulation.count - 1) ? ", " : "");
        }
        fprintf(out, "]\n    },\n");

        // 4. Resultados Questão C
        fprintf(out, "    \"euler\": {\n");
        fprintf(out, "      \"type\": %d,\n", experiments[i].euler.type);
        fprintf(out, "      \"path\": [");
        for(int p = 0; p < experiments[i].euler.pathLength; p++) {
            fprintf(out, "%d%s", experiments[i].euler.path[p], (p < experiments[i].euler.pathLength - 1) ? ", " : "");
        }
        fprintf(out, "]\n    }\n");

        fprintf(out, "  }%s\n", (i < 2) ? "," : ""); // Fim do objeto
    }
    
    fprintf(out, "]\n");
    fclose(out);
    printf("Resultados salvos com sucesso em %s\n", filename);
}