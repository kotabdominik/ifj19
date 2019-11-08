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

#include "string.h"

#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_


/* chybi nejake struktury */

typedef struct {
  root; //tady bude ukazatel na koren(nejaky node) binarniho stromu
} symbolTable;

void initSymbolTable(symbolTable *sT); //inicializace symbol tablu
void insertFunctionSymbolTable(symbolTable *sT, smartString string); //prida data o funkci do symbol tablu
void insertVariableSymbolTable(symbolTable *sT, smartString string); //prida data o promenne do symbol tablu
/* zatim neznamy node */ searchSymbolTable(symbolTable *sT, smartString string); //vyhleda prvek v symbol tablu
void removeSymbolTable(symbolTable *sT, smartString string); //odstrani prvek ze symbol tablu
void deleteSymbolTable(symbolTable *sT); //odstrani cely symbol table
/* vlozeni builtIn funkci do symtablu ???? */
/* btw https://github.com/DavidHribek/IFJ/blob/development/src/symtable.h */ 

#endif
