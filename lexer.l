%{
#include "syntaxTree.h"
#include "symbolTable.h"
#include "Parser.tab.h"
#include <math.h>
#include <string.h>
%}

ID       [a-zA-Z][a-zA-Z0-9]*
NUM      (0|[1-9][0-9]*)
NUMFLOAT (0|[1-9][0-9]*)[.](([0-9]*[1-9]*)|0)
NADA       [\n\t ]

%%

program    { return PROGRAM; }
begin      { return P_BEGIN;  }
end        { return END;}
:=         { return ASIGN; }
int        { yylval.sValor = 0; return INTEGER; }
float      { yylval.sValor = 1; return FLOAT;  }
if         { return IF; }
else       { return ELSE;}
then       { return THEN; }
endif      { return ENDIF;  }
while      { return WHILE; }
do         { return DO; }
endw       { return ENDW;  }
step       { return STEP;  }
until      { return UNTIL; }
repeat	   { return REPEAT; }
read       { return READ; }
print      { return PRINT;  }

{ID}       { yylval.valID = strdup(yytext); return ID;  }
{NUMFLOAT} { yylval.valFloat = atof(yytext); return NUMFLOAT;}
{NUM}      { yylval.valInt = atoi(yytext); return NUM;  }

[(]        { return LPAREN; }
[)]        { return RPAREN; }
[+]        { return SUM;  }
[-]        { return REST; }
[*]        { return MULT;  }
[\/]        { return DIV; }
[;]        { return SEMICOLON;  }
[:]        { return COLON; }
[>]        { return MAYORQUE; }
[<]        { return MENORQUE; }
[=]        { return IGUALA; }
{NADA}       {;}
%%