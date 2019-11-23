/**
  * expressions.h
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: header file of expressions
  *
  */

#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "parser.h"
#include "list.h"
#include "list.c"

#define TABLESIZE 7

//pravidla pro parsovani expresi
typedef enum{
  E_PLUS_E, // E + E
  E_MUL_E, // E * E
  LF_E_RG,  // (E)
  _I_, // i
  F_LF_E_RG, // f(E)
  F_LF_E_E_RG, // f(E,E)
  F_LF_E_E_E_RG, // f(E,E,E)
  FAIL
} precedenceRules;

// symboli pro parcovani
typedef enum {
  S_PLUS,
  S_MUL,
  S_LF, // (
  S_RG, // )
  S_I, //identifier
  S_INT,
  S_DOUBLE,
  S_STRING,
  S_COMMA,
  S_END,
  S_DOLLAR //im out of money :{
} parseSymbols;

typedef enum {
  A, // <
  B, // =
  C, // >
  E // ERROR
} precedenceSign;

typedef enum{
  I_PLUS,
  I_MUL,
  I_LF, // (
  I_RG, // )
  I_I, // identifier
  I_FUNC,
  I_COMMA,
  I_DOLLAR,
  I_E // E
} tableIndex;

typedef struct sItem{
  parseSymbols parseSymbol;
  dataType dataType;
  struct sItem *another;
} symbolItem;


parseSymbols convertToSymbol(token *token);
tableIndex convertToTableIndex(parseSymbols parsedSymbol);
//dataType convertToDataType(token* token, parserToken* pToken);
precedenceRules testParameters(int decide,symbolItem* operator1, symbolItem* operator2, symbolItem* operator3, symbolItem* operator4, symbolItem* operator5, symbolItem* operator6, symbolItem* operator7, symbolItem* operator8);

#endif
