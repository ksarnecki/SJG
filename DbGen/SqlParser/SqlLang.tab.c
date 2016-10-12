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

/* Substitute the type names.  */
#define YYSTYPE         SQLSTYPE
/* Substitute the variable and function names.  */
#define yyparse         sqlparse
#define yylex           sqllex
#define yyerror         sqlerror
#define yydebug         sqldebug
#define yynerrs         sqlnerrs

#define yylval          sqllval
#define yychar          sqlchar

/* Copy the first part of user declarations.  */
#line 2 "data/SqlLang.y" /* yacc.c:339  */


#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include "SqlParser.h"
#include "data/SqlParserData.h"

extern "C" {
  int yyparse(void);
  int yylex(void);
  extern int sqllineno;
  extern char* sqltext;
}

void yyerror(const char *s) {
  AnsiString ret = AnsiString(s) + " at line " + AnsiString(sqllineno);
  if (sqltext!=0)
    ret += ", near token " + AnsiString(sqltext);
  throw Exception(ret);
}

template <class T>
class Box {
  T v;
public:
  Box(const T& _v) : v(_v) {
  }
  virtual const T& get() const {
    return v;
  }
  virtual ~Box() {
  }
};

template <class T>
static T xbox(int v) {
  Box<T>* b = (Box<T>*) v;
  T t = b->get();
  delete b;
  return t;
}

static AnsiString xboxs(int v) {
  char* s = (char*) v;
  AnsiString ret(s);
  free(s);
  return ret;
}

int sqlResult = 0;


#line 130 "SqlLang.tab.c" /* yacc.c:339  */

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
   by #include "SqlLang.tab.h".  */
#ifndef YY_SQL_SQLLANG_TAB_H_INCLUDED
# define YY_SQL_SQLLANG_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef SQLDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define SQLDEBUG 1
#  else
#   define SQLDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define SQLDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined SQLDEBUG */
#if SQLDEBUG
extern int sqldebug;
#endif

/* Token type.  */
#ifndef SQLTOKENTYPE
# define SQLTOKENTYPE
  enum sqltokentype
  {
    SELECT = 258,
    FROM = 259,
    BEG = 260,
    END = 261,
    ABEG = 262,
    AEND = 263,
    PBEG = 264,
    PEND = 265,
    TEXT = 266,
    STRING = 267,
    NUMBER = 268,
    WHERE = 269,
    ORDER = 270,
    LIMIT = 271,
    DESC = 272,
    ASC = 273,
    AS = 274,
    LIKE = 275,
    AND = 276,
    OR = 277,
    SPEC = 278,
    CASE = 279,
    WHEN = 280,
    THEN = 281,
    IN = 282,
    ELSE = 283,
    MAX = 284,
    MIN = 285,
    COUNT = 286,
    GROUP = 287,
    EXISTS = 288,
    VALUES = 289,
    INTO = 290,
    INSERT = 291,
    UPDATE = 292,
    DELETE = 293,
    SET = 294,
    NOT = 295,
    EGR = 296,
    ESM = 297,
    NEQ = 298
  };
#endif

/* Value type.  */
#if ! defined SQLSTYPE && ! defined SQLSTYPE_IS_DECLARED
typedef int SQLSTYPE;
# define SQLSTYPE_IS_TRIVIAL 1
# define SQLSTYPE_IS_DECLARED 1
#endif


extern SQLSTYPE sqllval;

int sqlparse (void);

#endif /* !YY_SQL_SQLLANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 233 "SqlLang.tab.c" /* yacc.c:358  */

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
         || (defined SQLSTYPE_IS_TRIVIAL && SQLSTYPE_IS_TRIVIAL)))

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
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   228

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  137

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

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
       2,     2,    49,     2,    47,     2,    48,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      46,    44,    45,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if SQLDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    68,    68,    69,    70,    71,    74,    77,    78,    81,
      83,    84,    86,    89,    92,    93,    99,   101,   103,   105,
     107,   109,   111,   112,   113,   119,   120,   121,   123,   124,
     125,   128,   129,   131,   138,   139,   140,   143,   147,   151,
     157,   161,   169,   173,   177,   181,   185,   189,   193,   197,
     201,   205,   209,   216,   220,   225,   231,   238,   245,   250,
     256,   262,   268,   294,   298,   302,   306,   310,   314,   318,
     324,   328
};
#endif

