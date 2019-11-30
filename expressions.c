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
  if (index1 == -1 || index2 == -1) {
    printf("error\n");
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
    sData* data = tokenStackTop(s);
    int type1, type2;
    switch (state) {
      case 0:
        if (data->type == typeNonterm) {
          state = 1;
          type1 = data->dataType;
          tokenPrvni = *(data->token);
        } else if (data->type == typeToken) {
          if (data->token->type == RIGHTBRACKET) {
            state = 2;
            zpracuj = 1;
          } else if (data->token->type == INT) {
            token = data->token;
            zpracuj = 2; //????????????
            state = 3;
            type1 = INT;
          } else if (data->token->type == FLOAT) {
            token = data->token;
            state = 3;
            zpracuj = 2;
            type1 = FLOAT;
          } else if (data->token->type == LITERAL) {
            token = data->token;
            state = 3;
            zpracuj = 2;
            type1 = LITERAL;
            printf("%s\n", data->token->attribute.string->string);
          } else if (data->token->type == STR) {
            //prohledávám symtable xd
            //type1 = idk
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
          //potom neco dodelat na logicky
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
          } else {
            state = 3;
            tokenDruhy = *(data->token);
          }
        }
        break;
      case 3:
        if (state == 3) {
          if(data->type == typeHandler) {
            sData* newData = malloc(sizeof(sData));
            if (newData == NULL) {
              //yeet
            }
            newData->type = typeNonterm;
            if (zpracuj == 2) { //zpracování i -> E
              //printf("tady jsem jen kdyyž měním na Ečka\n");
            } else if (zpracuj == 1) {
              token->attribute = tokenDruhy.attribute;
            } else if (type1 == INT) {
              if (operacevtokenu == PLUS) {
                token->attribute.INT =  tokenDruhy.attribute.INT + tokenPrvni.attribute.INT;
              } else if (operacevtokenu == MINUS) {
                token->attribute.INT = tokenDruhy.attribute.INT - tokenPrvni.attribute.INT;
              } else if (operacevtokenu == TIMES) {
                token->attribute.INT = tokenDruhy.attribute.INT * tokenPrvni.attribute.INT;
              } else if (operacevtokenu == DIVINT) {
                token->attribute.INT = tokenDruhy.attribute.INT / tokenPrvni.attribute.INT;
              } else {
                printf("syntaxx pepe\n");
                return -1;
              }
            } else if (type1 == LITERAL) {
              if (operacevtokenu == PLUS) {
                stringAddString(tokenDruhy.attribute.string, tokenPrvni.attribute.string->string);
                token->attribute.string = tokenDruhy.attribute.string;
              } else {
                printf("jiná operace nad stringama by neměla být\n");
                return -1;
              }
            } else if (type1 == FLOAT) {
              if (operacevtokenu == PLUS) {
                token->attribute.FLOAT =  tokenDruhy.attribute.FLOAT + tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == MINUS) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT - tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == TIMES) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT * tokenPrvni.attribute.FLOAT;
              } else if (operacevtokenu == DIVINT) {
                token->attribute.FLOAT = tokenDruhy.attribute.FLOAT / tokenPrvni.attribute.FLOAT;
              } else {
                printf("syntaxx pepe\n");
                return -1;
              }
            }

            if(data != NULL) {
              tokenStackPop(s);
            }

            *type = type1;
            newData->dataType = type1;
            newData->token = token;
            tokenStackPush(s,newData);
            rule = zpracuj;
            continue;
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

  token token2 = nextToken(&error, stack, doIndent);
  if (token2.type == EOL || token2.type == EOL) {
    int typ;
    if (tokenAct.type == INT) {
      typ = INT;
    } else if (tokenAct.type == LITERAL) {
      typ = LITERAL;
    }
    exp->returnToken = &tokenAct;
    exp->returnType = &typ;
    return exp;
  }

  token2 = ungetToken(&error, stack, doIndent);
  token* current = &token2;

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
  int navr;

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
      printf("ukonci uspesne\n");
      exp->returnToken = current;
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

  token token1;
  token1 = nextToken(&error, stack, doIndent);
  precendentExpression* exp = doPrecedenceOperation(token1);
  if (exp == NULL) {
    return;
  }
  if (*exp->returnType == INT) {
    printf("'%d'vracím\n", exp->returnToken->attribute.INT);
  } else if (*exp->returnType == LITERAL) {
    printf("'%s'vracím\n", exp->returnToken->attribute.string->string);
  } else if (*exp->returnType == FLOAT) {
    printf("'%f'vracím\n", exp->returnToken->attribute.FLOAT);
  }
}
