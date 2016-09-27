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
#line 36 "c-.y" /* yacc.c:1915  */

    Token token;
    TreeNode *treeNode;
    DeclType declType;
    char *cstring;

#line 107 "c-.tab.h" /* yacc.c:1915  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_TAB_H_INCLUDED  */
