#include "semantic.hpp"
#include "list_tree.hpp"

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

string sliceChecker(string type1, string type2, string op) {
    string allowedTypes = "int";
    string result = "";

    if ((allowedTypes.find(type1) != string::npos && allowedTypes.find(type2) != string::npos))
        result = "int";

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
    string sliceSymbol = ":";

    if(op == attribSymbol)
        result = attribChecker(type1, type2, op);
    else if(logicSymbols.find(op) != string::npos)
        result = logicChecker(type1, type2, op);
    else if(relatSymbols.find(op) != string::npos)
        result = relatChecker(type1, type2, op);
    else if(aritSymbols.find(op) != string::npos)
        result = arithChecker(type1, type2, op);
    else if(op == sliceSymbol)
        result = sliceChecker(type1, type2, op);

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

struct Entry* findEntry(vector<struct Entry*> table, string symbol, vector<int> scope, string where) {
    for(struct Entry* entry : table) {
        // Checks if the symbol exists in any scope within an entry in the table
        if(entry->symbol == symbol && find(scope.begin(), scope.end(), entry->scope.back()) != scope.end()       
        && (entry->whereDeclared == where || where == ""))
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
    struct Entry* result = findEntry(table, symbol, scope, "");
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
bool alreadyDeclared(vector<struct Entry*> table, string symbol,
int scope, string structName, int line, int column) {
    for(struct Entry* entry : table) {
        if(entry->symbol == symbol && entry->scope.back() == scope &&
        entry->whereDeclared == structName) {
            cout << "Semantic error. Symbol " << symbol << " already declared in this scope.\n"
            << "Line: " << line << " Column: " << column << endl;
            return true;
        }
    }
    return false;
}


string structCheck(vector<struct Entry*> table, string arg1, struct Node* node, vector<int> scope, int line, int column) {
    struct Entry* arg1Entry = findEntry(table, arg1, scope, "");
    if(arg1Entry == NULL)
        cout << "ERROR structCheck" << endl;
    bool hasBrackets = false;
    while(node->symbol == "[]") {
        node = node->children[0];
        hasBrackets = true;
    }
    struct Entry* arg2Entry = findEntry(table, node->symbol, scope, arg1Entry->type.front());
    if(arg2Entry != NULL) {
    //cout << "TESTANDO: "<< arg1Entry->type.front()<< " " << arg2Entry->whereDeclared << endl;
        if(arg1Entry->type.front() == arg2Entry->whereDeclared) {
            if(hasBrackets)
                return arg2Entry->type.back();
            else
                return arg2Entry->type.front();
        }
    }
    
    cout << "Semantic error. Symbol " << arg1 << " does not have an entry for " << node->symbol <<
    ".\nLine: " << line << " Column: " << column << endl;
    return "error";
}

string builtinChecker(vector<struct Entry*> table, string func,
string objType, struct Node* node, int line,
int column, vector<int> scope) {
    string noArgFuncs = "len pop get_hdr get_data";
    string oneArgFuncs = "add push add_hdr add_data";
    // Built-in functions without arguments
    if(node == NULL) {
        if(func == "len" && (objType == "queue_t" || objType == "list" || objType == "stream"))
            return "int";
        // CHECK
        if(func == "pop" && objType == "queue_t")
            return "event";
        if(func == "get_hdr" && objType == "pkt_t")
            return "";
        if(func == "get_data" && objType == "pkt_t")
            return "";
        // If the function should have one argument
        if(noArgFuncs.find(func) == string::npos)
            cout << "Semantic error. " << func << " should have one argument." << endl;
        else
            cout << "Semantic error. Incompatible type for object at left of " << func << "." << endl;
    // Built-in functions with argument
    } else {
        // Gets table entry for the argument
        string acceptedArgs = "pkt_t event_t header stream";
        string argType; 
        struct Entry* newArgEntry = NULL;
        if(acceptedArgs.find(node->type) == string::npos) {
            newArgEntry = findEntry(table, node->symbol, scope, "");
            if(newArgEntry == NULL) {
                cout << "Semantic error. Incompatible type for object at left or for argument of " << func <<
                ".\nLine: " << line << " Column: " << column << endl;
                return "error";
            }
            argType = newArgEntry->type.back();
        } else
            argType = node->type;
        if(func == "add" && ((objType == "list" && (argType == "pkt_t" || argType == "event"))
        || (objType == "stream" && argType == "stream")))
            return "";
        if(func == "push" && objType == "queue_t" && argType == "event_t")
            return "";
        if(func == "add_hdr" && objType == "pkt_t" && argType == "header")
            return "";
        if(func == "add_data" && (objType == "pkt_t" || objType == "stream") && argType == "stream")
            return "";
        if(oneArgFuncs.find(func) == string::npos)
            cout << "Semantic error. " << func << " should have no arguments." << endl;
        else
            cout << "Semantic error. Incompatible type for object at left or for argument of " << func << "." << endl;
    }
    cout << "Line: " << line << " Column: " << column << endl;
    return "error";
}

string indexChecker(vector<string> objType, string indexType, int line, int column) {
    string acceptedObj = "stream list";
    
    if(acceptedObj.find(objType.front()) != string::npos && indexType == "int")
        return objType.back();
    cout << "Semantic error. Object should be of type stream or list and index an int.\n"
    << "Line: " << line << " Column: " << column << endl;
    return "error";
}

bool breakChecker(int numberLoops, int line, int column) {
    if(numberLoops == 0) {
        cout << "Semantic error. Break should be used within loops.\n"
        << "Line: " << line << " Column: " << column << endl;
        return true;
    }
    return false;
}