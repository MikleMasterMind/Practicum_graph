#include <stdio.h>
#include "./include/graph.h"
#include "./include/algorithm.h"



int main() {

    graph_t* graph = read_graph();

    print_graph(graph);

    set_number_out_graph(graph);

    print_numbered_graph(graph);

    graph_t* transposed_graph = get_transposed_graph(graph);

    print_graph(transposed_graph);

    print_numbered_graph(transposed_graph);

    delete_graph(graph);

    delete_graph(transposed_graph);

    return 0;
}