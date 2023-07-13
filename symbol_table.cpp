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
whereDeclared: symbol of the struct, event, ..., where it's declared
*/
void createEntry(string symbol, string type, vector<int> scope,
int line, int column, vector<struct Entry*> & table, string whereDeclared) {
    Entry* entry = new Entry; 
    entry->symbol = symbol;
    entry->type.push_back(type);
    entry->scope = scope;
    entry->lineDecl = line;
    entry->columnDecl = column;
    entry->whereDeclared = whereDeclared;
    entry->isFunction = false;
    entry->numParameters = 0;
    entry->typeParameters = {};
    table.push_back(entry);
}

/*
Updates function entries with relevant information
table: the symbol table
symbol: identifier of the entry
scope: present scope
numParam: number of parameters
typeParam: type of the parameters
*/
void updateFunctionEntry(vector<struct Entry*> & table,
string symbol, int scope, int numParam, vector<string> typeParam) {
    for(auto entry : table) {
        if(entry->symbol == symbol && entry->scope.back() == scope) {
            entry->isFunction = true;
            entry->numParameters = numParam;
            entry->typeParameters = typeParam;
        }
    }
}

void updateTypeEntry(vector<struct Entry*> & table,
string symbol, int scope, string newType) {
    for(auto entry : table) {
        if(entry->symbol == symbol && entry->scope.back() == scope) {
            entry->type.push_back(newType);
        }
    }
}

/*
Prints the symbol table
table: the symbol table
*/
void printTable(vector<struct Entry*> table) {
    const int l = 25, total = 126;

    cout << setfill('_') << setw(total) << "" << endl;
    cout << "|" << right << setfill(' ') << setw(l) << "Symbol |" << setw(l) << "Type |"
    << setw(l) << "Scope |" << setw(l) << "Line |" << setw(l) << "Column |" 
    /*<< setw(l) << "Function? |" << setw(l) << "Num param |" << setw(l) << "Type param |"
    << setw(l) << "Where |"*/
    << endl;
    cout << "|" << right << setfill(' ') << setw(l) << "|" << setw(l) << "|"
    << setw(l) << "|" << setw(l) << "|" << setw(l) << "|"
    /*<< setw(l) << "|" << setw(l) << "|" << setw(l) << "|" << setw(l) << "|"*/
    << endl;

    string typeList;
    string scopeList;
    string argTypeList;
    for(struct Entry* entry : table) {
        typeList = "";
        scopeList = "";
        argTypeList = "";

        for(auto types : entry->type)
            typeList = typeList + " " + types;

        for(auto scope : entry->scope)
            scopeList = scopeList + " " + to_string(scope);
        
        //for(auto test : entry->typeParameters)
        //    argTypeList = argTypeList + " " + test;
        
        cout << "|" << right << setfill(' ') << setw(l-2) << entry->symbol << " |"
        << setw(l-2) << typeList << " |" << setw(l-2) << scopeList << " |"
        << setw(l-2) << entry->lineDecl << " |" << setw(l-2) << entry->columnDecl << " |"
        /*<< setw(l-2) << entry->isFunction << " |" << setw(l-2) << entry->numParameters << " |"
        << setw(l-2) << argTypeList << " |" << setw(l-2) << entry->whereDeclared << " |"*/
        << endl;
    }

    cout << "|" << right << setfill('_') << setw(l) << "|" << setw(l) << "|"
    << setw(l) << "|" << setw(l) << "|" << setw(l) << "|"
    //<< setw(l) << "|"<< setw(l) << "|" << setw(l) << "|" << setw(l) << "|"
    << endl;
}

/*
Frees the memory allocated for the symbol table
table: the symbol table
*/
void freeTable(vector<struct Entry*> table) {
    for(struct Entry* entry : table)
        delete entry;
}