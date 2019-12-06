#ifndef INCLUDE
#define INCLUDE

#include <bits/stdc++.h>

#endif

#ifndef KRUSKAL_H
#define KRUSKAL_H

using namespace std;

class Kruskal {
private:

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

public:
    Graph* createGraph(int, int);
    int find(subset[], int);
    void Union(subset[], int, int);
    int comp(const void* a, const void* b);
    void KruskalMST(Graph*);
};

#endif


