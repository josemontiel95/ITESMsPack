%{
// Oscar Gaytan Montero A01327292
// Jose Maria Montiel Palacios A01323942
 #include "symbolTable.h"
 #include "syntaxTree.h"
 #include "Parser.tab.h"
 #include "lex.yy.h"
 #include <stdio.h>

 Variable *symbolTable;
 Nodo   *syntaxTree;
extern int yylex();
extern int yyerror(char const *);
%}

%error-verbose
%union {
    int valInt;
    float valFloat;
    char *valID;
    int sValor;
    Nodo *nodo;
}

%token <valInt>  NUM
%token <valFloat>  NUMFLOAT
%token <valID> ID
%token <sValor>  INTEGER
%token <sValor>  FLOAT
%token <nodo> SEMICOLON
%token <nodo> COLON
%token <nodo> ASIGN
%token <nodo> IF
%token <nodo> WHILE
%token <nodo> REPEAT
%token <nodo> ELSE
%token <nodo> READ
%token <nodo> PRINT
%token <nodo> SUM
%token <nodo> REST
%token <nodo> MULT
%token <nodo> DIV
%token <nodo> MAYORQUE
%token <nodo> MENORQUE
%token <nodo> IGUALA
%type <nodo> prog
%type <nodo> opt_decls
%type <nodo> decls
%type <nodo> dec
%type <nodo> tipo
%type <nodo> stmt
%type <nodo> opt_stmts
%type <nodo> stmt_lst
%type <nodo> expr
%type <nodo> term
%type <nodo> factor
%type <nodo> expresion
%token PROGRAM
%token P_BEGIN
%token END
%token THEN
%token ENDIF
%token DO
%token ENDW
%token STEP
%token UNTIL
%token LPAREN
%token RPAREN
%start prog 

%%
prog:
              PROGRAM ID opt_decls P_BEGIN opt_stmts END { syntaxTree = $5; interpretaArbol( syntaxTree, &symbolTable ); YYACCEPT;};

opt_decls:  
              decls
            | { };

decls:        dec SEMICOLON decls
            | dec;

dec:          ID COLON tipo { insertaSimbolo( &symbolTable , $1 , $3->simboloTipo ); };

tipo:         INTEGER { $$ = nodoSimboloTipo( $1 ); }
            | FLOAT { $$ = nodoSimboloTipo( $1 ); };

stmt:         ID ASIGN expr { $$ = nodoAsignacion( $1 , $3 , &symbolTable ); }
            | IF  LPAREN expresion RPAREN opt_stmts ENDIF { $$ = nodoIf( $3 , $5 ); }
            | IF  LPAREN expresion RPAREN opt_stmts ELSE opt_stmts ENDIF { $$ = nodoIfElse( $3 , $5, $7 ); }
            | WHILE LPAREN expresion RPAREN opt_stmts ENDW { $$ = nodoWhile( $3 , $5 ); }
            | REPEAT opt_stmts UNTIL LPAREN expresion RPAREN { $$ = nodoRepeat( $5 , $2 ); }
            | READ ID { $$ = nodoRead( $2 ); }
            | PRINT expr { $$ = nodoPrint( $2 ); };

opt_stmts:    stmt_lst                                                        {$$ = $1; }
            | { $$ = NULL; };

stmt_lst:     stmt SEMICOLON stmt_lst { $$ = nodoPuntoyComa( $1 , $3 ); }
            | stmt { $$ = $1; };

expr:         expr SUM term { $$ = nodoOperation( opSUM , $1 , $3); }
            | expr REST term { $$ = nodoOperation( opREST , $1 , $3); }
            | REST term { $$ = nodoOperation( opMULT , nodoMenos( $2 ) , $2 ); }
            | term { $$ = $1; };

term:         term MULT factor { $$ = nodoOperation( opMULT , $1 , $3); }
            | term DIV factor { $$ = nodoOperation( opDIV , $1 , $3); }
            | factor { $$ = $1; };

factor:       LPAREN expr RPAREN { $$ = $2; }
            | ID { $$ = nodoSimbolo( $1 , &symbolTable); }
            | NUM { $$ = nodoInt( $1 ); }
            | NUMFLOAT { $$ = nodopFLOAT( $1 ); };

expresion:    expr MENORQUE expr { $$ = nodoExpresion( 1 , $1 , $3); }
            | expr MAYORQUE expr { $$ = nodoExpresion( 0 , $1 , $3); }
            | expr IGUALA expr { $$ = nodoExpresion( 2 , $1 , $3 ); };

%%

int yyerror( char const * s ) {
  fprintf( stderr, "%s\n", s );
  exit(1);
}

int main( int argc, char **argv ) {
    extern FILE * yyin;
    yyin = fopen( argv[1], "r" );
    yyparse();
    return 0;
}