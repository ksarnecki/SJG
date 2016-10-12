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
