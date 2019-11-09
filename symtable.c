/**
  * symtable.c
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: implementation of operations above/on symbol table
  *
  */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "symtable.h"

/*
 * inicializace symbol table
 * table je implementovan pomoci binarniho stromu
 * = inicializuje se binarni strom
*/
void initSymbolTable(symbolTable *sT, unsigned int size){
  sT = (symbolTable *) malloc(sizeof(*sT) + size * sizeof(sT->symtabList[0]));
  if (!sT) {
    printf("%s\n", "yikes");
  }
  sT->size = size;
  for (unsigned int i = 0; i < sT->size; i++) {
		sT->symtabList[i] = NULL;
	}
}

void freeSymbolTable(symbolTable *sT) {
  symtableItem *tmpItem;

  for (unsigned int i = 0; i < sT->size; i++) {
    tmpItem = sT->symtabList[i];
    while (tmpItem) {
      symtableItem *thisItem = tmpItem;
      tmpItem = tmpItem->next;
      //xddd vy si fakt myslite ze to budu freeovat yeet (jk todo ... unless *blushes*)
      break;
    }
  }
}

void main() {
  symbolTable *table;
  initSymbolTable(table, 1);
  symtableItem *tableItem;
  tableItem = (symtableItem *) malloc(sizeof(*tableItem));
  if (!tableItem) {
    printf("%s\n", "yeet :c");
  }

  tableItem->elementType.variable.value.INT = 5; //setování value int tableItemu

  tableItem->key = (char *) malloc(sizeof(char) * 5); //malokace a setování klíče
  strcpy(tableItem->key, "aaaa\0");

  table->symtabList[0] = tableItem; //přiřazování tableItemu do tablu

  printf("%d\n", table->symtabList[0]->elementType.variable.value.INT);
  printf("%s\n", table->symtabList[0]->key);
}


/* for full version go to https://github.com/Endrych/IFJ-Projekt/blob/master/src/symtable.c */
