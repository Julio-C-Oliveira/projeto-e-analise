#ifndef PLANAR
#define PLANAR

#include <string.h>

#include "../general.h"
#include "../utils.h"
#include "../Base/adjacentListGraph.h"

void reduceSubdivisions(AdjacentGraph_list* graph);
void checkPlanarity(AdjacentGraph_list* graph, ResultPlanarity* result);

#endif
