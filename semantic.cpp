#include "semantic.hpp"

// We need to make the "spread" the scope of struct-like instruction variables
// ex: an element in send_queue must be able to send_queue.time_event, even if SEND event was described in other scope
bool notDeclared(vector<struct Entry*> & table, string symbol, int scope) {
    for(struct Entry* entry : table) {
        if(entry->symbol == symbol && find(entry->scope.begin(), entry->scope.end(), scope) == entry->scope.end()) {
            cout << "Sintatic error. Variable " << symbol << " not declared." << scope << endl;
            //return true;
        }
    }
    return false;
}

bool alreadyDeclared(vector<struct Entry*> & table, string symbol, int scope) {
    for(struct Entry* entry : table) {
        if(entry->symbol == symbol && entry->scope.back() == scope) {
            cout << "Sintatic error. Variable " << symbol << " already declared in this scope." << endl;
            return true;
        }
    }
    return false;
}