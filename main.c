#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

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
    char input;
    pnode firstNode = malloc(sizeof (node)); //first node allocation.
    pnode *pointerToHead = &firstNode; //Pointer to the head node address.
    build_nodes(pointerToHead, 10);
    print_nodes(pointerToHead);
    deallocate_nodes(pointerToHead);
    /*if(firstNode == NULL)
        exit(2);

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
                shortsPath_cmd(firstNode);
                break;
            case 'T':
                TSP_cmd(firstNode);
                break;
            default:
                printf("%c", input);

        }
    }
    free(firstNode);
    printf("\n");*/
    return 0;
}
