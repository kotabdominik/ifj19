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
#include "scanner.h"

/*
 * vrací hash hodnotu do symbol table
 */
 unsigned long hash(unsigned char *str) { //https://stackoverflow.com/a/7666577
     unsigned long hash = MAX_SYMTABLE_SIZE;
     int c;

     while (c = *str++)
         hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

     return hash % MAX_SYMTABLE_SIZE; //vrací hash v rozmezí 0 .. (MAX_SYMTABLE_SIZE - 1)
 }

/*
 * inicializace symbol table
 */
symbolTable *initSymbolTable(unsigned int size){
  symbolTable *sT = (symbolTable *) malloc(sizeof(*sT) + size * sizeof(sT->symtabList[0]));
  if (!sT) {
    printf("%s\n", "yikes");
  }
  sT->size = size;
  for (unsigned int i = 0; i < sT->size; i++) {
		sT->symtabList[i] = NULL;
	}
  return sT;
}

/*
 * uvolnění symbol table
 */
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

/*
 * vkládání tokenu do symbol table
 */
void insertSymbolTable(symbolTable *sT, int index) {
  symtableItem *new_item = (symtableItem *) malloc(sizeof(symtableItem));
  if (new_item == NULL) {
    fprintf(stderr, "%s\n", "yyee");
  }

  new_item->elementType.variable = (variableData *) malloc(sizeof(variableData));
  if (new_item->elementType.variable == NULL) {
    fprintf(stderr, "%s\n", "yexd");
  }

  new_item->key = "a\0";
  new_item->type = VARIABLE;
  new_item->elementType.variable->declared = true;
  new_item->elementType.variable->value.INT = index + 5;

  new_item->next = sT->symtabList[index];
  sT->symtabList[index] = new_item;
}

void main(int argc, char** argv) {
  printf("%ld\n", hash(argv[1]));

  /*
  symbolTable *table = initSymbolTable(10); //potom MAX_SYMTABLE_SIZE
  insertSymbolTable(table, 0);
  insertSymbolTable(table, 2);

  printf("%d\n", table->symtabList[0]->elementType.variable->value.INT);
  printf("%d\n", table->symtabList[2]->elementType.variable->value.INT);
*/
}


/* for full version go to https://github.com/Endrych/IFJ-Projekt/blob/master/src/symtable.c */
