/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "syntax.y"

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

#line 87 "syntax.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_T = 3,                      /* INT_T  */
  YYSYMBOL_BOOL_T = 4,                     /* BOOL_T  */
  YYSYMBOL_EVENT_T = 5,                    /* EVENT_T  */
  YYSYMBOL_QUEUE_T = 6,                    /* QUEUE_T  */
  YYSYMBOL_SCHEDULER_T = 7,                /* SCHEDULER_T  */
  YYSYMBOL_DISPATCH_T_T = 8,               /* DISPATCH_T_T  */
  YYSYMBOL_PROCESSOR_T = 9,                /* PROCESSOR_T  */
  YYSYMBOL_STATE_R_T = 10,                 /* STATE_R_T  */
  YYSYMBOL_CONST_INT = 11,                 /* CONST_INT  */
  YYSYMBOL_MATH_HIGH_OP = 12,              /* MATH_HIGH_OP  */
  YYSYMBOL_MATH_ADD_OP = 13,               /* MATH_ADD_OP  */
  YYSYMBOL_MATH_SUB_OP = 14,               /* MATH_SUB_OP  */
  YYSYMBOL_LOGIC_OR_OP = 15,               /* LOGIC_OR_OP  */
  YYSYMBOL_LOGIC_AND_OP = 16,              /* LOGIC_AND_OP  */
  YYSYMBOL_LOGIC_NOT_OP = 17,              /* LOGIC_NOT_OP  */
  YYSYMBOL_GREATER_OP = 18,                /* GREATER_OP  */
  YYSYMBOL_LESSER_OP = 19,                 /* LESSER_OP  */
  YYSYMBOL_RELAT_HIGH_OP = 20,             /* RELAT_HIGH_OP  */
  YYSYMBOL_RELAT_LOW_OP = 21,              /* RELAT_LOW_OP  */
  YYSYMBOL_ATTRIB_OP = 22,                 /* ATTRIB_OP  */
  YYSYMBOL_IF = 23,                        /* IF  */
  YYSYMBOL_ELSE = 24,                      /* ELSE  */
  YYSYMBOL_FOR = 25,                       /* FOR  */
  YYSYMBOL_FOREACH = 26,                   /* FOREACH  */
  YYSYMBOL_IN = 27,                        /* IN  */
  YYSYMBOL_RETURN = 28,                    /* RETURN  */
  YYSYMBOL_TYPE = 29,                      /* TYPE  */
  YYSYMBOL_NEXT_EVENT = 30,                /* NEXT_EVENT  */
  YYSYMBOL_ENQUEUE = 31,                   /* ENQUEUE  */
  YYSYMBOL_ID = 32,                        /* ID  */
  YYSYMBOL_OPEN_B = 33,                    /* OPEN_B  */
  YYSYMBOL_CLOSE_B = 34,                   /* CLOSE_B  */
  YYSYMBOL_OPEN_P = 35,                    /* OPEN_P  */
  YYSYMBOL_CLOSE_P = 36,                   /* CLOSE_P  */
  YYSYMBOL_COMMA = 37,                     /* COMMA  */
  YYSYMBOL_SEMIC = 38,                     /* SEMIC  */
  YYSYMBOL_ARROW = 39,                     /* ARROW  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_program = 41,                   /* program  */
  YYSYMBOL_declarations = 42,              /* declarations  */
  YYSYMBOL_dispatcher = 43,                /* dispatcher  */
  YYSYMBOL_dispMult = 44,                  /* dispMult  */
  YYSYMBOL_dispDecl = 45,                  /* dispDecl  */
  YYSYMBOL_processorIds = 46,              /* processorIds  */
  YYSYMBOL_processorMult = 47,             /* processorMult  */
  YYSYMBOL_processorDecl = 48,             /* processorDecl  */
  YYSYMBOL_stateRecord = 49,               /* stateRecord  */
  YYSYMBOL_srVariables = 50,               /* srVariables  */
  YYSYMBOL_scheduler = 51,                 /* scheduler  */
  YYSYMBOL_queues = 52,                    /* queues  */
  YYSYMBOL_queueAndDrop = 53,              /* queueAndDrop  */
  YYSYMBOL_qTypeDecl = 54,                 /* qTypeDecl  */
  YYSYMBOL_queueType = 55,                 /* queueType  */
  YYSYMBOL_queueTypeDecl = 56,             /* queueTypeDecl  */
  YYSYMBOL_queueDecl = 57,                 /* queueDecl  */
  YYSYMBOL_dropDecl = 58,                  /* dropDecl  */
  YYSYMBOL_dropFunc = 59,                  /* dropFunc  */
  YYSYMBOL_enquFunc = 60,                  /* enquFunc  */
  YYSYMBOL_nextEvent = 61,                 /* nextEvent  */
  YYSYMBOL_dropMultStmt = 62,              /* dropMultStmt  */
  YYSYMBOL_dropStmt = 63,                  /* dropStmt  */
  YYSYMBOL_comMultStmt = 64,               /* comMultStmt  */
  YYSYMBOL_commonStmt = 65,                /* commonStmt  */
  YYSYMBOL_dropCondition = 66,             /* dropCondition  */
  YYSYMBOL_comCondition = 67,              /* comCondition  */
  YYSYMBOL_dropLoop = 68,                  /* dropLoop  */
  YYSYMBOL_comLoop = 69,                   /* comLoop  */
  YYSYMBOL_loopArgs = 70,                  /* loopArgs  */
  YYSYMBOL_firstArgument = 71,             /* firstArgument  */
  YYSYMBOL_argument = 72,                  /* argument  */
  YYSYMBOL_return = 73,                    /* return  */
  YYSYMBOL_varDecl = 74,                   /* varDecl  */
  YYSYMBOL_attribution = 75,               /* attribution  */
  YYSYMBOL_logicalOr = 76,                 /* logicalOr  */
  YYSYMBOL_logicalAnd = 77,                /* logicalAnd  */
  YYSYMBOL_compareExp = 78,                /* compareExp  */
  YYSYMBOL_relationExp = 79,               /* relationExp  */
  YYSYMBOL_lowMathExp = 80,                /* lowMathExp  */
  YYSYMBOL_highMathExp = 81,               /* highMathExp  */
  YYSYMBOL_unaryExp = 82,                  /* unaryExp  */
  YYSYMBOL_element = 83                    /* element  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1352

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  283

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    54,    54,    57,    60,    67,    72,    74,    77,    81,
      82,    85,    87,    90,    95,   100,   101,   104,   112,   114,
     117,   122,   123,   126,   131,   132,   135,   140,   141,   144,
     149,   154,   159,   161,   164,   165,   166,   167,   168,   171,
     173,   176,   177,   178,   179,   180,   183,   187,   194,   199,
     206,   213,   219,   225,   226,   227,   230,   231,   234,   237,
     238,   242,   244,   247,   249,   252,   254,   257,   259,   262,
     264,   266,   268,   271,   273,   275,   278,   280,   284,   285,
     286,   287,   290,   291,   292
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT_T", "BOOL_T",
  "EVENT_T", "QUEUE_T", "SCHEDULER_T", "DISPATCH_T_T", "PROCESSOR_T",
  "STATE_R_T", "CONST_INT", "MATH_HIGH_OP", "MATH_ADD_OP", "MATH_SUB_OP",
  "LOGIC_OR_OP", "LOGIC_AND_OP", "LOGIC_NOT_OP", "GREATER_OP", "LESSER_OP",
  "RELAT_HIGH_OP", "RELAT_LOW_OP", "ATTRIB_OP", "IF", "ELSE", "FOR",
  "FOREACH", "IN", "RETURN", "TYPE", "NEXT_EVENT", "ENQUEUE", "ID",
  "OPEN_B", "CLOSE_B", "OPEN_P", "CLOSE_P", "COMMA", "SEMIC", "ARROW",
  "$accept", "program", "declarations", "dispatcher", "dispMult",
  "dispDecl", "processorIds", "processorMult", "processorDecl",
  "stateRecord", "srVariables", "scheduler", "queues", "queueAndDrop",
  "qTypeDecl", "queueType", "queueTypeDecl", "queueDecl", "dropDecl",
  "dropFunc", "enquFunc", "nextEvent", "dropMultStmt", "dropStmt",
  "comMultStmt", "commonStmt", "dropCondition", "comCondition", "dropLoop",
  "comLoop", "loopArgs", "firstArgument", "argument", "return", "varDecl",
  "attribution", "logicalOr", "logicalAnd", "compareExp", "relationExp",
  "lowMathExp", "highMathExp", "unaryExp", "element", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-179)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-85)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,   -26,    28,    50,     9,    39,  -179,    56,    92,   290,
     106,   108,    80,   103,   112,   316,   358,    38,    57,   115,
     114,   118,   110,   154,   123,   147,   881,   177,   164,   195,
     222,   203,   231,   242,   240,   214,   239,   246,   263,   280,
    1074,   248,    42,   178,   272,   304,   277,   278,   306,   279,
     320,   317,   298,   301,   299,   203,   300,   309,   308,   310,
     321,   326,   331,   341,   335,   343,   369,   183,   349,   350,
     394,     6,   252,   360,   364,   363,   370,   236,   373,   104,
       8,   378,   380,   104,   413,   381,   343,   385,   387,   901,
     216,   216,   396,   397,  1246,   398,   890,  1247,   376,   392,
     411,   427,   391,   399,   404,    -7,    -3,    33,     5,   270,
     911,   922,   932,   401,   104,   446,   415,   437,   417,   268,
      -8,   943,   953,   964,  1247,   265,   416,  1248,   216,   422,
     125,   462,   481,   497,   516,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   532,   419,   428,   429,  1246,   431,
     432,   434,   439,   444,   447,    17,   974,    70,    49,    62,
    1027,  1037,  1048,   985,   995,  1006,   465,   453,   477,   451,
     460,   466,   202,  1016,   866,   464,   104,   104,   467,   469,
     468,   470,   551,   567,   586,   602,   474,   479,   480,   510,
     621,   637,  1059,  1247,   496,   518,   656,   672,   691,   707,
     491,   315,   726,   498,   500,   505,   506,   507,   509,   514,
     517,   104,   866,   866,   520,   742,   761,   777,  1078,   796,
     357,   812,   519,   866,   831,   847,  1095,  1255,  1255,   521,
    1084,  1247,    30,     0,    78,   336,  1278,  1109,  1120,  1134,
     523,  1248,  1248,   528,   533,  1247,   535,   536,  1145,  1159,
    1170,  1248,  1255,   537,  1255,  1255,  1255,  1255,  1255,  1255,
    1255,  1255,  1255,   539,   540,  1248,   546,   552,    37,  1184,
     210,   208,  1316,  1287,  1297,  1306,  1195,  1209,  1220,   555,
     556,  1234,   558
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,  -179,  -179,   543,   501,  -179,   592,  -179,
     526,  -179,  -179,   593,  -179,  -179,   562,  -179,  -179,  -179,
    -179,  -179,    44,  -178,   -81,   -93,  -179,  -179,  -179,  -179,
    -179,  -179,   418,  -155,  -107,   153,    29,    79,   -13,    61,
       7,   -50,   -90,   -68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     8,    42,    43,    78,    12,    13,    23,
      58,     4,    15,    16,    17,    18,    47,    40,    29,    30,
      27,    37,   182,   183,    98,    99,   184,   100,   185,   101,
     150,   151,   178,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     122,   123,   115,    -3,   196,   131,     5,   238,   135,    46,
       1,    57,   -64,   136,   148,   -64,   255,     7,   152,   186,
     -68,   -68,   131,   138,   139,   140,   -68,   186,     6,   239,
     -59,   -62,   135,   144,   238,   -64,   -64,   154,   196,   196,
     -25,    28,   -16,   -68,   -28,   254,   196,   237,   -66,   -66,
      -2,   131,   254,   165,   137,   -61,   239,   186,   186,   246,
     -21,   186,   186,   -21,   -65,   -65,   -62,   187,   186,   186,
     137,   -66,     9,   -61,   237,   187,    54,   -67,   -67,    55,
     138,   139,   140,   -67,   234,   -63,   136,   -65,    10,    11,
      21,   163,   164,   -66,   -66,   190,   191,   131,   131,   256,
     -67,    11,   238,   238,   236,   187,   187,    88,   -63,   187,
     187,   234,   -12,   -12,   -66,    89,   187,   187,    90,   -11,
     -11,    91,   131,   158,   239,   239,   232,    92,    19,    93,
     215,   236,    94,    95,   -13,   -13,    96,   249,   250,    97,
      20,   238,   237,   237,    24,   160,   161,   162,    31,    32,
      33,   263,   264,   232,    -4,   238,    34,   155,   235,   239,
     239,   267,   238,   239,   238,   238,   238,   238,   238,   238,
     238,   238,   278,   246,   246,   279,   233,   239,    35,   234,
     234,   237,    36,   246,   239,   235,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   237,    38,   246,   159,   236,
     236,    39,   237,   233,   237,   237,   237,   237,   237,   237,
     276,   277,    -7,    89,   157,    -7,    90,    -6,   234,    91,
      -6,   232,   232,   -65,   -65,   -63,   255,    89,   -27,   256,
      90,    95,   234,    91,    96,    41,    44,    97,   236,   234,
     -57,   234,   271,    46,   -65,    95,   -63,   126,   121,    48,
     129,    97,   236,   235,   235,   -23,   216,   217,   -23,   236,
     232,   236,   236,   236,   273,   274,   275,   224,    88,    49,
     -10,   233,   233,    86,   232,    45,    89,   149,   153,    90,
      50,   268,    91,   141,   142,   -72,   -72,    53,   -72,   -72,
     -72,   -72,   235,   -22,    95,    14,   -22,    96,    51,    52,
      97,   169,    -8,   -55,    56,    -8,   235,    57,   -72,    59,
     233,    61,    60,   235,    62,   235,   235,   272,   -48,   -22,
      25,    14,   -22,    63,   233,   179,   -48,   188,   -17,   -48,
      64,   233,   -48,   270,    65,   188,    68,    66,   -48,   207,
     -48,    69,    70,   -48,   -48,   247,   204,   -48,    71,   -48,
     -48,   -68,   -68,    76,   257,   258,   259,   -68,    73,    72,
     -46,   -19,   -19,   -19,   -19,   188,   188,    74,   -46,   188,
     188,   -46,   -68,    75,   -46,    77,   188,   188,    -5,    88,
     -46,   222,    79,   -46,   253,   -46,   -46,    89,    80,   -46,
      90,   -46,   -46,    91,   -14,   -40,    82,    83,   266,    92,
      84,    93,    85,   -40,    94,    95,   -40,    87,    96,   -40,
     130,    97,   -24,   114,   -41,   -40,   117,   -40,   116,   120,
     -40,   -40,   -41,   119,   -40,   -41,   -40,   -40,   -41,   132,
     -42,   124,   125,   127,   -41,   -15,   -41,   133,   -42,   -41,
     -41,   -42,   134,   -41,   -42,   -41,   -41,   146,   147,    88,
     -42,    -9,   -42,   -31,   -58,   -42,   -42,    89,   156,   -42,
      90,   -42,   -42,    91,   167,   -39,   168,   170,   171,    92,
     -30,    93,   172,   -39,    94,    95,   -39,   -53,    96,   -39,
     145,    97,   -54,   173,   -44,   -39,   174,   -39,   175,   -60,
     -39,   -39,   -44,   176,   -39,   -44,   -39,   -39,   -44,   177,
     -45,   189,   194,   193,   -44,   192,   -44,   -56,   -45,   -44,
     -44,   -45,   197,   -44,   -45,   -44,   -44,   198,   199,   -43,
     -45,   200,   -45,   205,   -29,   -45,   -45,   -43,   206,   -45,
     -43,   -45,   -45,   -43,   -52,    88,   208,   209,   210,   -43,
     211,   -43,   212,    89,   -43,   -43,    90,   213,   -43,    91,
     -43,   -43,   223,   214,    88,    92,   251,    93,   218,   -83,
      94,    95,    89,   265,    96,    90,   166,    97,    91,   -82,
     -33,   -81,   -56,   269,   180,   -79,   -78,   181,   -33,    94,
      95,   -33,   280,    96,   -33,   195,    97,   118,   281,   -34,
     -33,   282,   -84,   -33,   -80,   -33,   -33,   -34,    67,   -33,
     -34,   -33,   -33,   -34,    22,   -35,   113,     0,    26,   -34,
     203,     0,   -34,   -35,   -34,   -34,   -35,     0,   -34,   -35,
     -34,   -34,     0,     0,    88,   -35,     0,     0,   -35,     0,
     -35,   -35,    89,    81,   -35,    90,   -35,   -35,    91,     0,
      88,     0,     0,     0,    92,     0,    93,     0,    89,    94,
      95,    90,     0,    96,    91,   201,    97,     0,     0,   -32,
      92,     0,    93,     0,     0,    94,    95,   -32,     0,    96,
     -32,   202,    97,   -32,     0,   -37,     0,     0,     0,   -32,
       0,     0,   -32,   -37,   -32,   -32,   -37,     0,   -32,   -37,
     -32,   -32,     0,     0,   -38,   -37,     0,     0,   -37,     0,
     -37,   -37,   -38,     0,   -37,   -38,   -37,   -37,   -38,     0,
     -36,     0,     0,     0,   -38,     0,     0,   -38,   -36,   -38,
     -38,   -36,     0,   -38,   -36,   -38,   -38,     0,     0,   -51,
     -36,     0,     0,   -36,     0,   -36,   -36,   -51,     0,   -36,
     -51,   -36,   -36,   -51,     0,    88,     0,     0,     0,   -51,
       0,   -51,     0,    89,   -51,   -51,    90,     0,   -51,    91,
     -51,   -51,     0,     0,    88,    92,     0,    93,     0,     0,
      94,    95,    89,     0,    96,    90,   219,    97,    91,     0,
      88,     0,     0,     0,   180,     0,     0,   181,    89,    94,
      95,    90,     0,    96,    91,   220,    97,     0,     0,   -49,
     180,     0,     0,   181,     0,    94,    95,   -49,     0,    96,
     -49,   221,    97,   -49,     0,   -50,     0,     0,     0,   -49,
       0,   -49,     0,   -50,   -49,   -49,   -50,     0,   -49,   -50,
     -49,   -49,     0,     0,    88,   -50,     0,     0,   -50,     0,
     -50,   -50,    89,     0,   -50,    90,   -50,   -50,    91,     0,
     -47,     0,     0,     0,   180,     0,     0,   181,   -47,    94,
      95,   -47,     0,    96,   -47,   225,    97,     0,     0,    88,
     -47,     0,     0,   -47,     0,   -47,   -47,    89,     0,   -47,
      90,   -47,   -47,    91,   -18,   -18,   -18,   -18,     0,   180,
       0,     0,   181,     0,    94,    95,     0,     0,    96,     0,
       0,    97,   -82,   -82,   -82,   -82,   -82,     0,   -82,   -82,
     -82,   -82,   128,   -83,   -83,   -83,   -83,   -83,     0,   -83,
     -83,   -83,   -83,   143,   -75,   -75,   -75,   -75,   -82,   -75,
     -75,   -75,   -75,     0,   -77,   -77,   -77,   -77,   -77,   -83,
     -77,   -77,   -77,   -77,   -81,   -81,   -81,   -81,   -81,   -75,
     -81,   -81,   -81,   -81,     0,   -82,   -82,   -82,   -82,   -82,
     -77,   -82,   -82,   -82,   -82,   -79,   -79,   -79,   -79,   -79,
     -81,   -79,   -79,   -79,   -79,     0,   -78,   -78,   -78,   -78,
     -78,   -82,   -78,   -78,   -78,   -78,   -84,   -84,   -84,   -84,
     -84,   -79,   -84,   -84,   -84,   -84,     0,   143,   -73,   -73,
     -73,   -73,   -78,   -73,   -73,   -73,   -73,   143,   -74,   -74,
     -74,   -74,   -84,   -74,   -74,   -74,   -74,     0,   -76,   -76,
     -76,   -76,   -76,   -73,   -76,   -76,   -76,   -76,   -80,   -80,
     -80,   -80,   -80,   -74,   -80,   -80,   -80,   -80,     0,     0,
     141,   142,   -69,   -69,   -76,   -69,   -69,   -69,   -69,     0,
     141,   142,   -70,   -70,   -80,   -70,   -70,   -70,   -70,     0,
       0,   141,   142,   -71,   -71,   -69,   -71,   -71,   -71,   -71,
     226,     0,     0,   227,     0,   -70,   228,   -20,   -20,   -20,
     -20,   -26,   -26,   -26,   -26,     0,   -71,     0,   229,     0,
       0,   230,     0,     0,   231,   -57,   -82,   -82,   -82,   -82,
     -82,     0,   -82,   -82,   -82,   -82,   252,   -83,   -83,   -83,
     -83,   -83,     0,   -83,   -83,   -83,   -83,     0,     0,     0,
     -82,   262,   -75,   -75,   -75,   -75,     0,   -75,   -75,   -75,
     -75,   -83,   -77,   -77,   -77,   -77,   -77,     0,   -77,   -77,
     -77,   -77,     0,     0,     0,   -75,   -81,   -81,   -81,   -81,
     -81,     0,   -81,   -81,   -81,   -81,   -77,   -82,   -82,   -82,
     -82,   -82,     0,   -82,   -82,   -82,   -82,     0,     0,     0,
     -81,   -79,   -79,   -79,   -79,   -79,     0,   -79,   -79,   -79,
     -79,   -82,   -78,   -78,   -78,   -78,   -78,     0,   -78,   -78,
     -78,   -78,     0,     0,     0,   -79,   -84,   -84,   -84,   -84,
     -84,     0,   -84,   -84,   -84,   -84,   -78,   262,   -73,   -73,
     -73,   -73,     0,   -73,   -73,   -73,   -73,     0,     0,     0,
     -84,   262,   -74,   -74,   -74,   -74,     0,   -74,   -74,   -74,
     -74,   -73,   -76,   -76,   -76,   -76,   -76,     0,   -76,   -76,
     -76,   -76,     0,     0,     0,   -74,   -80,   -80,   -80,   -80,
     -80,     0,   -80,   -80,   -80,   -80,   -76,    89,   226,   240,
      90,   227,   241,    91,   228,   242,   226,     0,     0,   227,
     -80,     0,   228,     0,     0,    95,   229,   243,    96,   230,
     244,    97,   231,   245,   229,     0,     0,   248,     0,     0,
     231,   260,   261,   -72,   -72,     0,   -72,   -72,   -72,   -72,
     260,   261,   -69,   -69,     0,   -69,   -69,   -69,   -69,     0,
     260,   261,   -70,   -70,   -72,   -70,   -70,   -70,   -70,   260,
     261,   -71,   -71,   -69,   -71,   -71,   -71,   -71,     0,     0,
       0,   -67,   -67,   -70,   257,   258,   259,   -67,     0,     0,
       0,     0,   -71,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -67
};

static const yytype_int16 yycheck[] =
{
      90,    91,    83,     0,   182,    98,    32,    97,    15,     3,
       7,     3,    15,    16,    22,    15,    16,     8,   125,   174,
      15,    16,   115,    18,    19,    20,    21,   182,     0,    97,
      38,    38,    15,   114,   124,    38,    36,   127,   216,   217,
      34,     3,    34,    38,     6,    15,   224,    97,    15,    16,
       0,   144,    15,   143,    21,    38,   124,   212,   213,   127,
       3,   216,   217,     6,    15,    16,    36,   174,   223,   224,
      21,    38,    33,    36,   124,   182,    34,    15,    16,    37,
      18,    19,    20,    21,    97,    15,    16,    38,    32,     9,
      10,   141,   142,    15,    16,   176,   177,   190,   191,    21,
      38,     9,   192,   193,    97,   212,   213,     3,    38,   216,
     217,   124,     9,    10,    36,    11,   223,   224,    14,     9,
      10,    17,   215,   136,   192,   193,    97,    23,    22,    25,
     211,   124,    28,    29,     9,    10,    32,   227,   228,    35,
      32,   231,   192,   193,    32,   138,   139,   140,    33,    35,
      32,   241,   242,   124,     0,   245,    33,   128,    97,   227,
     228,   251,   252,   231,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   241,   242,   265,    97,   245,    31,   192,
     193,   231,     5,   251,   252,   124,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   245,    32,   265,   137,   192,
     193,     6,   252,   124,   254,   255,   256,   257,   258,   259,
     260,   261,    34,    11,   135,    37,    14,    34,   231,    17,
      37,   192,   193,    15,    16,    15,    16,    11,     6,    21,
      14,    29,   245,    17,    32,    32,     5,    35,   231,   252,
      38,   254,   255,     3,    36,    29,    36,    94,    32,    35,
      97,    35,   245,   192,   193,     3,   212,   213,     6,   252,
     231,   254,   255,   256,   257,   258,   259,   223,     3,    30,
      34,   192,   193,    37,   245,    33,    11,   124,   125,    14,
      34,   252,    17,    13,    14,    15,    16,    39,    18,    19,
      20,    21,   231,     3,    29,     5,     6,    32,    35,    19,
      35,   148,    34,    38,    32,    37,   245,     3,    38,    32,
     231,     5,    34,   252,    35,   254,   255,   256,     3,     3,
       4,     5,     6,     6,   245,   172,    11,   174,     8,    14,
      32,   252,    17,   254,    33,   182,    36,    38,    23,    24,
      25,    32,    34,    28,    29,   192,   193,    32,    38,    34,
      35,    15,    16,    18,    18,    19,    20,    21,    32,    38,
       3,     3,     4,     5,     6,   212,   213,    36,    11,   216,
     217,    14,    36,    32,    17,    32,   223,   224,     9,     3,
      23,    24,    33,    26,   231,    28,    29,    11,    38,    32,
      14,    34,    35,    17,     0,     3,    36,    33,   245,    23,
      37,    25,    32,    11,    28,    29,    14,    34,    32,    17,
      34,    35,    34,    33,     3,    23,    35,    25,     5,    32,
      28,    29,    11,    38,    32,    14,    34,    35,    17,    38,
       3,    35,    35,    35,    23,    34,    25,    38,    11,    28,
      29,    14,    38,    32,    17,    34,    35,    32,    11,     3,
      23,    34,    25,    34,    38,    28,    29,    11,    36,    32,
      14,    34,    35,    17,    36,     3,    37,    36,    36,    23,
       5,    25,    38,    11,    28,    29,    14,    38,    32,    17,
      34,    35,    38,    36,     3,    23,    33,    25,    11,    38,
      28,    29,    11,    33,    32,    14,    34,    35,    17,    33,
       3,    37,    32,    35,    23,    38,    25,    38,    11,    28,
      29,    14,    38,    32,    17,    34,    35,    38,    38,     3,
      23,    11,    25,    27,     6,    28,    29,    11,    37,    32,
      14,    34,    35,    17,    36,     3,    36,    32,    32,    23,
      33,    25,    33,    11,    28,    29,    14,    33,    32,    17,
      34,    35,    33,    36,     3,    23,    35,    25,    38,    36,
      28,    29,    11,    35,    32,    14,    34,    35,    17,    36,
       3,    36,    36,    36,    23,    36,    36,    26,    11,    28,
      29,    14,    36,    32,    17,    34,    35,    86,    36,     3,
      23,    36,    36,    26,    36,    28,    29,    11,    55,    32,
      14,    34,    35,    17,    12,     3,    80,    -1,    15,    23,
     192,    -1,    26,    11,    28,    29,    14,    -1,    32,    17,
      34,    35,    -1,    -1,     3,    23,    -1,    -1,    26,    -1,
      28,    29,    11,    71,    32,    14,    34,    35,    17,    -1,
       3,    -1,    -1,    -1,    23,    -1,    25,    -1,    11,    28,
      29,    14,    -1,    32,    17,    34,    35,    -1,    -1,     3,
      23,    -1,    25,    -1,    -1,    28,    29,    11,    -1,    32,
      14,    34,    35,    17,    -1,     3,    -1,    -1,    -1,    23,
      -1,    -1,    26,    11,    28,    29,    14,    -1,    32,    17,
      34,    35,    -1,    -1,     3,    23,    -1,    -1,    26,    -1,
      28,    29,    11,    -1,    32,    14,    34,    35,    17,    -1,
       3,    -1,    -1,    -1,    23,    -1,    -1,    26,    11,    28,
      29,    14,    -1,    32,    17,    34,    35,    -1,    -1,     3,
      23,    -1,    -1,    26,    -1,    28,    29,    11,    -1,    32,
      14,    34,    35,    17,    -1,     3,    -1,    -1,    -1,    23,
      -1,    25,    -1,    11,    28,    29,    14,    -1,    32,    17,
      34,    35,    -1,    -1,     3,    23,    -1,    25,    -1,    -1,
      28,    29,    11,    -1,    32,    14,    34,    35,    17,    -1,
       3,    -1,    -1,    -1,    23,    -1,    -1,    26,    11,    28,
      29,    14,    -1,    32,    17,    34,    35,    -1,    -1,     3,
      23,    -1,    -1,    26,    -1,    28,    29,    11,    -1,    32,
      14,    34,    35,    17,    -1,     3,    -1,    -1,    -1,    23,
      -1,    25,    -1,    11,    28,    29,    14,    -1,    32,    17,
      34,    35,    -1,    -1,     3,    23,    -1,    -1,    26,    -1,
      28,    29,    11,    -1,    32,    14,    34,    35,    17,    -1,
       3,    -1,    -1,    -1,    23,    -1,    -1,    26,    11,    28,
      29,    14,    -1,    32,    17,    34,    35,    -1,    -1,     3,
      23,    -1,    -1,    26,    -1,    28,    29,    11,    -1,    32,
      14,    34,    35,    17,     3,     4,     5,     6,    -1,    23,
      -1,    -1,    26,    -1,    28,    29,    -1,    -1,    32,    -1,
      -1,    35,    12,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    12,    13,    14,    15,    16,    -1,    18,
      19,    20,    21,    12,    13,    14,    15,    16,    38,    18,
      19,    20,    21,    -1,    12,    13,    14,    15,    16,    38,
      18,    19,    20,    21,    12,    13,    14,    15,    16,    38,
      18,    19,    20,    21,    -1,    12,    13,    14,    15,    16,
      38,    18,    19,    20,    21,    12,    13,    14,    15,    16,
      38,    18,    19,    20,    21,    -1,    12,    13,    14,    15,
      16,    38,    18,    19,    20,    21,    12,    13,    14,    15,
      16,    38,    18,    19,    20,    21,    -1,    12,    13,    14,
      15,    16,    38,    18,    19,    20,    21,    12,    13,    14,
      15,    16,    38,    18,    19,    20,    21,    -1,    12,    13,
      14,    15,    16,    38,    18,    19,    20,    21,    12,    13,
      14,    15,    16,    38,    18,    19,    20,    21,    -1,    -1,
      13,    14,    15,    16,    38,    18,    19,    20,    21,    -1,
      13,    14,    15,    16,    38,    18,    19,    20,    21,    -1,
      -1,    13,    14,    15,    16,    38,    18,    19,    20,    21,
      11,    -1,    -1,    14,    -1,    38,    17,     3,     4,     5,
       6,     3,     4,     5,     6,    -1,    38,    -1,    29,    -1,
      -1,    32,    -1,    -1,    35,    36,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    22,    12,    13,    14,
      15,    16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,
      36,    12,    13,    14,    15,    16,    -1,    18,    19,    20,
      21,    36,    12,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    -1,    36,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    36,    12,    13,    14,
      15,    16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,
      36,    12,    13,    14,    15,    16,    -1,    18,    19,    20,
      21,    36,    12,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    -1,    36,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    36,    12,    13,    14,
      15,    16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,
      36,    12,    13,    14,    15,    16,    -1,    18,    19,    20,
      21,    36,    12,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    -1,    36,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    36,    11,    11,    11,
      14,    14,    14,    17,    17,    17,    11,    -1,    -1,    14,
      36,    -1,    17,    -1,    -1,    29,    29,    29,    32,    32,
      32,    35,    35,    35,    29,    -1,    -1,    32,    -1,    -1,
      35,    13,    14,    15,    16,    -1,    18,    19,    20,    21,
      13,    14,    15,    16,    -1,    18,    19,    20,    21,    -1,
      13,    14,    15,    16,    36,    18,    19,    20,    21,    13,
      14,    15,    16,    36,    18,    19,    20,    21,    -1,    -1,
      -1,    15,    16,    36,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    41,    42,    51,    32,     0,     8,    43,    33,
      32,     9,    47,    48,     5,    52,    53,    54,    55,    22,
      32,    10,    48,    49,    32,     4,    53,    60,     3,    58,
      59,    33,    35,    32,    33,    31,     5,    61,    32,     6,
      57,    32,    44,    45,     5,    33,     3,    56,    35,    30,
      34,    35,    19,    39,    34,    37,    32,     3,    50,    32,
      34,     5,    35,     6,    32,    33,    38,    45,    36,    32,
      34,    38,    38,    32,    36,    32,    18,    32,    46,    33,
      38,    56,    36,    33,    37,    32,    37,    34,     3,    11,
      14,    17,    23,    25,    28,    29,    32,    35,    64,    65,
      67,    69,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    50,    33,    64,     5,    35,    46,    38,
      32,    32,    82,    82,    35,    35,    75,    35,    22,    75,
      34,    65,    38,    38,    38,    15,    16,    21,    18,    19,
      20,    13,    14,    12,    64,    34,    32,    11,    22,    75,
      70,    71,    74,    75,    82,    76,    36,    77,    78,    79,
      80,    80,    80,    81,    81,    82,    34,    36,    37,    75,
      36,    36,    38,    36,    33,    11,    33,    33,    72,    75,
      23,    26,    62,    63,    66,    68,    73,    74,    75,    37,
      64,    64,    38,    35,    32,    34,    63,    38,    38,    38,
      11,    34,    34,    72,    75,    27,    37,    24,    36,    32,
      32,    33,    33,    33,    36,    64,    62,    62,    38,    34,
      34,    34,    24,    33,    62,    34,    11,    14,    17,    29,
      32,    35,    76,    77,    78,    79,    80,    81,    82,    83,
      11,    14,    17,    29,    32,    35,    83,    75,    32,    82,
      82,    35,    22,    75,    15,    16,    21,    18,    19,    20,
      13,    14,    12,    82,    82,    35,    75,    82,    76,    36,
      77,    78,    79,    80,    80,    80,    81,    81,    82,    82,
      36,    36,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    41,    42,    43,    44,    44,    45,    46,
      46,    47,    47,    48,    49,    50,    50,    51,    52,    52,
      53,    54,    54,    55,    56,    56,    57,    58,    58,    59,
      60,    61,    62,    62,    63,    63,    63,    63,    63,    64,
      64,    65,    65,    65,    65,    65,    66,    66,    67,    67,
      68,    69,    70,    71,    71,    71,    72,    72,    73,    74,
      74,    75,    75,    76,    76,    77,    77,    78,    78,    79,
      79,    79,    79,    80,    80,    80,    81,    81,    82,    82,
      82,    82,    83,    83,    83
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     4,     7,     3,     1,     6,     3,
       1,     2,     1,     9,     5,     4,     3,     7,     2,     1,
       3,     1,     0,     6,     4,     3,    15,     1,     0,    12,
       9,     7,     2,     1,     1,     1,     2,     2,     2,     2,
       1,     1,     1,     2,     2,     2,     7,    11,     7,    11,
       7,     7,     5,     1,     1,     0,     1,     0,     2,     2,
       4,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     2,     2,
       4,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declarations  */
