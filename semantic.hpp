#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include "symbol_table.hpp"

bool noEventDispatcher(vector<struct Entry*>, string, int, int);

bool noProcDispatcher(vector<struct Entry*>, string, int, int);

bool notDeclared(vector<struct Entry*>, string, vector<int>, int, int);

bool alreadyDeclared(vector<struct Entry*>, string, int);

#endif