/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "NEW_PASCC.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 抽象语法树头文件 */
#include "ast.h"
//#include "ast_class.h"

#include "symbol_table.h"
extern SymbolTable* globalSymbolTable;
extern SymbolTable* currentSymbolTable;

// void yyerror(const char *s);
// extern int yylex();
// extern FILE *yyin;
extern "C"			
{					
    void yyerror(const char *s);
    extern int yylex(void);
    extern int line_count;
    extern bool new_line_flag;
    extern int yyleng;
    extern int last_line_count;
}
using std::string;

extern void printNodeType(ASTNode* node, int indent = 0);

void yyerror(ASTNode** root, const char *msg);
void yyerror_var(ASTNode** root, const char *msg);
void yynote(std::string msg, int line);

#define GET_INT_VAL(ptr) (ptr)->value.int_value
#define GET_REAL_VAL(ptr) (ptr)->value.real_value
#define GET_CHAR_VAL(ptr) (ptr)->value.char_value
#define GET_BOOL_VAL(ptr) (ptr)->value.bool_value
#define GET_STR_VAL(ptr) (ptr)->string_value
#define GET_TYPE(ptr) (ptr)->type

/* Line 371 of yacc.c  */
#line 109 "NEW_PASCC.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "NEW_PASCC.tab.h".  */
#ifndef YY_YY_NEW_PASCC_TAB_H_INCLUDED
# define YY_YY_NEW_PASCC_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_NUM = 258,
     REAL_NUM = 259,
     CHAR = 260,
     BOO_LEAN = 261,
     STRING = 262,
     BASIC_TYPE = 263,
     IDENTIFIER = 264,
     ARRAY = 265,
     BEGIN_ = 266,
     BREAK = 267,
     CASE = 268,
     CONST = 269,
     CONTINUE = 270,
     DO = 271,
     DOWNTO = 272,
     ELSE = 273,
     END = 274,
     FOR = 275,
     FUNCTION = 276,
     IF = 277,
     NOT = 278,
     OF = 279,
     PROCEDURE = 280,
     PROGRAM = 281,
     RECORD = 282,
     THEN = 283,
     TO = 284,
     VAR = 285,
     WHILE = 286,
     READ = 287,
     READLN = 288,
     WRITE = 289,
     WRITELN = 290,
     DOT = 291,
     TYPE = 292,
     STD_FUNC = 293,
     ASSIGN = 294,
     EQUAL = 295,
     PLUS = 296,
     MINUS = 297,
     ADDING_OP = 298,
     MULTI_OP = 299,
     REL_OP = 300,
     COMMA = 301,
     COLON = 302,
     SEMICOLON = 303,
     RANGE = 304,
     LPAREN = 305,
     RPAREN = 306,
     LBRACKET = 307,
     RBRACKET = 308
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 43 "NEW_PASCC.y"

    class TokenInfo* token_info;
    class ASTNode* ast;


