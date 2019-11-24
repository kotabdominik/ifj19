/**
  * absTree.h
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: abstraktní strom pro uchování věcí
  *
  */

#include "scanner.h"
#include "symtable.h"
#include <stdbool.h>

#ifndef ATREE_H
#define ATREE_H

// Hodnota pretypovani
typedef enum{
  Integer2Double,
  Double2Integer,
  Double2Integer1
}TCast;

// Typ polozky ASS
typedef enum{
  at_operators,
  at_token,
  at_tsitem,
  at_type_cast
}ATType;

// Hodnota polozky abs
// op_value Ulozeni hodnoty operatoru
// token Ulozeni tokenu
// tsItem Ulozeni ukazatele do TS
// type_cast Ulozeni hodnoty pretypovani
typedef union{
  tokenType tokenValue;
  token* token;
  symtableItem* symItem;
  TCast typeCast;
}ATAtribute;

// Struktura polozky abs
// type Typ polozky
// Atr Hodnota polozky
typedef struct{
  ATType type;
  ATAtribute Atr;
}ATData;

// Struktura abs
// processed znaci zda byl uzel jiz zpracovan
// data hodnota, kterou obsahuje uzel abs
// left ukazatel na levou vetev abs
// right ukazatel na pravou vetev abs
typedef struct atleaf{
  bool processed;
  ATData data;
  struct atleaf *left;
  struct atleaf *right;
}ATLeaf;

ATLeaf *make_leaf(ATData data); //vytvoření uzlu
ATLeaf *make_tree(ATLeaf *leaf_1, ATLeaf *leaf_2, ATData data); //vytvoření stromu
void dispose_at(ATLeaf *leaf); //uvolnění abs

#endif
