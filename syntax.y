%define parse.error verbose
%define lr.type canonical-lr

%{
#include "list_tree.hpp"
#include "symbol_table.hpp"
#include "semantic.hpp"

extern int yylex(void);
extern int yylex_destroy(void);
extern char * yytext;
extern FILE *yyin;
void yyerror(const char *);

vector<struct Node*> children;
vector<struct Node*> emptyVector;
vector<struct Entry*> symbolTable;
struct Node * helper;
struct Node * helper2;
struct Node * helper3;
struct Node * helper4;

int maximumScope = 0;
vector<int> scopeList;

// Stores column where a symbol is declared, to be put on the symbol table later
int columnBeginDecl = 0;
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
%token <token> RELAT_LOW_OP SLICE_OP ATTRIB_OP IF ELSE FOR FOREACH TIME IN RETURN TYPE NEW_PKT
%token <token> LENGTH ADD_DATA ADD_HDR GET_HDR GET_DATA ADD PUSH POP BYTES /*NEXT_EVENT ENQUEUE*/ ID OPEN_B CLOSE_B OPEN_S CLOSE_S
%token <token> OPEN_P CLOSE_P DOT COMMA SEMIC ARROW TIMER SET_DURATION START STOP RESTART

%type <node> program multDecl declarations headerDecl dispatcher dispMult dispDecl
%type <node> processorIds processorOrType structDecl 
%type <node> /*processorDecl*/ context contVariables scheduler queues queueAndDrop
%type <node> queueType queueTypeDecl queueDecl /*dropDecl*/
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

FIX GET_HDR<>. IT IS CONSIDERING THEY ARE OPERATORS < AND >

*/

%start program

%%

program:        multDecl                                {children = removeBlankNodes($1);
                                                        $$ = createNode("program", children);
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
                                                        $$ = createNode("", children);}
                | declarations                          {$$ = $1;}
                ;

declarations:   /*headerDecl queueTMult scheduler dispatcher processorMult context
                                                        {children = removeBlankNodes($5);
                                                        children.insert(children.begin(), $4);
                                                        children.insert(children.begin(), $3);
                                                        vector<struct Node*> aux = removeBlankNodes($2);
                                                        children.insert(children.begin(), aux.begin(), aux.end());
                                                        children.insert(children.begin(), $1);
                                                        children.push_back($6);
                                                        $$ = createNode("", children);}*/
                headerDecl                              {$$ = $1;}
                | queueType                             {$$ = $1;}
                | scheduler                             {$$ = $1;}
                | dispatcher                            {$$ = $1;}
                | processorOrType                       {$$ = $1;}
                | context                               {$$ = $1;}
                ;

// HEADER START

headerDecl:     HEADER ID                               {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        increaseScope(scopeList, maximumScope);}
                    OPEN_B contVariables CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($5);
                                                        $$ = createNode("headerDecl", children);}
                ;

// HEADER END

// QUEUE TYPE START

    // event id { ... };
queueType:      EVENT ID                                {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        increaseScope(scopeList, maximumScope);}
                    OPEN_B queueTypeDecl CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = treeToVector($5);
                                                        $$ = createNode("eventDecl", children);}
                ;

    // int id;
queueTypeDecl:  types ID                                {createEntry($2.symbol, $1->symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        freeNode($1);}
                    SEMIC queueTypeDecl                 {if($5 != NULL)
                                                            children.push_back($5);
                                                        $$ = createNode($2.symbol, children);}
                | /* empty */                           {$$ = NULL;}
                ;

// QUEUE TYPE END

// DISPATCHER START

    // dispatch_table_t id = { ... };
dispatcher:     DISPATCH ID                             {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        increaseScope(scopeList, maximumScope);}
                    OPEN_B dispMult CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($5);
                                                        $$ = createNode("dispatcherDecl", children);}
                ;

dispMult:       dispMult dispDecl                       {children.push_back($1);
                                                        children.push_back($2);
                                                        $$ = createNode("", children);}
                | dispDecl                              {$$ = $1;}
                ;

    // id -> {...};
dispDecl:       ID ARROW OPEN_B processorIds CLOSE_B SEMIC
                                                        {children = treeToVector($4);
                                                        $$ = createNode($1.symbol, children);}
                ;

