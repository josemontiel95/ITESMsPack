#include "syntaxTree.h"
#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Node *allocateNode() {
    Node *node = malloc( sizeof( Node ) );
    if ( node == NULL ) {
        printf( "Error: Memory allocation failed. Program will be terminated\n" );
        exit(1);
    }
    return node;
}

//creacion de nodos---------------------------------------------------------------------------

Node * createInteger( int value ) {
    Node *nInteger = allocateNode();
    nInteger->tipo          = nVALUE;
    nInteger->operationType = oINTEGER;
    nInteger->symbolType    = vINT;
    nInteger->value.iValue  = value;
    return nInteger;
}

Node * createFloat( float value ) {
    Node *nFloat = allocateNode();
    nFloat->tipo          = nVALUE;
    nFloat->operationType = oFLOAT;
    nFloat->symbolType    = vFLOAT;
    nFloat->value.fValue  = value;
    return nFloat;
}

Node *createMinus( Node *rightOperand ) {
    Node *nMinus = allocateNode();
    nMinus->tipo = nVALUE;
    switch ( rightOperand->symbolType ) {
        case vINT:
            nMinus->symbolType    = vINT;
            nMinus->operationType = oINTEGER;
            nMinus->value.iValue  = -1;
            break;
        
        case vFLOAT:
            nMinus->symbolType    = vFLOAT;
            nMinus->operationType = oFLOAT;
            nMinus->value.fValue  = -1.0;
            break; 
    }
    return nMinus;
}

Node * createSymbol( char  *value , Variable **symbolTable) {
    Node *nSymbol = allocateNode();
    nSymbol->tipo          = nVALUE;
    nSymbol->operationType = oID;
    nSymbol->symbolType    = getTipoSimbolo( symbolTable , value );
    nSymbol->value.idValue = value;
    return nSymbol;
}

Node *createSymbolType( VarTipo symbolType ) {
    Node *nSymbolType = allocateNode();
    nSymbolType->tipo       = nSYMBOLTYPE;
    nSymbolType->symbolType = symbolType;
    return nSymbolType;
}

VarTipo assertSymbolType( VarTipo leftOperand , VarTipo rightOperand ) {
    if ( leftOperand == rightOperand ) {
        return leftOperand;
    } else { 
        printf( "Error: Types do not match. Program will be terminated.\n" );
        exit(1);
    }
}

Node *createOperation( OperationType operationType , Node *leftOperand , Node *rightOperand) {
    Node *nOperation = allocateNode();
    nOperation->tipo          = nOPERATION;
    nOperation->symbolType    = assertSymbolType( leftOperand->symbolType , rightOperand->symbolType ); //if assert fails compiler will terminate
    nOperation->operationType = operationType;
    nOperation->leftOperand   = leftOperand;
    nOperation->rightOperand  = rightOperand;
    return nOperation;
}

Node *createExpresion( ExpresionType expresionType , Node *leftOperand , Node *rightOperand) {
    Node *nExpresion = allocateNode();
    nExpresion->tipo = nEXPRESION;
    nExpresion->symbolType = assertSymbolType( leftOperand->symbolType , rightOperand->symbolType ); //if assert fails compiler will terminate
    nExpresion->expresionType = expresionType;
    nExpresion->leftOperand = leftOperand;
    nExpresion->rightOperand = rightOperand;
    return nExpresion;
}

Node *createSemiColon( Node *leftStatement , Node *rightStatement ) {
    Node *nSemicolon = allocateNode();
    nSemicolon->tipo = nSEMICOLON;
    nSemicolon->leftStatement = leftStatement;
    nSemicolon->rightStatement = rightStatement;
    return nSemicolon;
}

Node *createAssignment( char *identifier , Node *expr , Variable **symbolTable ) {
    Node *nAssignment = allocateNode();
    nAssignment->tipo = nASSIGNMENT;
    nAssignment->symbolType = assertSymbolType( expr->symbolType , getTipoSimbolo( symbolTable , identifier ) );
    nAssignment->expr = expr;
    nAssignment->value.idValue = identifier;
    return nAssignment;
}

