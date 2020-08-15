// MattsGraph.c ... implementation of MattsGraph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mattsGraph.h"

// MattsGraph representation (adjacency matrix)
typedef struct MattsGraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} MattsGraphRep;

// check validity of Vertex
int validMattsV(MattsGraph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertMattsEdge(MattsGraph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validMattsV(g,v) && validMattsV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeMattsEdge(MattsGraph g, Vertex v, Vertex w)
{
	assert(g != NULL && validMattsV(g,v) && validMattsV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty MattsGraph
MattsGraph newMattsGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	MattsGraph new = malloc(sizeof(MattsGraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with MattsGraph
void dropMattsGraph(MattsGraph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display MattsGraph, using names for vertices
void showMattsGraph(MattsGraph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

int getWeight(MattsGraph g, Vertex v, Vertex w) {
    return g->edges[v][w];
}
