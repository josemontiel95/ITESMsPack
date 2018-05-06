#include "syntaxTree.h"
#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Nodo *allocateNodo() {
    Nodo *nodoAux = malloc( sizeof( Nodo ) );
    if ( nodoAux == NULL ) {
        printf( "Error: Memory allocation failed. Program will be terminated\n" );
        exit(1);
    }
    return nodoAux;
}

//creacion de nodos---------------------------------------------------------------------------

Nodo * nodoInt( int valor ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo          = nVALUE;
    nodoAux->tipoOp = oINTEGER;
    nodoAux->simboloTipo    = vINT;
    nodoAux->value.valInt  = valor;
    return nodoAux;
}

Nodo * nodoFloat( float valor ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo          = nVALUE;
    nodoAux->tipoOp = oFLOAT;
    nodoAux->simboloTipo    = vFLOAT;
    nodoAux->value.valFloat  = valor;
    return nodoAux;
}

Nodo *nodoMenos( Nodo *nodoDerecha ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo = nVALUE;
    switch ( nodoDerecha->simboloTipo ) {
        case vINT:
            nodoAux->simboloTipo    = vINT;
            nodoAux->tipoOp = oINTEGER;
            nodoAux->value.valInt  = -1;
            break;
        
        case vFLOAT:
            nodoAux->simboloTipo    = vFLOAT;
            nodoAux->tipoOp = oFLOAT;
            nodoAux->value.valFloat  = -1.0;
            break; 
    }
    return nodoAux;
}

Nodo * nodoSimbolo( char  *valor , Variable **tablaAux) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo          = nVALUE;
    nodoAux->tipoOp = oID;
    nodoAux->simboloTipo    = getTipoSimbolo( tablaAux , valor );
    nodoAux->value.valID = valor;
    return nodoAux;
}

Nodo *nodoSimboloTipo( VarTipo tipo ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo       = nTIPOSIMBOLO;
    nodoAux->simboloTipo = tipo;
    return nodoAux;
}

Nodo *nodoOperation( OperacionTipo operacion , Nodo *nodoIzquierda , Nodo *nodoDerecha) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo          = nOPERATION;
    nodoAux->simboloTipo    = isSameTipo( nodoIzquierda->simboloTipo , nodoDerecha->simboloTipo ); 
    nodoAux->tipoOp = operacion;
    nodoAux->nodoIzquierda   = nodoIzquierda;
    nodoAux->nodoDerecha  = nodoDerecha;
    return nodoAux;
}

Nodo *nodoExpresion( ExpresionTipo expresion , Nodo *nodoIzquierda , Nodo *nodoDerecha) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo = nEXPRESION;
    nodoAux->simboloTipo = isSameTipo( nodoIzquierda->simboloTipo , nodoDerecha->simboloTipo ); 
    nodoAux->tipoExp = expresion;
    nodoAux->nodoIzquierda = nodoIzquierda;
    nodoAux->nodoDerecha = nodoDerecha;
    return nodoAux;
}

Nodo *nodoPuntoyComa( Nodo *nodoIzquierda , Nodo *nodoDerecha ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo = nSEMICOLON;
    nodoAux->nodoIzq = nodoIzquierda;
    nodoAux->nodoDer = nodoDerecha;
    return nodoAux;
}

Nodo *nodoAsignacion( char *id , Nodo *expr , Variable **tablaSimbolo ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo = nASSIGNMENT;
    nodoAux->simboloTipo = isSameTipo( expr->simboloTipo , getTipoSimbolo( tablaSimbolo , id ) );
    nodoAux->expr = expr;
    nodoAux->value.valID = id;
    return nodoAux;
}

Nodo *nodoIf( Nodo *expresion , Nodo *optStmts ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo         = nIF;
    nodoAux->expresion    = expresion;
    nodoAux->thenOptStmts = optStmts;
    return nodoAux;
}

Nodo *nodoIfElse( Nodo *expresion , Nodo *optStmts, Nodo *elseOptStmts ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo         = nIFELSE;
    nodoAux->expresion    = expresion;
    nodoAux->thenOptStmts = optStmts;
    nodoAux->elseOptStmts = elseOptStmts;
    return nodoAux;
}


Nodo *nodoWhile( Nodo *expresion , Nodo *optStmts ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo       = nWHILE;
    nodoAux->expresion  = expresion;
    nodoAux->doOptStmts = optStmts;
    return nodoAux;
}

Nodo *nodoRepeat( Nodo *expresion , Nodo *optStmts ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo       = nREPEAT;
    nodoAux->expresion  = expresion;
    nodoAux->doOptStmts = optStmts;
    return nodoAux;
}

/*Nodo *nodoFor( char *id , Nodo *expr , Nodo *stepExpr , Nodo *untilExpr , Nodo *doOptStmts ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo          = nFOR;
    nodoAux->value.valID = id;
    nodoAux->expr          = expr;
    nodoAux->stepExpr      = stepExpr;
    nodoAux->untilExpr     = untilExpr;
    nodoAux->doOptStmts    = doOptStmts;
    return nodoAux;

}*/

Nodo *nodoRead( char *id ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo          = nREAD;
    nodoAux->value.valID = id;
    return nodoAux;
}

Nodo *nodoPrint( Nodo *expr ) {
    Nodo *nodoAux = allocateNodo();
    nodoAux->tipo = nPRINT;
    nodoAux->expr = expr;
    return nodoAux;
}

VarTipo isSameTipo( VarTipo nodoIzquierda , VarTipo nodoDerecha ) {
    if ( nodoIzquierda == nodoDerecha ) {
        return nodoIzquierda;
    } else { 
        printf( "Error: Types do not match. Program will be terminated.\n" );
        exit(1);
    }
}

