#include "planar.h"

// Verifica se existe uma aresta entre u e v
static bool hasEdge(AdjacentGraph_list* graph, int u, int v) {
    Node_list* curr = graph->adjacentList[u];
    while (curr != NULL) {
        if (curr->destination == v) return true;
        curr = curr->next;
    }
    return false;
}

// Retorna o grau (número de arestas conectadas) de um vértice
static int getDegree(AdjacentGraph_list* graph, int v) {
    int degree = 0;
    Node_list* curr = graph->adjacentList[v];
    while (curr != NULL) {
        degree++;
        curr = curr->next;
    }
    return degree;
}

void reduceSubdivisions(AdjacentGraph_list* graph) {
    bool changed = true;
    int V = graph->numberOfVertices;

    while (changed) {
        changed = false;
        
        for (int i = 0; i < V; i++) {
            if (getDegree(graph, i) == 2) {
                // Encontra os dois vizinhos de 'i'
                int vizinho1 = -1, vizinho2 = -1;
                Node_list* curr = graph->adjacentList[i];
                
                vizinho1 = curr->destination;
                vizinho2 = curr->next->destination;

                // Remove as arestas antigas
                removeEdge_list(graph, i, vizinho1);
                removeEdge_list(graph, i, vizinho2);

                // Conecta os vizinhos diretamente (se já não estiverem conectados)
                // O peso aqui é arbitrário, pois só nos importa a topologia (peso 1)
                if (!hasEdge(graph, vizinho1, vizinho2)) {
                    addEdge_list(graph, vizinho1, vizinho2, 1);
                }
                
                changed = true;
                break; // Sai do for para recomeçar a varredura com o grafo atualizado
            }
        }
    }
}

static bool isPlanar_EulerChecks(AdjacentGraph_list* graph, ResultPlanarity* result) {
    int V = graph->numberOfVertices;
    if (V <= 3) return true;

    int E = 0;
    for (int i = 0; i < V; i++) E += getDegree(graph, i);
    E = E / 2;

    if (E > 3 * V - 6) {
        sprintf(result->reason, "Falhou no limite superior de Euler (E=%d > 3V-6)", E);
        return false; 
    }
    // Faltou a regra para bipartido aqui (se implementou, insira a lógica).
    return true; 
}

static bool containsK5(AdjacentGraph_list* graph, ResultPlanarity* result) {
    int V = graph->numberOfVertices;
    if (V < 5) return false;
    for (int a = 0; a < V - 4; a++) {
        for (int b = a + 1; b < V - 3; b++) {
            for (int c = b + 1; c < V - 2; c++) {
                for (int d = c + 1; d < V - 1; d++) {
                    for (int e = d + 1; e < V; e++) {
                        if (hasEdge(graph, a, b) && hasEdge(graph, a, c) && hasEdge(graph, a, d) && hasEdge(graph, a, e) &&
                            hasEdge(graph, b, c) && hasEdge(graph, b, d) && hasEdge(graph, b, e) && 
                            hasEdge(graph, c, d) && hasEdge(graph, c, e) && hasEdge(graph, d, e)) {
                            sprintf(result->reason, "Subgrafo K5 encontrado: {%d,%d,%d,%d,%d}", a, b, c, d, e);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

static bool containsK33(AdjacentGraph_list* graph, ResultPlanarity* result) {
    int V = graph->numberOfVertices;
    if (V < 6) return false;
    for (int a1 = 0; a1 < V - 2; a1++) {
        for (int a2 = a1 + 1; a2 < V - 1; a2++) {
            for (int a3 = a2 + 1; a3 < V; a3++) {
                for (int b1 = 0; b1 < V - 2; b1++) {
                    if (b1 == a1 || b1 == a2 || b1 == a3) continue;
                    for (int b2 = b1 + 1; b2 < V - 1; b2++) {
                        if (b2 == a1 || b2 == a2 || b2 == a3) continue;
                        for (int b3 = b2 + 1; b3 < V; b3++) {
                            if (b3 == a1 || b3 == a2 || b3 == a3) continue;
                            if (hasEdge(graph, a1, b1) && hasEdge(graph, a1, b2) && hasEdge(graph, a1, b3) &&
                                hasEdge(graph, a2, b1) && hasEdge(graph, a2, b2) && hasEdge(graph, a2, b3) &&
                                hasEdge(graph, a3, b1) && hasEdge(graph, a3, b2) && hasEdge(graph, a3, b3)) {
                                sprintf(result->reason, "Subgrafo K3,3 encontrado (A={%d,%d,%d}, B={%d,%d,%d})", a1, a2, a3, b1, b2, b3);
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

void checkPlanarity(AdjacentGraph_list* graph, ResultPlanarity* result) {
    result->isPlanar = true;
    strcpy(result->reason, "Passou nos testes de Euler e Kuratowski");

    if (!isPlanar_EulerChecks(graph, result)) {
        result->isPlanar = false;
        return;
    }

    AdjacentGraph_list* copy = copyAdjacentGraph_list(graph);
    reduceSubdivisions(copy);

    if (containsK5(copy, result) || containsK33(copy, result)) {
        result->isPlanar = false;
    }

    freeGraph_list(copy);
}