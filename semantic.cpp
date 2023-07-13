#include "semantic.hpp"

string attribChecker(string type1, string type2, string op) {
    string basicTypes = "int float bool";
    string result = "";

    if ((basicTypes.find(type1) != string::npos && basicTypes.find(type2) != string::npos) ||
    type1 == type2)
        result = type1;

    return result;
}

string logicChecker(string type1, string type2, string op) {
    string allowedTypes = "int float bool";
    string result = "";
    
    // && || !
    if (allowedTypes.find(type1) != string::npos &&
    (type2.empty() || allowedTypes.find(type2) != string::npos))
        result = "bool";

    return result;
}

string relatChecker(string type1, string type2, string op) {
    string allowedTypes = "int float bool";
    string result = "";

    // < > == != <= >=
    if(allowedTypes.find(type1) != string::npos && allowedTypes.find(type2) != string::npos)
        result = "bool";
    
    return result;
}

string arithChecker(string type1, string type2, string op) {
    string allowedTypes = "int float bool";
    string result = "";
    // Neg (-)
    if(op == "-" && type2 == "" && allowedTypes.find(type1) != string::npos)
        result = type1;
    
    // Add, sub, mult, div (+ - * /)
    else if (allowedTypes.find(type1) != string::npos && allowedTypes.find(type2) != string::npos) {
        if(type1 == "float" || type2 == "float")
            result = "float";
        else
            result = "int";
    }
    return result;
}

/*
Executes the type checking for basic operations
Returns: string containing the type to be transmited
or an empty string if there is an error

type1: type of the first argument
type2: type of the second argument
op: operation
line: line where this operation is executed
column: column where this operation is executed
*/
string checkType(string type1, string type2, string op, int line, int column) {
    string result;

    string attribSymbol = "=";
    string logicSymbols = "&& || !";
    string relatSymbols = "< > == != <= >=";
    string aritSymbols = "+ - * /";

    if(op == attribSymbol)
        result = attribChecker(type1, type2, op);
    else if(logicSymbols.find(op) != string::npos)
        result = logicChecker(type1, type2, op);
    else if(relatSymbols.find(op) != string::npos)
        result = relatChecker(type1, type2, op);
    else if(aritSymbols.find(op) != string::npos)
        result = arithChecker(type1, type2, op);

    if(result.empty()) {
        if(!type2.empty()) {
            cout << "Semantic error. Incompatible types " << type1 << " and " << type2
            << " for operation " << op << ".\n" << "Line: " << line << " Column: " << column << endl;
        } else {
            cout << "Semantic error. Incompatible type " << type1 <<" for operation "
            << op << ".\n" << "Line: " << line << " Column: " << column << endl;
        }
    }
    return result;
}

/*
Checks if an event used in the dispatcher was declared
Returns: a boolean saying if it was or wasn't declared

table: symbol table
symbol: symbol to be checked
line: line where it is used
column: column where it is used
*/
bool noEventDispatcher(vector<struct Entry*> table, string symbol, int line, int column) {
    for(struct Entry* entry : table) {
        if(entry->symbol == symbol && entry->type.front() == "event")
            return false;
    }
    cout << "Semantic error. Event " << symbol << " not declared in this scope.\n"
    << "Line: " << line << " Column: " << column << endl;
    return true;
}

/*
Checks if a processor used in the dispatcher was declared
Returns: a boolean saying if it was or wasn't declared

table: symbol table
symbol: symbol to be checked
line: line where it is used
column: column where it is used
*/
bool noProcDispatcher(vector<struct Entry*> table, string symbol, int line, int column) {
    for(struct Entry* entry : table) {
        if(entry->symbol == symbol && entry->isFunction)
            return false;
    }
    cout << "Semantic error. Processor " << symbol << " not declared in this scope.\n"
    << "Line: " << line << " Column: " << column << endl;
    return true;
}

struct Entry* findEntry(vector<struct Entry*> table, string symbol, vector<int> scope) {
    for(struct Entry* entry : table) {
        // Checks if the symbol exists in any scope within an entry in the table
        if(entry->symbol == symbol && find(scope.begin(), scope.end(), entry->scope.back()) != scope.end())
            return entry;
    }
    return NULL;
}

/*
Checks if a used symbol was declared previously
Returns: the type of the symbol

table: symbol table
symbol: symbol to be checked
scope: list of scopes where the symbol is located
line: line where it is used
column: column where it is used
*/
string findDeclaration(vector<struct Entry*> table, string symbol, vector<int> scope, int line, int column) {
    struct Entry* result = findEntry(table, symbol, scope);
    if(result != NULL)
        return result->type.front();
    cout << "Semantic error. Symbol " << symbol << " not declared in this scope.\n"
    << "Line: " << line << " Column: " << column << endl;
    return "error";
}

/*
Checks if a symbol was already declared given a scope
Returns: a boolean saying if it was or wasn't declared

table: symbol table
symbol: symbol to be checked
scope: scope where it was declared
*/
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


string structCheck(vector<struct Entry*> table, string arg1, string arg2, vector<int> scope, int line, int column) {
    struct Entry* arg1Entry = findEntry(table, arg1, scope);
    struct Entry* arg2Entry = findEntry(table, arg2, scope);

    if(arg1Entry->type.front() == arg2Entry->whereDeclared)
        return arg2Entry->type.front();
    
    cout << "Semantic error. Symbol " << arg1 << " does not have an entry for " << arg2 <<
    ".\nLine: " << line << " Column: " << column << endl;
    return "error";
}

string builtinChecker(vector<struct Entry*> table, string func,
string leftType, string argSymbol, int line,
int column, vector<int> scope) {

    // Built-in functions without arguments
    if(argSymbol.empty()) {
        if(func == "len" && (leftType == "queue_t" || leftType == "list"))
            return "int";
        // CHECK
        else if(func == "pop" && leftType == "queue_t")
            return "event";
        else if(func == "get_hdr" && leftType == "pkt_t")
            return "";
        else if(func == "get_data" && leftType == "pkt_t")
            return "";

    // Built-in functions with argument
    } else if(!argSymbol.empty()) {
        // Gets table entry for the argument
        struct Entry* argEntry = findEntry(table, argSymbol, scope);
        if(argEntry == NULL) {
            cout << "Semantic error. Function " << func << "does not accept parameters of type ." << endl;
            return "error";
        }
        if(func == "add" && (leftType == "list"))
            return "";
        else if(func == "push" && (leftType == "queue_t" && argEntry->type.back() == "event_t"))
            return "";
        else if(func == "add_hdr" && leftType == "pkt_t" && argEntry->type.back() == "header")
            return "";
        else if(func == "add_data" && leftType == "pkt_t" && argEntry->type.back() == "stream")
            return "";
    }
    return "error";
}