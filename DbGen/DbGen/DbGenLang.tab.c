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
#define YYSTYPE         DBGENSTYPE
/* Substitute the variable and function names.  */
#define yyparse         dbgenparse
#define yylex           dbgenlex
#define yyerror         dbgenerror
#define yydebug         dbgendebug
#define yynerrs         dbgennerrs

#define yylval          dbgenlval
#define yychar          dbgenchar

/* Copy the first part of user declarations.  */
#line 2 "data/DbGenLang.y" /* yacc.c:339  */


#include <string.h>
#include <malloc.h>
#include <stdio.h>

#include "data/Data.h"
#include "DbGen.h"

extern "C" {
  int yyparse(void);
  int yylex(void);
  int yywrap() {
    return 1;
  }
  extern int dbgenlineno;
  extern char* dbgentext;
}

void yyerror(const char *s) {
  printf("%s at line %d", s, dbgenlineno);
  if (dbgentext!=0)
    printf(", near token %s", dbgentext);
  printf("\n");
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

DbFile* fresult = 0;


#line 133 "DbGenLang.tab.c" /* yacc.c:339  */

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
   by #include "DbGenLang.tab.h".  */
#ifndef YY_DBGEN_DBGENLANG_TAB_H_INCLUDED
# define YY_DBGEN_DBGENLANG_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef DBGENDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define DBGENDEBUG 1
#  else
#   define DBGENDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define DBGENDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined DBGENDEBUG */
#if DBGENDEBUG
extern int dbgendebug;
#endif

/* Token type.  */
#ifndef DBGENTOKENTYPE
# define DBGENTOKENTYPE
  enum dbgentokentype
  {
    RECORD = 258,
    ARRAY = 259,
    OF = 260,
    MINUS = 261,
    PLUS = 262,
    NUMBER = 263,
    INT = 264,
    APPDATA = 265,
    STRING = 266,
    METHOD_DECL = 267,
    SPEC = 268,
    BEGIN = 269,
    BEG = 270,
    END = 271,
    ABEG = 272,
    AEND = 273,
    PBEG = 274,
    PEND = 275,
    FILENAME = 276,
    COLON = 277,
    J2JAPICLIENT = 278,
    APIURL = 279,
    UPDATE = 280,
    JAVAAPISERVER = 281,
    JAVASYNC = 282,
    JAVAASYNC = 283,
    PACKAGE = 284,
    DELETE = 285,
    INSERT = 286,
    IMPORT = 287,
    EXEC = 288,
    TEXT = 289,
    QUERY = 290,
    TO = 291,
    USING = 292,
    JOIN = 293,
    ON = 294
  };
#endif

/* Value type.  */
#if ! defined DBGENSTYPE && ! defined DBGENSTYPE_IS_DECLARED
typedef int DBGENSTYPE;
# define DBGENSTYPE_IS_TRIVIAL 1
# define DBGENSTYPE_IS_DECLARED 1
#endif


extern DBGENSTYPE dbgenlval;

int dbgenparse (void);

#endif /* !YY_DBGEN_DBGENLANG_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 232 "DbGenLang.tab.c" /* yacc.c:358  */

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
         || (defined DBGENSTYPE_IS_TRIVIAL && DBGENSTYPE_IS_TRIVIAL)))

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   102

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  39
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  99

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
       2,     2,     2,     2,    42,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    40,
       2,    41,     2,     2,     2,     2,     2,     2,     2,     2,
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

#if DBGENDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    64,    64,    66,    67,    68,    69,    70,    71,    72,
      74,    76,    78,    79,    80,    81,    82,    83,    85,    86,
      88,    89,    90,    91,    93,    94,    96,    98,    99,   100,
     101,   102,   104,   105,   106,   108,   109,   110,   112,   113
};
#endif

#if DBGENDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "RECORD", "ARRAY", "OF", "MINUS", "PLUS",
  "NUMBER", "INT", "APPDATA", "STRING", "METHOD_DECL", "SPEC", "BEGIN",
  "BEG", "END", "ABEG", "AEND", "PBEG", "PEND", "FILENAME", "COLON",
  "J2JAPICLIENT", "APIURL", "UPDATE", "JAVAAPISERVER", "JAVASYNC",
  "JAVAASYNC", "PACKAGE", "DELETE", "INSERT", "IMPORT", "EXEC", "TEXT",
  "QUERY", "TO", "USING", "JOIN", "ON", "';'", "'='", "','", "':'",
  "$accept", "dbfile", "outputfiles", "outputfile", "outputfilekind",
  "apiurl", "inputfile", "package", "filename", "appdata", "imports",
  "import", "elems", "elem", "spec", "non_empty_spec", "joins", "join",
  "args", "select_params", "select_param", YY_NULLPTR
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
      59,    61,    44,    58
};
# endif

