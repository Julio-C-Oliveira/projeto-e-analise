#include "dfs.h"

void dfsVisit_list(AdjacentGraph_list* graph, int vertex, DFS_AuxiliaryAttributes* auxiliaryAttibutes, int* timestamp) {
    ++(*timestamp);
    auxiliaryAttibutes[vertex].color = GRAY;
    auxiliaryAttibutes[vertex].startTime = (*timestamp); 

    printf("Visitando vértice %d\n", vertex);

    Node_list* currentNode = graph->adjacentList[vertex];
    while (currentNode != NULL) {
        int neighbor = currentNode->destination;
        if (auxiliaryAttibutes[neighbor].color == WHITE) {
            auxiliaryAttibutes[neighbor].predecessor = vertex;
            dfsVisit_list(graph, neighbor, auxiliaryAttibutes, timestamp);
        }
        currentNode = currentNode->next;
    }

    ++(*timestamp);
    auxiliaryAttibutes[vertex].color = BLACK;
    auxiliaryAttibutes[vertex].endTime = (*timestamp);
}

void dfs_list(AdjacentGraph_list* graph, int startVertex) {
    DFS_AuxiliaryAttributes* auxiliaryAttibutes = (DFS_AuxiliaryAttributes*)malloc(graph->numberOfVertices*sizeof(DFS_AuxiliaryAttributes));

    if (!auxiliaryAttibutes) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return;
    }

    int timestamp = 0;
    for (int i = 0; i < graph->numberOfVertices; i++) {
        auxiliaryAttibutes[i].color = WHITE;
        auxiliaryAttibutes[i].startTime = NULLNUMBER;
        auxiliaryAttibutes[i].endTime = NULLNUMBER;
        auxiliaryAttibutes[i].predecessor = NULLNUMBER;
    }

    printf("Iniciando DFS com o vértice %d\n", startVertex);

    dfsVisit_list(graph, startVertex, auxiliaryAttibutes, &timestamp);

    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (auxiliaryAttibutes[i].color == WHITE)
            dfsVisit_list(graph, i, auxiliaryAttibutes, &timestamp);
    }

    free(auxiliaryAttibutes);
}

bool dfsVisitCycleSearch_list(AdjacentGraph_list* graph, int vertex, DFS_AuxiliaryAttributes* auxiliaryAttibutes, int* timestamp, int* cycleStart, int* cycleEnd) {
    ++(*timestamp);
    auxiliaryAttibutes[vertex].color = GRAY;
    auxiliaryAttibutes[vertex].startTime = (*timestamp); 

    printf("Visitando vértice %d\n", vertex);

    Node_list* currentNode = graph->adjacentList[vertex];
    while (currentNode != NULL) {
        int neighbor = currentNode->destination;
        if (auxiliaryAttibutes[neighbor].color == WHITE) {
            auxiliaryAttibutes[neighbor].predecessor = vertex;
            if(dfsVisitCycleSearch_list(graph, neighbor, auxiliaryAttibutes, timestamp, cycleStart, cycleEnd) == true) 
                return true; // Pra propagar a saída em caso de true.
        } else if (auxiliaryAttibutes[neighbor].color == GRAY && neighbor != auxiliaryAttibutes[vertex].predecessor) {
            *cycleStart = neighbor;
            *cycleEnd = vertex;
            return true; // Aqui é o gatilho de encontro de ciclo. o if é só pra proagar essa resposta.
        }
        currentNode = currentNode->next;
    }

    ++(*timestamp);
    auxiliaryAttibutes[vertex].color = BLACK;
    auxiliaryAttibutes[vertex].endTime = (*timestamp);

    return false; // Se não parou no if do loop é porque não tem loop.
}

