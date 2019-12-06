#ifndef INCLUDE
#define INCLUDE

#include<vector>
#include<string>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<cmath>
#include<sstream>
#include<iterator>

#endif

#ifndef KRUSKAL_H
#define KRUSKAL_H

using namespace std;

class Kruskal {
public:

    class Edge {
    public:
        int source, dest, weight;
    };

    class Graph {
    public:
        // v - number of vertices | e - number of edges
        int v, e;
        Edge* edge;
    };

    class subset
    {
    public:
        int parent;
        int rank;
    };
    Graph* createGraph(int, int);
    int find(subset[], int);
    void Union(subset[], int, int);
    void KruskalMST(Graph*);
};

class Point {
public:
  int x, y;
} ;

float distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}

int comp(const void* a, const void* b) {
    Kruskal::Edge* a1 = (Kruskal::Edge*)a;
    Kruskal::Edge* b1 = (Kruskal::Edge*)b;
    return a1->weight > b1->weight;
}

#endif
