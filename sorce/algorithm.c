#include "../include/algorithm.h"
#include "../include/graph.h"

#define READ_FROM_FILE

// recursive function process nodes by one
void set_number_out_node(graph_t* graph, node_t* node, int* count) {
    
    if ((node != NULL) && !(node->used)) {
        node->used = true;
        dest_t* to = node->dest_list;
        while (to != NULL) {
            set_number_out_node(graph, to->dest_p, count);
            to = to->next;
        }
        node->tout = *count;
        ++(*count);
    }

}

// set tout to every nodes by using set_number_out_node
void set_number_out_graph(graph_t* graph) {
    
    node_t* tmp = graph->head;
    dest_t* to;
    int count = 1;
    while (tmp != NULL) {
        if (!(tmp->used)) {
            tmp->used = true;
            to = tmp->dest_list;
            while (to != NULL) {
                set_number_out_node(graph, to->dest_p, &count);
                to = to->next;
            }
            tmp->tout = count;
            ++count;          
        }
        tmp = tmp->next;  
    }
}

// all nodes -> used = false
void unset_used_nodes(graph_t* graph) {
    
    node_t* tmp = graph->head;
    while (tmp != NULL) {
        tmp->used = false;
        tmp = tmp->next;
    }
}

//
void mark_dest_list(graph_t* graph, node_t* node) {

    //  emtpy node or cycle
    if ((node == NULL) || (node->used)) {
        return;
    }

    // midified node
    node->used = true;
    dest_t* to = node->dest_list;

    while (to != NULL) {
        mark_dest_list(graph, to->dest_p);
        to = to->next;
    }
}

// return amount of strong components
int count_strong_components(graph_t* graph, const int N) {

    int count = 0; // amount of strong components
    
    node_t* node;
    dest_t* to;

    for (int i = N; i > 0; --i) {

        node = graph->head;
        
        // get node by tout
        while ((node != NULL) && (node->tout != i)) {
            node = node->next;
        }

        // count strong component
        if ((node != NULL ) && !(node->used)) {
            ++count;
            mark_dest_list(graph, node);
        }
    }

    return count;
}

// print node index and it's tout
void print_numbered_graph(const graph_t* graph) {
    #ifdef READ_FROM_FILE
    FILE* output = fopen("output.txt", "a");
    #endif

    node_t* node = graph->head;

    while (node != NULL) {
        
        #ifdef READ_FROM_FILE
        fprintf(output, "(%d) out = %d \n", node->index, node->tout);
        #else
        printf("(%d out = %d) \n", node->index, node->tout);
        #endif
        node =  node->next;
    }

    #ifdef READ_FROM_FILE
    fprintf(output, "\n");
    fclose(output);
    #endif
}
