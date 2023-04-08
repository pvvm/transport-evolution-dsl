%define parse.error verbose
%define lr.type canonical-lr

%{
#include "list_tree.hpp"

extern int yylex(void);
extern int yylex_destroy(void);
extern char * yytext;
extern FILE *yyin;
void yyerror(const char *);

vector<struct Node*> children;
vector<struct Node*> emptyVector;
%}

%code requires {
    struct token {
        char symbol[50];
        int line;
        int column;
    };
}

%union {
    struct token token;
    struct Node* node;
}

%token <token> INT_T FLOAT_T BOOL_T STREAM_T EVENT EVENT_T QUEUE_T SCHEDULER_T DISPATCH LIST_T PACKET_T
%token <token> PROC_OUT_T STRUCT_T CONTEXT_T HEADER CONST_INT CONST_FLOAT MATH_HIGH_OP MATH_ADD_OP TRUE FALSE
%token <token> MATH_SUB_OP LOGIC_OR_OP LOGIC_AND_OP LOGIC_NOT_OP GREATER_OP LESSER_OP RELAT_HIGH_OP
%token <token> RELAT_LOW_OP SLICE_OP ATTRIB_OP IF ELSE FOR FOREACH TIME IN RETURN TYPE LENGTH NEW_PKT
%token <token> ADD_DATA ADD_HDR GET_HDR ADD NEXT_EVENT /*ENQUEUE*/ PUSH ID OPEN_B CLOSE_B OPEN_S CLOSE_S
%token <token> OPEN_P CLOSE_P DOT COMMA SEMIC ARROW

%type <node> program declarations headerDecl dispatcher dispMult dispDecl
%type <node> processorIds processorMult processorOrType processorType procTypeDecl
%type <node> processorDecl context contVariables scheduler queues queueAndDrop
%type <node> queueType queueTypeDecl queueDecl dropDecl
%type <node> enquDecl nextEvent nextParam dropMultStmt dropStmt comMultStmt
%type <node> commonStmt dropCondition comCondition dropLoop comLoop loopArgs
%type <node> firstArgument argument return varDecl types
%type <node> attribution logicalOr logicalAnd compareExp relationExp
%type <node> lowMathExp highMathExp unaryExp element idVariations squareBrackets sliceExp

%start program

%%

program:        declarations                            {children = $1->children;
                                                        delete $1;
                                                        $$ = createNode("program", children);
                                                        fstream file;
                                                        file.open("tree_result.txt", ios::out);
                                                        printTree($$, 0, file);
                                                        freeTree($$);}
                | /* empty */                           {$$ = NULL;}
                ;

declarations:   headerDecl scheduler dispatcher processorMult context
                                                        {children = removeBlankNodes($4);
                                                        children.insert(children.begin(), $3);
                                                        children.insert(children.begin(), $2);
                                                        children.insert(children.begin(), $1);
                                                        children.push_back($5);
                                                        $$ = createNode("", children);}
                ;

// HEADER START

headerDecl:     HEADER ID OPEN_B contVariables CLOSE_B
                                                        {children = treeToVector($4);
                                                        $$ = createNode("headerDecl", children);}
                ;

// HEADER END

// DISPATCHER START

    // dispatch_table_t id = { ... };
