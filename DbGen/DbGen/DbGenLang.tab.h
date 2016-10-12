/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
