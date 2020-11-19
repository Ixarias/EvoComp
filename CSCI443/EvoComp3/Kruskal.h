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

class Edge {
public:
    int source, dest;
    float weight;
    Edge();
    Edge(int, int, float);
};

class Graph {
public:
    // v - number of vertices | e - number of edges
    int v, e;
    Edge* edge;
};

Graph* createGraph(int v, int e);


class subset {
public:
    int parent;
    int rank;
};

int find(subset, int);
void Union(subset, int, int);

int comp(const void*, const void*);
int KruskalMST(Graph*);

class Point {
public:
    int pos;
    float x, y;
    vector<Edge> edges;
    Point(int, float, float);
};

int comptoorigin(Point, Point);
float distance(int, int, int, int);


#endif