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
#include "tokenStack.h"
#include "tokenStack.c"
#include "scanner.h"

#define TABLESIZE 7 //velikost precedenční tabulky

typedef struct{
    int* returnType;
    token* returnToken;
} precendentExpression;

typedef enum {
  A, //0 <
  B, //1 =
  C, //2 >
	D, //3 DONE
  E  //4 ERROR
} precedenceSign;

#endif
