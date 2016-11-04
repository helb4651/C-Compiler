/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "c-.y" /* yacc.c:339  */

/****************************************************/
/* File: c.y                                        */
/* Bison specification for c-                       */
/* CS445                                            */
/* University of Idaho                              */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "scanType.h"
#include "globals.h"
#include "symbolTable.h"
#include "semantic.h"
#include "printtree.h"
#include "typingHelpers.h"
#include <ctype.h>
#include <getopt.h>
#define YYERROR_VERBOSE







extern int yylex();
extern FILE *yyin;
static TreeNode *syntaxTree;
SymbolTable st;
// static Scope st("global");

void yyerror(char const *msg) {
    printf("ERROR(): %s\n", msg);
}






#line 108 "c-.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "c-.tab.h".  */
#ifndef YY_YY_C_TAB_H_INCLUDED
# define YY_YY_C_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    NUMCONST = 259,
    CHARCONST = 260,
    BOOLCONST = 261,
    BOOL = 262,
    BREAK = 263,
    CHAR = 264,
    ELSE = 265,
    IF = 266,
    INT = 267,
    RETURN = 268,
    STATIC = 269,
    WHILE = 270,
    NOTEQ = 271,
    EQEQ = 272,
    LESSEQ = 273,
    GRTEQ = 274,
    INC = 275,
    DEC = 276,
    ADDASS = 277,
    SUBASS = 278,
    MULASS = 279,
    DIVASS = 280,
    EQ = 281,
    LESS = 282,
    GRT = 283,
    TRUE = 284,
    FALSE = 285,
    KEYWORD = 286,
    STAR = 287,
    MINUS = 288,
    PLUS = 289,
    DIVIDE = 290,
    MOD = 291,
    QMARK = 292,
    OPS = 293,
    RECORD = 294,
    AND = 295,
    OR = 296,
    NOT = 297,
    NULCHAR = 298,
    EMPTSTR = 299,
    RECTYPE = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 44 "c-.y" /* yacc.c:355  */

    Token token;
    TreeNode *treeNode;
    DeclType declType;
    char *cstring;

#line 201 "c-.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 218 "c-.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      46,    47,     2,     2,    53,     2,    52,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,    54,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    51,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   125,   125,   128,   138,   141,   142,   143,   149,   165,
     181,   197,   207,   211,   212,   219,   225,   236,   241,   264,
     265,   266,   267,   274,   283,   295,   296,   300,   310,   314,
     329,   339,   343,   348,   370,   371,   374,   375,   376,   377,
     378,   379,   382,   383,   387,   397,   409,   418,   428,   433,
     443,   447,   448,   458,   469,   478,   496,   502,   512,   522,
     530,   538,   546,   554,   562,   570,   578,   582,   589,   594,
     601,   606,   612,   616,   623,   627,   628,   629,   630,   631,
     632,   636,   643,   647,   648,   652,   660,   664,   665,   666,
     670,   676,   680,   681,   682,   686,   687,   692,   697,   704,
     712,   719,   720,   721,   725,   734,   735,   739,   749,   753,
     759,   765
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "NUMCONST", "CHARCONST",
  "BOOLCONST", "BOOL", "BREAK", "CHAR", "ELSE", "IF", "INT", "RETURN",
  "STATIC", "WHILE", "NOTEQ", "EQEQ", "LESSEQ", "GRTEQ", "INC", "DEC",
  "ADDASS", "SUBASS", "MULASS", "DIVASS", "EQ", "LESS", "GRT", "TRUE",
  "FALSE", "KEYWORD", "STAR", "MINUS", "PLUS", "DIVIDE", "MOD", "QMARK",
  "OPS", "RECORD", "AND", "OR", "NOT", "NULCHAR", "EMPTSTR", "RECTYPE",
  "'('", "')'", "'{'", "'}'", "'['", "']'", "'.'", "','", "';'", "':'",
  "$accept", "program", "declarationList", "declaration", "recDeclaration",
  "varDeclaration", "scopedVarDeclaration", "varDeclList",
  "varDeclInitialize", "varDeclId", "scopedTypeSpecifier", "typeSpecifier",
  "funDeclaration", "params", "paramList", "paramTypeList", "paramIdList",
  "paramId", "statement", "matched", "unmatched", "matchedIteration",
  "unmatchedIteration", "compoundStmt", "localDeclarations",
  "statementList", "expressionStmt", "matched_selection",
  "unmatched_selection", "returnStmt", "breakStmt", "expression",
  "simpleExpression", "andExpression", "unaryRelExpression",
  "relExpression", "relop", "sumExpression", "sumop", "term", "mulop",
  "unaryExpression", "unaryop", "factor", "mutable", "monkey", "immutable",
  "call", "args", "argList", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    40,    41,   123,   125,
      91,    93,    46,    44,    59,    58
};
# endif

