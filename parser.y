%define parse.error verbose
%define lr.type canonical-lr

%{
#include "include/list_tree.hpp"
#include "include/symbol_table.hpp"
#include "include/semantic.hpp"

extern int yylex(void);
extern int yylex_destroy(void);
extern char * yytext;
extern FILE *yyin;
void yyerror(const char *);
struct Node* opOperations(struct Node*, struct Node*, string, int, int);

vector<struct Node*> children;
vector<struct Node*> emptyVector;
vector<struct Entry*> symbolTable;
struct Node * helper;
struct Node * helper2;
struct Node * helper3;
struct Node * helper4;

// Variables used to construct the symbol table
int maximumScope = 0;
vector<int> scopeList;
// Stores column where a symbol is declared, to be put on the symbol table later
int columnBeginDecl = 0;
// Counter for the number of parameters of a function
int paramCounter = 0;
// Symbol of the struct/event/header where another symbol was declared
string whereDeclared = "";
// List of parameter type
vector<string> paramType;

string resultType = "";

int numberLoops = 0;

string functionType = "";

%}

%code requires {
    struct token {
        char symbol[50];
        int line;
        int column;
        int columnBegin;
    };
}

%union {
    struct token token;
    struct Node* node;
    struct Entry* entry;
}

%token <token> INT_T FLOAT_T BOOL_T STREAM_T EVENT EVENT_T QUEUE_T SCHEDULER_T DISPATCH LIST_T PACKET_T
%token <token> /*PROC_OUT_T*/ STRUCT_T CONTEXT_T HEADER CONST_INT CONST_FLOAT MATH_HIGH_OP MATH_ADD_OP TRUE FALSE
%token <token> MATH_SUB_OP LOGIC_OR_OP LOGIC_AND_OP LOGIC_NOT_OP GREATER_OP LESSER_OP RELAT_HIGH_OP
%token <token> RELAT_LOW_OP SLICE_OP ATTRIB_OP IF ELSE FOR FOREACH TIME IN RETURN BREAK TYPE NEW_PKT
%token <token> LENGTH ADD_DATA ADD_HDR GET_HDR GET_DATA ADD PUSH POP BYTES /*NEXT_EVENT ENQUEUE*/ ID OPEN_B CLOSE_B OPEN_S CLOSE_S
%token <token> OPEN_P CLOSE_P DOT COMMA SEMIC ARROW TIMER SET_DURATION START STOP RESTART

%type <node> program multDecl declarations headerDecl dispatcher dispMult dispDecl
%type <node> processorIds processorOrType structDecl 
%type <node> /*processorDecl*/ context contVariables scheduler queues queueAndDrop
%type <node> eventType eventTypeDecl queueDecl /*dropDecl*/
%type <node> /*enquDecl nextEvent nextParam*/ comMultStmt comFunction argsOrNot funcArgs
%type <node> commonStmt conditionDecl argCondition comCondition dropLoop comLoop loopArgs
%type <node> bracketsOrNot firstArgument argument return varDecl types
%type <node> attribution logicalOr logicalAnd compareExp relationExp
%type <node> lowMathExp highMathExp unaryExp element idVariations builtInFunc timerOps squareBrackets sliceExp

%right ELSE CLOSE_P

// CHECK: FOREACH FOR BOTH OR NOT
// CHECK: PROC_OUT_T KEYWORD OR NOT

/*
TO DO:

IN structCheck, MAKE SURE THAT THE LIST SUBTYPE OF AN OBJECT
MATCHES WITH THE ARGUMENT'S TYPE

WHAT IF WE CHANGE FROM id.get_hdr<id>() to id.get_hdr()?

ADD SEMANTIC ANALYSIS FOR QUEUE DECLARATION?

SHOULD TIME OPS WOKS AS BUILT IN FUNCTIONS?

IN for(something in listSomething), should something be declared
previously?
*/

%start program

%%

program:        multDecl                                {children = removeBlankNodes($1);
                                                        $$ = createNode("program", "test", children);
                                                        fstream file;
                                                        file.open("tree_result.txt", ios::out);
                                                        printTree($$, 0, file);
                                                        printTable(symbolTable);
                                                        freeTree($$);
                                                        freeTable(symbolTable);
                                                        delete $1;}
                | /* empty */                           {$$ = NULL;}
                ;

