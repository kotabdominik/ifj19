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
symbolTable *table;

// KDYZ PRIJDE PRVNE TO CO JE NAPRAVO A PAK AZ TO CO PRIJDE NAHORE, PAK
// priklad prvni radek, druha cell ... +* ... prvne se provede *
// A=0  '<' = prvne se provede to co je nahore v komentu
// B=1  '=' = jen u '(' a ')' zároveň
// C=2  '>' = prvne se provede to co je napravo v komentu
// D=3      = done xd
// E=4      = chybný sytax i guess

int precedenceTable[TABLESIZE][TABLESIZE] =
  {  //  +-  *///    (     )     i     r     $ <- vstup, dolu stack
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
  printf("%d je vstupniToken type\n", vstupniToken->type);
  if (index1 == -1 || index2 == -1) {
    printf("error\n");
    return -1;
  }
  //printf("%d a %d pricemz tokeny meli\n", stackToken->type, vstupniToken->type);
  return precedenceTable[index1][index2];
}

int findRule(tokenStack *s, int *type) {
  token* token, tokenPrvni, tokenDruhy;
  int state = 0;
  int zpracuj = 0;
  int rule = 0;
  int operacevtokenu = -1;
  while (rule == 0) {
    printf("yay\n");
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
          } else if (data->token->type == INT || data->token->type == FLOAT || data->token->type == LITERAL || data->token->type == STR) { //int, float, literal, str
            token = data->token;
            zpracuj = 2;
            state = 3;
            if (data->token->type == INT) {
              type1 = INT;
            } else if (data->token->type == FLOAT) {
              type1 = FLOAT;
            } else if (data->token->type == LITERAL) {
              type1 = LITERAL;
            } else if (data->token->type == STR) {
              symtableItem* item = searchSymbolTableWithString(table, data->token->attribute.string->string);
              if (item && item->elementType.variable->type == DATA_INT) {
                data->token->type = type1 = INT;
                data->token->attribute.INT = item->elementType.variable->value.INT;
              } else if (item && item->elementType.variable->type == DATA_STRING) {
                data->token->type = type1 = LITERAL;
                stringClear(data->token->attribute.string);
                stringAddString(data->token->attribute.string, item->elementType.variable->value.string);
              } else if (item && item->elementType.variable->type == DATA_FLOAT) {
                data->token->type = type1 = FLOAT;
                data->token->attribute.FLOAT = item->elementType.variable->value.FLOAT;
              } else {
              //prohledávám symtable xd
              //type1 = idk
                printf("%d je type\n", type1);
                return -1;
              }
            } else {
              return -1;
            }
          } else {
            return -1;
          }
        } else {
          return -1;
        }
        break;
      case 1:
        if (data->token->type == PLUS || data->token->type == MINUS || data->token->type == TIMES || data->token->type == DIVFLT || data->token->type == DIVINT) {
          state = 2;
        } else if (data->token->type == LESS || data->token->type == GREATER || data->token->type == LESSEQ || data->token->type == GREATEREQ || data->token->type == EQ || data->token->type == NOTEQ) {
          state = 2;
        } else {
          printf("syntaxerr\n");
          return -1;
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
            //type2 = data->dataType;
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
              //yeet
            }
            newData->type = typeNonterm;
            if (zpracuj == 2) { //zpracování i -> E
              //printf("tady jsem jen kdyyž měním na Ečka\n");
            } else if (zpracuj == 1) { //tady yavorkz
              token->attribute = tokenDruhy.attribute;
              newData->dataType = type1;
            } else if (type1 == INT && type2 == INT) {
              if (operacevtokenu == PLUS) {
                token->attribute.INT = tokenDruhy.attribute.INT + tokenPrvni.attribute.INT;
              } else if (operacevtokenu == MINUS) {
                token->attribute.INT = tokenDruhy.attribute.INT - tokenPrvni.attribute.INT;
              } else if (operacevtokenu == TIMES) {
                token->attribute.INT = tokenDruhy.attribute.INT * tokenPrvni.attribute.INT;
              } else if (operacevtokenu == DIVINT) {
                token->attribute.INT = tokenDruhy.attribute.INT / tokenPrvni.attribute.INT;
              } else if (operacevtokenu == DIVFLT) {
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

              } else if (operacevtokenu == LESSEQ) {

              } else if (operacevtokenu == GREATEREQ) {

              } else if (operacevtokenu == EQ) {

              } else if (operacevtokenu == NOTEQ) {

              } else if (operacevtokenu == ASSIGN) {

              } else {
                printf("syntaxx pepe\n");
                return -1;
              }
            } else if (type1 == LITERAL && type2 == LITERAL) {
              if (operacevtokenu == PLUS) {
                stringAddString(tokenDruhy.attribute.string, tokenPrvni.attribute.string->string);
                token->attribute.string = tokenDruhy.attribute.string;
              } else {
                printf("jiná operace nad stringama by neměla být\n");
                return -1;
              }
            } else if (type1 == FLOAT && type2 == FLOAT) {
              if (operacevtokenu == PLUS) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT + tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == MINUS) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT - tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == TIMES) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT * tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == DIVFLT) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT / tokenPrvni.attribute.FLOAT;
              } else {
                printf("syntaxx pepe\n");
                return -1;
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
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT / tokenPrvni.attribute.INT;
              } else {
                printf("syntaxx pepe\n");
                return -1;
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
                token->attribute.FLOAT = tokenDruhy.attribute.INT / tokenPrvni.attribute.FLOAT;
              } else {
                printf("syntaxx pepe\n");
                return -1;
              }
            } else {
              printf("operace mezi 2 špatnými typy\n");
              return -1;
            }

            if (data != NULL) {
              tokenStackPop(s);
            }

            *type = type1; //návratový typ
            printf("%d a %d typy nakonci\n", type1, type2);
            newData->dataType = type1;
            newData->token = token;
            tokenStackPush(s,newData);
            rule = zpracuj;
            continue;
          } else {
            printf("toto bz se nemelo stat\n");
          }
        }
        break;
      case 4:
        if (data->token->type == LEFTBRACKET) {
          state = 3;
        } else {
          return -1;
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

precendentExpression* doPrecedenceOperation(token tokenAct) {
  precendentExpression* exp = malloc(sizeof(precendentExpression));
  if (!exp) {
    //malloc pp
  }

  token* current = &tokenAct;
  tokenStack *s = (tokenStack*) malloc(sizeof(tokenStack));
  if(s == NULL){
    //malloc pp
  }
  tokenStackInit(s);

  sData *dataPred = malloc(sizeof(sData)); //dávám dolar do stacku
  if(dataPred == NULL){
    //yeet
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
        //yeet
      }
      data->type = typeToken;
      data->token = current;
      addHandler(s, termData); //dá zarážku na vrchol zásobníku
      tokenStackPush(s,data);
    } else if (operation == B) { //1 () //push(b) & přečti další symbol b ze vstupu
      sData *data = malloc(sizeof(sData));
      if (data == NULL) {
        //yeet
      }
      data->type = typeToken;
      data->token = current;
      tokenStackPush(s,data);
    } else if (operation == C) { //2  if <y je na vrcholu zásobníku and r: A→y∈P then zaměň <y za A & vypiš r na výstup else chyba
      int a = findRule(s, &navr); //THE REST OF THE LOVELY OWL
      if (a == -1) {
        printf("syntax error\n");
        return NULL;
      }
      continue; //nenačítat další token ze vstupu
    } else if (operation == D) { //D jako done xddddddd
      exp->returnToken = s->top->data->token;
      exp->returnType = &navr;
      return exp;
    } else if (operation == E) { //error
      printf("neplatná operace mezi dvěmi věcmi v precedenční tabulce\n");
      return NULL;
    }

    current = malloc(sizeof(token)); //načítáme další token ze vstupu
    tmptkn = nextToken(&error, stack, doIndent);
    current->attribute = tmptkn.attribute;
    current->type = tmptkn.type;
  }
}

void main() {
  stack = malloc(sizeof(tStack));
  stackInit(stack);
  stackPush(stack, 0);

  table = initSymbolTable(MAX_SYMTABLE_SIZE);
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
  item->elementType.variable->value.string = malloc(sizeof(char)*5);
  strcpy(item->elementType.variable->value.string, "uwu\0");
  item->elementType.variable->type = DATA_STRING;

  token token1;
  token1 = nextToken(&error, stack, doIndent);
  precendentExpression* exp = doPrecedenceOperation(token1);
  if (exp == NULL) {
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
}