#line 54 "syntax.y"
                                                        {(yyval.node) = createNode("program", (yyvsp[0].node), NULL);
                                                        printTree((yyval.node), 0);
                                                        freeTree((yyval.node));}
#line 1819 "syntax.tab.c"
    break;

  case 3: /* program: %empty  */
#line 57 "syntax.y"
                                                        {(yyval.node) = NULL;}
#line 1825 "syntax.tab.c"
    break;

  case 4: /* declarations: scheduler dispatcher processorMult stateRecord  */
#line 61 "syntax.y"
                                                        {helper = createNode("ignore", (yyvsp[0].node), NULL);
                                                        helper2 = createNode("ignore", (yyvsp[-1].node), helper);
                                                        helper3 = createNode("ignore", (yyvsp[-2].node), helper2);
                                                        (yyval.node) = createNode("ignore", (yyvsp[-3].node), helper3);}
#line 1834 "syntax.tab.c"
    break;

  case 5: /* dispatcher: DISPATCH_T_T ID ATTRIB_OP OPEN_B dispMult CLOSE_B SEMIC  */
#line 68 "syntax.y"
                                                        {helper = createNode((yyvsp[-5].token).symbol, (yyvsp[-2].node), NULL);
                                                        (yyval.node) = createNode("dispatcherDecl", helper, NULL);}
