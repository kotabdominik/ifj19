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
#include "strings.h"

#define MAX_SYMTABLE_SIZE 17569 //nějaká meme hodnota, která je shodou okolností prvočíslo

#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

//init value
typedef union{
    char *string;
    int INT;
    double FLOAT;
    bool BOOL;
} value;

typedef enum { //možné datové typy - 10.3 v zadání
	UNDEFINED, //nvm jestli nutný
	INT,
	BOOL,
	FLOAT,
	STRING,
} dataType;

typedef enum {
  FUNCTION,
	VARIABLE,
} elementType;

typedef struct { //typedef struct var_item{
	bool declared;
	//bool used;
	value value;
  //char *key;
	dataType type;
} variableData;

typedef struct { //typedef struct fc_item{
	bool declared; //je zeloženo
	bool defined; //je poprvé přiřazena hodnota
	dataType returnType;
	int argCount;
	//struct symtab_item *arguments;
	//struct symtable *sym_table;
	//char *key;
} functionData;

typedef struct symtableItm {
	struct symtableItm *next;
	char *key;
	union {
		functionData function;
		variableData variable;
	} elementType;
	elementType type;
} symtableItem;

typedef struct symtable {
	unsigned int size;
	symtableItem *symtabList[];
} symbolTable;

// Symbol table
//typedef Sym_table_item* Sym_table[MAX_SYMTABLE_SIZE]; nejspíš neřešit

void initSymbolTable(symbolTable *sT, unsigned int size); //inicializace symbol tablu
void freeSymbolTable(symbolTable *sT); //uvolnění celého symbol tablu

void insertFunctionSymbolTable(symbolTable *sT, smartString string); //prida data o funkci do symbol tablu
void insertVariableSymbolTable(symbolTable *sT, smartString string); //prida data o promenne do symbol tablu
/* zatim neznamy node */ //searchSymbolTable(symbolTable *sT, smartString string); //vyhleda prvek v symbol tablu
void removeSymbolTable(symbolTable *sT, smartString string); //odstrani prvek ze symbol tablu
void deleteSymbolTable(symbolTable *sT); //odstrani cely symbol table
/* vlozeni builtIn funkci do symtablu ???? */
/* btw https://github.com/DavidHribek/IFJ/blob/development/src/symtable.h */

#endif
