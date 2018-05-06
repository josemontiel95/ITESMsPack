/**
 * syntaxTree.h
 * Definition of the structure to build a syntax tree
 * @author Jose Pablo Ortiz Lack
 */
#ifndef __SYNTAX_TREE_H__
#define __SYNTAX_TREE_H__

#include "symbolTable.h"
/**
 * @brief The node type
 */
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
    nPRINT
    
} NodeType;

/**
 * @brief The operation type
 */
typedef enum tagOperationType {

    oINTEGER,
    oFLOAT,
    oID,
    oSUM,
    oSUB,
    oDIV,
    oMULT

} OperationType;

/**
 * @brief The expresion type
 */
typedef enum tagExpresionType {

    eGREATER_THAN,
    eLESS_THAN,
    eEQUAL_TO

} ExpresionType;

/**
 * @brief The syntax tree structure
 */
typedef struct tagNode {
  
    NodeType type; //Type of node (see NodeType ENUM)

    /********** EXPR | TERM | FACTOR components **********/
    OperationType operationType; //Type of operation (see OperationType ENUM)
    SymbolType valueType; //type of value (see SymbolType ENUM) of the expresion or value
    
    union {

        int iValue; //integer value
        float fValue; //float value
        char *idValue; //symbol value

    } value; //value (if Operand)
    
    struct tagNode *leftOperand; //left operand of the operation
    struct tagNode *rightOperand; //right operand of the operation

    /********** EXPRESION components **********/
    ExpresionType expresionType;
    //valueType, leftOperand and rightOperand reused from EXPR | TERM | FACTOR components

    /********** SEMICOLON components **********/
    struct tagNode *leftStatement; //left statement of the semicolon
    struct tagNode *rightStatement; //right statement of the semicolon

    /********** DEC Components **********/
    SymbolType symbolType; //type of the simbol
    //identifier reused from EXPR | TERM | FACTOR component value.idValue

    /********** ASSIGNMENT STMT Components **********/
    //identifier reused from DEC Components
    struct tagNode *expr; //operation to assign

    /********** IF STMT Components **********/
    struct tagNode *expresion; //conditional expresion to be evaluated
    struct tagNode *thenOptStmts; //optional statements to be executed if expresion is true

    /********** WHILE STMT Components **********/
    //expresion reused from IF STMT components
    struct tagNode *doOptStmts; //optional statements to be executed in a loop while a condition is met

    /********** FOR STMT Components **********/
    struct tagNode *assignment_stmt; //assignment statement (View ASSIGNMENT STMT components)
    struct tagNode *stepExpr; //Step expresion to be executed in each loop (view EXPR components)
    struct tagNode *untilExpr; //Stop expr to be met (e.g 7, 14.5, x where x := 10) (view EXPR components)
    //do_opt_stmts reused from WHILE STMT components

    /********** READ STMT Components **********/
    //identifier reused from EXPR | TERM | FACTOR component value.idValue

    /********** WRITE STMT Components **********/
    //expr reused from ASSIGNMENT STMT components

} Node;

/**
 * @brief creates integer Node
 * @param value value of the integer
 * @return integer node
 */
Node *createInteger( int value );

/**
 * @brief creates float Node
 * @param value value of the float
 * @return float node
 */
Node *createFloat( float value );

/**
 * @brief creates a minus one node to multiply against a right operand, of either integer or float type
 * @param rightOperand operand against which the minus node will be multiplied
 * @return integer or float node with a value of minus one, depending on the right operand
 */
Node *createMinus( Node *rightOperand );

/**
 * @brief creates symbol Node
 * @param value value of the symbol
 * @param symbolTable symbol table of the compiler
 * @return symbol node
 */
Node *createSymbol( char *value , Symbol **symbolTable );

/**
 * @brief creates a symbol type Node
 * param symbolType type of symbol
 * @returns symbol type node
 */
Node *createSymbolType( SymbolType symbolType );

/**
 * @brief verifies that the symbol types of two operands match. If they don't match an error message is sent and the program is closed
 * @param leftOperand tye symbol type of the left operand
 * @param rightOperand tye symbol type of the right operand
 * @return the type of symbol of both expresions if they match
 */
