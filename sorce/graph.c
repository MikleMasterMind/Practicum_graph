#include<stdlib.h>
#include<stdio.h>
#include "../include/graph.h"

#define READ_FROM_FILE

void add_node(graph_t* graph, node_t* new) {
    //first node
    if (graph->num == 0) {
        graph->head = new;
        graph->end = new;
    } else {
        graph->end->next = new;
        graph->end = new;
    }
    graph->num++;
    graph->end->next=NULL;
}

// create graph from given edges
// graph is stored as adjacency list
graph_t* read_graph() {

    // amount of nodes
    int N; 
    #ifdef READ_FROM_FILE
    FILE* input = fopen("input.txt", "r");
    fscanf(input, "%d", &N);
    #else
    scanf("%d", &N);
    #endif

    // init graph
    graph_t* graph = malloc(sizeof(graph_t));
    graph->num = 0;
    graph->head = NULL;
    graph->end = NULL;

    // add edges to graph by one
    int k, dest;
    for (int src = 1; src <= N; ++src) {

        #ifdef READ_FROM_FILE
        fscanf(input, "%d", &k);
        #else
        scanf("%d", &k); // amount of edges
        #endif

        // no arcs go from node
        if (k == 0) {
            node_t* newnode  = malloc(sizeof(node_t));
            newnode->index = src;
            newnode->dest = -1;
            add_node(graph, newnode);
        } else {
            for (int i = 0; i < k; ++i) {

                #ifdef READ_FROM_FILE
                fscanf(input, "%d", &dest);
                #else
                scanf("%d", &dest); // amount of edges
                #endif

                node_t* newnode  = malloc(sizeof(node_t));
                newnode->index = src;
                newnode->dest = dest;
                add_node(graph, newnode);
            }
        }
    }

    #ifdef READ_FROM_FILE
    fclose(input);
    #endif

    return graph;
}

// print graph
void print_graph(const graph_t* graph) {

    #ifdef READ_FROM_FILE
    FILE* output = fopen("output.txt", "a");
    #endif

    node_t* tmp = graph->head;
    int prev = -1;

    while (tmp != NULL) {
        #ifdef READ_FROM_FILE
        if (prev != tmp->index) {
            fprintf(output, "\n");
            prev = tmp->index;
        }
        fprintf(output, "(%d -> %d) \t", tmp->index, tmp->dest);
        tmp = tmp->next;
        #else
        if (prev != tmp->index) {
            printf("\n");
            prev = tmp->index;
        }
        printf("(%d -> %d) \t", tmp->index, tmp->dest);
        tmp = tmp->next;
        #endif
    }

    #ifdef READ_FROM_FILE
    fprintf(output, "\n");
    fclose(output);
    #endif
}