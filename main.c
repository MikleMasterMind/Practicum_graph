#include <stdio.h>
#include "graph.h"
#include "algorithm.h"


int main() {

    // amount of nodes
    int N;
    scanf("%d", &N);

    graph_t* graph = read_graph(N);

    set_number_out_graph(graph);

    graph_t* transposed_graph = get_transposed_graph(graph);

    unset_used_nodes(transposed_graph);

    int strong_components = count_strong_components(transposed_graph, N);

    graph_t* undir_graph = get_undirected_graph(graph, transposed_graph);
    unset_used_nodes(undir_graph);
    int weak_components = count_weak_components(undir_graph);

    unset_used_nodes(graph);
    int strong_bridges = count_strong_bridges(graph);

    unset_used_nodes(undir_graph);
    int weak_bridges = count_weak_bridges(undir_graph);

    delete_graph(undir_graph);
    delete_graph(transposed_graph);
    delete_graph(graph);
    
    printf("%d %d\n%d %d\n", strong_components, strong_bridges, weak_components, weak_bridges);

    return 0;
}