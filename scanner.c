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
#define STATE_NUMBR 106
#define STATE_NUFLT 107
#define STATE_NUEXP 109
#define STATE_NUSGN 110
#define STATE_NUEND 111
#define STATE_STRNG 112
#define STATE_STRLT 113
#define STATE_ESCAP 114




 FILE *SourceFile;
 //smartString *s = malloc(sizeof(smartString));


token nextToken() {
  token Token;

  char c,tmp;

  c = getchar()
  while((c = getchar() != EOF){
    smartString *s = malloc(sizeof(smartString)); //check
    if (smartString == NULL){

    }
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

      case ';':
        smartString *s = malloc(sizeof(smartString));
        if (s == NULL){
            return INTERN_ERR;
        }
        stringInit(s);
        stringAddChar(s,';');
        Token.attribute.string = s;

        Token.type = SEMICOLON;
        break;

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
          if ((c = getchar) != '"')
            if ((c = getchar) != '"')
              if ((c = getchar) != '"')
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
      if (isalpha(c) || c == '_'){
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

      if (isalnum(c)){
        smartString *s = malloc(sizeof(smartString));
        stringInit(s);
        if (s == NULL){
            return INTERN_ERR;
        }
        stringAddChar(s,c);

        getchar(c);
        while (1) {
          if(c == 'E' || c == 'e'){

          }
          else if(c == '.'){
            stringAddChar(s,c);
            c = getchar();
            if (!(isalnum(c)))
              return LEXICAL_ERR;

          }
          else if(isalnum(c)){
            stringAddChar(s,c);
            c = getchar();
            continue;
          }



        }



      }




    }




  }

}
