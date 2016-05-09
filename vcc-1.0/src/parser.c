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
#line 7 "parser.y" /* yacc.c:339  */



#include <stdio.h>

#include "symtab.h"  
#include "mem.h"
#include "gen.h"
#include "heap.h"


extern 	int  byte_count;

static 	int break_loc, loop_body;

extern	FILE *temp;
bool 	err = false;
bool 	argRgn = false;
int 	storageClass;

enum
{
	kInt,
	kVoid
};


 

#line 96 "parser.tab.c" /* yacc.c:339  */

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
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    Identifier = 258,
    Constant = 259,
    INT = 260,
    VOID = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    FOR = 265,
    BREAK = 266,
    CONTINUE = 267,
    RETURN = 268,
    GETC = 269,
    PUTC = 270,
    GE = 271,
    LE = 272,
    EQ = 273,
    NE = 274,
    PE = 275,
    ME = 276,
    TE = 277,
    DE = 278,
    RE = 279,
    PP = 280,
    MM = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 36 "parser.y" /* yacc.c:355  */

	struct symtab *y_sym;	/* Identifier */
	char *y_str;		/* Constant */
	int  y_num;		/* count */
	int  y_lab;		/* label */
	int  y_reg;		/* Register */

#line 171 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 188 "parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   334

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  195

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    25,    32,     2,
      17,    18,    23,    21,    43,    22,     2,    24,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    16,
      26,    35,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    19,    34,    20,     2,     2,     2,     2,
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
      15,    28,    29,    30,    31,    36,    37,    38,    39,    40,
      41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   119,   119,   119,   137,   137,   139,   138,   142,   143,
     147,   148,   153,   159,   152,   185,   187,   192,   193,   197,
     200,   205,   207,   209,   215,   221,   225,   234,   233,   246,
     248,   250,   254,   257,   258,   260,   261,   262,   264,   267,
     269,   278,   283,   291,   296,   301,   303,   307,   309,   311,
     316,   320,   321,   326,   330,   334,   338,   339,   345,   344,
     354,   353,   370,   372,   378,   377,   389,   393,   388,   407,
     416,   417,   422,   424,   425,   428,   430,   434,   436,   439,
     438,   444,   449,   454,   458,   462,   464,   466,   468,   470,
     472,   474,   476,   478,   480,   482,   484,   486,   488,   491,
     496,   501,   505,   511,   516,   526,   527,   531,   536,   542,
     544,   545,   551,   552,   553
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Identifier", "Constant", "INT", "VOID",
  "IF", "ELSE", "WHILE", "FOR", "BREAK", "CONTINUE", "RETURN", "GETC",
  "PUTC", "';'", "'('", "')'", "'{'", "'}'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'<'", "'>'", "GE", "LE", "EQ", "NE", "'&'", "'^'", "'|'", "'='",
  "PE", "ME", "TE", "DE", "RE", "PP", "MM", "','", "'['", "']'", "$accept",
  "program", "$@1", "definitions", "$@2", "$@3", "definition",
  "function_definition", "$@4", "@5", "type_class",
  "optional_parameter_list", "parameter_list", "param_decl",
  "compound_statement", "@6", "declarations", "declaration",
  "declarator_list", "initializer", "integer_list", "statements",
  "statement", "@7", "@8", "if_prefix", "loop_prefix", "@9", "@10", "@11",
  "expression", "binary", "$@12", "memory_ref", "optional_argument_list",
  "argument_list", "rp", "sc", "rr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,    59,    40,    41,   123,
     125,    43,    45,    42,    47,    37,    60,    62,   271,   272,
     273,   274,    38,    94,   124,    61,   275,   276,   277,   278,
     279,   280,   281,    44,    91,    93
};
# endif

#define YYPACT_NINF -91

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-91)))