Node *createIfStatement( Node *expresion , Node *thenOptStmts ) {
    Node *nIfStatement = allocateNode();
    nIfStatement->tipo         = nIF;
    nIfStatement->expresion    = expresion;
    nIfStatement->thenOptStmts = thenOptStmts;
    return nIfStatement;
}

Node *createIfElseStatement( Node *expresion , Node *thenOptStmts, Node *elseOptStmts ) {
    Node *nIfElseStatement = allocateNode();
    nIfElseStatement->tipo         = nIFELSE;
    nIfElseStatement->expresion    = expresion;
    nIfElseStatement->thenOptStmts = thenOptStmts;
    nIfElseStatement->elseOptStmts = elseOptStmts;
    return nIfElseStatement;
}


Node *createWhileStatement( Node *expresion , Node *doOptStmts ) {
    Node *nWhileStatement = allocateNode();
    nWhileStatement->tipo       = nWHILE;
    nWhileStatement->expresion  = expresion;
    nWhileStatement->doOptStmts = doOptStmts;
    return nWhileStatement;
}

Node *createRepeatStatement( Node *expresion , Node *doOptStmts ) {
    Node *nRepeatStatement = allocateNode();
    nRepeatStatement->tipo       = nREPEAT;
    nRepeatStatement->expresion  = expresion;
    nRepeatStatement->doOptStmts = doOptStmts;
    return nRepeatStatement;
}

Node *createForStatement( char *identifier , Node *expr , Node *stepExpr , Node *untilExpr , Node *doOptStmts ) {
    Node *nForStatement = allocateNode();
    nForStatement->tipo          = nFOR;
    nForStatement->value.idValue = identifier;
    nForStatement->expr          = expr;
    nForStatement->stepExpr      = stepExpr;
    nForStatement->untilExpr     = untilExpr;
    nForStatement->doOptStmts    = doOptStmts;
    return nForStatement;

}

Node *createReadStatement( char *identifier ) {
    Node *nReadStatement = allocateNode();
    nReadStatement->tipo          = nREAD;
    nReadStatement->value.idValue = identifier;
    return nReadStatement;
}

Node *createPrintStatement( Node *expr ) {
    Node *nPrintStatement = allocateNode();
    nPrintStatement->tipo = nPRINT;
    nPrintStatement->expr = expr;
    return nPrintStatement;
}


//Interprete------------------------------------------------------------
int evaluateIntegerOperation( Node *operation , Variable **symbolTable) {
    switch ( operation->operationType ) {
        case oINTEGER:
            return operation->value.iValue;
        case oID:
            return getSimboloInt( symbolTable , operation->value.idValue);
        case oSUM:
            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) + evaluateIntegerOperation( operation->rightOperand , symbolTable );
        case oSUB:
            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) - evaluateIntegerOperation( operation->rightOperand , symbolTable );
        case oMULT:
            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) * evaluateIntegerOperation( operation->rightOperand , symbolTable );
        case oDIV:
            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) / evaluateIntegerOperation( operation->rightOperand , symbolTable );
        default:
            return 0;
    }
}

float evaluateFloatOperation( Node *operation , Variable **symbolTable) {
    switch (operation->operationType) {
        case oFLOAT:
            return operation->value.fValue;
        case oID:
            return getSimboloFloat( symbolTable , operation->value.idValue);
        case oSUM:
            return evaluateFloatOperation( operation->leftOperand , symbolTable ) + evaluateFloatOperation( operation->rightOperand , symbolTable );
        case oSUB:
            return evaluateFloatOperation( operation->leftOperand , symbolTable ) - evaluateFloatOperation( operation->rightOperand , symbolTable );
        case oMULT:
            return evaluateFloatOperation( operation->leftOperand , symbolTable ) * evaluateFloatOperation( operation->rightOperand , symbolTable );
        case oDIV:
            return evaluateFloatOperation( operation->leftOperand , symbolTable ) / evaluateFloatOperation( operation->rightOperand , symbolTable );
        default:
            return 0;
    }
}

