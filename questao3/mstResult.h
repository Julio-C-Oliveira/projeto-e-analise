// mstResult.h
#ifndef MSTRESULT_H
#define MSTRESULT_H

#include <vector>

using namespace std;

struct MSTResult {
    vector<vector<int>> tree;
    double executionTimeMs;
    int totalWeight;
};

#endif