processorIds:   ID COMMA processorIds                   {children = removeBlankNodes($3);
                                                        $$ = createNode($1.symbol, children);}
                | ID                                    {$$ = createNode($1.symbol, emptyVector);}
                ;

// DISPATCHER END

// PROCESSOR START

processorOrType: structDecl                             {$$ = $1;}
                | comFunction                           {$$ = $1;}
                ;

// check this later
    // struct proc_out_t { ... }
structDecl:     /*STRUCT_T PROC_OUT_T                     {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        increaseScope(scopeList, maximumScope);}
                    OPEN_B contVariables CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($5);
                                                        $$ = createNode("structDecl", children);}
                | */
                STRUCT_T ID OPEN_B                    {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        increaseScope(scopeList, maximumScope);}
                    contVariables CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($5);
                                                        $$ = createNode("structDecl", children);}
                ;

    // proc_out_t id (id id) { ... }
/*processorDecl:  PROC_OUT_T ID                           {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");}
                    OPEN_P ID ID COMMA ID ID CLOSE_P
                                                        {increaseScope(scopeList, maximumScope);}
                    OPEN_B comMultStmt CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($13);
                                                        $$ = createNode("processorDecl", children);}
                ;
*/

// PROCESSOR END

// CONTEXT START

    // context_t id { ... }
context:        CONTEXT_T ID                            {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        increaseScope(scopeList, maximumScope);}
                    OPEN_B contVariables CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($5);
                                                        $$ = createNode("contextDecl", children);}
                ;

    // int id;
contVariables:  varDecl SEMIC contVariables             {children = removeBlankNodes($3);
                                                        children.insert(children.begin(), $1);
                                                        $$ = createNode("", children);}
                | /* empty */                           {$$ = createNode("", emptyVector);}
                ;

// CONTEXT END

// SCHEDULER START

    // scheduler_t id { ... }
scheduler:      SCHEDULER_T ID                          {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        increaseScope(scopeList, maximumScope);}
                    OPEN_B queues /*nextEvent*/ comFunction CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($5);
                                                        children.push_back($6);
                                                        $$ = createNode("schedulerDecl", children);}
                ;

// QUEUE START

queues:         queues queueAndDrop                     {children = removeBlankNodes($2);
                                                        children.insert(children.begin(), $1);
                                                        $$ = createNode("", children);}
                | queueAndDrop                          {$$ = $1;}
                ;

queueAndDrop:   /*dropDecl*/comFunction                 {children.push_back($1);
                                                        $$ = createNode("", children);}
                | queueDecl                             {children.push_back($1);
                                                        $$ = createNode("", children);}
                //| enquDecl
                ;

    // queue_t<id> id (const, const, id); 
