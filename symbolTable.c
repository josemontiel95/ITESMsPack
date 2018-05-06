#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Symbol *allocateSymbol() {
    Symbol *symbol = malloc( sizeof( Symbol ) );
    if ( symbol == NULL )
        return NULL;

    return symbol;
}

int insertSymbol( Symbol **head, char *identifier , SymbolType type) {
    if ( findSymbol( head, identifier ) == NULL ) {
        Symbol *new = allocateSymbol();
        if ( new != NULL ) {
            if ( *head == NULL ) {
                *head     = new;
                new->next = NULL;
            } else {
                new->next = *head;
                *head     = new;
            }

            new->type       = type;
            new->identifier = malloc( ( strlen( identifier ) + 1 ) * sizeof( char ) );
            strcpy( new->identifier , identifier );
            
            if ( type == sINTEGER ) {
                new->value.iValue = 0;
            } else if ( type == sFLOAT ) {
                new->value.fValue = 0.0;
            }

            return 1;
        } else {
            printf( "Error: Memory allocation failed. Program will be terminated\n" );
            exit(1);
        }
    } else {
        printf( "Error: Symbol to be inserted already exists. Program will be terminated\n" );
        exit(1);
    }
}

Symbol *findSymbol( Symbol **head , char *identifier ) {
    Symbol *result =  *head;
    while ( result != NULL ) {
        if ( strcmp( result->identifier , identifier ) == 0 ) {
            return result;
        }
        result = result->next;
    }
    return result;
}

int setIntegerSymbolValue( Symbol **head , char *identifier , int newValue ) {
    if ( *head == NULL ) {
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    Symbol *updateSymbol = findSymbol( head, identifier );
    if ( updateSymbol == NULL ) { 
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);   
    }
    updateSymbol->value.iValue = newValue;
    return 1;
}

int setFloatSymbolValue( Symbol **head, char *identifier, float newValue ) {
    if ( *head == NULL ) {
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    Symbol *updateSymbol = findSymbol( head, identifier );
    if ( updateSymbol == NULL ) {
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    updateSymbol->value.fValue = newValue;
    return 1;
}

int getIntegerSymbolValue( Symbol **head, char *identifier ) {
    if ( *head == NULL ) {
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    Symbol *symbol = findSymbol( head, identifier );
    if ( symbol == NULL ) { 
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    return symbol->value.iValue;
}

float getFloatSymbolValue( Symbol **head , char *identifier ) {
    if ( *head == NULL ) {
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    Symbol *symbol = findSymbol( head , identifier );
    if ( symbol == NULL ) { 
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    return symbol->value.fValue;
}

SymbolType getSymbolType( Symbol **head , char * identifier ) {
    if ( *head == NULL ) {
        printf("Error: Cannot obtain symbol type from undeclared symbol. Program will be terminated\n");
        exit(1);
    }
    Symbol *symbol = findSymbol( head , identifier ); 
    if ( symbol == NULL ) {        
        printf( "Error: Cannot obtain symbol type from undeclared symbol. Program will be terminated\n" );
        exit(1);
    }
    return symbol->type;
}