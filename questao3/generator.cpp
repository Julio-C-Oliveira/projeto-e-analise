#include "generateGraph.h" 
#include "kruskal.h"        // ADICIONADO: Inclusão do header do Kruskal
#include "prim.h"           // ADICIONADO: Inclusão do header do Prim
#include "saveExperiment.h" // ADICIONADO: Inclusão do header para salvar JSON
#include <cstdlib>
#include <iostream>
#include <vector>    // ADICIONADO: Para tratar o tipo vector

using namespace std;

int main(int argc, char* argv[]) {
    // Verifica se os argumentos foram passados corretamente via linha de comando
    if (argc < 4) {
        cout << "Uso: ./generator <num_vertices> <is_dense (1 ou 0)> <seed>" << endl;
        return 1;
    }

    int vertices = atoi(argv[1]);
    bool isDense = atoi(argv[2]) != 0;
    unsigned int seed = atoi(argv[3]);

    vector<vector<int>> graph = generateGraph(vertices, isDense, seed);

    if (!graph.empty()) {

        MSTResult kruskal = runKruskal(graph, vertices);
        MSTResult prim     = runPrim(graph, vertices);

        saveExperiment(
            graph,
            kruskal,
            prim,
            vertices,
            isDense,
            seed
        );
    }



    return 0;
}