#define YYPACT_NINF -156

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-156)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     129,   -33,  -156,  -156,  -156,    29,  -156,    30,   129,  -156,
    -156,  -156,    41,  -156,     8,     1,  -156,  -156,    39,     3,
    -156,   -13,    44,    23,    32,  -156,  -156,     8,    73,    88,
    -156,     6,    46,    51,  -156,    97,     8,   128,    45,    43,
      47,  -156,    53,  -156,  -156,  -156,  -156,  -156,  -156,     6,
       6,    65,    67,  -156,  -156,   176,    27,  -156,   121,  -156,
     -34,  -156,  -156,  -156,    60,    44,    59,    68,   115,    69,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,  -156,  -156,    62,    65,   165,  -156,     8,  -156,  -156,
      88,  -156,    97,  -156,     6,  -156,    70,     6,     6,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,   121,   121,  -156,
    -156,  -156,   121,  -156,     6,   119,  -156,  -156,  -156,     6,
    -156,    74,     6,   169,  -156,  -156,  -156,     6,     6,     6,
       6,     6,  -156,    15,  -156,  -156,    84,    80,  -156,    67,
    -156,    42,    27,  -156,    93,  -156,  -156,    -6,  -156,    -1,
      18,  -156,  -156,  -156,  -156,  -156,  -156,  -156,     6,  -156,
      97,    97,  -156,  -156,  -156,  -156,   136,  -156,  -156,    97,
    -156,  -156
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    21,    22,    19,     0,    20,     0,     2,     4,
       7,     5,     0,     6,    26,     0,     1,     3,    15,     0,
      12,    13,     0,     0,    25,    28,    48,    26,     0,     0,
       9,     0,    32,    29,    31,     0,     0,     0,     0,     0,
      15,    11,    97,   109,   110,   111,    93,    92,    94,     0,
       0,    14,    68,    70,    72,    74,    82,    86,     0,    91,
      96,    95,   102,   103,     0,     0,     0,     0,     0,     0,
      48,    52,    24,    35,    34,    39,    43,    38,    37,    36,
      42,    40,    41,     0,    66,    96,    27,     0,     8,    47,
       0,    18,     0,    16,   106,    71,     0,     0,     0,    80,
      79,    75,    78,    76,    77,    84,    83,     0,     0,    87,
      88,    89,     0,    90,     0,     0,    33,    30,    58,     0,
      56,     0,     0,    50,    51,    64,    65,     0,     0,     0,
       0,     0,    17,     0,    23,   108,     0,   105,   101,    67,
      69,    73,    81,    85,     0,   100,    99,     0,    57,     0,
       0,    60,    61,    62,    63,    59,    10,   104,     0,    98,
       0,     0,    46,    49,   107,    55,    35,    44,    45,     0,
      53,    54
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -156,  -156,  -156,   141,  -156,  -156,  -156,    66,   126,  -156,
    -156,     0,  -156,   123,  -156,   124,  -156,    94,   -89,  -133,
    -155,  -156,  -156,  -156,    92,  -156,  -156,  -156,  -156,  -156,
    -156,   -49,   -29,    75,   -44,  -156,  -156,    56,  -156,    57,
    -156,   -54,  -156,  -156,   -24,  -156,  -156,  -156,  -156,  -156,
    -156
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,    89,    19,    20,    21,
      90,    22,    13,    23,    24,    25,    33,    34,    72,    73,
      74,    75,    76,    77,    37,   150,    78,    79,    80,    81,
      82,    83,    84,    52,    53,    54,   107,    55,   108,    56,
     112,    57,    58,    59,    85,   146,    61,    62,   136,   137,
      63
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      12,    96,    51,   134,   113,    95,   168,    60,    12,    42,
      43,    44,    45,    14,   171,     2,   114,     3,   115,   121,
       4,    42,    43,    44,    45,    60,    66,   166,   167,    67,
      16,    68,    15,    69,    60,    97,   170,    91,    46,    47,
      97,   160,    31,    48,    18,   135,   161,    32,    49,    26,
      46,    47,    50,     6,   140,    48,    29,    30,   143,   109,
      49,   163,   110,   111,    50,   144,    70,   162,    29,   156,
      35,   165,    71,    60,    60,   105,   106,    39,   151,   152,
     153,   154,   155,    60,    60,    27,    36,   132,    60,    28,
     147,    40,    92,   149,    93,    60,    64,    28,    60,    94,
      42,    43,    44,    45,    65,    66,    97,    98,    67,   164,
      68,   116,    69,   118,   119,   122,   124,   138,    42,    43,
      44,    45,   145,    91,    42,    43,    44,    45,   148,    46,
      47,   157,     1,   158,    48,     2,     2,     3,     3,    49,
       4,     4,    87,    50,   159,    70,   169,    46,    47,    17,
      38,    71,    48,    46,    47,    41,   133,    49,    48,   117,
      86,    50,   123,   141,     0,   142,     0,    50,     5,   120,
       0,     0,   139,     6,     6,     0,     2,    88,     3,     0,
       0,     4,     0,    87,     0,   125,   126,   127,   128,   129,
     130,   131,    99,   100,   101,   102,     0,     0,     0,     0,
       0,     0,     0,   103,   104,     0,     0,     0,     0,   105,
     106,     0,     0,     0,     6,   114,     0,   115
};

