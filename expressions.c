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
/* A  <
 * B  =
 * C  >
 */
int precedenceTable[TABLESIZE][TABLESIZE] =
{
  //  +-   */    (   )    i    f    ,  DOLLAR
    { C  ,  A  , A , C  , A ,  A ,  C ,  C  }// +-
    { C  ,  C  , A , C  , A ,  A ,  C ,  C  }// */
    { A  ,  A  , A , B  , A ,  A ,  B ,  E  }// (
    { C  ,  C  , E , C  , E ,  E ,  C ,  C  }// )
    { C  ,  C  , E , C  , E ,  E ,  C ,  C  }// i
    { E  ,  E  , B , E  , E ,  E ,  E ,  E  }// f
    { A  ,  A  , A , B  , A ,  A ,  B ,  E  }// ,
    { A  ,  A  , A , E  , A ,  E ,  E ,  E  }// DOLLAR
};


/* converts token type to symbol */
parseSymbols convertToSymbol(token *token){
  switch (token->type) {
    case PLUS:
        return S_PLUS;

    case TIMES:
        return S_MUL;

    case INT:
    case INTEXP:
        return S_INT;

    case FLOAT:
        return S_DOUBLE;

    case LITERAL:
      return S_STRING;

    case STR:
        return S_I; //identifier (i)

    case LEFTBRACKET:
        return S_LF;

    case RIGHTBRACKET:
        return S_RG;

    case COMMA:
        return S_COMMA;

    default:
      return S_DOLLAR;
  }
}

/* converts symbol to table index */
tableIndex convertToTableIndex(parseSymbols parsedSymbol){
    switch (parsedSymbol) {

      case S_PLUS:
          return I_PLUS;

      case S_MUL:
        return I_MUL;

      case S_LF:
        return I_LF;

      case S_RG:
        return I_RG;

      case S_I:
      case S_INT:
      case S_DOUBLE:
      case S_STRING:
        return I_I;

      case S_COMMA:
          return I_COMMA;

      case :
          return I_FUNC;

      default:
        return I_DOLLAR;
    }
}

/* converts token to data type */
/*
 * token = token z analyseru
 * pToken = token z parseru, ktery uchovava potrebna data pro parsovani
 */
dataType convertToDataType (token* token, parserToken* pToken){
  symtableItem* item; //polozka ze symbol table

  if(token->type == INT || token->type == INTEXP){
    return DATA_INT;
  }
  else if(token->type == FLOAT || token->type == FLOATEXP){
    return DATA_FLOAT;
  }
  else if(token->type == LITERAL){
    return DATA_STRING;
  }
  else if(token->type == STR){
    item = ;/* search symtable ... not yet implemented*/
    if(item == NULL){ /* probably NULL, but not yet implemented */
      return DATA_UNDEFINED;
    }
    else {
        return item->type;
    }
  }
  else{
    return DATA_UNDEFINED;
  }
}

/* tests if parameters are by the rules */
precedenceRules testParameters (int decide,symbolItem* operator1, symbolItem* operator2, symbolItem* operator3, symbolItem* operator4, symbolItem* operator5, symbolItem* operator6, symbolItem* operator7, symbolItem* operator8){
  //-----------------------------------------------------------
  if (decide == 1) {
    // i
    if(operator1->parseSymbol == S_INT    ||
       operator1->parseSymbol == S_DOUBLE ||
       operator1->parseSymbol == S_STRING ||
       operator1->parseSymbol == S_I      ){
          return _I_;
    }
    else{
          return FAIL;
    }
  }
  // ----------------------------------------------------------
  else if(decide == 3){
    // (E)
    if(operator1->parseSymbol == I_LF &&
       operator2->parseSymbol == I_E  &&
       operator3->parseSymbol == I_RG ){
          return LF_E_RG;
    }
    // E + E
    else if(operator1->parseSymbol == I_E     &&
            operator2->parseSymbol == I_PLUS  &&
            operator3->parseSymbol == I_E     ){
              return E_PLUS_E;
    }
    // E * E
    else if(operator1->parseSymbol == I_E     &&
            operator2->parseSymbol == I_MUL   &&
            operator3->parseSymbol == I_E     ){
              return E_MUL_E;
    }
    else{
      return FAIL;
    }
  }
  //-----------------------------------------------------------
  else if(decide == 4){
    // f(E)
    if(operator1->parseSymbol == I_FUNC &&
       operator2->parseSymbol == I_LF   &&
       operator3->parseSymbol == I_E    &&
       operator4->parseSymbol == I_RG   ){
       return F_LF_E_RG;
     }
     else{
       return FAIL;
     }
  }
  //-----------------------------------------------------------
  else if(decide == 6){
    // f(E,E)
    if(operator1->parseSymbol == I_FUNC  &&
       operator2->parseSymbol == I_LF    &&
       operator3->parseSymbol == I_E     &&
       operator4->parseSymbol == I_COMMA &&
       operator5->parseSymbol == I_E     &&
       operator6->parseSymbol == I_RG    ){
       return F_LF_E_E_RG;
     }
     else{
       return FAIL;
     }
  }
  //-----------------------------------------------------------
  else if(decide = 8){
    // f(E,E,E)
    if(operator1->parseSymbol == I_FUNC  &&
       operator2->parseSymbol == I_LF    &&
       operator3->parseSymbol == I_E     &&
       operator4->parseSymbol == I_COMMA &&
       operator5->parseSymbol == I_E     &&
       operator6->parseSymbol == I_COMMA &&
       operator7->parseSymbol == I_E     &&
       operator8->parseSymbol == I_RG    ){
       return F_LF_E_E_E_RG;
     }
     else{
       return FAIL;
     }
  }
  //-----------------------------------------------------------
  else{
    return FAIL;
  }
}

int checkRules()
