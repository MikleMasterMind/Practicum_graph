#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include<stdio.h>
#include<stdbool.h>


typedef struct {
    int src, dest; // edge: src -> dest
} edge_t;

struct node_t {
    struct node_t* next;
    int dest;
    int index;
};
typedef struct node_t node_t;

typedef struct {
    int num; // amount nodes
    node_t* head; // first node
    node_t* end; // last node
} graph_t;


graph_t* create_graph(edge_t[], const int);

void print_graph(const graph_t*);


#endif