#ifndef LIST_TREE_HPP
#define LIST_TREE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

typedef struct Node {
    string symbol;
    vector<struct Node*> children;
}node;

struct Node* createNode(string, vector<struct Node*> &);

vector<struct Node*> treeToVector(struct Node*);

vector<struct Node*> removeBlankNodes(struct Node*);

void printTree(struct Node*, int);

void freeTree(struct Node*);

#endif