//Interprete------------------------------------------------------------
int operacionInt( Nodo *operacion , Variable **tablaSimbolo) {
    switch ( operacion->tipoOp ) {
        case oINTEGER:
            return operacion->value.valInt;
        case oID:
            return getSimboloInt( tablaSimbolo , operacion->value.valID);
        case oSUM:
            return operacionInt( operacion->nodoIzquierda , tablaSimbolo ) + operacionInt( operacion->nodoDerecha , tablaSimbolo );
        case oSUB:
            return operacionInt( operacion->nodoIzquierda , tablaSimbolo ) - operacionInt( operacion->nodoDerecha , tablaSimbolo );
        case oMULT:
            return operacionInt( operacion->nodoIzquierda , tablaSimbolo ) * operacionInt( operacion->nodoDerecha , tablaSimbolo );
        case oDIV:
            return operacionInt( operacion->nodoIzquierda , tablaSimbolo ) / operacionInt( operacion->nodoDerecha , tablaSimbolo );
        default:
            return 0;
    }
}

float operacionFloat( Nodo *operation , Variable **tablaSimbolo) {
    switch (operation->tipoOp) {
        case oFLOAT:
            return operation->value.valFloat;
        case oID:
            return getSimboloFloat( tablaSimbolo , operation->value.valID);
        case oSUM:
            return operacionFloat( operation->nodoIzquierda , tablaSimbolo ) + operacionFloat( operation->nodoDerecha , tablaSimbolo );
        case oSUB:
            return operacionFloat( operation->nodoIzquierda , tablaSimbolo ) - operacionFloat( operation->nodoDerecha , tablaSimbolo );
        case oMULT:
            return operacionFloat( operation->nodoIzquierda , tablaSimbolo ) * operacionFloat( operation->nodoDerecha , tablaSimbolo );
        case oDIV:
            return operacionFloat( operation->nodoIzquierda , tablaSimbolo ) / operacionFloat( operation->nodoDerecha , tablaSimbolo );
        default:
            return 0;
    }
}

int booleanos(Nodo *expresion , Variable **tablaSimbolo ) {
    switch ( expresion->tipoExp ) {
        case eGREATER_THAN:
            switch ( expresion->simboloTipo ) {
                case vINT:
                    return operacionInt( expresion->nodoIzquierda , tablaSimbolo ) > operacionInt( expresion->nodoDerecha  , tablaSimbolo );
                case vFLOAT:
                    return operacionFloat( expresion->nodoIzquierda , tablaSimbolo ) > operacionFloat( expresion->nodoDerecha  , tablaSimbolo );
                default:
                    return 0;
            }
        case eLESS_THAN:
            switch ( expresion->simboloTipo ) {
                case vINT:
                    return operacionInt( expresion->nodoIzquierda , tablaSimbolo ) < operacionInt( expresion->nodoDerecha  , tablaSimbolo );
                case vFLOAT:
                    return operacionFloat( expresion->nodoIzquierda , tablaSimbolo ) < operacionFloat( expresion->nodoDerecha  , tablaSimbolo );
                default:
                    return 0;
            }
        case eEQUAL_TO:
            switch ( expresion->simboloTipo ) {
                case vINT:
                    return operacionInt( expresion->nodoIzquierda , tablaSimbolo ) == operacionInt( expresion->nodoDerecha  , tablaSimbolo );
                case vFLOAT:
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
        case nSEMICOLON:
            interpretaArbol( tree->nodoIzq, tablaSimbolo );
            interpretaArbol( tree->nodoDer, tablaSimbolo );
            break;
        case nASSIGNMENT:
            switch ( tree->simboloTipo ) {
                case vINT:
                    setSimboloInt( tablaSimbolo , tree->value.valID , operacionInt( tree->expr , tablaSimbolo ) );
                    break;
                case vFLOAT:
                    setSimboloFloat( tablaSimbolo , tree->value.valID , operacionFloat( tree->expr , tablaSimbolo ) );
                    break;
                default:
                    return 0;
                break;
            }
            break;
        case nIF:
            if ( booleanos( tree->expresion , tablaSimbolo ) ) {
                interpretaArbol( tree->thenOptStmts , tablaSimbolo );
            }
            break;  
        case nIFELSE:
            if ( booleanos( tree->expresion , tablaSimbolo ) ) {
                interpretaArbol( tree->thenOptStmts , tablaSimbolo );
            }
            else{
                interpretaArbol( tree->elseOptStmts , tablaSimbolo );
            }
            break;
        case nWHILE:
            while ( booleanos( tree->expresion , tablaSimbolo ) ) {
                interpretaArbol( tree->doOptStmts , tablaSimbolo );
            }
            break;

        case nREPEAT:
            do{
                interpretaArbol( tree->doOptStmts , tablaSimbolo );
            }
            while ( booleanos( tree->expresion , tablaSimbolo ) );
            break;

        case nREAD:
            switch ( getTipoSimbolo( tablaSimbolo , tree->value.valID ) ) {
                case vINT: {
                    printf( "read value for %s: ", tree->value.valID );
                    int value;
                    scanf( "%d" , &value );
                    printf( "\n" );
                    setSimboloInt( tablaSimbolo, tree->value.valID , value );
                    break;
                }
                case vFLOAT: {
                    float value;
                    printf( "read value for %s: ", tree->value.valID );
                    scanf( "%f" , &value );
                    printf( "\n" );
                    setSimboloFloat( tablaSimbolo, tree->value.valID , value );
                    break;
                }
            }
            break;
        case nPRINT:
            switch ( tree->expr->simboloTipo ) {
                case vINT:
                    printf ( "%d\n" , operacionInt( tree->expr , tablaSimbolo ) );
                break;
                case vFLOAT:
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