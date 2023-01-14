#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

char input;

void print_nodes(pnode *head){
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
}

int main() {
    input = (char)fgetc(stdin);
    pnode firstNode = malloc(sizeof (node)); //first node allocation.
    if(firstNode == NULL)
        exit(2);

    pnode *pointerToHead = &firstNode; //Pointer to the head node address.
    while(input != EOF){
        switch (input) {
            case 'A':
                build_graph_cmd(pointerToHead);
                printGraph_cmd(firstNode);
                input = (char )fgetc(stdin);
                break;
            case 'B':
                insert_node_cmd(pointerToHead);
                input = (char )fgetc(stdin);
                break;
            case 'D':
                delete_node_cmd(pointerToHead);
                input = (char )fgetc(stdin);
                break;
            case 'S':
                shortsPath_cmd(firstNode);
                input = (char )fgetc(stdin);
                break;
            case 'T':
                TSP_cmd(firstNode);
                input = (char )fgetc(stdin);
                break;
            default:
                input = (char )fgetc(stdin);
        }
    }
    printf("\n");

    return 0;
}