void dfsCycleSearch_list(AdjacentGraph_list* graph, int startVertex) {
    DFS_AuxiliaryAttributes* auxiliaryAttibutes = (DFS_AuxiliaryAttributes*)malloc(graph->numberOfVertices*sizeof(DFS_AuxiliaryAttributes));

    if (!auxiliaryAttibutes) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return;
    }

    int timestamp = 0;
    for (int i = 0; i < graph->numberOfVertices; i++) {
        auxiliaryAttibutes[i].color = WHITE;
        auxiliaryAttibutes[i].startTime = NULLNUMBER;
        auxiliaryAttibutes[i].endTime = NULLNUMBER;
        auxiliaryAttibutes[i].predecessor = NULLNUMBER;
    }

    printf("Iniciando DFS com o vértice %d\n", startVertex);

    int cycleStart = NULLNUMBER, cycleEnd = NULLNUMBER;

    if (dfsVisitCycleSearch_list(graph, startVertex, auxiliaryAttibutes, &timestamp, &cycleStart, &cycleEnd) == true) {
        printf("Ciclo encontrado:\n|- ");
        int currentVertex = cycleEnd;
        while (currentVertex != cycleStart && currentVertex != NULLNUMBER) {
            printf("%d <- ", currentVertex);
            currentVertex = auxiliaryAttibutes[currentVertex].predecessor;
        }
        if (currentVertex != NULLNUMBER)
            printf("%d <- %d\n", cycleStart, cycleEnd);

        free(auxiliaryAttibutes);
        return;
    }

    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (auxiliaryAttibutes[i].color == WHITE) {
            if (dfsVisitCycleSearch_list(graph, i, auxiliaryAttibutes, &timestamp, &cycleStart, &cycleEnd) == true) {
                printf("Ciclo encontrado: \n");
                int currentVertex = cycleEnd;
                while (currentVertex != cycleStart && currentVertex != NULLNUMBER) {
                    printf("%d <- ", currentVertex);
                    currentVertex = auxiliaryAttibutes[currentVertex].predecessor;
                }
                if (currentVertex != NULLNUMBER)
                    printf("%d <- %d\n", cycleStart, cycleEnd);

                free(auxiliaryAttibutes);
                return;
            }
        }
    }

    free(auxiliaryAttibutes);
}

void dfsVisit_matriz(AdjacentGraph_matriz* graph, int vertex, DFS_AuxiliaryAttributes* auxiliaryAttibutes, int* timestamp) {
    ++(*timestamp);
    auxiliaryAttibutes[vertex].color = GRAY;
    auxiliaryAttibutes[vertex].startTime = (*timestamp); 

    printf("Visitando vértice %d\n", vertex);

    for (int neighbor = 0; neighbor < graph->numberOfVertices; neighbor++) {
        if (graph->adjacentMatriz[vertex][neighbor] != 0 && auxiliaryAttibutes[neighbor].color == WHITE) {
            auxiliaryAttibutes[neighbor].predecessor = vertex;
            dfsVisit_matriz(graph, neighbor, auxiliaryAttibutes, timestamp);
        }
    }

    ++(*timestamp);
    auxiliaryAttibutes[vertex].color = BLACK;
    auxiliaryAttibutes[vertex].endTime = (*timestamp);
}

void dfs_matriz(AdjacentGraph_matriz* graph, int startVertex) {
    DFS_AuxiliaryAttributes* auxiliaryAttibutes = (DFS_AuxiliaryAttributes*)malloc(graph->numberOfVertices*sizeof(DFS_AuxiliaryAttributes));

    if (!auxiliaryAttibutes) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return;
    }

    int timestamp = 0;
    for (int i = 0; i < graph->numberOfVertices; i++) {
        auxiliaryAttibutes[i].color = WHITE;
        auxiliaryAttibutes[i].startTime = NULLNUMBER;
        auxiliaryAttibutes[i].endTime = NULLNUMBER;
        auxiliaryAttibutes[i].predecessor = NULLNUMBER;
    }

    printf("Iniciando DFS com o vértice %d\n", startVertex);

    dfsVisit_matriz(graph, startVertex, auxiliaryAttibutes, &timestamp);

    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (auxiliaryAttibutes[i].color == WHITE)
            dfsVisit_matriz(graph, i, auxiliaryAttibutes, &timestamp);
    }

    free(auxiliaryAttibutes);
}

// O erro persiste, o problema está no modo como a implementação funciona, avaliando até as areastas inexistentes, diferente da implementação de lista.
void dfsVisitCycleSearch_matriz(AdjacentGraph_matriz* graph, int vertex, DFS_AuxiliaryAttributes* auxiliaryAttibutes, int* timestamp, int* cycleStart, int* cycleEnd, bool* hasCycle) {
    ++(*timestamp);
    auxiliaryAttibutes[vertex].color = GRAY;
    auxiliaryAttibutes[vertex].startTime = (*timestamp); 

    printf("Visitando vértice %d\n", vertex);

    for (int neighbor = 0; neighbor < graph->numberOfVertices; neighbor++) {
        if (*hasCycle == true) 
            return;
        if (graph->adjacentMatriz[vertex][neighbor] != 0 ) {
            if (auxiliaryAttibutes[neighbor].color == WHITE) {
                auxiliaryAttibutes[neighbor].predecessor = vertex;
                dfsVisitCycleSearch_matriz(graph, neighbor, auxiliaryAttibutes, timestamp, cycleStart, cycleEnd, hasCycle);
            } else if (auxiliaryAttibutes[neighbor].color == GRAY && neighbor != auxiliaryAttibutes[vertex].predecessor) { // O bug está sendo ocasionado por essa linha. Pois, não existe a verificação de existência da aresta.
                *cycleStart = neighbor;
                *cycleEnd = vertex;
                *hasCycle = true;
                return; // Aqui é o gatilho de encontro de ciclo. o if é só pra proagar essa resposta.
            }
        }
    }

    ++(*timestamp);
    auxiliaryAttibutes[vertex].color = BLACK;
    auxiliaryAttibutes[vertex].endTime = (*timestamp);
}

