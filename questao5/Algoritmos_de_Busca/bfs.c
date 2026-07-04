#include "bfs.h"

void bfs_list(AdjacentGraph_list* graph, int startVertex) {
    BFS_AuxiliaryAttributes* auxiliaryAttibutes = (BFS_AuxiliaryAttributes*)malloc(graph->numberOfVertices*sizeof(BFS_AuxiliaryAttributes));

    if (!auxiliaryAttibutes) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return;
    }

    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (i != startVertex) {
            auxiliaryAttibutes[i].color = WHITE;
            auxiliaryAttibutes[i].distance = INFINITY;
            auxiliaryAttibutes[i].predecessor = NULLNUMBER;
        }
    }

    auxiliaryAttibutes[startVertex].color = GRAY;
    auxiliaryAttibutes[startVertex].distance = INITIALDISTANCE;
    auxiliaryAttibutes[startVertex].predecessor = NULLNUMBER;

    int* queue = (int*)malloc(graph->numberOfVertices*sizeof(int));

    if (!queue) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        free(auxiliaryAttibutes);
        return;
    }

    int front = 0; int back = 0;

    queue[back] = startVertex;
    back++;

    printf("Iniciando BFS com o vértice %d\n", startVertex);

    while (front != back) {
        int vertex = queue[front];
        front++;

        printf("Visitando vértice %d\n", vertex);

        Node_list* currentNode = graph->adjacentList[vertex];
        while (currentNode != NULL) {
            int neighbor = currentNode->destination;

            if (auxiliaryAttibutes[neighbor].color == WHITE) {
                auxiliaryAttibutes[neighbor].color = GRAY;
                auxiliaryAttibutes[neighbor].distance = auxiliaryAttibutes[vertex].distance + 1;
                auxiliaryAttibutes[neighbor].predecessor = vertex;
                queue[back] = neighbor;
                back++;

                printf("|- Vértice %d descoberto.\n", neighbor);
            }

            currentNode = currentNode->next;
        }

        auxiliaryAttibutes[vertex].color = BLACK;
    }

    free(queue);
    free(auxiliaryAttibutes);
}

void bfs_matriz(AdjacentGraph_matriz* graph, int startVertex) {
    BFS_AuxiliaryAttributes* auxiliaryAttibutes = (BFS_AuxiliaryAttributes*)malloc(graph->numberOfVertices*sizeof(BFS_AuxiliaryAttributes));

    if (!auxiliaryAttibutes) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return;
    }

    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (i != startVertex) {
            auxiliaryAttibutes[i].color = WHITE;
            auxiliaryAttibutes[i].distance = INFINITY;
            auxiliaryAttibutes[i].predecessor = NULLNUMBER;
        }
    }

    auxiliaryAttibutes[startVertex].color = GRAY;
    auxiliaryAttibutes[startVertex].distance = INITIALDISTANCE;
    auxiliaryAttibutes[startVertex].predecessor = NULLNUMBER;

    int* queue = (int*)malloc(graph->numberOfVertices*sizeof(int));

    if (!queue) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        free(auxiliaryAttibutes);
        return;
    }

    int front = 0; int back = 0;

    queue[back] = startVertex;
    back++;

    printf("Iniciando BFS com o vértice %d\n", startVertex);

    while (front != back) {
        int vertex = queue[front];
        front++;

        printf("Visitando vértice %d\n", vertex);

        for (int neighbor = 0; neighbor < graph->numberOfVertices; neighbor++) {
            if (graph->adjacentMatriz[vertex][neighbor] != 0) {
                if (auxiliaryAttibutes[neighbor].color == WHITE) {
                    auxiliaryAttibutes[neighbor].color = GRAY;
                    auxiliaryAttibutes[neighbor].distance = auxiliaryAttibutes[vertex].distance + 1;
                    auxiliaryAttibutes[neighbor].predecessor = vertex;
                    queue[back] = neighbor;
                    back++;

                    printf("|- Vértice %d descoberto.\n", neighbor);
                }
            }
        }

        auxiliaryAttibutes[vertex].color = BLACK;
    }

    free(queue);
    free(auxiliaryAttibutes);
}

