%define parse.error verbose
%define lr.type canonical-lr

%{
#include <stdio.h>
#include "list_tree.h"

extern int yylex(void);
extern int yylex_destroy(void);
extern char * yytext;
extern FILE *yyin;
void yyerror(const char *);

struct ListNode * root;
struct ListNode * helper;
struct ListNode * helper2;
struct ListNode * helper3;
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
    struct ListNode* node;
}

%token <token> INT_T BOOL_T EVENT_T QUEUE_T SCHEDULER_T DISPATCH_T_T
%token <token> PROCESSOR_T STATE_R_T CONST_INT MATH_HIGH_OP MATH_ADD_OP
%token <token> MATH_SUB_OP LOGIC_OR_OP LOGIC_AND_OP LOGIC_NOT_OP GREATER_OP
%token <token> LESSER_OP RELAT_HIGH_OP RELAT_LOW_OP ATTRIB_OP IF ELSE FOR FOREACH
%token <token> IN RETURN TYPE NEXT_EVENT ENQUEUE ID OPEN_B CLOSE_B OPEN_P CLOSE_P
%token <token> COMMA SEMIC ARROW

%type <node> program declarations dispatcher dispMult dispDecl
%type <node> processorIds processorMult processorDecl stateRecord
%type <node> srVariables scheduler queues queueAndDrop qTypeDecl
%type <node> queueType queueTypeDecl queueDecl dropDecl dropFunc
%type <node> enquFunc nextEvent dropMultStmt dropStmt comMultStmt
%type <node> commonStmt dropCondition comCondition dropLoop comLoop loopArgs
%type <node> firstArgument argument return varDecl
%type <node> attribution logicalOr logicalAnd compareExp relationExp
%type <node> lowMathExp highMathExp unaryExp element

%start program

%%

program:        declarations                            {$$ = createNode("program", $1, NULL);
                                                        printTree($$, 0);
                                                        freeTree($$);}
                | /* empty */                           {$$ = NULL;}
                ;

declarations:   scheduler dispatcher processorMult stateRecord
                                                        {helper = createNode("", $4, NULL);
                                                        helper2 = createNode("", $3, helper);
                                                        helper3 = createNode("", $2, helper2);
                                                        $$ = createNode("", $1, helper3);}
                ;

dispatcher:     DISPATCH_T_T ID ATTRIB_OP OPEN_B dispMult CLOSE_B SEMIC
                                                        {helper = createNode($2.symbol, $5, NULL);
                                                        $$ = createNode("dispatcherDecl", helper, NULL);}
                ;

dispMult:       dispMult dispDecl                       {$1->next = $2;
                                                        $$ = $1;}
                | dispDecl                              {$$ = $1;}
                ;

dispDecl:       ID ARROW OPEN_B processorIds CLOSE_B SEMIC
                                                        {$$ = createNode($1.symbol, $4, NULL);}
                ;

processorIds:   ID COMMA processorIds                   {$$ = createNode($1.symbol, NULL, $3);}
                | ID                                    {$$ = createNode($1.symbol, NULL, NULL);}
                ;

processorMult:  processorMult processorDecl             {helper = createNode("", $2, NULL);
                                                        $$ = createNode("", $1, helper);}
                | processorDecl                         {$$ = $1;}
                ;

processorDecl:  PROCESSOR_T ID OPEN_P EVENT_T ID CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {helper = createNode($2.symbol, $8, NULL);
                                                        $$ = createNode("processorDecl", helper, NULL);}
                ;

stateRecord:    STATE_R_T ID OPEN_B srVariables CLOSE_B
                                                        {helper = createNode($2.symbol, $4, NULL);
                                                        $$ = createNode("stateRecordDecl", helper, NULL);}
                ;

srVariables:    INT_T ID SEMIC srVariables              {$$ = createNode($2.symbol, NULL, $4);}
                | INT_T ID SEMIC                        {$$ = createNode($2.symbol, NULL, NULL);}
                ;

scheduler:      SCHEDULER_T ID OPEN_B queues enquFunc nextEvent CLOSE_B
                                                        {helper = createNode("", $6, NULL);
                                                        helper2 = createNode("", $5, helper);
                                                        helper = createNode("", $4, helper2);
                                                        helper3 = createNode($2.symbol, helper, NULL);
                                                        $$ = createNode("schedulerDecl", helper3, NULL);}
                ;

queues:         queues queueAndDrop                     {helper = createNode("", $2, NULL);
                                                        $$ = createNode("", $1, helper);}
                | queueAndDrop                          {$$ = $1;}
                ;