#if SQLDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SELECT", "FROM", "BEG", "END", "ABEG",
  "AEND", "PBEG", "PEND", "TEXT", "STRING", "NUMBER", "WHERE", "ORDER",
  "LIMIT", "DESC", "ASC", "AS", "LIKE", "AND", "OR", "SPEC", "CASE",
  "WHEN", "THEN", "IN", "ELSE", "MAX", "MIN", "COUNT", "GROUP", "EXISTS",
  "VALUES", "INTO", "INSERT", "UPDATE", "DELETE", "SET", "NOT", "EGR",
  "ESM", "NEQ", "'='", "'>'", "'<'", "','", "'.'", "'*'", "$accept", "sql",
  "selectQuery", "insertQuery", "updateQuery", "sets", "set",
  "deleteQuery", "fields", "field", "agrFun", "charaters", "tables",
  "table", "condition", "operation", "binaryOperator", "unaryOperator",
  "whenConditions", "whenCondition", "orders", "sort", "limit", "groups", YY_NULLPTR
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
     295,   296,   297,   298,    61,    62,    60,    44,    46,    42
};
# endif

#define YYPACT_NINF -66

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-66)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,   122,   -32,    81,     9,    17,   -66,   -66,   -66,   -66,
      21,   -25,   -66,   -66,   -66,   -66,   -66,   -66,   -66,     3,
     -66,    26,    10,    81,    21,    66,    33,    81,   -66,    68,
      75,    81,   122,   131,    82,    62,    87,   -66,    94,   122,
      20,    84,    88,    89,    23,   -66,   -66,    99,     4,   -66,
     122,   101,    96,   -66,   -66,    72,    90,   122,   102,   102,
     106,   114,    81,    97,   -66,   -66,     5,   122,   115,   122,
      51,   103,   118,   -66,   -66,   182,    90,   -66,    93,   -66,
     -66,   -66,   -66,   -66,   122,    -8,    98,     8,   -66,   -66,
     145,    90,    48,   -66,    21,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   -66,    90,   182,   -66,   -66,   -66,
     -66,   -66,   122,   104,   128,   -66,   -66,   155,    90,   -66,
     136,   182,   -66,   122,    32,   122,    90,     0,   -66,   -66,
     122,   -66,    18,   182,   -66,   -66,   -66
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     3,     4,     5,
       0,    28,    30,    29,    21,    25,    26,    27,    24,     0,
      15,     0,    20,     0,     0,    36,     0,     0,     1,     0,
       0,     0,     0,     0,     0,     0,     0,    35,     0,     0,
      37,    37,     0,    18,    37,    32,    14,    24,     0,    19,
       0,     0,     0,    34,    11,     0,     0,     0,    68,    68,
       0,     0,     0,    62,    23,    22,     0,     0,     0,     0,
       0,    58,     0,    53,    39,    38,     0,    10,     0,     9,
      13,    16,    17,    31,     0,    65,     0,     0,    33,    12,
       0,     0,     0,    57,     0,    44,    43,    42,    46,    49,
      50,    51,    45,    47,    48,     0,    52,    67,    66,    61,
      63,    64,     0,    71,     0,     8,    40,     0,     0,    56,
       0,    41,    60,     0,    68,     0,     0,     0,    54,    70,
       0,     6,     0,    59,    55,    69,     7
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -66,     1,   -66,   -66,   -66,   -66,    91,   -66,   -31,    -1,
     -66,   -66,   -66,   -15,   -11,   -65,   -66,   -66,   -66,    46,
     -66,   -66,   -55,   -66
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    29,     6,     7,     8,    40,    54,     9,    19,    74,
      21,    22,    44,    26,    58,    75,   105,    76,    92,    93,
      85,   113,    79,   124
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      20,     5,    48,    23,    80,    90,   134,    31,    35,   110,
     111,   106,    41,    27,    65,    86,    45,    28,   115,    66,
      95,    96,    97,    30,     1,    36,   117,    98,   136,    34,
      59,    46,    20,    63,    56,    33,    87,    56,    55,   112,
     121,    99,   100,   101,   102,   103,   104,    83,    78,    20,
      32,    32,    32,   127,     1,    32,    55,     2,     3,     4,
      70,   133,    11,    12,    13,    32,    20,    57,    89,   131,
      62,    50,    39,    91,    14,    71,   118,    37,    42,   130,
      15,    16,    17,   109,    72,    38,    43,     2,     3,     4,
      24,    73,    25,    49,   132,   120,    51,    52,    56,    70,
      18,    11,    12,    13,   107,    53,   108,    60,    61,    64,
      67,   122,    84,    14,    71,    68,    69,    81,    78,    15,
      16,    17,   129,    72,    20,    82,    88,    94,    91,   135,
      73,    10,   114,    11,    12,    13,   123,   125,   119,    18,
      10,     0,    11,    12,    13,    14,   128,     0,    77,     0,
       0,    15,    16,    17,    14,   116,     0,     0,     0,     0,
      15,    16,    17,     0,     0,    95,    96,    97,     0,     0,
       0,    18,    98,     0,     0,    95,    96,    97,     0,     0,
      47,   126,    98,     0,     0,     0,    99,   100,   101,   102,
     103,   104,     0,     0,     0,     0,    99,   100,   101,   102,
     103,   104,    95,    96,    97,     0,     0,     0,     0,    98,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,   100,   101,   102,   103,   104
};

