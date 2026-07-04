#include "fleury.h"

/*
Vou me basear nesse pseudo-código:
Entrada: Grafo conexo G = (V, E)
Saída: Um percurso fechado de Euler C

Algoritmo:
Escolher um vértice v qualquer de G; C <- {v}
repita
    Escolher uma aresta (v, w) não marcada via regra da ponte
    atravessar (v,w); C <- C{w}
    Marcar (v,w); v <- w
até todas as arestas estarem marcadas;
C <- C{v}; imprimir C

Regra da Ponte: Se uma aresta (v,w) é uma ponte no grafo induzido pelas arestas não marcadas, 
então (v,w) só deve ser escolhido pelo algoritmo caso não exista qualquer outra opção.
*/

// Função auxiliar para contar vértices alcançáveis a partir de um vértice (DFS)
static int dfsCount(AdjacentGraph_list* graph, int v, bool visited[]) {
    visited[v] = true;
    int count = 1; // O próprio vértice

    Node_list* current = graph->adjacentList[v];
    while (current != NULL) {
        if (!visited[current->destination]) {
            count += dfsCount(graph, current->destination, visited);
        }
        current = current->next;
    }
    return count;
}

// Verifica se a aresta (u, v) é uma escolha válida baseada na Regra da Ponte
static bool isValidNextEdge(AdjacentGraph_list* graph, int u, int v, int weight) {
    // 1. Conta quantas arestas saem de u
    int count = 0;
    Node_list* curr = graph->adjacentList[u];
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    
    // Se for a única aresta sobrando no vértice, você DEVE usá-la.
    if (count == 1) return true;

    // 2. Se houver mais de uma aresta, verifica se (u, v) é uma ponte
    int V = graph->numberOfVertices;
    
    // Conta vértices alcançáveis ANTES de remover a aresta
    bool* visited1 = (bool*)calloc(V, sizeof(bool));
    int count1 = dfsCount(graph, u, visited1);
    free(visited1);

    // Remove a aresta temporariamente para testar a conectividade
    removeEdge_list(graph, u, v);

    // Conta vértices alcançáveis DEPOIS de remover a aresta
    bool* visited2 = (bool*)calloc(V, sizeof(bool));
    int count2 = dfsCount(graph, u, visited2);
    free(visited2);

    // Adiciona a aresta de volta para restaurar o estado do grafo
    // Nota: Como o seu grafo não-direcionado adiciona (u,v) e (v,u) automaticamente,
    // passar o peso correto garante a estabilidade.
    addEdge_list(graph, u, v, weight);

    // Se count1 > count2, a remoção diminuiu o alcance (logo, é uma ponte).
    // Só retornamos true se NÃO for ponte (count1 <= count2).
    return (count1 <= count2);
}

// Função auxiliar para contar o grau no Fleury
static int getDegree_fleury(AdjacentGraph_list* graph, int v) {
    int degree = 0;
    Node_list* curr = graph->adjacentList[v];
    while (curr != NULL) {
        degree++;
        curr = curr->next;
    }
    return degree;
}

void fleury_list(AdjacentGraph_list* graph, ResultEuler* result) {
    result->pathLength = 0;
    result->type = 0; // Assume que não tem
    
    if (graph == NULL || graph->numberOfVertices == 0) return;

    // 1. CHECAGEM EULERIANA (Teorema de Euler)
    int oddCount = 0;
    int startVertex = 0;
    for(int i = 0; i < graph->numberOfVertices; i++) {
        if (getDegree_fleury(graph, i) % 2 != 0) {
            oddCount++;
            startVertex = i; // Guarda um vértice ímpar como início obrigatório
        }
    }

    if (oddCount == 0) result->type = 2; // Ciclo Euleriano
    else if (oddCount == 2) result->type = 1; // Caminho Euleriano
    else return; // Não é Euleriano, cancela a busca para poupar processamento

    // 2. PERCURSO DE FLEURY
    AdjacentGraph_list* g_copy = copyAdjacentGraph_list(graph);
    int curr_v = startVertex;
    
    while (true) {
        int adjCount = getDegree_fleury(g_copy, curr_v);

        // Se acabou as arestas, registra o último passo e termina
        if (adjCount == 0) {
            result->path[result->pathLength++] = curr_v;
            break; 
        }
        
        int* dests = (int*)malloc(adjCount * sizeof(int));
        int* weights = (int*)malloc(adjCount * sizeof(int));
        
        Node_list* countNode = g_copy->adjacentList[curr_v];
        for (int i = 0; i < adjCount; i++) {
            dests[i] = countNode->destination;
            weights[i] = countNode->weight;
            countNode = countNode->next;
        }
        
        int next_v = -1;
        for (int i = 0; i < adjCount; i++) {
            if (isValidNextEdge(g_copy, curr_v, dests[i], weights[i])) {
                next_v = dests[i];
                break;
            }
        }
        
        free(dests);
        free(weights);
        
        if (next_v != -1) {
            result->path[result->pathLength++] = curr_v; // Salva o passo
            removeEdge_list(g_copy, curr_v, next_v);
            curr_v = next_v;
        } else {
            break; // Travou (fail-safe)
        }
    }
    
    freeGraph_list(g_copy);
}