/* Line 387 of yacc.c  */
#line 211 "NEW_PASCC.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (ASTNode** rootPtr);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_NEW_PASCC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 239 "NEW_PASCC.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   286

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNRULES -- Number of states.  */
#define YYNSTATES  246

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    14,    17,    23,    25,    29,    30,
      34,    38,    44,    47,    50,    52,    54,    56,    58,    60,
      62,    63,    67,    71,    77,    78,    82,    86,    92,    96,
     102,   104,   106,   108,   115,   121,   122,   128,   132,   138,
     139,   143,   147,   151,   157,   158,   162,   163,   165,   169,
     171,   173,   176,   180,   185,   189,   191,   195,   197,   199,
     201,   203,   205,   207,   209,   211,   213,   215,   217,   219,
     221,   222,   226,   230,   236,   245,   254,   259,   264,   269,
     274,   281,   283,   287,   291,   296,   298,   302,   305,   306,
     308,   309,   314,   316,   318,   322,   326,   331,   336,   337,
     340,   342,   346,   348,   350,   354,   358,   360,   364,   368,
     372,   376,   380,   382,   384,   388,   390,   392,   396,   398,
     401,   404
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    56,    48,    57,    36,    -1,    26,     9,
      50,    58,    51,    -1,    26,     9,    -1,    59,    63,    65,
      72,    81,    -1,     9,    -1,    58,    46,     9,    -1,    -1,
      14,    60,    48,    -1,     9,    40,    61,    -1,    60,    48,
       9,    40,    61,    -1,    41,    62,    -1,    42,    62,    -1,
      62,    -1,     5,    -1,     6,    -1,     7,    -1,     3,    -1,
       4,    -1,    -1,    37,    64,    47,    -1,     9,    40,    67,
      -1,    64,    48,     9,    40,    67,    -1,    -1,    30,    66,
      48,    -1,    58,    47,    67,    -1,    66,    48,    58,    47,
      67,    -1,    58,    47,     9,    -1,    66,    48,    58,    47,
       9,    -1,     8,    -1,    68,    -1,    69,    -1,    10,    52,
      71,    53,    24,     8,    -1,     9,    40,    27,    70,    19,
      -1,    -1,    70,    58,    47,    67,    48,    -1,     3,    49,
       3,    -1,    71,    46,     3,    49,     3,    -1,    -1,    72,
      73,    48,    -1,    74,    48,    80,    -1,    25,     9,    75,
      -1,    21,     9,    75,    47,     8,    -1,    -1,    50,    76,
      51,    -1,    -1,    77,    -1,    76,    48,    77,    -1,    78,
      -1,    79,    -1,    30,    79,    -1,    58,    47,     8,    -1,
      59,    63,    65,    81,    -1,    11,    82,    19,    -1,    83,
      -1,    82,    48,    83,    -1,    84,    -1,    85,    -1,    86,
      -1,    99,    -1,    81,    -1,    87,    -1,    88,    -1,    89,
      -1,    90,    -1,    91,    -1,    94,    -1,    12,    -1,    15,
      -1,    -1,    96,    39,   102,    -1,     9,    39,   102,    -1,
      22,   102,    28,    83,   100,    -1,    20,     9,    39,   102,
      29,   102,    16,    83,    -1,    20,     9,    39,   102,    17,
     102,    16,    83,    -1,    32,    50,    95,    51,    -1,    33,
      50,    95,    51,    -1,    34,    50,   101,    51,    -1,    35,
      50,   101,    51,    -1,    13,   102,    24,    92,    48,    19,
      -1,    93,    -1,    92,    48,    93,    -1,   102,    47,    83,
      -1,    31,   102,    16,    83,    -1,    96,    -1,    95,    46,
      96,    -1,     9,    97,    -1,    -1,    98,    -1,    -1,    98,
      52,   101,    53,    -1,     9,    -1,    38,    -1,     9,    50,
      51,    -1,    38,    50,    51,    -1,     9,    50,   101,    51,
      -1,    38,    50,   101,    51,    -1,    -1,    18,    83,    -1,
     102,    -1,   101,    46,   102,    -1,   104,    -1,   103,    -1,
     104,    45,   104,    -1,   104,    40,   104,    -1,     7,    -1,
       7,    41,     7,    -1,     7,    41,     5,    -1,   104,    42,
     105,    -1,   104,    41,   105,    -1,   104,    43,   105,    -1,
     105,    -1,   106,    -1,   105,    44,   106,    -1,    61,    -1,
      96,    -1,    50,   102,    51,    -1,    99,    -1,    23,   106,
      -1,    41,   106,    -1,    42,   106,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    81,    81,    89,   106,   118,   126,   132,   140,   141,
     148,   183,   224,   230,   236,   240,   246,   252,   259,   265,
     273,   274,   281,   309,   338,   339,   346,   387,   429,   441,
     454,   461,   465,   473,   481,   526,   530,   539,   546,   555,
     559,   567,   574,   612,   652,   655,   662,   666,   671,   679,
     681,   684,   693,   700,   708,   715,   720,   728,   729,   730,
     731,   732,   733,   734,   735,   736,   737,   738,   740,   746,
     753,   758,   765,   772,   779,   785,   792,   798,   805,   811,
     818,   826,   831,   840,   848,   856,   861,   869,   881,   884,
     889,   892,   904,   910,   916,   922,   928,   934,   941,   942,
     949,   954,   962,   966,   970,   976,   983,   989,   995,  1002,
    1008,  1014,  1020,  1025,  1029,  1036,  1040,  1044,  1050,  1054,
    1060,  1066
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_NUM", "REAL_NUM", "CHAR",
  "BOO_LEAN", "STRING", "BASIC_TYPE", "IDENTIFIER", "ARRAY", "BEGIN_",
  "BREAK", "CASE", "CONST", "CONTINUE", "DO", "DOWNTO", "ELSE", "END",
  "FOR", "FUNCTION", "IF", "NOT", "OF", "PROCEDURE", "PROGRAM", "RECORD",
  "THEN", "TO", "VAR", "WHILE", "READ", "READLN", "WRITE", "WRITELN",
  "DOT", "TYPE", "STD_FUNC", "ASSIGN", "EQUAL", "PLUS", "MINUS",
  "ADDING_OP", "MULTI_OP", "REL_OP", "COMMA", "COLON", "SEMICOLON",
  "RANGE", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "$accept",
  "programstruct", "program_head", "program_body", "identifier_list",
  "const_declarations", "const_declaration", "const_value",
  "unsigned_const", "type_declarations", "type_declaration",
  "var_declarations", "var_declaration", "type", "array_type",
  "record_type", "field_list", "period", "subprogram_declarations",
  "subprogram", "subprogram_head", "formal_parameter", "parameter_list",
  "parameter", "var_parameter", "value_parameter", "subprogram_body",
  "compound_statement", "statement_list", "statement", "empty_statement",
  "assign_statement", "func_assign_statement", "if_statement",
  "for_statement", "read_statement", "write_statement", "switch_statement",
  "switch_case_list", "switch_case_item", "while_statement",
  "variable_list", "variable", "id_varpart", "id_varpart_n",
  "procedure_call", "else_part", "expression_list", "expression",
  "str_expression", "simple_expression", "term", "factor", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    58,    58,    59,    59,
      60,    60,    61,    61,    61,    61,    61,    61,    62,    62,
      63,    63,    64,    64,    65,    65,    66,    66,    66,    66,
      67,    67,    67,    68,    69,    70,    70,    71,    71,    72,
      72,    73,    74,    74,    75,    75,    76,    76,    76,    77,
      77,    78,    79,    80,    81,    82,    82,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      84,    85,    86,    87,    88,    88,    89,    89,    90,    90,
      91,    92,    92,    93,    94,    95,    95,    96,    97,    97,
      98,    98,    99,    99,    99,    99,    99,    99,   100,   100,
     101,   101,   102,   102,   102,   102,   103,   103,   103,   104,
     104,   104,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     2,     5,     1,     3,     0,     3,
       3,     5,     2,     2,     1,     1,     1,     1,     1,     1,
       0,     3,     3,     5,     0,     3,     3,     5,     3,     5,
       1,     1,     1,     6,     5,     0,     5,     3,     5,     0,
       3,     3,     3,     5,     0,     3,     0,     1,     3,     1,
       1,     2,     3,     4,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     3,     5,     8,     8,     4,     4,     4,     4,
       6,     1,     3,     3,     4,     1,     3,     2,     0,     1,
       0,     4,     1,     1,     3,     3,     4,     4,     0,     2,
       1,     3,     1,     1,     3,     3,     1,     3,     3,     3,
       3,     3,     1,     1,     3,     1,     1,     3,     1,     2,
       2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     4,     1,     8,     0,     0,     0,
      20,     6,     0,     0,     0,     2,     0,    24,     0,     3,
       0,     9,     0,     0,     0,    39,     7,    18,    19,    15,
      16,    17,     0,     0,    10,    14,     0,     0,    21,     0,
       0,     0,     0,    12,    13,     0,    30,     0,     0,    22,
      31,    32,     0,     0,    25,    70,     0,     0,     0,     0,
       5,    11,     0,     0,     0,    28,    26,     0,    92,    68,
       0,    69,     0,     0,     0,     0,     0,     0,     0,    93,
      61,     0,    55,    57,    58,    59,    62,    63,    64,    65,
      66,    67,     0,    60,    44,    44,    40,     8,    35,     0,
       0,    23,     0,     0,     0,    87,    89,    17,    88,     0,
       0,     0,     0,   115,   116,   118,     0,   103,   102,   112,
     113,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      70,     0,    46,     0,    42,    20,    41,     0,     0,     0,
       0,    29,    27,    72,    94,     0,   100,     0,     0,   119,
      12,   120,    13,   121,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    70,    88,     0,    85,     0,     0,
       0,    95,     0,    56,    71,     0,     0,     0,    47,    49,
      50,     0,    24,    34,     0,    37,     0,     0,     0,    96,
       0,   108,   107,   117,     0,    81,     0,   105,   110,   109,
     111,   104,   114,     0,    98,    84,     0,    76,    77,    78,
      79,    97,    51,     0,     0,    45,    43,     0,     0,     0,
      33,   101,    91,     0,    70,     0,     0,    70,    73,    86,
      52,    48,    53,     0,    38,    80,    82,    83,     0,     0,
      99,    36,    70,    70,    75,    74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     9,   176,    10,    14,   113,    35,    17,
      23,    25,    41,    49,    50,    51,   137,   100,    42,    58,
      59,   133,   177,   178,   179,   180,   136,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,   194,   195,
      91,   166,   114,   105,   106,   115,   228,   145,   146,   117,
     118,   119,   120
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -126
static const yytype_int16 yypact[] =
{
      38,    64,   128,    86,    87,  -126,    76,   140,   154,   137,
     130,  -126,    20,   135,   132,  -126,   172,   155,   175,  -126,
      13,   177,   158,    36,   140,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,   138,   138,  -126,  -126,   165,    40,  -126,   198,
      54,   160,    57,  -126,  -126,    13,  -126,   169,   159,  -126,
    -126,  -126,   170,    97,   140,   233,   203,   205,   167,   168,
    -126,  -126,   191,   214,    40,   169,  -126,   109,    -9,  -126,
     190,  -126,   210,   190,   190,   171,   173,   174,   176,   179,
    -126,    -4,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,   183,  -126,   180,   180,  -126,    76,  -126,   178,
     -19,  -126,   105,   190,    53,  -126,   181,   184,    88,   197,
     197,   197,   190,  -126,  -126,  -126,   212,  -126,    90,   193,
    -126,   195,   213,   227,   240,   240,   190,   190,   141,  -126,
     233,   190,    12,   204,  -126,   130,  -126,    42,   247,   249,
     230,   169,  -126,  -126,  -126,    21,  -126,   190,    26,  -126,
    -126,  -126,  -126,  -126,   206,   190,   197,   197,   197,   197,
     197,   197,   190,   233,   233,   207,    28,  -126,    34,    35,
      46,  -126,    47,  -126,  -126,   140,   119,   -16,  -126,  -126,
    -126,   248,   155,  -126,   131,  -126,   209,   252,   190,  -126,
     -17,  -126,  -126,  -126,   215,  -126,   222,    78,   193,   193,
     193,    78,  -126,    11,   243,  -126,   240,  -126,  -126,  -126,
    -126,  -126,  -126,   254,    12,  -126,  -126,   259,    40,   269,
    -126,  -126,  -126,   120,   233,   190,   190,   233,  -126,  -126,
    -126,  -126,  -126,   225,  -126,  -126,  -126,  -126,   258,   260,
    -126,  -126,   233,   233,  -126,  -126
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -126,  -126,  -126,  -126,    -1,   182,  -126,     2,   -23,   142,
    -126,    93,  -126,   -50,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,   185,  -126,    67,  -126,   103,  -126,   -41,  -126,  -125,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,    59,
    -126,   161,   -55,  -126,  -126,   -53,  -126,  -102,   -66,  -126,
     -44,    -5,   -98
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -91
static const yytype_int16 yytable[] =
{
      92,    60,    93,    66,   116,   173,    12,   122,   123,    43,
      44,   149,   151,   153,   101,   129,    27,    28,    29,    30,
      31,    11,    34,    40,   169,   170,   172,   139,   225,   188,
     103,   191,   214,   192,   140,   215,   222,   143,   204,   205,
     226,   104,   175,   -90,   130,   190,   154,    61,    46,    47,
      48,    11,   142,    67,    32,    33,    27,    28,    29,    30,
     107,   183,   108,   202,     1,   174,    18,   188,    55,   167,
     167,    19,   189,     4,   206,    92,   109,    93,    56,   207,
     206,   188,    57,    38,    39,   208,   209,   150,   152,   196,
       8,    79,   188,   188,   110,   111,   203,   210,   211,   237,
      18,    53,   240,   112,   144,    46,    65,    48,    92,    92,
      93,    93,   197,    46,   141,    48,   201,   244,   245,   157,
     158,   159,   221,    27,    28,    29,    30,   107,     5,   108,
     156,   157,   158,   159,     6,   160,   184,     7,   104,   235,
     -90,    27,    28,   109,    27,    28,    29,    30,   107,    11,
     108,   229,   198,   199,   200,    18,   102,   196,    79,   238,
     239,   110,   111,    13,   109,    18,   213,    16,   233,    92,
     112,    93,    92,    15,    93,    20,   232,    18,   218,    79,
      21,    22,   110,   111,    26,    24,    36,    92,    92,    93,
      93,   112,   171,    27,    28,    29,    30,   107,    37,   108,
      27,    28,    29,    30,    31,    45,   108,    52,    54,    62,
      64,    63,    94,   109,    95,    96,    97,    99,    98,   121,
     109,   124,   131,   125,   126,   148,   127,   138,    79,   128,
     132,   110,   111,   147,   162,    79,   155,   161,   110,   111,
     112,   163,    68,   164,    55,    69,    70,   112,    71,   165,
     185,   181,   186,    72,   187,    73,   216,   193,   219,   -90,
     220,   227,   230,   223,    74,    75,    76,    77,    78,   224,
      55,    79,   234,   241,   242,   217,   243,   182,   212,   135,
     134,   231,   236,     0,     0,     0,   168
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-126)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      55,    42,    55,    53,    70,   130,     7,    73,    74,    32,
      33,   109,   110,   111,    64,    19,     3,     4,     5,     6,
       7,     9,    20,    24,   126,   127,   128,    46,    17,    46,
      39,     5,    48,     7,    53,    51,    53,   103,   163,   164,
      29,    50,    30,    52,    48,   147,   112,    45,     8,     9,
      10,     9,   102,    54,    41,    42,     3,     4,     5,     6,
       7,    19,     9,   161,    26,   131,    46,    46,    11,   124,
     125,    51,    51,     9,    46,   130,    23,   130,    21,    51,
      46,    46,    25,    47,    48,    51,    51,   110,   111,   155,
      14,    38,    46,    46,    41,    42,   162,    51,    51,   224,
      46,    47,   227,    50,    51,     8,     9,    10,   163,   164,
     163,   164,   156,     8,     9,    10,   160,   242,   243,    41,
      42,    43,   188,     3,     4,     5,     6,     7,     0,     9,
      40,    41,    42,    43,    48,    45,   137,    50,    50,    19,
      52,     3,     4,    23,     3,     4,     5,     6,     7,     9,
       9,   206,   157,   158,   159,    46,    47,   223,    38,   225,
     226,    41,    42,     9,    23,    46,    47,    37,   218,   224,
      50,   224,   227,    36,   227,    40,   217,    46,    47,    38,
      48,     9,    41,    42,     9,    30,     9,   242,   243,   242,
     243,    50,    51,     3,     4,     5,     6,     7,    40,     9,
       3,     4,     5,     6,     7,    40,     9,     9,    48,    40,
      40,    52,     9,    23,     9,    48,    48,     3,    27,     9,
      23,    50,    39,    50,    50,    41,    50,    49,    38,    50,
      50,    41,    42,    52,    39,    38,    24,    44,    41,    42,
      50,    28,     9,    16,    11,    12,    13,    50,    15,     9,
       3,    47,     3,    20,    24,    22,     8,    51,    49,    52,
       8,    18,     8,    48,    31,    32,    33,    34,    35,    47,
      11,    38,     3,    48,    16,   182,    16,   135,   175,    97,
      95,   214,   223,    -1,    -1,    -1,   125
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,    55,    56,     9,     0,    48,    50,    14,    57,
      59,     9,    58,     9,    60,    36,    37,    63,    46,    51,
      40,    48,     9,    64,    30,    65,     9,     3,     4,     5,
       6,     7,    41,    42,    61,    62,     9,    40,    47,    48,
      58,    66,    72,    62,    62,    40,     8,     9,    10,    67,
      68,    69,     9,    47,    48,    11,    21,    25,    73,    74,
      81,    61,    40,    52,    40,     9,    67,    58,     9,    12,
      13,    15,    20,    22,    31,    32,    33,    34,    35,    38,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    94,    96,    99,     9,     9,    48,    48,    27,     3,
      71,    67,    47,    39,    50,    97,    98,     7,     9,    23,
      41,    42,    50,    61,    96,    99,   102,   103,   104,   105,
     106,     9,   102,   102,    50,    50,    50,    50,    50,    19,
      48,    39,    50,    75,    75,    59,    80,    70,    49,    46,
      53,     9,    67,   102,    51,   101,   102,    52,    41,   106,
      62,   106,    62,   106,   102,    24,    40,    41,    42,    43,
      45,    44,    39,    28,    16,     9,    95,    96,    95,   101,
     101,    51,   101,    83,   102,    30,    58,    76,    77,    78,
      79,    47,    63,    19,    58,     3,     3,    24,    46,    51,
     101,     5,     7,    51,    92,    93,   102,   104,   105,   105,
     105,   104,   106,   102,    83,    83,    46,    51,    51,    51,
      51,    51,    79,    47,    48,    51,     8,    65,    47,    49,
       8,   102,    53,    48,    47,    17,    29,    18,   100,    96,
       8,    77,    81,    67,     3,    19,    93,    83,   102,   102,
      83,    48,    16,    16,    83,    83
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      yyerror (rootPtr, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, rootPtr); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, ASTNode** rootPtr)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, rootPtr)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    ASTNode** rootPtr;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (rootPtr);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, ASTNode** rootPtr)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, rootPtr)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    ASTNode** rootPtr;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, rootPtr);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, ASTNode** rootPtr)
#else
static void
yy_reduce_print (yyvsp, yyrule, rootPtr)
    YYSTYPE *yyvsp;
    int yyrule;
    ASTNode** rootPtr;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , rootPtr);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, rootPtr); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, ASTNode** rootPtr)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, rootPtr)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    ASTNode** rootPtr;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (rootPtr);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (ASTNode** rootPtr)
