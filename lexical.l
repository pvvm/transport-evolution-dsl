%{
#include <stdio.h>
#include <string.h>

#include "syntax.tab.h"

int line = 1;
int column = 1;

void tokenCreator();
%}

%option nounput
%option noinput
%option noyywrap

COMMON_TYPE     (int|bool)
NEW_TYPE        (event_t|queue_t|scheduler_t|dispatch_table_t|processor_t|state_record_t)

CONST_INT       [0-9]+

MATH_HIGH_OP    [\*/]
MATH_ADD_OP     [\+]
MATH_SUB_OP     [\-]
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
{COMMON_TYPE}   {tokenCreator();
                return COMMON_TYPE;}

    /* New types */
{NEW_TYPE}      {tokenCreator();
                return NEW_TYPE;}

    /* Integer constant */
{CONST_INT}     {tokenCreator();
                return CONST_INT;}

    /* High precedence mathematical operators (* /) */
{MATH_HIGH_OP}  {tokenCreator();
                return MATH_HIGH_OP;}

    /* Low precedence mathematical operator (+) */
{MATH_ADD_OP}   {tokenCreator();
                return MATH_ADD_OP;}

    /* Low precedence mathematical operator and negative (-) */
{MATH_SUB_OP}   {tokenCreator();
                return MATH_SUB_OP;}

    /* Logical OR operator (||) */
{LOGIC_OR_OP}   {tokenCreator();
                return LOGIC_OR_OP;}

    /* Logical AND operator (&&) */
{LOGIC_AND_OP}  {tokenCreator();
                return LOGIC_AND_OP;}

    /* Logical NOT operator (!) */
{LOGIC_NOT_OP}  {tokenCreator();
                return LOGIC_NOT_OP;}

    /* Greater than and Lesser than (> <) */
{GREAT_LESS_OP} {tokenCreator();
                return GREAT_LESS_OP;}

    /* Greater or equal and Lesser or equal (>= <=) */
{RELAT_HIGH_OP} {tokenCreator();
                return RELAT_HIGH_OP;}

    /* Equal and Different (== !=) */
{RELAT_LOW_OP}  {tokenCreator();
                return RELAT_LOW_OP;}

    /* Attribution operator (=) */
{ATTRIB_OP}     {tokenCreator();
                return ATTRIB_OP;}

"if"            {tokenCreator();
                return IF;}

"else"          {tokenCreator();
                return ELSE;}

"foreach"       {tokenCreator();
                return FOREACH;}

"in"            {tokenCreator();
                return IN;}

"return"        {tokenCreator();
                return RETURN;}

"type"          {tokenCreator();
                return TYPE;}

{ID}            {tokenCreator();
                return ID;}

"{"             {tokenCreator();
                return OPEN_B;}

"}"             {tokenCreator();
                return CLOSE_B;}

"("             {tokenCreator();
                return OPEN_P;}

")"             {tokenCreator();
                return CLOSE_P;}

","             {tokenCreator();
                return COMMA;}

";"             {tokenCreator();
                return SEMIC;}

"->"            {tokenCreator();
                return ARROW;}

\n              {++line;    column = 1;}

[\t ]           column += yyleng;

.               {printf("Lexical error: %s Line: %d Column: %d\n", yytext, line, column);
                column += yyleng;}

%%

void tokenCreator() {
    strcpy(yylval.token.symbol, yytext);
    yylval.token.line = line;
    yylval.token.column = column;
    column += yyleng;
}