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
int line, int column, vector<struct Entry*> & table) {
    Entry* entry = new Entry; 
    entry->symbol = symbol;
    entry->type = type;
    entry->scope = scope;
    entry->line_decl = line;
    entry->column_decl = column;
    table.push_back(entry);
}

/*
Prints the symbol table
table: the symbol table
*/
void printTable(vector<struct Entry*> table) {
    const int l = 20, total = 101;

    cout << setfill('_') << setw(total) << "" << endl;
    cout << "|" << right << setfill(' ') << setw(l) << "Symbol |" << setw(l) << "Type |"
    << setw(l) << "Scope |" << setw(l) << "Line |" << setw(l) << "Column |" << endl;
    cout << "|" << right << setfill(' ') << setw(l) << "|" << setw(l) << "|"
    << setw(l) << "|" << setw(l) << "|" << setw(l) << "|" << endl;

    string scopeList;
    for(struct Entry* entry : table) {
        scopeList = "";
        for(int scope : entry->scope) {
            scopeList = scopeList + " " + to_string(scope);
        }
        cout << "|" << right << setfill(' ') << setw(l-2) << entry->symbol << " |"
        << setw(l-2) << entry->type << " |" << setw(l-2) << scopeList << " |"
        << setw(l-2) << entry->line_decl << " |" << setw(l-2) << entry->column_decl
        << " |" << endl;
    }

    cout << "|" << right << setfill('_') << setw(l) << "|" << setw(l) << "|"
    << setw(l) << "|" << setw(l) << "|" << setw(l) << "|" << endl;
}

/*
Frees the memory allocated for the symbol table
table: the symbol table
*/
void freeTable(vector<struct Entry*> table) {
    for(struct Entry* entry : table)
        delete entry;
}