#define YYTABLE_NINF -107

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -91,    16,   215,   -91,   -91,   -91,   -91,    94,   -91,   -91,
     -91,    22,    22,   -11,    14,   -91,   -91,   -91,   -91,   -91,
     -91,   -30,    12,   -91,     6,    72,    57,    82,   -91,    95,
     -91,    61,    98,    52,   -91,    64,   -91,    60,    80,   -91,
     -91,   -91,    68,   -91,    79,   -91,   -91,    68,    68,   -91,
      89,   -91,    90,   106,   -91,   -91,   135,   -91,   -91,   -91,
     -91,    66,   -91,   -91,   -91,    77,   117,   -91,   -91,   -91,
     -91,   137,   102,   -13,   -91,     9,    63,   138,   144,   144,
     190,   150,   164,   223,   -91,   193,   193,   -91,   -91,   173,
     -91,    67,   268,   291,   -91,   -91,   158,   -91,   238,   -91,
     238,   -91,   -91,   238,   -91,   -91,   102,    67,   -91,    52,
     238,   -10,    71,   157,   -91,   -91,   195,   173,   -91,   242,
     -91,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   268,
     194,    11,    71,   238,    74,   -91,   -91,    71,   -91,   -91,
     -91,   -91,   -91,   268,   119,   119,   -91,   -91,   310,   310,
     310,   310,   142,   142,   294,   282,   245,   268,   268,   268,
     268,   268,   -91,   268,    52,    73,   -91,   -91,    71,   -91,
     -91,   173,   -91,   -91,   246,   -91,   238,   -91,   -91,   268,
      76,   -91,   238,    71,   -91
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     8,    15,    16,     0,     4,     9,
       6,     0,     0,     0,     0,     5,    10,    11,     7,    12,
      35,    39,     0,    33,     0,     0,     0,    36,   113,     0,
      32,     0,     0,     0,    18,     0,    40,     0,     0,    37,
      38,    34,     0,    22,    25,   112,    13,     0,     0,    41,
       0,    24,     0,     0,    23,    20,     0,    26,    27,    14,
      43,     0,    29,    46,    42,     0,     0,    45,    44,    31,
      30,     0,    49,   103,    76,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,     0,     0,    56,    48,     0,
      60,     0,    70,    75,    51,    28,     0,    79,     0,    63,
       0,    69,    64,     0,    52,    53,     0,     0,    54,     0,
       0,     0,     0,   103,    81,    82,    57,     0,    73,     0,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    72,
       0,     0,     0,     0,     0,    55,    83,     0,    78,    77,
      58,    61,    74,    71,    85,    86,    87,    88,    90,    89,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   109,   107,     0,     0,   104,    62,     0,    66,
      84,     0,    80,   110,     0,    65,     0,    59,   111,   108,
       0,    67,     0,     0,    68
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -91,   -91,   -91,   -91,   -91,   -91,   198,   -91,   -91,   -91,
     210,   -91,   171,   -91,   169,   -91,   -91,   159,   -91,    84,
     -91,   -91,   -88,   -91,   -91,   -91,   -91,   -91,   -91,   -91,
     -80,   -87,   -91,   143,   -91,   -91,   -90,   -20,   -91
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,    11,    12,    15,    16,    24,    53,
       8,    33,    34,    35,    87,    62,    66,    17,    22,    23,
      61,    71,    88,   181,   117,    89,    90,   143,   186,   192,
      91,    92,   140,    93,   174,   175,    46,    94,    95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     107,   116,    30,   112,    97,    25,    19,    31,    45,   139,
      99,    32,   118,    27,    26,    20,     3,    21,   141,   146,
     142,   148,   149,   144,   -17,    13,   100,    14,    28,   151,
     147,    98,   153,    96,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   177,   173,   119,    29,   176,   180,   104,   105,
     108,    37,    31,   178,   101,    47,    32,    63,   118,    31,
      45,   120,   118,    32,   183,   118,    36,   118,    67,   -21,
     102,    68,   -19,    28,   182,    21,    64,   145,   185,    45,
     179,  -106,   191,   187,    -3,     9,    40,   189,    21,     5,
       6,    44,    38,   194,    42,    49,   190,    48,    56,    65,
     119,    39,   193,    41,   119,    50,   184,   119,    69,   119,
     -47,   -47,    14,    52,   -47,    58,   -47,   -47,   -47,   -47,
     -47,   -47,   -47,   -47,   -47,    57,   -47,   -47,    72,    60,
      73,    74,   123,   124,    75,    96,    76,    77,    78,    79,
      80,    81,    82,    28,    83,   103,    58,    84,   -47,   -47,
      28,    73,    74,   121,   122,   123,   124,   109,   125,   126,
     127,   128,    81,    82,   106,    83,    73,    74,    85,    86,
      75,   110,    76,    77,    78,    79,    80,    81,    82,    28,
      83,   106,    58,    73,    74,   172,   113,    73,    74,    85,
      86,    98,    43,   150,    81,    82,    28,    83,    81,    82,
      18,    83,  -105,    51,    85,    86,     4,    10,    54,    55,
       5,     6,    59,     0,   111,    70,    73,    74,   114,   115,
       0,    85,    86,     0,     0,    85,    86,    81,    82,   106,
      83,    73,    74,   152,     0,    73,    74,   188,     0,    73,
      74,     0,    81,    82,     0,    83,    81,    82,     0,    83,
      81,    82,     0,    83,    85,    86,   121,   122,   123,   124,
       0,   125,   126,   127,   128,   129,   130,   131,   132,    85,
      86,     0,     0,    85,    86,     0,     0,    85,    86,   121,
     122,   123,   124,     0,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   121,   122,   123,   124,     0,   125,   126,
     127,   128,   129,   130,   131,   121,   122,   123,   124,     0,
     125,   126,   127,   128,   129,   130,   134,   135,   136,   137,
     138,   121,   122,   123,   124
};

