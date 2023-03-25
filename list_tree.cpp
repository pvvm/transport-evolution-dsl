#include "list_tree.hpp"

struct Node* createNode(string symbol, vector<struct Node*>& child) {
    Node* node = new Node;
    node->symbol = symbol;
    node->children = child;

    child.clear();
    
    return node;
}

vector<struct Node*> treeToVector(struct Node* node) {
    vector<struct Node*> resultVector;

    if(!node->children.empty()) {
        resultVector = treeToVector(node->children[0]);
    }
    node->children.clear();
    resultVector.insert(resultVector.begin(), node);

    return resultVector;
}

vector<struct Node*> removeBlankNodes(struct Node* node) {
    vector<struct Node*> resultVector;

    if(node->symbol != "") {
        resultVector.push_back(node);
        return resultVector;
    } else  {
        resultVector = removeBlankNodes(node->children[0]);
        resultVector.push_back(node->children[1]);

        delete node;

        return resultVector;
    }

    /*if(node->children[1]->symbol != "") {
        resultVector = removeBlankNodes(node->children[1]);
    }
    resultVector.push_back(node->children[0]);

    return resultVector;*/
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

void freeTree(struct Node* node) {
    for(struct Node* child : node->children) {
        freeTree(child);
    }
    delete node;
}