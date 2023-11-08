#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>


struct dest_t {
    int dest_i;
    struct dest_t* next;
    struct node_t* dest_p;
};
typedef struct dest_t dest_t;

struct node_t {
    struct node_t* next;
    dest_t* dest_list;
    int index;
    bool used;
    int tout;
};
typedef struct node_t node_t;

typedef struct {
    node_t* head; // first node
    node_t* end; // last node
} graph_t;

graph_t* read_graph();

void print_graph(const graph_t*);

void delete_graph(graph_t*);

#endif