#line 1841 "syntax.tab.c"
    break;

  case 6: /* dispMult: dispMult COMMA dispDecl  */
#line 72 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = (yyvsp[-2].node);}
#line 1848 "syntax.tab.c"
    break;

  case 7: /* dispMult: dispDecl  */
#line 74 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 1854 "syntax.tab.c"
    break;

  case 8: /* dispDecl: ID ARROW OPEN_B processorIds CLOSE_B SEMIC  */
#line 78 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[-5].token).symbol, (yyvsp[-2].node), NULL);}
#line 1860 "syntax.tab.c"
    break;

  case 9: /* processorIds: ID COMMA processorIds  */
#line 81 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[-2].token).symbol, NULL, (yyvsp[0].node));}
#line 1866 "syntax.tab.c"
    break;

  case 10: /* processorIds: ID  */
#line 82 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[0].token).symbol, NULL, NULL);}
#line 1872 "syntax.tab.c"
    break;

  case 11: /* processorMult: processorMult processorDecl  */
#line 85 "syntax.y"
                                                        {helper = createNode("ignore", (yyvsp[0].node), NULL);
                                                        (yyval.node) = createNode("ignore", (yyvsp[-1].node), helper);}
#line 1879 "syntax.tab.c"
    break;

  case 12: /* processorMult: processorDecl  */
