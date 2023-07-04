#include "symbol_table.hpp"

void increaseScope(vector<int>& scope, int& maximumScope) {
    maximumScope++;
    scope.push_back(maximumScope);
}

void decreaseScope(vector<int>& scope) {
    scope.pop_back();
}

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

void freeTable(vector<struct Entry*> table) {
    for(struct Entry* entry : table)
        delete entry;
}