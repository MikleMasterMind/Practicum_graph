#include <stdio.h>
#include "./include/graph.h"
#include "./include/algorithm.h"

#define READ_FROM_FILE



int main() {

    // amount of nodes
    int N;
    #ifdef READ_FROM_FILE
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &N);
    fclose(input);
    #else
    scanf("%d", &N);
    #endif

    graph_t* graph = read_graph();

    set_number_out_graph(graph);

    graph_t* transposed_graph = get_transposed_graph(graph);

    unset_used_nodes(transposed_graph);

    int strong_components = count_strong_components(transposed_graph, N);

    unset_used_nodes(graph);
    unset_used_nodes(transposed_graph);
    int weak_components = count_weak_components(graph, transposed_graph);

    delete_graph(graph);
    graph = get_transposed_graph(transposed_graph);
    unset_used_nodes(graph);
    int strong_bridges = count_strong_bridges(graph);

    graph_t* undir_graph = get_undirected_graph(graph, transposed_graph);
    unset_used_nodes(undir_graph);
    int weak_bridges = count_weak_bridges(undir_graph);

    delete_graph(undir_graph);
    delete_graph(transposed_graph);
    delete_graph(graph);
    
    #ifdef READ_FROM_FILE
    FILE* output = fopen("output.txt", "a");
    fprintf(output, "%d %d\n%d %d\n----\n", strong_components, strong_bridges, weak_components, weak_bridges);
    fclose(output);
    #else
    printf("%d\n", &n);
    #endif

    return 0;
}