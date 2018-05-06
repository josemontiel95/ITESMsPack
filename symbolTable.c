#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int insertaSimbolo( Variable **head, char *id , int tipo) {
    if ( buscaSimbolo( head, id ) == NULL ) {
        Variable *aux = malloc( sizeof( Variable ) );
        if ( aux != NULL ) {
            if ( *head == NULL ) {
                *head = aux;
                aux->next = NULL;
            } else {
                aux->next = *head;
                *head     = aux;
            }

            aux->tipo       = tipo;
            aux->id = malloc( ( strlen( id ) + 1 ) * sizeof( char ) );
            strcpy( aux->id , id );

            if ( tipo == 0 )
                aux->uValor.valInt = 0;
            else if ( tipo == 1 ) {
                aux->uValor.valFloat = 0.0;
            }

            return 1;
        } else {
            printf( "Error: malloc\n" );
            exit(1);
        }
    } else {
        printf( "Error: Variable ya existe\n" );
        exit(1);
    }
}

Variable *buscaSimbolo( Variable **head , char *id ) {
    Variable *resultado =  *head;
    while ( resultado != NULL ) {
        if ( strcmp( resultado->id , id ) == 0 ) {
            return resultado;
        }
        resultado = resultado->next;
    }
    return resultado;
}

int setSimboloInt( Variable **head , char *id , int valorNuevo ) {
    if ( *head == NULL ) {
        printf( "Error: variable no declarada\n" );
        exit(1);
    }
    Variable *nuevo = buscaSimbolo( head, id );
    if ( nuevo == NULL ) { 
        printf( "Error: variable no declarada\n" );
        exit(1);   
    }
    nuevo->uValor.valInt = valorNuevo;
    return 1;
}

int setSimbolopFLOAT( Variable **head, char *id, float valorNuevo ) {
    if ( *head == NULL ) {
        printf( "Error: variable no declarada\n" );
        exit(1);
    }
    Variable *nuevo = buscaSimbolo( head, id );
    if ( nuevo == NULL ) {
        printf( "Error: variable no declarada\n" );
        exit(1);
    }
    nuevo->uValor.valFloat = valorNuevo;
    return 1;
}

int getSimboloInt( Variable **head, char *id ) {
    if ( *head == NULL ) {
        printf( "Error: variable no declarada\n" );
        exit(1);
    }
    Variable *aux = buscaSimbolo( head, id );
    if ( aux == NULL ) { 
        printf( "Error: variable no declarada\n" );
        exit(1);
    }
    return aux->uValor.valInt;
}

float getSimbolopFLOAT( Variable **head , char *id ) {
    if ( *head == NULL ) {
        printf( "Error: variable no declarada\n" );
        exit(1);
    }
    Variable *aux = buscaSimbolo( head , id );
    if ( aux == NULL ) { 
        printf( "Error: variable no declarada\n" );
        exit(1);
    }
    return aux->uValor.valFloat;
}

int getTipoSimbolo( Variable **head , char * id ) {
    if ( *head == NULL ) {
        printf("Error: variable no declarada\n");
        exit(1);
    }
    Variable *aux = buscaSimbolo( head , id ); 
    if ( aux == NULL ) {        
        printf( "Error: variable no declarada\n" );
        exit(1);
    }
    return aux->tipo;
}