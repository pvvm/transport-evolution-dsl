/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 20 "syntax.y"

    struct token {
        char symbol[50];
        int line;
        int column;
    };

#line 57 "syntax.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT_T = 258,                   /* INT_T  */
    BOOL_T = 259,                  /* BOOL_T  */
    EVENT_T = 260,                 /* EVENT_T  */
    QUEUE_T = 261,                 /* QUEUE_T  */
    SCHEDULER_T = 262,             /* SCHEDULER_T  */
    DISPATCH_T_T = 263,            /* DISPATCH_T_T  */
    PROCESSOR_T = 264,             /* PROCESSOR_T  */
    STATE_R_T = 265,               /* STATE_R_T  */
    CONST_INT = 266,               /* CONST_INT  */
    MATH_HIGH_OP = 267,            /* MATH_HIGH_OP  */
    MATH_ADD_OP = 268,             /* MATH_ADD_OP  */
    MATH_SUB_OP = 269,             /* MATH_SUB_OP  */
    LOGIC_OR_OP = 270,             /* LOGIC_OR_OP  */
    LOGIC_AND_OP = 271,            /* LOGIC_AND_OP  */
    LOGIC_NOT_OP = 272,            /* LOGIC_NOT_OP  */
    GREATER_OP = 273,              /* GREATER_OP  */
    LESSER_OP = 274,               /* LESSER_OP  */
    RELAT_HIGH_OP = 275,           /* RELAT_HIGH_OP  */
    RELAT_LOW_OP = 276,            /* RELAT_LOW_OP  */
    ATTRIB_OP = 277,               /* ATTRIB_OP  */
    IF = 278,                      /* IF  */
    ELSE = 279,                    /* ELSE  */
    FOR = 280,                     /* FOR  */
    FOREACH = 281,                 /* FOREACH  */
    IN = 282,                      /* IN  */
    RETURN = 283,                  /* RETURN  */
    TYPE = 284,                    /* TYPE  */
    NEXT_EVENT = 285,              /* NEXT_EVENT  */
    ENQUEUE = 286,                 /* ENQUEUE  */
    ID = 287,                      /* ID  */
    OPEN_B = 288,                  /* OPEN_B  */
    CLOSE_B = 289,                 /* CLOSE_B  */
    OPEN_P = 290,                  /* OPEN_P  */
    CLOSE_P = 291,                 /* CLOSE_P  */
    COMMA = 292,                   /* COMMA  */
    SEMIC = 293,                   /* SEMIC  */
    ARROW = 294                    /* ARROW  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "syntax.y"

    struct token token;
    struct ListNode* node;

#line 118 "syntax.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */
