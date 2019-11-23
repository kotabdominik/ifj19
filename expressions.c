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

// KDYZ PRIJDE PRVNE TO CO JE NAPRAVO A PAK AZ TO CO PRIJDE NAHORE, PAK
// priklad prvni radek, druha cell ... +* ... prvne se provede *
// A = prvne se provede to co je nahore v komentu
// B = obe naraz?
// C = prvne se provede to co je napravo v komentu
// E = nenastane?
/* A  <                              S
 * B  =                              E
 * C  >                              R
 */
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

int expression(token tokenAct){

}


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
