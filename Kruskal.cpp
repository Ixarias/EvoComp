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

using namespace std;

class Edge {
public:
    int source, dest;
    float weight;
    Edge() {
      source = 0;
      dest = 0;
      weight = 0;
    }
    Edge(int s, int d, float w) {
      source = s;
      dest = d;
      weight = w;
    }
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

Graph* createGraph(int v, int e) {
    Graph* graph = new Graph;
    graph->v = v;
    graph->e = e;

    graph->edge = new Edge[e];

    return graph;
}


int find(subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y) {
    int rootx = find(subsets, x);
    int rooty = find(subsets, y);

    if (subsets[rootx].rank < subsets[rooty].rank)
        subsets[rootx].parent = rooty;
    else if (subsets[rootx].rank > subsets[rooty].rank)
        subsets[rooty].parent = rootx;
    else {
        subsets[rooty].parent = rootx;
        subsets[rootx].rank++;
    }
}

int comp(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}

int KruskalMST(Graph* graph) {
    int v = graph->v;
    Edge result[v];
    int e = 0,
        i = 0;

    qsort(graph->edge, graph->e, sizeof(graph->edge[0]), comp);

    subset* subsets = new subset[(v * sizeof(subset))];

    for (int ve = 0; ve < v; ++ve) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < v - 1 && i < graph->e) {
        Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.source);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    int total = 0;
    for (int i = 0; i < e; i++)
      total += result[i].weight;
    return total;
}

class Point {
public:
  int pos;
  float x, y;
  vector<Edge> edges;
  Point(int position, float xv, float yv) {
    pos = position;
    x = xv;
    y = yv;
  }
} ;

int comptoorigin(Point pt1, Point pt2) {
  return pt1.x + pt1.y > pt2.x + pt2.y;
}

float distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}
