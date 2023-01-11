#include <stdio.h>
#include <stdlib.h>
#include "edges.h"
#include "nodes.h"
#include "algo.h"

int main() {
    char input;
    pnode headNode = malloc(sizeof (node)); //first node allocation.
    pnode *pointerToHead = &headNode; //Pointer to the head node address.
    
    while(scanf("%c", &input) != EOF){
        switch (input) {
            case 'A':
                build_graph_cmd(pointerToHead);
                break;
            case 'B':
                insert_node_cmd(pointerToHead);
                break;
            case 'D':
                delete_node_cmd(pointerToHead);
                break;
            case 'S':
                shortsPath_cmd(headNode);
                break;
            case 'T':
                TSP_cmd(headNode);
                break;
            default:
                printf("%c", input);

        }
    }
    free(headNode);
    return 0;
}
