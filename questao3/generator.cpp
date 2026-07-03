#include "generateGraph.h" 
#include "kruskal.h" // ADICIONADO: Inclusão do header do Kruskal
#include "prim.h"    // ADICIONADO: Inclusão do header do Prim
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

    // ALTERADO: Agora capturamos o retorno da função em uma variável chamada 'graph'
    vector<vector<int>> graph = generateGraph(vertices, isDense, seed);

    // ADICIONADO: Se o grafo foi gerado com sucesso, executa os algoritmos de árvore geradora mínima
    if (!graph.empty()) {
        runKruskal(graph, vertices);
        runPrim(graph, vertices);
    }

    return 0;
}