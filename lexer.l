%{
/**
 * lexer.l
 *
 * lexer file for the simple language
 *
 * @author Jose Pablo Ortiz Lack
 *
 * To generate the lexical analyzer run: "flex Lexer.l"
 *
 **/

//Include our syntax Tree and symbol table libraries
#include "syntaxTree.h"
#include "symbolTable.h"

//we include the bison generated file to have access to the tokens
#include "Parser.h"

#include<math.h>
#include<string.h>

%}

/*Compiler directives*/

%option outfile="Lexer.c" header-file="Lexer.h" 

/*Identifier Definitions*/

ID       [a-zA-Z][a-zA-Z0-9]*

NUM      (0|[1-9][0-9]*)

NUMFLOAT (0|[1-9][0-9]*)[.](([0-9]*[1-9]*)|0)

WS       [\n\t ]

%%

program    { return PROGRAM; /*terminal symbol program was found*/ }

begin      { return P_BEGIN; /*terminal symbol begin was found*/ }

end        { return END; /*terminal symbol end was found*/ }

:=         { return ASSIGNMENT; /*terminal symbol assignment was found*/ }

int        { yylval.sValue = sINTEGER; return INTEGER; /*terminal symbol int was found*/ }

float      { yylval.sValue = sFLOAT; return FLOAT; /*terminal symbol float was found*/ }

if         { return IF; /*terminal symbol if was found*/ }

then       { return THEN; /*terminal symbol then was found*/ }

endif      { return ENDIF; /*terminal symbol endif was found*/ }

while      { return WHILE; /*terminal symbol while was found*/ }

do         { return DO; /*terminal symbol do was found*/ }

endw       { return ENDW; /*terminal symbol endw was found*/ }

for        { return FOR; /*terminal symbol for was found*/ }

step       { return STEP;  /*terminal symbol step was found*/ }

until      { return UNTIL; /*terminal symbol until was found*/ }

repeat	   { return REPEAT; /*terminal symbol until was found*/ }

endfor     { return ENDFOR; /*terminal symbol endfor was found*/ }

read       { return READ; /*terminal symbol read was found*/ }

print      { return PRINT; /*terminal symbol print was found*/ }

{ID}       { yylval.idValue = strdup(yytext); return ID; /*stores the identifier string and returns the ID token*/ }

{NUMFLOAT} { yylval.fValue = atof(yytext); return NUMFLOAT; /*converts the text to a float and returns the NUMFLOAT token*/ }

{NUM}      { yylval.iValue = atoi(yytext); return NUM; /*converts the text to an integer and returns the NUM token*/ }

[(]        { return LPAREN; /*terminal symbol left parenthesis was found*/ }

[)]        { return RPAREN; /*terminal symbol right parenthesis was found*/ }

[+]        { return SUM; /*terminal symbol sum was found*/ }

[-]        { return SUB; /*terminal symbol substract was found*/ }

[*]        { return MULT; /*terminal symbol multiply was found*/ }

[\/]        { return DIV; /*terminal symbol divide was found*/ }

[;]        { return SEMICOLON; /*terminal symbol semicolon was found*/ }

[:]        { return COLON; /*terminal symbol colon was found*/ }

[>]        { return GREATER_THAN; /*terminal symbol greater than was found*/ }

[<]        { return LESS_THAN; /*terminal symbol less than was found*/ }

[=]        { return EQUAL_TO; /*terminal symbol equal to was found*/ }

{WS}       { /*skip blanks*/; }

%%

//end lexer.l