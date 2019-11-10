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

#include "symtable.h"

/*
 * vrací hash hodnotu do symbol table
 */
unsigned long hash(unsigned char *str) { //https://stackoverflow.com/a/7666577
  unsigned long hash = MAX_SYMTABLE_SIZE;
  int c;

  while (c = *str++) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }

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
void freeSymbolTable(symbolTable *sT) { //zatim freeuju jen variables, funkce ne
  symtableItem *tmpItem;

  for (unsigned int i = 0; i < sT->size; i++) {
    tmpItem = sT->symtabList[i];
    while (tmpItem) {
      symtableItem *thisItem = tmpItem;
      tmpItem = tmpItem->next; //nejspis bude NULL btw
      if (thisItem->type == VARIABLE) {
        free(thisItem->elementType.variable);
      }
      free(thisItem->key);
      free(thisItem);
    }
  }
  free(sT);
}

/*
 * vkládání tokenu do symbol table
 */
void insertSymbolTable(symbolTable *sT, token token, elementType type) {
  char* key = token.attribute.string->string; //získáme jmeno variable/fce
  unsigned long hashVal = hash(key); //získáme hash

  symtableItem *newItem = (symtableItem *) malloc(sizeof(symtableItem));
  if (newItem == NULL) {
    fprintf(stderr, "%s\n", "yyee");
  }

  if (type == VARIABLE) {
    newItem->elementType.variable = (variableData *) malloc(sizeof(variableData));
    if (newItem->elementType.variable == NULL) {
      fprintf(stderr, "%s\n", "yexd");
    }
    newItem->type = VARIABLE;
// token s variablem nemůže mít zároveň nějakou hodnotu, takže toto se nemůže dělat tady
/*    if (token.type == STR) {
      printf("%s\n", "je to string");
      newItem->elementType.variable->type = DATA_STRING;
      newItem->elementType.variable->value = token.attribute.string->string
    } else if (token.type == INT) {
      printf("%s\n", "je to integer");
      newItem->elementType.variable->value.INT =
    } else if (token.type == FLOAT) {
      printf("%s\n", "je to float");
    } */
  } else if (type == FUNCTION) {
    newItem->elementType.function = (functionData *) malloc(sizeof(functionData));
    if (newItem->elementType.function == NULL) {
      fprintf(stderr, "%s\n", "yexxd");
    }
    newItem->elementType.function->sT = initSymbolTable(MAX_FUNCTION_PARAMS);
    newItem->type = FUNCTION;
    newItem->elementType.function->argCount = 1;
  }

  newItem->declared = true;
  newItem->key = key;

  if (sT->symtabList[hashVal] == NULL) { //ještě není nic na tomto indexu
    newItem->next = NULL;
  } else { //už je něco na tomto indexu
    newItem->next = sT->symtabList[hashVal];
  }

  sT->symtabList[hashVal] = newItem;

}

void deleteItemFromSymbolTable(symbolTable *sT, token token) {
  char* key = token.attribute.string->string; //získáme jmeno variable/fce
  unsigned long hashVal = hash(key); //získáme hash
  symtableItem *tmp = sT->symtabList[hashVal];

  while (tmp) {
    if (!strcmp(key, tmp->key)) {
      free(tmp);
      tmp = NULL;
    } else {
      tmp = tmp->next;
    }
  }

  free(key);
}

symtableItem *searchSymbolTable(symbolTable *sT, token token) {
  char* key = token.attribute.string->string; //získáme jmeno variable/fce
  unsigned long hashVal = hash(key); //získáme hash
  symtableItem *tmp = sT->symtabList[hashVal];

  while (tmp) {
    if (!strcmp(key, tmp->key)) {
      return tmp;
    }

    tmp = tmp->next;
  }

  return NULL;
}

/*
void main(int argc, char** argv) {
  symbolTable *table = initSymbolTable(MAX_SYMTABLE_SIZE);

  //muj tmp token variable string
  token Token;
  smartString *s = malloc(sizeof(smartString));
  if (s == NULL){
      return;
  }
  stringInit(s);
  stringAddChar(s,'u');
  stringAddChar(s,'w');
  stringAddChar(s,'u');
  Token.attribute.string = s;
  Token.type = STR;

  insertSymbolTable(table, Token, FUNCTION);
  if(table->symtabList[hash("uwu")]->elementType.function->argCount) {
    printf("%s\n", "je zalozena");
  }

  symtableItem *tmp = searchSymbolTable(table, Token); //vraci ukazatel
  printf("%s\n", tmp->key);
  deleteItemFromSymbolTable(table, Token);
  tmp = searchSymbolTable(table, Token); //vrati NULL

  freeSymbolTable(table);
//  stringFree(s);

}


/* for full version go to https://github.com/Endrych/IFJ-Projekt/blob/master/src/symtable.c */
