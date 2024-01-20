%{
#include <stdio.h>
#include <string.h>

#include "parser.tab.hpp"

int line = 1;
int column = 1;
int columnBegin = 1;

void tokenCreator();
%}

%option nounput
%option noinput
%option noyywrap

INT_T           (int)
FLOAT_T         (float)
BOOL_T          (bool)
STREAM_T        (stream)
EVENT           (event)
EVENT_T         (event_t)
QUEUE_T         (queue_t)
SCHEDULER_T     (sched)
DISPATCH        (dispatch)
CONTEXT_T       (context)
PACKET_T        (pkt_t)

CONST_INT       [0-9]+
CONST_FLOAT     ([0-9]*"."[0-9]+)

MATH_HIGH_OP    [\*/]
MATH_ADD_OP     [\+]
MATH_SUB_OP     [\-]
LOGIC_OR_OP     (\|\|)
LOGIC_AND_OP    (&&)
LOGIC_NOT_OP    (!)
RELAT_HIGH_OP   (<=|>=)
RELAT_LOW_OP    (==|!=)
SLICE_OP        (:)
ATTRIB_OP       (=)

ID              [a-zA-Z][_a-zA-Z0-9]*

%%
    /* Rules */

    /* Common types (int bool) */
{INT_T}         {tokenCreator();
                return INT_T;}

{FLOAT_T}       {tokenCreator();
                return FLOAT_T;}

{BOOL_T}        {tokenCreator();
                return BOOL_T;}

    /* New types */
{STREAM_T}      {tokenCreator();
                return STREAM_T;}

{EVENT_T}       {tokenCreator();
                return EVENT_T;}

{EVENT}         {tokenCreator();
                return EVENT;}

{QUEUE_T}       {tokenCreator();
                return QUEUE_T;}

{SCHEDULER_T}   {tokenCreator();
                return SCHEDULER_T;}

{DISPATCH}      {tokenCreator();
                return DISPATCH;}

"header"        {tokenCreator();
                return HEADER;}

"struct"        {tokenCreator();
                return STRUCT_T;}

"list"          {tokenCreator();
                return LIST_T;}

{PACKET_T}      {tokenCreator();
                return PACKET_T;}


{CONTEXT_T}     {tokenCreator();
                return CONTEXT_T;}

    /* Integer constant */
{CONST_INT}     {tokenCreator();
                return CONST_INT;}

    /* Float constant */
{CONST_FLOAT}   {tokenCreator();
                return CONST_FLOAT;}

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
">"             {tokenCreator();
                return GREATER_OP;}

"<"             {tokenCreator();
                return LESSER_OP;}

    /* Greater or equal and Lesser or equal (>= <=) */
{RELAT_HIGH_OP} {tokenCreator();
                return RELAT_HIGH_OP;}

    /* Equal and Different (== !=) */
{RELAT_LOW_OP}  {tokenCreator();
                return RELAT_LOW_OP;}

{SLICE_OP}      {tokenCreator();
                return SLICE_OP;}

    /* Attribution operator (=) */
{ATTRIB_OP}     {tokenCreator();
                return ATTRIB_OP;}

"true"          {tokenCreator();
                return TRUE;}

"false"         {tokenCreator();
                return FALSE;}

"if"            {tokenCreator();
                return IF;}

"else"          {tokenCreator();
                return ELSE;}

"for"           {tokenCreator();
                return FOR;}

"foreach"       {tokenCreator();
                return FOREACH;}

"in"            {tokenCreator();
                return IN;}

"return"        {tokenCreator();
                return RETURN;}

"break"         {tokenCreator();
                return BREAK;}

"type"          {tokenCreator();
                return TYPE;}

"len"           {tokenCreator();
                return LENGTH;}

"timer"         {tokenCreator();
                return TIMER;}

"set_duration"  {tokenCreator();
                return SET_DURATION;}

"start"         {tokenCreator();
                return START;}

"stop"          {tokenCreator();
                return STOP;}

"restart"       {tokenCreator();
                return RESTART;}

"time"          {tokenCreator();
                return TIME;}

"new_pkt"       {tokenCreator();
                return NEW_PKT;}

"add_data"      {tokenCreator();
                return ADD_DATA;}

"add_hdr"       {tokenCreator();
                return ADD_HDR;}

"get_hdr"       {tokenCreator();
                return GET_HDR;}

"get_data"      {tokenCreator();
                return GET_DATA;}

"add"           {tokenCreator();
                return ADD;}

"bytes"         {tokenCreator();
                return BYTES;}

"push"          {tokenCreator();
                return PUSH;}

"pop"           {tokenCreator();
                return POP;}

{ID}            {tokenCreator();
                return ID;}

"{"             {tokenCreator();
                return OPEN_B;}

"}"             {tokenCreator();
                return CLOSE_B;}

"."             {tokenCreator();
                return DOT;}

"("             {tokenCreator();
                return OPEN_P;}

")"             {tokenCreator();
                return CLOSE_P;}

"["             {tokenCreator();
                return OPEN_S;}

"]"             {tokenCreator();
                return CLOSE_S;}

","             {tokenCreator();
                return COMMA;}

";"             {tokenCreator();
                return SEMIC;}

"->"            {tokenCreator();
                return ARROW;}

\n              {++line;    column = 1;}

[\t ]           column += yyleng;

"//".*          {}

.               {printf("Lexical error: %s\nLine: %d Column: %d\n", yytext, line, column);
                column += yyleng;}

%%

void tokenCreator() {
    strcpy(yylval.token.symbol, yytext);
    yylval.token.columnBegin = yylval.token.column;
    yylval.token.line = line;
    yylval.token.column = column;
    
    column += yyleng;
}