static const yytype_int16 yycheck[] =
{
      80,    89,    22,    83,    17,    35,    17,     1,    18,    96,
       1,     5,     1,     1,    44,     1,     0,     3,    98,   109,
     100,   111,   112,   103,    18,     3,    17,     5,    16,   117,
     110,    44,   119,    43,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   142,   140,    43,    43,    45,   147,    78,    79,
      80,     4,     1,   143,     1,     1,     5,     1,     1,     1,
      18,    91,     1,     5,     1,     1,     4,     1,     1,    18,
      17,     4,    18,    16,   174,     3,    20,   107,   178,    18,
      16,    18,    16,   181,     0,     1,     1,   184,     3,     5,
       6,     3,    45,   193,    43,    45,   186,    43,    19,    43,
      43,    27,   192,    29,    43,    35,    43,    43,     1,    43,
       3,     4,     5,    44,     7,    19,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    45,    19,    20,     1,     4,
       3,     4,    23,    24,     7,    43,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    17,    19,    20,    41,    42,
      16,     3,     4,    21,    22,    23,    24,    17,    26,    27,
      28,    29,    14,    15,     1,    17,     3,     4,    41,    42,
       7,    17,     9,    10,    11,    12,    13,    14,    15,    16,
      17,     1,    19,     3,     4,     1,     3,     3,     4,    41,
      42,    44,    31,     8,    14,    15,    16,    17,    14,    15,
      12,    17,    18,    42,    41,    42,     1,     7,    47,    48,
       5,     6,    53,    -1,     1,    66,     3,     4,    85,    86,
      -1,    41,    42,    -1,    -1,    41,    42,    14,    15,     1,
      17,     3,     4,     1,    -1,     3,     4,     1,    -1,     3,
       4,    -1,    14,    15,    -1,    17,    14,    15,    -1,    17,
      14,    15,    -1,    17,    41,    42,    21,    22,    23,    24,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    41,
      42,    -1,    -1,    41,    42,    -1,    -1,    41,    42,    21,
      22,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    21,    22,    23,    24,    -1,    26,    27,
      28,    29,    30,    31,    32,    21,    22,    23,    24,    -1,
      26,    27,    28,    29,    30,    31,    35,    36,    37,    38,
      39,    21,    22,    23,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    48,     0,     1,     5,     6,    49,    56,     1,
      56,    50,    51,     3,     5,    52,    53,    63,    52,    17,
       1,     3,    64,    65,    54,    35,    44,     1,    16,    43,
      83,     1,     5,    57,    58,    59,     4,     4,    45,    65,
       1,    65,    43,    58,     3,    18,    82,     1,    43,    45,
      35,    58,    44,    55,    58,    58,    19,    45,    19,    60,
       4,    66,    61,     1,    20,    43,    62,     1,     4,     1,
      63,    67,     1,     3,     4,     7,     9,    10,    11,    12,
      13,    14,    15,    17,    20,    41,    42,    60,    68,    71,
      72,    76,    77,    79,    83,    84,    43,    17,    44,     1,
      17,     1,    17,    17,    83,    83,     1,    76,    83,    17,
      17,     1,    76,     3,    79,    79,    68,    70,     1,    43,
      83,    21,    22,    23,    24,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    77,
      78,    76,    76,    73,    76,    83,    82,    76,    82,    82,
       8,    68,     1,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,     1,    77,    80,    81,    45,    82,    76,    16,
      82,    69,    82,     1,    43,    82,    74,    68,     1,    77,
      76,    16,    75,    76,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    48,    47,    50,    49,    51,    49,    49,    49,
      52,    52,    54,    55,    53,    56,    56,    57,    57,    58,
      58,    58,    58,    58,    58,    59,    59,    61,    60,    62,
      62,    62,    63,    64,    64,    64,    64,    64,    64,    65,
      65,    65,    65,    66,    66,    66,    66,    67,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    69,    68,
      70,    68,    71,    71,    73,    72,    74,    75,    72,    72,
      76,    76,    76,    76,    76,    77,    77,    77,    77,    78,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    79,    79,    80,    80,    81,    81,    81,
      81,    81,    82,    83,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     3,     0,     4,     1,     2,
       1,     1,     0,     0,     7,     1,     1,     0,     1,     1,
       3,     1,     2,     3,     3,     2,     4,     0,     5,     0,
       2,     2,     3,     1,     3,     1,     2,     3,     3,     1,
       3,     4,     7,     1,     3,     3,     2,     0,     2,     2,
       2,     1,     2,     2,     2,     3,     1,     2,     0,     5,
       0,     3,     4,     2,     0,     5,     0,     0,    10,     2,
       1,     3,     3,     2,     3,     1,     1,     3,     3,     0,
       5,     2,     2,     3,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     4,     0,     1,     1,     3,     1,
       2,     3,     1,     1,     1
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
#line 119 "parser.y" /* yacc.c:1646  */
    { 
	  	SymtabInit(); 
		write_header();
	  }
#line 1436 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 124 "parser.y" /* yacc.c:1646  */
    { 
	  	write_io();
		write_globals();
	  	#ifdef TRACE
		message("\n;; Total number of bytes: %d\n", byte_count);
		#endif
		
		if (err) return -1;
		
	  }
#line 1451 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 137 "parser.y" /* yacc.c:1646  */
    { storageClass = (yyvsp[0].y_num); }
#line 1457 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 139 "parser.y" /* yacc.c:1646  */
    { storageClass = (yyvsp[0].y_num); }
#line 1463 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 141 "parser.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1469 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 153 "parser.y" /* yacc.c:1646  */
    { 
	  	make_func((yyvsp[-1].y_sym));
		blk_push(); 
		st_offset = 0;
	  }
#line 1479 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 159 "parser.y" /* yacc.c:1646  */
    { 
		(yyval.y_lab) = l_offset;
		chk_parm((yyvsp[-4].y_sym), count_parms((yyvsp[-1].y_sym))); 
		all_parm((yyvsp[-1].y_sym));
		l_max = st_offset;
		fprintf(temp, "\n;; Function %s - offset %d\n", 
			(yyvsp[-4].y_sym)->s_name, (yyvsp[-4].y_sym)->byte_offset);
		
		gen_func_header((yyvsp[-4].y_sym), (yyvsp[-1].y_sym));
		currentf = (yyvsp[-4].y_sym);
	  }
#line 1495 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 171 "parser.y" /* yacc.c:1646  */
    { 
	  	all_func((yyvsp[-6].y_sym));
		if (currentf->returnSet == 0)
		{
			gen_return(-1);
			if (storageClass != kVoid)
				warning("Function %s should return a value.\n",
					currentf->s_name);
		} 
		l_offset = (yyvsp[-1].y_lab);
		clear_regs();
		currentf = NULL;
	  }
#line 1513 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 186 "parser.y" /* yacc.c:1646  */
    { (yyval.y_num) = kInt; }
#line 1519 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 188 "parser.y" /* yacc.c:1646  */
    { (yyval.y_num) = kVoid; }
#line 1525 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 192 "parser.y" /* yacc.c:1646  */
    { (yyval.y_sym) = 0; /* No formal parameters */ }
#line 1531 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 198 "parser.y" /* yacc.c:1646  */
    { (yyval.y_sym) = link_parm((yyvsp[0].y_sym), NULL);
		  make_parm((yyvsp[0].y_sym)); }
#line 1538 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 201 "parser.y" /* yacc.c:1646  */
    { (yyval.y_sym) = link_parm((yyvsp[-2].y_sym), (yyvsp[0].y_sym));
		  make_parm((yyvsp[-2].y_sym));
		  yyerrok; 
		}
#line 1547 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 206 "parser.y" /* yacc.c:1646  */
    { (yyval.y_sym) = 0; }
#line 1553 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 208 "parser.y" /* yacc.c:1646  */
    { (yyval.y_sym) = (yyvsp[0].y_sym); }
#line 1559 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 210 "parser.y" /* yacc.c:1646  */
    { 
	  	(yyval.y_sym) = link_parm((yyvsp[-2].y_sym), (yyvsp[0].y_sym));
		make_parm((yyvsp[-2].y_sym));
		yyerrok;
	  }
#line 1569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 216 "parser.y" /* yacc.c:1646  */
    { (yyval.y_sym) = (yyvsp[0].y_sym);
		  yyerrok;
		}
#line 1577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 222 "parser.y" /* yacc.c:1646  */
    {
			(yyval.y_sym) = (yyvsp[0].y_sym);
		}
#line 1585 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 226 "parser.y" /* yacc.c:1646  */
    {
	  	arrayparam((yyvsp[-2].y_sym));
	  	(yyval.y_sym) = (yyvsp[-2].y_sym);
	  }
#line 1594 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 234 "parser.y" /* yacc.c:1646  */
    { 
	  	(yyval.y_lab) = l_offset;
	  	blk_push(); 
	  }
#line 1603 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 239 "parser.y" /* yacc.c:1646  */
    { 
	  	if (l_offset > l_max)
			l_max = l_offset;
		l_offset = (yyvsp[-3].y_lab);
		blk_pop(); 
	  }
#line 1614 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 249 "parser.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1620 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 259 "parser.y" /* yacc.c:1646  */
    {  yyerrok; }
#line 1626 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 263 "parser.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1632 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 268 "parser.y" /* yacc.c:1646  */
    { all_var((yyvsp[0].y_sym), 0); }
#line 1638 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 270 "parser.y" /* yacc.c:1646  */
    { 
	  	all_var((yyvsp[-2].y_sym), atoi((yyvsp[0].y_str)));
	  	/* We don't want to load globals immediately into registers */
	  	if ((yyvsp[-2].y_sym)->s_scope == LOCAL_PTR)
	  	{
			assign((yyvsp[-2].y_sym), gen_li((yyvsp[0].y_str)));
	  	}
	  }
#line 1651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 279 "parser.y" /* yacc.c:1646  */
    { 
	  	all_array((yyvsp[-3].y_sym), atoi((yyvsp[-1].y_str)));
	  	gen_array_alloc((yyvsp[-3].y_sym));
	  }
#line 1660 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 284 "parser.y" /* yacc.c:1646  */
    {
	  	all_array((yyvsp[-6].y_sym), (yyvsp[-1].y_num));
		gen_array_alloc((yyvsp[-6].y_sym));
		arrayInit((yyvsp[-6].y_sym), (yyvsp[-1].y_num));
	  }
#line 1670 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 292 "parser.y" /* yacc.c:1646  */
    { 
			(yyval.y_num) = 1; 
			addInitElement((yyvsp[0].y_str), 0);
		}
#line 1679 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 297 "parser.y" /* yacc.c:1646  */
    { 
			addInitElement((yyvsp[0].y_str), (yyvsp[-2].y_num));
			(yyval.y_num) += 1; 
		}
#line 1688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 302 "parser.y" /* yacc.c:1646  */
    { (yyval.y_num) = 0; }
#line 1694 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 304 "parser.y" /* yacc.c:1646  */
    { (yyval.y_num) = 0; }
#line 1700 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 310 "parser.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1706 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 317 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = (yyvsp[-1].y_reg); 
		  currentf->returnSet = 0;
		}
