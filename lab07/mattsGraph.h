// MattsGraph.h ... interface to MattsGraph ADT
// Written by John Shepherd, March 2013

#ifndef MATT_Graph_H
#define MATT_Graph_H

#include <stdio.h>

// MattsGraph representation is hidden
typedef struct MattsGraphRep *MattsGraph;

// vertices denoted by integers 0..N-1
typedef int Vertex;
int   validMattsV(MattsGraph,Vertex); //validity check

//MattsEdges are pairs of vertices (end-points)
void insertMattsEdge(MattsGraph, Vertex, Vertex, int);
void removeMattsEdge(MattsGraph, Vertex, Vertex);

// operations on MattsGraphs
MattsGraph newMattsGraph(int nV);
void dropMattsGraph(MattsGraph);
MattsGraph makeMattsGraph(int, int**);
void showMattsGraph(MattsGraph, char **);

int getWeight(MattsGraph g, Vertex v, Vertex w);

#endif
