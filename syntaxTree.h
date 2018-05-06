#ifndef __SYNTAX_TREE_H__
#define __SYNTAX_TREE_H__
#include "symbolTable.h"

typedef enum aNodoTipo {
    nodoVALOR,
    nodoTIPOSIMBOLO,
    nodoOPERATION,
    nodoEXPRESION,
    nodoSEMICOLON,
    nodoDECLARATION,
    nodoASIGN,
    nodoIF,
    nodoWHILE,
    nodoENDWHILE,
    nodoREAD,
    nodoPRINT,
    nodoREPEAT,
    nodoIFELSE
} NodoTipo;

typedef enum aOperacionTipo {
    opINT,
    opFLOAT,
    opID,
    opSUM,
    opREST,
    opDIV,
    opMULT
} OperacionTipo;

typedef struct aNodo {  
    NodoTipo tipo; 
    OperacionTipo tipoOp; 
    int valorTipo;
    union {
        int valInt;
        float valFloat; 
        char *valID;
    } uValor;
    
    struct aNodo *nodoIzquierda; 
    struct aNodo *nodoDerecha; 

    int tipoExp;  
    int simboloTipo;  

    //SEMICOLON
    struct aNodo *nodoIzq;
    struct aNodo *nodoDer;

    struct aNodo *expr;

    //IF STMT
    struct aNodo *expresion;
    struct aNodo *thenOptStmts;
    struct aNodo *elseOptStmts;

    //WHILE STMT
    struct aNodo *doOptStmts;
    struct aNodo *untilExpr;
} Nodo;


Nodo *nodoInt( int valor );
Nodo *nodopFLOAT( float valor );
Nodo *nodoMenos( Nodo *nodoDerecha );
Nodo *nodoSimbolo( char *valor , Variable **tablaAux );
Nodo *nodoSimboloTipo( int tipo );
Nodo *nodoOperation( OperacionTipo operacion , Nodo *nodoIzquierda , Nodo *nodoDerecha);
Nodo *nodoExpresion( int expresion , Nodo *nodoIzquierda , Nodo *nodoDerecha );
Nodo *nodoPuntoyComa( Nodo *nodoIzquierda , Nodo *nodoDerecha );
Nodo *nodoAsignacion( char *id , Nodo *expr , Variable **tablaSimbolo );
Nodo *nodoIf( Nodo *expresion , Nodo *optStmts );
Nodo *nodoIfElse( Nodo *expresion , Nodo *optStmts, Nodo *elseOptStmts );
Nodo *nodoWhile( Nodo *expresion , Nodo *optStmts );
Nodo *nodoRepeat( Nodo *expresion , Nodo *optStmts );
Nodo *nodoRead( char *id );
Nodo *nodoPrint( Nodo *expr );
int isSameTipo( int nodoIzquierda , int nodoDerecha );

int operacionInt( Nodo *operation , Variable **tablaSimbolo );
float operacionFloat( Nodo *operation , Variable **tablaSimbolo );
int booleanos(Nodo *expresion , Variable **tablaSimbolo );
int interpretaArbol( Nodo *tree , Variable **tablaSimbolo);

#endif