#line 1714 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 322 "parser.y" /* yacc.c:1646  */
    { 
	  	gen_break(); 
		currentf->returnSet = 0;
	  }
#line 1723 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 327 "parser.y" /* yacc.c:1646  */
    { gen_continue(); 
			currentf->returnSet = 0;
		}
#line 1731 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 331 "parser.y" /* yacc.c:1646  */
    { gen_return(-1);
		  currentf->returnSet = 1;
		 }
#line 1739 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 335 "parser.y" /* yacc.c:1646  */
    { gen_return((yyvsp[-1].y_reg)); 
		  currentf->returnSet = 1;
		}
#line 1747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 340 "parser.y" /* yacc.c:1646  */
    { 
	  	gen_label((yyvsp[-1].y_lab)); 
		currentf->returnSet = 0;
	  }
#line 1756 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 345 "parser.y" /* yacc.c:1646  */
    {
	  	(yyval.y_lab) = gen_jump(BRA, new_label(), "past ELSE");
		gen_label((yyvsp[-2].y_lab));
	  }
#line 1765 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 350 "parser.y" /* yacc.c:1646  */
    { 
	  	gen_label((yyvsp[-1].y_lab)); 
	  }
#line 1773 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 354 "parser.y" /* yacc.c:1646  */
    {
	  	push_break(break_loc);
		(yyval.y_lab) = break_loc;
	  }