#define YYPACT_NINF -55

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-55)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      13,    -3,   -55,   -55,   -55,    16,     4,   -55,     2,    14,
     -55,     8,   -55,   -55,     3,    14,     9,    15,     5,    12,
      17,    18,    19,     3,   -55,    15,     7,    20,   -55,   -55,
      29,    30,    31,    21,   -55,   -55,   -55,    22,   -14,    23,
      23,    23,    37,   -11,   -55,    24,    25,    44,   -55,    -6,
     -20,   -55,   -19,   -18,    23,   -55,    26,    27,   -55,    34,
      48,    23,    48,    48,   -17,   -55,   -55,    46,   -55,    32,
     -55,    33,    35,    48,    47,   -55,   -55,   -55,   -55,   -55,
     -55,   -27,    36,   -55,   -55,    28,    40,    45,    -5,   -55,
     -55,   -16,    38,    42,    49,   -55,    39,    50,   -55
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     7,     8,     9,     0,     0,     4,     0,     0,
       1,     0,     3,     2,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,    19,     0,     0,     0,    16,    14,
       0,     0,     0,     0,    18,    16,    13,     0,     0,    37,
      37,    37,     0,     0,    12,     0,     0,     0,    15,     0,
       0,    35,     0,     0,    37,     5,     0,     0,     6,     0,
       0,     0,     0,     0,     0,    10,    17,    38,    26,     0,
      36,     0,     0,    25,     0,    22,    23,    21,    28,    24,
      39,     0,     0,    20,    27,     0,     0,     0,    34,    31,
      33,     0,    30,     0,     0,    32,     0,     0,    29
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,   -55,    65,   -55,   -55,   -55,    53,    64,   -55,
      51,   -55,   -55,    58,   -55,   -54,   -55,   -55,   -55,   -34,
      41
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    47,    13,    28,    17,    14,
      38,    48,    23,    24,    78,    69,    81,    84,    91,    50,
      51
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      60,    62,    63,    73,    92,    55,    52,    53,    71,    72,
      45,    82,     9,    83,    11,    89,    10,    15,    46,    79,
      64,    46,    61,    61,    61,    61,    93,     1,    19,    90,
       2,     3,     4,    20,    21,    16,     1,    59,    22,     2,
       3,     4,    18,    26,    27,    29,    30,    36,    39,    40,
      41,    31,    32,    33,    37,    42,    54,    49,    56,    57,
      58,    68,    44,    74,    88,    80,    65,    66,    67,    86,
      85,    12,    75,    76,    87,    77,    95,    94,    35,    25,
      97,    34,     0,    96,    98,     0,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70
};

