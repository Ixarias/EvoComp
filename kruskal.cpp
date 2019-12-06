#ifndef INCLUDE
#define INCLUDE

#include<vector>
#include<string>
#include<algorithm>
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
  int source, dest, weight;
};

class Graph {
public:
  // v - number of vertices | e - number of edges
  int v, e;
  Edge* edge;
};

Graph* createGraph(int v, int e) {
  Graph* graph = new Graph;
  graph->v = v;
  graph->e = e;

  graph->edge = new Edge[e];

  return graph;
}

class subset
{
public:
  int parent;
  int rank;
};

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

void KruskalMST(Graph* graph) {
  int v = graph->v;
  Edge result[v];
  int e = 0,
    i = 0;

  qsort(graph->edge, graph->e, sizeof(graph->edge[0]), comp);

  subset *subsets = new subset[(v * sizeof(subset) )];

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
  cout << "edges in constructed MST\n";
  for (int i = 0; i < e; i++)
    cout << result[i].source << " -- " << result[i].dest << " == " << result[i].weight << endl;
  return;
}

///////////////////////////////////////////////////////

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