static const yytype_int16 yycheck[] =
{
       0,    50,    31,    92,    58,    49,   161,    31,     8,     3,
       4,     5,     6,    46,   169,     7,    50,     9,    52,    68,
      12,     3,     4,     5,     6,    49,     8,   160,   161,    11,
       0,    13,     3,    15,    58,    41,   169,    37,    32,    33,
      41,    47,    55,    37,     3,    94,    47,     3,    42,    48,
      32,    33,    46,    45,    98,    37,    53,    54,   112,    32,
      42,   150,    35,    36,    46,   114,    48,    49,    53,    54,
      47,   160,    54,    97,    98,    33,    34,     4,   127,   128,
     129,   130,   131,   107,   108,    46,    54,    87,   112,    50,
     119,     3,    47,   122,    51,   119,    50,    50,   122,    46,
       3,     4,     5,     6,    53,     8,    41,    40,    11,   158,
      13,    51,    15,    54,    46,    46,    54,    47,     3,     4,
       5,     6,     3,   123,     3,     4,     5,     6,    54,    32,
      33,    47,     3,    53,    37,     7,     7,     9,     9,    42,
      12,    12,    14,    46,    51,    48,    10,    32,    33,     8,
      27,    54,    37,    32,    33,    29,    90,    42,    37,    65,
      36,    46,    70,   107,    -1,   108,    -1,    46,    39,    54,
      -1,    -1,    97,    45,    45,    -1,     7,    49,     9,    -1,
      -1,    12,    -1,    14,    -1,    20,    21,    22,    23,    24,
      25,    26,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    45,    50,    -1,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     7,     9,    12,    39,    45,    57,    58,    59,
      60,    61,    67,    68,    46,     3,     0,    59,     3,    63,
      64,    65,    67,    69,    70,    71,    48,    46,    50,    53,
      54,    55,     3,    72,    73,    47,    54,    80,    69,     4,
       3,    64,     3,     4,     5,     6,    32,    33,    37,    42,
      46,    88,    89,    90,    91,    93,    95,    97,    98,    99,
     100,   102,   103,   106,    50,    53,     8,    11,    13,    15,
      48,    54,    74,    75,    76,    77,    78,    79,    82,    83,
      84,    85,    86,    87,    88,   100,    71,    14,    49,    62,
      66,    67,    47,    51,    46,    90,    87,    41,    40,    16,
      17,    18,    19,    27,    28,    33,    34,    92,    94,    32,
      35,    36,    96,    97,    50,    52,    51,    73,    54,    46,
      54,    87,    46,    80,    54,    20,    21,    22,    23,    24,
      25,    26,    67,    63,    74,    87,   104,   105,    47,    89,
      90,    93,    95,    97,    87,     3,   101,    88,    54,    88,
      81,    87,    87,    87,    87,    87,    54,    47,    53,    51,
      47,    47,    49,    74,    87,    74,    75,    75,    76,    10,
      75,    76
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    60,    61,
      62,    63,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    67,    67,    68,    68,    69,    69,    70,    70,    71,
      72,    72,    73,    73,    74,    74,    75,    75,    75,    75,
      75,    75,    76,    76,    77,    78,    79,    80,    80,    81,
      81,    82,    82,    83,    84,    84,    85,    85,    86,    87,
      87,    87,    87,    87,    87,    87,    87,    88,    88,    89,
      89,    90,    90,    91,    91,    92,    92,    92,    92,    92,
      92,    93,    93,    94,    94,    95,    95,    96,    96,    96,
      97,    97,    98,    98,    98,    99,    99,   100,   100,   100,
     101,   102,   102,   102,   103,   104,   104,   105,   105,   106,
     106,   106
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     5,     3,
       3,     3,     1,     1,     3,     1,     4,     2,     1,     1,
       1,     1,     1,     6,     5,     1,     0,     3,     1,     2,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     5,     4,     2,     0,     2,
       0,     2,     1,     7,     7,     5,     2,     3,     2,     3,
       3,     3,     3,     3,     2,     2,     1,     3,     1,     3,
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     4,     3,
       1,     3,     1,     1,     4,     1,     0,     3,     1,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 125 "c-.y" /* yacc.c:1661  */
    { syntaxTree = (yyvsp[0].treeNode); }
#line 1446 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 3:
#line 128 "c-.y" /* yacc.c:1661  */
    {
                               TreeNode *node = (yyvsp[-1].treeNode);
                               if(node != NULL) {
                                   while (node->sibling != NULL) node = node->sibling;
                                   node->sibling = (yyvsp[0].treeNode);
                                   (yyval.treeNode) = (yyvsp[-1].treeNode);
                               } else {
                                   (yyval.treeNode) = (yyvsp[0].treeNode);
                               }
                            }
#line 1461 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 4:
#line 138 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1467 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 5:
#line 141 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1473 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 6:
#line 142 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1479 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 7:
#line 143 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1485 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 8:
#line 149 "c-.y" /* yacc.c:1661  */
    {
                     st.insert( (yyvsp[-3].token).tokenstring, (char *)"record"); // add to record symbol table

                     (yyval.treeNode) = newDeclNode(RecordK);
                     (yyval.treeNode)->declType = Record;
                     (yyval.treeNode)->attr.name = (yyvsp[-3].token).sval;
                     (yyval.treeNode)->attrType = Name;
                     (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode);
                     (yyval.treeNode)->linenum = (yyvsp[-2].token).linenum;
                     (yyval.treeNode)->isRecord=true;
              }
#line 1501 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 9:
#line 165 "c-.y" /* yacc.c:1661  */
    {
                                TreeNode *complete = (yyvsp[-1].treeNode);
                                if(complete != NULL) {
                                    do {
                                        complete -> declType = (yyvsp[-2].declType);
                                        complete = complete -> sibling;

                                    } while(complete != NULL);
                                    (yyval.treeNode) = (yyvsp[-1].treeNode);
                                } else {
                                    (yyval.treeNode) = NULL;
                                }
                            }
#line 1519 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 10:
#line 181 "c-.y" /* yacc.c:1661  */
    {
                                TreeNode *complete = (yyvsp[-1].treeNode);
                                if(complete != NULL) {
                                    do {
                                        complete->declType = (yyvsp[-2].treeNode)->declType;
                                        complete->isStatic = (yyvsp[-2].treeNode)->isStatic;
                                        complete = complete->sibling;
                                    } while(complete != NULL);
                                    (yyval.treeNode) = (yyvsp[-1].treeNode);
                                } else {
                                    (yyval.treeNode) = NULL;
                                }
                            }
#line 1537 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 11:
#line 197 "c-.y" /* yacc.c:1661  */
    {
                               TreeNode *node = (yyvsp[-2].treeNode);
                               if(node != NULL) {
                                    while(node->sibling != NULL) node = node->sibling;
                                    node->sibling = (yyvsp[0].treeNode);
                                    (yyval.treeNode) = (yyvsp[-2].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[0].treeNode);
                                }
                            }
#line 1552 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 12:
#line 207 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1558 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 13:
#line 211 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1564 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 14:
#line 212 "c-.y" /* yacc.c:1661  */
    {
                            (yyvsp[-2].treeNode)->child[0] = (yyvsp[0].treeNode); // <- NOT NULL, SHOULD BE $3
                            (yyval.treeNode) = (yyvsp[-2].treeNode);
                        }
#line 1573 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 15:
#line 219 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newDeclNode(VarK);
                                (yyval.treeNode)->attr.name = (yyvsp[0].token).sval;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->linenum = (yyvsp[0].token).linenum;
                            }
