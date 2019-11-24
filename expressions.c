/**
  * expressions.c
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: implementation of operations that parse expressions
  *
  */


#include "expressions.h"

int error = OK;
tStack *stack;
int doIndent = 0;

// KDYZ PRIJDE PRVNE TO CO JE NAPRAVO A PAK AZ TO CO PRIJDE NAHORE, PAK
// priklad prvni radek, druha cell ... +* ... prvne se provede *
// A=0  '<' = prvne se provede to co je nahore v komentu
// B=1  '=' = jen u '(' a ')' zároveň
// C=2  '>' = prvne se provede to co je napravo v komentu
// E=3      = chybný sytax i guess

int precedenceTable[TABLESIZE][TABLESIZE] =
{
  //   +-  *///    (     )     i     r     $
    {  C  ,  A  ,  A  ,  C  ,  A  ,  C  ,  C  }, // +-
    {  C  ,  C  ,  A  ,  C  ,  A  ,  C  ,  C  }, // *///
    {  A  ,  A  ,  A  ,  B  ,  A  ,  A  ,  E  }, // (
    {  C  ,  C  ,  E  ,  C  ,  E  ,  C  ,  C  }, // )
    {  C  ,  C  ,  E  ,  C  ,  E  ,  C  ,  C  }, // i
    {  A  ,  A  ,  A  ,  C  ,  A  ,  E  ,  C  }, // r (relationship operators)
    {  A  ,  A  ,  A  ,  E  ,  A  ,  A  ,  E  }  // $
};

//vraci 1 pokud je token operator
//vraci 0 pokud neni token operator
int isOperator(token tokenAct){
  switch (tokenAct.type) {
    case INT:
    case FLOAT:
    case STR:
    case LITERAL:
      return 1;
    case KEYWORD:
      if(tokenAct.attribute.keyword == NONE) return 1;
      else return 0;
    default:
      return 0;
  }
}

//vraci 1 pokud je token operand
//vraci 0 pokud neni token operand
int isOperand(token tokenAct){
  switch (tokenAct.type) {
    case PLUS:
    case MINUS:
    case TIMES:
    case DIVFLT:
    case DIVINT:
    case LESS:
    case GREATER:
    case LESSEQ:
    case GREATEREQ:
    case EQ:
    case NOTEQ:
        return 1;
    default:
        return 0;
  }
}

int getPrecedenceIndex(token tokenAct) { //vrací index z precedence tablu
  switch (tokenAct.type) {
    case PLUS: // +
    case MINUS: // -
      return 0;
    case TIMES: // *
    case DIVFLT: // /
    case DIVINT: // //
      return 1;
    case LEFTBRACKET: // (
      return 2;
    case RIGHTBRACKET: // )
      return 3;
    case INT: // i
    case FLOAT: // i
    case STR: // i
    case LITERAL: // i
      return 4;
    case LESSEQ: // <=
    case GREATEREQ: // >=
    case EQ: // ==
    case NOTEQ: // !=
    case LESS: // <
    case GREATER: // >
      return 5;
    default: // $ toto nejspíš asi ee ale pšš prozatím, potom předělat na: case KEYWORD.then, EOL atd..
      return 6;
  }
}

int getPrecedenceOperatorValue(token stackToken, token vstupniToken) {
  int index1, index2 = 0;
  index1 = getPrecedenceIndex(vstupniToken);
  index2 = getPrecedenceIndex(stackToken);
  return *precedenceTable[index1, index2];
}

precendentExpression* doExpression(token tokenAct) {
  precendentExpression* exp = malloc(sizeof(precendentExpression));
  if (!exp) {
    //malloc pp
  }
  exp->Tree = NULL;
  exp->ReturnToken = NULL;

  bool logical = false, readNextToken = true;
  tokenStack *s = (tokenStack*) malloc(sizeof(tokenStack));
  if(s == NULL){
    //malloc pp
  }
  tokenStackInit(s);
  token current = tokenAct;
  if (&current == NULL)
    current = nextToken(&error, stack, doIndent);

}
/*
void main() {

  stack = malloc(sizeof(tStack));
  stackInit(stack);
  stackPush(stack, 0);
  setFile("txt.txt");
  token token1, token2;

  token1 = nextToken(&error, stack, doIndent);
  token2 = nextToken(&error, stack, doIndent);

  printf("%d\n", getPrecedenceOperatorValue(token1, token2));
  doExpression(token1);
}
*/
