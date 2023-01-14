//
// Created by ely6899 on 1/12/23.
//
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

char inputGraphs;

void build_graph_cmd(pnode *head){
    int numOfNodes = 0;
    inputGraphs = (char ) fgetc(stdin);
    while(inputGraphs != 'A' && inputGraphs != 'B' && inputGraphs != 'D' && inputGraphs != 'S' && inputGraphs != 'T' && inputGraphs != EOF){
        if(inputGraphs == ' ')
            inputGraphs = (char ) fgetc(stdin);

        if(numOfNodes == 0){
            numOfNodes = atoi(&inputGraphs);
            build_nodeList(head, numOfNodes);
            inputGraphs = (char ) fgetc(stdin);
        }

        if(inputGraphs == 'n'){
            build_block(head);
            continue;
        }
    }
}

void build_nodeList(pnode *head, int numberOfNodes){
    pnode root = *head; //Get address of first node in list.

    //Build a linked list by iterating through the number of nodes given
    for(int i = 1; i <= numberOfNodes; i++){
        root->node_num = i - 1;
        if(i != numberOfNodes){
            root->next = calloc(1, sizeof (node)); //If last of the nodes, next value should be null
            root = root->next;
        }
        else{
            root->next = NULL; //point to next node in list.
        }
    }
}

void build_block(pnode *head) {
    //pnode nodeRoot = *head;
    pnode temp;
    int endNode = 0;
    int buildFlag = 0, rootFlag = 0, numToFind = 0;
    inputGraphs = (char ) getc(stdin);
    while(inputGraphs != 'n' ){
        inputGraphs = (char ) getc(stdin);
        if(inputGraphs == ' '){
            continue;
        }

        if(
        inputGraphs == 'n' ||
        inputGraphs == EOF ||
        inputGraphs == '\0'||
        inputGraphs == 'A' ||
        inputGraphs == 'B' ||
        inputGraphs == 'D' ||
        inputGraphs == 'S' ||
        inputGraphs == 'T')
            break;

        if(rootFlag == 0){
            numToFind = atoi(&inputGraphs);
            temp = search_nodeList(head, numToFind);
            rootFlag = 1;
            continue;
        }

        if(buildFlag == 0){
            endNode = atoi(&inputGraphs);
            buildFlag = (buildFlag + 1) % 2;
            continue;
        }

        if(buildFlag == 1){
            pedge newEdge = calloc(1, sizeof (edge));
            newEdge->weight = atoi(&inputGraphs);
            newEdge->endpoint = search_nodeList(head, endNode);
            newEdge->next = NULL;
            add_edge_to_end(temp, newEdge);
            //printf("new edge added (%d)----(%d)----(%d)\n", numToFind, newEdge->weight, newEdge->endpoint->node_num);
            buildFlag = (buildFlag + 1) % 2;
            continue;
        }
    }
}

pnode search_nodeList(pnode *head, int find){
    pnode helper = *head;
    while(helper != NULL){
        if(helper->node_num == find)
            return helper;
        helper = helper->next;
    }
    return NULL;
}

void add_edge_to_end(pnode root, pedge newEdge){
    if(root->edges == NULL)
        root->edges = newEdge;
    else{
        pedge edgeHead = root->edges;
        while(edgeHead->next != NULL){
            edgeHead = edgeHead->next;
        }
        edgeHead->next = newEdge;
    }
}

void insert_node_cmd(pnode *head){

}

void delete_node_cmd(pnode *head){

}


/*
 * Print functions
 * */
void printGraph_cmd(pnode head){
    while(head != NULL){
        printEdgesOfNode(head);
        head = head->next;
    }

} //for self debug
void printEdgesOfNode(pnode root){
    pedge edgeHelper = root->edges;
    while(edgeHelper != NULL){
        printf("(%d)----(%d)---->(%d)\n", root->node_num, edgeHelper->weight, edgeHelper->endpoint->node_num);
        edgeHelper = edgeHelper->next;
    }
}



/*
 * De-allocation functions
 * */
void deleteGraph_cmd(pnode* head){
    pnode currNode = *head;

    while(currNode != NULL){
        deleteEdgesOfNode(currNode);
        currNode = currNode->next;
    }

    deleteNodes(head);

}
void deleteEdgesOfNode(pnode root){
    pedge currEdge = root->edges;

    while(currEdge != NULL){
        pedge helper = currEdge;
        currEdge = currEdge->next;
        free(helper);
    }
    root->edges = NULL; //Disconnect current node edge pointer from deallocated edges.
}
void deleteNodes(pnode *head){
    pnode currNode = *head;

    while(currNode != NULL){
        pnode helper = currNode;
        currNode = currNode->next;
        free(helper);
    }
    *head = NULL;
}

void shortsPath_cmd(pnode head){

}

void TSP_cmd(pnode head){

}