dispatcher:     DISPATCH ID OPEN_B dispMult CLOSE_B
                                                        {children = removeBlankNodes($4);
                                                        //struct Node * helper = createNode($2.symbol, children);
                                                        //children.push_back(helper);
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

// DISPATCHER END

// PROCESSOR START

processorIds:   ID COMMA processorIds                   {children = removeBlankNodes($3);
                                                        $$ = createNode($1.symbol, children);}
                | ID                                    {$$ = createNode($1.symbol, emptyVector);}
                ;

processorMult:  processorMult processorOrType           {children = removeBlankNodes($2);
                                                        children.insert(children.begin(), $1);
                                                        $$ = createNode("", children);}
                | processorOrType                       {$$ = $1;}
                ;

processorOrType: processorType                          {$$ = $1;}
                | processorDecl                         {$$ = $1;}
                ;

    // struct proc_out_t { ... }
processorType:  STRUCT_T PROC_OUT_T OPEN_B procTypeDecl CLOSE_B
                                                        {children = treeToVector($4);
                                                        $$ = createNode("structDecl", children);}
                ;

    // list<event> id;
procTypeDecl:   LIST_T LESSER_OP EVENT GREATER_OP ID SEMIC procTypeDecl
                                                        {children.push_back($7);
                                                        $$ = createNode($5.symbol, children);}
                | LIST_T LESSER_OP EVENT GREATER_OP ID SEMIC
                                                        {$$ = createNode($5.symbol, emptyVector);}
                | LIST_T LESSER_OP PACKET_T GREATER_OP ID SEMIC procTypeDecl
                                                        {children.push_back($7);
                                                        $$ = createNode($5.symbol, children);}
                | LIST_T LESSER_OP PACKET_T GREATER_OP ID SEMIC
                                                        {$$ = createNode($5.symbol, emptyVector);}
                ;

    // proc_out_t id (id id) { ... }
processorDecl:  PROC_OUT_T ID OPEN_P ID ID COMMA ID ID CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {children = removeBlankNodes($11);
                                                        $$ = createNode("processorDecl", children);}
                ;

// PROCESSOR END

// CONTEXT START

    // context_t id { ... }
context:        CONTEXT_T ID OPEN_B contVariables CLOSE_B
                                                        {children = treeToVector($4);
                                                        $$ = createNode("contextDecl", children);}
                ;

    // int id;
contVariables:  types ID SEMIC contVariables            {children.push_back($4);
                                                        $$ = createNode($2.symbol, children);}
                | types ID SEMIC                        {$$ = createNode($2.symbol, emptyVector);}
                ;

// CONTEXT END

// SCHEDULER START

    // scheduler_t id { ... }
scheduler:      SCHEDULER_T ID OPEN_B queues nextEvent CLOSE_B
                                                        {children = removeBlankNodes($4);
                                                        children.push_back($5);
                                                        //struct Node * helper = createNode($2.symbol, children);
                                                        //children.push_back(helper);
                                                        $$ = createNode("schedulerDecl", children);}
                ;

// QUEUE START

queues:         queues queueAndDrop                     {children = removeBlankNodes($2);
                                                        children.insert(children.begin(), $1);
                                                        $$ = createNode("", children);}
                | queueAndDrop                          {$$ = $1;}
                ;

queueAndDrop:   queueType                               {children.push_back($1);
                                                        $$ = createNode("", children);}
                | dropDecl                              {children.push_back($1);
                                                        $$ = createNode("", children);}
                | queueDecl                             {children.push_back($1);
                                                        $$ = createNode("", children);}
                | enquDecl
                ;

    // event id { ... };
queueType:      EVENT ID OPEN_B queueTypeDecl CLOSE_B
                                                        {children = treeToVector($4);
                                                        //struct Node * helper = createNode($2.symbol, children);
                                                        //children.push_back(helper);
                                                        $$ = createNode("eventDecl", children);}
                ;

    // int id;
queueTypeDecl:  types ID SEMIC queueTypeDecl            {children.push_back($4);
                                                        $$ = createNode($2.symbol, children);}
                | types ID SEMIC                        {$$ = createNode($2.symbol, emptyVector);}
                ;

    // queue_t<id> id (const, const, id); 
queueDecl:      QUEUE_T LESSER_OP ID GREATER_OP ID OPEN_P CONST_INT COMMA CONST_INT COMMA ID CLOSE_P SEMIC
                                                        {struct Node * helper = createNode($5.symbol, emptyVector);
                                                        children.push_back(helper);
                                                        $$ = createNode("queueDecl", children);}
                ;

    // int id (queue_t id, id id) { ... }
dropDecl:       INT_T ID OPEN_P QUEUE_T ID COMMA ID ID CLOSE_P OPEN_B dropMultStmt CLOSE_B
                                                        {children = removeBlankNodes($11);
                                                        //struct Node * helper = createNode($2.symbol, children);
                                                        //children.push_back(helper);
                                                        $$ = createNode("dropDecl", children);}
                ;

// QUEUES END

// SCHEDULLER DEFAULT FUNCTIONS START

    // bool enqueue (event id) { ... }
enquDecl:       BOOL_T ID /*ENQUEUE*/ OPEN_P EVENT ID CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {children = removeBlankNodes($8);
                                                        $$ = createNode("enqueueDecl", children);}
                ;

    // event_t next_event () { ... }
nextEvent:      EVENT_T NEXT_EVENT OPEN_P nextParam CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {children = removeBlankNodes($7);
                                                        $$ = createNode("nextEventDecl", children);}
                ;

nextParam:      nextParam COMMA QUEUE_T ID              {$$ = NULL;}
                | QUEUE_T ID                            {$$ = NULL;}
                ;

// SCHEDULLER DEFAULT FUNCTIONS END

// SCHEDULLER END

// COMMON GRAMMAR START

dropMultStmt:   dropMultStmt dropStmt                   {children.push_back($1);
                                                        children.push_back($2);
                                                        $$ = createNode("", children);}
                | dropStmt                              {$$ = $1;}
                ;

dropStmt:       dropCondition                           {$$ = $1;}
                | dropLoop                              {$$ = $1;}
                | attribution SEMIC                     {$$ = $1;}
                | return SEMIC                          {$$ = $1;}
                | varDecl SEMIC                         {$$ = $1;}
                ;

comMultStmt:    comMultStmt commonStmt                  {children.push_back($1);
                                                        children.push_back($2);
                                                        $$ = createNode("", children);}
                | commonStmt                            {$$ = $1;}
                ;

commonStmt:     comCondition                            {$$ = $1;}
                | comLoop                               {$$ = $1;}
                | attribution SEMIC                     {$$ = $1;}
                | return SEMIC                          {$$ = $1;}
                | varDecl SEMIC                         {$$ = $1;}
                ;

    // if ( ... ) { ... }
    // if ( ... ) { ... } else { ... }
dropCondition:   IF OPEN_P attribution CLOSE_P OPEN_B dropMultStmt CLOSE_B
                                                        {children.push_back($3);
                                                        struct Node * helper = createNode("ifArg", children);
                                                        children = removeBlankNodes($6);
                                                        struct Node * helper2 = createNode("ifStmts", children);
                                                        children.push_back(helper);
                                                        children.push_back(helper2);
                                                        $$ = createNode("if", children);}
                | IF OPEN_P attribution CLOSE_P OPEN_B dropMultStmt CLOSE_B ELSE OPEN_B dropMultStmt CLOSE_B
                                                        {children.push_back($3);
                                                        struct Node * helper = createNode("ifArg", children);
                                                        children = removeBlankNodes($6);
                                                        struct Node * helper2 = createNode("ifStmts", children);
                                                        children = removeBlankNodes($10);
                                                        struct Node * helper3 = createNode("elseStmts", children);
                                                        children.push_back(helper);
                                                        children.push_back(helper2);
                                                        children.push_back(helper3);
                                                        $$ = createNode("ifelse", children);}
                ;

    // if ( ... ) { ... }
    // if ( ... ) { ... } else { ... }
comCondition:   IF OPEN_P attribution CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {children.push_back($3);
                                                        struct Node * helper = createNode("ifArg", children);
                                                        children = removeBlankNodes($6);
                                                        struct Node * helper2 = createNode("ifStmts", children);
                                                        children.push_back(helper);
                                                        children.push_back(helper2);
                                                        $$ = createNode("if", children);}

                | IF OPEN_P attribution CLOSE_P OPEN_B comMultStmt CLOSE_B ELSE OPEN_B comMultStmt CLOSE_B
                                                        {children.push_back($3);
                                                        struct Node * helper = createNode("ifArg", children);
                                                        children = removeBlankNodes($6);
                                                        struct Node * helper2 = createNode("ifStmts", children);
                                                        children = removeBlankNodes($10);
                                                        struct Node * helper3 = createNode("elseStmts", children);
                                                        children.push_back(helper);
                                                        children.push_back(helper2);
                                                        children.push_back(helper3);
                                                        $$ = createNode("ifelse", children);}
                ;

    // foreach id in id { ... }
dropLoop:       FOREACH ID IN ID OPEN_B dropMultStmt CLOSE_B
                                                        {children = removeBlankNodes($6);
                                                        struct Node * helper = createNode("loopStmts", children);
                                                        struct Node * helper2 = createNode($2.symbol, emptyVector);
                                                        struct Node * helper3 = createNode($4.symbol, emptyVector);
                                                        children.push_back(helper2);
                                                        children.push_back(helper3);
                                                        struct Node * helper4 = createNode("loopArgs", children);
                                                        children.push_back(helper4);
                                                        children.push_back(helper);
                                                        $$ = createNode("foreach", children);}
                ;

    // for ( ... ) { ... }
comLoop:        FOR OPEN_P loopArgs CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {children = removeBlankNodes($6);
                                                        struct Node * helper = createNode("loopStmts", children);
                                                        children.push_back($3);
                                                        children.push_back(helper);
                                                        $$ = createNode("for", children);}
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

varDecl:        types ID                                {$$ = createNode($2.symbol, emptyVector);}
                | types ID ATTRIB_OP attribution        {struct Node * helper = createNode($2.symbol, emptyVector);
                                                        children.push_back(helper);
                                                        children.push_back($4);
                                                        $$ = createNode($3.symbol, children);}
                | PACKET_T ID ATTRIB_OP NEW_PKT OPEN_P CLOSE_P
                                                        {struct Node * helper = createNode($2.symbol, emptyVector);
                                                        children.push_back(helper);
                                                        struct Node * helper2 = createNode($4.symbol, emptyVector);
                                                        children.push_back(helper2);
                                                        $$ = createNode($3.symbol, children);}
                | PROC_OUT_T ID                         {$$ = createNode($2.symbol, emptyVector);}
                ;

types:          INT_T                                   {$$ = NULL;}
                | FLOAT_T                               {$$ = NULL;}
                | STREAM_T                              {$$ = NULL;}
                | ID                                    {$$ = NULL;}
                | BOOL_T                                {$$ = NULL;}
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
                | LENGTH OPEN_P unaryExp CLOSE_P        {children.push_back($3);
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
                ;

idVariations:   idVariations DOT squareBrackets         {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | idVariations ARROW squareBrackets       {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode($2.symbol, children);}
                | idVariations DOT ADD OPEN_P ID CLOSE_P
                                                        {struct Node * helper = createNode($5.symbol, emptyVector);
                                                        children.push_back(helper);
                                                        struct Node * helper2 = createNode($3.symbol, children);
                                                        children.push_back($1);
                                                        children.push_back(helper2);
                                                        $$ = createNode($2.symbol, children);}
                | idVariations DOT ADD_HDR OPEN_P ID CLOSE_P
                                                        {struct Node * helper = createNode($5.symbol, emptyVector);
                                                        children.push_back(helper);
                                                        struct Node * helper2 = createNode($3.symbol, children);
                                                        children.push_back($1);
                                                        children.push_back(helper2);
                                                        $$ = createNode($2.symbol, children);}
                | idVariations DOT GET_HDR LESSER_OP ID GREATER_OP OPEN_P CLOSE_P
                                                        {struct Node * helper = createNode($5.symbol, emptyVector);
                                                        children.push_back(helper);
                                                        struct Node * helper2 = createNode($3.symbol, children);
                                                        children.push_back($1);
                                                        children.push_back(helper2);
                                                        $$ = createNode($2.symbol, children);}
                | idVariations DOT ADD_DATA OPEN_P attribution CLOSE_P
                                                        {children.push_back($5);
                                                        struct Node * helper = createNode($3.symbol, children);
                                                        children.push_back($1);
                                                        children.push_back(helper);
                                                        $$ = createNode($2.symbol, children);}
                | idVariations DOT PUSH OPEN_P attribution CLOSE_P
                                                        {children.push_back($5);
                                                        struct Node * helper = createNode($3.symbol, children);
                                                        children.push_back($1);
                                                        children.push_back(helper);
                                                        $$ = createNode($2.symbol, children);}
                | squareBrackets                        {$$ = $1;}
                ;

squareBrackets: squareBrackets OPEN_S sliceExp CLOSE_S
                                                        {children.push_back($1);
                                                        children.push_back($3);
                                                        $$ = createNode("index", children);}
                | ID                                    {$$ = createNode($1.symbol, emptyVector);}
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