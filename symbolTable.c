/**
 * symbolTable.c
 * Implementation of functions used to build the symbol table
 * @author Jose Pablo Ortiz Lack
 */
#include "symbolTable.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Allocates space for the Symbol
 * @return The Symbol or NULL if there is not enough memory
 */
static Symbol *allocateSymbol() {

    Symbol *symbol = malloc( sizeof( Symbol ) );

    //if there was not enough memory, malloc returns null
    if ( symbol == NULL ) {

        return NULL;
    }

    return symbol;

}

int insertSymbol( Symbol **head, char *identifier , SymbolType type) {

    if ( findSymbol( head, identifier ) == NULL ) {

        Symbol *new = allocateSymbol();

        if ( new != NULL ) {

            if ( *head == NULL ) { //The table is empty
                
                //Make the new symbol head of the table
                *head     = new;
                new->next = NULL;

            } else { //The table has at least one symbol
               
                new->next = *head;

                *head     = new;
            }

            new->type       = type;
            
            //reserve memory for the identifier and copy the identifier to the new symbol
            new->identifier = malloc( ( strlen( identifier ) + 1 ) * sizeof( char ) );
            strcpy( new->identifier , identifier );

            if ( type == sINTEGER ) {

                new->value.iValue = 0;

            } else if ( type == sFLOAT ) {

                new->value.fValue = 0.0;

            }

            return 1;

        } else { //There was an error assigning memory to the new symbol
            
            printf( "Error: Memory allocation failed. Program will be terminated\n" );
            exit(1);

            
        }

    } else {

        printf( "Error: Symbol to be inserted already exists. Program will be terminated\n" );
        exit(1);

    }

}

Symbol *findSymbol( Symbol **head , char *identifier ) {

    Symbol *result =  *head; //We start searching at the beginning of the table
    
    while ( result != NULL ) { //Traverse the complete table
    
        if ( strcmp( result->identifier , identifier ) == 0 ) { //If the identifier of the current node matches the search criteria
            
            return result;

        }

        result = result->next;
    }

    return result; //If the search criteria is not met, return NULL
}

int setIntegerSymbolValue( Symbol **head , char *identifier , int newValue ) {

    //verify the table is not empty
    if ( *head == NULL ) {
        
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);

    }

    Symbol *updateSymbol = findSymbol( head, identifier ); //Search the symbol to be updated

    if ( updateSymbol == NULL ) { //The symbol was not found
        
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);
        
    }

    updateSymbol->value.iValue = newValue;

    return 1;

}

int setFloatSymbolValue( Symbol **head, char *identifier, float newValue ) {

    //verify the table is not empty
    if ( *head == NULL ) {
        
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);
        
    }

    Symbol *updateSymbol = findSymbol( head, identifier ); //Search the symbol to be updated

    if ( updateSymbol == NULL ) { //The symbol was not found
        
        printf( "Error: Cannot assign value to undeclared symbol. Program will be terminated\n" );
        exit(1);
        
    }

    updateSymbol->value.fValue = newValue;

    return 1;

}

int getIntegerSymbolValue( Symbol **head, char *identifier ) {

    //verify the table is not empty
    if ( *head == NULL ) {
        
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
        
    }

    Symbol *symbol = findSymbol( head, identifier ); //Search the symbol to get the value from

    if ( symbol == NULL ) { //The symbol was not found
        
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
        
    }

    return symbol->value.iValue;

}

float getFloatSymbolValue( Symbol **head , char *identifier ) {

    //verify the table is not empty
    if ( *head == NULL ) {
        
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
        
    }

    Symbol *symbol = findSymbol( head , identifier ); //Search the symbol to get the value from

    if ( symbol == NULL ) { //The symbol was not found
        
        printf( "Error: Cannot obtain value from undeclared symbol. Program will be terminated\n" );
        exit(1);
        
    }

    return symbol->value.fValue;

}

SymbolType getSymbolType( Symbol **head , char * identifier ) {

    //verify the table is not empty
    if ( *head == NULL ) {
        
        printf("Error: Cannot obtain symbol type from undeclared symbol. Program will be terminated\n");
        exit(1);
        
    }

    Symbol *symbol = findSymbol( head , identifier ); //Search the symbol to get the value from

    if ( symbol == NULL ) { //The symbol was not found
        
        printf( "Error: Cannot obtain symbol type from undeclared symbol. Program will be terminated\n" );
        exit(1);
        
    }

    return symbol->type;

}

//end symbolTable.c