#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

typedef enum aVarTipo {
    vINT,
    vFLOAT
} VarTipo; //SymbolType

typedef struct aVariable {
    VarTipo  tipo; //tipo
    char* identifier; //nombre
    union {
        int   iValue; //valor int
        float fValue; //valor float 
    } value;
    struct aVariable *next;
} Variable; //Symbol

int insertaSimbolo( Variable **head , char *identifier , VarTipo tipo );//insertSymbol
Variable *buscaSimbolo( Variable **head , char *identifier );
int setSimboloInt( Variable **head , char *identifier , int newValue );
int setSimboloFloat( Variable **head , char *identifier , float newValue );
int getSimboloInt( Variable **head , char *identifier );
float getSimboloFloat( Variable **head , char *identifier );
VarTipo getTipoSimbolo( Variable **head , char * identifier);

#endif