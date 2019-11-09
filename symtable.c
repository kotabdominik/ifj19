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
/*
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

void main() {
  //symbolTable *table;
  symbolTable *table = initSymbolTable(10);
//  printf("%d\n", table->size);
  insertSymbolTable(table, 0);
  insertSymbolTable(table, 2);

  printf("%d\n", table->symtabList[0]->elementType.variable->value.INT);
  printf("%d\n", table->symtabList[2]->elementType.variable->value.INT);

/*
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


  //table->symtabList[0]->elementType.variable->value.INT = 5;
  printf("%d\n", table->symtabList[0]->elementType.variable->value.INT);

/*
  symtableItem *new = (symtableItem *) malloc(sizeof(symtableItem));
  if (new == NULL) {
    fprintf(stderr, "%s\n", "yyee");
  }

  new->elementType.variable = (variableData *) malloc(sizeof(variableData));
  if (new->elementType.variable == NULL) {
    fprintf(stderr, "%s\n", "yexd");
  }

  new->key = "a\0";
  new->type = VARIABLE;
  new->elementType.variable->declared = true;

  new->next = table->symtabList[1];
  table->symtabList[1] = new;

  table->symtabList[1]->elementType.variable->value.INT = 10;
  printf("%d\n", table->symtabList[1]->elementType.variable->value.INT);
*/
  //table->symtabList[1] = new_item;

  //printf("%s\n", new_item->key); //a

  //table->symtabList[0] = new_item;


  //table->symtabList[0] = (symtableItem *) calloc(1, sizeof(symtableItem));


//  if (!(table->symtabList[0] = (symtableItem *) malloc(sizeof(*tmpItem)))) {
//    printf("%s\n", "yeet :c");
//  }

  //symtableItem *tableItem;
  //struct symtableItm *tableItem

  //table->symtabList[0]->elementType.variable.value.INT = 5;
  //tableItem->elementType.variable.value.INT = 5; //setování value int tableItemu

  //tableItem->key = (char *) malloc(sizeof(char) * 5); //malokace a setování klíče, 5 je délka klíče
  //strcpy(tableItem->key, "aaaa\0");

  //table->symtabList[2] = nextTableItem;
  //tableItem->next = nextTableItem;

  //table->symtabList[0] = tableItem; //přiřazování tableItemu do tablu

  //printf("%s\n", table->symtabList[0]->key);
}


/* for full version go to https://github.com/Endrych/IFJ-Projekt/blob/master/src/symtable.c */
