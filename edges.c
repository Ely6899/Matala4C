//
// Created by ely6899 on 1/5/23.
//

#include "nodes.h"

typedef struct edge_ {
    int weight;
    node *endpoint;
    struct edge_ *next;
} edge, *pedge;

