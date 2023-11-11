#include "../include/algorithm.h"
#include "../include/graph.h"

#define READ_FROM_FILE

// recursive function process nodes by one
void set_number_out_node(node_t* node, int* timer) {
    
    if ((node != NULL) && !(node->used)) {
        node->used = true;
        for (dest_t* to = node->dest_list; to != NULL; to = to->next) {
            set_number_out_node(to->dest_p, timer);
        }
        node->time1 = *timer;
        ++(*timer);
    }

}

// set time1 to every nodes by using set_number_out_node
void set_number_out_graph(graph_t* graph) {
    
    int timer = 1;

    for (node_t* tmp = graph->head; tmp != NULL; tmp = tmp->next) {
        if (!(tmp->used)) {
            tmp->used = true;
            for (dest_t* to = tmp->dest_list; to != NULL; to = to->next) {
                set_number_out_node(to->dest_p, &timer);
            }
            tmp->time1 = timer;
            ++timer;          
        } 
    }
}

// check if possible build way node -> index using dfs
bool can_get_way(node_t* node, const int index) {
    if ((node == NULL) || (node->used)) {
        return false;
    } else if (node->index == index) {
        return true;
    } else {
        node->used = true;
        for (dest_t* to = node->dest_list; to != NULL; to = to->next) {
            if (can_get_way(to->dest_p, index)) { return true; }
        }
        return false;
    }
}

// all nodes -> used = false
void unset_used_nodes(graph_t* graph) {
    for (node_t* tmp = graph->head; tmp != NULL; tmp = tmp->next) {
        tmp->used = false;
    }
}

// mark all nodes (where can get) as used
void mark_dest_list(node_t* node) {

    //  emtpy node or cycle
    if ((node == NULL) || (node->used)) {
        return;
    }

    // midified node
    node->used = true;

    for (dest_t* to = node->dest_list; to != NULL; to = to->next) {
        mark_dest_list(to->dest_p);
    }
}

//
int set_times(node_t* node, const int prev, int *timer, int* count) {

    node->used = true;
    node->time1 = node->time2 = (*timer)++;

    int count_back = 0;

    for (dest_t* to = node->dest_list; to != NULL; to = to->next) {
        if ((to->dest_i == prev) && !(count_back)) {
            ++count_back;
            continue;
        }

        if (to->dest_p->used) {
            // min
            node->time2 = (node->time2 > to->dest_p->time1) ? to->dest_p->time1 : node->time2;
        } else {
            set_times(to->dest_p, node->index, timer, count);
            // min
            node->time2 = (node->time2 > to->dest_p->time2) ? to->dest_p->time2 : node->time2;
            if (to->dest_p->time2 > node->time1) {
                ++(*count);
            }
        }
    }
    return *count;
}

// return amount of strong components
int count_strong_components(graph_t* graph, const int N) {

    int count = 0; // result to return
    
    node_t* node;
    dest_t* to;

    for (int i = N; i > 0; --i) {

        node = graph->head;
        
        // get node by time1
        while ((node != NULL) && (node->time1 != i)) {
            node = node->next;
        }

        // count strong component
        if ((node != NULL ) && !(node->used)) {
            ++count;
            mark_dest_list(node);
        }
    }

    return count;
}

// return amount of weak components
int count_weak_components(graph_t* graph, graph_t* trans) {
    
    int count = 0; // result to return

    node_t* node1 = graph->head;
    node_t* node2 = trans->head;

    while (node1 != NULL) {

        if (!(node1->used) && !(node2->used)) {
            ++count;
            mark_dest_list(node1);
            mark_dest_list(node2);
        }

        node1 = node1->next;
        node2 = node2->next;
    }

    return count;
}

// return amount of strong bridges
// FIX ???????????
int count_strong_bridges(graph_t* graph) {
    
    int count = 0; // result to return

    // cycle on nodes
    for (node_t* node = graph->head; node != NULL; node = node->next) {

        // single arc
        unset_used_nodes(graph);
        if ((node->dest_list != NULL) && (node->dest_list->next == NULL) && (can_get_way(node->dest_list->dest_p, node->index))) {
            ++count;
            continue;
        }
        
        // cycle on dest_list
        for (dest_t* to = node->dest_list; to != NULL; to = to->next) {

            // check if dest is in cycle
            unset_used_nodes(graph);
            if (!can_get_way(to->dest_p, node->index)) continue; 

            // cycle on dest_list exsept to
            for (dest_t* p = node->dest_list; p != NULL; p = p->next) {
                
                // got dest <to> => skip
                if (p == to) continue;

                // can't get way without arc <to>
                unset_used_nodes(graph);
                node->used = true;
                if (!can_get_way(p->dest_p, to->dest_i)) {
                    ++count;
                    break;
                }
            }
        }
    }
    return count;
}

// return amount of weak bridges
// FIX
int count_weak_bridges(graph_t* graph) {

    int count = 0;
    int timer = 0;
    int buf;

    for (node_t* node = graph->head; node != NULL; node = node->next) {
        if (!(node->used)) {
            buf = 0;
            count += set_times(node, -1, &timer, &buf);
        }
    }

    return count;
}

// print node index and it's time1
void print_numbered_graph(const graph_t* graph) {
    #ifdef READ_FROM_FILE
    FILE* output = fopen("output.txt", "a");
    #endif

    for (node_t* node = graph->head; node != NULL; node =  node->next) {
        
        #ifdef READ_FROM_FILE
        fprintf(output, "(%d) out = %d \n", node->index, node->time1);
        #else
        printf("(%d out = %d) \n", node->index, node->time1);
        #endif
    }

    #ifdef READ_FROM_FILE
    fprintf(output, "\n");
    fclose(output);
    #endif
}
