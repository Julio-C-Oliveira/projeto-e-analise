#ifndef PRIM_H
#define PRIM_H
#include "mstResult.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <climits>

using namespace std;



MSTResult runPrim(const vector<vector<int>>& graph, int numVertices) {
    // Inicia a contagem de tempo
    auto start = chrono::high_resolution_clock::now();

    vector<int> parent(numVertices, -1);
    vector<int> key(numVertices, INT_MAX);
    vector<bool> inMST(numVertices, false);

    // Começamos pelo vértice 0
    key[0] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int minKey = INT_MAX;
        int u = -1;

        // Encontra o vértice com a menor "chave" que ainda não está na MST
        for (int v = 0; v < numVertices; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }
        
        if (u == -1) break; // Prevenção contra grafos desconexos
        inMST[u] = true;

        // Atualiza chaves e pais dos vértices adjacentes a 'u'
        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Constrói a matriz de adjacência da MST
    vector<vector<int>> mstMatrix(numVertices, vector<int>(numVertices, 0));
    for (int i = 1; i < numVertices; i++) {
        if (parent[i] != -1) {
            mstMatrix[i][parent[i]] = graph[i][parent[i]];
            mstMatrix[parent[i]][i] = graph[i][parent[i]]; // Espelhamento
        }
    }

    // Finaliza a contagem de tempo
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = end - start;

    // --- Output Visual da Árvore Geradora Mínima ---
    cout << "\n--- Prim Minimum Spanning Tree ---" << endl;
    cout << "   ";
    for (int i = 0; i < numVertices; ++i) {
        cout << setw(4) << (char)('A' + i);
    }
    cout << "\n" << string(3 + numVertices * 4, '-') << "\n";

    for (int i = 0; i < numVertices; ++i) {
        cout << (char)('A' + i) << " |";
        for (int j = 0; j < numVertices; ++j) {
            cout << setw(4) << mstMatrix[i][j];
        }
        cout << endl;
    }
    
    // Imprime o tempo de execução
    cout << "Execution time: " << duration.count() << " ms\n";
    MSTResult result;

result.tree = mstMatrix;
result.executionTimeMs = duration.count();

int total = 0;
for (int i = 1; i < numVertices; i++)
    if (parent[i] != -1)
        total += graph[i][parent[i]];

result.totalWeight = total;

return result;
}

#endif