multDecl:       multDecl declarations                   {children = removeBlankNodes($2);
                                                        children.insert(children.begin(), $1);
                                                        $$ = createNode("", "test", children);}
                | declarations                          {$$ = $1;}
                ;

declarations:   headerDecl                              {$$ = $1;}
                | eventType                             {$$ = $1;}
                | scheduler                             {$$ = $1;}
                | dispatcher                            {$$ = $1;}
                | processorOrType                       {$$ = $1;}
                | context                               {$$ = $1;}
                ;

// HEADER START

headerDecl:     HEADER ID                               {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        //increaseScope(scopeList, maximumScope);
                                                        whereDeclared = $2.symbol;}
                    OPEN_B contVariables CLOSE_B
                                                        {//decreaseScope(scopeList);
                                                        whereDeclared = "";
                                                        children = removeBlankNodes($5);
                                                        $$ = createNode("headerDecl", "test", children);}
                ;

// HEADER END

// EVENT START

    // event id { ... };
eventType:      EVENT ID                                {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        //increaseScope(scopeList, maximumScope);
                                                        whereDeclared = $2.symbol;}
                    OPEN_B eventTypeDecl CLOSE_B
                                                        {//decreaseScope(scopeList);
                                                        whereDeclared = "";
                                                        children = treeToVector($5);
                                                        $$ = createNode("eventDecl", "test", children);}
                ;

    // int id;
eventTypeDecl:  types ID                                {createEntry($2.symbol, $1->symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        freeNode($1);}
                    SEMIC eventTypeDecl                 {if($5 != NULL)
                                                            children.push_back($5);
                                                        $$ = createNode($2.symbol, "test", children);}
                | /* empty */                           {$$ = NULL;}
                ;

// EVENT END

// DISPATCHER START

    // dispatch_table_t id = { ... };
dispatcher:     DISPATCH ID                             {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        //increaseScope(scopeList, maximumScope);
                                                        }
                    OPEN_B dispMult CLOSE_B
                                                        {//decreaseScope(scopeList);
                                                        children = removeBlankNodes($5);
                                                        $$ = createNode("dispatcherDecl", "test", children);}
                ;

dispMult:       dispMult dispDecl                       {children.push_back($1);
                                                        children.push_back($2);
                                                        $$ = createNode("", "test", children);}
                | dispDecl                              {$$ = $1;}
                ;

    // id -> {...};
dispDecl:       ID ARROW OPEN_B processorIds CLOSE_B SEMIC
                                                        {if(noEventDispatcher(symbolTable, $1.symbol, yylval.token.line, yylval.token.column))
                                                            YYABORT;
                                                        children = treeToVector($4);
                                                        $$ = createNode($1.symbol, "test", children);}
                ;

processorIds:   ID COMMA processorIds                   {if(noProcDispatcher(symbolTable, $1.symbol, yylval.token.line, yylval.token.column))
                                                            YYABORT;
                                                        children = removeBlankNodes($3);
                                                        $$ = createNode($1.symbol, "test", children);}
                | ID                                    {if(noProcDispatcher(symbolTable, $1.symbol, yylval.token.line, yylval.token.columnBegin))
                                                            YYABORT;
                                                        $$ = createNode($1.symbol, "test", emptyVector);}
                ;

// DISPATCHER END

// PROCESSOR START

processorOrType: structDecl                             {$$ = $1;}
                | comFunction                           {$$ = $1;}
                ;

// check this later
    // struct proc_out_t { ... }
structDecl:     /*STRUCT_T PROC_OUT_T                     {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        increaseScope(scopeList, maximumScope);}
                    OPEN_B contVariables CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($5);
                                                        $$ = createNode("structDecl", "test", children);}
                | */
                STRUCT_T ID OPEN_B                      {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        //increaseScope(scopeList, maximumScope);
                                                        whereDeclared = $2.symbol;}
                    contVariables CLOSE_B
                                                        {//decreaseScope(scopeList);
                                                        whereDeclared = "";
                                                        children = removeBlankNodes($5);
                                                        $$ = createNode("structDecl", "test", children);}
                ;

    // proc_out_t id (id id) { ... }
/*processorDecl:  PROC_OUT_T ID                           {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);}
                    OPEN_P ID ID COMMA ID ID CLOSE_P
                                                        {increaseScope(scopeList, maximumScope);}
                    OPEN_B comMultStmt CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($13);
                                                        $$ = createNode("processorDecl", "test", children);}
                ;
*/

// PROCESSOR END

// CONTEXT START

    // context_t id { ... }
context:        CONTEXT_T ID                            {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        //increaseScope(scopeList, maximumScope);
                                                        whereDeclared = $2.symbol;}
                    OPEN_B contVariables CLOSE_B
                                                        {//decreaseScope(scopeList);
                                                        whereDeclared = "";
                                                        children = removeBlankNodes($5);
                                                        $$ = createNode("contextDecl", "test", children);}
                ;

    // int id;
contVariables:  varDecl SEMIC contVariables             {children = removeBlankNodes($3);
                                                        children.insert(children.begin(), $1);
                                                        $$ = createNode("", "test", children);}
                | /* empty */                           {$$ = createNode("", "test", emptyVector);}
                ;

// CONTEXT END

// SCHEDULER START

    // scheduler_t id { ... }
scheduler:      SCHEDULER_T ID                          {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        increaseScope(scopeList, maximumScope);}
                    OPEN_B queues /*nextEvent*/ comFunction CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($5);
                                                        children.push_back($6);
                                                        $$ = createNode("schedulerDecl", "test", children);}
                ;

