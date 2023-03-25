#ifndef LIST_TREE_HPP
#define LIST_TREE_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef struct Node {
    string symbol;
    vector<struct Node*> children;
}node;

struct Node* createNode(string, vector<struct Node*> &);
void printTree(struct Node*, int);
struct Node* freeTree(struct Node*);

#endif