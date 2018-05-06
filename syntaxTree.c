/**
 * syntaxTree.c
 * Implementation of the methods to build, manage and resolve a syntax tree
 * @author Jose Pablo Ortiz Lack
 */
#include "syntaxTree.h"
#include "symbolTable.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Allocates space for the Node
 * @return The Node or NULL if there is not enough memory
 */
static Node *allocateNode() {

    Node *node = malloc( sizeof( Node ) );

    if ( node == NULL ) {

        printf( "Error: Memory allocation failed. Program will be terminated\n" );
        exit(1);

    }

    return node;
}

Node * createInteger( int value ) {

    Node *nInteger = allocateNode();

    nInteger->type          = nVALUE;

    nInteger->operationType = oINTEGER;
    nInteger->symbolType    = sINTEGER;
    nInteger->value.iValue  = value;
    
    return nInteger;

}

Node * createFloat( float value ) {

    Node *nFloat = allocateNode();

    nFloat->type          = nVALUE;

    nFloat->operationType = oFLOAT;
    nFloat->symbolType    = sFLOAT;
    nFloat->value.fValue  = value;
    
    return nFloat;

}

Node *createMinus( Node *rightOperand ) {

    Node *nMinus = allocateNode();

    nMinus->type = nVALUE;

    switch ( rightOperand->symbolType ) {

        case sINTEGER:

            nMinus->symbolType    = sINTEGER;
            nMinus->operationType = oINTEGER;
            nMinus->value.iValue  = -1;

        break;
        
        case sFLOAT:

            nMinus->symbolType    = sFLOAT;
            nMinus->operationType = oFLOAT;
            nMinus->value.fValue  = -1.0;

        break;

    }

    return nMinus;

}

Node * createSymbol( char  *value , Symbol **symbolTable) {

    Node *nSymbol = allocateNode();

    nSymbol->type          = nVALUE;

    nSymbol->operationType = oID;
    nSymbol->symbolType    = getSymbolType( symbolTable , value );
    nSymbol->value.idValue = value;
    
    return nSymbol;

}

Node *createSymbolType( SymbolType symbolType ) {

    Node *nSymbolType = allocateNode();

    nSymbolType->type       = nSYMBOLTYPE;

    nSymbolType->symbolType = symbolType;

    return nSymbolType;
}

SymbolType assertSymbolType( SymbolType leftOperand , SymbolType rightOperand ) {

    if ( leftOperand == rightOperand ) { //both operand symbol types match

        return leftOperand;

    } else { //operands do not match, print error and exit program

        printf( "Error: Types do not match. Program will be terminated.\n" );

        exit(1); //We exit the program as there was an error
    }
}

Node *createOperation( OperationType operationType , Node *leftOperand , Node *rightOperand) {

    Node *nOperation = allocateNode();

    nOperation->type          = nOPERATION;

    nOperation->symbolType    = assertSymbolType( leftOperand->symbolType , rightOperand->symbolType ); //if assert fails compiler will terminate
    nOperation->operationType = operationType;
    nOperation->leftOperand   = leftOperand;
    nOperation->rightOperand  = rightOperand;

    return nOperation;

}

Node *createExpresion( ExpresionType expresionType , Node *leftOperand , Node *rightOperand) {

    Node *nExpresion = allocateNode();

    nExpresion->type          = nEXPRESION;

    nExpresion->symbolType    = assertSymbolType( leftOperand->symbolType , rightOperand->symbolType ); //if assert fails compiler will terminate
    nExpresion->expresionType = expresionType;
    nExpresion->leftOperand   = leftOperand;
    nExpresion->rightOperand  = rightOperand;

    return nExpresion;

}

Node *createSemiColon( Node *leftStatement , Node *rightStatement ) {

    Node *nSemicolon = allocateNode();

    nSemicolon->type           = nSEMICOLON;

    nSemicolon->leftStatement  = leftStatement;
    nSemicolon->rightStatement = rightStatement;

    return nSemicolon;

}

Node *createAssignment( char *identifier , Node *expr , Symbol **symbolTable ) {

    Node *nAssignment = allocateNode();

    nAssignment->type          = nASSIGNMENT;

    nAssignment->symbolType    = assertSymbolType( expr->symbolType , getSymbolType( symbolTable , identifier ) );
    nAssignment->expr          = expr;
    nAssignment->value.idValue = identifier;

    return nAssignment;

}

Node *createIfStatement( Node *expresion , Node *thenOptStmts ) {

    Node *nIfStatement = allocateNode();

    nIfStatement->type         = nIF;

    nIfStatement->expresion    = expresion;
    nIfStatement->thenOptStmts = thenOptStmts;

    return nIfStatement;

}

Node *createWhileStatement( Node *expresion , Node *doOptStmts ) {

    Node *nWhileStatement = allocateNode();

    nWhileStatement->type       = nWHILE;

    nWhileStatement->expresion  = expresion;
    nWhileStatement->doOptStmts = doOptStmts;

    return nWhileStatement;

}

