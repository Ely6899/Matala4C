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
    int isVisited;
    int shortestPathTemp;
    struct GRAPH_NODE_ *next;
} node, *pnode;


//1
void build_graph_cmd(pnode *head);
void build_nodeList(pnode *head, int numOfNodes);
void build_block(pnode *head);
pnode search_nodeList(pnode *head, int find);
void add_edge_to_end(pnode root, pedge);


//2
void insert_node_cmd(pnode *head);
pnode addNodeToEnd(pnode *head, int newNodeValue);


//3
void delete_node_cmd(pnode *head);
void deleteEdgeFromNode(pedge *head, int deleteValue);
void deleteNode(pnode *head, int value);


//4
void shortsPath_cmd(pnode head);
int dijkstra(pnode head, int, int);
pnode addressOfNextNode(pnode head);


//5
void TSP_cmd(pnode head);


/*
 * Print functions
 * */
void printGraph_cmd(pnode head); //for self debug
void printEdgesOfNode(pnode root);


/*
 * Deletion functions
 * */
void deleteGraph_cmd(pnode* head);
void deleteEdgesOfNode(pnode root);
void deleteNodes(pnode *head);


#endif //MATALA4C_GRAPH_H