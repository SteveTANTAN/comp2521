// travel.c ... client for Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"
#include "mattsGraph.h"

// make some assumptions on much data is supplied
#define MAXCITIES 40
#define MAXNAME   20

int cityID(char *, char **, int);

int testPath(char *srcName, char *destName, int expectedLength, int maxEdgeLength, char *city[MAXCITIES], int ncities, Graph world, MattsGraph mattsWorld) ;
int testGraph(char *city[MAXCITIES], int ncities, Graph world, MattsGraph mattsWorld);


int main(int argc, char *argv[])
{
	Graph world;           // graph of world/distances
    MattsGraph mattsWorld;
	FILE *data;            // file handle
	char  name[MAXNAME+2]; // input buffer to hold city name lines
	int   ncities;         // how many cities
	char *city[MAXCITIES]; // array of up to MAXCITIES city names

    // get array of city names (assumes < MAXCITIES names)
	if ((data = fopen("ha30_name.txt","r")) == NULL) {
        exit(1);
	}
	ncities = 0;
	while (fgets(name,MAXNAME,data) != NULL) {
		name[strlen(name)-1] = '\0';
		city[ncities] = strdup(name);
		ncities++;
	}
	fclose(data);

	// make empty Graph
	world = newGraph(ncities);
    mattsWorld = newMattsGraph(ncities);

	// get distances and populate Graph edges
	if ((data = fopen("ha30_dist.txt","r")) == NULL) {
        exit(1);
	}
	int n=0, fromCity, toCity, distance;
	while (fscanf(data,"%d",&distance) == 1) {
		fromCity = n / ncities;
		toCity = n % ncities;
		// convert miles to km
		distance = distance * 100 * 1.609344;
		insertEdge(world, toCity, fromCity, distance);
        insertMattsEdge(mattsWorld, toCity, fromCity, distance);
		n++;
	}
	fclose(data);

    //Test Graph
    testGraph(city, ncities, world, mattsWorld);
    
    return 0;
}

// find city name in table of names
// return index where found, or -1 if not found
int cityID(char *name, char **world, int nC)
{
	int i;
	for (i = 0; i < nC; i++) {
		if (strcmp(world[i],name) == 0)
			return i;
	}
	return -1;
}


#define NUM_TESTS 12
typedef struct _test {
    char *src;
    char *dest;
    int expectedLength;
    int maxEdgeLength;
} test;

int testGraph(char *city[MAXCITIES], int ncities, Graph world, MattsGraph mattsWorld) {
    int numPassed = 0;
    
    test tests[] = {
        {"Berlin", "Chicago", 2, 10000},
        {"Sydney", "Chicago", 3, 10000},
        {"Sydney", "London", 3, 10000},
        {"Sydney", "Buenos Aires", 4, 10000},
        {"Sydney", "London", 6, 6000},
        {"Sydney", "Buenos Aires", 0, 5000},
        {"Sydney", "Buenos Aires", 6, 7000},
        {"Sydney", "Buenos Aires", 5, 8000},
        {"Sydney", "Buenos Aires", 4, 11000},
        {"Sydney", "Buenos Aires", 2, 12000},
        {"Bombay", "Chicago", 5, 5000},
        {"Sydney", "Sydney", 1, 10000}
    };
    
    int i;
    for(i = 0; i < NUM_TESTS; i++) {
        printf("\n***Test %d\n", i);
        if (testPath(tests[i].src, tests[i].dest, tests[i].expectedLength, tests[i].maxEdgeLength, city, ncities, world, mattsWorld)) {
            numPassed++;
        } else {
            printf("Failed test %d!\n", i);
        }
        
    }
    printf("Passed %d of %d tests!\n", numPassed, NUM_TESTS);
    return numPassed;
}

int testPath(char *srcName, char *destName, int expectedLength, int maxEdgeLength, char *city[MAXCITIES], int ncities, Graph world, MattsGraph mattsWorld) {
    int src = cityID(srcName,city,ncities);
    int dest = cityID(destName,city,ncities);
    
    // use graph algorithm to find path
    int *path = malloc(ncities*sizeof(int));
    int len = findPath(world,src,dest,maxEdgeLength,path);
    
    int passed = 1;
    
    if (len != expectedLength) {
        fprintf(stderr, "Length is %d, expected %d\n", len, expectedLength);
        passed = 0;
    }
    
    if(expectedLength > 0) {
    if (path[0] != src) {
        fprintf(stderr, "Source is %d: %s, expected %d: %s\n", path[0], city[path[0]], src, city[src]);
        passed = 0;
    }
    
    if (path[len-1] != dest) {
        fprintf(stderr, "Dest is %d: %s, expected %d: %s\n", path[len - 1], city[path[len-1]], dest, city[dest]);
        passed = 0;
    }
    
    int i;
    printf("Path: %s ", city[path[0]]);
    for(i = 0; i < len -1; i++) {
        printf("%s ", city[path[i+1]]);
        if(!getWeight(mattsWorld, path[i], path[i+1])) {
            fprintf(stderr, "Segment %d: %s to %d: %s not connected\n", path[i],city[path[i]], path[i+1], city[path[i+1]]);
            passed = 0;
        }
    }
    printf("\n");
    }
    free(path);
    return passed;
}
