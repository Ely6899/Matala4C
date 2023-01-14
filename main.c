#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

char input;
extern char inputGraphs;

/*void print_nodes(pnode *head){
    node *root = *head;
    while(root != NULL){
        printf("%d->", root->node_num);
        root = root->next;
    }
    printf("\n");
}

void deallocate_nodes(pnode *head){
    node *root = *head;
    node *temp = *head;
    while(root != NULL){
        root = root->next;
        free(temp);
        temp = root;
    }
    free(root);
}*/

int main() {
    input = (char)fgetc(stdin);
    pnode firstNode;//first node allocation.
    pnode *pointerToHead;//Pointer to the head node address.
    int graphExists = 0;

    while(input != EOF){
        switch (input) {
            case 'A':
                if(graphExists == 1){
                    deleteGraph_cmd(pointerToHead);
                }
                firstNode = calloc(1, sizeof (node)); //first node allocation.
                pointerToHead = &firstNode; //Pointer to the head node address.

                build_graph_cmd(pointerToHead);
                graphExists = 1;
                printGraph_cmd(firstNode);
                printf("\n");
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
    printf("\n");
    deleteGraph_cmd(pointerToHead);
    printf("First node address %p\n", firstNode);
    printf("Head of first node address %p\n", *pointerToHead);
    return 0;
}