#line 1782 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 359 "parser.y" /* yacc.c:1646  */
    {
	  	gen_jump(BRA, (yyvsp[-2].y_lab), "repeat loop");
		gen_label((yyvsp[-1].y_lab));
		pop_break();
		pop_continue();
		currentf->returnSet = 0;
	  }
#line 1794 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 371 "parser.y" /* yacc.c:1646  */
    { (yyval.y_lab) = gen_prefix((yyvsp[-1].y_reg), "IF"); }
#line 1800 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 373 "parser.y" /* yacc.c:1646  */
    { (yyval.y_lab) = -1; }
#line 1806 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 378 "parser.y" /* yacc.c:1646  */
    {
	  	(yyval.y_lab) = gen_label(new_label());
		push_continue((yyval.y_lab));
	  }
#line 1815 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 383 "parser.y" /* yacc.c:1646  */
    {
	  		break_loc = gen_prefix((yyvsp[-1].y_reg), "WHILE loop");
	  		(yyval.y_lab) = (yyvsp[-2].y_lab); 
	  }
#line 1824 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 389 "parser.y" /* yacc.c:1646  */
    {
		(yyval.y_lab) = gen_label(new_label()); /* COND */
	  }
#line 1832 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 393 "parser.y" /* yacc.c:1646  */
    {
		break_loc = gen_prefix((yyvsp[-1].y_reg), "FOR loop"); /* DONE */
		loop_body = gen_jump(BRA, new_label(), "Goto loop body"); /* BODY */
		(yyval.y_lab) = gen_label(new_label());	/* LOOPBACK */
		push_continue((yyval.y_lab));
	  }
