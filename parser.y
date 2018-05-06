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
 Node   *syntaxTree;

//Variables y metodos externos
extern int yylex();
extern int yyerror(char const *);

%}

%error-verbose



//Unite tokens from flex with bison using bison %union directive
%union {

    int iValue;
    float fValue;
    char *idValue;
    VarTipo sValue;
    Node *node;
    
}

//==============================Declaracion de tokens

%token <iValue>  NUM
%token <fValue>  NUMFLOAT
%token <idValue> ID
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
              PROGRAM ID opt_decls P_BEGIN opt_stmts END                      { syntaxTree = $5; resolveTree( syntaxTree, &symbolTable ); YYACCEPT;}
            ;

opt_decls:  
              decls
            | /*empty*/                                                       { }
            ;

decls:        dec SEMICOLON decls
            | dec
            ;

dec:          ID COLON tipo                                                         { insertaSimbolo( &symbolTable , $1 , $3->symbolType ); }
            ;

tipo:         INTEGER                                                         { $$ = createSymbolType( $1 ); }
            | FLOAT                                                           { $$ = createSymbolType( $1 ); }
            ;

stmt:         ID ASSIGNMENT expr                                              { $$ = createAssignment( $1 , $3 , &symbolTable ); }
            | IF  LPAREN expresion RPAREN opt_stmts ENDIF                     { $$ = createIfStatement( $3 , $5 ); }
            | IF  LPAREN expresion RPAREN opt_stmts ELSE opt_stmts ENDIF      { $$ = createIfElseStatement( $3 , $5, $7 ); }
            | WHILE LPAREN expresion RPAREN opt_stmts ENDW                    { $$ = createWhileStatement( $3 , $5 ); }
            | REPEAT opt_stmts UNTIL LPAREN expresion RPAREN                  { $$ = createRepeatStatement( $5 , $2 ); }
            | FOR ID ASSIGNMENT expr STEP expr UNTIL expr DO opt_stmts ENDFOR { $$ = createForStatement( $2 , $4 , $6 , $8 , $10 ); }
            | READ ID                                                         { $$ = createReadStatement( $2 ); }
            | PRINT expr                                                      { $$ = createPrintStatement( $2 ); }
            ;

opt_stmts:    stmt_lst                                                        {$$ = $1; }
            | /*empty*/                                                       { $$ = NULL; }
            ;

stmt_lst:     stmt SEMICOLON stmt_lst                                         { $$ = createSemiColon( $1 , $3 ); }
            | stmt                                                            { $$ = $1; }
            ;

expr:         expr SUM term                                                   { $$ = createOperation( oSUM , $1 , $3); }
            | expr SUB term                                                   { $$ = createOperation( oSUB , $1 , $3); }
            | SUB term                                                        { $$ = createOperation( oMULT , createMinus( $2 ) , $2 ); }
            | term                                                            { $$ = $1; }
            ;

term:         term MULT factor                                                { $$ = createOperation( oMULT , $1 , $3); }
            | term DIV factor                                                 { $$ = createOperation( oDIV , $1 , $3); }
            | factor                                                          { $$ = $1; }
            ;

factor:       LPAREN expr RPAREN                                              { $$ = $2; }
            | ID                                                              { $$ = createSymbol( $1 , &symbolTable); }
            | NUM                                                             { $$ = createInteger( $1 ); }
            | NUMFLOAT                                                        { $$ = createFloat( $1 ); }
            ;

expresion:    expr LESS_THAN expr                                             { $$ = createExpresion( eLESS_THAN , $1 , $3); }
            | expr GREATER_THAN expr                                          { $$ = createExpresion( eGREATER_THAN , $1 , $3); }
            | expr EQUAL_TO expr                                              { $$ = createExpresion( eEQUAL_TO , $1 , $3 ); }
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



