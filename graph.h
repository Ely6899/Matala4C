//
// Created by ely6899 on 1/10/23.
//

#ifndef MATALA4C_GRAPH_H
#define MATALA4C_GRAPH_H

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;



void build_graph_cmd(pnode *head);
void build_nodeList(pnode *head, int);
void build_block(pnode *head);
pnode search_nodeList(pnode *head, int);

void insert_node_cmd(pnode *head);


void delete_node_cmd(pnode *head);


void printGraph_cmd(pnode head); //for self debug


void deleteGraph_cmd(pnode* head);


void shortsPath_cmd(pnode head);


void TSP_cmd(pnode head);


#endif //MATALA4C_GRAPH_H
