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
	bool declared;
	//bool used;
	value value;
	dataType type;
} variableData;

typedef struct { //typedef struct fc_item{
	bool declared; //je zeloženo
	bool defined; //je poprvé přiřazena hodnota
	dataType returnType;
	int argCount;
	//struct symtab_item *arguments;
	//struct symtable *sym_table;
} functionData;

typedef struct symtableItm {
	struct symtableItm *next;
	char *key;
	union {
		functionData *function;
		variableData *variable;
	} elementType;
	elementType type;
} symtableItem;

typedef struct symtable {
	unsigned int size;
	symtableItem *symtabList[];
} symbolTable;

// Symbol table
//typedef Sym_table_item* Sym_table[MAX_SYMTABLE_SIZE]; nejspíš neřešit

//void initSymbolTable(symbolTable *sT, unsigned int size); //inicializace symbol tablu
symbolTable *initSymbolTable(unsigned int size);
void freeSymbolTable(symbolTable *sT); //uvolnění celého symbol tablu


#endif
