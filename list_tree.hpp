#ifndef LIST_TREE_HPP
#define LIST_TREE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

/*
Struct to represent abstract syntax tree nodes

symbol: string that represents the token
type: used for type-checking
children: vector of children nodes
*/
typedef struct Node {
    string symbol;
    string type;
    vector<struct Node*> children;
}node;

/*
Allocate memory for a node and stores new values in it

Returns: pointer to new node
string: symbol of the node
string: type used to check
vector<struct Node*>&: address of children vector
*/
struct Node* createNode(string, string, vector<struct Node*> &);

/*
Turns parent and child nodes into siblings in a vector
Uses recursion to access child node

Returns: vector containing nodes as siblings
struct Node*: parent node
*/
vector<struct Node*> treeToVector(struct Node*);

/*
Unnecessary nodes with blank symbol ("") are removed
and their children nodes are grouped in a vector
Uses recursion to access child node

Returns: vector containing nodes as siblings
struct Node*: parent node
*/
vector<struct Node*> removeBlankNodes(struct Node*);


/*
Prints abstract syntax tree
Uses recursion to access child node

struct Node*: node which will be printed
int: number of spaces necessary to represent the depth of a node
*/
void printTree(struct Node*, int, fstream&);

/*
Frees memory allocated to tree
Uses recursion to access child node

struct Node*: node which will be freed
*/
void freeTree(struct Node*);

/*
Frees memory allocated for a node
Used to delete type nodes, which are used
to build the symbol table

struct Node*: node which will be freed
*/
void freeNode(struct Node*);

#endif