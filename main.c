#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

char input;
extern char inputGraphs;

int main() {
    input = (char)fgetc(stdin);
    pnode firstNode;//first node allocation.
    pnode *pointerToHead;//Pointer to the head node address.
    int graphExists = 0;

    while(input != EOF && input != '\n'){
        switch (input) {
            case 'A':
                if(graphExists == 1){
                    deleteGraph_cmd(pointerToHead);
                }
                firstNode = calloc(1, sizeof (node)); //first node allocation.
                pointerToHead = &firstNode; //Pointer to the head node address.

                build_graph_cmd(pointerToHead);
                graphExists = 1;
                break;
            case 'B':
                insert_node_cmd(pointerToHead);
                break;
            case 'D':
                delete_node_cmd(pointerToHead);
                break;
            case 'S':
                shortsPath_cmd(firstNode);
                break;
            case 'T':
                TSP_cmd(firstNode);
                break;
            default:
                break;
        }
        if(inputGraphs != ' ')
            input = inputGraphs;
        else
            input = (char)fgetc(stdin);
    }

    deleteGraph_cmd(pointerToHead);
    return 0;
}