int evaluateExpresion(Node *expresion , Variable **symbolTable ) {
    switch ( expresion->expresionType ) {
        case eGREATER_THAN:
            switch ( expresion->symbolType ) {
                case vINT:
                    return evaluateIntegerOperation( expresion->leftOperand , symbolTable ) > evaluateIntegerOperation( expresion->rightOperand  , symbolTable );
                case vFLOAT:
                    return evaluateFloatOperation( expresion->leftOperand , symbolTable ) > evaluateFloatOperation( expresion->rightOperand  , symbolTable );
                default:
                    return 0;
            }
        case eLESS_THAN:
            switch ( expresion->symbolType ) {
                case vINT:
                    return evaluateIntegerOperation( expresion->leftOperand , symbolTable ) < evaluateIntegerOperation( expresion->rightOperand  , symbolTable );
                case vFLOAT:
                    return evaluateFloatOperation( expresion->leftOperand , symbolTable ) < evaluateFloatOperation( expresion->rightOperand  , symbolTable );
                default:
                    return 0;
            }
        case eEQUAL_TO:
            switch ( expresion->symbolType ) {
                case vINT:
                    return evaluateIntegerOperation( expresion->leftOperand , symbolTable ) == evaluateIntegerOperation( expresion->rightOperand  , symbolTable );
                case vFLOAT:
                    return evaluateFloatOperation( expresion->leftOperand , symbolTable ) == evaluateFloatOperation( expresion->rightOperand  , symbolTable );
                default:
                    return 0;
            }
        default:
            return 0;
    }
}

int resolveTree( Node *tree , Variable **symbolTable) {
    switch ( tree->tipo ) {
        case nSEMICOLON:
            resolveTree( tree->leftStatement, symbolTable );
            resolveTree( tree->rightStatement, symbolTable );
            break;
        case nASSIGNMENT:
            switch ( tree->symbolType ) {
                case vINT:
                    setSimboloInt( symbolTable , tree->value.idValue , evaluateIntegerOperation( tree->expr , symbolTable ) );
                    break;
                case vFLOAT:
                    setSimboloFloat( symbolTable , tree->value.idValue , evaluateFloatOperation( tree->expr , symbolTable ) );
                    break;
                default:
                    return 0;
                break;
            }
            break;
        case nIF:
            if ( evaluateExpresion( tree->expresion , symbolTable ) ) {
                resolveTree( tree->thenOptStmts , symbolTable );
            }
            break;  
        case nIFELSE:
            if ( evaluateExpresion( tree->expresion , symbolTable ) ) {
                resolveTree( tree->thenOptStmts , symbolTable );
            }
            else{
                resolveTree( tree->elseOptStmts , symbolTable );
            }
            break;
        case nWHILE:
            while ( evaluateExpresion( tree->expresion , symbolTable ) ) {
                resolveTree( tree->doOptStmts , symbolTable );
            }
            break;

        case nREPEAT:
            do{
                resolveTree( tree->doOptStmts , symbolTable );
            }
            while ( evaluateExpresion( tree->expresion , symbolTable ) );
            break;

        case nREAD:
            switch ( getTipoSimbolo( symbolTable , tree->value.idValue ) ) {
                case vINT: {
                    printf( "read value for %s: ", tree->value.idValue );
                    int value;
                    scanf( "%d" , &value );
                    printf( "\n" );
                    setSimboloInt( symbolTable, tree->value.idValue , value );
                    break;
                }
                case vFLOAT: {
                    float value;
                    printf( "read value for %s: ", tree->value.idValue );
                    scanf( "%f" , &value );
                    printf( "\n" );
                    setSimboloFloat( symbolTable, tree->value.idValue , value );
                    break;
                }
            }
            break;
        case nPRINT:
            switch ( tree->expr->symbolType ) {
                case vINT:
                    printf ( "%d\n" , evaluateIntegerOperation( tree->expr , symbolTable ) );
                break;
                case vFLOAT:
                    printf ( "%f\n" , evaluateFloatOperation( tree->expr , symbolTable ) );
                break;
            }
            break;
        default:
            return 1;
            break;
    }
    return 1;
}