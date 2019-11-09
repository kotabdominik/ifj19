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
int precedenceTable[TABLESIZE][TABLESIZE] =
{
  //  +-   */   REL   (   )   EXP
    { C  ,  A ,  C  , A , C  , A }// +-
    { C  ,  C ,  C  , A , C  , A }// */
    { A  ,  A ,  E  , A , C  , A }// REL
    { A  ,  A ,  A  , A , B  , A }// (
    { C  ,  C ,  C  , E , C  , E }// )
    { C  ,  C ,  C  , E , C  , E }// EXP
};

/* converts symbol to table index */
tableIndex getTableIndex(parseSymbols parsedSymbol){
    switch (parsedSymbol) {
      case S_EQ:
      case S_NOTQE:
      case S_L:
      case S_G:
      case S_LOREQ:
      case S_GOREQ:
          return RELATION_OP;

      case S_PLUS:
      case S_MINUS:
          return PLUS_MINUS;

      case S_MUL:
      case S_DIV:
      case S_INTDIV:
        return MUL_DIV;

      case S_LF:
        return I_LF;

      case S_RG:
        return I_RG;

      case S_ID:
      case S_INT:
      case S_DOUBLE:
      case S_STRING:
        return EXPRESSION;
    }
}


parseSymbols getSymbol(){

}
