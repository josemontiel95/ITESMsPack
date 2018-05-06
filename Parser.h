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
    REPEAT = 268,
    FOR = 269,
    ELSE = 270,
    READ = 271,
    PRINT = 272,
    SUM = 273,
    SUB = 274,
    MULT = 275,
    DIV = 276,
    GREATER_THAN = 277,
    LESS_THAN = 278,
    EQUAL_TO = 279,
    PROGRAM = 280,
    P_BEGIN = 281,
    END = 282,
    THEN = 283,
    ENDIF = 284,
    DO = 285,
    ENDW = 286,
    STEP = 287,
    UNTIL = 288,
    ENDFOR = 289,
    LPAREN = 290,
    RPAREN = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 28 "Parser.y" /* yacc.c:1915  */


    int iValue;
    float fValue;
    char *idValue;
    SymbolType sValue;
    Node *node;
    

#line 101 "Parser.h" /* yacc.c:1915  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