Node *createForStatement( char *identifier , Node *expr , Node *stepExpr , Node *untilExpr , Node *doOptStmts ) {

    Node *nForStatement = allocateNode();

    nForStatement->type          = nFOR;

    nForStatement->value.idValue = identifier;
    nForStatement->expr          = expr;
    nForStatement->stepExpr      = stepExpr;
    nForStatement->untilExpr     = untilExpr;
    nForStatement->doOptStmts    = doOptStmts;

    return nForStatement;

}

Node *createReadStatement( char *identifier ) {

    Node *nReadStatement = allocateNode();

    nReadStatement->type          = nREAD;

    nReadStatement->value.idValue = identifier;

    return nReadStatement;
}

Node *createPrintStatement( Node *expr ) {

    Node *nPrintStatement = allocateNode();

    nPrintStatement->type = nPRINT;

    nPrintStatement->expr = expr;

    return nPrintStatement;

}

int evaluateIntegerOperation( Node *operation , Symbol **symbolTable) {

    switch ( operation->operationType ) {
        
        case oINTEGER:

            return operation->value.iValue;

        case oID:

            return getIntegerSymbolValue( symbolTable , operation->value.idValue);
        
        case oSUM:

            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) + evaluateIntegerOperation( operation->rightOperand , symbolTable );
        
        case oSUB:

            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) - evaluateIntegerOperation( operation->rightOperand , symbolTable );
        
        case oMULT:

            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) * evaluateIntegerOperation( operation->rightOperand , symbolTable );
        
        case oDIV:

            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) / evaluateIntegerOperation( operation->rightOperand , symbolTable );
        
        default:
            // should not be here
            return 0;
    
    }

}

float evaluateFloatOperation( Node *operation , Symbol **symbolTable) {

    switch (operation->operationType) {
        
        case oFLOAT:

            return operation->value.fValue;

        case oID:

            return getFloatSymbolValue( symbolTable , operation->value.idValue);
        
        case oSUM:

            return evaluateFloatOperation( operation->leftOperand , symbolTable ) + evaluateFloatOperation( operation->rightOperand , symbolTable );
        
        case oSUB:

            return evaluateFloatOperation( operation->leftOperand , symbolTable ) - evaluateFloatOperation( operation->rightOperand , symbolTable );
        
        case oMULT:

            return evaluateFloatOperation( operation->leftOperand , symbolTable ) * evaluateFloatOperation( operation->rightOperand , symbolTable );
        
        case oDIV:

            return evaluateFloatOperation( operation->leftOperand , symbolTable ) / evaluateFloatOperation( operation->rightOperand , symbolTable );
        
        default:
            // should not be here
            return 0;
    
    }

}

int evaluateExpresion(Node *expresion , Symbol **symbolTable ) {

    switch ( expresion->expresionType ) {

        case eGREATER_THAN:

            switch ( expresion->symbolType ) {

                case sINTEGER:

                    return evaluateIntegerOperation( expresion->leftOperand , symbolTable ) > evaluateIntegerOperation( expresion->rightOperand  , symbolTable );

                case sFLOAT:

                    return evaluateFloatOperation( expresion->leftOperand , symbolTable ) > evaluateFloatOperation( expresion->rightOperand  , symbolTable );

                default:
                    // should not be here
                    return 0;

            }

        case eLESS_THAN:

            switch ( expresion->symbolType ) {

                case sINTEGER:

                    return evaluateIntegerOperation( expresion->leftOperand , symbolTable ) < evaluateIntegerOperation( expresion->rightOperand  , symbolTable );

                case sFLOAT:

                    return evaluateFloatOperation( expresion->leftOperand , symbolTable ) < evaluateFloatOperation( expresion->rightOperand  , symbolTable );

                default:
                    // should not be here
                    return 0;

            }

        case eEQUAL_TO:

            switch ( expresion->symbolType ) {

                case sINTEGER:

                    return evaluateIntegerOperation( expresion->leftOperand , symbolTable ) == evaluateIntegerOperation( expresion->rightOperand  , symbolTable );

                case sFLOAT:

                    return evaluateFloatOperation( expresion->leftOperand , symbolTable ) == evaluateFloatOperation( expresion->rightOperand  , symbolTable );

                default:
                    // should not be here
                    return 0;

            }

        default:
            // should not be here
            return 0;

    }
}