static const yytype_int8 yycheck[] =
{
      20,    20,    20,    20,    20,    16,    40,    41,    62,    63,
      24,    38,    15,    40,    10,    20,     0,    15,    32,    73,
      54,    32,    42,    42,    42,    42,    42,    23,    25,    34,
      26,    27,    28,    30,    31,    21,    23,    43,    35,    26,
      27,    28,    34,    34,    29,    40,    34,    40,    19,    19,
      19,    34,    34,    34,    34,    34,    19,    34,    34,    34,
      16,    13,    40,    17,    19,    18,    40,    40,    34,    41,
      34,     6,    40,    40,    34,    40,    34,    39,    25,    15,
      41,    23,    -1,    34,    34,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    23,    26,    27,    28,    45,    46,    47,    48,    15,
       0,    10,    47,    50,    53,    15,    21,    52,    34,    25,
      30,    31,    35,    56,    57,    52,    34,    29,    51,    40,
      34,    34,    34,    34,    57,    51,    40,    34,    54,    19,
      19,    19,    34,    54,    40,    24,    32,    49,    55,    34,
      63,    64,    63,    63,    19,    16,    34,    34,    16,    43,
      20,    42,    20,    20,    63,    40,    40,    34,    13,    59,
      64,    59,    59,    20,    17,    40,    40,    40,    58,    59,
      18,    60,    38,    40,    61,    34,    41,    34,    19,    20,
      34,    62,    20,    42,    39,    34,    34,    41,    34
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    48,    48,    48,
      49,    50,    51,    52,    53,    54,    54,    55,    56,    56,
      57,    57,    57,    57,    58,    58,    59,    60,    60,    61,
      61,    61,    62,    62,    62,    63,    63,    63,    64,    64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     6,     7,     1,     1,     1,
       3,     2,     3,     3,     3,     2,     0,     3,     2,     1,
       9,     7,     7,     7,     1,     0,     1,     2,     0,    11,
       7,     6,     3,     1,     0,     1,     3,     0,     3,     5
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
#if DBGENDEBUG

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
#else /* !DBGENDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !DBGENDEBUG */


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
#line 64 "data/DbGenLang.y" /* yacc.c:1646  */
    { fresult = new DbFile(xbox<OutputFiles>((yyvsp[-1])), xbox<InputFile>((yyvsp[0])));}
#line 1373 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 66 "data/DbGenLang.y" /* yacc.c:1646  */
    { OutputFiles s = xbox<OutputFiles>((yyvsp[-1])); s.Insert(xbox<OutputFile>((yyvsp[0]))); (yyval) = new Box<OutputFiles>(s);}
#line 1379 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 67 "data/DbGenLang.y" /* yacc.c:1646  */
    { OutputFiles s = OutputFiles(); s.Insert(xbox<OutputFile>((yyvsp[0]))); (yyval) = new Box<OutputFiles>(s);}
#line 1385 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 68 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<OutputFile>(OutputFile(xbox<OutputFileKind>((yyvsp[-5])),xboxs((yyvsp[-3])),xboxs((yyvsp[-2])), xbox<StringArray>((yyvsp[-1]))));  }
#line 1391 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 69 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<OutputFile>(OutputFile(OutputFileKind::createJ2jApiClient(xbox<AnsiString>((yyvsp[-1]))),xboxs((yyvsp[-4])),xboxs((yyvsp[-3])), xbox<StringArray>((yyvsp[-2]))));  }
#line 1397 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 70 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<OutputFileKind>(OutputFileKind::createJavaApiProcessor()); }
#line 1403 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 71 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<OutputFileKind>(OutputFileKind::createJavaSync()); }
#line 1409 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 72 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<OutputFileKind>(OutputFileKind::createJavaAsync()); }
#line 1415 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 74 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<AnsiString>(xboxs((yyvsp[-1]))); }
#line 1421 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 76 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<InputFile>(InputFile(xboxs((yyvsp[-1])), xbox<Elems>((yyvsp[0])))); }
#line 1427 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 78 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1433 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 79 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1439 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 80 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1445 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 81 "data/DbGenLang.y" /* yacc.c:1646  */
    { StringArray arr = xbox<StringArray>((yyvsp[-1])); arr.Insert(xbox<AnsiString>((yyvsp[0]))); (yyval) = new Box<StringArray>(arr); }
#line 1451 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 82 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<StringArray>(StringArray());}
#line 1457 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 83 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<AnsiString>("import " + xboxs((yyvsp[-1])) + ";");}
#line 1463 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 85 "data/DbGenLang.y" /* yacc.c:1646  */
    { Elems m = xbox<Elems>((yyvsp[-1])); m.Insert(xbox<Elem>((yyvsp[0]))); (yyval) = new Box<Elems>(m); }
#line 1469 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 86 "data/DbGenLang.y" /* yacc.c:1646  */
    { Elems m; m.Insert(xbox<Elem>((yyvsp[0]))); (yyval) = new Box<Elems>(m); }
#line 1475 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 88 "data/DbGenLang.y" /* yacc.c:1646  */
    { Elem e = Elem::createSelect( Select( xboxs((yyvsp[-7])), xboxs((yyvsp[-6])), xbox<SelectParams>((yyvsp[-4])), xbox<AnsiString>((yyvsp[-2])), xbox<Joins>((yyvsp[-1])) ) ); (yyval) = new Box<Elem>( e ); }
#line 1481 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 89 "data/DbGenLang.y" /* yacc.c:1646  */
    { Elem e = Elem::createInsert( Insert(xboxs((yyvsp[-5])), xbox<SelectParams>((yyvsp[-3])), xbox<AnsiString>((yyvsp[-1])))); (yyval) = new Box<Elem>( e ); }
#line 1487 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 90 "data/DbGenLang.y" /* yacc.c:1646  */
    { Elem e = Elem::createUpdate( Update(xboxs((yyvsp[-5])), xbox<SelectParams>((yyvsp[-3])), xbox<AnsiString>((yyvsp[-1])))); (yyval) = new Box<Elem>( e ); }
#line 1493 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 91 "data/DbGenLang.y" /* yacc.c:1646  */
    { Elem e = Elem::createDelete( Delete(xboxs((yyvsp[-5])), xbox<SelectParams>((yyvsp[-3])), xbox<AnsiString>((yyvsp[-1])))); (yyval) = new Box<Elem>( e ); }
#line 1499 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 93 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1505 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 94 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<AnsiString>(""); }
#line 1511 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 96 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<AnsiString>(xboxs((yyvsp[0]))); }
#line 1517 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 98 "data/DbGenLang.y" /* yacc.c:1646  */
    { Joins js = xbox<Joins> ((yyvsp[-1])); js.Insert(xbox<Join>((yyvsp[0]))); (yyval) = new Box<Joins>(js);}
#line 1523 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 99 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<Joins>(Joins());}
#line 1529 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 100 "data/DbGenLang.y" /* yacc.c:1646  */
    { Join j = Join(xboxs((yyvsp[-9])),xboxs((yyvsp[-7])),xbox<StringArray>((yyvsp[-5])),xboxs((yyvsp[-2])),xboxs((yyvsp[0]))); (yyval) = new Box<Join>( j ); }
#line 1535 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 101 "data/DbGenLang.y" /* yacc.c:1646  */
    { Join j = Join(xboxs((yyvsp[-5])),xboxs((yyvsp[-3])),xbox<StringArray>((yyvsp[-1])),"",""); (yyval) = new Box<Join>( j ); }
#line 1541 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 102 "data/DbGenLang.y" /* yacc.c:1646  */
    { Join j = Join(xboxs((yyvsp[-4])),xboxs((yyvsp[-2])), StringArray(),"",""); (yyval) = new Box<Join>( j ); }
#line 1547 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 104 "data/DbGenLang.y" /* yacc.c:1646  */
    { StringArray arr = xbox<StringArray>((yyvsp[-2])); arr.Insert(xboxs((yyvsp[0]))); (yyval) = new Box<StringArray>(arr);}
#line 1553 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 105 "data/DbGenLang.y" /* yacc.c:1646  */
    { StringArray arr; arr.Insert(xboxs((yyvsp[0]))); (yyval) = new Box<StringArray>(arr);}
#line 1559 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 106 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<StringArray>(StringArray()); }
#line 1565 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 108 "data/DbGenLang.y" /* yacc.c:1646  */
    { SelectParams m; m.Insert(xbox<SelectParam>((yyvsp[0]))); (yyval) = new Box<SelectParams>(m); }
#line 1571 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 109 "data/DbGenLang.y" /* yacc.c:1646  */
    { SelectParams m = xbox<SelectParams>((yyvsp[-2])); m.Insert(xbox<SelectParam>((yyvsp[0]))); (yyval) = new Box<SelectParams>(m); }
#line 1577 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 110 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<SelectParams>(SelectParams());}
#line 1583 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 112 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<SelectParam>(SelectParam(xboxs((yyvsp[-2])), SelectParamType::createPlain(xboxs((yyvsp[0]))) )); }
#line 1589 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 113 "data/DbGenLang.y" /* yacc.c:1646  */
    { (yyval) = new Box<SelectParam>(SelectParam(xboxs((yyvsp[-4])), SelectParamType::createArray(xboxs((yyvsp[-2]))) )); }
#line 1595 "DbGenLang.tab.c" /* yacc.c:1646  */
    break;


#line 1599 "DbGenLang.tab.c" /* yacc.c:1646  */
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
#line 115 "data/DbGenLang.y" /* yacc.c:1906  */


int yylex(void);
void yyerror(const char *);

#include <stdio.h>
#include "lex.dbgen.c"

DbFile dbgen_yacc_parse(LineStream& stream) {
  AnsiString input = "";
  stream.next();
  while(!stream.isEof()) {
    AnsiString line = stream.getLine() + "\r\n";
    input += line;
    stream.next();
  }
  dbgen_scan_string(input.c_str());
  dbgenparse(); 
  if(fresult!=0) {
    DbFile data = *fresult;
    return data;
  } else 
    throw Exception("Parser error...");
}
