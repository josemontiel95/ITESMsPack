#ifndef __SYNTAX_TREE_H__
#define __SYNTAX_TREE_H__
#include "symbolTable.h"

typedef enum tagNodeType {
    nVALUE,
    nSYMBOLTYPE,
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
} NodeType;

typedef enum tagOperationType {
    oINTEGER,
    oFLOAT,
    oID,
    oSUM,
    oSUB,
    oDIV,
    oMULT
} OperationType;

typedef enum tagExpresionType {
    eGREATER_THAN,
    eLESS_THAN,
    eEQUAL_TO
} ExpresionType;

typedef struct tagNode {  
    NodeType tipo; 

    /********** EXPR | TERM | FACTOR components **********/
    OperationType operationType; 
    VarTipo valueType;
    
    union {
        int iValue;
        float fValue; 
        char *idValue;
    } value;
    
    struct tagNode *leftOperand; 
    struct tagNode *rightOperand; 

    /********** EXPRESION components **********/
    ExpresionType expresionType;
    
    /********** SEMICOLON components **********/
    struct tagNode *leftStatement;
    struct tagNode *rightStatement;

    /********** DEC Components **********/
    VarTipo symbolType;

    /********** ASSIGNMENT STMT Components **********/
    struct tagNode *expr;

    /********** IF STMT Components **********/
    struct tagNode *expresion;
    struct tagNode *thenOptStmts;
    struct tagNode *elseOptStmts;

    /********** WHILE STMT Components **********/
    struct tagNode *doOptStmts;

    /********** FOR STMT Components **********/
    struct tagNode *assignment_stmt; 
    struct tagNode *stepExpr; 
    struct tagNode *untilExpr;
} Node;


Node *createInteger( int value );
Node *createFloat( float value );
Node *createMinus( Node *rightOperand );
Node *createSymbol( char *value , Variable **symbolTable );
Node *createSymbolType( VarTipo symbolType );
VarTipo assertSymbolType( VarTipo leftOperand , VarTipo rightOperand );
Node *createOperation( OperationType operationType , Node *leftOperand , Node *rightOperand);
Node *createExpresion( ExpresionType expresionType , Node *leftOperand , Node *rightOperand );
Node *createSemiColon( Node *leftStatement , Node *rightStatement );
Node *createAssignment( char *identifier , Node *expr , Variable **symbolTable );
Node *createIfStatement( Node *expresion , Node *thenOptStmts );
Node *createIfElseStatement( Node *expresion , Node *thenOptStmts, Node *elseOptStmts );
Node *createWhileStatement( Node *expresion , Node *doOptStmts );
Node *createRepeatStatement( Node *expresion , Node *doOptStmts );
Node *createForStatement( char *identifier , Node *expr , Node *stepExpr , Node *untilExpr , Node *doOptStmts );
Node *createReadStatement( char *identifier );
Node *createPrintStatement( Node *expr );
int evaluateIntegerOperation( Node *operation , Variable **symbolTable );
float evaluateFloatOperation( Node *operation , Variable **symbolTable );
int evaluateExpresion(Node *expresion , Variable **symbolTable );
void assignSymbol( char *identifier , Node *expr , Variable **symbolTable , VarTipo symbolType);
int resolveTree( Node *tree , Variable **symbolTable);

#endif