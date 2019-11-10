/**
  * symboltable.h
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: header for symbol table
  *
  */

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "scanner.h"
#include "strings.h"

#define MAX_SYMTABLE_SIZE 17569 //nějaká meme hodnota, která je shodou okolností prvočíslo
#define MAX_FUNCTION_PARAMS 100 //maximální počet parametrů v uživatelské funkci

#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

//init value
struct symtable;
struct symtableItm;

typedef union{
    char *string;
    int INT;
    double FLOAT;
    bool BOOL;
} value;

typedef enum { //možné datové typy - 10.3 v zadání
	DATA_UNDEFINED, //nvm jestli nutný
	DATA_INT,
	DATA_BOOL,
	DATA_FLOAT,
	DATA_STRING,
} dataType;

typedef enum {
  FUNCTION,
	VARIABLE,
} elementType;

typedef struct { //typedef struct var_item{
	bool used;
	value value;
	dataType type;
} variableData;

typedef struct { //typedef struct fc_item{
	bool defined; //je poprvé přiřazena hodnota
	dataType returnType;
	int argCount;
	struct symtableItm *arguments;
	struct symtable *sT;
} functionData;

typedef struct symtableItm {
  bool declared; //je zeloženo
	struct symtableItm *next;
	char *key;
	union {
		functionData *function;
		variableData *variable;
	} elementType;
	elementType type;
} symtableItem;

typedef struct symtable { //tady musi
	unsigned int size;
	symtableItem *symtabList[];
} symbolTable;


symbolTable *initSymbolTable(unsigned int size); //init celého symbol tablu
void freeSymbolTable(symbolTable *sT); //uvolnění celého symbol tablu
symtableItem *searchSymbolTable(symbolTable *sT, token token); //vrací ukazatel na prvek v symbol tablu pokud tam je, jinak NULL
void deleteItemFromSymbolTable(symbolTable *sT, token token); //odstraní deklarovanou variable/fci z symtable

#endif
