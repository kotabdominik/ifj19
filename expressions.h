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

#define TABLESIZE 6

//pravidla pro parsovani expresi
typedef enum{
  E_EQ_E, // E = E
  E_NOTEQ_E, // E != E
  E_L_E, // E < E
  E_G_E, // E > E
  E_LOREQ_E, // E <= E
  E_GOREQ_E, // E >= E
  E_PLUS_E, // E + E
  E_MINUS_E, // E - E
  E_MUL_E, // E * E
  E_DIV_E, // E / E
  LF_E_RG,  // (E)
  FAIL
} precedenceRules;

// symboli pro parcovani
typedef enum {
  S_EQ,
  S_NOTEQ,
  S_L,  // <
  S_G,  // >
  S_LOREQ, // <=
  S_GOREQ, // >=
  S_PLUS,
  S_MINUS,
  S_MUL,
  S_DIV,
  S_INTDIV, // //(celociselne deleni)
  S_LF, // (
  S_RG, // )
  S_ID,
  S_INT,
  S_DOUBLE,
  S_STRING
} parseSymbols;

typedef enum {
  A, // <
  B, // =
  C, // >
  E // ERROR
} precedenceSign;

typedef enum{
  PLUS_MINUS,
  MUL_DIV,
  RELATION_OP,
  I_LF, // (
  I_RG, // )
  EXPRESSION
} tableIndex;


tableIndex getTableIndex(parseSymbols parsedSymbol);

#endif