queueDecl:      QUEUE_T LESSER_OP ID GREATER_OP ID      {createEntry($5.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");}
                    OPEN_P CONST_INT COMMA CONST_INT COMMA ID CLOSE_P SEMIC
                                                        {helper = createNode($5.symbol, emptyVector);
                                                        children.push_back(helper);
                                                        $$ = createNode("queueDecl", children);}
                ;

    // int id (queue_t id, id id) { ... }
/*dropDecl:       INT_T ID                                {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");}
                    OPEN_P QUEUE_T ID COMMA ID ID CLOSE_P
                                                        {increaseScope(scopeList, maximumScope);}
                    OPEN_B /*dropMultStmt comMultStmt CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($13);
                                                        $$ = createNode("dropDecl", children);}
                ;
*/

// QUEUES END

// SCHEDULLER DEFAULT FUNCTIONS START

    // bool enqueue (event id) { ... }
/*
enquDecl:       BOOL_T ENQUEUE                          {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");}
                    OPEN_P EVENT ID CLOSE_P             {increaseScope(scopeList, maximumScope);}
                    OPEN_B comMultStmt CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($10);
                                                        $$ = createNode("enqueueDecl", children);}
                ;
*/

    // event_t next_event () { ... }
/*nextEvent:      EVENT_T NEXT_EVENT                      {createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");}
                    OPEN_P nextParam CLOSE_P
                                                        {increaseScope(scopeList, maximumScope);}
                    OPEN_B comMultStmt CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($9);
                                                        $$ = createNode("nextEventDecl", children);}
                ;

nextParam:      nextParam COMMA QUEUE_T ID              {$$ = NULL;}
                | QUEUE_T ID                            {$$ = NULL;}
                ;
*/

// SCHEDULLER DEFAULT FUNCTIONS END

// SCHEDULLER END

// COMMON GRAMMAR START

comFunction:    types ID                                {increaseScope(scopeList, maximumScope);}
                    OPEN_P argsOrNot CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {decreaseScope(scopeList);
                                                        createEntry($2.symbol, $1->symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        freeNode($1);
                                                        /*children = removeBlankNodes($4);
                                                        helper = createNode("funcArgs", children);*/
                                                        children = removeBlankNodes($8);
                                                        helper = createNode("funcStmts", children);
                                                        children.push_back(helper);
                                                        //children.push_back(helper2);
                                                        $$ = createNode($2.symbol, children);
                                                        }
                ;

argsOrNot:      funcArgs                                {$$ = NULL;}
                | /* empty */                           {$$ = NULL;}
                ;

funcArgs:       funcArgs COMMA varDecl                  {/*children = removeBlankNodes($1);
                                                        children.push_back($3);
                                                        $$ = createNode("", children);*/
                                                        $$ = NULL;}
                | varDecl                               {/*$$ = $1;*/
                                                        $$ = NULL;}
                // Used in drop functions
                | EVENT ID                               {$$ = NULL;}
                ;

comMultStmt:    comMultStmt commonStmt                  {children.push_back($1);
                                                        children.push_back($2);
                                                        $$ = createNode("", children);}
                | commonStmt                            {$$ = $1;}
                ;

commonStmt:     conditionDecl                           {$$ = $1;}
                | comLoop                               {$$ = $1;}
                | dropLoop                              {$$ = $1;}
                | attribution SEMIC                     {$$ = $1;}
                | return SEMIC                          {$$ = $1;}
                | varDecl SEMIC                         {$$ = $1;}
                ;

conditionDecl:  IF                                      {increaseScope(scopeList, maximumScope);}
                    OPEN_P argCondition comCondition
                                                        {children.push_back($4);
                                                        helper = createNode("ifArg", children);
                                                        children.push_back(helper);
                                                        vector<struct Node*> aux = removeBlankNodes($5);
                                                        for(auto node : aux)
                                                            children.push_back(node);
                                                        $$ = createNode("if", children);}
                ;

argCondition:   varDecl                                 {$$ = $1;}
                | attribution                           {$$ = $1;}
                ;

comCondition:   CLOSE_P bracketsOrNot
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($2);
                                                        helper = createNode("then", children);
                                                        children.push_back(helper);
                                                        $$ = createNode("", children);}

                | CLOSE_P bracketsOrNot ELSE            {decreaseScope(scopeList);
                                                        increaseScope(scopeList, maximumScope);}
                    bracketsOrNot      
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($2);
                                                        helper = createNode("then", children);
                                                        children = removeBlankNodes($5);
                                                        helper2 = createNode("else", children);
                                                        children.push_back(helper);
                                                        children.push_back(helper2);
                                                        $$ = createNode("", children);}
                ;

    // foreach id in id { ... }
dropLoop:       FOREACH                                 {increaseScope(scopeList, maximumScope);}
                    OPEN_P ID IN idVariations CLOSE_P bracketsOrNot
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($8);
                                                        helper = createNode("loopStmts", children);
                                                        helper2 = createNode($4.symbol, emptyVector);
                                                        children.push_back(helper2);
                                                        children.push_back($6);
                                                        helper4 = createNode("loopArgs", children);
                                                        children.push_back(helper4);
                                                        children.push_back(helper);
                                                        $$ = createNode("foreach", children);}
                ;

    // for ( ... ) { ... }
comLoop:        FOR                                     {increaseScope(scopeList, maximumScope);}
                    OPEN_P loopArgs CLOSE_P bracketsOrNot
                                                        {decreaseScope(scopeList);
                                                        children = removeBlankNodes($6);
                                                        helper = createNode("loopStmts", children);
                                                        children.push_back($4);
                                                        children.push_back(helper);
                                                        $$ = createNode("for", children);}
                ;

bracketsOrNot:  OPEN_B comMultStmt CLOSE_B              {$$ = $2;}
                | commonStmt                            {$$ = $1;}
                ;

