#include "syntaxTree.h"
#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//creacion de nodos---------------------------------------------------------------------------

Nodo * nodoInt( int valor ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoVALOR;
    nodoAux->tipoOp = opINT;
    nodoAux->simboloTipo = 0;
    nodoAux->uValor.valInt  = valor;
    return nodoAux;
}

Nodo * nodopFLOAT( float valor ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoVALOR;
    nodoAux->tipoOp = opFLOAT;
    nodoAux->simboloTipo = 1;
    nodoAux->uValor.valFloat  = valor;
    return nodoAux;
}

Nodo *nodoMenos( Nodo *nodoDerecha ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoVALOR;
    switch ( nodoDerecha->simboloTipo ) {
        case 0:
            nodoAux->simboloTipo = 0;
            nodoAux->tipoOp = opINT;
            nodoAux->uValor.valInt = -1;
            break;
        
        case 1:
            nodoAux->simboloTipo = 1;
            nodoAux->tipoOp = opFLOAT;
            nodoAux->uValor.valFloat  = -1.0;
            break; 
    }
    return nodoAux;
}

Nodo * nodoSimbolo( char  *valor , Variable **tablaAux) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoVALOR;
    nodoAux->tipoOp = opID;
    nodoAux->simboloTipo = getTipoSimbolo( tablaAux , valor );
    nodoAux->uValor.valID = valor;
    return nodoAux;
}

Nodo *nodoSimboloTipo( int tipo ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoTIPOSIMBOLO;
    nodoAux->simboloTipo = tipo;
    return nodoAux;
}

Nodo *nodoOperation( OperacionTipo operacion , Nodo *nodoIzquierda , Nodo *nodoDerecha) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoOPERATION;
    nodoAux->simboloTipo = isSameTipo( nodoIzquierda->simboloTipo , nodoDerecha->simboloTipo ); 
    nodoAux->tipoOp = operacion;
    nodoAux->nodoIzquierda = nodoIzquierda;
    nodoAux->nodoDerecha = nodoDerecha;
    return nodoAux;
}

Nodo *nodoExpresion( int expresion , Nodo *nodoIzquierda , Nodo *nodoDerecha) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoEXPRESION;
    nodoAux->simboloTipo = isSameTipo( nodoIzquierda->simboloTipo , nodoDerecha->simboloTipo ); 
    nodoAux->tipoExp = expresion;
    nodoAux->nodoIzquierda = nodoIzquierda;
    nodoAux->nodoDerecha = nodoDerecha;
    return nodoAux;
}

Nodo *nodoPuntoyComa( Nodo *nodoIzquierda , Nodo *nodoDerecha ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoSEMICOLON;
    nodoAux->nodoIzq = nodoIzquierda;
    nodoAux->nodoDer = nodoDerecha;
    return nodoAux;
}

Nodo *nodoAsignacion( char *id , Nodo *expr , Variable **tablaSimbolo ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoASIGN;
    nodoAux->simboloTipo = isSameTipo( expr->simboloTipo , getTipoSimbolo( tablaSimbolo , id ) );
    nodoAux->expr = expr;
    nodoAux->uValor.valID = id;
    return nodoAux;
}

Nodo *nodoIf( Nodo *expresion , Nodo *optStmts ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoIF;
    nodoAux->expresion = expresion;
    nodoAux->thenOptStmts = optStmts;
    return nodoAux;
}

Nodo *nodoIfElse( Nodo *expresion , Nodo *optStmts, Nodo *elseOptStmts ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoIFELSE;
    nodoAux->expresion = expresion;
    nodoAux->thenOptStmts = optStmts;
    nodoAux->elseOptStmts = elseOptStmts;
    return nodoAux;
}


Nodo *nodoWhile( Nodo *expresion , Nodo *optStmts ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoWHILE;
    nodoAux->expresion = expresion;
    nodoAux->doOptStmts = optStmts;
    return nodoAux;
}

Nodo *nodoRepeat( Nodo *expresion , Nodo *optStmts ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoREPEAT;
    nodoAux->expresion = expresion;
    nodoAux->doOptStmts = optStmts;
    return nodoAux;
}

Nodo *nodoRead( char *id ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoREAD;
    nodoAux->uValor.valID = id;
    return nodoAux;
}

Nodo *nodoPrint( Nodo *expr ) {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    nodoAux->tipo = nodoPRINT;
    nodoAux->expr = expr;
    return nodoAux;
}

int isSameTipo( int nodoIzquierda , int nodoDerecha ) {
    if ( nodoIzquierda == nodoDerecha )
        return nodoIzquierda;
    else { 
        printf( "Error: Tipos diferentes\n" );
        exit(1);
    }
}

//Interprete------------------------------------------------------------
int operacionInt( Nodo *operacion , Variable **tablaSimbolo) {
    switch ( operacion->tipoOp ) {
        case opINT:
            return operacion->uValor.valInt;
        case opID:
            return getSimboloInt( tablaSimbolo , operacion->uValor.valID);
        case opSUM:
            return operacionInt( operacion->nodoIzquierda , tablaSimbolo ) + operacionInt( operacion->nodoDerecha , tablaSimbolo );
        case opREST:
            return operacionInt( operacion->nodoIzquierda , tablaSimbolo ) - operacionInt( operacion->nodoDerecha , tablaSimbolo );
        case opMULT:
            return operacionInt( operacion->nodoIzquierda , tablaSimbolo ) * operacionInt( operacion->nodoDerecha , tablaSimbolo );
        case opDIV:
            return operacionInt( operacion->nodoIzquierda , tablaSimbolo ) / operacionInt( operacion->nodoDerecha , tablaSimbolo );
        default:
            return 0;
    }
}