static const yytype_int16 yycheck[] =
{
       1,     0,    33,    35,    59,    70,     6,     4,    23,    17,
      18,    76,    27,     4,    10,    10,    31,     0,    10,    50,
      20,    21,    22,    48,     3,    24,    91,    27,    10,    19,
      41,    32,    33,    44,    14,     9,    67,    14,    39,    47,
     105,    41,    42,    43,    44,    45,    46,    62,    16,    50,
      47,    47,    47,   118,     3,    47,    57,    36,    37,    38,
       9,   126,    11,    12,    13,    47,    67,    47,    69,   124,
      47,     9,    39,    25,    23,    24,    28,    11,    10,    47,
      29,    30,    31,    84,    33,    19,    11,    36,    37,    38,
       9,    40,    11,    11,   125,    94,    34,    10,    14,     9,
      49,    11,    12,    13,    11,    11,    13,    19,    19,    10,
       9,   112,    15,    23,    24,    19,    44,    11,    16,    29,
      30,    31,   123,    33,   125,    11,    11,     9,    25,   130,
      40,     9,    34,    11,    12,    13,    32,     9,    92,    49,
       9,    -1,    11,    12,    13,    23,    10,    -1,    57,    -1,
      -1,    29,    30,    31,    23,    10,    -1,    -1,    -1,    -1,
      29,    30,    31,    -1,    -1,    20,    21,    22,    -1,    -1,
      -1,    49,    27,    -1,    -1,    20,    21,    22,    -1,    -1,
      49,    26,    27,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    20,    21,    22,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    36,    37,    38,    51,    52,    53,    54,    57,
       9,    11,    12,    13,    23,    29,    30,    31,    49,    58,
      59,    60,    61,    35,     9,    11,    63,     4,     0,    51,
      48,     4,    47,     9,    19,    63,    51,    11,    19,    39,
      55,    63,    10,    11,    62,    63,    59,    49,    58,    11,
       9,    34,    10,    11,    56,    59,    14,    47,    64,    64,
      19,    19,    47,    64,    10,    10,    58,     9,    19,    44,
       9,    24,    33,    40,    59,    65,    67,    56,    16,    72,
      72,    11,    11,    63,    15,    70,    10,    58,    11,    59,
      65,    25,    68,    69,     9,    20,    21,    22,    27,    41,
      42,    43,    44,    45,    46,    66,    65,    11,    13,    59,
      17,    18,    47,    71,    34,    10,    10,    65,    28,    69,
      51,    65,    59,    32,    73,     9,    26,    65,    10,    59,
      47,    72,    58,    65,     6,    59,    10
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    51,    51,    51,    52,    53,    53,    54,
      55,    55,    56,    57,    58,    58,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    60,    60,    60,    61,    61,
      61,    62,    62,    63,    63,    63,    63,    64,    64,    65,
      65,    65,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    65,    67,    65,    65,    68,    68,    68,    69,
      70,    70,    70,    71,    71,    71,    72,    72,    72,    73,
      73,    73
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     9,    10,     7,     5,
       3,     2,     3,     5,     3,     1,     5,     5,     3,     3,
       1,     1,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     5,     3,     2,     1,     0,     2,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     4,     5,     2,     1,     0,     4,
       3,     2,     0,     1,     1,     0,     2,     2,     0,     3,
       2,     0
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
#if SQLDEBUG

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
#else /* !SQLDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !SQLDEBUG */


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
#line 68 "data/SqlLang.y" /* yacc.c:1646  */
    { sqlResult = new Box<Sql>(Sql::createSelectQuery(xbox<SelectQuery>((yyvsp[0])))); }
#line 1422 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 69 "data/SqlLang.y" /* yacc.c:1646  */
    { sqlResult = new Box<Sql>(Sql::createInsertQuery(xbox<InsertQuery>((yyvsp[0])))); }
#line 1428 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 70 "data/SqlLang.y" /* yacc.c:1646  */
    { sqlResult = new Box<Sql>(Sql::createUpdateQuery(xbox<UpdateQuery>((yyvsp[0])))); }
#line 1434 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 71 "data/SqlLang.y" /* yacc.c:1646  */
    { sqlResult = new Box<Sql>(Sql::createDeleteQuery(xbox<DeleteQuery>((yyvsp[0])))); }
#line 1440 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 74 "data/SqlLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<SelectQuery>(SelectQuery(xbox<Fields>((yyvsp[-7])), xbox<Tables>((yyvsp[-5])), xbox<Operation>((yyvsp[-4])), xbox<Orders>((yyvsp[-3])), xbox<Sort>((yyvsp[-2])), xbox<Groups>((yyvsp[-1])), xbox<Limit>((yyvsp[0])))); }
#line 1446 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 77 "data/SqlLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<InsertQuery>(InsertQuery(xbox<Table>((yyvsp[-7])), xbox<Fields>((yyvsp[-5])), xbox<Fields>((yyvsp[-1]))));}
#line 1452 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 78 "data/SqlLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<InsertQuery>(InsertQuery(xbox<Table>((yyvsp[-4])), Fields(), xbox<Fields>((yyvsp[0]))));}
#line 1458 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 81 "data/SqlLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<UpdateQuery>(UpdateQuery(xbox<Table>((yyvsp[-3])), xbox<Sets>((yyvsp[-2])),  xbox<Operation>((yyvsp[-1])), xbox<Limit>((yyvsp[0]))));}
#line 1464 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 83 "data/SqlLang.y" /* yacc.c:1646  */
    { Sets ss = xbox<Sets>((yyvsp[-2])); ss.Insert(xbox<Set>((yyvsp[0]))); (yyval) = new Box<Sets>(ss); }
#line 1470 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 84 "data/SqlLang.y" /* yacc.c:1646  */
    { Sets ss = Sets(); ss.Insert(xbox<Set>((yyvsp[0]))); (yyval) = new Box<Sets>(ss); }
#line 1476 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 86 "data/SqlLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<Set>(Set(xbox<Field>((yyvsp[-2])), xbox<Field>((yyvsp[0])))); }
#line 1482 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 89 "data/SqlLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<DeleteQuery>(DeleteQuery(xbox<Table>((yyvsp[-3])),  xbox<Operation>((yyvsp[-2])), xbox<Limit>((yyvsp[-1]))));}
#line 1488 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 92 "data/SqlLang.y" /* yacc.c:1646  */
    {Fields fs = xbox<Fields>((yyvsp[-2])); fs.Insert(xbox<Field>((yyvsp[0]))); (yyval) = new Box<Fields>(fs); }
#line 1494 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 93 "data/SqlLang.y" /* yacc.c:1646  */
    { Fields fs = Fields(); fs.Insert(xbox<Field>((yyvsp[0]))); (yyval) = new Box<Fields>(fs); }
#line 1500 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 99 "data/SqlLang.y" /* yacc.c:1646  */
    {Field f = Field(xboxs((yyvsp[0])), FieldKind::createQuery(SqlPtr::createValue(xbox<Sql>((yyvsp[-3]))))); (yyval) = new Box<Field>(f); }
#line 1506 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 101 "data/SqlLang.y" /* yacc.c:1646  */
    {Field f = Field(xboxs((yyvsp[-1])), FieldKind::createBasicField(BasicField(xboxs((yyvsp[-4])), xboxs((yyvsp[-2]))))); (yyval) = new Box<Field>(f); }
#line 1512 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 103 "data/SqlLang.y" /* yacc.c:1646  */
    { AnsiString str1 = xboxs((yyvsp[-2])); AnsiString str2 = xboxs((yyvsp[0])); Field f = Field(str1 + "." + str2, FieldKind::createBasicField(BasicField(str1, str2))); (yyval) = new Box<Field>(f); }
#line 1518 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 105 "data/SqlLang.y" /* yacc.c:1646  */
    {Field f = Field(xboxs((yyvsp[0])), FieldKind::createBasicField(BasicField(xboxs((yyvsp[-2])), ""))); (yyval) = new Box<Field>(f); }
#line 1524 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 107 "data/SqlLang.y" /* yacc.c:1646  */
    { AnsiString str1 = xboxs((yyvsp[0])); Field f = Field(str1, FieldKind::createBasicField(BasicField(str1, ""))); (yyval) = new Box<Field>(f); }
#line 1530 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 109 "data/SqlLang.y" /* yacc.c:1646  */
    { AnsiString str1 = xboxs((yyvsp[0])); Field f = Field(str1, FieldKind::createSpecialField(str1)); (yyval) = new Box<Field>(f); }
#line 1536 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 111 "data/SqlLang.y" /* yacc.c:1646  */
    { Field f = Field("todo", FieldKind::createAgrField(AgrField(xbox<AgrFieldKind>((yyvsp[-3])), "todo AgrField"))); (yyval) = new Box<Field>(f); }
#line 1542 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 112 "data/SqlLang.y" /* yacc.c:1646  */
    { Field f = Field("todo", FieldKind::createAgrField(AgrField(xbox<AgrFieldKind>((yyvsp[-3])), "todo AgrField"))); (yyval) = new Box<Field>(f); }
#line 1548 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 113 "data/SqlLang.y" /* yacc.c:1646  */
    {
  AnsiString str1 = "*"; 
  Field f = Field(str1, FieldKind::createAllField()); 
  (yyval) = new Box<Field>(f);
  }
#line 1558 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 119 "data/SqlLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<AgrFieldKind>(AgrFieldKind::createMax()); }
#line 1564 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 120 "data/SqlLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<AgrFieldKind>(AgrFieldKind::createMin()); }
#line 1570 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 121 "data/SqlLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<AgrFieldKind>(AgrFieldKind::createCount()); }
#line 1576 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 128 "data/SqlLang.y" /* yacc.c:1646  */
    { Tables ts = xbox<Tables>((yyvsp[-2])); ts.Insert(xbox<Table>((yyvsp[0]))); (yyval) = new Box<Tables>(ts); }
#line 1582 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 129 "data/SqlLang.y" /* yacc.c:1646  */
    { Tables ts = Tables();  ts.Insert(xbox<Table>((yyvsp[0]))); (yyval) = new Box<Tables>(ts); }
#line 1588 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 131 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  Sql sql = xbox<Sql> ((yyvsp[-3]));
  AnsiString as = xboxs((yyvsp[0]));
  Table t = Table(TableKind::createQuery(SqlPtr::createValue(sql)), as); 
  (yyval) = new Box<Table>(t);
}
#line 1599 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 138 "data/SqlLang.y" /* yacc.c:1646  */
    { Table t = Table(TableKind::createBasic(xboxs((yyvsp[-2]))), xboxs((yyvsp[0]))); (yyval) = new Box<Table>(t); }
