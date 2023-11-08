#include<stdlib.h>
#include<stdio.h>
#include "../include/graph.h"

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
graph_t* create_graph(edge_t edges[], int N) {
    
    // get memory for graph
    // at first graph has place for 10 nodes
    graph_t* graph = malloc(sizeof(graph_t));
    graph->num = 0;
    graph->head = NULL;
    graph->end = NULL;

    for (int i = 0; i < N; ++i) {

        // get new node adjacency list
        node_t* newnode  = malloc(sizeof(node_t));
        
        // point out new node to node src
        newnode->index = edges[i].src;
        newnode->dest = edges[i].dest;

        add_node(graph, newnode);
    }

    return graph;
}

// print graph
void print_graph(const graph_t* graph) {

    node_t* tmp = graph->head;
    int prev = -1;

    while (tmp != NULL) {
        printf("(%d -> %d) \t", tmp->index, tmp->dest);
        if (prev != tmp->index) {
            printf("\n");
            prev = tmp->index;
        }
        tmp = tmp->next;
    }
}