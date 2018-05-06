%{
// Oscar Gaytan Montero A01327292
// Jose Maria Montiel Palacios A01323942

//Include our syntax Tree and symbol table libraries
#include "syntaxTree.h"
#include "symbolTable.h"

//we include the bison generated file to have access to the tokens
#include "Parser.tab.h"

#include<math.h>
#include<string.h>

%}

/*Compiler directives*/

/*Identifier Definitions*/

ID       [a-zA-Z][a-zA-Z0-9]*

NUM      (0|[1-9][0-9]*)

NUMFLOAT (0|[1-9][0-9]*)[.](([0-9]*[1-9]*)|0)

WS       [\n\t ]

%%

program    { return PROGRAM; }

begin      { return P_BEGIN;  }

end        { return END;}

:=         { return ASSIGNMENT; }

int        { yylval.sValue = vINT; return INTEGER; }

float      { yylval.sValue = vFLOAT; return FLOAT;  }

if         { return IF; }

else       { return ELSE;}

then       { return THEN; }

endif      { return ENDIF;  }

while      { return WHILE; }

do         { return DO; }

endw       { return ENDW;  }

for        { return FOR;  }

step       { return STEP;  }

until      { return UNTIL; }

repeat	   { return REPEAT; }

endfor     { return ENDFOR; }

read       { return READ; }

print      { return PRINT;  }

{ID}       { yylval.idValue = strdup(yytext); return ID;  }

{NUMFLOAT} { yylval.fValue = atof(yytext); return NUMFLOAT;}

{NUM}      { yylval.iValue = atoi(yytext); return NUM;  }

[(]        { return LPAREN; }

[)]        { return RPAREN; }

[+]        { return SUM;  }

[-]        { return SUB; }

[*]        { return MULT;  }

[\/]        { return DIV; }

[;]        { return SEMICOLON;  }

[:]        { return COLON; }

[>]        { return GREATER_THAN; }

[<]        { return LESS_THAN; }

[=]        { return EQUAL_TO; }

{WS}       { /*saltar espacios en blanco*/; }

%%

//end lexer.l