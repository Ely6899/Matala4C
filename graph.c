//
// Created by ely6899 on 1/12/23.
//
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#define INFINITY 100000000
char inputGraphs;

//1
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


//2
void insert_node_cmd(pnode *head){
    inputGraphs = (char ) getc(stdin);
    inputGraphs = (char ) getc(stdin);

    int givenNodeNumber = atoi(&inputGraphs);
    pnode newNodeAddress = search_nodeList(head, givenNodeNumber);

    //Add new node
    if(newNodeAddress == NULL){
        newNodeAddress = addNodeToEnd(head, givenNodeNumber);
    }
    else{
        deleteEdgesOfNode(newNodeAddress);
    }

    int buildFlag = 0, endNode = 0;
    while(inputGraphs != 'A' && inputGraphs != 'B' && inputGraphs != 'D' && inputGraphs != 'S' && inputGraphs != 'T' && inputGraphs != EOF){
        inputGraphs = (char ) getc(stdin);

        if(inputGraphs == ' ')
            continue;

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
            add_edge_to_end(newNodeAddress, newEdge);
            buildFlag = (buildFlag + 1) % 2;
            //printf("new edge added (%d)----(%d)----(%d)\n", numToFind, newEdge->weight, newEdge->endpoint->node_num);
            continue;
        }


    }
}
pnode addNodeToEnd(pnode *head, int newNodeValue){
    pnode newNode = calloc(1, sizeof (node));
    newNode->node_num = newNodeValue;

    pnode curr = *head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = newNode;

    return newNode;
}


//3
void delete_node_cmd(pnode *head){
    inputGraphs = (char ) getc(stdin);
    inputGraphs = (char ) getc(stdin); //Get required node we wish to delete.
    int deletedNodeValue = atoi(&inputGraphs);
    pnode addressOfNodeToDelete = search_nodeList(head, deletedNodeValue); //Get address of desired node to delete.
    pnode currNode = *head;

    //Iterate through each node to delete relevant outgoing edges
    while(currNode != NULL){
        pedge edgeHelper = currNode->edges;
        pedge prev = edgeHelper;
        while(edgeHelper != NULL){
            if(edgeHelper->endpoint->node_num == deletedNodeValue){
                if(edgeHelper == prev){
                    edgeHelper = edgeHelper->next;
                    currNode->edges = edgeHelper;
                    free(prev);
                    prev = edgeHelper;
                }
                else{
                    prev->next = edgeHelper->next;
                    free(edgeHelper);
                    edgeHelper = prev->next;
                }
            }
            else{
                if(edgeHelper == prev)
                    edgeHelper = edgeHelper->next;
                else{
                    edgeHelper = edgeHelper->next;
                    prev = prev->next;
                }
            }
        }
        currNode = currNode->next;
    }

    deleteEdgesOfNode(addressOfNodeToDelete); //Delete outgoing edges of node to delete.
    deleteNode(head, deletedNodeValue); //Delete node after deleting all its edges.

    inputGraphs = (char ) getc(stdin);
}
/*void deleteEdgeFromNode(pnode currNode ,pedge *head){
    *//*if((*head)->endpoint->node_num == deleteValue){
        pedge to_remove = *head;
        to_remove->endpoint = NULL;
        (*head) = (*head)->next;
        free(to_remove);
        return;
    }

    for(pedge helper = *head; helper->next != NULL; helper = helper->next){
        if(helper->next->endpoint->node_num == deleteValue){
            pedge to_remove = helper->next;
            to_remove->endpoint = NULL;
            helper->next = helper->next->next;
            free(to_remove);
            return;
        }
    }*//*

}*/
void deleteNode(pnode *head, int value){
    if((*head)->node_num == value){
        pnode to_remove = *head;
        *head = (*head)->next;
        free(to_remove);
        return;
    }

    for(pnode helper = *head; helper->next != NULL; helper = helper->next){
        if(helper->next->node_num == value){
            pnode to_remove = helper->next;
            helper->next = helper->next->next;
            free(to_remove);
            return;
        }
    }
}


//4
void shortsPath_cmd(pnode head){
    inputGraphs = (char ) getc(stdin);
    inputGraphs = (char ) getc(stdin);
    int sourceNum = atoi(&inputGraphs); //Source node number value

    inputGraphs = (char ) getc(stdin);
    inputGraphs = (char ) getc(stdin);
    int destNum = atoi(&inputGraphs); //Destination node number value

    pnode temp = head;
    pnode sourceAddress = NULL, destAddress = NULL;
    while(temp != NULL){
        temp->shortestPathTemp = INFINITY;
        if(temp->node_num == sourceNum && sourceAddress == NULL)
            sourceAddress = temp;
        else if(temp->node_num == destNum && destAddress == NULL)
            destAddress = temp;

        temp = temp->next;
    }

    sourceAddress->shortestPathTemp = 0;
    int shortestPath = dijkstra(head ,sourceAddress, destAddress);
    printf("Shortest path between %d and %d is: %d\n", sourceNum, destNum, shortestPath);
    inputGraphs = (char ) getc(stdin);
}
int dijkstra(pnode head ,pnode src, pnode dst){
    int shortestRoute = 0;
    pnode temp = src;
    while(temp != dst){
        temp->isVisited = 1;
        pedge tempEdge = temp->edges;
        while(tempEdge != NULL){
            if(tempEdge->endpoint->isVisited == 0){
                tempEdge->endpoint->shortestPathTemp = shortestRoute + tempEdge->weight;
            }
            tempEdge = tempEdge->next;
        }
        temp = addressOfNextNode(head);
        shortestRoute = temp->shortestPathTemp;

        if(temp == NULL){
            shortestRoute = -1;
            break;
        }
    }
    return shortestRoute;
}
pnode addressOfNextNode(pnode head){
    int minValue = INFINITY;
    pnode helper = head;
    pnode ans = NULL;
    while(helper != NULL){
        if(helper->shortestPathTemp < minValue && helper->isVisited == 0){
            minValue = helper->shortestPathTemp;
            ans = helper;
        }
        helper = helper->next;
    }

    return ans;
}


//4
void TSP_cmd(pnode head){
    inputGraphs = (char ) getc(stdin);
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
        printf("(%d)----[%d]---->(%d)\n", root->node_num, edgeHelper->weight, edgeHelper->endpoint->node_num);
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
