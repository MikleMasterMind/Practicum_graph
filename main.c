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

    int count = count_strong_components(transposed_graph, N);

    #ifdef READ_FROM_FILE
    FILE* output = fopen("output.txt", "a");
    fprintf(output, "%d\n", count);
    fclose(output);
    #else
    printf("%d\n", &n);
    #endif

    delete_graph(graph);

    delete_graph(transposed_graph);

    return 0;
}