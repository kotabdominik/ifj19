#include "absTree.h"
#include "symtable.h"

#ifndef STACK_H
#define STACK_H

// Typ polozky
typedef enum{
    type_token,
    type_nonterm,
    type_handler
}SType;

// Atribut pro ulozeni tokenu nebo ukazatele na ASS
typedef union{
    token* Token;
    ATLeaf* Leaf;
}SAtribute;

// Data polozek zasobniku
// DataType Datovy typ polozky
// Type Typ polozky
// Atr Atribut polozky
typedef struct{
    dataType DataType;
    SType Type;
    SAtribute Atr;
}SData;

// Polozka zasobniku
// Data Data polozky zasobniku
// Next Ukazatel na nasledujici polozku
typedef struct SItem{
    SData* Data;
    struct SItem* Next;
}TSItem;

// Struktura zasobniku
// Top Ukazatel na vrchol zasobniku
typedef struct Stack{
    TSItem* Top;
} tokenStack;

/**
 * Funkce inicializuje zasobnik
 * @param s Ukazatel na zasobnik
 */
void tokenStackInit ( tokenStack* s );

/**
 * Funkce pro zruseni zasobniku
 * @param s Ukazatel na zasobnik
 */
void tokenStackDestruct ( tokenStack* s );

/**
 * Funkce pro zjisteni jesli je zasobnik prazdny
 * @param s Ukazatel na zasobnik
 * @return Vraci 1 pokud je zasobnik prazdny jinak vraci 0
 */
int tokenStackEmpty ( const tokenStack* s );

/**
 * Funkce pro ziskani dat z vrcholu zasobniku
 * @param s Ukazatel na zasobnik
 * @return Vraci data z vrcholu zasobniku
 */
SData* tokenStackTop ( const tokenStack* s);

/**
 * Funkce odebere polozku z vrcholu zasobniku
 * @param s Ukazatel na zasobnik
 */
void tokenStackPop ( tokenStack* s );

/**
 * Funkce vlozi polozku do zasobniku
 * @param s Ukazatel na zasobnik
 * @param data Data, ktera se maji v zasobniku ulozit
 */
void tokenStackPush ( tokenStack* s, SData* data);

/**
 * Funkce vraci ze zasobniku data prvnihu terminalu
 * @param s Ukazatel na zasobnik
 * @return Data terminalu
 */
SData* getTerminalData(tokenStack* s);

/**
 * Funkce vytvori v zasobniku zarazku na urcite pozici
 * @param s Ukazatel na zasobnik
 * @param sData Ukazatel na data v zasobniku, kde se zarazka ma vytvorit
 */
void addHandler(tokenStack* s,SData * sData);
#endif