#line 1584 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 16:
#line 225 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newDeclNode(VarK);
                            (yyval.treeNode)->attr.name = (yyvsp[-3].token).sval;
                            (yyval.treeNode)->attrType = Name;
                            (yyval.treeNode)->isArray = true;
                            (yyval.treeNode)->arrayLen = (yyvsp[-1].token).ival;
                            (yyval.treeNode)->linenum = (yyvsp[-3].token).linenum;
                        }
#line 1597 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 17:
#line 236 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newDeclNode(VarK);
                                (yyval.treeNode)->isStatic = true;
                                (yyval.treeNode)->declType = (yyvsp[0].declType);
                            }
#line 1607 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 18:
#line 241 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newDeclNode(VarK);
                            (yyval.treeNode)->declType = (yyvsp[0].declType);
                        }
#line 1616 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 19:
#line 264 "c-.y" /* yacc.c:1661  */
    { (yyval.declType) = Int; }
#line 1622 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 20:
#line 265 "c-.y" /* yacc.c:1661  */
    { (yyval.declType) = Record; }
#line 1628 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 21:
#line 266 "c-.y" /* yacc.c:1661  */
    { (yyval.declType) = Bool; }
#line 1634 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 22:
#line 267 "c-.y" /* yacc.c:1661  */
    { (yyval.declType) = Char; }
