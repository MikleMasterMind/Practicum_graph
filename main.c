#include <stdio.h>
#include "./include/graph.h"

int main() {
    
    edge_t edges[2];
    edges[0].src = 1;
    edges[0].dest = 2;
    edges[1].src = 2;
    edges[1].dest = 3;


    graph_t* graph = create_graph(edges, 2);

    print_graph(graph);

    return 0;
}