void dfsCycleSearch_matriz(AdjacentGraph_matriz* graph, int startVertex) {
    DFS_AuxiliaryAttributes* auxiliaryAttibutes = (DFS_AuxiliaryAttributes*)malloc(graph->numberOfVertices*sizeof(DFS_AuxiliaryAttributes));

    if (!auxiliaryAttibutes) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return;
    }

    int timestamp = 0;
    for (int i = 0; i < graph->numberOfVertices; i++) {
        auxiliaryAttibutes[i].color = WHITE;
        auxiliaryAttibutes[i].startTime = NULLNUMBER;
        auxiliaryAttibutes[i].endTime = NULLNUMBER;
        auxiliaryAttibutes[i].predecessor = NULLNUMBER;
    }

    printf("Iniciando DFS com o vértice %d\n", startVertex);

    int cycleStart = NULLNUMBER, cycleEnd = NULLNUMBER;
    bool hasCycle = false;

    dfsVisitCycleSearch_matriz(graph, startVertex, auxiliaryAttibutes, &timestamp, &cycleStart, &cycleEnd, &hasCycle);

    if (hasCycle == true) {
        printf("Ciclo encontrado:\n|- ");
        int currentVertex = cycleEnd;
        while (currentVertex != cycleStart && currentVertex != NULLNUMBER) {
            printf("%d <- ", currentVertex);
            currentVertex = auxiliaryAttibutes[currentVertex].predecessor;
        }
        if (currentVertex != NULLNUMBER)
            printf("%d <- %d\n", cycleStart, cycleEnd);

        free(auxiliaryAttibutes);
        return;
    }

    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (auxiliaryAttibutes[i].color == WHITE) {
            dfsVisitCycleSearch_matriz(graph, i, auxiliaryAttibutes, &timestamp, &cycleStart, &cycleEnd, &hasCycle);

            if (hasCycle == true) {
                printf("Ciclo encontrado:\n|- ");
                int currentVertex = cycleEnd;
                while (currentVertex != cycleStart && currentVertex != NULLNUMBER) {
                    printf("%d <- ", currentVertex);
                    currentVertex = auxiliaryAttibutes[currentVertex].predecessor;
                }
                if (currentVertex != NULLNUMBER)
                    printf("%d <- %d\n", cycleStart, cycleEnd);

                free(auxiliaryAttibutes);
                return;
            }
        }
    }

    free(auxiliaryAttibutes);
}

int dfsGetNumberOfConnectedComponents_list(AdjacentGraph_list* graph, int startVertex) {
    DFS_AuxiliaryAttributes* auxiliaryAttibutes = (DFS_AuxiliaryAttributes*)malloc(graph->numberOfVertices*sizeof(DFS_AuxiliaryAttributes));

    if (!auxiliaryAttibutes) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return NULLNUMBER;
    }

    int timestamp = 0;
    for (int i = 0; i < graph->numberOfVertices; i++) {
        auxiliaryAttibutes[i].color = WHITE;
        auxiliaryAttibutes[i].startTime = NULLNUMBER;
        auxiliaryAttibutes[i].endTime = NULLNUMBER;
        auxiliaryAttibutes[i].predecessor = NULLNUMBER;
    }

    printf("Iniciando DFS com o vértice %d\n", startVertex);

    dfsVisit_list(graph, startVertex, auxiliaryAttibutes, &timestamp);

    int nullPredecessorCounter = 0;
    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (auxiliaryAttibutes[i].predecessor == NULLNUMBER)
            nullPredecessorCounter++;
    }

    free(auxiliaryAttibutes);

    return nullPredecessorCounter;
}