#line 87 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 1885 "syntax.tab.c"
    break;

  case 13: /* processorDecl: PROCESSOR_T ID OPEN_P EVENT_T ID CLOSE_P OPEN_B comMultStmt CLOSE_B  */
#line 91 "syntax.y"
                                                        {helper = createNode((yyvsp[-7].token).symbol, (yyvsp[-1].node), NULL);
                                                        (yyval.node) = createNode("processorDecl", helper, NULL);}
#line 1892 "syntax.tab.c"
    break;

  case 14: /* stateRecord: STATE_R_T ID OPEN_B srVariables CLOSE_B  */
#line 96 "syntax.y"
                                                        {helper = createNode((yyvsp[-3].token).symbol, (yyvsp[-1].node), NULL);
                                                        (yyval.node) = createNode("stateRecordDecl", helper, NULL);}
#line 1899 "syntax.tab.c"
    break;

  case 15: /* srVariables: INT_T ID SEMIC srVariables  */
#line 100 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[-2].token).symbol, NULL, (yyvsp[0].node));}
#line 1905 "syntax.tab.c"
    break;

  case 16: /* srVariables: INT_T ID SEMIC  */
#line 101 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[-1].token).symbol, NULL, NULL);}
#line 1911 "syntax.tab.c"
    break;

  case 17: /* scheduler: SCHEDULER_T ID OPEN_B queues enquFunc nextEvent CLOSE_B  */
