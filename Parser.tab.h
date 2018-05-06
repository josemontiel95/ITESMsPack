/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     NUMFLOAT = 259,
     ID = 260,
     INTEGER = 261,
     FLOAT = 262,
     SEMICOLON = 263,
     COLON = 264,
     ASIGN = 265,
     IF = 266,
     WHILE = 267,
     REPEAT = 268,
     ELSE = 269,
     READ = 270,
     PRINT = 271,
     SUM = 272,
     REST = 273,
     MULT = 274,
     DIV = 275,
     MAYORQUE = 276,
     MENORQUE = 277,
     IGUALA = 278,
     PROGRAM = 279,
     P_BEGIN = 280,
     END = 281,
     THEN = 282,
     ENDIF = 283,
     DO = 284,
     ENDW = 285,
     STEP = 286,
     UNTIL = 287,
     LPAREN = 288,
     RPAREN = 289
   };
#endif
/* Tokens.  */
#define NUM 258
#define NUMFLOAT 259
#define ID 260
#define INTEGER 261
#define FLOAT 262
#define SEMICOLON 263
#define COLON 264
#define ASIGN 265
#define IF 266
#define WHILE 267
#define REPEAT 268
#define ELSE 269
#define READ 270
#define PRINT 271
#define SUM 272
#define REST 273
#define MULT 274
#define DIV 275
#define MAYORQUE 276
#define MENORQUE 277
#define IGUALA 278
#define PROGRAM 279
#define P_BEGIN 280
#define END 281
#define THEN 282
#define ENDIF 283
#define DO 284
#define ENDW 285
#define STEP 286
#define UNTIL 287
#define LPAREN 288
#define RPAREN 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "Parser.y"
{
    int valInt;
    float valFloat;
    char *valID;
    int sValor;
    Nodo *nodo;
}
/* Line 1529 of yacc.c.  */
#line 125 "Parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

