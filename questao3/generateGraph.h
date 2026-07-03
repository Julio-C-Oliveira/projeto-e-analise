#ifndef GENERATEGRAPH_H
#define GENERATEGRAPH_H
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <random>

using namespace std;


inline string getVertexName(int index) {
    int letter = index % 26;
    int cycle = index / 26;

    string name;
    name += char('A' + letter);

    if (cycle > 0)
        name += to_string(cycle + 1);

    return name;
}



// ALTERADO: O tipo de retorno mudou de void para vector<vector<int>>
vector<vector<int>> generateGraph(int numVertices, bool isDense, unsigned int seed = 42) {
    if (numVertices <= 0) {
        cout << "Error: Number of vertices must be greater than zero." << endl;
        return {}; // Retorna vetor vazio em caso de erro
    }


    const int maxWeight = 30;           
    
    vector<vector<int>> matrix(numVertices, vector<int>(numVertices, 0));

    // --- Configuração das Probabilidades ---
    double probDense = 0.5; 
    double probSparse = 2.0 / (numVertices * numVertices); 
    
    double probabilidadeAresta = isDense ? probDense : probSparse;

    // --- Configuração do Motor de Aleatoriedade ---
    mt19937 gen(seed); 
    uniform_int_distribution<> distWeight(1, maxWeight); 
    uniform_real_distribution<double> distChance(0.0, 1.0); 

    // --- STEP 1: Ensure Connectivity (Simple Path) ---
    for (int i = 0; i < numVertices - 1; ++i) {
        int weight = distWeight(gen);
        matrix[i][i + 1] = weight; 
        matrix[i + 1][i] = weight; 
    }

    // --- STEP 2: Fill the rest based on density ---
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (j == i + 1) continue; 

            if (distChance(gen) < probabilidadeAresta) { 
                int weight = distWeight(gen);
                matrix[i][j] = weight;          
                matrix[j][i] = weight; 
            }
        }
    }

    // --- Graph Display Output ---
    cout << "\n--- Generated Connected Graph (" << (isDense ? "Dense" : "Sparse") << ") [Seed: " << seed << "] ---" << endl;
    
    cout << "    ";
for (int i = 0; i < numVertices; ++i) {
    cout << setw(5) << getVertexName(i);
}
    cout << "\n" << string(6 + numVertices * 5, '-') << "\n";

    for (int i = 0; i < numVertices; ++i) {
        cout << setw(3) << getVertexName(i) << " |";
        for (int j = 0; j < numVertices; ++j) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }

    return matrix; // ADICIONADO: Retorna a matriz preenchida
}

#endif