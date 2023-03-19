#include "list_tree.h"

/*
Allocate memory for a node and stores values in it
Returns a pointer to this new node

symbol: symbol to be stored at the node
son: pointer to the new node's son
next: pointer to the next node
*/
struct ListNode* createNode(char *symbol, struct ListNode* son, struct ListNode* next) {
    struct ListNode * node = (struct ListNode *) malloc(sizeof(struct ListNode));

    strcpy(node->symbol, symbol);
    node->son = son;
    node->next = next;

    return node;
}

/*
Prints the tree

node: pointer to a node which might be printed
printSpacing: number of spaces necessary to print a "branch" of the tree
*/
void printTree(struct ListNode* node, int printSpacing){
    if(strcmp(node->symbol, "")) {
        for(int i = 0; i < printSpacing; i++)
            printf("|    ");
        printf("|-> %s\n", node->symbol);
    }

    if(node->son) {
        printTree(node->son, ++printSpacing);
        --printSpacing;
    }
    while(node->next){
        printTree(node->next, printSpacing);
        node = node->next;
    }
}


/*
Frees memory allocated for the tree.
Returns a pointer to the next node pointed by the parameterized node
node: pointer to a node which will be freed
*/
struct ListNode* freeTree(struct ListNode* node) {
    while(node->son) {
        node->son = freeTree(node->son);
    }
    struct ListNode* aux = node->next;
    node->next = NULL;
    free(node);
    return aux;
}