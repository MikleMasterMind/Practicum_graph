#include "../include/algorithm.h"
#include "../include/graph.h"

void set_out(const graph_t* graph, const int index, const int out) {
    node_t* tmp = graph->head;

    while (tmp != NULL) {
        if (tmp->index == index) {
            tmp->tout = out;
        }

        tmp = tmp->next;
    }
}

node_t* get_node(const graph_t* graph, const int index) {
    node_t* tmp = graph->head;

    if (index == -1) {
        return NULL;
    }

    while (tmp->index != index) {
        tmp = tmp->next;
    }

    return tmp;
}

void set_number_out_node(const graph_t* graph, node_t* node, int count) {
    if (node == NULL) {
        return;
    }
    node_t* next_node = get_node(graph, node->dest);
    set_number_out_node(graph, next_node, count);
    set_out(graph, node->index, count);
    ++count;
    return;
}

int get_index_by_out(const graph_t* graph, int out) {
    node_t* tmp = graph->head;

    while ((tmp != NULL) && (tmp->tout != out)) {
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        return -1;
    } else {
        return tmp->index;
    }

}

void print_nodes_by_out(const graph_t* graph) {
    int index;
    for (int count = 0; ; ++count) {
        index = get_index_by_out(graph, count);
        if (index == -1) {
            break;
        }
        printf("%d\n", index);
    }
}
