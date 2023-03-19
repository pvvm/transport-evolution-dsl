#ifndef LIST_TREE_H
#define LIST_TREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Struct for tree's nodes
symbol: string which represents the symbol of the node
son: pointer to node's son
next: pointer to the next element of node's list
*/
typedef struct ListNode {
    char symbol[50];
    struct ListNode* son;
    struct ListNode* next;
}listNode;

/*
Allocate memory for a node and stores values in it
Returns a pointer to this new node
char *: symbol to be stored at the node
struct ListNode*: pointer to the new node's son
struct ListNode*: pointer to the next node
*/
struct ListNode* createNode(char *, struct ListNode*, struct ListNode*);

/*
Prints the tree
structListNode*: pointer to a node which might be printed
int: number of spaces necessary to print a "branch" of the tree
*/
void printTree(struct ListNode*, int);

// Create function to free tree

#endif