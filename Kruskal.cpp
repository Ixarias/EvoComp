#include "Kruskal.h"
using namespace std;

Kruskal::Graph* Kruskal::createGraph(int v, int e) {
    Graph* graph = new Graph;
    graph->v = v;
    graph->e = e;

    graph->edge = new Edge[e];

    return graph;
}


int Kruskal::find(subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Kruskal::Union(subset subsets[], int x, int y) {
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

void Kruskal::KruskalMST(Graph* graph) {
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
    cout << "edges in constructed MST\n";
    for (int i = 0; i < e; i++)
        cout << result[i].source << " -- " << result[i].dest << " == " << result[i].weight << endl;
    return;
}