loopArgs:       firstArgument SEMIC argument SEMIC argument 
                                                        {children.push_back($1);
                                                        children.push_back($3);
                                                        children.push_back($5);
                                                        $$ = createNode("loopArgs", children);}
                ;

firstArgument:  varDecl                                 {$$ = $1;}
                | attribution                           {$$ = $1;}
                | /* empty */                           {$$ = createNode("empty", emptyVector);}
                ;

argument:       attribution                             {$$ = $1;}
                | /* empty */                           {$$ = createNode("empty", emptyVector);}
                ;

return:         RETURN attribution                      {children.push_back($2);
                                                        $$ = createNode($1.symbol, children);}
                ;

varDecl:        types ID                                {if(alreadyDeclared(symbolTable, $2.symbol, scopeList.back()))
                                                            cout << "OI";
                                                        createEntry($2.symbol, $1->symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        freeNode($1);
                                                        $$ = createNode($2.symbol, emptyVector);}
                | types ID                              {columnBeginDecl = yylval.token.columnBegin;}
                    ATTRIB_OP attribution               {if(alreadyDeclared(symbolTable, $2.symbol, scopeList.back()))
                                                            cout << "OI";
                                                        createEntry($2.symbol, $1->symbol, scopeList, yylval.token.line, columnBeginDecl, symbolTable, false, 0, {"test"}, "seu cu");
                                                        freeNode($1);
                                                        helper = createNode($2.symbol, emptyVector);
                                                        children.push_back(helper);
                                                        children.push_back($5);
                                                        $$ = createNode($4.symbol, children);}
                | LIST_T LESSER_OP types GREATER_OP ID
                                                        {if(alreadyDeclared(symbolTable, $5.symbol, scopeList.back()))
                                                            cout << "OI";
                                                        createEntry($5.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        freeNode($3);
                                                        $$ = createNode($5.symbol, emptyVector);}
                /*| PROC_OUT_T ID                         {if(alreadyDeclared(symbolTable, $2.symbol, scopeList.back()))
                                                            cout << "OI";
                                                        createEntry($2.symbol, $1.symbol, scopeList, yylval.token.line, yylval.token.columnBegin, symbolTable, false, 0, {"test"}, "seu cu");
                                                        $$ = createNode($2.symbol, emptyVector);}*/
                ;

types:          INT_T                                   {$$ = createNode($1.symbol, emptyVector);}
                | FLOAT_T                               {$$ = createNode($1.symbol, emptyVector);}
                | STREAM_T                              {$$ = createNode($1.symbol, emptyVector);}
                | ID                                    {$$ = createNode($1.symbol, emptyVector);}
                | BOOL_T                                {$$ = createNode($1.symbol, emptyVector);}
                | EVENT_T                               {$$ = createNode($1.symbol, emptyVector);}
                | PACKET_T                              {$$ = createNode($1.symbol, emptyVector);}
                | QUEUE_T                               {$$ = createNode($1.symbol, emptyVector);}
                ;

attribution:    idVariations ATTRIB_OP attribution      {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | logicalOr                             {$$ = $1;}
                ;

logicalOr:      logicalOr LOGIC_OR_OP logicalAnd        {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | logicalAnd                            {$$ = $1;}
                ;

logicalAnd:     logicalAnd LOGIC_AND_OP compareExp      {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | compareExp                            {$$ = $1;}
                ;

compareExp:     compareExp RELAT_LOW_OP relationExp     {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | relationExp                           {$$ = $1;}
                ;

relationExp:    relationExp GREATER_OP lowMathExp       {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | relationExp LESSER_OP lowMathExp      {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | relationExp RELAT_HIGH_OP lowMathExp  {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | lowMathExp                            {$$ = $1;}
                ;

lowMathExp:     lowMathExp MATH_ADD_OP highMathExp      {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | lowMathExp MATH_SUB_OP highMathExp    {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | highMathExp                           {$$ = $1;}
                ;

highMathExp:    highMathExp MATH_HIGH_OP unaryExp       {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | unaryExp                              {$$ = $1;}
                ;


unaryExp:       LOGIC_NOT_OP unaryExp                   {children.push_back($2);
                                                        $$ = createNode($1.symbol, children);}
                | MATH_SUB_OP unaryExp                  {children.push_back($2);
                                                        $$ = createNode($1.symbol, children);}
                | TYPE OPEN_P unaryExp CLOSE_P          {children.push_back($3);
                                                        $$ = createNode($1.symbol, children);}
                | BYTES OPEN_P unaryExp CLOSE_P         {children.push_back($3);
                                                        $$ = createNode($1.symbol, children);}
                | element                               {$$ = $1;}
                ;

element:        idVariations                            {$$ = $1;}
                | CONST_INT                             {$$ = createNode($1.symbol, emptyVector);}
                | CONST_FLOAT                           {$$ = createNode($1.symbol, emptyVector);}
                | FALSE                                 {$$ = createNode($1.symbol, emptyVector);}
                | TRUE                                  {$$ = createNode($1.symbol, emptyVector);}
                | OPEN_P attribution CLOSE_P            {$$ = $2;}
                | TIME OPEN_P CLOSE_P                   {$$ = createNode($1.symbol, emptyVector);}
                | TIMER DOT timerOps OPEN_P CLOSE_P     {helper = createNode($1.symbol, emptyVector);
                                                        children.push_back(helper);
                                                        helper2 = createNode($3->symbol, emptyVector);
                                                        children.push_back(helper2);
                                                        $$ = createNode($2.symbol, children);}
                | NEW_PKT OPEN_P CLOSE_P                {$$ = createNode($1.symbol, emptyVector);}
                ;

timerOps:       SET_DURATION                            {$$ = createNode($1.symbol, emptyVector);}
                | START                                 {$$ = createNode($1.symbol, emptyVector);}
                | STOP                                  {$$ = createNode($1.symbol, emptyVector);}
                | RESTART                               {$$ = createNode($1.symbol, emptyVector);}
                ;

idVariations:   idVariations DOT squareBrackets         {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | idVariations DOT builtInFunc OPEN_P CLOSE_P
                                                        {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | idVariations DOT builtInFunc OPEN_P attribution CLOSE_P
                                                        {children.push_back($5);
                                                        helper = createNode($3->symbol, children);
                                                        freeNode($3);
                                                        children.push_back($1);
                                                        children.push_back(helper);
                                                        $$ = createNode($2.symbol, children);}
                | idVariations DOT builtInFunc LESSER_OP ID GREATER_OP OPEN_P CLOSE_P
                                                        {helper = createNode($5.symbol, emptyVector);
                                                        helper2 = createNode($3->symbol, children);
                                                        freeNode($3);
                                                        children.push_back($1);
                                                        children.push_back(helper2);
                                                        children.push_back(helper);
                                                        $$ = createNode($2.symbol, children);}
                | idVariations ARROW squareBrackets     {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | squareBrackets                        {$$ = $1;}
                ;

                // id.add(...)
builtInFunc:    ADD                                     {$$ = createNode($1.symbol, emptyVector);}
                // id.add_hdr(...)
                | ADD_HDR                               {$$ = createNode($1.symbol, emptyVector);}
                // id.get_hdr<id>()
                | GET_HDR                               {$$ = createNode($1.symbol, emptyVector);}
                // id.add_data(...)
                | ADD_DATA                              {$$ = createNode($1.symbol, emptyVector);}
                // id.get_data()
                | GET_DATA                              {$$ = createNode($1.symbol, emptyVector);}
                // id.push(...)
                | PUSH                                  {$$ = createNode($1.symbol, emptyVector);}
                // id.pop()
                | POP                                   {$$ = createNode($1.symbol, emptyVector);}
                // id.length()
                | LENGTH                                {$$ = createNode($1.symbol, emptyVector);}
                ;

squareBrackets: squareBrackets OPEN_S sliceExp CLOSE_S
                                                        {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode("[]", children);}
                | ID                                    {//if(notDeclared(symbolTable, $1.symbol, scopeList.back()))
                                                        //    cout << "OI";;
                                                        $$ = createNode($1.symbol, emptyVector);}
                ;

sliceExp:       sliceExp SLICE_OP logicalOr             {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | logicalOr                             {$$ = $1;}
                ;

// COMMON GRAMMAR END
%%

void yyerror(const char *error){
    cout << "Error:" << error << "\nLine:" << yylval.token.line
    << "\nColumn:" << yylval.token.column << endl;
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