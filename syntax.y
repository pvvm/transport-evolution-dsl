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

%token <token> COMMON_TYPE NEW_TYPE CONST_INT MATH_HIGH_OP MATH_ADD_OP
%token <token> MATH_SUB_OP LOGIC_OR_OP LOGIC_AND_OP LOGIC_NOT_OP GREAT_LESS_OP
%token <token> RELAT_HIGH_OP RELAT_LOW_OP ATTRIB_OP IF ELSE FOREACH
%token <token> IN RETURN TYPE ID OPEN_B CLOSE_B OPEN_P CLOSE_P
%token <token> COMMA SEMIC ARROW

%type <node> attribution logicalOr logicalAnd compareExp relationExp
%type <node> lowMathExp highMathExp unaryExp element

%start attribution

%%

attribution:    ID ATTRIB_OP attribution                {helper = createNode($1.symbol, NULL, $3);
                                                        root = createNode($2.symbol, helper, NULL);
                                                        printTree(root, 0);
                                                        freeTree(root);}
                | logicalOr                             {root = $1; /*$$ = $1;*/}
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

relationExp:    relationExp GREAT_LESS_OP lowMathExp    {$1->next = $3;
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

//completar aqui
element:        ID                                      {$$ = createNode($1.symbol, NULL, NULL);}
                | CONST_INT                             {$$ = createNode($1.symbol, NULL, NULL);}
                | OPEN_P attribution CLOSE_P            {$$ = $2;}
                ;

%%

void yyerror(const char *error){
    printf("Error");
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