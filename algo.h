//
// Created by ely6899 on 1/5/23.
//

#ifndef MATALA4C_ALGO_H
#define MATALA4C_ALGO_H
#include "nodes.h"

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);

#endif //MATALA4C_ALGO_H
