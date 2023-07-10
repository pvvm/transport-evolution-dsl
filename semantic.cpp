#include "semantic.hpp"


bool noEventDispatcher(vector<struct Entry*> table, string symbol, int line, int column) {
    for(struct Entry* entry : table) {
        if(entry->symbol == symbol && entry->type == "event")
            return false;
    }
    cout << "Semantic error. Event " << symbol << " not declared.\n"
    << "Line: " << line << " Column: " << column << endl;
    return true;
}

bool noProcDispatcher(vector<struct Entry*> table, string symbol, int line, int column) {
    for(struct Entry* entry : table) {
        if(entry->symbol == symbol && entry->isFunction)
            return false;
    }
    cout << "Semantic error. Processor " << symbol << " not declared.\n"
    << "Line: " << line << " Column: " << column << endl;
    return true;
}

bool notDeclared(vector<struct Entry*> table, string symbol, vector<int> scope, int line, int column) {
    for(struct Entry* entry : table) {
        // Checks if the symbol exists in any scope within an entry in the table
        if(entry->symbol == symbol && find(scope.begin(), scope.end(), entry->scope.back()) != scope.end())
            return false;
    }
    cout << "Semantic error. Symbol " << symbol << " not declared.\n"
    << "Line: " << line << " Column: " << column << endl;
    return true;
}

bool alreadyDeclared(vector<struct Entry*> table, string symbol, int scope) {
    for(struct Entry* entry : table) {
        if(entry->symbol == symbol && entry->scope.back() == scope) {
            cout << "Semantic error. Symbol " << symbol << " already declared in this scope.\n"
            << "Line: " << entry->lineDecl << " Column: " << entry->columnDecl << endl;
            return true;
        }
    }
    return false;
}