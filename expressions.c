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

int errorE = OK;
tStack *stack;
int doIndentE = 0;

// KDYZ PRIJDE PRVNE TO CO JE NAPRAVO A PAK AZ TO CO PRIJDE NAHORE, PAK
// priklad prvni radek, druha cell ... +* ... prvne se provede *
// A=0  '<' = prvne se provede to co je nahore v komentu
// B=1  '=' = jen u '(' a ')' zároveň
// C=2  '>' = prvne se provede to co je napravo v komentu
// D=3      = done xd
// E=4      = chybný sytax i guess

int precedenceTable[TABLESIZE][TABLESIZE] =
{//  +-  *///    (     )     i     r     $ <- vstup, dolu stack
  {  C  ,  A  ,  A  ,  C  ,  A  ,  C  ,  C  }, // +-
  {  C  ,  C  ,  A  ,  C  ,  A  ,  C  ,  C  }, // *///
  {  A  ,  A  ,  A  ,  B  ,  A  ,  A  ,  E  }, // (
  {  C  ,  C  ,  E  ,  C  ,  E  ,  C  ,  C  }, // )
  {  C  ,  C  ,  E  ,  C  ,  E  ,  C  ,  C  }, // i
  {  A  ,  A  ,  A  ,  C  ,  A  ,  E  ,  C  }, // r (relationship operators)
  {  A  ,  A  ,  A  ,  E  ,  A  ,  A  ,  D  }  // $
};

int getPrecedenceIndex(token* tokenAct) { //vrací index z precedence tablu
  switch (tokenAct->type) {
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
    case DOCCOM: // stejný co literal
    case KEYWORD: //NONE
      if (tokenAct->type == KEYWORD && tokenAct->attribute.keyword != NONE) {
        return -1;
      }
    return 4;
  case LESSEQ: // <=
  case GREATEREQ: // >=
  case EQ: // ==
  case NOTEQ: // !=
  case LESS: // <
  case GREATER: // >
  case ASSIGN: // =
    return 5;
  case COLON: //$
  case EOL:
  case EOFTOKEN:
    return 6;
  default:
    return -1;
  }
}

int getPrecedenceOperatorValue(token* stackToken, token* vstupniToken) {
  int index1, index2 = 0;
  index1 = getPrecedenceIndex(stackToken);
  index2 = getPrecedenceIndex(vstupniToken);
  //printf("%did1, %did2\n", index1, index2);
  if (index1 == -1 || index2 == -1) {
    return E;
  }
  //printf("%d a %d pricemz tokeny meli\n", stackToken->type, vstupniToken->type);
  return precedenceTable[index1][index2];
}

