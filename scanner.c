/**
  * scanner.c
  * Project IFJ19
  *
  * Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
  * Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
  * Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
  * Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)
  *
  * Brief: scanner and Lexical analyzer
  *
  */

#include "scanner.h"

#define STATE_START 100



#define STATE_EQUAL 101
#define STATE_GRTER 102
#define STATE_LSSER 103
#define STATE_NOTEQ 104
#define STATE_COMMT 105
#define STATE_F2 106
#define STATE_P1 107
//#define STATE_NUEXP 109
#define STATE_F3 1091
#define STATE_P2 1092
#define STATE_P3 1093
#define STATE_NUSGN 110
#define STATE_NUEND 111
#define STATE_STRNG 112
#define STATE_STRLT 113
#define STATE_ESCAP 114




 FILE *SourceFile;
 //smartString *s = malloc(sizeof(smartString));


token nextToken(token *Token) {
/*
  smartString *s = malloc(sizeof(smartString)); //check
  if (s == NULL){
      return INTERN_ERR;
  }
  Token.attribute.string = s;

  int state = STATE_START;

  char c,tmp;


  while (1){
    c = getchar()
    switch (state)
    {
      case (STATE_START):

    }

  }*/
 token Token;

 char c,tmp;

 c = getchar()
 while((c = getchar() != EOF){
  /* smartString *s = malloc(sizeof(smartString)); //check
   if (smartString == NULL){
     return INTERN_ERR;
   }*/
  int state = STATE_START;
  while((c = getchar() != EOF){


    switch (c) {
                  // SINGULAR //
      //TODO
      case ',':
        break;

      case '+':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'+');
        Token.attribute.string = s;

        Token.type = PLUS;
        break;

      case '-':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'-');
        Token.attribute.string = s;

        Token.type = MINUS;
        break;

      case '*':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'*');
        Token.attribute.string = s;

        Token.type = TIMES;
        break;

      case '(':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'(');
        Token.attribute.string = s;

        Token.type = LEFTBRACKET;
        break;

      case ')':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,')');
        Token.attribute.string = s;

        Token.type = RIGHTBRACKET;
        break;

  /*    case ';':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,';');
        Token.attribute.string = s;

        Token.type = SEMICOLON;
        break;*/

      case ':':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,':');
        Token.attribute.string = s;

        Token.type = COLON;
        break;
                  // MULTIPLE //
      case '=':

        c = getchar();
        if (c == '='){
          smartString *s = malloc(sizeof(smartString));
          if (s == NULL){
              return INTERN_ERR;
          }
          stringInit(s);
          stringAddChar(s,'=');
          stringAddChar(s,'=');
          Token.attribute.string = s;

          Token.type = EQ;
          break;
        }
        else {
          smartString *s = malloc(sizeof(smartString));
          if (s == NULL){
              return INTERN_ERR;
          }
          stringInit(s);
          stringAddChar(s,'=');
          Token.attribute.string = s;

          Token.type = ASSIGN;
          continue;
        }

      case '>':
        c = getchar();
        if (c == '='){
          smartString *s = malloc(sizeof(smartString));
          if (s == NULL){
              return INTERN_ERR;
          }
          stringInit(s);
          stringAddChar(s,'>');
          stringAddChar(s,'=');
          Token.attribute.string = s;

          Token.type = GREATEREQ;
          break;
        }
        else {
          smartString *s = malloc(sizeof(smartString));
          if (s == NULL){
              return INTERN_ERR;
          }
          stringInit(s);
          stringAddChar(s,'>');
          Token.attribute.string = s;
          Token.type = GREATER;
          continue;
        }

      case '<':
          c = getchar();
          if (c == '='){
            smartString *s = malloc(sizeof(smartString));
            if (s == NULL){
                return INTERN_ERR;
            }
            stringInit(s);
            stringAddChar(s,'<');
            stringAddChar(s,'=');
            Token.attribute.string = s;

            Token.type = LESSEQ;
            break;
          }
          else {
            smartString *s = malloc(sizeof(smartString));
            if (s == NULL){
                return INTERN_ERR;
            }
            stringInit(s);
            stringAddChar(s,'<');
            Token.attribute.string = s;

            Token.type = LESS;
            continue;
          }

      case '!':
      c = getchar();
      if (c == '='){
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,'!');
        stringAddChar(s,'=');
        Token.attribute.string = s;

        Token.type = NOTEQ;
        break;
      }
      else {
        return LEXICAL_ERR;
      }

      case '"':
        if ((c = getchar) != '"')
          return LEXICAL_ERR;
        if ((c = getchar) != '"')
          return LEXICAL_ERR;

        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        Token.type = DOCCOM;

        while (1){
          c = getchar();
          if ((c = getchar()) != '"')
            if ((c = getchar()) != '"')
            else stringAddChar(s,c);
              if ((c = getchar()) != '"')
                else {stringAddChar(s,'"'); stringAddChar(s,'"');}
                break;
          stringAddChar(s,c);
        }
        Token.attribute.string = s;
        break;

      case '#':
         while ((c = getchar()) != EOL || c = getchar()) != EOF)
          c = getchar();
         break;

      case EOL:
        c = getchar();
        continue;

      default:
      if (isalpha(c) || c == '_'){ //Robíme basic string
        smartString *s = malloc(sizeof(smartString));
        stringInit(s);
        if (s == NULL){
            return INTERN_ERR;
        }
        Token.attribute.string = STR;

        while(1){
          if ( !(isalpha(c)) || !(isalnum(c) || (c != '_') ){
            continue;
          }
          stringAddChar(s,c);
          c = getchar();
        }
      }

      if (isalnum(c)){ //Robíme číslo
        smartString *s = malloc(sizeof(smartString));
        stringInit(s);
        if (s == NULL){
            return INTERN_ERR;
        }
        stringAddChar(s,c);
        getchar(c);

        state = STATE_F2;
        int isINTorFLT = 0; //0 is for INT, 1 is for FLOAT
        while (1){
          switch (state) {
            case (STATE_F2): //Začiatočný state čísla
              if(c == '.'){ //Bude float
                stringAddChar(s,c);
                c = getchar();
                state = STATE_P1;
              }
              else if(c == 'E' || c == 'e'){ //Bude Exp
                stringAddChar(s,c);
                c = getchar();
                state = STATE_P2;
              }
              else if(isalnum(c)){ //Bude cislo
                stringAddChar(s,c);
                c = getchar();
                state = STATE_F2;
              }
              else{
                Token.attribute.string = s;
                Token.type = INT;
                state = STATE_START;
                break; //Koniec integer čísla
              }


            case (STATE_P1): //Je float
              if(isalnum(c)){ //Musí nasledovať číslo
                stringAddChar(s,c);
                c = getchar();
                state = STATE_F3;
              }
              else
                return LEXICAL_ERR;
              break;

            case (STATE_F3): //Je float v tvare (example) 132.1_
            isINTorFLT = 1; ///Kontrola že je TYP FLOATEXP
              if(c == 'E' || c == 'e'){ //Bude 132.1e
                stringAddChar(s,c);
                c = getchar();
                state = STATE_P2;
              }
              else if (isalnum(c)) { //Bude 132.12
                stringAddChar(s,c);
                c = getchar();
                state = STATE_F3; //Vráti sa tu
              }
              else{
                Token.attribute.string = s;
                Token.type = FLOAT;
                state = STATE_START;
                break; //Koniec float čísla
              }

            case (STATE_P2):
              if (isalnum(c)){
                stringAddChar(s,c);
                c = getchar();
                state = STATE_F4;
              }
              else if (c == '+' || c == '-'){
                stringAddChar(s,c);
                c = getchar();
                state = STATE_P3;
              }
              else
                return LEXICAL_ERR;
              break;

              case (STATE_P3):
                if (isalnum(c)){
                  stringAddChar(s,c);
                  c = getchar();
                  state = STATE_F4;
                }
                else
                  return LEXICAL_ERR;
                break;

              case (STATE_F4):
              if (isalnum(c)){
                stringAddChar(s,c);
                c = getchar();
                state = STATE_F4;
              }
              else{
                Token.attribute.string = s;
                if (isINTorFLT == 1){
                  Token.type = FLOATEXP;
                  isINTorFLT = 0;
                  break; //Koniec float s e v čísle
                }
                else {
                  Token.type = INTEXP;
                  break; //Koniec integer s e v čísle
                }
                state = STATE_START;
              }
          }
          break; //Vraciam sa do switch (c)
        }





      }




    }




  }

}
