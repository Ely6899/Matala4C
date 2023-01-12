//
// Created by ely6899 on 1/12/23.
//
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void build_graph_cmd(pnode *head){
    char currInput; //Current input in the stream.
    int numOfNodes = 0; //Number of nodes to build.
    scanf("%c", &currInput);
    while(currInput != 'A' && currInput != 'B' && currInput != 'D' && currInput != 'S' && currInput != 'T'){
        //Scan next char and continue loop.
        if(currInput == ' '){
            scanf("%c", &currInput);
            continue;
        }

        //If we don't have the number of nodes, then find it. Will only happen once.
        if(numOfNodes == 0){
            numOfNodes = atoi(&currInput);
            build_nodeList(head, numOfNodes);
            scanf("%c", &currInput);
            continue;
        }

        if(currInput == 'n'){
            build_block(head);
        }

        if(scanf("%c", &currInput) == EOF){
            break;
        }
    }
}

void build_nodeList(pnode *head, int numberOfNodes){
    node *root = *head; //Get address of first node in list.

    //Build a linked list by iterating through the number of nodes given
    for(int i = 1; i <= numberOfNodes; i++){
        root->node_num = i - 1;
        if(i == numberOfNodes){
            root->next = NULL; //If last of the nodes, next value should be null
        }
        else{
            root->next = malloc(sizeof (node));
            root = root->next; //point to next node in list.
        }
    }
}

void build_block(pnode *head){
    pnode root = *head;
    char currInput;
    int getRoot = 0; //Boolean of root node to add edges to.
    int typeSwitcher = 0;
    int endNode;
    scanf("%c", &currInput);
    while(currInput != 'n'){
        if(currInput == ' '){
            scanf("%c", &currInput);
            continue;
        }

        if(getRoot == 0){
            getRoot = 1;
            root = search_nodeList(head, atoi(&currInput));
            scanf("%c", &currInput);
            continue;
        }

        //End node input.
        if(typeSwitcher == 0){
            endNode = atoi(&currInput);
            scanf("%c", &currInput);
            typeSwitcher += 1;
        }

        //Edge node input.
        if(typeSwitcher == 1){
            pedge newEdge = malloc(sizeof (edge)); //new edge node
            newEdge->weight = atoi(&currInput); //current char in input is weight of the node.
            newEdge->endpoint = search_nodeList(head,endNode); //Pointer to relevant end node.
            newEdge->next = NULL;
            //TODO Add edge adder function
            root->edges = newEdge; //
            scanf("%c", &currInput);
        }






    }
}

pnode search_nodeList(pnode* head, int find){
    node *root = *head;
    while(root != NULL){
        if(root->node_num == find)
            return root;
    }
    return NULL;
}

void insert_node_cmd(pnode *head){

}

void delete_node_cmd(pnode *head){

}

void printGraph_cmd(pnode head){

} //for self debug

void deleteGraph_cmd(pnode* head){

}

void shortsPath_cmd(pnode head){

}

void TSP_cmd(pnode head){

}