#line 105 "syntax.y"
                                                        {helper = createNode("ignore", (yyvsp[-1].node), NULL);
                                                        helper2 = createNode("ignore", (yyvsp[-2].node), helper);
                                                        helper = createNode("ignore", (yyvsp[-3].node), helper2);
                                                        helper3 = createNode((yyvsp[-5].token).symbol, helper, NULL);
                                                        (yyval.node) = createNode("schedulerDecl", helper3, NULL);}
#line 1921 "syntax.tab.c"
    break;

  case 18: /* queues: queues queueAndDrop  */
#line 112 "syntax.y"
                                                        {helper = createNode("ignore", (yyvsp[0].node), NULL);
                                                        (yyval.node) = createNode("ignore", (yyvsp[-1].node), helper);}
#line 1928 "syntax.tab.c"
    break;

  case 19: /* queues: queueAndDrop  */
#line 114 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 1934 "syntax.tab.c"
    break;

  case 20: /* queueAndDrop: qTypeDecl dropDecl queueDecl  */
#line 117 "syntax.y"
                                                        {helper = createNode("ignore", (yyvsp[0].node), NULL);
                                                        helper2 = createNode("ignore", (yyvsp[-1].node), helper);
                                                        (yyval.node) = createNode("ignore", (yyvsp[-2].node), helper2);}
