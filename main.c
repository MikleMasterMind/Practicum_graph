#include <stdio.h>
#include "./include/graph.h"
#include "./include/algorithm.h"



int main() {

    graph_t* graph = read_graph();

    print_graph(graph);

    delete_graph(graph);

    // int count = 0;
    // set_number_out_node(graph, graph->head, count);

    // print_nodes_by_out(graph);

    return 0;
}