//
// Created by ely6899 on 1/5/23.
//
#include "edges.h"

typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
}node, *pnode ;