#line 1942 "syntax.tab.c"
    break;

  case 21: /* qTypeDecl: queueType  */
#line 122 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 1948 "syntax.tab.c"
    break;

  case 22: /* qTypeDecl: %empty  */
#line 123 "syntax.y"
                                                        {(yyval.node) = NULL;}
#line 1954 "syntax.tab.c"
    break;

  case 23: /* queueType: EVENT_T ID OPEN_B queueTypeDecl CLOSE_B SEMIC  */
#line 127 "syntax.y"
                                                        {helper = createNode((yyvsp[-4].token).symbol, (yyvsp[-2].node), NULL);
                                                        (yyval.node) = createNode("eventDecl", helper, NULL);}
#line 1961 "syntax.tab.c"
    break;

  case 24: /* queueTypeDecl: INT_T ID SEMIC queueTypeDecl  */
#line 131 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[-2].token).symbol, NULL, (yyvsp[0].node));}
#line 1967 "syntax.tab.c"
    break;

  case 25: /* queueTypeDecl: INT_T ID SEMIC  */
#line 132 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[-1].token).symbol, NULL, NULL);}
#line 1973 "syntax.tab.c"
    break;

  case 26: /* queueDecl: QUEUE_T LESSER_OP ID GREATER_OP ID OPEN_P CONST_INT COMMA CONST_INT COMMA CONST_INT COMMA ID CLOSE_P SEMIC  */
