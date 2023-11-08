#include "../include/graph.h"

#define READ_FROM_FILE

// add node without dests to end of list
void add_node(graph_t* graph, node_t* new) {
    // first node
    if (graph->head == NULL) {
        graph->head = new;
    } else {
        graph->end->next = new;
    }
    graph->end = new;
    graph->end->dest_list = NULL;
    graph->end->next = NULL;
}

// add new dest to 
void add_dest(graph_t* graph, const int index, const int dest) {
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
    } else {
        dest_t* buf = tmp->dest_list;
        // go to the end of list
        while (buf->next != NULL) {
            buf = buf->next;
        }
        buf->next = new;
    }
}

//
node_t* get_node(const graph_t* graph, const int index) {

    node_t* tmp = graph->head;

    if (index == -1) {
        return NULL;
    }

    while ((tmp != NULL) && (tmp->index != index)) {
        tmp = tmp->next;
    }

    return tmp;

}

// create graph from input data
// graph is stored as list of nodes with pointers to lists of destinations
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

        // create new node
        node_t* newnode  = malloc(sizeof(node_t));
        newnode->index = src;
        newnode->dest_list = NULL;
        newnode->next = NULL;
        newnode->tout = -1;
        newnode->used = false;
        add_node(graph, newnode);

        // add destinations
        for (int i = 0; i < k; ++i) {

            #ifdef READ_FROM_FILE
            fscanf(input, "%d", &dest);
            #else
            scanf("%d", &dest); // amount of edges
            #endif
            
            add_dest(graph, src, dest);
        }
    }

    #ifdef READ_FROM_FILE
    fclose(input);
    #endif

    node_t* node = graph->head;
    dest_t* to;

    // set pointers
    while (node != NULL) {
        to = node->dest_list;
        while (to != NULL) {
            to->dest_p = get_node(graph, to->dest_i);
            to = to->next;
        }
        node = node->next;
    }

    return graph;
}

// print graph
void print_graph(const graph_t* graph) {

    #ifdef READ_FROM_FILE
    FILE* output = fopen("output.txt", "w");
    #endif

    node_t* node = graph->head;

    while (node != NULL) {
        dest_t* tmp = node->dest_list;
        if (tmp == NULL) {
            #ifdef READ_FROM_FILE
            fprintf(output, "(%d -> -1) \t", node->index);
            #else
            printf("(%d -> -1) \t", node->index);
            #endif
        }
        while (tmp != NULL) {
            #ifdef READ_FROM_FILE
            fprintf(output, "(%d -> %d) \t", node->index, tmp->dest_i);
            #else
            printf("(%d -> %d) \t", node->index, tmp->dest_i);
            #endif
            tmp = tmp->next;
        }
        #ifdef READ_FROM_FILE
        fprintf(output, "\n");
        #else
        printf("\n");
        #endif
        node =  node->next;
    }

    #ifdef READ_FROM_FILE
    fprintf(output, "\n");
    fclose(output);
    #endif
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

// return first not used edge from node <index>
// if all edges used return NULL
node_t* get_no_used_node(const graph_t* graph, const int index) {
    node_t* tmp = graph->head;

    while ((tmp != NULL) && (tmp->index != index) && !(tmp->used)) {
        tmp= tmp->next;
    }

    tmp->used = true;

    return tmp;
}
