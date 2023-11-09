#include "../include/graph.h"

#define READ_FROM_FILE

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
    } 
    // not first => add to end
    else {
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

    // read and add edges to graph by one
    // if no egdes => add -1
    int k, dest;
    for (int src = 1; src <= N; ++src) {

        // amount of destinations
        #ifdef READ_FROM_FILE
        fscanf(input, "%d", &k);
        #else
        scanf("%d", &k); // amount of edges
        #endif

        // create new node
        node_t* newnode = malloc(sizeof(node_t));
        newnode->index = src;
        newnode->dest_list = NULL;
        newnode->tout = -1;
        newnode->used = false;
        add_node(graph, newnode);

        // add destinations
        for (int i = 0; i < k; ++i) {
            
            // read dest index
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

//
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

// print graph
void print_graph(const graph_t* graph) {

    #ifdef READ_FROM_FILE
    FILE* output = fopen("output.txt", "a");
    #endif

    node_t* node = graph->head;

    // go trow list and print edges from one node in one line
    while (node != NULL) {
        dest_t* tmp = node->dest_list;
        // no arc from node
        if (tmp == NULL) {
            #ifdef READ_FROM_FILE
            fprintf(output, "(%d -> -1)", node->index);
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
