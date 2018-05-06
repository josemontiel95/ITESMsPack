#ifndef __SYNTAX_TREE_H__
#define __SYNTAX_TREE_H__
#include "symbolTable.h"

typedef enum aNodoTipo {
    nVALUE,
    nTIPOSIMBOLO,
    nOPERATION,
    nEXPRESION,
    nSEMICOLON,
    nDECLARATION,
    nASSIGNMENT,
    nIF,
    nWHILE,
    nFOR,
    nREAD,
    nPRINT,
    nREPEAT,
    nIFELSE
} NodoTipo;

typedef enum aOperacionTipo {
    oINTEGER,
    oFLOAT,
    oID,
    oSUM,
    oSUB,
    oDIV,
    oMULT
} OperacionTipo;

typedef enum aExpresionTipo {
    eGREATER_THAN,
    eLESS_THAN,
    eEQUAL_TO
} ExpresionTipo;

typedef struct aNodo {  
    NodoTipo tipo; 
    /********** EXPR | TERM | FACTOR components **********/
    OperacionTipo tipoOp; 
    VarTipo valorTipo;

    union {
        int valInt;
        float valFloat; 
        char *valID;
    } value;
    
    struct aNodo *nodoIzquierda; 
    struct aNodo *nodoDerecha; 

    /********** EXPRESION components **********/
    ExpresionTipo tipoExp;
    
    /********** SEMICOLON components **********/
    struct aNodo *nodoIzq;
    struct aNodo *nodoDer;

    /********** DEC Components **********/
    VarTipo simboloTipo;

    /********** ASSIGNMENT STMT Components **********/
    struct aNodo *expr;

    /********** IF STMT Components **********/
    struct aNodo *expresion;
    struct aNodo *thenOptStmts;
    struct aNodo *elseOptStmts;

    /********** WHILE STMT Components **********/
    struct aNodo *doOptStmts;

    /********** FOR STMT Components **********/
    struct aNodo *assignment_stmt; 
    //struct aNodo *stepExpr; 
    struct aNodo *untilExpr;
} Nodo;


Nodo *nodoInt( int valor );
Nodo *nodoFloat( float valor );
Nodo *nodoMenos( Nodo *nodoDerecha );
Nodo *nodoSimbolo( char *valor , Variable **tablaAux );
Nodo *nodoSimboloTipo( VarTipo tipo );
Nodo *nodoOperation( OperacionTipo operacion , Nodo *nodoIzquierda , Nodo *nodoDerecha);
Nodo *nodoExpresion( ExpresionTipo expresion , Nodo *nodoIzquierda , Nodo *nodoDerecha );
Nodo *nodoPuntoyComa( Nodo *nodoIzquierda , Nodo *nodoDerecha );
Nodo *nodoAsignacion( char *id , Nodo *expr , Variable **tablaSimbolo );
Nodo *nodoIf( Nodo *expresion , Nodo *optStmts );
Nodo *nodoIfElse( Nodo *expresion , Nodo *optStmts, Nodo *elseOptStmts );
Nodo *nodoWhile( Nodo *expresion , Nodo *optStmts );
Nodo *nodoRepeat( Nodo *expresion , Nodo *optStmts );
//Nodo *nodoFor( char *id , Nodo *expr , Nodo *stepExpr , Nodo *untilExpr , Nodo *doOptStmts );
Nodo *nodoRead( char *id );
Nodo *nodoPrint( Nodo *expr );
VarTipo isSameTipo( VarTipo nodoIzquierda , VarTipo nodoDerecha );

int operacionInt( Nodo *operation , Variable **tablaSimbolo );
float operacionFloat( Nodo *operation , Variable **tablaSimbolo );
int booleanos(Nodo *expresion , Variable **tablaSimbolo );
int interpretaArbol( Nodo *tree , Variable **tablaSimbolo);

#endif