#line 1605 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 139 "data/SqlLang.y" /* yacc.c:1646  */
    { Table t = Table(TableKind::createBasic(xboxs((yyvsp[-1]))), xboxs((yyvsp[0]))); (yyval) = new Box<Table>(t); }
#line 1611 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 140 "data/SqlLang.y" /* yacc.c:1646  */
    { Table t = Table(TableKind::createBasic(xboxs((yyvsp[0]))), ""); (yyval) = new Box<Table>(t); }
#line 1617 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 143 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  (yyval) = new Box<Operation>(Operation::createEmpty());
}
#line 1625 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 147 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  (yyval) = (yyvsp[0]);
}
#line 1633 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 151 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  Field f = xbox<Field> ((yyvsp[0]));
  Operation o = Operation::createField(f);
  (yyval) = new Box<Operation>(o); 
}
#line 1643 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 157 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  (yyval) = (yyvsp[-1]);
}
#line 1651 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 161 "data/SqlLang.y" /* yacc.c:1646  */
    {
  Operation left = xbox<Operation>((yyvsp[-2])); 
  Operation right = xbox<Operation>((yyvsp[0])); 
  BinaryOperator bop = xbox<BinaryOperator>((yyvsp[-1]));
  BinaryOperation u = BinaryOperation(OperationPtr::createValue(left), OperationPtr::createValue(right), bop);
  (yyval) = new Box<Operation>(Operation::createBinaryOperation(u)); 
}
#line 1663 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 169 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<BinaryOperator>(BinaryOperator::createOr());
}
#line 1671 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 173 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<BinaryOperator>(BinaryOperator::createAnd());
}
#line 1679 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 177 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<BinaryOperator>(BinaryOperator::createLike());
}
#line 1687 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 181 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<BinaryOperator>(BinaryOperator::createEqual());
}
#line 1695 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 185 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<BinaryOperator>(BinaryOperator::createIn());
}
#line 1703 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 189 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<BinaryOperator>(BinaryOperator::createGreater());
}
#line 1711 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 193 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<BinaryOperator>(BinaryOperator::createSmaller());
}
#line 1719 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 197 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<BinaryOperator>(BinaryOperator::createGreaterOrEqual());
}
#line 1727 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 201 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<BinaryOperator>(BinaryOperator::createSmallerOrEqual());
}
#line 1735 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 205 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<BinaryOperator>(BinaryOperator::createNoEqual());
}
#line 1743 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 209 "data/SqlLang.y" /* yacc.c:1646  */
    {
  Operation o = xbox<Operation>((yyvsp[0]));
  UnaryOperator uop = xbox<UnaryOperator> ((yyvsp[-1]));
  UnaryOperation u = UnaryOperation(OperationPtr::createValue(o), uop);
  (yyval) = new Box<Operation>(Operation::createUnaryOperation(u)); 
}
#line 1754 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 216 "data/SqlLang.y" /* yacc.c:1646  */
    {
  (yyval) = new Box<UnaryOperator> (UnaryOperator::createNot());
}
#line 1762 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 220 "data/SqlLang.y" /* yacc.c:1646  */
    {
  Sql sql = xbox<Sql>((yyvsp[-1]));
  (yyval) = new Box<Operation>(Operation::createExistsOperation(sql));
}
#line 1771 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 225 "data/SqlLang.y" /* yacc.c:1646  */
    {
  WhenOperations cases = xbox<WhenOperations>((yyvsp[-3]));
  Operation elseStmnt = xbox<Operation>((yyvsp[-1]));
  (yyval) = new Box<Operation>(Operation::createCaseOperation(CaseOperation(cases, OperationPtr::createValue(elseStmnt))));
}
#line 1781 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 231 "data/SqlLang.y" /* yacc.c:1646  */
    {
  WhenOperation wo = xbox<WhenOperation>((yyvsp[0]));
  WhenOperations os = xbox<WhenOperations>((yyvsp[-1]));
  os.Insert(wo); 
  (yyval) = new Box<WhenOperations>(os); 
}
#line 1792 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 238 "data/SqlLang.y" /* yacc.c:1646  */
    {
  WhenOperation wo = xbox<WhenOperation>((yyvsp[0]));
  WhenOperations os = WhenOperations();  
  os.Insert(wo); 
  (yyval) = new Box<WhenOperations>(os); 
}
#line 1803 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 245 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  WhenOperations os = WhenOperations();
  (yyval) = new Box<WhenOperations>(os);
}
#line 1812 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 250 "data/SqlLang.y" /* yacc.c:1646  */
    {
  Operation condition = xbox<Operation>((yyvsp[-2])); 
  Operation stmnt = xbox<Operation>((yyvsp[0]));
  (yyval) = new Box<WhenOperation>(WhenOperation(OperationPtr::createValue(condition), OperationPtr::createValue(stmnt))); 
}
#line 1822 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 256 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  Orders os = xbox<Orders>((yyvsp[-2])); 
  os.Insert(xbox<Field>((yyvsp[0]))); 
  (yyval) = new Box<Orders>(os);
}
#line 1832 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 262 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  Orders os = Orders();
  os.Insert(xbox<Field>((yyvsp[0])));
  (yyval) = new Box<Orders>(os); 
}
#line 1842 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 268 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  Orders os = Orders();
  (yyval) = new Box<Orders>(os);
}
#line 1851 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 294 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  (yyval) = new Box<Sort>(Sort::createDesc());
}
#line 1859 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 298 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  (yyval) = new Box<Sort>(Sort::createAsc());
}
#line 1867 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 302 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  (yyval) = new Box<Sort>(Sort::createEmpty());
}
#line 1875 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 306 "data/SqlLang.y" /* yacc.c:1646  */
    {
 (yyval) = new Box<Limit>(Limit::createValue(xboxs((yyvsp[0]))));
}
#line 1883 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 310 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  (yyval) = new Box<Limit>(Limit::createValue(xboxs((yyvsp[0]))));
}
#line 1891 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 314 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  (yyval) = new Box<Limit>(Limit::createEmpty());
}
#line 1899 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 318 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  Groups gs = xbox<Groups>((yyvsp[-2])); 
  gs.Insert(xbox<Field>((yyvsp[0]))); 
  (yyval) = new Box<Groups>(gs); 
}
#line 1909 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 324 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  Groups gs = Groups();  gs.Insert(xbox<Field>((yyvsp[0]))); (yyval) = new Box<Groups>(gs);
}
#line 1917 "SqlLang.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 328 "data/SqlLang.y" /* yacc.c:1646  */
    { 
  Groups gs = Groups(); (yyval) = new Box<Groups>(gs); 
}
#line 1925 "SqlLang.tab.c" /* yacc.c:1646  */
    break;


#line 1929 "SqlLang.tab.c" /* yacc.c:1646  */
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
#line 332 "data/SqlLang.y" /* yacc.c:1906  */


int yylex(void);
void yyerror(const char *);

#include <stdio.h>
#include "lex.sql.c"

Sql sql_yacc_parse(LineStream& stream) {
  AnsiString input = "";
  stream.next();
  while(!stream.isEof()) {
    AnsiString line = stream.getLine() + "\r\n";
    input += line;
    stream.next();
  }
  sql_scan_string(input.c_str());
  sqlparse(); 
  if(sqlResult!=0) {
    Sql data = xbox<Sql>(sqlResult);
    return data;
  } else 
    throw Exception("Parser error...");
}
