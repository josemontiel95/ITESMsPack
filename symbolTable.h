#ifndef __TABLA_H__
#define __TABLA_H__

typedef struct aVariable {
    int  tipo; //tipo int=0 float=1
    char* id; //nombre
    union {
        int   valInt; //valor int
        float valFloat; //valor float 
    } uValor;
    struct aVariable *next;
} Variable; //Symbol

int insertaSimbolo( Variable **head , char *id , int tipo ); //insertSymbol
Variable *buscaSimbolo( Variable **head , char *id );
int setSimboloInt( Variable **head , char *id , int valorNuevo );
int setSimbolopFLOAT( Variable **head , char *id , float valorNuevo );
int getSimboloInt( Variable **head , char *id );
float getSimbolopFLOAT( Variable **head , char *id );
int getTipoSimbolo( Variable **head , char * id);

#endif