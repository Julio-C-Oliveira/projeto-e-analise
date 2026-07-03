#ifndef SAVEEXPERIMENT_H
#define SAVEEXPERIMENT_H

#include "mstResult.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

// Escreve uma matriz 2D como array JSON
static void writeMatrix(ofstream& out, const vector<vector<int>>& matrix, const string& indent) {
    out << indent << "[\n";
    for (size_t i = 0; i < matrix.size(); i++) {
        out << indent << "    [";
        for (size_t j = 0; j < matrix[i].size(); j++) {
            out << matrix[i][j];
            if (j < matrix[i].size() - 1) out << ",";
        }
        out << "]";
        if (i < matrix.size() - 1) out << ",";
        out << "\n";
    }
    out << indent << "]";
}

void saveExperiment(
    const vector<vector<int>>& graph,
    const MSTResult& kruskal,
    const MSTResult& prim,
    int vertices,
    bool isDense,
    unsigned int seed
) {
    // Cria o diretório grafos/ se não existir
    mkdir("grafos", 0755);

    // Monta o nome do arquivo
    string density = isDense ? "dense" : "sparse";
    string filename = "grafos/graph_V" + to_string(vertices)
                    + "_" + density
                    + "_S" + to_string(seed) + ".json";

    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Erro: não foi possível criar o arquivo " << filename << endl;
        return;
    }

    out << "{\n";

    // --- Seção "graph" ---
    out << "    \"graph\": {\n";
    out << "        \"vertices\": " << vertices << ",\n";
    out << "        \"dense\": " << (isDense ? "true" : "false") << ",\n";
    out << "        \"seed\": " << seed << ",\n";
    out << "        \"adjacency_matrix\":\n";
    writeMatrix(out, graph, "        ");
    out << "\n";
    out << "    },\n";

    // --- Seção "prim" ---
    out << "\n";
    out << "    \"prim\": {\n";
    out << "        \"execution_time_ms\": " << prim.executionTimeMs << ",\n";
    out << "        \"total_weight\": " << prim.totalWeight << ",\n";
    out << "        \"tree\":\n";
    writeMatrix(out, prim.tree, "        ");
    out << "\n";
    out << "    },\n";

    // --- Seção "kruskal" ---
    out << "\n";
    out << "    \"kruskal\": {\n";
    out << "        \"execution_time_ms\": " << kruskal.executionTimeMs << ",\n";
    out << "        \"total_weight\": " << kruskal.totalWeight << ",\n";
    out << "        \"tree\":\n";
    writeMatrix(out, kruskal.tree, "        ");
    out << "\n";
    out << "    }\n";

    out << "}\n";

    out.close();
    cout << "Resultado salvo em: " << filename << endl;
}

#endif