int resolveTree( Node *tree , Symbol **symbolTable) {
    
    switch ( tree->type ) {

        case nSEMICOLON:
            
            resolveTree( tree->leftStatement, symbolTable );
            
            resolveTree( tree->rightStatement, symbolTable );

        break;

        case nASSIGNMENT:

            switch ( tree->symbolType ) {

                case sINTEGER:
                    
                    setIntegerSymbolValue( symbolTable , tree->value.idValue , evaluateIntegerOperation( tree->expr , symbolTable ) );
                
                break;
                
                case sFLOAT:
                    
                    setFloatSymbolValue( symbolTable , tree->value.idValue , evaluateFloatOperation( tree->expr , symbolTable ) );
                
                break;

                default:

                    //should not be here
                    return 0;

                break;
            
            }

        break;

        case nIF:
            
            if ( evaluateExpresion( tree->expresion , symbolTable ) ) {

                resolveTree( tree->thenOptStmts , symbolTable );

            }
        
        break;

        case nWHILE:
            
            while ( evaluateExpresion( tree->expresion , symbolTable ) ) {

                resolveTree( tree->doOptStmts , symbolTable );

            }
        
        break;

        case nFOR: {
            
            //Check that the symbol and the expr have the same type
            SymbolType symbolType = assertSymbolType( getSymbolType( symbolTable , tree->value.idValue) , tree->expr->symbolType );
            
            //assert that the stepExpr and unitlExpr have the same symbol type as the symbol
            assertSymbolType( symbolType , tree->stepExpr->symbolType );
            assertSymbolType( symbolType , tree->untilExpr->symbolType );

            switch (symbolType) {

                case sINTEGER: {

                    //resolve expr and assign to symbol
                    int integerStart = evaluateIntegerOperation( tree->expr , symbolTable );
                    int integerStep  = evaluateIntegerOperation( tree->stepExpr , symbolTable );
                    int integerUntil = evaluateIntegerOperation( tree->untilExpr , symbolTable );
                    int integerIterator;
                    setIntegerSymbolValue( symbolTable , tree->value.idValue , integerStart );

                    if ( integerStep < 0 ) {
                        
                        for ( integerIterator = integerStart ; integerIterator >= integerUntil ; integerIterator += integerStep ) {

                            setIntegerSymbolValue( symbolTable , tree->value.idValue , integerIterator); //updates the symbol value with the step value
                            
                            resolveTree( tree-> doOptStmts , symbolTable );

                        }

                        setIntegerSymbolValue( symbolTable, tree->value.idValue , integerIterator - integerStep); //updates the symbol value with the step value

                    } else if ( integerStep > 0 ) {
                        
                        for ( integerIterator = integerStart ; integerIterator <= integerUntil ; integerIterator += integerStep ) {

                            setIntegerSymbolValue( symbolTable , tree->value.idValue , integerIterator); //updates the symbol value with the step value
                            
                            resolveTree( tree-> doOptStmts , symbolTable );
                        }

                         setIntegerSymbolValue( symbolTable , tree->value.idValue , integerIterator - integerStep); //updates the symbol value with the step value

                    } else {

                        printf( "Error: Step cannot be 0.0 . Program will be terminated.\n" );
                        exit(1);
                    }

                    break;
                }

                case sFLOAT: {

                    //resolve expr and assign to symbol
                    float floatStart = evaluateFloatOperation( tree->expr , symbolTable );
                    float floatStep  = evaluateFloatOperation( tree->stepExpr , symbolTable );
                    float floatUntil = evaluateFloatOperation( tree->untilExpr , symbolTable );
                    float floatIterator;
                    
                    setFloatSymbolValue( symbolTable, tree->value.idValue , floatStart );
                    if ( floatStep < 0 ) {
                        
                        for ( floatIterator = floatStart ; floatIterator >= floatUntil ; floatIterator += floatStep ) {

                            setFloatSymbolValue( symbolTable, tree->value.idValue , floatIterator); //updates the symbol value with the step value
                            
                            resolveTree( tree-> doOptStmts , symbolTable );

                        }

                        setFloatSymbolValue( symbolTable, tree->value.idValue , floatIterator - floatStep); //updates the symbol value by removing the excess step

                    } else if ( floatStep > 0 ) {
                        
                        for (floatIterator = floatStart ; floatIterator <= floatUntil ; floatIterator += floatStep ) {
  
                            setFloatSymbolValue( symbolTable, tree->value.idValue , floatIterator ); //updates the symbol value with the step value
                            
                            resolveTree( tree-> doOptStmts , symbolTable );
                        }

                        setFloatSymbolValue( symbolTable, tree->value.idValue , floatIterator - floatStep ); //updates the symbol by removing the excess step

                    } else {

                        printf( "Error: Step cannot be 0.0 . Program will be terminated.\n" );
                        exit(1);
                    } 

                    break;
                }

            }

            break;
        }

        case nREAD:

            switch ( getSymbolType( symbolTable , tree->value.idValue ) ) {

                case sINTEGER: {
                    
                    printf( "read value for %s: ", tree->value.idValue );
                    
                    int value;
                    
                    scanf( "%d" , &value );
                    
                    printf( "\n" );

                    setIntegerSymbolValue( symbolTable, tree->value.idValue , value );

                    break;
                }

                case sFLOAT: {

                    float value;

                    printf( "read value for %s: ", tree->value.idValue );
                    scanf( "%f" , &value );
                    
                    printf( "\n" );
                    
                    setFloatSymbolValue( symbolTable, tree->value.idValue , value );

                    break;
                }
            }

        break;

        case nPRINT:

            switch ( tree->expr->symbolType ) {

                case sINTEGER:
                
                    printf ( "%d\n" , evaluateIntegerOperation( tree->expr , symbolTable ) );

                break;

                case sFLOAT:

                    printf ( "%f\n" , evaluateFloatOperation( tree->expr , symbolTable ) );

                break;
            }

        break;

        default: //no statements

            return 1;

        break;

    }

    
    return 1;

}

//end syntaxTree.c