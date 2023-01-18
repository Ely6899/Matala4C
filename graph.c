//
// Created by ely6899 on 1/12/23.
//
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#define INFINITY 1000000000
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

    int shortestPath = dijkstra(head,sourceNum, destNum);
    printf("Dijsktra shortest path: %d \n", shortestPath);
    inputGraphs = (char ) getc(stdin);
}
int dijkstra(pnode head ,int srcNum, int dstNum){
    pnode temp1 = head;
    pnode sourceAddress = NULL, destAddress = NULL;
    while(temp1 != NULL){
        temp1->shortestPathTemp = INFINITY;
        if(temp1->node_num == srcNum && sourceAddress == NULL)
            sourceAddress = temp1;
        else if(temp1->node_num == dstNum && destAddress == NULL)
            destAddress = temp1;

        temp1 = temp1->next;
    }

    sourceAddress->shortestPathTemp = 0;


    int shortestRoute = 0;
    pnode temp = sourceAddress;
    while(temp != destAddress){
        temp->isVisited = 1;
        pedge tempEdge = temp->edges;
        while(tempEdge != NULL){
            if(tempEdge->endpoint->isVisited == 0){
                tempEdge->endpoint->shortestPathTemp = shortestRoute + tempEdge->weight;
            }
            tempEdge = tempEdge->next;
        }
        pnode ansOfTrueShortestPath = minShortestPathTemp(head);
        if(ansOfTrueShortestPath != NULL)
            temp = addressOfNextNode(temp, ansOfTrueShortestPath);


        if(temp == NULL || ansOfTrueShortestPath == NULL){
            shortestRoute = -1;
            break;
        }

        shortestRoute = temp->shortestPathTemp;
    }

    pnode resetNode = head;
    while(resetNode != NULL){
        resetNode->shortestPathTemp = INFINITY;
        resetNode->isVisited = 0;
        resetNode = resetNode->next;
    }

    return shortestRoute;
}
pnode minShortestPathTemp(pnode head){
    int min = INFINITY;
    pnode temp = head;
    pnode ans = NULL;
    while(temp != NULL){
        if(temp->shortestPathTemp < min && temp->isVisited == 0){
            min = temp->shortestPathTemp;
            ans = temp;
        }
        temp = temp->next;
    }
    //printf("Shortest path: %d\n", ans->node_num);
    return ans;
}
pnode addressOfNextNode(pnode head, pnode ans){
    int minValue = ans->shortestPathTemp;
    pedge helperEdge = head->edges;
    while(helperEdge != NULL){
        if(helperEdge->endpoint->shortestPathTemp < minValue && helperEdge->endpoint->isVisited == 0){
            minValue = helperEdge->endpoint->shortestPathTemp;
            ans = helperEdge->endpoint;
        }
        helperEdge = helperEdge->next;
    }
    return ans;
}


//5
void TSP_cmd(pnode head){
    inputGraphs = (char ) getc(stdin);
    inputGraphs = (char ) getc(stdin);
    int numOfNodes = atoi(&inputGraphs);
    //int srcNum = 0, destNum = 0;
    char* permutationString = (char* )malloc(sizeof (char ) * numOfNodes);

    //Build first permutation string
    for(int i = 0; i < numOfNodes; i++){
        inputGraphs = (char ) getc(stdin);
        inputGraphs = (char ) getc(stdin);

        *(permutationString + i) = inputGraphs;
    }

    int minAns = -1;
    permute(permutationString, 0, numOfNodes - 1, &minAns, head);
    free(permutationString);
    printf("TSP shortest path: %d \n", minAns);
    inputGraphs = (char ) getc(stdin);
    /*inputGraphs = (char ) getc(stdin);
    inputGraphs = (char ) getc(stdin);
    srcNum = atoi(&inputGraphs);

    inputGraphs = (char ) getc(stdin);
    inputGraphs = (char ) getc(stdin);
    destNum = atoi(&inputGraphs);

    sum += dijkstra(head, srcNum, destNum);
    for(int i = 1; i < numOfNodes - 1; i++){
        srcNum = destNum;
        inputGraphs = (char ) getc(stdin);
        inputGraphs = (char ) getc(stdin);
        destNum = atoi(&inputGraphs);

        sum+= dijkstra(head, srcNum, destNum);
    }

    printf("TSP shortest path: %d\n", sum);
    inputGraphs = (char ) getc(stdin);*/
}
void permute(char* string, int startIndex, int endIndex, int* ansAddress ,pnode head){
    if(startIndex == endIndex){
        int tempSum = 0;
        for(int i = 0; i < endIndex; i++){
            char srcChar = string[i];
            char dstChar = string[i+1];
            int srcNum = srcChar - '0';
            int dstNum = dstChar - '0';
            int tempAns = dijkstra(head, srcNum, dstNum);
            if(tempAns > 0)
                tempSum+= tempAns;
            else{
                tempSum = -1;
                break;
            }
        }

        if(*ansAddress == -1 && tempSum > 0)
            *ansAddress = tempSum;
        else
        {
            if(tempSum < *ansAddress && tempSum != -1)
                *ansAddress = tempSum;
        }
    }
    else{
        for(int i = startIndex; i <= endIndex; i++){
            swap((string + i), (string + startIndex));
            permute(string, startIndex + 1, endIndex, ansAddress, head);
            swap((string + i), (string + startIndex));
        }
    }
}
void swap(char *x, char *y){
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


/*int factorial(int n){
    int ans = 1;
    if(n == 0)
        return ans;
    for(int i = 1; i <= n; i++){
        ans *= i;
    }
    return ans;
}*/


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
