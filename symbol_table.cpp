#include "symbol_table.hpp"

/*
Increases the new scope and adds it to scope list
scope: list of scopes we are in
maximum: the scope with highest number
*/
void increaseScope(vector<int>& scope, int& maximumScope) {
    maximumScope++;
    scope.push_back(maximumScope);
}

/*
Pops a scope from the scope list
Used when we are leaving a scope
scope: list of scopes we are in
*/
void decreaseScope(vector<int>& scope) {
    scope.pop_back();
}

/*
Creates a new entry to the symbol table
symbol: identifier of the entry
type: type of the variable, returned value from a function, ...
scope: list of scopes we are in
line: line where the symbol is located in the inputed code
column: column where the symbol is located in the inputed code
table: the symbol table
*/
void createEntry(string symbol, string type, vector<int> scope,
int line, int column, vector<struct Entry*> & table, bool isFunction,
int numParameters, vector<string> typeParameters, string whereDeclared) {
    Entry* entry = new Entry; 
    entry->symbol = symbol;
    entry->type = type;
    entry->scope = scope;
    entry->lineDecl = line;
    entry->columnDecl = column;
    entry->isFunction = isFunction;
    entry->numParameters = numParameters;
    entry->typeParameters = typeParameters;
    entry->whereDeclared = whereDeclared;
    table.push_back(entry);
}

/*
Prints the symbol table
table: the symbol table
*/
void printTable(vector<struct Entry*> table) {
    const int l = 18, total = 163;

    cout << setfill('_') << setw(total) << "" << endl;
    cout << "|" << right << setfill(' ') << setw(l) << "Symbol |" << setw(l) << "Type |"
    << setw(l) << "Scope |" << setw(l) << "Line |" << setw(l) << "Column |" 
    << setw(l) << "Function? |" << setw(l) << "Num param |" << setw(l) << "Type param |"
    << setw(l) << "Where |" << endl;
    cout << "|" << right << setfill(' ') << setw(l) << "|" << setw(l) << "|"
    << setw(l) << "|" << setw(l) << "|" << setw(l) << "|" << setw(l) << "|"
    << setw(l) << "|" << setw(l) << "|" << setw(l) << "|"<< endl;

    string scopeList;
    string typeList;
    for(struct Entry* entry : table) {
        scopeList = "";
        typeList = "";
        for(auto scope : entry->scope)
            scopeList = scopeList + " " + to_string(scope);
        
        for(auto test : entry->typeParameters)
            typeList = typeList + " " + test;
        
        cout << "|" << right << setfill(' ') << setw(l-2) << entry->symbol << " |"
        << setw(l-2) << entry->type << " |" << setw(l-2) << scopeList << " |"
        << setw(l-2) << entry->lineDecl << " |" << setw(l-2) << entry->columnDecl << " |"
        << setw(l-2) << entry->isFunction << " |" << setw(l-2) << entry->numParameters << " |"
        << setw(l-2) << typeList << " |" << setw(l-2) << entry->whereDeclared
        << " |" << endl;
    }

    cout << "|" << right << setfill('_') << setw(l) << "|" << setw(l) << "|"
    << setw(l) << "|" << setw(l) << "|" << setw(l) << "|" << setw(l) << "|"
    << setw(l) << "|" << setw(l) << "|" << setw(l) << "|"<< endl;
}

/*
Frees the memory allocated for the symbol table
table: the symbol table
*/
void freeTable(vector<struct Entry*> table) {
    for(struct Entry* entry : table)
        delete entry;
}