#line 136 "syntax.y"
                                                        {helper = createNode((yyvsp[-10].token).symbol, NULL, NULL);
                                                        (yyval.node) = createNode("queueDecl", helper, NULL);}
#line 1980 "syntax.tab.c"
    break;

  case 27: /* dropDecl: dropFunc  */
#line 140 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 1986 "syntax.tab.c"
    break;

  case 28: /* dropDecl: %empty  */
#line 141 "syntax.y"
                                                        {(yyval.node) = NULL;}
#line 1992 "syntax.tab.c"
    break;

  case 29: /* dropFunc: INT_T ID OPEN_P QUEUE_T ID COMMA EVENT_T ID CLOSE_P OPEN_B dropMultStmt CLOSE_B  */
#line 145 "syntax.y"
                                                        {helper = createNode((yyvsp[-10].token).symbol, (yyvsp[-1].node), NULL);
                                                        (yyval.node) = createNode("dropDecl", helper, NULL);}
#line 1999 "syntax.tab.c"
    break;

  case 30: /* enquFunc: BOOL_T ENQUEUE OPEN_P EVENT_T ID CLOSE_P OPEN_B comMultStmt CLOSE_B  */
#line 150 "syntax.y"
                                                        {helper = createNode((yyvsp[-7].token).symbol, (yyvsp[-1].node), NULL);
                                                        (yyval.node) = createNode("enqueueDecl", helper, NULL);}
#line 2006 "syntax.tab.c"
    break;

  case 31: /* nextEvent: EVENT_T NEXT_EVENT OPEN_P CLOSE_P OPEN_B comMultStmt CLOSE_B  */
#line 155 "syntax.y"
                                                        {helper = createNode((yyvsp[-5].token).symbol, (yyvsp[-1].node), NULL);
                                                        (yyval.node) = createNode("nextEventDecl", helper, NULL);}
#line 2013 "syntax.tab.c"
    break;

  case 32: /* dropMultStmt: dropMultStmt dropStmt  */
#line 159 "syntax.y"
                                                        {helper = createNode("ignore", (yyvsp[0].node), NULL);
                                                        (yyval.node) = createNode("ignore", (yyvsp[-1].node), helper);}
#line 2020 "syntax.tab.c"
    break;

  case 33: /* dropMultStmt: dropStmt  */
#line 161 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2026 "syntax.tab.c"
    break;

  case 34: /* dropStmt: dropCondition  */
#line 164 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2032 "syntax.tab.c"
    break;

  case 35: /* dropStmt: dropLoop  */
#line 165 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2038 "syntax.tab.c"
    break;

  case 36: /* dropStmt: attribution SEMIC  */
#line 166 "syntax.y"
                                                        {(yyval.node) = (yyvsp[-1].node);}
#line 2044 "syntax.tab.c"
    break;

  case 37: /* dropStmt: return SEMIC  */
#line 167 "syntax.y"
                                                        {(yyval.node) = (yyvsp[-1].node);}
#line 2050 "syntax.tab.c"
    break;

  case 38: /* dropStmt: varDecl SEMIC  */
#line 168 "syntax.y"
                                                        {(yyval.node) = (yyvsp[-1].node);}
#line 2056 "syntax.tab.c"
    break;

  case 39: /* comMultStmt: comMultStmt commonStmt  */
#line 171 "syntax.y"
                                                        {(yyvsp[-1].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = (yyvsp[-1].node);}
#line 2063 "syntax.tab.c"
    break;

  case 40: /* comMultStmt: commonStmt  */
#line 173 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2069 "syntax.tab.c"
    break;

  case 41: /* commonStmt: comCondition  */
#line 176 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2075 "syntax.tab.c"
    break;

  case 42: /* commonStmt: comLoop  */
#line 177 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2081 "syntax.tab.c"
    break;

  case 43: /* commonStmt: attribution SEMIC  */
#line 178 "syntax.y"
                                                        {(yyval.node) = (yyvsp[-1].node);}
#line 2087 "syntax.tab.c"
    break;

  case 44: /* commonStmt: return SEMIC  */
#line 179 "syntax.y"
                                                        {(yyval.node) = (yyvsp[-1].node);}
#line 2093 "syntax.tab.c"
    break;

  case 45: /* commonStmt: varDecl SEMIC  */
#line 180 "syntax.y"
                                                        {(yyval.node) = (yyvsp[-1].node);}
#line 2099 "syntax.tab.c"
    break;

  case 46: /* dropCondition: IF OPEN_P attribution CLOSE_P OPEN_B dropMultStmt CLOSE_B  */
#line 184 "syntax.y"
                                                        {helper = createNode("ifStmts", (yyvsp[-1].node), NULL);
                                                        helper2 = createNode("ifArg", (yyvsp[-4].node), helper);
                                                        (yyval.node) = createNode("if", helper2, NULL);}
#line 2107 "syntax.tab.c"
    break;

  case 47: /* dropCondition: IF OPEN_P attribution CLOSE_P OPEN_B dropMultStmt CLOSE_B ELSE OPEN_B dropMultStmt CLOSE_B  */
#line 188 "syntax.y"
                                                        {helper = createNode("elseStmts", (yyvsp[-1].node), NULL);
                                                        helper2 = createNode("ifStmts", (yyvsp[-5].node), helper);
                                                        helper3 = createNode("ifArg", (yyvsp[-8].node), helper2);
                                                        (yyval.node) = createNode("ifelse", helper3, NULL);}
#line 2116 "syntax.tab.c"
    break;

  case 48: /* comCondition: IF OPEN_P attribution CLOSE_P OPEN_B comMultStmt CLOSE_B  */
#line 195 "syntax.y"
                                                        {helper = createNode("ifStmts", (yyvsp[-1].node), NULL);
                                                        helper2 = createNode("ifArg", (yyvsp[-4].node), helper);
                                                        (yyval.node) = createNode("if", helper2, NULL);}
#line 2124 "syntax.tab.c"
    break;

  case 49: /* comCondition: IF OPEN_P attribution CLOSE_P OPEN_B comMultStmt CLOSE_B ELSE OPEN_B comMultStmt CLOSE_B  */
#line 200 "syntax.y"
                                                        {helper = createNode("elseStmts", (yyvsp[-1].node), NULL);
                                                        helper2 = createNode("ifStmts", (yyvsp[-5].node), helper);
                                                        helper3 = createNode("ifArg", (yyvsp[-8].node), helper2);
                                                        (yyval.node) = createNode("ifelse", helper3, NULL);}
#line 2133 "syntax.tab.c"
    break;

  case 50: /* dropLoop: FOREACH ID IN ID OPEN_B dropMultStmt CLOSE_B  */
#line 207 "syntax.y"
                                                        {helper = createNode("loopStmts", (yyvsp[-1].node), NULL);
                                                        helper2 = createNode((yyvsp[-3].token).symbol, NULL, helper);
                                                        helper3 = createNode((yyvsp[-5].token).symbol, NULL, helper2);
                                                        (yyval.node) = createNode("foreach", helper3, NULL);}
#line 2142 "syntax.tab.c"
    break;

  case 51: /* comLoop: FOR OPEN_P loopArgs CLOSE_P OPEN_B comMultStmt CLOSE_B  */
#line 214 "syntax.y"
                                                        {helper = createNode("loopStmts", (yyvsp[-1].node), NULL);
                                                        (yyvsp[-4].node)->next = helper;
                                                        (yyval.node) = createNode("for", (yyvsp[-4].node), NULL);}
#line 2150 "syntax.tab.c"
    break;

  case 52: /* loopArgs: firstArgument SEMIC argument SEMIC argument  */
#line 220 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyvsp[-4].node)->next = (yyvsp[-2].node);
                                                        (yyval.node) = createNode("loopArgs", (yyvsp[-4].node), NULL);}
