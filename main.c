#include <stdio.h>
#include "./include/graph.h"

int main() {

    graph_t* graph = read_graph();

    print_graph(graph);

    return 0;
}