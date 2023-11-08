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
    int count = 0;
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