#line 1640 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 23:
#line 274 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newDeclNode(FuncK);
                                (yyval.treeNode)->declType = (yyvsp[-5].declType);
                                (yyval.treeNode)->attr.name = (yyvsp[-4].token).sval;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                                (yyval.treeNode)->linenum = (yyvsp[-3].token).linenum; // Allows for correct line no
                            }
#line 1654 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 24:
#line 283 "c-.y" /* yacc.c:1661  */
    {
                           (yyval.treeNode) = newDeclNode(FuncK);
                           (yyval.treeNode)->declType = Void;
                           (yyval.treeNode)->attr.name = (yyvsp[-4].token).sval;
                           (yyval.treeNode)->attrType = Name;
                           (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                           (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                           (yyval.treeNode)->linenum = (yyvsp[-3].token).linenum;
                        }
#line 1668 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 25:
#line 295 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1674 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 26:
#line 296 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = NULL; }
#line 1680 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 27:
#line 300 "c-.y" /* yacc.c:1661  */
    {
                                TreeNode *node = (yyvsp[-2].treeNode);
                                if(node != NULL) {
                                    while(node->sibling != NULL) node = node->sibling;
                                    node->sibling = (yyvsp[0].treeNode);
                                    (yyval.treeNode) = (yyvsp[-2].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[0].treeNode);
                                }
                            }
#line 1695 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 28:
#line 310 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1701 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 29:
#line 314 "c-.y" /* yacc.c:1661  */
    {
                                TreeNode *complete = (yyvsp[0].treeNode);
                                if(complete != NULL) {
                                    do {
                                        complete->declType = (yyvsp[-1].declType);
                                        complete = complete->sibling;
                                    } while(complete != NULL);
                                    (yyval.treeNode) = (yyvsp[0].treeNode);
                                } else {
                                    (yyval.treeNode) = NULL;
                                }
                            }
#line 1718 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 30:
#line 329 "c-.y" /* yacc.c:1661  */
    {
                               TreeNode *node = (yyvsp[-2].treeNode);
                               if(node != NULL) {
                                   while(node->sibling != NULL) node = node->sibling;
                                   node->sibling = (yyvsp[0].treeNode);
                                   (yyval.treeNode) = (yyvsp[-2].treeNode);
                               } else {
                                   (yyval.treeNode) = (yyvsp[0].treeNode);
                               }
                            }
#line 1733 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 31:
#line 339 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1739 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 32:
#line 343 "c-.y" /* yacc.c:1661  */
    {
                               (yyval.treeNode) = newDeclNode(ParamK);
                               (yyval.treeNode)->attr.name = (yyvsp[0].token).sval;
                               (yyval.treeNode)->attrType = Name;
                            }
#line 1749 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 33:
#line 348 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newDeclNode(ParamK);
                                (yyval.treeNode)->attr.name = (yyvsp[-2].token).sval;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->isArray = true;
                              }
#line 1760 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 34:
#line 370 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1766 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 35:
#line 371 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1772 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 36:
#line 374 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1778 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 37:
#line 375 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1784 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 38:
#line 376 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1790 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 39:
#line 377 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1796 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 40:
#line 378 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1802 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 41:
#line 379 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1808 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 42:
#line 382 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1814 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 43:
#line 383 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1820 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 44:
#line 387 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newStmtNode(WhileK);
                                (yyval.treeNode)->attr.name = (yyvsp[-4].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                                (yyval.treeNode)->linenum = (yyvsp[-4].token).linenum;
                            }
#line 1833 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 45:
#line 397 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newStmtNode(WhileK);
                                (yyval.treeNode)->attr.name = (yyvsp[-4].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                                (yyval.treeNode)->linenum = (yyvsp[-4].token).linenum;
                            }
#line 1846 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 46:
#line 409 "c-.y" /* yacc.c:1661  */
    {
                               (yyval.treeNode) = newStmtNode(CompK);
                               (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                               (yyval.treeNode)->child[1] = (yyvsp[-1].treeNode);
                               (yyval.treeNode)->linenum = (yyvsp[-3].token).linenum;
                            }
#line 1857 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 47:
#line 418 "c-.y" /* yacc.c:1661  */
    {
                                TreeNode *node = (yyvsp[-1].treeNode);
                                if(node != NULL) {
                                    while(node->sibling != NULL) node = node->sibling;
                                    node->sibling = (yyvsp[0].treeNode);
                                    (yyval.treeNode) = (yyvsp[-1].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[0].treeNode);
                                }
                            }
#line 1872 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 48:
#line 428 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = NULL; }
#line 1878 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 49:
#line 433 "c-.y" /* yacc.c:1661  */
    {
                                TreeNode *node = (yyvsp[-1].treeNode);
                                if(node != NULL) {
                                    while(node->sibling != NULL) node = node->sibling;
                                    node->sibling = (yyvsp[0].treeNode);
                                    (yyval.treeNode) = (yyvsp[-1].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[0].treeNode);
                                }
                            }
#line 1893 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 50:
#line 443 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = NULL; }
#line 1899 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 51:
#line 447 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[-1].treeNode); }
#line 1905 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 52:
#line 448 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = NULL; }
#line 1911 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 53:
#line 458 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newStmtNode(IfK);
                                (yyval.treeNode)->attr.name = (yyvsp[-6].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
                                (yyval.treeNode)->child[2] = (yyvsp[0].treeNode);
                                (yyval.treeNode)->linenum = (yyvsp[-6].token).linenum;
                            }
#line 1925 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 54:
#line 469 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newStmtNode(IfK);
                                (yyval.treeNode)->attr.name = (yyvsp[-6].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
                                (yyval.treeNode)->child[2] = (yyvsp[0].treeNode);
                                (yyval.treeNode)->linenum = (yyvsp[-6].token).linenum;
                            }
#line 1939 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 55:
#line 478 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newStmtNode(IfK);
                            (yyval.treeNode)->attr.name = (yyvsp[-4].token).tokenstring;
                            (yyval.treeNode)->attrType = Name;
                            (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                            (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                            (yyval.treeNode)->linenum = (yyvsp[-4].token).linenum;
                        }
#line 1952 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 56:
#line 496 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newStmtNode(ReturnK);
                                (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->linenum = (yyvsp[-1].token).linenum;
                            }
#line 1963 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 57:
#line 502 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newStmtNode(ReturnK);
                            (yyval.treeNode)->attr.name = (yyvsp[-2].token).tokenstring;
                            (yyval.treeNode)->attrType = Name;
                            (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode);
                            (yyval.treeNode)->linenum = (yyvsp[-2].token).linenum;
                        }
#line 1975 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 58:
#line 512 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newStmtNode(BreakK);
                                (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                            }
#line 1985 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 59:
#line 522 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newExprNode(AssignK);
                                (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                                (yyval.treeNode)->linenum = (yyvsp[-1].token).linenum;
                            }
#line 1998 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 60:
#line 530 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newExprNode(AssignK);
                            (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                            (yyval.treeNode)->attrType = Name;
                            (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                            (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                            (yyval.treeNode)->linenum = (yyvsp[-1].token).linenum;
                        }
#line 2011 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 61:
#line 538 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newExprNode(AssignK);
                            (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                            (yyval.treeNode)->attrType = Name;
                            (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                            (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                            (yyval.treeNode)->linenum = (yyvsp[-1].token).linenum;
                        }
#line 2024 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 62:
#line 546 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newExprNode(AssignK);
                            (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                            (yyval.treeNode)->attrType = Name;
                            (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                            (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                            (yyval.treeNode)->linenum = (yyvsp[-1].token).linenum;
                        }
#line 2037 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 63:
#line 554 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newExprNode(AssignK);
                            (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                            (yyval.treeNode)->attrType = Name;
                            (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                            (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                            (yyval.treeNode)->linenum = (yyvsp[-1].token).linenum;
                        }
#line 2050 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 64:
#line 562 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newExprNode(AssignK);
                            (yyval.treeNode)->attr.name = (yyvsp[0].token).tokenstring;
                            (yyval.treeNode)->attrType = Name;
                            (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode);
                            //$$->child[1] = $3;
                            (yyval.treeNode)->linenum = (yyvsp[0].token).linenum;
                        }
#line 2063 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 65:
#line 570 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newExprNode(AssignK);
                            (yyval.treeNode)->attr.name = (yyvsp[0].token).tokenstring;
                            (yyval.treeNode)->attrType = Name;
                            (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode);
                            //$$->child[1] = $3;
                            (yyval.treeNode)->linenum = (yyvsp[0].token).linenum;
                        }
#line 2076 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 66:
#line 578 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2082 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 67:
#line 582 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                            }
#line 2094 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 68:
#line 589 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2100 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 69:
#line 594 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                            }
#line 2112 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 70:
#line 601 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2118 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 71:
#line 606 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[0].treeNode);
                            }
#line 2129 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 72:
#line 612 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2135 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 73:
#line 616 "c-.y" /* yacc.c:1661  */
    {
                               (yyval.treeNode) = newExprNode(OpK);
                               (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                               (yyval.treeNode)->attrType = Name;
                               (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                               (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                            }
#line 2147 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 74:
#line 623 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2153 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 75:
#line 627 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2159 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 76:
#line 628 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2165 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 77:
#line 629 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2171 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 78:
#line 630 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2177 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 79:
#line 631 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2183 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 80:
#line 632 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2189 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 81:
#line 636 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                            }
#line 2201 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 82:
#line 643 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2207 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 83:
#line 647 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2213 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 84:
#line 648 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2219 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 85:
#line 652 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                                (yyval.treeNode)->linenum = (yyvsp[-1].token).linenum;
                            }
#line 2232 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 86:
#line 660 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2238 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 87:
#line 664 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2244 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 88:
#line 665 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2250 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 89:
#line 666 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2256 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 90:
#line 670 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                                (yyval.treeNode)->attrType = Name;
                                (yyval.treeNode)->child[0] = (yyvsp[0].treeNode);
                            }
#line 2267 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 91:
#line 676 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2273 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 92:
#line 680 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2279 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 93:
#line 681 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2285 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 94:
#line 682 "c-.y" /* yacc.c:1661  */
    { (yyval.token) = (yyvsp[0].token); }
#line 2291 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 95:
#line 686 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2297 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 96:
#line 687 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2303 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 97:
#line 692 "c-.y" /* yacc.c:1661  */
    {
                               (yyval.treeNode) = newExprNode(IdK);
                               (yyval.treeNode)->attr.name = (yyvsp[0].token).sval;
                               (yyval.treeNode)->attrType = Name;
                            }
#line 2313 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 98:
#line 697 "c-.y" /* yacc.c:1661  */
    {
                           (yyval.treeNode) = newExprNode(OpK);
                           (yyval.treeNode)->attr.name = (yyvsp[-2].token).tokenstring;
                           (yyval.treeNode)->attrType = Name;
                           (yyval.treeNode)->child[0] = (yyvsp[-3].treeNode);
                           (yyval.treeNode)->child[1] = (yyvsp[-1].treeNode);
                        }
#line 2325 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 99:
#line 704 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newExprNode(OpK);
                            (yyval.treeNode)->attr.name = (yyvsp[-1].token).tokenstring;
                            (yyval.treeNode)->attrType = Name;
                            (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                            (yyval.treeNode)->child[1] = (yyvsp[0].treeNode);
                                    }
#line 2337 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 100:
#line 712 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newExprNode(IdK);
                            (yyval.treeNode)->attr.name = (yyvsp[0].token).sval;
                            (yyval.treeNode)->attrType = Name;
                          }
#line 2347 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 101:
#line 719 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[-1].treeNode); }
#line 2353 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 102:
#line 720 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2359 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 103:
#line 721 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2365 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 104:
#line 725 "c-.y" /* yacc.c:1661  */
    {
                               (yyval.treeNode) = newExprNode(CallK);
                               (yyval.treeNode)->attr.name = (yyvsp[-3].token).sval;
                               (yyval.treeNode)->attrType = Name;
                               (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode);
                            }
#line 2376 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 105:
#line 734 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2382 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 106:
#line 735 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = NULL; }
#line 2388 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 107:
#line 739 "c-.y" /* yacc.c:1661  */
    {
                                TreeNode *node = (yyvsp[-2].treeNode);
                                if(node != NULL) {
                                    while(node->sibling != NULL) node = node->sibling;
                                    node->sibling = (yyvsp[0].treeNode);
                                    (yyval.treeNode) = (yyvsp[-2].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[0].treeNode);
                                }
                            }
#line 2403 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 108:
#line 749 "c-.y" /* yacc.c:1661  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2409 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 109:
#line 753 "c-.y" /* yacc.c:1661  */
    {
                                (yyval.treeNode) = newExprNode(ConstK);
                                (yyval.treeNode)->attr.value = (yyvsp[0].token).ival;
                                (yyval.treeNode)->attrType = Value;
                                (yyval.treeNode)->declType = Int;
                            }
#line 2420 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 110:
#line 759 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newExprNode(ConstK);
                            (yyval.treeNode)->attr.cvalue = (yyvsp[0].token).cval;
                            (yyval.treeNode)->attrType = CValue;
                            (yyval.treeNode)->declType = Char;
                        }
#line 2431 "c-.tab.c" /* yacc.c:1661  */
    break;

  case 111:
#line 765 "c-.y" /* yacc.c:1661  */
    {
                            (yyval.treeNode) = newExprNode(ConstK);
                            (yyval.treeNode)->attr.value = (yyvsp[0].token).ival;
                            (yyval.treeNode)->attrType = Value;
                            (yyval.treeNode)->declType = Bool;
                        }
#line 2442 "c-.tab.c" /* yacc.c:1661  */
    break;


#line 2446 "c-.tab.c" /* yacc.c:1661  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 774 "c-.y" /* yacc.c:1906  */

int main(int argc, char** argv) {
  int c;
  bool print_ast_no_types  = false;
  bool print_ast_types = false;

  while((c = getopt(argc, argv, "dpP")) != EOF) {
      switch(c) {
          default:
              abort();
              break;
          case 'd':
              yydebug = 1;
              break;
          case 'p':
              print_ast_no_types=true;
              break;
          case 'P':
              print_ast_types=true;
              break;
      }
  }


  extern FILE *yyin;
  if(print_ast_no_types==false && print_ast_types==false && yydebug==0){
    yyin = fopen(argv[1], "r");
  } else {
    yyin = fopen(argv[2], "r");
  }
  yyparse();


    TreeNode* input = newDeclNode(FuncK);
    input->attr.name = "input";
    input->linenum=-1;
    input->declType=Int;
    //semanticsSymbolTable.insert((char *) "input", input);

    TreeNode* output_child = newDeclNode(ParamK);
    output_child->attr.name = "*dummy*";
    output_child->linenum=-1;
    output_child->declType=Int;

    TreeNode* output = newDeclNode(FuncK);
    output->attr.name = "output";
    output->linenum=-1;
    output->child[0]=output_child;

    TreeNode* inputb = newDeclNode(FuncK);
    inputb->attr.name = "inputb";
    inputb->linenum=-1;
    inputb->declType=Bool;

    TreeNode* output_childb = newDeclNode(ParamK);
    output_childb->attr.name = "*dummy*";
    output_childb->linenum=-1;
    output_childb->declType=Bool;

    TreeNode* outputb = newDeclNode(FuncK);
    outputb->attr.name = "outputb";
    outputb->linenum=-1;
    outputb->child[0]=output_childb;

    TreeNode* inputc = newDeclNode(FuncK);
    inputc->attr.name = "inputc";
    inputc->linenum=-1;
    inputc->declType=Char;

    TreeNode* output_childc = newDeclNode(ParamK);
    output_childc->attr.name = "*dummy*";
    output_childc->linenum=-1;

    TreeNode* outputc = newDeclNode(FuncK);
    outputc->attr.name = "outputc";
    outputc->linenum=-1;
    outputc->child[0]=output_childc;

    TreeNode* outnl = newDeclNode(FuncK);
    outnl->attr.name = "outnl";
    outnl->linenum=-1;

    input->sibling = output;
    output->sibling = inputb;
    inputb->sibling = outputb;
    outputb->sibling = inputc;
    inputc->sibling = outputc;
    outputc->sibling = outnl;
    outnl->sibling = syntaxTree;

    //cout << "HEY!! " << output->sibling->attr.name << endl;
    syntaxTree = input;

  if(print_ast_no_types) {
    printTree(syntaxTree, -1, false);
    getTypesDataStructure();
    scopeAndType(syntaxTree, -1, false);
            TreeNode* n = static_cast<TreeNode*>(semanticsSymbolTable.lookup("main"));
            if(main_function_exists==false && n==NULL) {
                number_of_errors++;
                printf("ERROR(LINKER): Procedure main is not defined.\n");
            }
    printf("Number of warnings: 0\n");
    printf("Number of errors: %d\n", number_of_errors);
  }

  else if(print_ast_types) {
    getTypesDataStructure();
    scopeAndType(syntaxTree, -1, false);

        TreeNode* n = static_cast<TreeNode*>(semanticsSymbolTable.lookup("main"));
        if(main_function_exists==false && n==NULL) {
            number_of_errors++;
            printf("ERROR(LINKER): Procedure main is not defined.\n");
        }
    printTree(syntaxTree, -1, true);
    printf("Number of warnings: 0\n");
    printf("Number of errors: %d\n", number_of_errors);
  }

  else {
    getTypesDataStructure();
    scopeAndType(syntaxTree, -1, false);
            TreeNode* n = static_cast<TreeNode*>(semanticsSymbolTable.lookup("main"));
            if(main_function_exists==false && n==NULL) {
                number_of_errors++;
                printf("ERROR(LINKER): Procedure main is not defined.\n");
            }
    printf("Number of warnings: 0\n");
    printf("Number of errors: %d\n", number_of_errors);
  }

  return 0;
}
