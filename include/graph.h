#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include<stdio.h>
#include<stdbool.h>


typedef struct {
    int src, dest;
} Tedge;

typedef struct {
    Tnode* node;
} Tgraph;

typedef struct {
    Tnode* prev, next;
    int num;
    bool used;
    int tin, tup;
} Tnode;

Tgraph* create_graph();


#endif