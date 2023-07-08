#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

typedef struct Entry {
    string symbol;
    string type;
    vector<int> scope;
    int line_decl;
    int column_decl;
}entry;

/*
Increases the new scope and adds it to scope list
vector<int>&: list of scopes we are in
int&: the scope with highest number
*/
void increaseScope(vector<int>&, int&);

/*
Pops a scope from the scope list
Used when we are leaving a scope
vector<int>&: list of scopes we are in
*/
void decreaseScope(vector<int>&);

/*
Creates a new entry to the symbol table
string: identifier of the entry
string: type of the variable, returned value from a function, ...
vector<int>: list of scopes we are in
int: line where the symbol is located in the inputed code
int: column where the symbol is located in the inputed code
vector<struct Entry*>&: the symbol table
*/
void createEntry(string, string, vector<int>, int, int, vector<struct Entry*> &);

/*
Prints the symbol table
vector<struct Entry*>: the symbol table
*/
void printTable(vector<struct Entry*>);

/*
Frees the memory allocated for the symbol table
vector<struct Entry*>&: the symbol table
*/
void freeTable(vector<struct Entry*>);

#endif