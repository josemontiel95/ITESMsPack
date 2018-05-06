%{
// Oscar Gaytan Montero A01327292
// Jose Maria Montiel Palacios A01323942

 #include "symbolTable.h"
 #include "syntaxTree.h"
 #include "Parser.tab.h"
 #include "lex.yy.h"
 #include <stdio.h>

 //Declaracion del arbol y la tabla de simbolos.
 Variable *symbolTable;
 Nodo   *syntaxTree;

//Variables y metodos externos
extern int yylex();
extern int yyerror(char const *);

%}

%error-verbose



//Unite tokens from flex with bison using bison %union directive
%union {

    int valInt;
    float valFloat;
    char *valID;
    VarTipo sValue;
    Nodo *node;
    
}

//==============================Declaracion de tokens

%token <valInt>  NUM
%token <valFloat>  NUMFLOAT
%token <valID> ID
%token <sValue>  INTEGER
%token <sValue>  FLOAT

%token <node> SEMICOLON
%token <node> COLON
%token <node> ASSIGNMENT
%token <node> IF
%token <node> WHILE
%token <node> REPEAT
%token <node> FOR
%token <node> ELSE
%token <node> READ
%token <node> PRINT
%token <node> SUM
%token <node> SUB
%token <node> MULT
%token <node> DIV
%token <node> GREATER_THAN
%token <node> LESS_THAN
%token <node> EQUAL_TO

%type <node> prog
%type <node> opt_decls
%type <node> decls
%type <node> dec
%type <node> tipo
%type <node> stmt
%type <node> opt_stmts
%type <node> stmt_lst
%type <node> expr
%type <node> term
%type <node> factor
%type <node> expresion


%token PROGRAM
%token P_BEGIN
%token END
%token THEN
%token ENDIF
%token DO
%token ENDW
%token STEP
%token UNTIL
%token ENDFOR
%token LPAREN
%token RPAREN

%start prog //starting point of the parser

%%

prog:
              PROGRAM ID opt_decls P_BEGIN opt_stmts END                      { syntaxTree = $5; interpretaArbol( syntaxTree, &symbolTable ); YYACCEPT;}
            ;

opt_decls:  
              decls
            | /*empty*/                                                       { }
            ;

decls:        dec SEMICOLON decls
            | dec
            ;

dec:          ID COLON tipo                                                         { insertaSimbolo( &symbolTable , $1 , $3->simboloTipo ); }
            ;

tipo:         INTEGER                                                         { $$ = nodoSimboloTipo( $1 ); }
            | FLOAT                                                           { $$ = nodoSimboloTipo( $1 ); }
            ;

stmt:         ID ASSIGNMENT expr                                              { $$ = nodoAsignacion( $1 , $3 , &symbolTable ); }
            | IF  LPAREN expresion RPAREN opt_stmts ENDIF                     { $$ = nodoIf( $3 , $5 ); }
            | IF  LPAREN expresion RPAREN opt_stmts ELSE opt_stmts ENDIF      { $$ = nodoIfElse( $3 , $5, $7 ); }
            | WHILE LPAREN expresion RPAREN opt_stmts ENDW                    { $$ = nodoWhile( $3 , $5 ); }
            | REPEAT opt_stmts UNTIL LPAREN expresion RPAREN                  { $$ = nodoRepeat( $5 , $2 ); }
            | FOR ID ASSIGNMENT expr STEP expr UNTIL expr DO opt_stmts ENDFOR { /*$$ = nodoFor( $2 , $4 , $6 , $8 , $10 ); */}
            | READ ID                                                         { $$ = nodoRead( $2 ); }
            | PRINT expr                                                      { $$ = nodoPrint( $2 ); }
            ;

opt_stmts:    stmt_lst                                                        {$$ = $1; }
            | /*empty*/                                                       { $$ = NULL; }
            ;

stmt_lst:     stmt SEMICOLON stmt_lst                                         { $$ = nodoPuntoyComa( $1 , $3 ); }
            | stmt                                                            { $$ = $1; }
            ;

expr:         expr SUM term                                                   { $$ = nodoOperation( oSUM , $1 , $3); }
            | expr SUB term                                                   { $$ = nodoOperation( oSUB , $1 , $3); }
            | SUB term                                                        { $$ = nodoOperation( oMULT , nodoMenos( $2 ) , $2 ); }
            | term                                                            { $$ = $1; }
            ;

term:         term MULT factor                                                { $$ = nodoOperation( oMULT , $1 , $3); }
            | term DIV factor                                                 { $$ = nodoOperation( oDIV , $1 , $3); }
            | factor                                                          { $$ = $1; }
            ;

factor:       LPAREN expr RPAREN                                              { $$ = $2; }
            | ID                                                              { $$ = nodoSimbolo( $1 , &symbolTable); }
            | NUM                                                             { $$ = nodoInt( $1 ); }
            | NUMFLOAT                                                        { $$ = nodoFloat( $1 ); }
            ;

expresion:    expr LESS_THAN expr                                             { $$ = nodoExpresion( eLESS_THAN , $1 , $3); }
            | expr GREATER_THAN expr                                          { $$ = nodoExpresion( eGREATER_THAN , $1 , $3); }
            | expr EQUAL_TO expr                                              { $$ = nodoExpresion( eEQUAL_TO , $1 , $3 ); }
            ;

%%

int yyerror( char const * s ) 
{
  fprintf( stderr, "%s\n", s );
  exit(1);
}

int main( int argc, char **argv ) {

    extern FILE * yyin;

    yyin = fopen( argv[1], "r" );

    yyparse();

    return 0;

    //end main
}

//End parser.y



