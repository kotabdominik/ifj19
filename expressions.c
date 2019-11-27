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
    case KEYWORD: //NONE
      if (tokenAct.type == KEYWORD && tokenAct.attribute.keyword != NONE) {
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

int getPrecedenceOperatorValue(token stackToken, token vstupniToken) {
  int index1, index2 = 0;
  index1 = getPrecedenceIndex(stackToken);
  index2 = getPrecedenceIndex(vstupniToken);
  if (index1 == -1 || index2 == -1) {
    printf("error\n");
  }
  printf("%d a %d jsou indexy z getPrecedenceIndex\n", index1, index2);
  printf("%d a %d pricemz tokeny meli\n", stackToken.type, vstupniToken.type);
  return *precedenceTable[index1, index2];
}

precendentExpression* doPrecedenceOperation(token tokenAct) {
  precendentExpression* exp = malloc(sizeof(precendentExpression));
  if (!exp) {
    //malloc pp
  }
  exp->Tree = NULL;
  exp->ReturnToken = NULL;
  token current;
  int readNextToken = 1;
  tokenStack *s = (tokenStack*) malloc(sizeof(tokenStack));
  if(s == NULL){
    //malloc pp
  }
  tokenStackInit(s);

  SData *dataPred = malloc(sizeof(SData)); //dávám dolar do stacku idk jestli mám
  if(dataPred == NULL){
    //yeet
  }
  dataPred->Type = type_token;
  token dolar;
  dolar.type = COLON;
  dataPred->Atr.Token = &dolar;
  tokenStackPush(s,dataPred);

  current = tokenAct;
  token tmptkn;
  //https://cdn.discordapp.com/attachments/591341433353666582/632206569551167488/unknown.png
  while(readNextToken || getTerminalData(s) != NULL){
    SData* termData = getTerminalData(s);
    if (termData->Type == type_handler) { //je token vždy
      printf("yeet handler popuju dál\n");
    }
    token token;
    if(termData != NULL)
      token = *(termData->Atr.Token);
    if(&current != NULL){
      if(current.type == EOL || current.type == EOFTOKEN || current.type == COLON) {
        readNextToken = false;
        return NULL; //tmp, odstranit potom
      }
    }

    //token = nextToken(&error, stack, doIndent);

    int operation = getPrecedenceOperatorValue(token, current); //token = ze stacku, current = ze scanneru

    if (operation == A) { //0  if <y je na vrcholu zásobníku and r: A→y∈P then zaměň <y za A & vypiš r na výstup else chyba
      //findRule(s); //THE REST OF THE FUCKING OWL
      printf("aa\n");
      //continue; //nenačítat token
    } else if (operation == B) { //1 () //push(b) & přečti další symbol b ze vstupu
      SData *data = malloc(sizeof(SData));
      if(data == NULL){
        //yeet
      }
      data->Type = type_token;
      data->Atr.Token = &current;
      tokenStackPush(s,data);
    } else if (operation == C) { //2 +- atd //zaměň a za a< na zásobníku & push(b) & přečti další symbol b ze vstupu
      addHandler(s,termData); //dastali jsme z getTerminalData(s), vraci ze zasobniku data prvnihu terminalu
      printf("dávám zarážku\n");
      SData *data = malloc(sizeof(SData));
      if(data == NULL){
        //yeet
      }
      data->Type = type_token;
      data->Atr.Token = &current;
      tokenStackPush(s,data);
    } else if (operation == E) { //error
      printf("error, neplatná operace mezi dvěmi věcmi idk\n");
      return NULL;
    }

    if (readNextToken) {
      tmptkn = nextToken(&error, stack, doIndent);
      current = tmptkn;
    }
  }
}

void main() {

  stack = malloc(sizeof(tStack));
  stackInit(stack);
  stackPush(stack, 0);
  setFile("txt.txt");
  token token1, token2;

  token1 = nextToken(&error, stack, doIndent);
  //token2 = nextToken(&error, stack, doIndent);

  doPrecedenceOperation(token1);
}
