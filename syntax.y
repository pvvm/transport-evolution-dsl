%define parse.error verbose
%define lr.type canonical-lr

%{
#include <stdio.h>

extern int yylex(void);
extern int yylex_destroy(void);
extern char * yytext;
extern FILE *yyin;
void yyerror(const char *);
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
}

%token <token> COMMON_TYPE NEW_TYPE CONST_INT MATH_HIGH_OP MATH_ADD_OP
%token <token> MATH_SUB_OP LOGIC_OR_OP LOGIC_AND_OP LOGIC_NOT_OP GREAT_LESS_OP
%token <token> RELAT_HIGH_OP RELAT_LOW_OP ATTRIB_OP IF ELSE FOREACH
%token <token> IN RETURN TYPE ID OPEN_B CLOSE_B OPEN_P CLOSE_P
%token <token> COMMA SEMIC ARROW

%start attribution

%%

attribution:    ID ATTRIB_OP attribution    {printf("1" );}
                | logicalOr {printf("2 ");}
                ;

logicalOr:      logicalOr LOGIC_OR_OP logicalAnd {printf("3 ");}
                | logicalAnd {printf("4 ");}
                ;

logicalAnd:     logicalAnd LOGIC_AND_OP compareExp {printf("5 ");}
                | compareExp {printf("6 ");}
                ;

compareExp:     compareExp RELAT_LOW_OP relationExp {printf("7 ");}
                | relationExp {printf("8 ");}
                ;

relationExp:    relationExp GREAT_LESS_OP lowMathExp {printf("9 ");}
                | relationExp RELAT_HIGH_OP lowMathExp {printf("10 ");}
                | lowMathExp {printf("11 ");}
                ;

lowMathExp:     lowMathExp MATH_ADD_OP highMathExp {printf("12 ");}
                | lowMathExp MATH_SUB_OP highMathExp {printf("13 ");}
                | highMathExp {printf("14 ");}
                ;

highMathExp:    highMathExp MATH_HIGH_OP unaryExp {printf("15 ");}
                | unaryExp {printf("16 ");}
                ;


unaryExp:       LOGIC_NOT_OP unaryExp {printf("17 ");}
                | MATH_SUB_OP unaryExp {printf("18 ");}
                | TYPE OPEN_P unaryExp CLOSE_P {printf("19 ");}
                | element {printf("20 ");}
                ;

//completar aqui
element:        ID {printf("21 ");}
                | CONST_INT {printf("22 ");}
                | OPEN_P attribution CLOSE_P {printf("23 ");}
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
    }
    fclose(fp);
    yylex_destroy();

    return 0;
}