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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    NUM = 258,
    NUMFLOAT = 259,
    ID = 260,
    INTEGER = 261,
    FLOAT = 262,
    SEMICOLON = 263,
    COLON = 264,
    ASSIGNMENT = 265,
    IF = 266,
    WHILE = 267,
    FOR = 268,
    READ = 269,
    PRINT = 270,
    SUM = 271,
    SUB = 272,
    MULT = 273,
    DIV = 274,
    GREATER_THAN = 275,
    LESS_THAN = 276,
    EQUAL_TO = 277,
    PROGRAM = 278,
    P_BEGIN = 279,
    END = 280,
    THEN = 281,
    ENDIF = 282,
    DO = 283,
    ENDW = 284,
    STEP = 285,
    UNTIL = 286,
    ENDFOR = 287,
    LPAREN = 288,
    RPAREN = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 36 "Parser.y" /* yacc.c:1915  */


    int iValue;
    float fValue;
    char *idValue;
    SymbolType sValue;
    Node *node;
    

#line 99 "Parser.h" /* yacc.c:1915  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