#line 1843 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 400 "parser.y" /* yacc.c:1646  */
    {
		gen_jump(BRA, (yyvsp[-5].y_lab), "Goto test condition");
		gen_label(loop_body);
		(yyval.y_lab) = (yyvsp[-2].y_lab);
	  }
#line 1853 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 408 "parser.y" /* yacc.c:1646  */
    {
	  	(yyval.y_lab) = gen_label(new_label());
		push_continue((yyval.y_lab));
	  }
#line 1862 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 418 "parser.y" /* yacc.c:1646  */
    {
	  	(yyval.y_reg) = (yyvsp[0].y_reg); 
		yyerrok; 
	  }
#line 1871 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 423 "parser.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 429 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_ldx((yyvsp[0].y_sym), (yyvsp[0].y_sym)->s_name); }
#line 1883 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 431 "parser.y" /* yacc.c:1646  */
    { 
	  	(yyval.y_reg) = gen_li((yyvsp[0].y_str)); 
	  }
#line 1891 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 435 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = (yyvsp[-1].y_reg); }
#line 1897 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 437 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = MAX_REG; }
#line 1903 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 439 "parser.y" /* yacc.c:1646  */
    { chk_func((yyvsp[-1].y_sym)); argRgn = true; }
#line 1909 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 441 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_call((yyvsp[-4].y_sym), (yyvsp[-1].y_num)); 
		  argRgn = false;
		}
