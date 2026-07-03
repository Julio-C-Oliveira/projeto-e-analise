#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <chrono>

using namespace std;

// Estrutura para representar as arestas
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Estrutura Disjoint Set Union (Union-Find) para detectar ciclos
struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) parent[root_i] = root_j;
            else if (rank[root_i] > rank[root_j]) parent[root_j] = root_i;
            else { parent[root_j] = root_i; rank[root_i]++; }
            return true;
        }
        return false;
    }
};

void runKruskal(const vector<vector<int>>& graph, int numVertices) {
    // Inicia a contagem de tempo
    auto start = chrono::high_resolution_clock::now();

    vector<Edge> edges;
    // Extrai todas as arestas do grafo (ignora 0 e pega apenas a metade superior para não duplicar)
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (graph[i][j] > 0) {
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }

    // Ordena do menor peso para o maior
    sort(edges.begin(), edges.end());

    DSU dsu(numVertices);
    vector<vector<int>> mstMatrix(numVertices, vector<int>(numVertices, 0));
    int edgesAdded = 0;

    // Constrói a Árvore Geradora Mínima (MST)
    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            mstMatrix[edge.u][edge.v] = edge.weight;
            mstMatrix[edge.v][edge.u] = edge.weight; // Espelhamento
            edgesAdded++;
            if (edgesAdded == numVertices - 1) break; // A árvore está completa
        }
    }

    // Finaliza a contagem de tempo
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = end - start;

    // --- Output Visual da Árvore Geradora Mínima ---
    cout << "\n--- Kruskal Minimum Spanning Tree ---" << endl;
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
}

#endif