int bfsCalculateStepSize_list(AdjacentGraph_list* graph, int startVertex, int endVertex) {
    printf("Iniciando a busca com BFS para o caminho entre %d e %d.\n", startVertex, endVertex);

    if (startVertex == endVertex)
        return 0;

    BFS_AuxiliaryAttributes* auxiliaryAttibutes = (BFS_AuxiliaryAttributes*)malloc(graph->numberOfVertices*sizeof(BFS_AuxiliaryAttributes));

    if (!auxiliaryAttibutes) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return NULLNUMBER;
    }

    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (i != startVertex) {
            auxiliaryAttibutes[i].color = WHITE;
            auxiliaryAttibutes[i].distance = INFINITY;
            auxiliaryAttibutes[i].predecessor = NULLNUMBER;
        }
    }

    auxiliaryAttibutes[startVertex].color = GRAY;
    auxiliaryAttibutes[startVertex].distance = INITIALDISTANCE;
    auxiliaryAttibutes[startVertex].predecessor = NULLNUMBER;

    int* queue = (int*)malloc(graph->numberOfVertices*sizeof(int));

    if (!queue) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        free(auxiliaryAttibutes);
        return NULLNUMBER;
    }

    int front = 0; int back = 0; int numberOfSteps = 0;

    queue[back] = startVertex;
    back++;

    printf("Iniciando BFS com o vértice %d\n", startVertex);

    while (front != back) {
        int vertex = queue[front];
        front++;

        printf("Visitando vértice %d\n", vertex);

        Node_list* currentNode = graph->adjacentList[vertex];
        while (currentNode != NULL) {
            int neighbor = currentNode->destination;

            if (auxiliaryAttibutes[neighbor].color == WHITE) {
                auxiliaryAttibutes[neighbor].color = GRAY;
                auxiliaryAttibutes[neighbor].distance = auxiliaryAttibutes[vertex].distance + 1;
                auxiliaryAttibutes[neighbor].predecessor = vertex;
                queue[back] = neighbor;
                back++;

                printf("|- Vértice %d descoberto.\n", neighbor);

                if (neighbor == endVertex) {
                    numberOfSteps = auxiliaryAttibutes[neighbor].distance;
                    free(queue);
                    free(auxiliaryAttibutes);
                    return numberOfSteps;
                }
            }

            currentNode = currentNode->next;
        }

        auxiliaryAttibutes[vertex].color = BLACK;
    }

    free(queue);
    free(auxiliaryAttibutes);
    return NULLNUMBER;
}

int bfsCalculateStepSize_matriz(AdjacentGraph_matriz* graph, int startVertex, int endVertex) {
    printf("Iniciando a busca com BFS para o caminho entre %d e %d.\n", startVertex, endVertex);

    if (startVertex == endVertex)
        return 0;

    BFS_AuxiliaryAttributes* auxiliaryAttibutes = (BFS_AuxiliaryAttributes*)malloc(graph->numberOfVertices*sizeof(BFS_AuxiliaryAttributes));

    if (!auxiliaryAttibutes) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return NULLNUMBER;
    }

    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (i != startVertex) {
            auxiliaryAttibutes[i].color = WHITE;
            auxiliaryAttibutes[i].distance = INFINITY;
            auxiliaryAttibutes[i].predecessor = NULLNUMBER;
        }
    }

    auxiliaryAttibutes[startVertex].color = GRAY;
    auxiliaryAttibutes[startVertex].distance = INITIALDISTANCE;
    auxiliaryAttibutes[startVertex].predecessor = NULLNUMBER;

    int* queue = (int*)malloc(graph->numberOfVertices*sizeof(int));

    if (!queue) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        free(auxiliaryAttibutes);
        return NULLNUMBER;
    }

    int front = 0; int back = 0; int numberOfSteps = 0;

    queue[back] = startVertex;
    back++;

    printf("Iniciando BFS com o vértice %d\n", startVertex);

    while (front != back) {
        int vertex = queue[front];
        front++;

        printf("Visitando vértice %d\n", vertex);

        for (int neighbor = 0; neighbor < graph->numberOfVertices; neighbor++) {
            if (graph->adjacentMatriz[vertex][neighbor] != 0) {
                if (auxiliaryAttibutes[neighbor].color == WHITE) {
                    auxiliaryAttibutes[neighbor].color = GRAY;
                    auxiliaryAttibutes[neighbor].distance = auxiliaryAttibutes[vertex].distance + 1;
                    auxiliaryAttibutes[neighbor].predecessor = vertex;
                    queue[back] = neighbor;
                    back++;

                    printf("|- Vértice %d descoberto.\n", neighbor);

                    if (neighbor == endVertex) {
                        numberOfSteps = auxiliaryAttibutes[neighbor].distance;
                        free(queue);
                        free(auxiliaryAttibutes);
                        return numberOfSteps;
                    }
                }
            }
        }

        auxiliaryAttibutes[vertex].color = BLACK;
    }

    free(queue);
    free(auxiliaryAttibutes);
    return NULLNUMBER;
}