#line 1917 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 445 "parser.y" /* yacc.c:1646  */
    { 
		chk_var((yyvsp[0].y_sym));
		(yyval.y_reg) = assign((yyvsp[0].y_sym), gen_aluc(ADD, sym_reg((yyvsp[0].y_sym)), gen_ldx((yyvsp[0].y_sym)), 1, "Increment"));
	  }
#line 1926 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 450 "parser.y" /* yacc.c:1646  */
    { 
	  	chk_var((yyvsp[0].y_sym));
		(yyval.y_reg) = assign((yyvsp[0].y_sym), gen_aluc(SUB, sym_reg((yyvsp[0].y_sym)), gen_ldx((yyvsp[0].y_sym)), 1, "Decrement"));
	  }
#line 1935 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 455 "parser.y" /* yacc.c:1646  */
    {
	  	(yyval.y_reg) = gen_io(kInput, -1);
	  }
#line 1943 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 459 "parser.y" /* yacc.c:1646  */
    {
	  	(yyval.y_reg) = gen_io(kOutput, (yyvsp[-1].y_reg));
	  }
#line 1951 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 463 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_alu(ADD, -1, (yyvsp[-2].y_reg), (yyvsp[0].y_reg), "+"); }
#line 1957 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 465 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_alu(SUB, -1, (yyvsp[-2].y_reg), (yyvsp[0].y_reg), "-"); }
#line 1963 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 467 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_alu(MULT, -1, (yyvsp[-2].y_reg), (yyvsp[0].y_reg), "*"); }
#line 1969 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 469 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_alu(DIV, -1, (yyvsp[-2].y_reg), (yyvsp[0].y_reg), "/"); }
#line 1975 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 471 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_cmp((yyvsp[-2].y_reg), (yyvsp[0].y_reg), BGT); }
#line 1981 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 473 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_cmp((yyvsp[-2].y_reg), (yyvsp[0].y_reg), BLT); }
#line 1987 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 475 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_cmp((yyvsp[-2].y_reg), (yyvsp[0].y_reg), BGE); }
#line 1993 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 477 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_cmp((yyvsp[-2].y_reg), (yyvsp[0].y_reg), BLE); }
#line 1999 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 479 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_cmp((yyvsp[-2].y_reg), (yyvsp[0].y_reg), BEQ); }
#line 2005 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 481 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_cmp((yyvsp[-2].y_reg), (yyvsp[0].y_reg), BNE); }
#line 2011 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 483 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_alu(AND, -1, (yyvsp[-2].y_reg), (yyvsp[0].y_reg), "&"); }
#line 2017 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 485 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_alu(XOR, -1, (yyvsp[-2].y_reg), (yyvsp[0].y_reg), "^"); }
#line 2023 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 487 "parser.y" /* yacc.c:1646  */
    { (yyval.y_reg) = gen_alu(OR, -1, (yyvsp[-2].y_reg), (yyvsp[0].y_reg), "|"); }