// QUEUE START

queues:         queues queueAndDrop                     {children = removeBlankNodes($2);
                                                        children.insert(children.begin(), $1);
                                                        $$ = createNode("", "test", children);}
                | queueAndDrop                          {$$ = $1;}
                ;

queueAndDrop:   /*dropDecl*/comFunction                 {children.push_back($1);
                                                        $$ = createNode("", "test", children);}
                | queueDecl                             {children.push_back($1);
                                                        $$ = createNode("", "test", children);}
                //| enquDecl
                ;

    // queue_t<id> id (const, const, id); 
queueDecl:      QUEUE_T LESSER_OP ID GREATER_OP ID      {createEntry($5.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        updateTypeEntry(symbolTable, $5.symbol, scopeList.back(), $3.symbol);}
                    OPEN_P CONST_INT COMMA CONST_INT COMMA ID CLOSE_P SEMIC
                                                        {helper = createNode($5.symbol, "test", emptyVector);
                                                        children.push_back(helper);
                                                        $$ = createNode("queueDecl", "test", children);}
                ;

    // int id (queue_t id, id id) { ... }
/*dropDecl:       INT_T ID                                {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);}
                    OPEN_P QUEUE_T ID COMMA ID ID CLOSE_P
                                                        {increaseScope(scopeList, maximumScope);}
                    OPEN_B /*dropMultStmt comMultStmt CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($13);
                                                        $$ = createNode("dropDecl", "test", children);}
                ;
*/

// QUEUES END

// SCHEDULLER DEFAULT FUNCTIONS START

    // bool enqueue (event id) { ... }
/*
enquDecl:       BOOL_T ENQUEUE                          {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);}
                    OPEN_P EVENT ID CLOSE_P             {increaseScope(scopeList, maximumScope);}
                    OPEN_B comMultStmt CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($10);
                                                        $$ = createNode("enqueueDecl", "test", children);}
                ;
*/

    // event_t next_event () { ... }
/*nextEvent:      EVENT_T NEXT_EVENT                      {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);}
                    OPEN_P nextParam CLOSE_P
                                                        {increaseScope(scopeList, maximumScope);}
                    OPEN_B comMultStmt CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($9);
                                                        $$ = createNode("nextEventDecl", "test", children);}
                ;

nextParam:      nextParam COMMA QUEUE_T ID              {$$ = NULL;}
                | QUEUE_T ID                            {$$ = NULL;}
                ;
*/

// SCHEDULLER DEFAULT FUNCTIONS END

// SCHEDULLER END

// COMMON GRAMMAR START

comFunction:    types ID                                {createEntry($2.symbol, $1->symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        increaseScope(scopeList, maximumScope);
                                                        paramType.clear();
                                                        functionType = $1->symbol;}
                    OPEN_P argsOrNot CLOSE_P            {updateFunctionEntry(symbolTable, $2.symbol, scopeList.end()[-2], paramCounter, paramType);}
                    OPEN_B comMultStmt CLOSE_B          {decreaseScope(scopeList);
                                                        paramCounter = 0;
                                                        functionType = "";
                                                        freeNode($1);
                                                        /*children = removeBlankNodes($4);
                                                        helper2 = createNode("funcArgs", "test", children);*/
                                                        children = removeBlankNodes($9);
                                                        helper = createNode("funcStmts", "test", children);
                                                        children.push_back(helper);
                                                        //children.push_back(helper2);
                                                        $$ = createNode($2.symbol, "test", children);}
                ;

argsOrNot:      funcArgs                                {$$ = NULL;}
                | /* empty */                           {$$ = NULL;}
                ;

funcArgs:       funcArgs COMMA varDecl                  {/*children = removeBlankNodes($1);
                                                        children.push_back($3);
                                                        $$ = createNode("", "test", children);*/
                                                        paramCounter++;
                                                        freeNode($3);
                                                        $$ = NULL;}
                | varDecl                               {/*$$ = $1;*/
                                                        freeNode($1);
                                                        paramCounter++;
                                                        $$ = NULL;
                                                        }
                // Used in drop functions
                | EVENT ID                              {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        paramCounter++;
                                                        $$ = NULL;}
                | funcArgs COMMA EVENT ID               {createEntry($4.symbol, $3.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        paramCounter++;
                                                        $$ = NULL;}
                ;

comMultStmt:    comMultStmt commonStmt                  {children.push_back($1);
                                                        children.push_back($2);
                                                        $$ = createNode("", "test", children);}
                | commonStmt                            {$$ = $1;}
                ;

commonStmt:     conditionDecl                           {$$ = $1;}
                | comLoop                               {$$ = $1;}
                | dropLoop                              {$$ = $1;}
                | attribution SEMIC                     {$$ = $1;}
                | return SEMIC                          {$$ = $1;}
                | varDecl SEMIC                         {$$ = $1;}
                | BREAK SEMIC                           {if(breakChecker(numberLoops, yylval.token.line, yylval.token.columnBegin))
                                                            YYABORT;
                                                        $$ = createNode("break", "", children);}
                ;

conditionDecl:  IF                                      {increaseScope(scopeList, maximumScope);}
                    OPEN_P argCondition comCondition
                                                        {children.push_back($4);
                                                        helper = createNode("ifArg", "test", children);
                                                        children.push_back(helper);
                                                        vector<struct Node*> aux = removeBlankNodes($5);
                                                        for(auto node : aux)
                                                            children.push_back(node);
                                                        $$ = createNode("if", "test", children);}
                ;

argCondition:   varDecl                                 {$$ = $1;}
                | attribution                           {$$ = $1;}
                ;

comCondition:   CLOSE_P bracketsOrNot
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($2);
                                                        helper = createNode("then", "test", children);
                                                        children.push_back(helper);
                                                        $$ = createNode("", "test", children);}

                | CLOSE_P bracketsOrNot ELSE            {decreaseScope(scopeList);
                                                        increaseScope(scopeList, maximumScope);}
                    bracketsOrNot      
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($2);
                                                        helper = createNode("then", "test", children);
                                                        children = removeBlankNodes($5);
                                                        helper2 = createNode("else", "test", children);
                                                        children.push_back(helper);
                                                        children.push_back(helper2);
                                                        $$ = createNode("", "test", children);}
                ;

    // foreach id in id { ... }
dropLoop:       FOREACH                                 {increaseScope(scopeList, maximumScope);
                                                        numberLoops++;}
                    OPEN_P ID IN idVariations CLOSE_P bracketsOrNot
                                                        {numberLoops--;
                                                        decreaseScope(scopeList);
                                                        children = removeBlankNodes($8);
                                                        helper = createNode("loopStmts", "test", children);
                                                        helper2 = createNode($4.symbol, "test", emptyVector);
                                                        children.push_back(helper2);
                                                        children.push_back($6);
                                                        helper4 = createNode("loopArgs", "test", children);
                                                        children.push_back(helper4);
                                                        children.push_back(helper);
                                                        $$ = createNode("foreach", "test", children);}
                ;

    // for ( ... ) { ... }
comLoop:        FOR                                     {increaseScope(scopeList, maximumScope);
                                                        numberLoops++;}
                    OPEN_P loopArgs CLOSE_P bracketsOrNot
                                                        {numberLoops--;
                                                        decreaseScope(scopeList);
                                                        children = removeBlankNodes($6);
                                                        helper = createNode("loopStmts", "test", children);
                                                        children.push_back($4);
                                                        children.push_back(helper);
                                                        $$ = createNode("for", "test", children);}
                ;

bracketsOrNot:  OPEN_B comMultStmt CLOSE_B              {$$ = $2;}
                | commonStmt                            {$$ = $1;}
                ;

loopArgs:       firstArgument SEMIC argument SEMIC argument 
                                                        {children.push_back($1);
                                                        children.push_back($3);
                                                        children.push_back($5);
                                                        $$ = createNode("loopArgs", "test", children);}
                ;

firstArgument:  varDecl                                 {$$ = $1;}
                | attribution                           {$$ = $1;}
                | /* empty */                           {$$ = createNode("empty", "test", emptyVector);}
                ;

argument:       attribution                             {$$ = $1;}
                | /* empty */                           {$$ = createNode("empty", "test", emptyVector);}
                ;

return:         RETURN attribution                      {if(returnChecker(functionType, $2->type, yylval.token.line, yylval.token.columnBegin))
                                                            YYABORT;
                                                        children.push_back($2);
                                                        $$ = createNode($1.symbol, "", children);}
                ;

varDecl:        types ID                                {if(alreadyDeclared(symbolTable, $2.symbol, scopeList.back(), whereDeclared, yylval.token.line, yylval.token.columnBegin))
                                                            YYABORT;
                                                        createEntry($2.symbol, $1->symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        if($1->type == "") {
                                                            string type = findDeclaration(symbolTable, $1->symbol, scopeList, yylval.token.line, yylval.token.columnBegin);
                                                            updateTypeEntry(symbolTable, $2.symbol, scopeList.back(), type);
                                                        }
                                                        paramType.push_back($1->symbol);
                                                        freeNode($1);
                                                        $$ = createNode($2.symbol, $1->symbol, emptyVector);}
                | types ID                              {columnBeginDecl = yylval.token.columnBegin;}
                    ATTRIB_OP attribution               {if(alreadyDeclared(symbolTable, $2.symbol, scopeList.back(), whereDeclared, yylval.token.line, yylval.token.columnBegin))
                                                            YYABORT;
                                                        createEntry($2.symbol, $1->symbol, scopeList, yylval.token.line, columnBeginDecl, symbolTable, whereDeclared);
                                                        if($1->type == "") {
                                                            string type = findDeclaration(symbolTable, $1->symbol, scopeList, yylval.token.line, yylval.token.columnBegin);
                                                            updateTypeEntry(symbolTable, $2.symbol, scopeList.back(), type);
                                                        }
                                                        paramType.push_back($1->symbol);
                                                        helper = createNode($2.symbol, $1->symbol, emptyVector);
                                                        freeNode($1);
                                                        //children.push_back(helper);
                                                        //children.push_back($5);
                                                        //$$ = createNode($4.symbol, $1->symbol, children);
                                                        $$ = opOperations(helper, $5, $4.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | LIST_T LESSER_OP types GREATER_OP ID
                                                        {if(alreadyDeclared(symbolTable, $5.symbol, scopeList.back(), whereDeclared, yylval.token.line, yylval.token.columnBegin))
                                                            YYABORT;
                                                        createEntry($5.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        updateTypeEntry(symbolTable, $5.symbol, scopeList.back(), $3->symbol);
                                                        paramType.push_back($1.symbol);
                                                        freeNode($3);
                                                        $$ = createNode($5.symbol, $1.symbol, emptyVector);}
                /*| PROC_OUT_T ID                       {if(alreadyDeclared(symbolTable, $2.symbol, scopeList.back(), whereDeclared, yylval.token.line, yylval.token.columnBegin))
                                                            YYABORT;
                                                        createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, whereDeclared);
                                                        $$ = createNode($2.symbol, "test", emptyVector);}*/
                ;

types:          INT_T                                   {$$ = createNode($1.symbol, $1.symbol, emptyVector);}
                | FLOAT_T                               {$$ = createNode($1.symbol, $1.symbol, emptyVector);}
                | STREAM_T                              {$$ = createNode($1.symbol, $1.symbol, emptyVector);}
                | ID                                    {$$ = createNode($1.symbol, "", emptyVector);}
                | BOOL_T                                {$$ = createNode($1.symbol, $1.symbol, emptyVector);}
                | EVENT_T                               {$$ = createNode($1.symbol, $1.symbol, emptyVector);}
                | PACKET_T                              {$$ = createNode($1.symbol, $1.symbol, emptyVector);}
                | QUEUE_T                               {$$ = createNode($1.symbol, $1.symbol, emptyVector);}
                ;

attribution:    idVariations ATTRIB_OP attribution      {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | logicalOr                             {$$ = $1;}
                ;

logicalOr:      logicalOr LOGIC_OR_OP logicalAnd        {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | logicalAnd                            {$$ = $1;}
                ;

logicalAnd:     logicalAnd LOGIC_AND_OP compareExp      {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | compareExp                            {$$ = $1;}
                ;

compareExp:     compareExp RELAT_LOW_OP relationExp     {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | relationExp                           {$$ = $1;}
                ;

relationExp:    relationExp GREATER_OP lowMathExp       {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | relationExp LESSER_OP lowMathExp      {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | relationExp RELAT_HIGH_OP lowMathExp  {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | lowMathExp                            {$$ = $1;}
                ;

lowMathExp:     lowMathExp MATH_ADD_OP highMathExp      {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | lowMathExp MATH_SUB_OP highMathExp    {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | highMathExp                           {$$ = $1;}
                ;

highMathExp:    highMathExp MATH_HIGH_OP unaryExp       {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | unaryExp                              {$$ = $1;}
                ;


unaryExp:       LOGIC_NOT_OP unaryExp                   {resultType = checkType($2->type, "", $1.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if(resultType.empty())
                                                            YYABORT;
                                                        children.push_back($2);
                                                        $$ = createNode($1.symbol, resultType, children);}
                | MATH_SUB_OP unaryExp                  {resultType = checkType($2->type, "", $1.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if(resultType.empty())
                                                            YYABORT;
                                                        children.push_back($2);
                                                        $$ = createNode($1.symbol, resultType, children);}
                | TYPE OPEN_P unaryExp CLOSE_P          {resultType = findDeclaration(symbolTable, $3->symbol, scopeList, yylval.token.line, yylval.token.columnBegin);
                                                        resultType = typeBuiltIn($3->type, $3->symbol, scopeList, symbolTable);
                                                        children.push_back($3);
                                                        $$ = createNode($1.symbol, resultType, children);}
                | BYTES OPEN_P unaryExp CLOSE_P         {children.push_back($3);
                                                        $$ = createNode($1.symbol, "stream", children);}
                | element                               {$$ = $1;}
                ;

element:        idVariations                            {$$ = $1;}
                | CONST_INT                             {$$ = createNode($1.symbol, "int", emptyVector);}
                | CONST_FLOAT                           {$$ = createNode($1.symbol, "float", emptyVector);}
                | FALSE                                 {$$ = createNode($1.symbol, "bool", emptyVector);}
                | TRUE                                  {$$ = createNode($1.symbol, "bool", emptyVector);}
                | OPEN_P attribution CLOSE_P            {$$ = $2;}
                | TIME OPEN_P CLOSE_P                   {$$ = createNode($1.symbol, "float", emptyVector);}
                | TIMER DOT timerOps OPEN_P CLOSE_P     {helper = createNode($1.symbol, "", emptyVector);
                                                        children.push_back(helper);
                                                        helper2 = createNode($3->symbol, "", emptyVector);
                                                        children.push_back(helper2);
                                                        $$ = createNode($2.symbol, "", children);}
                | NEW_PKT OPEN_P CLOSE_P                {$$ = createNode($1.symbol, "pkt_t", emptyVector);}
                ;

timerOps:       SET_DURATION                            {$$ = createNode($1.symbol, "", emptyVector);}
                | START                                 {$$ = createNode($1.symbol, "", emptyVector);}
                | STOP                                  {$$ = createNode($1.symbol, "", emptyVector);}
                | RESTART                               {$$ = createNode($1.symbol, "", emptyVector);}
                ;

idVariations:   idVariations DOT squareBrackets         {resultType = structCheck(symbolTable, $1->symbol, $3, scopeList, yylval.token.line, yylval.token.columnBegin);
                                                        if(resultType == "error")
                                                            YYABORT;
                                                        children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, resultType, children);}
                | idVariations DOT builtInFunc OPEN_P CLOSE_P
                                                        {resultType = builtinChecker(symbolTable, $3->symbol, $1, NULL, yylval.token.line, yylval.token.columnBegin, scopeList);
                                                        if(resultType == "error")
                                                            YYABORT;
                                                        children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, resultType, children);}
                | idVariations DOT builtInFunc OPEN_P attribution CLOSE_P
                                                        {resultType = builtinChecker(symbolTable, $3->symbol, $1, $5, yylval.token.line, yylval.token.columnBegin, scopeList);
                                                        if(resultType == "error")
                                                            YYABORT;
                                                        children.push_back($5);
                                                        helper = createNode($3->symbol, resultType, children);
                                                        freeNode($3);
                                                        children.push_back($1);
                                                        children.push_back(helper);
                                                        $$ = createNode($2.symbol, resultType, children);}
                /*| idVariations DOT builtInFunc LESSER_OP ID GREATER_OP OPEN_P CLOSE_P
                                                        {helper = createNode($5.symbol, "test", emptyVector);
                                                        helper2 = createNode($3->symbol, "test", children);
                                                        freeNode($3);
                                                        children.push_back($1);
                                                        children.push_back(helper2);
                                                        children.push_back(helper);
                                                        $$ = createNode($2.symbol, "test", children);}*/
                | idVariations ARROW squareBrackets     {resultType = structCheck(symbolTable, $1->symbol, $3, scopeList, yylval.token.line, yylval.token.columnBegin);
                                                        if(resultType == "error")
                                                            YYABORT;
                                                        children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, resultType, children);}
                | squareBrackets                        {$$ = $1;}
                ;

                // id.add(...)
builtInFunc:    ADD                                     {$$ = createNode($1.symbol, "", emptyVector);}
                // id.add_hdr(...)
                | ADD_HDR                               {$$ = createNode($1.symbol, "", emptyVector);}
                // id.get_hdr<id>()
                | GET_HDR                               {$$ = createNode($1.symbol, "", emptyVector);}
                // id.add_data(...)
                | ADD_DATA                              {$$ = createNode($1.symbol, "", emptyVector);}
                // id.get_data()
                | GET_DATA                              {$$ = createNode($1.symbol, "", emptyVector);}
                // id.push(...)
                | PUSH                                  {$$ = createNode($1.symbol, "", emptyVector);}
                // id.pop()
                | POP                                   {$$ = createNode($1.symbol, "", emptyVector);}
                // id.len()
                | LENGTH                                {$$ = createNode($1.symbol, "", emptyVector);}
                ;

squareBrackets: squareBrackets OPEN_S sliceExp CLOSE_S
                                                        {vector<string> objType;
                                                        objType.push_back(findDeclaration(symbolTable, $1->symbol, scopeList, yylval.token.line, yylval.token.columnBegin));
                                                        resultType = indexChecker(objType, $3->type, yylval.token.line, yylval.token.columnBegin);
                                                        if(resultType == "error")
                                                            YYABORT;
                                                        children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode("[]", resultType, children);}
                | ID                                    {resultType = findDeclaration(symbolTable, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin);
                                                        if(resultType == "error")
                                                            YYABORT;
                                                        $$ = createNode($1.symbol, resultType, emptyVector);}
                ;

sliceExp:       sliceExp SLICE_OP logicalOr             {$$ = opOperations($1, $3, $2.symbol, yylval.token.line, yylval.token.columnBegin);
                                                        if($$ == NULL)
                                                            YYABORT;}
                | logicalOr                             {$$ = $1;}
                ;

// COMMON GRAMMAR END
%%

struct Node* opOperations(struct Node* arg1, struct Node* arg2, string op, int line, int column) {
    resultType = checkType(arg1->type, arg2->type, op, line, column);
    if(resultType == "error")
        return NULL;
    children.push_back(arg1);
    children.push_back(arg2);
    return createNode(op, resultType, children);
}

void yyerror(const char *error){
    cout << error << "\nLine: " << yylval.token.line
    << " Column: " << yylval.token.column << endl;
}

int main(int arc, char **argv) {
    scopeList.push_back(maximumScope);
    FILE *fp = fopen(argv[1], "r");
    if(fp) {
        yyin = fp;
        yyparse();
    } else {
        printf("Wrong file input\n");
        return 1;
    }
    fclose(fp);
    yylex_destroy();

    return 0;
}