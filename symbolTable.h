#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

typedef enum tagSymbolType {
    sINTEGER,
    sFLOAT
} SymbolType;

typedef struct tagSymbol {
    SymbolType  type; //tipo
    char* identifier; //nombre
    union {
        int   iValue; //valor int
        float fValue; //valor float 
    } value;
    struct tagSymbol *next;
} Symbol;

int insertSymbol( Symbol **head , char *identifier , SymbolType type );
Symbol *findSymbol( Symbol **head , char *identifier );
int setIntegerSymbolValue( Symbol **head , char *identifier , int newValue );
int setFloatSymbolValue( Symbol **head , char *identifier , float newValue );
int getIntegerSymbolValue( Symbol **head , char *identifier );
float getFloatSymbolValue( Symbol **head , char *identifier );
SymbolType getSymbolType( Symbol **head , char * identifier);

#endif