#line 2029 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 489 "parser.y" /* yacc.c:1646  */
    { chk_var((yyvsp[-2].y_sym));
		  (yyval.y_reg) = assign((yyvsp[-2].y_sym), (yyvsp[0].y_reg)); }
#line 2036 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 492 "parser.y" /* yacc.c:1646  */
    { 
	  	chk_var((yyvsp[-2].y_sym)); 
		(yyval.y_reg) = assign((yyvsp[-2].y_sym), gen_alu(ADD, -1, gen_ldx((yyvsp[-2].y_sym)), (yyvsp[0].y_reg), "+=")); 
	  }
#line 2045 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 497 "parser.y" /* yacc.c:1646  */
    { 
	  	chk_var((yyvsp[-2].y_sym)); 
		(yyval.y_reg) = assign((yyvsp[-2].y_sym), gen_alu(SUB, -1, gen_ldx((yyvsp[-2].y_sym)), (yyvsp[0].y_reg), "-="));
	  }
#line 2054 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 502 "parser.y" /* yacc.c:1646  */
    { chk_var((yyvsp[-2].y_sym)); 
		  (yyval.y_reg) = assign((yyvsp[-2].y_sym), gen_alu(MULT, -1, gen_ldx((yyvsp[-2].y_sym)), (yyvsp[0].y_reg), "*="));
		}
#line 2062 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 506 "parser.y" /* yacc.c:1646  */
    { chk_var((yyvsp[-2].y_sym)); 
		  (yyval.y_reg) = assign((yyvsp[-2].y_sym), gen_alu(DIV, -1, gen_ldx((yyvsp[-2].y_sym)), (yyvsp[0].y_reg), "/="));
		}
#line 2070 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 512 "parser.y" /* yacc.c:1646  */
    {
	  	chk_var((yyvsp[0].y_sym));
	  }
#line 2078 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 517 "parser.y" /* yacc.c:1646  */
    { 
	  	int reg;
	  	chk_array((yyvsp[-3].y_sym)); 
		reg = gen_ldx((yyvsp[-3].y_sym), (yyvsp[-3].y_sym)->s_name);
		(yyval.y_sym) = make_dummy(reg, (yyvsp[-1].y_reg));
	  }
#line 2089 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 526 "parser.y" /* yacc.c:1646  */
    { (yyval.y_num) = 0; /* No args */ }
#line 2095 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 532 "parser.y" /* yacc.c:1646  */
    { 
	  	(yyval.y_num) = 1;
		eval_hist[0] = (yyvsp[0].y_reg);
	  }
#line 2104 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 537 "parser.y" /* yacc.c:1646  */
    { 
	  	eval_hist[(yyval.y_num)] = (yyvsp[0].y_reg);
		++(yyval.y_num);
		yyerrok; 
	  }
#line 2114 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 543 "parser.y" /* yacc.c:1646  */
    { (yyval.y_num) = 0; }
#line 2120 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 551 "parser.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2126 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 552 "parser.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2132 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 553 "parser.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2138 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2142 "parser.tab.c" /* yacc.c:1646  */
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