queueAndDrop:   qTypeDecl dropDecl queueDecl            {helper = createNode("", $3, NULL);
                                                        helper2 = createNode("", $2, helper);
                                                        $$ = createNode("", $1, helper2);}
                ;

qTypeDecl:      queueType                               {$$ = $1;}
                | /* empty */                           {$$ = NULL;}
                ;

queueType:      EVENT_T ID OPEN_B queueTypeDecl CLOSE_B SEMIC
                                                        {helper = createNode($2.symbol, $4, NULL);
                                                        $$ = createNode("eventDecl", helper, NULL);}
                ;

queueTypeDecl:  INT_T ID SEMIC queueTypeDecl            {$$ = createNode($2.symbol, NULL, $4);}
                | INT_T ID SEMIC                        {$$ = createNode($2.symbol, NULL, NULL);}
                ;

queueDecl:      QUEUE_T LESSER_OP ID GREATER_OP ID OPEN_P CONST_INT COMMA CONST_INT COMMA CONST_INT COMMA ID CLOSE_P SEMIC
                                                        {helper = createNode($5.symbol, NULL, NULL);
                                                        $$ = createNode("queueDecl", helper, NULL);}
                ;

dropDecl:       dropFunc                                {$$ = $1;}
                | /* empty */                           {$$ = NULL;}
                ;

dropFunc:       INT_T ID OPEN_P QUEUE_T ID COMMA EVENT_T ID CLOSE_P OPEN_B dropMultStmt CLOSE_B
                                                        {helper = createNode($2.symbol, $11, NULL);
                                                        $$ = createNode("dropDecl", helper, NULL);}
                ;

enquFunc:       BOOL_T ENQUEUE OPEN_P EVENT_T ID CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {helper = createNode($2.symbol, $8, NULL);
                                                        $$ = createNode("enqueueDecl", helper, NULL);}
                ;

nextEvent:      EVENT_T NEXT_EVENT OPEN_P CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {helper = createNode($2.symbol, $6, NULL);
                                                        $$ = createNode("nextEventDecl", helper, NULL);}
                ;

dropMultStmt:   dropMultStmt dropStmt                   {helper = createNode("", $2, NULL);
                                                        $$ = createNode("", $1, helper);}
                | dropStmt                              {$$ = $1;}
                ;

dropStmt:       dropCondition                           {$$ = $1;}
                | dropLoop                              {$$ = $1;}
                | attribution SEMIC                     {$$ = $1;}
                | return SEMIC                          {$$ = $1;}
                | varDecl SEMIC                         {$$ = $1;}
                ;

comMultStmt:    comMultStmt commonStmt                  {helper = createNode("", $2, NULL);
                                                        $$ = createNode("", $1, helper);}
                | commonStmt                            {$$ = $1;}
                ;

commonStmt:     comCondition                            {$$ = $1;}
                | comLoop                               {$$ = $1;}
                | attribution SEMIC                     {$$ = $1;}
                | return SEMIC                          {$$ = $1;}
                | varDecl SEMIC                         {$$ = $1;}
                ;

dropCondition:   IF OPEN_P attribution CLOSE_P OPEN_B dropMultStmt CLOSE_B
                                                        {helper = createNode("ifStmts", $6, NULL);
                                                        helper2 = createNode("ifArg", $3, helper);
                                                        $$ = createNode("if", helper2, NULL);}
                | IF OPEN_P attribution CLOSE_P OPEN_B dropMultStmt CLOSE_B ELSE OPEN_B dropMultStmt CLOSE_B
                                                        {helper = createNode("elseStmts", $10, NULL);
                                                        helper2 = createNode("ifStmts", $6, helper);
                                                        helper3 = createNode("ifArg", $3, helper2);
                                                        $$ = createNode("ifelse", helper3, NULL);}
                ;

comCondition:   IF OPEN_P attribution CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {helper = createNode("ifStmts", $6, NULL);
                                                        helper2 = createNode("ifArg", $3, helper);
                                                        $$ = createNode("if", helper2, NULL);}

                | IF OPEN_P attribution CLOSE_P OPEN_B comMultStmt CLOSE_B ELSE OPEN_B comMultStmt CLOSE_B
                                                        {helper = createNode("elseStmts", $10, NULL);
                                                        helper2 = createNode("ifStmts", $6, helper);
                                                        helper3 = createNode("ifArg", $3, helper2);
                                                        $$ = createNode("ifelse", helper3, NULL);}
                ;

