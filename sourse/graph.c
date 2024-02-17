#include "../lib/graph.h"


// add node without dests to end of list
void add_node(graph_t* graph, node_t* new) {
    // first node
    if (graph->head == NULL) {
        graph->head = new;
    } 
    // not first => add to end
    else {
        graph->end->next = new;
    }
    graph->end = new;
    graph->end->next = NULL;
}

// add new dest to node in graph
void add_dest(graph_t* graph, int index, int dest) {

    node_t* tmp = graph->head;

    // find node
    while ((tmp != NULL) && (tmp->index != index)) {
        tmp = tmp->next;
    }

    // graph doesn't consist given node
    if (tmp == NULL) {
        return;
    }

    // create new node in dest_list
    dest_t* new = malloc(sizeof(dest_t));
    new->dest_i = dest;
    new->next = NULL;

    // first dest
    if (tmp->dest_list == NULL) {
        tmp->dest_list = new;
    } 
    // not first => add to end
    else {  
        // go to the end of list
        dest_t* buf;
        for (buf = tmp->dest_list; buf->next != NULL; buf = buf->next) {}
        buf->next = new;
    }
}

// return pointer to node of graph
node_t* get_node(const graph_t* graph, int index) {

    node_t* tmp = graph->head;

    // no nodes with this index
    if (index == -1) {
        return NULL;
    }

    // go until end or find node
    while ((tmp != NULL) && (tmp->index != index)) {
        tmp = tmp->next;
    }

    return tmp;

}

// create graph from input data
// graph is stored as list of nodes with pointers to lists of destinations
graph_t* read_graph(int N) {

    // init graph
    graph_t* graph = malloc(sizeof(graph_t));
    graph->head = NULL;
    graph->end = NULL;

    // read and add edges to graph by one
    // if no egdes => add -1
    int k, dest;
    for (int src = 1; src <= N; ++src) {

        // amount of destinations
        scanf("%d", &k);

        // create new node
        node_t* newnode = malloc(sizeof(node_t));
        newnode->index = src;
        newnode->dest_list = NULL;
        newnode->used = false;
        add_node(graph, newnode);

        // add destinations
        for (int i = 0; i < k; ++i) {
            
            // read dest index
            scanf("%d", &dest);
  
            add_dest(graph, src, dest);
        }
    }

    // set pointers
    for (node_t* node = graph->head; node != NULL; node = node->next) {
        for (dest_t* to = node->dest_list; to != NULL; to = to->next) {
            to->dest_p = get_node(graph, to->dest_i);
        }
    }

    return graph;
}

// return transposed graph
graph_t* get_transposed_graph(const graph_t* graph) {

    // init new graph
    graph_t* trans = malloc(sizeof(graph_t));
    trans->head = NULL;
    trans->end = NULL;

    // copy nodes
    node_t* node = graph->head;
    node_t* new;
    while (node != NULL) {
        new = malloc(sizeof(node_t));
        *new = *node;
        new->used = false;
        new->dest_list = NULL;
        add_node(trans, new);
        node = node->next;
    }

    // add destinations
    node = graph->head;
    dest_t* to;
    while (node != NULL) {
        to = node->dest_list;
        while (to != NULL) {
            add_dest(trans, to->dest_i, node->index);
            to = to->next;
        }
        node = node->next;
    }

    //set pointers
    node = trans->head;
    while (node != NULL) {
        to = node->dest_list;
        while (to != NULL) {
            to->dest_p = get_node(trans, to->dest_i);
            to = to->next;
        }
        node = node->next;
    }
    
    return trans;
}

//
graph_t* get_undirected_graph(const graph_t* graph1, const graph_t* graph2) {

    // init graph
    graph_t* undir = malloc(sizeof(graph_t));
    undir->head = NULL;
    undir->end = NULL;

    // copy nodes
    node_t* node = graph1->head;
    node_t* new;
    while (node != NULL) {
        new = malloc(sizeof(node_t));
        *new = *node;
        new->used = false;
        new->dest_list = NULL;
        add_node(undir, new);
        node = node->next;
    }

    // add destinations
    node = graph1->head;
    dest_t* to;
    while (node != NULL) {
        to = node->dest_list;
        while (to != NULL) {
            add_dest(undir, to->dest_i, node->index);
            to = to->next;
        }
        node = node->next;
    }
    node = graph2->head;
    while (node != NULL) {
        to = node->dest_list;
        while (to != NULL) {
            add_dest(undir, to->dest_i, node->index);
            to = to->next;
        }
        node = node->next;
    }

    //set pointers
    node = undir->head;
    while (node != NULL) {
        to = node->dest_list;
        while (to != NULL) {
            to->dest_p = get_node(undir, to->dest_i);
            to = to->next;
        }
        node = node->next;
    }
    
    return undir;
}

// free memory form graph
void delete_graph(graph_t* graph) {
    
    node_t* node;
    dest_t* dest, *tmp;
    
    while (graph->head != NULL) {
        node = graph->head;
        graph->head = graph->head->next;
        dest = node->dest_list;
        while (dest != NULL) {
            tmp = dest;
            dest = dest->next;
            free(tmp);
        }
        free(node);
    }
    free(graph);
}
