#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include "symbol_table.hpp"

/*
Executes the type checking for basic operations
Returns: string containing the type to be transmited
or an empty string if there is an error

string: type of the first argument
string: type of the second argument
string: operation
int: line where this operation is executed
int: column where this operation is executed
*/
string checkType(string, string, string, int, int);

/*
Checks if an event used in the dispatcher was declared
Returns: a boolean saying if it was or wasn't declared

vector<struct Entry*>: symbol table
string: symbol to be checked
int: line where it is used
int: column where it is used
*/
bool noEventDispatcher(vector<struct Entry*>, string, int, int);

/*
Checks if a processor used in the dispatcher was declared
Returns: a boolean saying if it was or wasn't declared

vector<struct Entry*>: symbol table
string: symbol to be checked
int: line where it is used
int: column where it is used
*/
bool noProcDispatcher(vector<struct Entry*>, string, int, int);

/*
Checks if a used symbol was declared previously
Returns: the type of the symbol

vector<struct Entry*>: symbol table
string: symbol to be checked
vector<int>: list of scopes where the symbol is located
int: line where it is used
int: column where it is used
*/
string findDeclaration(vector<struct Entry*>, string, vector<int>, int, int);

/*
Checks if a symbol is getting declared twice
Returns: a boolean saying if it was or wasn't declared

vector<struct Entry*>: symbol table
string: symbol to be checked
int: scope where it was declared
*/
bool alreadyDeclared(vector<struct Entry*>, string, int, string, int, int);


string structCheck(vector<struct Entry*>, string, struct Node*, vector<int>, int, int);

string builtinChecker(vector<struct Entry*>, string, struct Node*, struct Node*, int, int, vector<int>);

string indexChecker(vector<string>, string, int, int);

bool breakChecker(int, int, int);

bool returnChecker(string, string, int, int);

string typeBuiltIn(string, string, vector<int>, vector<struct Entry*>);

#endif