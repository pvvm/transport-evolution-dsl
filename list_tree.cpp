#include "list_tree.hpp"

/*
Allocate memory for a node and stores new values in it
Returns: pointer to new node
symbol: symbol of the node
child: address of children vector
*/
struct Node* createNode(string symbol, string type, vector<struct Node*>& child) {
    Node* node = new Node;
    node->symbol = symbol;
    node->type = type;
    node->children = child;

    child.clear();
    
    return node;
}

/*
Turns parent and child nodes into siblings in a vector
Uses recursion to access child node
Returns: vector containing nodes as siblings
node: parent node
*/
vector<struct Node*> treeToVector(struct Node* node) {
    vector<struct Node*> resultVector;

    if(!node->children.empty()) {
        resultVector = treeToVector(node->children[0]);
    }
    node->children.clear();
    resultVector.insert(resultVector.begin(), node);

    return resultVector;
}

/*
Unnecessary nodes with blank symbol ("") are removed
and their children nodes are grouped in a vector
Uses recursion to access child node

Returns: vector containing nodes as siblings
node: parent node
*/
vector<struct Node*> removeBlankNodes(struct Node* node) {
    vector<struct Node*> resultVector;

    if(node->symbol != "") {
        resultVector.push_back(node);
        return resultVector;
    }
    if(node->children.size() != 0) {
        resultVector = removeBlankNodes(node->children[0]);
        for(int i = 1; i < node->children.size(); i++)
            resultVector.push_back(node->children[i]);
    }
    delete node;

    return resultVector;
}

/*
Prints abstract syntax tree
Uses recursion to access child node

node: node which will be printed
printSpacing: number of spaces necessary to represent the depth of a node
*/
void printTree(struct Node* node, int printSpacing, fstream& file) {
    for(int i = 0; i < printSpacing; i++) {
        cout << "|    ";
        file << "|    ";
    }
    cout << "|-> " << node->symbol << endl;
    file << "|-> " << node->symbol << endl;

    for(struct Node* child : node->children) {
        printTree(child, ++printSpacing, file);
        --printSpacing;
    }
}

/*
Frees memory allocated to tree
Uses recursion to access child node

node: node which will be freed
*/
void freeTree(struct Node* node) {
    for(struct Node* child : node->children) {
        freeTree(child);
    }
    delete node;
}

/*
Frees memory allocated for a node
Used to delete type nodes, which are used
to build the symbol table

node: node which will be freed
*/
void freeNode(struct Node* node) {
    delete node;
}