dropLoop:       FOREACH ID IN ID OPEN_B dropMultStmt CLOSE_B
                                                        {helper = createNode("loopStmts", $6, NULL);
                                                        helper2 = createNode($4.symbol, NULL, NULL);
                                                        helper3 = createNode($2.symbol, NULL, helper2);
                                                        helper = createNode("loopArgs", helper3, helper);
                                                        $$ = createNode("foreach", helper, NULL);}
                ;

comLoop:        FOR OPEN_P loopArgs CLOSE_P OPEN_B comMultStmt CLOSE_B
                                                        {helper = createNode("loopStmts", $6, NULL);
                                                        $3->next = helper;
                                                        $$ = createNode("for", $3, NULL);}
                ;

loopArgs:       firstArgument SEMIC argument SEMIC argument 
                                                        {$3->next = $5;
                                                        $1->next = $3;
                                                        $$ = createNode("loopArgs", $1, NULL);}
                ;

firstArgument:  varDecl                                 {$$ = $1;}
                | attribution                           {$$ = $1;}
                | /* empty */                           {$$ = NULL;}
                ;

argument:       attribution                             {$$ = $1;}
                | /* empty */                           {$$ = NULL;}
                ;

return:         RETURN attribution                      {$$ = createNode($1.symbol, $2, NULL);}
                ;

varDecl:        INT_T ID                                {$$ = NULL;}
                | INT_T ID ATTRIB_OP attribution        {helper = createNode($2.symbol, NULL, $4);
                                                        $$ = createNode($3.symbol, helper, NULL);}
                ;

attribution:    ID ATTRIB_OP logicalOr                  {helper = createNode($1.symbol, NULL, $3);
                                                        $$ = createNode($2.symbol, helper, NULL);}
                | logicalOr                             {$$ = $1;}
                ;

logicalOr:      logicalOr LOGIC_OR_OP logicalAnd        {$1->next = $3;
                                                        $$ = createNode($2.symbol, $1, NULL);}
                | logicalAnd                            {$$ = $1;}
                ;

logicalAnd:     logicalAnd LOGIC_AND_OP compareExp      {$1->next = $3;
                                                        $$ = createNode($2.symbol, $1, NULL);}
                | compareExp                            {$$ = $1;}
                ;

compareExp:     compareExp RELAT_LOW_OP relationExp     {$1->next = $3;
                                                        $$ = createNode($2.symbol, $1, NULL);}
                | relationExp                           {$$ = $1;}
                ;

relationExp:    relationExp GREATER_OP lowMathExp       {$1->next = $3;
                                                        $$ = createNode($2.symbol, $1, NULL);}
                | relationExp LESSER_OP lowMathExp      {$1->next = $3;
                                                        $$ = createNode($2.symbol, $1, NULL);}
                | relationExp RELAT_HIGH_OP lowMathExp  {$1->next = $3;
                                                        $$ = createNode($2.symbol, $1, NULL);}
                | lowMathExp                            {$$ = $1;}
                ;

lowMathExp:     lowMathExp MATH_ADD_OP highMathExp      {$1->next = $3;
                                                        $$ = createNode($2.symbol, $1, NULL);}
                | lowMathExp MATH_SUB_OP highMathExp    {$1->next = $3;
                                                        $$ = createNode($2.symbol, $1, NULL);}
                | highMathExp                           {$$ = $1;}
                ;

highMathExp:    highMathExp MATH_HIGH_OP unaryExp       {$1->next = $3;
                                                        $$ = createNode($2.symbol, $1, NULL);}
                | unaryExp                              {$$ = $1;}
                ;


unaryExp:       LOGIC_NOT_OP unaryExp                   {$$ = createNode($1.symbol, $2, NULL);}
                | MATH_SUB_OP unaryExp                  {$$ = createNode($1.symbol, $2, NULL);}
                | TYPE OPEN_P unaryExp CLOSE_P          {$$ = createNode($1.symbol, $3, NULL);}
                | element                               {$$ = $1;}
                ;

element:        ID                                      {$$ = createNode($1.symbol, NULL, NULL);}
                | CONST_INT                             {$$ = createNode($1.symbol, NULL, NULL);}
                | OPEN_P attribution CLOSE_P            {$$ = $2;}
                ;

%%

void yyerror(const char *error){
    printf("Error: %s\nLine: %d\nColumn: %d", error, yylval.token.line, yylval.token.column);
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