int findRule(tokenStack *s, int *type, symbolTable* tableG, symbolTable* tableGG) {
  token* token, tokenPrvni, tokenDruhy;
  int state = 0;
  int zpracuj = 0;
  int rule = 0;
  int operacevtokenu = -1;
  while (rule == 0) {
    int type1, type2;
    sData* data = tokenStackTop(s);
    switch (state) {
      case 0:
        if (data->type == typeNonterm) {
          state = 1;
          tokenPrvni = *(data->token);
          type1 = data->dataType;
        } else if (data->type == typeToken) {
          if (data->token->type == RIGHTBRACKET) {
            state = 2;
            zpracuj = 1;
          } else if (data->token->type == INT || data->token->type == FLOAT || data->token->type == LITERAL || data->token->type == STR || data->token->type == NONE || data->token->type == DOCCOM) { //int, float, literal, str
            token = data->token;
            zpracuj = 2;
            state = 3;
            if (data->token->type == INT) {
              type1 = INT;
            } else if (data->token->type == FLOAT) {
              type1 = FLOAT;
            } else if (data->token->type == LITERAL || data->token->type == DOCCOM) {
              type1 = LITERAL;
            } else if (data->token->type == STR) {
              symtableItem* item = searchSymbolTableWithString(tableG, data->token->attribute.string->string);
              if (!item && tableGG) { //to jestli je item funkce se ošetřuje jinde prej, dává to PARSING_ERR (2)
                item = searchSymbolTableWithString(tableGG, data->token->attribute.string->string);
              }
              if (item && item->type == VARIABLE && item->elementType.variable->type == DATA_INT) {
                data->token->type = type1 = INT;
                data->token->attribute.INT = item->elementType.variable->value.INT;
              } else if (item && item->type == VARIABLE && item->elementType.variable->type == DATA_STRING) {
                data->token->type = type1 = LITERAL;
                stringClear(data->token->attribute.string);
                stringAddString(data->token->attribute.string, item->elementType.variable->value.string);
              } else if (item && item->type == VARIABLE && item->elementType.variable->type == DATA_FLOAT) {
                data->token->type = type1 = FLOAT;
                data->token->attribute.FLOAT = item->elementType.variable->value.FLOAT;
              } else { //není v symtablu
                //data->token->attribute.string->string;
                //token->type = data->token->type = type1 = KEYWORD;
                printf("%s není deklarováno\n", data->token->attribute.string->string);
              }
            } else {
              return -1; //dostanu něco jinýho než int, str, float, lit
            }
          } else {
            return -1; //dostanu něco jinýho než int, str, float, lit
          }
        } else {
          return -1; //dostanu něco jinýho než token a nonterm
        }
        break;
      case 1:
        if (data->token->type == PLUS || data->token->type == MINUS || data->token->type == TIMES || data->token->type == DIVFLT || data->token->type == DIVINT) {
          state = 2;
        } else if (data->token->type == LESS || data->token->type == GREATER || data->token->type == LESSEQ || data->token->type == GREATEREQ || data->token->type == EQ || data->token->type == NOTEQ || data->token->type == ASSIGN) {
          state = 2;
        } else {
          return -1; //neplatný výraz mezi 2mi věcmi
        }
        zpracuj = 3;
        operacevtokenu = data->token->type;
        break;
      case 2:
        if (data->type == typeNonterm) {
          if (zpracuj == 1) { //tady řeším závorky
            state = 4;
            tokenDruhy = *(data->token);
            type1 = data->dataType;
          } else {
            state = 3;
            tokenDruhy = *(data->token);
            type2 = data->dataType;
          }
        }
        break;
      case 3:
        if (state == 3) {
          if (data->type == typeHandler) {
            sData* newData = malloc(sizeof(sData));
            if (newData == NULL) {
              return -2; //intern err
            }
            newData->type = typeNonterm;
            if (zpracuj == 2) { //zpracování i -> E
              //printf("tady jsem jen kdyyž měním na Ečka\n");
              if (type1 == INT && data->token->type == INT) {
                int* hodnota = (int*) malloc(sizeof(int));
                int* typetokenu = (int*) malloc(sizeof(int));
                *hodnota = token->attribute.INT;
                *typetokenu = token->type;
                generateInstruction(I_PUSHS, hodnota, typetokenu, NULL);
              } else if (type1 == INT && data->token->type == STR) {
                //printf("je to něco ze symboltablu\n");
                char* promena = (char*) malloc(sizeof(char));
                promena = token->attribute.string->string;
                generateInstruction(I_PUSHS, promena, NULL, promena);
              }
            } else if (zpracuj == 1) { //tady zavorky
              token->attribute = tokenDruhy.attribute;
              newData->dataType = type1;
            } else if (type1 == INT && type2 == INT) {
              if (operacevtokenu == PLUS) {
                generateInstruction(I_ADDS, NULL, NULL, NULL);
                //token->attribute.INT = tokenDruhy.attribute.INT + tokenPrvni.attribute.INT;
              } else if (operacevtokenu == MINUS) {
                generateInstruction(I_SUBS, NULL, NULL, NULL);
                //token->attribute.INT = tokenDruhy.attribute.INT - tokenPrvni.attribute.INT;
              } else if (operacevtokenu == TIMES) {
                generateInstruction(I_MULS, NULL, NULL, NULL);
                //token->attribute.INT = tokenDruhy.attribute.INT * tokenPrvni.attribute.INT;
              } else if (operacevtokenu == DIVINT) {
                if (tokenPrvni.attribute.INT == 0) {
                  return -4; //dělení nulou lmao
                }
                generateInstruction(I_IDIVS, NULL, NULL, NULL);
                token->attribute.INT = tokenDruhy.attribute.INT / tokenPrvni.attribute.INT;
              } else if (operacevtokenu == DIVFLT) {
                if (tokenPrvni.attribute.INT == 0) {
                  return -4; //dělení nulou lmao
                }
                token->attribute.FLOAT = (float)tokenDruhy.attribute.INT / (float)tokenPrvni.attribute.INT;
                type1 = FLOAT;
              } else if (operacevtokenu == LESS) {
                if (tokenDruhy.attribute.INT < tokenPrvni.attribute.INT) {
                  token->attribute.BOOL = true;
                } else {
                  token->attribute.BOOL = false;
                }
                type1 = BOOL;

              } else if (operacevtokenu == GREATER) {
                generateInstruction(I_GTS, NULL, NULL, NULL);
              } else if (operacevtokenu == LESSEQ) {

              } else if (operacevtokenu == GREATEREQ) {

              } else if (operacevtokenu == EQ) {

              } else if (operacevtokenu == NOTEQ) {

              } else if (operacevtokenu == ASSIGN) {
                printf("%d budu zapisovat do %s\n", token->attribute.INT, data->token->attribute.string->string);
              } else {
                return -1; //neplatná operace mezi 2mi inty
              }
            } else if (type1 == LITERAL && type2 == LITERAL) {
              if (operacevtokenu == PLUS) {
                stringAddString(tokenDruhy.attribute.string, tokenPrvni.attribute.string->string);
                token->attribute.string = tokenDruhy.attribute.string;
              } else {
                return -1; //neplatná operace
              }
            } else if (type1 == FLOAT && type2 == FLOAT) {
              if (operacevtokenu == PLUS) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT + tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == MINUS) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT - tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == TIMES) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT * tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == DIVFLT) {
                if (tokenPrvni.attribute.FLOAT == 0) {
                  return -4; //dělení nulou lmao
                }
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT / tokenPrvni.attribute.FLOAT;
              } else {
                return -1; //neplatná operace
              }
            } else if (type1 == INT && type2 == FLOAT) {
              type1 = FLOAT;
              if (operacevtokenu == PLUS) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT + tokenPrvni.attribute.INT;
              } else if (operacevtokenu == MINUS) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT - tokenPrvni.attribute.INT;
              } else if (operacevtokenu == TIMES) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT * tokenPrvni.attribute.INT;
              } else if (operacevtokenu == DIVFLT) {
                if (tokenPrvni.attribute.INT == 0) {
                  return -4; //dělení nulou lmao
                }
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT / tokenPrvni.attribute.INT;
              } else {
                return -1; //neplatná operace
              }
            } else if (type1 == FLOAT && type2 == INT) {
              type2 = FLOAT;
              if (operacevtokenu == PLUS) {
                token->attribute.FLOAT = tokenDruhy.attribute.INT + tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == MINUS) {
                token->attribute.FLOAT = tokenDruhy.attribute.INT - tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == TIMES) {
                token->attribute.FLOAT = tokenDruhy.attribute.INT * tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == DIVFLT) {
                if (tokenPrvni.attribute.FLOAT == 0) {
                  return -4; //dělení nulou lmao
                }
                token->attribute.FLOAT = tokenDruhy.attribute.INT / tokenPrvni.attribute.FLOAT;
              } else {
                return -1; //neplatná operace
              }
            } else if (type1 == INT && type2 == KEYWORD) {
              //printf("%d budu zapisovat do %s\n", token->attribute.INT, tokenDruhy.attribute.string->string);
            } else {
              return -3; //neplatná operace mezi dvěmy typy, semantická chyba
            }

            if (data != NULL) {
              tokenStackPop(s);
            }

            *type = type1; //návratový typ
            //printf("%d a %d typy nakonci\n", type1, type2);
            newData->dataType = type1;
            newData->token = token;
            tokenStackPush(s,newData);
            rule = zpracuj;
            continue;
          } else {
            return -1; //toto by se asi ani nemělo stát
          }
        }
        break;
      case 4:
        if (data->token->type == LEFTBRACKET) {
          state = 3;
        } else {
          return -1; //pro každou pravou závorku musí být levá
        }
        break;
      }

      if (data->token->type != COLON) {
        tokenStackPop(s);
      } else {
        return rule;
    }
  }
  return rule;
}

