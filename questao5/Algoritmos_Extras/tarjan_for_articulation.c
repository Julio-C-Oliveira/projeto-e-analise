#include "tarjan_for_articulation.h"

// Estrutura interna auxiliar para armazenar as propriedades dos vértices durante a DFS de Tarjan
typedef struct {
    bool visited;
    int startTime;
    int lowTime;
    int predecessor;
    bool isArticulation;
} TarjanAttributes;

/**
 * @brief Função auxiliar recursiva que executa a DFS modificada de Tarjan.
 */
static void tarjanDFS(AdjacentGraph_list* graph, int u, TarjanAttributes* attrs, int* timestamp, int root, int* rootChildren) {
    attrs[u].visited = true;
    (*timestamp)++;
    attrs[u].startTime = *timestamp;
    attrs[u].lowTime = *timestamp;

    Node_list* curr = graph->adjacentList[u];
    while (curr != NULL) {
        int v = curr->destination;

        // Se v não foi visitado, então é um filho de u na árvore DFS
        if (!attrs[v].visited) {
            attrs[v].predecessor = u;
            
            if (u == root) {
                (*rootChildren)++;
            }

            tarjanDFS(graph, v, attrs, timestamp, root, rootChildren);

            // Na volta da recursão, atualiza o lowTime do pai com o menor valor alcançável pelo filho
            if (attrs[v].lowTime < attrs[u].lowTime) {
                attrs[u].lowTime = attrs[v].lowTime;
            }

            // Regra 1: Se u NÃO é a raiz e o lowTime do seu filho v é maior ou igual
            // ao tempo de descoberta de u, u é um ponto de articulação.
            if (u != root && attrs[v].lowTime >= attrs[u].startTime) {
                attrs[u].isArticulation = true;
            }
        } 
        // Se v já foi visitado e não é o pai imediato de u, encontramos uma aresta de retorno (back-edge)
        else if (v != attrs[u].predecessor) {
            if (attrs[v].startTime < attrs[u].lowTime) {
                attrs[u].lowTime = attrs[v].startTime;
            }
        }
        curr = curr->next;
    }
}

void findArticulationPoints_list(AdjacentGraph_list* graph, ResultArticulation* result) {
    // Inicializa a struct de resultado
    result->count = 0;
    result->hasArticulation = false;

    if (graph == NULL || graph->numberOfVertices == 0) return;

    int V = graph->numberOfVertices;
    TarjanAttributes* attrs = (TarjanAttributes*)malloc(V * sizeof(TarjanAttributes));

    for (int i = 0; i < V; i++) {
        attrs[i].visited = false;
        attrs[i].startTime = -1;
        attrs[i].lowTime = -1;
        attrs[i].predecessor = -1;
        attrs[i].isArticulation = false;
    }

    int timestamp = 0;

    for (int i = 0; i < V; i++) {
        if (!attrs[i].visited) {
            int rootChildren = 0;
            tarjanDFS(graph, i, attrs, &timestamp, i, &rootChildren);
            if (rootChildren > 1) {
                attrs[i].isArticulation = true;
            }
        }
    }

    // Salva os pontos na struct em vez de dar printf
    for (int i = 0; i < V; i++) {
        if (attrs[i].isArticulation) {
            result->points[result->count++] = i;
            result->hasArticulation = true;
        }
    }

    free(attrs);
}