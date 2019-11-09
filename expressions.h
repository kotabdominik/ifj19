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
  EQ,
  NOTEQ,
  L,  // <
  G,  // >
  LOREQ, // <=
  GOREQ, // >=
  PLUS,
  MINUS,
  MUL,
  DIV,
  LF, // (
  RG, // )
  ID,
  INT,
  DOUBLE,
  STRING
} parseSymbols;



#endif
