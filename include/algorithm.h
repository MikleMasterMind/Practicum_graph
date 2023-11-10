#ifndef ALGORITHM_INCLUDED
#define ALGORITHM_INCLUDED

#include "graph.h"

// set tout to every nodes using deep first search
void set_number_out_graph(graph_t*);

// all nodes -> used = false
void unset_used_nodes(graph_t* graph);

// return amount of strong components
int count_strong_components(graph_t*, const int);

// print node index and it's tout
void print_numbered_graph(const graph_t*);

#endif