#line 2158 "syntax.tab.c"
    break;

  case 53: /* firstArgument: varDecl  */
#line 225 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2164 "syntax.tab.c"
    break;

  case 54: /* firstArgument: attribution  */
#line 226 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2170 "syntax.tab.c"
    break;

  case 55: /* firstArgument: %empty  */
#line 227 "syntax.y"
                                                        {(yyval.node) = NULL;}
#line 2176 "syntax.tab.c"
    break;

  case 56: /* argument: attribution  */
#line 230 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2182 "syntax.tab.c"
    break;

  case 57: /* argument: %empty  */
#line 231 "syntax.y"
                                                        {(yyval.node) = NULL;}
#line 2188 "syntax.tab.c"
    break;

  case 58: /* return: RETURN attribution  */
#line 234 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[0].node), NULL);}
#line 2194 "syntax.tab.c"
    break;

  case 59: /* varDecl: INT_T ID  */
#line 237 "syntax.y"
                                                        {(yyval.node) = NULL;}
#line 2200 "syntax.tab.c"
    break;

  case 60: /* varDecl: INT_T ID ATTRIB_OP attribution  */
#line 238 "syntax.y"
                                                        {helper = createNode((yyvsp[-2].token).symbol, NULL, (yyvsp[0].node));
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, helper, NULL);}
#line 2207 "syntax.tab.c"
    break;

  case 61: /* attribution: ID ATTRIB_OP logicalOr  */
#line 242 "syntax.y"
                                                        {helper = createNode((yyvsp[-2].token).symbol, NULL, (yyvsp[0].node));
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, helper, NULL);}
#line 2214 "syntax.tab.c"
    break;

  case 62: /* attribution: logicalOr  */
#line 244 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2220 "syntax.tab.c"
    break;

  case 63: /* logicalOr: logicalOr LOGIC_OR_OP logicalAnd  */
#line 247 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[-2].node), NULL);}
#line 2227 "syntax.tab.c"
    break;

  case 64: /* logicalOr: logicalAnd  */
#line 249 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2233 "syntax.tab.c"
    break;

  case 65: /* logicalAnd: logicalAnd LOGIC_AND_OP compareExp  */
#line 252 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[-2].node), NULL);}
#line 2240 "syntax.tab.c"
    break;

  case 66: /* logicalAnd: compareExp  */
#line 254 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2246 "syntax.tab.c"
    break;

  case 67: /* compareExp: compareExp RELAT_LOW_OP relationExp  */
#line 257 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[-2].node), NULL);}
#line 2253 "syntax.tab.c"
    break;

  case 68: /* compareExp: relationExp  */
#line 259 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2259 "syntax.tab.c"
    break;

  case 69: /* relationExp: relationExp GREATER_OP lowMathExp  */
#line 262 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[-2].node), NULL);}
#line 2266 "syntax.tab.c"
    break;

  case 70: /* relationExp: relationExp LESSER_OP lowMathExp  */
#line 264 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[-2].node), NULL);}
#line 2273 "syntax.tab.c"
    break;

  case 71: /* relationExp: relationExp RELAT_HIGH_OP lowMathExp  */
#line 266 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[-2].node), NULL);}
#line 2280 "syntax.tab.c"
    break;

  case 72: /* relationExp: lowMathExp  */
#line 268 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2286 "syntax.tab.c"
    break;

  case 73: /* lowMathExp: lowMathExp MATH_ADD_OP highMathExp  */
#line 271 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[-2].node), NULL);}
#line 2293 "syntax.tab.c"
    break;

  case 74: /* lowMathExp: lowMathExp MATH_SUB_OP highMathExp  */
#line 273 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[-2].node), NULL);}
#line 2300 "syntax.tab.c"
    break;

  case 75: /* lowMathExp: highMathExp  */
#line 275 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2306 "syntax.tab.c"
    break;

  case 76: /* highMathExp: highMathExp MATH_HIGH_OP unaryExp  */
#line 278 "syntax.y"
                                                        {(yyvsp[-2].node)->next = (yyvsp[0].node);
                                                        (yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[-2].node), NULL);}
#line 2313 "syntax.tab.c"
    break;

  case 77: /* highMathExp: unaryExp  */
#line 280 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2319 "syntax.tab.c"
    break;

  case 78: /* unaryExp: LOGIC_NOT_OP unaryExp  */
#line 284 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[0].node), NULL);}
#line 2325 "syntax.tab.c"
    break;

  case 79: /* unaryExp: MATH_SUB_OP unaryExp  */
#line 285 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[-1].token).symbol, (yyvsp[0].node), NULL);}
#line 2331 "syntax.tab.c"
    break;

  case 80: /* unaryExp: TYPE OPEN_P unaryExp CLOSE_P  */
#line 286 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[-3].token).symbol, (yyvsp[-1].node), NULL);}
#line 2337 "syntax.tab.c"
    break;

  case 81: /* unaryExp: element  */
#line 287 "syntax.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 2343 "syntax.tab.c"
    break;

  case 82: /* element: ID  */
#line 290 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[0].token).symbol, NULL, NULL);}
#line 2349 "syntax.tab.c"
    break;

  case 83: /* element: CONST_INT  */
#line 291 "syntax.y"
                                                        {(yyval.node) = createNode((yyvsp[0].token).symbol, NULL, NULL);}
#line 2355 "syntax.tab.c"
    break;

  case 84: /* element: OPEN_P attribution CLOSE_P  */
#line 292 "syntax.y"
                                                        {(yyval.node) = (yyvsp[-1].node);}
#line 2361 "syntax.tab.c"
    break;


#line 2365 "syntax.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 295 "syntax.y"


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