SymbolType assertSymbolType( SymbolType leftOperand , SymbolType rightOperand );

/**
 * @brief creates operation tree
 * @param operationType type of operation from the tree
 * @param leftOperand the left operand of the operation
 * @param rightOperand the right operand of the operation
 * @return operation tree
 */
Node *createOperation( OperationType operationType , Node *leftOperand , Node *rightOperand);

/**
 * @brief creates expresion tree
 * @param expresionType type of expresion from the tree
 * @param leftOperand the left operand of the expresion
 * @param rightOperand the right operand of the expresion
 * @return expresion tree
 */
Node *createExpresion( ExpresionType expresionType , Node *leftOperand , Node *rightOperand );

/**
 * @brief creates semicolon tree
 * @param leftStatement the left statement of the semicolon
 * @param rightStatement the right statement of the semicolon
 * @return semicolon tree
 */
Node *createSemiColon( Node *leftStatement , Node *rightStatement );

/**
 * @brief creates assignment statement tree
 * @param identifier identifier of the symbol to be assigned
 * @param expr operation to be assigned to the symbol
 * @param symbolTable symbol table of the compiler
 * @return assignment statement tree
 */
Node *createAssignment( char *identifier , Node *expr , Symbol **symbolTable );

/**
 * @brief creates if statement tree
 * @param expresion conditional expresion to be resolved
 * @param then_opt_stmts optional statements to be resolved if condition is proven true
 * @return if statement tree
 */
Node *createIfStatement( Node *expresion , Node *thenOptStmts );

/**
 * @brief creates if statement tree
 * @param expresion conditional expresion to be resolved
 * @param do_opt_stmts optional statements to be executed in a loop while condition is proven true
 * @return while statement tree
 */
Node *createWhileStatement( Node *expresion , Node *doOptStmts );

/**
 * @brief creates for loop statement tree
 * @param identifier identifier for the assignment statement
 * @param expr expresion to be assigned to the identifier
 * @param stepExpr expresion to be resolved for the for loop steps
 * @param untilExpr expresion to be resolved as the stop expresion of the for loop
 * @param doOptStmts optional statements to be executed inside the for loop
 * @return for statement tree
 */
Node *createForStatement( char *identifier , Node *expr , Node *stepExpr , Node *untilExpr , Node *doOptStmts );

/**
 * @brief creates read statement tree
 * @param identifier identifier for the assignment statement
 * @return read statement tree
 */
Node *createReadStatement( char *identifier );

/**
 * @brief creates print statement tree
 * @param expr expr to be resolved and printed
 * @return print statement tree
 */
Node *createPrintStatement( Node *expr );

/**
 * @brief calculates the result of of an integer Operation
 * @param operation operation to be calculated
 * @param symbolTable the symbolTable of the compiler
 * @return integer value result of the operation
 */
int evaluateIntegerOperation( Node *operation , Symbol **symbolTable );

/**
 * @brief calculates the result of a float operation
 * @param operation operation to be calculated
 * @param symbolTable the symbolTable of the compiler
 * @return float value result of the operation
 */
float evaluateFloatOperation( Node *operation , Symbol **symbolTable );

/**
 * @brief evaluates an Expresion
 * @param expresion expresion to be evaluated
 * @param symbolTable the symbolTable of the compiler
 * @return 1 if the expresion is true, 0 if the expresion is false
 */
int evaluateExpresion(Node *expresion , Symbol **symbolTable );

/**
 * @brief assigns a value to a symbol in the table
 * @param identifier identifier of the symbol whose value is to be assigned
 * @param expr expresion to be evaluated and assigned to the symbol
 */
void assignSymbol( char *identifier , Node *expr , Symbol **symbolTable , SymbolType symbolType);

/**
 * @brief resolves the syntactic tree
 * @param tree tree to be resolved
 * @param symbolTable the symbolTable of the compiler
 * @returns 1 if the resolution concluded successfully, 0 if there was a problem resolving the tree
 */
int resolveTree( Node *tree , Symbol **symbolTable);

#endif //__SYNTAX_TREE_H__

//end syntaxtTree.h