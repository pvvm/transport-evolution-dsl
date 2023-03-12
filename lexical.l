%{
#include <stdio.h>
int line = 1;
int column = 1;
%}

%option nounput
%option noinput
%option noyywrap

COMMON_TYPE     (int|bool)
NEW_TYPE        (event_t|queue_t|scheduler_t|dispatch_table_t|processor_t|state_record_t)

CONST_INT       [0-9]+

MATH_HIGH_OP    [\*/]
MATH_LOW_OP     [\+\-]
LOGIC_OR_OP     (\|\|)
LOGIC_AND_OP    (&&)
LOGIC_NOT_OP    (!)
GREAT_LESS_OP   (<|>)
RELAT_HIGH_OP   (<=|>=)
RELAT_LOW_OP    (==|!=)
ATTRIB_OP       (=)

ID              [a-zA-Z][_a-zA-Z0-9]*

%%
    /* Rules */

    /* Types (int bool) */
{COMMON_TYPE}   {printf("CT %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* New types */
{NEW_TYPE}      {printf("NT %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* Integer constant */
{CONST_INT}     {printf("INT %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* High precedence mathematical operators (* /) */
{MATH_HIGH_OP}  {printf("MH %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* Low precedence mathematical operators (+ -) */
{MATH_LOW_OP}   {printf("ML %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* Logical OR operator (||) */
{LOGIC_OR_OP}   {printf("LO %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* Logical AND operator (&&) */
{LOGIC_AND_OP}  {printf("LA %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* Logical NOT operator (!) */
{LOGIC_NOT_OP}  {printf("LN %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* Greater than and Lesser than (> <) */
{GREAT_LESS_OP} {printf("GL %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* Greater or equal and Lesser or equal (>= <=) */
{RELAT_HIGH_OP} {printf("RH %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* Equal and Different (== !=) */
{RELAT_LOW_OP}  {printf("RL %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

    /* Attribution operator (=) */
{ATTRIB_OP}     {printf("AT %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

"if"            {printf("IF %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

"else"          {printf("EL %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

"foreach"       {printf("FO %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

"in"            {printf("IN %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

"return"        {printf("RE %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

{ID}            {printf("ID %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

"{"             {printf("OB %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

"}"             {printf("CB %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

"("             {printf("OP %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

")"             {printf("CP %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

","             {printf("CO %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

";"             {printf("SE %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

"->"            {printf("AR %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

\n              {++line;    column = 1;}

[\t ]           column += yyleng;

.               {printf("Lexical error! %s\t%d\t%d\n", yytext, line, column);
                column += yyleng;}

%%


int main(int argc, char **argv) {

    if(argc > 1) {
        yyin = fopen(argv[1], "r");
        if(!yyin)
            return 1;

        yylex();
        fclose(yyin);
        yylex_destroy();
    }
    return 0;
}