#else
int
yyparse (rootPtr)
    ASTNode** rootPtr;
#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

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
/* Line 1792 of yacc.c  */
#line 82 "NEW_PASCC.y"
    {   
                  cout << "Program" << endl;
                  *rootPtr = new ProgramNode((yyvsp[(1) - (4)].ast), (yyvsp[(3) - (4)].ast));
                  // printNodeType(*rootPtr, 0);
                  safeDelete((yyvsp[(2) - (4)].token_info), (yyvsp[(4) - (4)].token_info));
                }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 90 "NEW_PASCC.y"
    {
                  cout << "Program Head with parameters: " << GET_STR_VAL((yyvsp[(2) - (5)].token_info)) << endl;
                  (yyval.ast) = new ProgramHeadNode(GET_STR_VAL((yyvsp[(2) - (5)].token_info)), (yyvsp[(4) - (5)].ast));
                  
                  ProcSymbol* programSymbol = new ProcSymbol(GET_STR_VAL((yyvsp[(2) - (5)].token_info)), (yyval.ast));
                  vector<string> idList = dynamic_cast<IdentifierListNode*>((yyvsp[(4) - (5)].ast))->identifier_list;
                  for (const auto& s : idList) {
                    SymbolType* idType = new SymbolType(NULL_TYPE);
                    VarSymbol* id = new VarSymbol(s, idType);
                    programSymbol->addParameter(id);
                  }
                  globalSymbolTable->addSymbol(programSymbol);
                  currentSymbolTable = globalSymbolTable->getChildTable(GET_STR_VAL((yyvsp[(2) - (5)].token_info)));
                  
                  safeDelete((yyvsp[(1) - (5)].token_info), (yyvsp[(2) - (5)].token_info), (yyvsp[(3) - (5)].token_info), (yyvsp[(5) - (5)].token_info));
                }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 107 "NEW_PASCC.y"
    {
                  cout << "Program Head: " << GET_STR_VAL((yyvsp[(2) - (2)].token_info)) << endl;
                  (yyval.ast) = new ProgramHeadNode(GET_STR_VAL((yyvsp[(2) - (2)].token_info)), nullptr);
                  
                  Symbol* programSymbol = new ProcSymbol(GET_STR_VAL((yyvsp[(2) - (2)].token_info)), (yyval.ast));
                  globalSymbolTable->addSymbol(programSymbol);
                  currentSymbolTable = globalSymbolTable->getChildTable(GET_STR_VAL((yyvsp[(2) - (2)].token_info)));

                  safeDelete((yyvsp[(1) - (2)].token_info), (yyvsp[(2) - (2)].token_info));
                }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 119 "NEW_PASCC.y"
    {
                  cout << "Program Body" << endl;
                  (yyval.ast) = new ProgramBodyNode((yyvsp[(1) - (5)].ast), (yyvsp[(2) - (5)].ast), (yyvsp[(3) - (5)].ast), (yyvsp[(4) - (5)].ast), (yyvsp[(5) - (5)].ast));

                  currentSymbolTable = currentSymbolTable->getParent();
                }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 127 "NEW_PASCC.y"
    {
                  cout << "Identifier: " << GET_STR_VAL((yyvsp[(1) - (1)].token_info)) << endl;
                  (yyval.ast) = new IdentifierListNode(vector<string>{GET_STR_VAL((yyvsp[(1) - (1)].token_info))});
                  safeDelete((yyvsp[(1) - (1)].token_info));
                }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 133 "NEW_PASCC.y"
    {
                  cout << "Adding Identifier: " << GET_STR_VAL((yyvsp[(3) - (3)].token_info)) << endl;
                  dynamic_cast<IdentifierListNode*>((yyvsp[(1) - (3)].ast))->identifier_list.push_back(GET_STR_VAL((yyvsp[(3) - (3)].token_info)));
                  (yyval.ast) = (yyvsp[(1) - (3)].ast);
                  safeDelete((yyvsp[(2) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 140 "NEW_PASCC.y"
    { (yyval.ast) = nullptr; }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 142 "NEW_PASCC.y"
    {
                      cout << "Const Declarations" << endl;
                      (yyval.ast) = (yyvsp[(2) - (3)].ast);
                      safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                    }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 149 "NEW_PASCC.y"
    {
                      if (currentSymbolTable->lookupEntry(GET_STR_VAL((yyvsp[(1) - (3)].token_info)))) {
                          std::cerr <<"LINE["<< (yyvsp[(1) - (3)].token_info)->line_no << "]ERROR"<<": The constant declaration is duplicated. '" << GET_STR_VAL((yyvsp[(1) - (3)].token_info)) << "'\n";                      
                      }
                      else{
                        cout << "Const Declaration: " << GET_STR_VAL((yyvsp[(1) - (3)].token_info)) << endl;
                        ASTNode* const_declaration_node = new ConstDeclarationNode(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), (yyvsp[(3) - (3)].ast));
                        (yyval.ast) = new ConstDeclarationListNode(vector<ASTNode*>{const_declaration_node});
                        
                        StdTypeNode* std_node = dynamic_cast<StdTypeNode*>((yyvsp[(3) - (3)].ast));
                        BasicType bt = std_node->getBasicType();
                        switch (bt) {
                            case INTEGER:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), INTEGER, std_node->getValue<int>()));
                                break;
                            case REAL:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), REAL, std_node->getValue<float>()));
                                break;
                            case CHAR_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), CHAR_, std_node->getValue<char>()));
                                break;
                            case BOOLEAN_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), BOOLEAN_, std_node->getValue<bool>()));
                                break;
                            case STRING_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), STRING_, std_node->getValue<string>()));
                                break;
                            default:
                                throw invalid_argument("Invalid type for getVal");
                        }

                        safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(2) - (3)].token_info));
                      }
                    }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 184 "NEW_PASCC.y"
    {
                      if (currentSymbolTable->lookupEntry(GET_STR_VAL((yyvsp[(3) - (5)].token_info)))) {
                          std::cerr <<"LINE["<< (yyvsp[(3) - (5)].token_info)->line_no << "]ERROR" << ": The constant declaration is duplicated. '" << GET_STR_VAL((yyvsp[(3) - (5)].token_info)) << "'\n";
                      }
                      else{
                        cout << "Adding Const Declaration: " << GET_STR_VAL((yyvsp[(3) - (5)].token_info)) << endl;
                        ASTNode* const_declaration_node = new ConstDeclarationNode(GET_STR_VAL((yyvsp[(3) - (5)].token_info)), (yyvsp[(5) - (5)].ast));
                        dynamic_cast<ConstDeclarationListNode*>((yyvsp[(1) - (5)].ast))->const_list.push_back(const_declaration_node);
                        (yyval.ast) = (yyvsp[(1) - (5)].ast);
                        
                        StdTypeNode* std_node = dynamic_cast<StdTypeNode*>((yyvsp[(5) - (5)].ast));
                        cout<<"get_type"<<endl;
                        BasicType bt = std_node->getBasicType();
                        cout<<"after_get_type"<<endl;
                        switch (bt) {
                            case INTEGER:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL((yyvsp[(3) - (5)].token_info)), INTEGER, std_node->getValue<int>()));
                                break;
                            case REAL:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL((yyvsp[(3) - (5)].token_info)), REAL, std_node->getValue<float>()));
                                break;
                            case CHAR_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL((yyvsp[(3) - (5)].token_info)), CHAR_, std_node->getValue<char>()));
                                break;
                            case BOOLEAN_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL((yyvsp[(3) - (5)].token_info)), BOOLEAN_, std_node->getValue<bool>()));
                                break;
                            case STRING_:
                                currentSymbolTable->addSymbol(new ConstSymbol(GET_STR_VAL((yyvsp[(3) - (5)].token_info)), STRING_, std_node->getValue<string>()));
                                break;
                            default:
                                throw invalid_argument("Invalid type for getVal");
                        }
                        
                        cout<<"1"<<endl;

                        safeDelete((yyvsp[(2) - (5)].token_info), (yyvsp[(3) - (5)].token_info), (yyvsp[(4) - (5)].token_info));
                      }
                    }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 225 "NEW_PASCC.y"
    {
              cout << "Signed Constant" << endl;
              (yyval.ast) = new UnaryOpNode(GET_STR_VAL((yyvsp[(1) - (2)].token_info)), (yyvsp[(2) - (2)].ast));
              safeDelete((yyvsp[(1) - (2)].token_info));
            }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 231 "NEW_PASCC.y"
    {
              cout << "Signed Constant" << endl;
              (yyval.ast) = new UnaryOpNode(GET_STR_VAL((yyvsp[(1) - (2)].token_info)), (yyvsp[(2) - (2)].ast));
              safeDelete((yyvsp[(1) - (2)].token_info));
            }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 237 "NEW_PASCC.y"
    { 
              cout<<"Unsigned Constant" << endl;
              (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 241 "NEW_PASCC.y"
    {
              cout << "Char Constant: " << GET_CHAR_VAL((yyvsp[(1) - (1)].token_info)) << endl;
              (yyval.ast) = new StdTypeNode(CHAR_, GET_CHAR_VAL((yyvsp[(1) - (1)].token_info)));
              safeDelete((yyvsp[(1) - (1)].token_info));
            }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 247 "NEW_PASCC.y"
    {
              cout << "Boolean Constant: " << GET_BOOL_VAL((yyvsp[(1) - (1)].token_info)) << endl;
              (yyval.ast) = new StdTypeNode(BOOLEAN_, GET_BOOL_VAL((yyvsp[(1) - (1)].token_info)));
              safeDelete((yyvsp[(1) - (1)].token_info));
            }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 253 "NEW_PASCC.y"
    {
              cout << "String Constant: " << GET_STR_VAL((yyvsp[(1) - (1)].token_info)) << endl;
              (yyval.ast) = new StdTypeNode(STRING_, GET_STR_VAL((yyvsp[(1) - (1)].token_info)));
              safeDelete((yyvsp[(1) - (1)].token_info));
            }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 260 "NEW_PASCC.y"
    {
                  cout << "Unsigned Integer: " << GET_INT_VAL((yyvsp[(1) - (1)].token_info)) << endl;
                  (yyval.ast) = new StdTypeNode(INTEGER, GET_INT_VAL((yyvsp[(1) - (1)].token_info)));
                  safeDelete((yyvsp[(1) - (1)].token_info));
                }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 266 "NEW_PASCC.y"
    {
                  cout << "Unsigned Real: " << GET_REAL_VAL((yyvsp[(1) - (1)].token_info)) << endl;
                  (yyval.ast) = new StdTypeNode(REAL, GET_REAL_VAL((yyvsp[(1) - (1)].token_info)));
                  safeDelete((yyvsp[(1) - (1)].token_info));
                }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 273 "NEW_PASCC.y"
    { (yyval.ast) = nullptr; }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 275 "NEW_PASCC.y"
    {
                    cout << "Type Declarations" << endl;
                    safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                    (yyval.ast) = (yyvsp[(2) - (3)].ast);
                  }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 282 "NEW_PASCC.y"
    {
                    cout << "Type Declaration: " << GET_STR_VAL((yyvsp[(1) - (3)].token_info)) << endl;
                    ASTNode* type_dec_list_node = new TypeDeclarationListNode(vector<ASTNode*>{new TypeDeclarationNode(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), (yyvsp[(3) - (3)].ast))});
                    (yyval.ast) = type_dec_list_node;

                    if (((yyvsp[(3) - (3)].ast))->node_type == NODE_BASIC_TYPE) {
                      SymbolType* type = new SymbolType(dynamic_cast<BasicTypeNode*>((yyvsp[(3) - (3)].ast))->type);
                      VarSymbol* var = new VarSymbol(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), type);
                      currentSymbolTable->addSymbol(var);
                    } else if (((yyvsp[(3) - (3)].ast))->node_type == NODE_ARRAY_TYPE) {
                      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>((yyvsp[(3) - (3)].ast));
                      SymbolType* elementType = new SymbolType(arrTypeNode->type);
                      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
                      ArrayType* arrType = new ArrayType(elementType);
                      for (const auto& it : pariodList) {
                        PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
                        arrType->addDimension(pariod->start, pariod->end);
                      }
                      SymbolType* type = new SymbolType(arrType);
                      VarSymbol* var = new VarSymbol(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), type);
                      currentSymbolTable->addSymbol(var);
                    } else if (((yyvsp[(3) - (3)].ast))->node_type == NODE_RECORD_TYPE) {

                    }

                    safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(2) - (3)].token_info));
                  }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 310 "NEW_PASCC.y"
    {
                    cout << "Adding Type Declaration: " << GET_STR_VAL((yyvsp[(3) - (5)].token_info)) << endl;
                    dynamic_cast<TypeDeclarationListNode*>((yyvsp[(1) - (5)].ast))->type_decl_list.push_back(new TypeDeclarationNode(GET_STR_VAL((yyvsp[(3) - (5)].token_info)), (yyvsp[(5) - (5)].ast)));
                    (yyval.ast) = (yyvsp[(1) - (5)].ast);

                    if (((yyvsp[(5) - (5)].ast))->node_type == NODE_BASIC_TYPE) {
                      SymbolType* type = new SymbolType(dynamic_cast<BasicTypeNode*>((yyvsp[(5) - (5)].ast))->type);
                      VarSymbol* var = new VarSymbol(GET_STR_VAL((yyvsp[(3) - (5)].token_info)), type);
                      currentSymbolTable->addSymbol(var);
                    } else if (((yyvsp[(5) - (5)].ast))->node_type == NODE_ARRAY_TYPE) {
                      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>((yyvsp[(5) - (5)].ast));
                      SymbolType* elementType = new SymbolType(arrTypeNode->type);
                      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
                      ArrayType* arrType = new ArrayType(elementType);
                      for (const auto& it : pariodList) {
                        PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
                        arrType->addDimension(pariod->start, pariod->end);
                      }
                      SymbolType* type = new SymbolType(arrType);
                      VarSymbol* var = new VarSymbol(GET_STR_VAL((yyvsp[(3) - (5)].token_info)), type);
                      currentSymbolTable->addSymbol(var);
                    } else if (((yyvsp[(5) - (5)].ast))->node_type == NODE_RECORD_TYPE) {

                    }

                    safeDelete((yyvsp[(2) - (5)].token_info), (yyvsp[(3) - (5)].token_info), (yyvsp[(4) - (5)].token_info));
                  }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 338 "NEW_PASCC.y"
    { (yyval.ast) = nullptr; }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 340 "NEW_PASCC.y"
    {
                      cout << "Var Declarations" << endl;
                      (yyval.ast) = (yyvsp[(2) - (3)].ast);
                      safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                    }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 347 "NEW_PASCC.y"
    {
                  cout << "Var Declaration" << endl;
                  ASTNode* var_declaration_node = new VarDeclarationNode((yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
                  (yyval.ast) = new VarDeclarationListNode(vector<ASTNode*>{var_declaration_node});

                  vector<string> idList = dynamic_cast<IdentifierListNode*>((yyvsp[(1) - (3)].ast))->identifier_list;
                  for (auto s : idList) {
                    if (currentSymbolTable->lookupEntry(s)){
                        std::cerr << "LINE[" << (yyvsp[(2) - (3)].token_info)->line_no << "]ERROR" << ": Duplicate vaiable declaration'" << s << "'\n";
                        continue;
                    }
                    if (((yyvsp[(3) - (3)].ast))->node_type == NODE_BASIC_TYPE) {
                      SymbolType* type = new SymbolType(dynamic_cast<BasicTypeNode*>((yyvsp[(3) - (3)].ast))->type);
                      VarSymbol* var = new VarSymbol(s, type);
                      currentSymbolTable->addSymbol(var);
                    } else if (((yyvsp[(3) - (3)].ast))->node_type == NODE_ARRAY_TYPE) {
                      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>((yyvsp[(3) - (3)].ast));
                      SymbolType* elementType = new SymbolType(arrTypeNode->type);
                      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
                      ArrayType* arrType = new ArrayType(elementType);
                      for (const auto& it : pariodList) {
                        PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
                        if(pariod->start > pariod->end){
                            std::cerr << "LINE[" << (yyvsp[(2) - (3)].token_info)->line_no << "]ERROR" << ": Invalid Array Index'" << s << "'\n";
                            int swap_i = pariod->start;
                            pariod->start = pariod->end;
                            pariod->end = swap_i;
                        }
                        arrType->addDimension(pariod->start, pariod->end);
                      }
                      SymbolType* type = new SymbolType(arrType);
                      VarSymbol* var = new VarSymbol(s, type);
                      currentSymbolTable->addSymbol(var);
                    } else if (((yyvsp[(3) - (3)].ast))->node_type == NODE_RECORD_TYPE) {

                    }
                  }

                  safeDelete((yyvsp[(2) - (3)].token_info));
                }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 388 "NEW_PASCC.y"
    {
                  cout << "Adding Var Declaration" << endl;
                  ASTNode* var_declaration_node = new VarDeclarationNode((yyvsp[(3) - (5)].ast), (yyvsp[(5) - (5)].ast));
                  dynamic_cast<VarDeclarationListNode*>((yyvsp[(1) - (5)].ast))->var_list.push_back(var_declaration_node);
                  (yyval.ast) = (yyvsp[(1) - (5)].ast);

                  vector<string> idList = dynamic_cast<IdentifierListNode*>((yyvsp[(3) - (5)].ast))->identifier_list;
                  for (auto s : idList) {
                    if (currentSymbolTable->lookupEntry(s)){
                        std::cerr << "LINE[" << (yyvsp[(4) - (5)].token_info)->line_no << "]ERROR" << ": Duplicate vaiable declaration '" << s << "'\n";
                        continue;
                    }
                    if (((yyvsp[(5) - (5)].ast))->node_type == NODE_BASIC_TYPE) {
                      SymbolType* type = new SymbolType(dynamic_cast<BasicTypeNode*>((yyvsp[(5) - (5)].ast))->type);
                      VarSymbol* var = new VarSymbol(s, type);
                      currentSymbolTable->addSymbol(var);
                    } else if (((yyvsp[(5) - (5)].ast))->node_type == NODE_ARRAY_TYPE) {
                      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>((yyvsp[(5) - (5)].ast));
                      SymbolType* elementType = new SymbolType(arrTypeNode->type);
                      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
                      ArrayType* arrType = new ArrayType(elementType);
                      for (const auto& it : pariodList) {
                        PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
                        if(pariod->start > pariod->end){
                            std::cerr << "LINE[" << (yyvsp[(4) - (5)].token_info)->line_no << "]ERROR" << ": Invalid Array Index '" << s << "'\n";
                            int swap_i = pariod->start;
                            pariod->start = pariod->end;
                            pariod->end = swap_i;
                        }
                        arrType->addDimension(pariod->start, pariod->end);
                      }
                      SymbolType* type = new SymbolType(arrType);
                      VarSymbol* var = new VarSymbol(s, type);
                      currentSymbolTable->addSymbol(var);
                    } else if (((yyvsp[(5) - (5)].ast))->node_type == NODE_RECORD_TYPE) {
                      // record 我想想 有点难搞
                    }
                  }

                  safeDelete((yyvsp[(2) - (5)].token_info), (yyvsp[(4) - (5)].token_info));
                }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 430 "NEW_PASCC.y"
    {
                  // cout << "Var Declaration with type identifier: " << GET_STR_VAL($3) << endl;
                  std::cerr << "LINE[" << (yyvsp[(3) - (3)].token_info)->line_no << "]ERROR" << ": The declared type does not exist '" << GET_STR_VAL((yyvsp[(3) - (3)].token_info)) << "'\n";
                  ASTNode* var_declaration_node = new VarDeclarationNode((yyvsp[(1) - (3)].ast), GET_STR_VAL((yyvsp[(3) - (3)].token_info)));
                  (yyval.ast) = new VarDeclarationListNode(vector<ASTNode*>{var_declaration_node});

                  // 好像 没有定义自定义类型的符号啊
                  // 先不理会

                  safeDelete((yyvsp[(2) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 442 "NEW_PASCC.y"
    {
                  // cout << "Adding Var Declaration with type identifier: " << GET_STR_VAL($5) << endl;
                  std::cerr << "LINE[" << (yyvsp[(5) - (5)].token_info)->line_no << "]ERROR" << ": The declared type does not exist '" << GET_STR_VAL((yyvsp[(5) - (5)].token_info)) << "'\n";
                  ASTNode* var_declaration_node = new VarDeclarationNode((yyvsp[(3) - (5)].ast), GET_STR_VAL((yyvsp[(5) - (5)].token_info)));
                  dynamic_cast<VarDeclarationListNode*>((yyvsp[(1) - (5)].ast))->var_list.push_back(var_declaration_node);
                  (yyval.ast) = (yyvsp[(1) - (5)].ast);

                  // 自定义类型 扩展再做

                  safeDelete((yyvsp[(2) - (5)].token_info), (yyvsp[(4) - (5)].token_info), (yyvsp[(5) - (5)].token_info));
                }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 455 "NEW_PASCC.y"
    {
      cout << "Basic Type: " << GET_STR_VAL((yyvsp[(1) - (1)].token_info)) << endl;
      (yyval.ast) = new BasicTypeNode(GET_STR_VAL((yyvsp[(1) - (1)].token_info)));
      // cout<<dynamic_cast<BasicTypeNode*>($$)->type<<endl;
      safeDelete((yyvsp[(1) - (1)].token_info));
    }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 462 "NEW_PASCC.y"
    {
      (yyval.ast) = (yyvsp[(1) - (1)].ast);
    }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 466 "NEW_PASCC.y"
    {
      (yyval.ast) = (yyvsp[(1) - (1)].ast);
      // record 是否应该新开符号表 感觉可开可不开啊
      // 感觉不开有道理一点 符号表应该对应作用域 record 内并非新作用域
      // 但这样 插入需要进行存在检查 需要修改一下 错误检测内容
    }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 474 "NEW_PASCC.y"
    {
                cout << "Array Type with base type: " << GET_TYPE((yyvsp[(6) - (6)].token_info)) << endl;
                (yyval.ast) = new ArrayTypeNode((yyvsp[(3) - (6)].ast), GET_STR_VAL((yyvsp[(6) - (6)].token_info)));
                safeDelete((yyvsp[(1) - (6)].token_info), (yyvsp[(2) - (6)].token_info), (yyvsp[(4) - (6)].token_info), (yyvsp[(5) - (6)].token_info), (yyvsp[(6) - (6)].token_info));
              }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 482 "NEW_PASCC.y"
    {
                cout << "Record Type" << endl;
                (yyval.ast) = new RecordTypeNode((yyvsp[(4) - (5)].ast));

                RecordType* recType = new RecordType(GET_STR_VAL((yyvsp[(1) - (5)].token_info)));
                vector<ASTNode*> fieldList = dynamic_cast<FieldListNode*>((yyvsp[(4) - (5)].ast))->field_list;
                for (const auto& it : fieldList) {
                  FieldNode* field = dynamic_cast<FieldNode*>(it);
                  vector<string> idList = dynamic_cast<IdentifierListNode*>(field->id_list)->identifier_list;
                  auto nodeType = field->node_type;
                  ASTNode* type = field->type;
                  for (const auto& id : idList) {
                    SymbolType* symbolType;
                    if (nodeType == NODE_BASIC_TYPE) {
                      symbolType = new SymbolType(dynamic_cast<BasicTypeNode*>(type)->type);
                    } else if (nodeType == NODE_ARRAY_TYPE) {
                      ArrayTypeNode* arrTypeNode = dynamic_cast<ArrayTypeNode*>(type);
                      SymbolType* elementType = new SymbolType(arrTypeNode->type);
                      vector<ASTNode*> pariodList = dynamic_cast<PeriodListNode*>(arrTypeNode->period_list)->period_list;
                      ArrayType* arrType = new ArrayType(elementType);
                      for (const auto& it : pariodList) {
                        PeriodNode* pariod = dynamic_cast<PeriodNode*>(it);
                        if(pariod->start > pariod->end){
                            std::cerr << "LINE[" << (yyvsp[(1) - (5)].token_info)->line_no << "]ERROR" << ": Invalid Array Index '" << GET_STR_VAL((yyvsp[(1) - (5)].token_info)) << "'\n";
                            int swap_i = pariod->start;
                            pariod->start = pariod->end;
                            pariod->end = swap_i;
                        }
                        arrType->addDimension(pariod->start, pariod->end);
                      }
                      symbolType = new SymbolType(arrType);
                    } else if (nodeType == NODE_RECORD_TYPE) {

                    }
                    recType->addField(id, symbolType);
                  }
                }
                SymbolType* symbolType = new SymbolType(recType);
                currentSymbolTable->addSymbol(new VarSymbol(GET_STR_VAL((yyvsp[(1) - (5)].token_info)), symbolType));

                safeDelete((yyvsp[(1) - (5)].token_info), (yyvsp[(2) - (5)].token_info), (yyvsp[(3) - (5)].token_info), (yyvsp[(5) - (5)].token_info));
              }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 526 "NEW_PASCC.y"
    {
                cout << "Empty Field List" << endl;
                (yyval.ast) = new FieldListNode(vector<ASTNode*>{});
              }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 531 "NEW_PASCC.y"
    {   
                cout << "Adding Field" << endl;
                ASTNode* field_node = new FieldNode((yyvsp[(2) - (5)].ast), (yyvsp[(4) - (5)].ast));
                dynamic_cast<FieldListNode*>((yyvsp[(1) - (5)].ast))->field_list.push_back(field_node);
                (yyval.ast) = (yyvsp[(1) - (5)].ast);
                safeDelete((yyvsp[(3) - (5)].token_info), (yyvsp[(5) - (5)].token_info));
              }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 540 "NEW_PASCC.y"
    {
          cout << "Period: " << GET_INT_VAL((yyvsp[(1) - (3)].token_info)) << ".." << GET_INT_VAL((yyvsp[(3) - (3)].token_info)) << endl;
          ASTNode* period_node = new PeriodNode(GET_INT_VAL((yyvsp[(1) - (3)].token_info)), GET_INT_VAL((yyvsp[(3) - (3)].token_info)));
          (yyval.ast) = new PeriodListNode(vector<ASTNode*>{period_node});
          safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(2) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
        }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 547 "NEW_PASCC.y"
    {
          cout << "Adding Period: " << GET_INT_VAL((yyvsp[(3) - (5)].token_info)) << ".." << GET_INT_VAL((yyvsp[(5) - (5)].token_info)) << endl;
          ASTNode* period_node = new PeriodNode(GET_INT_VAL((yyvsp[(3) - (5)].token_info)), GET_INT_VAL((yyvsp[(5) - (5)].token_info)));
          dynamic_cast<PeriodListNode*>((yyvsp[(1) - (5)].ast))->period_list.push_back(period_node);
          (yyval.ast) = (yyvsp[(1) - (5)].ast);
          safeDelete((yyvsp[(2) - (5)].token_info), (yyvsp[(3) - (5)].token_info), (yyvsp[(4) - (5)].token_info), (yyvsp[(5) - (5)].token_info));
        }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 555 "NEW_PASCC.y"
    {
                            cout << "Empty Subprogram Declarations" << endl;
                            (yyval.ast) = new SubprogramDeclarationsNode(vector<ASTNode*>{});
                          }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 560 "NEW_PASCC.y"
    {
                          cout << "Adding Subprogram" << endl;
                          dynamic_cast<SubprogramDeclarationsNode*>((yyvsp[(1) - (3)].ast))->subprogram_list.push_back((yyvsp[(2) - (3)].ast));
                          (yyval.ast) = (yyvsp[(1) - (3)].ast);
                          safeDelete((yyvsp[(3) - (3)].token_info));
                        }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 568 "NEW_PASCC.y"
    {
              cout << "Subprogram" << endl;
              (yyval.ast) = new SubprogramNode((yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
              safeDelete((yyvsp[(2) - (3)].token_info));
            }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 575 "NEW_PASCC.y"
    {
                    if (currentSymbolTable->lookupEntry(GET_STR_VAL((yyvsp[(2) - (3)].token_info)))) {
                          std::cerr << "LINE[" << (yyvsp[(2) - (3)].token_info)->line_no << "]ERROR: Duplicate procedure definition '" << GET_STR_VAL((yyvsp[(2) - (3)].token_info)) << "'\n";
                          exit(EXIT_FAILURE);
                    }
                    else{
                      cout << "Procedure: " << GET_STR_VAL((yyvsp[(2) - (3)].token_info)) << endl;
                      (yyval.ast) = new SubprogramHeadNode(GET_STR_VAL((yyvsp[(2) - (3)].token_info)), (yyvsp[(3) - (3)].ast), false, "");

                      ProcSymbol* proc = new ProcSymbol(GET_STR_VAL((yyvsp[(2) - (3)].token_info)), (yyval.ast));
                      currentSymbolTable->addSymbol(proc);
                      currentSymbolTable = currentSymbolTable->getChildTable(GET_STR_VAL((yyvsp[(2) - (3)].token_info)));
                      if ((yyvsp[(3) - (3)].ast)) {
                        vector<string> allParamNames;
                        vector<ASTNode*> param_list = dynamic_cast<ParameterListNode*>((yyvsp[(3) - (3)].ast))->param_list;
                        for (const auto& it : param_list) {
                          ParameterNode* param = dynamic_cast<ParameterNode*>(it);
                          vector<string> idList = dynamic_cast<IdentifierListNode*>(param->id_list)->identifier_list;
                          BasicType type = param->type;
                          for (const auto& id : idList) {
                            if (currentSymbolTable->lookupCurrent(id)) {
                            std::cerr << "LINE[" << (yyvsp[(1) - (3)].token_info)->line_no << "]ERROR: Duplicate procedure parameter '" << id << "'\n";  
                            continue;
                            }
                            allParamNames.push_back(id);
                            SymbolType* varType = new SymbolType(type);
                            VarSymbol* var = new VarSymbol(id, varType);
                            var->setPointer(static_cast<ParameterNode*>(it)->is_pointer);
                            currentSymbolTable->addSymbol(var);
                            proc->addParameter(var);
                          }
                        }
                      }
                    }

                      safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(2) - (3)].token_info));
                  }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 613 "NEW_PASCC.y"
    {
                    if (currentSymbolTable->lookupEntry(GET_STR_VAL((yyvsp[(2) - (5)].token_info)))) {
                        std::cerr << "LINE[" << (yyvsp[(2) - (5)].token_info)->line_no << "]ERROR: Duplicate function definition '" << GET_STR_VAL((yyvsp[(2) - (5)].token_info)) << "'\n";
                        exit(EXIT_FAILURE);
                    }
                    else{
                      cout << "Function: " << GET_STR_VAL((yyvsp[(2) - (5)].token_info)) << " returning " << GET_TYPE((yyvsp[(5) - (5)].token_info)) << endl;
                      (yyval.ast) = new SubprogramHeadNode(GET_STR_VAL((yyvsp[(2) - (5)].token_info)), (yyvsp[(3) - (5)].ast), true, GET_STR_VAL((yyvsp[(5) - (5)].token_info)));
                      cout<<"1"<<endl;

                      FuncSymbol* func = new FuncSymbol(GET_STR_VAL((yyvsp[(2) - (5)].token_info)), (yyval.ast), dynamic_cast<SubprogramHeadNode*>((yyval.ast))->return_type);
                      currentSymbolTable->addSymbol(func);
                      currentSymbolTable = currentSymbolTable->getChildTable(GET_STR_VAL((yyvsp[(2) - (5)].token_info)));
                      if ((yyvsp[(3) - (5)].ast)) {
                        vector<string> allParamNames;
                        vector<ASTNode*> param_list = dynamic_cast<ParameterListNode*>((yyvsp[(3) - (5)].ast))->param_list;
                        for (const auto& it : param_list) {
                          ParameterNode* param = dynamic_cast<ParameterNode*>(it);
                          vector<string> idList = dynamic_cast<IdentifierListNode*>(param->id_list)->identifier_list;
                          BasicType type = param->type;
                          for (const auto& id : idList) {
                            if (currentSymbolTable->lookupCurrent(id)) {
                              std::cerr << "LINE[" << (yyvsp[(1) - (5)].token_info)->line_no << "]ERROR: Duplicate function parameter '" << id << "'\n";
                              continue;
                            }
                            allParamNames.push_back(id);
                            SymbolType* varType = new SymbolType(type);
                            VarSymbol* var = new VarSymbol(id, varType);
                            var->setPointer(static_cast<ParameterNode*>(it)->is_pointer);
                            currentSymbolTable->addSymbol(var);
                            func->addParameter(var);
                          }
                        }
                      }
                    }
                    cout<<"--------------"<<endl;
                    safeDelete((yyvsp[(1) - (5)].token_info), (yyvsp[(2) - (5)].token_info), (yyvsp[(4) - (5)].token_info), (yyvsp[(5) - (5)].token_info));
                  }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 652 "NEW_PASCC.y"
    { 
                    cout<<"Empty Formal Parameters" << endl;
                    (yyval.ast) = nullptr;}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 656 "NEW_PASCC.y"
    {
                  cout << "Formal Parameters" << endl;
                  (yyval.ast) = (yyvsp[(2) - (3)].ast);
                  safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 662 "NEW_PASCC.y"
    { 
                  cout << "Empty Parameter List" << endl;
                  (yyval.ast) = new ParameterListNode();
                }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 667 "NEW_PASCC.y"
    {
                  cout << "Parameter" << endl;
                  (yyval.ast) = new ParameterListNode(vector<ASTNode*>{(yyvsp[(1) - (1)].ast)});
                }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 672 "NEW_PASCC.y"
    {
                  cout << "Adding Parameter" << endl;
                  dynamic_cast<ParameterListNode*>((yyvsp[(1) - (3)].ast))->param_list.push_back((yyvsp[(3) - (3)].ast));
                  (yyval.ast) = (yyvsp[(1) - (3)].ast);
                  safeDelete((yyvsp[(2) - (3)].token_info));
                }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 680 "NEW_PASCC.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 682 "NEW_PASCC.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 685 "NEW_PASCC.y"
    { 
                cout << "Var Parameter" << endl;
                // printNodeType($2);
                (yyval.ast) = (yyvsp[(2) - (2)].ast);
                dynamic_cast<ParameterNode*>((yyval.ast))->is_pointer = true;
                safeDelete((yyvsp[(1) - (2)].token_info));
              }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 694 "NEW_PASCC.y"
    {
                    cout << "Value Parameter with type: " << GET_TYPE((yyvsp[(3) - (3)].token_info)) << endl;
                    (yyval.ast) = new ParameterNode((yyvsp[(1) - (3)].ast), GET_STR_VAL((yyvsp[(3) - (3)].token_info)));
                    safeDelete((yyvsp[(2) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                  }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 701 "NEW_PASCC.y"
    {
                    cout << "Subprogram Body" << endl;
                    (yyval.ast) = new SubprogramBodyNode((yyvsp[(1) - (4)].ast), (yyvsp[(2) - (4)].ast), (yyvsp[(3) - (4)].ast), (yyvsp[(4) - (4)].ast));

                    currentSymbolTable = currentSymbolTable->getParent();
                  }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 709 "NEW_PASCC.y"
    { 
                      cout << "Compound Statement" << endl;
                      (yyval.ast) = (yyvsp[(2) - (3)].ast);
                      safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(3) - (3)].token_info)); 
                    }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 716 "NEW_PASCC.y"
    {
                  cout << "Statement" << endl;
                  (yyval.ast) = new StatementListNode(vector<ASTNode*>{(yyvsp[(1) - (1)].ast)});
                }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 721 "NEW_PASCC.y"
    {
                  cout << "Adding Statement" << endl;
                  dynamic_cast<StatementListNode*>((yyvsp[(1) - (3)].ast))->statement_list.push_back((yyvsp[(3) - (3)].ast));
                  (yyval.ast) = (yyvsp[(1) - (3)].ast);
                  safeDelete((yyvsp[(2) - (3)].token_info));
                }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 739 "NEW_PASCC.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 741 "NEW_PASCC.y"
    { 
              cout << "Control Statement: " << GET_STR_VAL((yyvsp[(1) - (1)].token_info)) << endl;
              (yyval.ast) = new ControlStatementNode(GET_STR_VAL((yyvsp[(1) - (1)].token_info)));
              safeDelete((yyvsp[(1) - (1)].token_info));
            }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 747 "NEW_PASCC.y"
    { 
              cout << "Control Statement: " << GET_STR_VAL((yyvsp[(1) - (1)].token_info)) << endl;
              (yyval.ast) = new ControlStatementNode(GET_STR_VAL((yyvsp[(1) - (1)].token_info)));
              safeDelete((yyvsp[(1) - (1)].token_info));
            }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 753 "NEW_PASCC.y"
    {
                    cout << "Empty Statement" << endl;
                    (yyval.ast) = new EmptyStatementNode();
                  }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 759 "NEW_PASCC.y"
    {
                    cout << "Assign Statement" << endl;
                    (yyval.ast) = new AssignStatementNode((yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
                    safeDelete((yyvsp[(2) - (3)].token_info));
                  }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 766 "NEW_PASCC.y"
    {
                    cout << "Function Assign Statement: " << GET_STR_VAL((yyvsp[(1) - (3)].token_info)) << endl;
                    (yyval.ast) = new FuncAssignStatementNode(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), (yyvsp[(3) - (3)].ast));
                    safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(2) - (3)].token_info));
                  }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 773 "NEW_PASCC.y"
    {
                cout << "If Statement" << endl;
                (yyval.ast) = new IfStatementNode((yyvsp[(2) - (5)].ast), (yyvsp[(4) - (5)].ast), (yyvsp[(5) - (5)].ast));
                safeDelete((yyvsp[(1) - (5)].token_info), (yyvsp[(3) - (5)].token_info));
              }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 780 "NEW_PASCC.y"
    {
                  cout << "For Statement (to): " << GET_STR_VAL((yyvsp[(2) - (8)].token_info)) << endl;
                  (yyval.ast) = new ForStatementNode(GET_STR_VAL((yyvsp[(2) - (8)].token_info)), (yyvsp[(4) - (8)].ast), (yyvsp[(6) - (8)].ast), (yyvsp[(8) - (8)].ast), false);
                  safeDelete((yyvsp[(1) - (8)].token_info), (yyvsp[(2) - (8)].token_info), (yyvsp[(3) - (8)].token_info), (yyvsp[(5) - (8)].token_info), (yyvsp[(7) - (8)].token_info));
                }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 786 "NEW_PASCC.y"
    {
                  cout << "For Statement (downto): " << GET_STR_VAL((yyvsp[(2) - (8)].token_info)) << endl;
                  (yyval.ast) = new ForStatementNode(GET_STR_VAL((yyvsp[(2) - (8)].token_info)), (yyvsp[(4) - (8)].ast), (yyvsp[(6) - (8)].ast), (yyvsp[(8) - (8)].ast), true);
                  safeDelete((yyvsp[(1) - (8)].token_info), (yyvsp[(2) - (8)].token_info), (yyvsp[(3) - (8)].token_info), (yyvsp[(5) - (8)].token_info), (yyvsp[(7) - (8)].token_info));
                }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 793 "NEW_PASCC.y"
    {
                  cout << "Read Statement" << endl;
                  (yyval.ast) = new ReadStatementNode((yyvsp[(3) - (4)].ast));
                  safeDelete((yyvsp[(1) - (4)].token_info), (yyvsp[(2) - (4)].token_info), (yyvsp[(4) - (4)].token_info));
                }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 799 "NEW_PASCC.y"
    {
                  cout << "Readln Statement" << endl;
                  (yyval.ast) = new ReadlnStatementNode((yyvsp[(3) - (4)].ast));
                  safeDelete((yyvsp[(1) - (4)].token_info), (yyvsp[(2) - (4)].token_info), (yyvsp[(4) - (4)].token_info));
                }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 806 "NEW_PASCC.y"
    {
                  //cout << "Write Statement" << endl;
                  (yyval.ast) = new WriteStatementNode((yyvsp[(3) - (4)].ast));
                  safeDelete((yyvsp[(1) - (4)].token_info), (yyvsp[(2) - (4)].token_info), (yyvsp[(4) - (4)].token_info));
                }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 812 "NEW_PASCC.y"
    {
                  cout << "Writeln Statement" << endl;
                  (yyval.ast) = new WritelnStatementNode((yyvsp[(3) - (4)].ast));
                  safeDelete((yyvsp[(1) - (4)].token_info), (yyvsp[(2) - (4)].token_info), (yyvsp[(4) - (4)].token_info));
                }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 819 "NEW_PASCC.y"
    {
                    cout << "Switch Statement" << endl;
                    (yyval.ast) = new SwitchStatementNode((yyvsp[(2) - (6)].ast), (yyvsp[(4) - (6)].ast));
                    safeDelete((yyvsp[(1) - (6)].token_info), (yyvsp[(3) - (6)].token_info), (yyvsp[(5) - (6)].token_info));
                  }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 827 "NEW_PASCC.y"
    { 
                    cout << "Switch Case" << endl;
                    (yyval.ast) = new SwitchCaseListNode(vector<ASTNode*>{(yyvsp[(1) - (1)].ast)});
                  }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 832 "NEW_PASCC.y"
    { 
                    cout << "Adding Switch Case" << endl;
                    dynamic_cast<SwitchCaseListNode*>((yyvsp[(1) - (3)].ast))->cases.push_back((yyvsp[(3) - (3)].ast));
                    (yyval.ast) = (yyvsp[(1) - (3)].ast);
                    safeDelete((yyvsp[(2) - (3)].token_info));
                  }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 841 "NEW_PASCC.y"
    { 
                    cout << "Switch Case Item" << endl;
                    (yyval.ast) = new SwitchCaseItemNode((yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
                    safeDelete((yyvsp[(2) - (3)].token_info));
                  }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 849 "NEW_PASCC.y"
    { 
                    cout << "While Statement" << endl;
                    (yyval.ast) = new WhileStatementNode((yyvsp[(2) - (4)].ast), (yyvsp[(4) - (4)].ast));
                    safeDelete((yyvsp[(1) - (4)].token_info), (yyvsp[(3) - (4)].token_info));
                  }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 857 "NEW_PASCC.y"
    {
                  cout << "Variable" << endl;
                  (yyval.ast) = new VariableListNode(vector<ASTNode*>{(yyvsp[(1) - (1)].ast)});
                }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 862 "NEW_PASCC.y"
    {
                  cout << "Adding Variable" << endl;
                  dynamic_cast<VariableListNode*>((yyvsp[(1) - (3)].ast))->variables.push_back((yyvsp[(3) - (3)].ast));
                  (yyval.ast) = (yyvsp[(1) - (3)].ast);
                  safeDelete((yyvsp[(2) - (3)].token_info));
                }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 870 "NEW_PASCC.y"
    {
              if (!currentSymbolTable->lookupEntry(GET_STR_VAL((yyvsp[(1) - (2)].token_info)))) {
                std::cerr << "LINE[" << (yyvsp[(1) - (2)].token_info)->line_no << "]ERROR: Undefined variable or variable of a non-existent type '" 
                 << GET_STR_VAL((yyvsp[(1) - (2)].token_info)) << "'\n";
                exit(EXIT_FAILURE);
              }
              cout << "Variable: " << GET_STR_VAL((yyvsp[(1) - (2)].token_info)) << endl;
              (yyval.ast) = new VariableNode(GET_STR_VAL((yyvsp[(1) - (2)].token_info)), (yyvsp[(2) - (2)].ast));
              safeDelete((yyvsp[(1) - (2)].token_info));
            }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 881 "NEW_PASCC.y"
    {
              cout<<"id_varpart: nullptr"<<endl; 
              (yyval.ast) = nullptr; }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 885 "NEW_PASCC.y"
    { 
              cout<<"id_varpart: id_varpart_n"<<endl;
              (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 889 "NEW_PASCC.y"
    { 
                cout<<"IdVarPartList : nullptr"<<endl;
                (yyval.ast) = new IdVarPartListNode(); }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 893 "NEW_PASCC.y"
    {
              cout << "Array Access" << endl;
              // printNodeType($3);
              cout<<endl<<endl;
              ASTNode* idVarPartNode = new IdVarPartNode((yyvsp[(3) - (4)].ast));
              // printNodeType(idVarPartNode);
              dynamic_cast<IdVarPartListNode*>((yyvsp[(1) - (4)].ast))->id_var_part_list.push_back(idVarPartNode);
              (yyval.ast) = (yyvsp[(1) - (4)].ast);
              safeDelete((yyvsp[(2) - (4)].token_info), (yyvsp[(4) - (4)].token_info));
            }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 905 "NEW_PASCC.y"
    {
                  cout << "Procedure Call: " << GET_STR_VAL((yyvsp[(1) - (1)].token_info)) << endl;
                  (yyval.ast) = new ProcedureCallNode(GET_STR_VAL((yyvsp[(1) - (1)].token_info)), nullptr);
                  safeDelete((yyvsp[(1) - (1)].token_info));
                }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 911 "NEW_PASCC.y"
    {
                  cout << "Procedure Call: " << GET_STR_VAL((yyvsp[(1) - (1)].token_info)) << endl;
                  (yyval.ast) = new ProcedureCallNode(GET_STR_VAL((yyvsp[(1) - (1)].token_info)), nullptr);
                  safeDelete((yyvsp[(1) - (1)].token_info));
                }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 917 "NEW_PASCC.y"
    {
                  cout << "Procedure Call: " << GET_STR_VAL((yyvsp[(1) - (3)].token_info)) << endl;
                  (yyval.ast) = new ProcedureCallNode(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), nullptr);
                  safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(2) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 923 "NEW_PASCC.y"
    {
                  cout << "Procedure Call: " << GET_STR_VAL((yyvsp[(1) - (3)].token_info)) << endl;
                  (yyval.ast) = new ProcedureCallNode(GET_STR_VAL((yyvsp[(1) - (3)].token_info)), nullptr);
                  safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(2) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 929 "NEW_PASCC.y"
    {
                  cout << "Procedure Call with args: " << GET_STR_VAL((yyvsp[(1) - (4)].token_info)) << endl;
                  (yyval.ast) = new ProcedureCallNode(GET_STR_VAL((yyvsp[(1) - (4)].token_info)), (yyvsp[(3) - (4)].ast));
                  safeDelete((yyvsp[(1) - (4)].token_info), (yyvsp[(2) - (4)].token_info), (yyvsp[(4) - (4)].token_info));
                }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 935 "NEW_PASCC.y"
    {
                  cout << "Procedure Call with args: " << GET_STR_VAL((yyvsp[(1) - (4)].token_info)) << endl;
                  (yyval.ast) = new ProcedureCallNode(GET_STR_VAL((yyvsp[(1) - (4)].token_info)), (yyvsp[(3) - (4)].ast));
                  safeDelete((yyvsp[(1) - (4)].token_info), (yyvsp[(2) - (4)].token_info), (yyvsp[(4) - (4)].token_info));
                }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 941 "NEW_PASCC.y"
    { (yyval.ast) = nullptr; }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 943 "NEW_PASCC.y"
    {
              cout << "Else Part" << endl;
              (yyval.ast) = new ElsePartNode((yyvsp[(2) - (2)].ast));
              safeDelete((yyvsp[(1) - (2)].token_info));
            }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 950 "NEW_PASCC.y"
    {
                  cout << "Expression" << endl;
                  (yyval.ast) = new ExpressionListNode(vector<ASTNode*>{(yyvsp[(1) - (1)].ast)});
                }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 955 "NEW_PASCC.y"
    {
                  cout << "Adding Expression" << endl;
                  dynamic_cast<ExpressionListNode*>((yyvsp[(1) - (3)].ast))->expr_list.push_back((yyvsp[(3) - (3)].ast));
                  (yyval.ast) = (yyvsp[(1) - (3)].ast);
                  safeDelete((yyvsp[(2) - (3)].token_info));
                }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 963 "NEW_PASCC.y"
    { 
              cout<<"Simple Expression"<<endl;
              (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 967 "NEW_PASCC.y"
    { 
              cout<<"String Expression"<<endl;
              (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 971 "NEW_PASCC.y"
    {
              cout << "Relational Expression: " << GET_STR_VAL((yyvsp[(2) - (3)].token_info)) << endl;
              (yyval.ast) = new BinaryOpNode(GET_STR_VAL((yyvsp[(2) - (3)].token_info)), (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
              safeDelete((yyvsp[(2) - (3)].token_info));
            }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 977 "NEW_PASCC.y"
    {
              cout << "Relational Expression: " << GET_STR_VAL((yyvsp[(2) - (3)].token_info)) << endl;
              (yyval.ast) = new BinaryOpNode(GET_STR_VAL((yyvsp[(2) - (3)].token_info)), (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
              safeDelete((yyvsp[(2) - (3)].token_info));
            }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 984 "NEW_PASCC.y"
    {
                  cout << "String Expression: " << GET_STR_VAL((yyvsp[(1) - (1)].token_info)) << endl;
                  (yyval.ast) = new StrExpressionNode(GET_STR_VAL((yyvsp[(1) - (1)].token_info)));
                  safeDelete((yyvsp[(1) - (1)].token_info));
                }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 990 "NEW_PASCC.y"
    {
                  cout << "String Concatenation" << endl;
                  (yyval.ast) = new StrExpressionNode(GET_STR_VAL((yyvsp[(1) - (3)].token_info)) + GET_STR_VAL((yyvsp[(3) - (3)].token_info)));
                  safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(2) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 996 "NEW_PASCC.y"
    {
                  cout << "String-Char Concatenation" << endl;
                  (yyval.ast) = new StrExpressionNode(GET_STR_VAL((yyvsp[(1) - (3)].token_info)) + string(1, GET_CHAR_VAL((yyvsp[(3) - (3)].token_info))));
                  safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(2) - (3)].token_info), (yyvsp[(3) - (3)].token_info));
                }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1003 "NEW_PASCC.y"
    {
                      cout << "Additive Operation: " << GET_STR_VAL((yyvsp[(2) - (3)].token_info)) << endl;
                      (yyval.ast) = new BinaryOpNode(GET_STR_VAL((yyvsp[(2) - (3)].token_info)), (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
                      safeDelete((yyvsp[(2) - (3)].token_info));
                    }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1009 "NEW_PASCC.y"
    {
                      cout << "Additive Operation: " << GET_STR_VAL((yyvsp[(2) - (3)].token_info)) << endl;
                      (yyval.ast) = new BinaryOpNode(GET_STR_VAL((yyvsp[(2) - (3)].token_info)), (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
                      safeDelete((yyvsp[(2) - (3)].token_info));
                    }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1015 "NEW_PASCC.y"
    {
                      cout << "Additive Operation: " << GET_STR_VAL((yyvsp[(2) - (3)].token_info)) << endl;
                      (yyval.ast) = new BinaryOpNode(GET_STR_VAL((yyvsp[(2) - (3)].token_info)), (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
                      safeDelete((yyvsp[(2) - (3)].token_info));
                    }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1021 "NEW_PASCC.y"
    { 
                      cout<<"Term"<<endl;
                      (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1026 "NEW_PASCC.y"
    { 
          cout<<"Factor"<<endl;
          (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 1030 "NEW_PASCC.y"
    {
          cout << "Multiplicative Operation: " << GET_STR_VAL((yyvsp[(2) - (3)].token_info)) << endl;
          (yyval.ast) = new BinaryOpNode(GET_STR_VAL((yyvsp[(2) - (3)].token_info)), (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
          safeDelete((yyvsp[(2) - (3)].token_info));
        }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1037 "NEW_PASCC.y"
    { 
          cout<<"Constant Value"<<endl;
          (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1041 "NEW_PASCC.y"
    { 
          cout<<"Variable"<<endl; 
          (yyval.ast) = (yyvsp[(1) - (1)].ast); }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1045 "NEW_PASCC.y"
    { 
          cout << "Parenthesized Expression" << endl;
          (yyval.ast) = (yyvsp[(2) - (3)].ast);
          safeDelete((yyvsp[(1) - (3)].token_info), (yyvsp[(3) - (3)].token_info)); 
        }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1051 "NEW_PASCC.y"
    {
          (yyval.ast) = (yyvsp[(1) - (1)].ast);
        }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1055 "NEW_PASCC.y"
    {
          cout << "Unary Operation: " << GET_STR_VAL((yyvsp[(1) - (2)].token_info)) << endl;
          (yyval.ast) = new UnaryOpNode(GET_STR_VAL((yyvsp[(1) - (2)].token_info)), (yyvsp[(2) - (2)].ast));
          safeDelete((yyvsp[(1) - (2)].token_info));
        }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1061 "NEW_PASCC.y"
    {
          cout << "Unary Operation: " << GET_STR_VAL((yyvsp[(1) - (2)].token_info)) << endl;
          (yyval.ast) = new UnaryOpNode(GET_STR_VAL((yyvsp[(1) - (2)].token_info)), (yyvsp[(2) - (2)].ast));
          safeDelete((yyvsp[(1) - (2)].token_info));
        }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1067 "NEW_PASCC.y"
    {
          cout << "Unary Operation: " << GET_STR_VAL((yyvsp[(1) - (2)].token_info)) << endl;
          (yyval.ast) = new UnaryOpNode(GET_STR_VAL((yyvsp[(1) - (2)].token_info)), (yyvsp[(2) - (2)].ast));
          safeDelete((yyvsp[(1) - (2)].token_info));
        }
    break;


/* Line 1792 of yacc.c  */
#line 3050 "NEW_PASCC.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (rootPtr, YY_("syntax error"));
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
        yyerror (rootPtr, yymsgp);
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
		      yytoken, &yylval, rootPtr);
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
		  yystos[yystate], yyvsp, rootPtr);
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
  yyerror (rootPtr, YY_("memory exhausted"));
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
                  yytoken, &yylval, rootPtr);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, rootPtr);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 1073 "NEW_PASCC.y"


void yyerror(ASTNode** rootPtr, const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    cout<<"Error: " << msg << endl;
    *rootPtr = nullptr;
}

void yynote(ASTNode** rootPtr, std::string msg, int line) {
    fprintf(stderr, "Note: %s at line %d\n", msg.c_str(), line);
    *rootPtr = nullptr;
}

void yyerror_var(ASTNode** rootPtr, const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    *rootPtr = nullptr;
}