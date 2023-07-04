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

void increaseScope(vector<int>&, int&);

void decreaseScope(vector<int>&);

void createEntry(string, string, vector<int>, int, int, vector<struct Entry*> &);

void printTable(vector<struct Entry*>);

void freeTable(vector<struct Entry*>);

#endif