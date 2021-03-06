#ifndef BN_H_INCLUDED
#define BN_H_INCLUDED

#include <list>
using std::list;

int nearestNeighborEdge(double **adj, int dimension, list<int> path, int city);
int *solveNearestEdge(double **adj, int dimension, int start);

#endif