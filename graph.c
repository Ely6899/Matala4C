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

    printf("Number of nodes: %d\n", numOfNodes);
}

void build_block(pnode *head){
    char currInput;
    int iterNum = 0;
    scanf("%c", &currInput);

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
