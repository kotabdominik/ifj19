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

#define STATE_F2 300
#define STATE_F3 301
#define STATE_F4 302
#define STATE_P1 303
#define STATE_P2 304
#define STATE_P3 305

#define STATE_F22 400
#define STATE_P10 401
#define STATE_P11 402
#define STATE_P12 403
#define STATE_P13 404





FILE *SourceFile;



nextToken() {

 token Token;

 char c,tmp;

 c = getchar()
 while((c = getchar() != EOF){

  int state = STATE_START;
  while((c = getchar() != EOF){
/////////////check prepisovanie c s podmienkou while

    switch (c) {
                  // SINGULAR //

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
          if (c == EOF)
            return LEXICAL_ERR;
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
        Token.type = STR;

        while(1){
          if ( !(isalpha(c)) || !(isalnum(c) || (c != '_') ){
            break;
          }
          stringAddChar(s,c);
          c = getchar();
        }
        int i = 0;
        if ((i = stringIsKeyword(s)) != -1)
          Token.attribute.keyword = i;
        else
          Token.attribute.string = s;
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
        char *ptr; //pri prevode
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
                Token.attribute.INT = strtod(s,&ptr);
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
                Token.attribute.FLOAT = strtod(s,&ptr);
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
                if (isINTorFLT == 1){
                  Token.attribute.FLOAT = strtod(s,&ptr);
                  Token.type = FLOAT;
                  isINTorFLT = 0;
                  break; //Koniec float
                }
                else {
                  Token.attribute.INT = strtod(s,&ptr);
                  Token.type = INT;
                  break; //Koniec integer
                }
                state = STATE_START;
              }
          }

          break; //Vraciam sa do switch (c)
        }
      }

      if (c == '\'') { // Robíme literál
              smartString *s = malloc(sizeof(smartString));
              stringInit(s);
              if (s == NULL){
                  return INTERN_ERR;
              }
              stringAddChar(s,c);
              getchar(c);
              state = STATE_P10;

              while (1){
                if (c == EOF)
                  return LEXICAL_ERR;
                switch (state) {
                  case (STATE_P10):
                    if (c > 31 && c != 92 && c != 39){ // '\'' && '\\' && '\,' //normalny znak
                      stringAddChar(s,c);
                      c = getchar();
                      state = STATE_P10;
                    }
                    else if (c == 39){ //Apostrof teda koniec stringu
                      stringAddChar(s,c);
                      c = getchar();
                      state = STATE_F22;
                    }
                    else if (c == 92){ // Backslash teda escape seq
                      c = getchar();
                      state = STATE_P11;
                    }
                    else{
                      return LEXICAL_ERR;
                    }
                    continue;

                  case (STATE_P11): //Riešime či escape alebo nah
                    if (c > 31 && c != 92 && c != 39 && c != 44 c != n && c != t){//nebola
                      stringAddChar(s,'\\');
                      stringAddChar(s,c);
                      c = getchar();
                      state = STATE_P10;
                    }
                    else if (c == 92 || c == 39 || c == 34){//  _/_'_"_
                      stringAddChar(s,c);
                      c = getchar();
                      state = STATE_P10;
                    }
                    else if (c == n){ // Spraví EOL
                      stringAddChar(s,EOL); /////////////////hmmm check?
                      c = getchar();
                      state = STATE_P10;
                    }
                    else if (c == t){ // Spraví TAB
                      stringAddChar(s,'\t'); /////////////////hmmm check?
                      c = getchar();
                      state = STATE_P10;
                    }
                    else if (c == x){ //Bude robiť HEX
                      c = getchar();
                      state = STATE_P12;
                    }
                    else {
                      return LEXICAL_ERR;
                    }
                    continue;

                  case (STATE_P12): //Riešime prvú hex val
                    if ( (c >= 48 && c <= 57) || (c >= 65 && c <= 70) || (c >= 97 && c >= 102)){ // 0..9 || A..F || a..f
                      char hexvalue[3];
                      hexvalue[0] = c;
                      c = getchar();
                      state = STATE_P13;
                    }
                    else {
                      return LEXICAL_ERR;
                    }
                    continue;

                  case (STATE_P13): //Riešime druhú hex val
                    if ( (c >= 48 && c <= 57) || (c >= 65 && c <= 70) || (c >= 97 && c >= 102)){ // 0..9 || A..F || a..f
                      hexvalue[1] = c;
                      int decvalue = (int)strtol(hexvalue, NULL, 16); //convertne hexvalue na int v decimáloch
                      char tmp[2];
                      sprintf(tmp,"%c",decvalue); //convertnem decvalue na ASCII znak
                      c = *tmp;
                      stringAddChar(s,c);
                      c = getchar();
                      state = STATE_P10;
                    }
                    else {
                      return LEXICAL_ERR;
                    }
                    continue;

                  case (STATE_F22): //Koniec
                      Token.attribute.string = s;
                      Token.type = LITERAL;
                      state = STATE_START;
                      c = getchar();

                    break;
              }
              break;
        }





      }


    }
  }
}
return Token;
}
