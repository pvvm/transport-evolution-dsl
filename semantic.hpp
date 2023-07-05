#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include "symbol_table.hpp"

bool notDeclared(vector<struct Entry*> &, string, int);

bool alreadyDeclared(vector<struct Entry*> &, string, int);

#endif