precendentExpression* doPrecedenceOperation(token tokenAct, symbolTable* tableG, symbolTable* tableGG) {
  precendentExpression* exp = malloc(sizeof(precendentExpression));
  if (!exp) {
    return NULL;
  }

  token* current = &tokenAct;
  tokenStack *s = (tokenStack*) malloc(sizeof(tokenStack));
  if(s == NULL){
    exp->error = INTERN_ERR;
    return exp;
  }
  tokenStackInit(s);

  sData *dataPred = malloc(sizeof(sData)); //dávám dolar do stacku
  if(dataPred == NULL){
    exp->error = INTERN_ERR;
    return exp;
  }
  dataPred->type = typeToken;
  token dolar;
  dolar.type = COLON;
  dataPred->token = &dolar;
  tokenStackPush(s, dataPred);

  token tmptkn;
  int navr = 0;

  while(1) { //dostanu se z toho daijoubně
    sData* termData = getTerminalData(s);
    token* token = termData->token;
    int operation = getPrecedenceOperatorValue(token, current); //token = ze stacku, current = ze scanneru

    if (operation == A) { //0 +- atd //zaměň a za a< na zásobníku & push(b) & přečti další symbol b ze vstupu
      sData *data = malloc(sizeof(sData));
      if (data == NULL) {
        exp->error = INTERN_ERR;
        return exp;
      }
      data->type = typeToken;
      data->token = current;
      addHandler(s, termData); //dá zarážku na vrchol zásobníku
      tokenStackPush(s,data);
    } else if (operation == B) { //1 () //push(b) & přečti další symbol b ze vstupu
      sData *data = malloc(sizeof(sData));
      if (data == NULL) {
        exp->error = INTERN_ERR;
        return exp;
      }
      data->type = typeToken;
      data->token = current;
      tokenStackPush(s,data);
    } else if (operation == C) { //2  if <y je na vrcholu zásobníku and r: A→y∈P then zaměň <y za A & vypiš r na výstup else chyba
      int a = findRule(s, &navr, tableG, tableGG); //THE REST OF THE LOVELY OWL
      if (a == -1) {
        exp->error = PARSING_ERR;
        return exp;
      } else if (a == -2) {
        exp->error = INTERN_ERR;
        return exp;
      } else if (a == -3) {
        exp->error = SEM_DEF_ERR;
        return exp;
      } else if (a == -4) {
        exp->error = DIVISION_BY_ZERO;
        return exp;
      }
      continue; //nenačítat další token ze vstupu
    } else if (operation == D) { //D jako done xddddddd
        if (navr == INT) {
          exp->returnType = DATA_INT;
          exp->returnValue.INT = s->top->data->token->attribute.INT;
        } else if (navr == LITERAL) {
          exp->returnType = DATA_STRING;
          exp->returnValue.string = s->top->data->token->attribute.string->string;
        } else if (navr == FLOAT) {
          exp->returnType = DATA_FLOAT;
          exp->returnValue.FLOAT = s->top->data->token->attribute.FLOAT;
        }
        exp->error = OK;
        return exp;
    } else if (operation == E) { //errorE
        exp->error = PARSING_ERR;
        return exp;
    }

    current = malloc(sizeof(token)); //načítáme další token ze vstupu
    tmptkn = nextToken(&errorE, stack, doIndentE);
    if (errorE != OK) {
      exp->error = errorE;
      return exp;
    }
    current->attribute = tmptkn.attribute;
    current->type = tmptkn.type;
  }
}
/*
void main() {
  stack = malloc(sizeof(tStack));
  stackInit(stack);
  stackPush(stack, 0);
  symbolTable *table = initSymbolTable(MAX_SYMTABLE_SIZE);
  symbolTable* table2 = initSymbolTable(MAX_SYMTABLE_SIZE);
  token TokenUwu, TokenOwo, TokenQQ;
  smartString *s = malloc(sizeof(smartString));
  if (s == NULL){
      return;
  }
  stringInit(s);
  stringAddString(s, "uwu");
  TokenUwu.attribute.string = s;
  TokenUwu.type = STR;
  insertSymbolTable(table, TokenUwu, VARIABLE);
  symtableItem* item = searchSymbolTableWithString(table, "uwu");
  item->elementType.variable->value.INT = 5;
  item->elementType.variable->type = DATA_INT;

  token token1;
  token1 = nextToken(&errorE, stack, doIndentE);
  if (errorE != OK) {
    printf("%d\n", errorE);
    return;
  }
  precendentExpression* exp = doPrecedenceOperation(token1, table, table2);
  if (exp == NULL || exp->error != OK) {
    printf("%d\n", exp->error);
    return;
  }
  if (*exp->returnType == INT) {
    printf("'%d'vracím jako int\n", exp->returnToken->attribute.INT);
  } else if (*exp->returnType == LITERAL) {
    printf("'%s'vracím jako string\n", exp->returnToken->attribute.string->string);
  } else if (*exp->returnType == FLOAT) {
    printf("'%f'vracím float\n", exp->returnToken->attribute.FLOAT);
  } else if (*exp->returnType == BOOL) {
    printf("'%d'vracím pravdivostní hodnotu\n", exp->returnToken->attribute.BOOL);
  }
}*/