float operacionFloat( Nodo *operation , Variable **tablaSimbolo) {
    switch (operation->tipoOp) {
        case opFLOAT:
            return operation->uValor.valFloat;
        case opID:
            return getSimbolopFLOAT( tablaSimbolo , operation->uValor.valID);
        case opSUM:
            return operacionFloat( operation->nodoIzquierda , tablaSimbolo ) + operacionFloat( operation->nodoDerecha , tablaSimbolo );
        case opREST:
            return operacionFloat( operation->nodoIzquierda , tablaSimbolo ) - operacionFloat( operation->nodoDerecha , tablaSimbolo );
        case opMULT:
            return operacionFloat( operation->nodoIzquierda , tablaSimbolo ) * operacionFloat( operation->nodoDerecha , tablaSimbolo );
        case opDIV:
            return operacionFloat( operation->nodoIzquierda , tablaSimbolo ) / operacionFloat( operation->nodoDerecha , tablaSimbolo );
        default:
            return 0;
    }
}

int booleanos(Nodo *expresion , Variable **tablaSimbolo ) {
    switch ( expresion->tipoExp ) {
        case 0:
            switch ( expresion->simboloTipo ) {
                case 0:
                    return operacionInt( expresion->nodoIzquierda , tablaSimbolo ) > operacionInt( expresion->nodoDerecha  , tablaSimbolo );
                case 1:
                    return operacionFloat( expresion->nodoIzquierda , tablaSimbolo ) > operacionFloat( expresion->nodoDerecha  , tablaSimbolo );
                default:
                    return 0;
            }
        case 1:
            switch ( expresion->simboloTipo ) {
                case 0:
                    return operacionInt( expresion->nodoIzquierda , tablaSimbolo ) < operacionInt( expresion->nodoDerecha  , tablaSimbolo );
                case 1:
                    return operacionFloat( expresion->nodoIzquierda , tablaSimbolo ) < operacionFloat( expresion->nodoDerecha  , tablaSimbolo );
                default:
                    return 0;
            }
        case 2:
            switch ( expresion->simboloTipo ) {
                case 0:
                    return operacionInt( expresion->nodoIzquierda , tablaSimbolo ) == operacionInt( expresion->nodoDerecha  , tablaSimbolo );
                case 1:
                    return operacionFloat( expresion->nodoIzquierda , tablaSimbolo ) == operacionFloat( expresion->nodoDerecha  , tablaSimbolo );
                default:
                    return 0;
            }
        default:
            return 0;
    }
}

int interpretaArbol( Nodo *tree , Variable **tablaSimbolo) {
    switch ( tree->tipo ) {
        case nodoSEMICOLON:
            interpretaArbol( tree->nodoIzq, tablaSimbolo );
            interpretaArbol( tree->nodoDer, tablaSimbolo );
            break;
        case nodoASIGN:
            switch ( tree->simboloTipo ) {
                case 0:
                    setSimboloInt( tablaSimbolo , tree->uValor.valID , operacionInt( tree->expr , tablaSimbolo ) );
                    break;
                case 1:
                    setSimbolopFLOAT( tablaSimbolo , tree->uValor.valID , operacionFloat( tree->expr , tablaSimbolo ) );
                    break;
                default:
                    return 0;
                break;
            }
            break;
        case nodoIF:
            if ( booleanos( tree->expresion , tablaSimbolo ) ) {
                interpretaArbol( tree->thenOptStmts , tablaSimbolo );
            }
            break;  
        case nodoIFELSE:
            if ( booleanos( tree->expresion , tablaSimbolo ) ) {
                interpretaArbol( tree->thenOptStmts , tablaSimbolo );
            }
            else{
                interpretaArbol( tree->elseOptStmts , tablaSimbolo );
            }
            break;
        case nodoWHILE:
            while ( booleanos( tree->expresion , tablaSimbolo ) ) {
                interpretaArbol( tree->doOptStmts , tablaSimbolo );
            }
            break;

        case nodoREPEAT:
            do{
                interpretaArbol( tree->doOptStmts , tablaSimbolo );
            }
            while ( booleanos( tree->expresion , tablaSimbolo ) );
            break;

        case nodoREAD:
            switch ( getTipoSimbolo( tablaSimbolo , tree->uValor.valID ) ) {
                case 0: {
                    printf( "%s= ", tree->uValor.valID );
                    int aux;
                    scanf( "%d" , &aux );
                    printf( "\n" );
                    setSimboloInt( tablaSimbolo, tree->uValor.valID , aux );
                    break;
                }
                case 1: {
                    float aux;
                    printf( "%s= ", tree->uValor.valID );
                    scanf( "%f" , &aux );
                    printf( "\n" );
                    setSimbolopFLOAT( tablaSimbolo, tree->uValor.valID , aux );
                    break;
                }
            }
            break;
        case nodoPRINT:
            switch ( tree->expr->simboloTipo ) {
                case 0:
                    printf ( "%d\n" , operacionInt( tree->expr , tablaSimbolo ) );
                break;
                case 1:
                    printf ( "%f\n" , operacionFloat( tree->expr , tablaSimbolo ) );
                break;
            }
            break;
        default:
            return 1;
            break;
    }
    return 1;
}