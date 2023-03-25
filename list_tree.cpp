#include "list_tree.hpp"

struct Node* createNode(string symbol, vector<struct Node*>& child) {
    Node* node = new Node;
    node->symbol = symbol;
    node->children = child;

    child.clear();
    
    return node;
}

void printTree(struct Node* node, int printSpacing) {
    for(int i = 0; i < printSpacing; i++)
        cout << "|    ";
    cout << "|-> " << node->symbol << endl;

    for(struct Node* child : node->children) {
        printTree(child, ++printSpacing);
        --printSpacing;
    }
}

struct Node* freeTree(struct Node* node) {
    for(struct Node* child : node->children) {
        freeTree(child);
    }
    delete node;
}