#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Variable *allocateSymbol() {
    Variable *symbol = malloc( sizeof( Variable ) );
    if ( symbol == NULL )
        return NULL;

    return symbol;
}

int insertaSimbolo( Variable **head, char *identifier , VarTipo tipo) {
    if ( buscaSimbolo( head, identifier ) == NULL ) {
        Variable *new = allocateSymbol();
        if ( new != NULL ) {
            if ( *head == NULL ) {
                *head     = new;
                new->next = NULL;
            } else {
                new->next = *head;
                *head     = new;
            }

            new->tipo       = tipo;
            new->identifier = malloc( ( strlen( identifier ) + 1 ) * sizeof( char ) );
            strcpy( new->identifier , identifier );
            
            if ( tipo == vINT ) {
                new->value.valInt = 0;
            } else if ( tipo == vFLOAT ) {
                new->value.valFloat = 0.0;
            }

            return 1;
        } else {
            printf( "Error: Memory allocation failed. Program will be terminated\n" );
            exit(1);
        }
    } else {
        printf( "Error: Variable to be inserted already exists. Program will be terminated\n" );
        exit(1);
    }
}

Variable *buscaSimbolo( Variable **head , char *identifier ) {
    Variable *result =  *head;
    while ( result != NULL ) {
        if ( strcmp( result->identifier , identifier ) == 0 ) {
            return result;
        }
        result = result->next;
    }
    return result;
}

int setSimboloInt( Variable **head , char *identifier , int newValue ) {
    if ( *head == NULL ) {
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    Variable *updateSymbol = buscaSimbolo( head, identifier );
    if ( updateSymbol == NULL ) { 
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);   
    }
    updateSymbol->value.valInt = newValue;
    return 1;
}

int setSimboloFloat( Variable **head, char *identifier, float newValue ) {
    if ( *head == NULL ) {
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    Variable *updateSymbol = buscaSimbolo( head, identifier );
    if ( updateSymbol == NULL ) {
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    updateSymbol->value.valFloat = newValue;
    return 1;
}

int getSimboloInt( Variable **head, char *identifier ) {
    if ( *head == NULL ) {
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    Variable *symbol = buscaSimbolo( head, identifier );
    if ( symbol == NULL ) { 
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    return symbol->value.valInt;
}

float getSimboloFloat( Variable **head , char *identifier ) {
    if ( *head == NULL ) {
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    Variable *symbol = buscaSimbolo( head , identifier );
    if ( symbol == NULL ) { 
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    return symbol->value.valFloat;
}

VarTipo getTipoSimbolo( Variable **head , char * identifier ) {
    if ( *head == NULL ) {
        printf("Error: Cannot obtain symbol tipo from undeclared symbol. Program will be terminated\n");
        exit(1);
    }
    Variable *symbol = buscaSimbolo( head , identifier ); 
    if ( symbol == NULL ) {        
        printf( "Error: Cannot obtain symbol tipo from undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    return symbol->tipo;
}